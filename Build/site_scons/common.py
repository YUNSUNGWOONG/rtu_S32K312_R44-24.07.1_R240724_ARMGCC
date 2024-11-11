# uncompyle6 version 3.9.2
# Python bytecode version base 2.7 (62211)
# Decompiled from: Python 3.10.11 (tags/v3.10.11:7d4cc5a, Apr  5 2023, 00:38:17) [MSC v.1929 64 bit (AMD64)]
# Embedded file name: D:\01_Project\09_R44\05_NGV\01_RTU\02_trunk\rtu_S32K312_R44_app\Build\site_scons\common.py
# Compiled at: 2024-07-24 15:56:59
"""
    common.py

    Tool-specific initialization for build process.

    Copyright (c) 2021 HYUNDAI AUTOEVER Corp.
    
/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By           Description                          **
********************************************************************************
** 2.6.0      08-Jan-2024   SY Han       BUGCLASSIC-671
*******************************************************************************/
"""
import sys, autronlogger, os
from re import *
from xml.etree.ElementTree import parse
from xml.etree import ElementTree as ET
import datetime, sort_scons
from collections import OrderedDict
_compile_count = 0

def print_to_log(env, msg_lines):
    if os.path.exists(env['SCONS_LOG_FILE']):
        curr_size = os.path.getsize(env['SCONS_LOG_FILE'])
        max_size = 50000000
        if curr_size > max_size:
            os.remove(env['SCONS_LOG_FILE'])
            print ('deleted log file due to size greater than {0}bytes').format(str(max_size))
    with open(env['SCONS_LOG_FILE'], 'a+') as f:
        curr_time = str(datetime.datetime.now())
        f.write('\n' + curr_time)
        f.write(('\n').join(msg_lines))


def print_compile_command(target, source, env):
    global _compile_count
    _compile_count += 1
    return ('Compiling {src_count}th file : {src_name}').format(src_name=source[0].name, src_count=_compile_count)


def _get_pure_library_name(library_files):
    return map((lambda lib: os.path.basename(lib.path).replace('lib', '', 1).replace('.a', '')), library_files)


def get_library_name(library, library_path):
    import SCons
    return SCons.Util.flatten([
     _get_pure_library_name(library), _get_pure_library_name(SCons.Script.Glob(library_path + os.sep + 'lib*.a'))])


class ProgressCounter(object):
    count = 0
    interval = 10

    def __call__(self, node):
        self.count += self.interval
        sys.stdout.write(('Evaluated {node_count}th file: {node_name} \r').format(node_name=node, node_count=self.count))
        sys.stdout.flush()


def decide_if_changed(dependency, target, prev_ni):
    is_changed = False
    dep = str(dependency)
    tgt = str(target)
    if not os.path.exists(tgt):
        print (
         "Target don't exists:", tgt)
        return True
    if 'csig' not in dir(prev_ni):
        print (
         'No target was built yet:', dep)
        return True
    new_csig = dependency.get_csig()
    new_time = dependency.get_timestamp()
    new_size = dependency.get_size()
    old = target.get_stored_info().binfo
    old.prepare_dependencies()
    old_bkids = old.bsources + old.bdepends + old.bimplicit
    old_bkidsigs = old.bsourcesigs + old.bdependsigs + old.bimplicitsigs
    osig = dict(zip(old_bkids, old_bkidsigs))
    print 'trg:' + str(tgt)
    for src_file, info in osig.iteritems():
        print 'src:' + str(src_file)
        print 'info:' + str(info)

    if new_csig != prev_ni.csig:
        if dependency.get_text_contents() != target.get_text_contents():
            if dep.endswith('.arxml'):
                is_changed = True
            elif dependency.get_size() != prev_ni.size:
                is_changed = True
    return is_changed


def setting(env):
    import SCons
    SCons.Script.Main.AddOption('--progress', dest='progress', type='string', default=None, action='store', help='print additional information')
    if '--progress=ProgressCounter' in sys.argv:
        SCons.Script.Main.Progress(ProgressCounter(), interval=ProgressCounter.interval)
    env.Decider('MD5-timestamp')
    autronlogger.AutronLogger(env)
    return


def gen_emitter(target, source, env):
    import SCons
    new_target, new_source = [], []
    output_dir = env['OUTPUTDIR'].replace('/', os.sep)
    for aTarget in target:
        t_path = ''
        if type(aTarget) == SCons.Node.FS.File:
            t_path = aTarget.path
        elif type(aTarget) == str:
            t_path = aTarget
        else:
            print ('Found unknown type {0}').format(aTarget)
            continue
        if t_path.lower().startswith(output_dir.lower()):
            if t_path.lower().split('.')[-1] in env['CSuffixes'] + ['h'] + env['MATCH_PATTERN']:
                new_target.append(t_path)
            else:
                print ('Invalid target, ignoring file {0} for generation').format(t_path)
        else:
            print ('Invalid target, ignoring file {0} for generation').format(t_path)

    for aSource in source:
        if type(aSource) == SCons.Node.FS.File:
            s_name = aSource.name
        elif type(aSource) == str:
            s_name = aSource
        else:
            print ('Found unknown type {0}').format(aSource)
            continue
        if s_name.lower().split('.')[-1] in env['MATCH_PATTERN'] and s_name != 'BswMdt.arxml':
            if s_name in env['files'].keys():
                s_path = env['files'][s_name]
                new_source += [os.path.join(s_path)]
            elif s_name.startswith('Swcd_'):
                s_path = os.path.join(output_dir, 'swcd', s_name)
                env['files'][s_name] = s_path
                new_source += [os.path.join(s_path)]
            elif s_name.startswith('Bswmd_'):
                s_path = os.path.join(output_dir, 'bswmd', s_name)
                env['files'][s_name] = s_path
                new_source += [os.path.join(s_path)]
            elif search('ioc', s_name, I):
                s_path = os.path.join(output_dir, 'xml', s_name)
                env['files'][s_name] = s_path
                new_source += [os.path.join(s_path)]
            else:
                t_name = env['MODULE_NAME'].split('.')[0]
                print ('Source file "{0}" is not found for target file "{1}" (will be ignored as an input)').format(s_name, t_name)

    return (
     list(OrderedDict.fromkeys(new_target)), list(OrderedDict.fromkeys(new_source)))


def _config_arxml(b_cmd, cmd_dict, arxml_file, fbl_str):
    build_cmds = {'Build': False, 'Compile': False, 'Release': False}
    if fbl_str != '':
        cmd_key = b_cmd.split(fbl_str)[0]
    else:
        cmd_key = b_cmd
    sort_arxml_flag = False
    arxml_tree = parse(arxml_file)
    arxml_root = arxml_tree.getroot()
    arxml_tag_prefix = arxml_root.tag.split('}')[0] + '}'
    arxml_parent_map = dict((c, p) for p in arxml_tree.getiterator() for c in p)
    _copyToCProject = False
    arxml_iterator = list(arxml_root.getiterator(('{0}{1}').format(arxml_tag_prefix, 'ECUC-NUMERICAL-PARAM-VALUE')))
    tag_name = '/AUTRON/SCons/Build/CopyToCProject'
    for item in arxml_iterator:
        curr_tag = item.find(("./[{0}DEFINITION-REF='{1}']").format(arxml_tag_prefix, tag_name))
        if not curr_tag == None:
            curr_val = item.find(('{0}VALUE').format(arxml_tag_prefix))
            if curr_val.text == '1' or curr_val.text == 'true':
                _copyToCProject = True
            break

    if _copyToCProject == True:
        return
    else:
        remove_element = []
        element_found = False
        arxml_iterator = list(arxml_root.getiterator(('{0}{1}').format(arxml_tag_prefix, 'ECUC-CONTAINER-VALUE')))
        tag_name = '/AUTRON/SCons/Build/Compile/CompileCmdChoice/' + cmd_key + '/ExcludeList'
        for item in arxml_iterator:
            a_items = item.findall((".//*[{0}DEFINITION-REF='{1}']").format(arxml_tag_prefix, tag_name))
            for a_item in a_items:
                element_found = True
                curr_val = a_item.find(('{0}VALUE').format(arxml_tag_prefix))
                if not curr_val == None:
                    build_cmds[cmd_key] = True
                    for val in curr_val.text.split(','):
                        val = val.replace(os.sep, '/')
                        if val in cmd_dict[b_cmd]:
                            cmd_dict[b_cmd].remove(val)
                        else:
                            remove_element.append(a_item)

            if element_found:
                break

        for _ele in remove_element:
            arxml_parent_map[_ele].remove(_ele)
            sort_arxml_flag = True

        element_found = False
        if len(cmd_dict[b_cmd]) > 0:
            arxml_iterator = list(arxml_root.getiterator(('{0}{1}').format(arxml_tag_prefix, 'ECUC-CONTAINER-VALUE')))
            for item in arxml_iterator:
                tag_name = '/AUTRON/SCons/Build/Compile'
                top_element = item.find(("./[{0}DEFINITION-REF='{1}']").format(arxml_tag_prefix, tag_name))
                if top_element == None:
                    continue
                sub_container = top_element.find(('./{0}SUB-CONTAINERS').format(arxml_tag_prefix))
                if not sub_container == None:
                    if build_cmds[cmd_key] == False:
                        sub_element = ET.Element(('{0}ECUC-CONTAINER-VALUE').format(arxml_tag_prefix))
                        sub_element.text = '\n'
                        sub_element.tail = '\n'
                        _item = ET.SubElement(sub_element, ('{0}SHORT-NAME').format(arxml_tag_prefix))
                        _item.text = cmd_key
                        _item.tail = '\n'
                        _item = ET.SubElement(sub_element, ('{0}DEFINITION-REF').format(arxml_tag_prefix), {'DEST': 'ECUC-CHOICE-CONTAINER-DEF'})
                        _item.text = '/AUTRON/SCons/Build/Compile/CompileCmdChoice'
                        _item.tail = '\n'
                        top_element1 = ET.SubElement(sub_element, ('{0}SUB-CONTAINERS').format(arxml_tag_prefix))
                        top_element1.text = '\n'
                        top_element1.tail = '\n'
                        sub_element1 = ET.SubElement(top_element1, ('{0}ECUC-CONTAINER-VALUE').format(arxml_tag_prefix))
                        sub_element1.text = '\n'
                        sub_element1.tail = '\n'
                        _item = ET.SubElement(sub_element1, ('{0}SHORT-NAME').format(arxml_tag_prefix))
                        _item.text = cmd_key
                        _item.tail = '\n'
                        _item = ET.SubElement(sub_element1, ('{0}DEFINITION-REF').format(arxml_tag_prefix), {'DEST': 'ECUC-PARAM-CONF-CONTAINER-DEF'})
                        _item.text = '/AUTRON/SCons/Build/Compile/CompileCmdChoice/' + cmd_key
                        _item.tail = '\n'
                        sub_element2 = ET.SubElement(sub_element1, ('{0}PARAMETER-VALUES').format(arxml_tag_prefix))
                        sub_element2.text = '\n'
                        sub_element2.tail = '\n'
                        sub_element3 = ET.SubElement(sub_element2, ('{0}ECUC-TEXTUAL-PARAM-VALUE').format(arxml_tag_prefix))
                        sub_element3.text = '\n'
                        sub_element3.tail = '\n'
                        _item = ET.SubElement(sub_element3, ('{0}DEFINITION-REF').format(arxml_tag_prefix), {'DEST': 'ECUC-STRING-PARAM-DEF'})
                        _item.text = '/AUTRON/SCons/Build/Compile/CompileCmdChoice/' + cmd_key + '/ExcludeList'
                        _item.tail = '\n'
                        _item = ET.SubElement(sub_element3, ('{0}VALUE').format(arxml_tag_prefix))
                        _item.text = (',').join(cmd_dict[b_cmd])
                        _item.tail = '\n'
                        sort_arxml_flag = True
                        sub_container.append(sub_element)
                    else:
                        tag_name = '/AUTRON/SCons/Build/Compile/CompileCmdChoice/' + cmd_key + '/ExcludeList'
                        _element = sub_container.find((".//*[{0}DEFINITION-REF='{1}']/..").format(arxml_tag_prefix, tag_name))
                        if not _element == None:
                            _item = ET.Element(('{0}ECUC-TEXTUAL-PARAM-VALUE').format(arxml_tag_prefix))
                            _item.text = '\n'
                            _item.tail = '\n'
                            _item1 = ET.SubElement(_item, ('{0}DEFINITION-REF').format(arxml_tag_prefix), {'DEST': 'ECUC-STRING-PARAM-DEF'})
                            _item1.text = tag_name
                            _item1.tail = '\n'
                            _item1 = ET.SubElement(_item, ('{0}VALUE').format(arxml_tag_prefix))
                            _item1.text = (',').join(cmd_dict[b_cmd])
                            _item1.tail = '\n'
                            _element.append(_item)
                            sort_arxml_flag = True

        if sort_arxml_flag == True:
            ET.register_namespace('', 'http://autosar.org/schema/r4.0')
            arxml_tree.write(arxml_file, encoding='UTF-8', xml_declaration=True)
            sort_scons.sort_action(arxml_file)
            sort_arxml_pretty(arxml_file)
        return


def update_arxml_from_cproject(env, cproject_file):
    cmd_dict = {'Build': [], 'Compile': [], 'Debug': [], 'Rebuild': [], 'Release': [], 'BuildFBL': [], 'CompileFBL': [], 'ReleaseFBL': [], 'DebugFBL': [], 'FBL': [], 'Fbl': []}
    matched_items = None
    fbl_str = ''
    if any([x for x in env['COMPILE_RULE'] if search('fbl', x, I)]):
        fbl_str = 'FBL'
    tree = parse(cproject_file)
    root = tree.getroot()
    parent_map = dict((c, p) for p in tree.getiterator() for c in p)
    iterator = list(root.getiterator('configuration'))
    for a_cmd in cmd_dict.keys():
        for item in iterator:
            matched_items = item.find(("./[@description='{0}']/sourceEntries/entry").format(a_cmd))
            if matched_items == None:
                matched_items = item.find(("./[@name='{0}']/sourceEntries/entry").format(a_cmd))
            if not matched_items == None and 'excluding' in matched_items.attrib.keys():
                tmp_list = [f for f in sorted(list(matched_items.attrib['excluding'].split('|'))) if os.path.exists(f)]
                cmd_dict[a_cmd] = tmp_list

    if fbl_str == 'FBL':
        cmd_dict['FBL'].extend(cmd_dict['Fbl'])
        cmd_dict['Fbl'] == ''
    iterator = list(root.getiterator('cconfiguration'))
    change_flag = False
    for a_cmd in cmd_dict.keys():
        if a_cmd.lower().startswith(('release', 'debug')):
            continue
        if a_cmd.lower() == 'fbl':
            continue
        if a_cmd.lower().endswith('fbl') and fbl_str == '':
            continue
        if not a_cmd.lower().endswith('fbl') and fbl_str == 'FBL':
            continue
        if fbl_str == 'FBL':
            if not cmd_dict['FBL'] == []:
                cmd_dict['BuildFBL'].extend(cmd_dict['FBL'])
                cmd_dict['FBL'] = []
                print '"FBL" excluding list will be copied to "BuildFBL"'
        if cmd_dict[a_cmd] == []:
            print ('No excluding list found in .cproject for "{0}".').format(a_cmd)
            if not cmd_dict['Build' + fbl_str] == '':
                cmd_dict[a_cmd] = list(sorted(set(cmd_dict['Build' + fbl_str])))
                print ('"Build{0}" excluding list will be copied to "{1}"').format(fbl_str, a_cmd)

    for a_cmd in cmd_dict.keys():
        if a_cmd.lower() == 'fbl':
            continue
        if a_cmd.lower().endswith('fbl') and fbl_str == '':
            continue
        if not a_cmd.lower().endswith('fbl') and fbl_str == 'FBL':
            continue
        if cmd_dict[a_cmd] == []:
            print ('excluding list was not set for "{0}" in .cproject').format(a_cmd)
            continue
        fnd_item = [i for i in iterator if not i.find('./storageModule/configuration') == None]
        if not any([x for x in fnd_item if x == None]):
            match_str = ("./storageModule/configuration/[@description='{0}']/sourceEntries/entry").format(a_cmd)
            fnd_name = [i for i in iterator if not i.find(match_str) == None]
            match_str = ("./storageModule/configuration/[@name='{0}']/sourceEntries/entry").format(a_cmd)
            fnd_name.extend([i for i in iterator if not i.find(match_str) == None])
            if len(fnd_name) == 0:
                _ele = _set_sample_cproject(env, a_cmd, cmd_dict[a_cmd])
                if not _ele == None:
                    change_flag = True
                    parent_map[fnd_item[0]].append(_ele)
                    print ('Sample configuration added in .cproject for "{0}".').format(a_cmd)

    if fbl_str == 'FBL':
        for n in ['FBL', 'Fbl']:
            match_str = ("./storageModule/configuration/[@name='{0}']/sourceEntries/entry").format(n)
            fnd_item = [i for i in iterator if not i.find(match_str) == None]
            if len(fnd_item) == 0:
                match_str = ("./storageModule/configuration/[@description='{0}']/sourceEntries/entry").format(n)
                fnd_item = [i for i in iterator if not i.find(match_str) == None]
            if len(fnd_item) > 0:
                parent_map[fnd_item[0]].remove(fnd_item[0])
                change_flag = True
                print ('"{0}" rule is deprecated. It will be removed.').format(n)

    if not any([f for f in cmd_dict.values() if not f == '']):
        return
    else:
        if change_flag == True:
            with open(cproject_file, 'wb') as f:
                f.write('<?xml version="1.0" encoding="UTF-8" standalone="no"?>')
                f.write('<?fileVersion 4.0.0?>')
                tree.write(f, encoding='UTF-8', xml_declaration=False)
            sort_arxml_pretty(cproject_file)
        for a_cmd in cmd_dict.keys():
            cmd_dict[a_cmd][:] = [d for d in cmd_dict[a_cmd] if os.path.exists(d)]

        if fbl_str == 'FBL':
            arxml_file = os.path.join(env['CONFIG_SCRIPT_DIR'], 'SCons_FBL.arxml')
        else:
            arxml_file = os.path.join(env['CONFIG_SCRIPT_DIR'], 'SCons.arxml')
        if os.path.isfile(arxml_file):
            for _cmd in env['COMPILE_RULE']:
                if _cmd in cmd_dict.keys() and not cmd_dict[_cmd] == '':
                    _config_arxml(_cmd, cmd_dict, arxml_file, fbl_str)

        return


def sort_arxml_pretty(arxml_file):
    prev_tag, prev_txt, changed_txt = [], [], []
    tab_str = ''
    f = open(arxml_file, 'r+')
    prev_txt = f.readlines()
    f.close()
    prev_txt = [l.replace('><', '>\n<') for l in prev_txt]
    for line in prev_txt:
        for l in line.split('\n'):
            if l == '':
                continue
            tab_str = '  ' * len(prev_tag)
            if not l.startswith('<?'):
                pattern_start = compile('(?:\\s*)(<[a-zA-Z\\-]+)(\\s*.*>)(.*)')
                pattern_end = compile('(?:\\s*)(</[a-zA-Z\\-]+)(\\s*.*>)(.*)')
                pattern_end2 = compile('(?:\\s*<.*)(/>)(\\s*)')
                _tmp_start = search(pattern_start, l)
                _tmp_end = search(pattern_end, l)
                _tmp_end2 = search(pattern_end2, l)
                if not _tmp_start == None and _tmp_end == None:
                    if _tmp_end2 == None:
                        prev_tag.insert(0, _tmp_start.group(1).replace('<', '</'))
                elif _tmp_start == None and not _tmp_end == None:
                    prev_tag.remove(_tmp_end.group(1))
                    tab_str = '  ' * len(prev_tag)
            changed_txt.append(tab_str + l.lstrip() + '\n')

    f = open(arxml_file, 'w+')
    f.seek(0)
    [f.write(l) for l in changed_txt]
    f.truncate()
    f.close()
    return


def _set_sample_cproject(env, a_cmd, file_list):
    sample_file = os.path.join(env['BUILD_SCRIPT_DIR'], 'dummy', '_cproject')
    if not os.path.exists(sample_file):
        return
    else:
        tree = parse(sample_file)
        root = tree.getroot()
        parent_map = dict((c, p) for p in tree.getiterator() for c in p)
        iterator = list(root.getiterator('storageModule'))
        top_element = None
        for item in iterator:
            matched_item = item.find((".//storageModule/configuration/[@description='{0}']").format(a_cmd))
            if matched_item == None:
                matched_item = item.find((".//storageModule/configuration/[@name='{0}']").format(a_cmd))
            if not matched_item == None:
                entry = matched_item.find('./sourceEntries/entry/[@excluding]')
                if not entry == None:
                    entry.attrib['excluding'] = ('|').join([s.replace(os.sep, '/') for s in file_list])
                    if entry.attrib['excluding'] == '':
                        print ('Sample "{0}"\'s exclude list is empty,').format(a_cmd) + 'Please check your configuration if different.'
                top_element = parent_map[parent_map[matched_item]]
                break

        return top_element


def update_cproject(env, cproject_file):
    cmd_dict = {'Build': '', 
       'Compile': '', 'BuildFBL': '', 
       'CompileFBL': '', 'Release': '', 
       'ReleaseFBL': '', 'Debug': '', 
       'DebugFBL': '', 'Rebuild': ''}
    try:
        tree = parse(cproject_file)
    except IOError as e:
        print ("File .cproject doesn't exist, {0}").format(e.message)
        sys.exit(-1)

    root = tree.getroot()
    parent_map = dict((c, p) for p in tree.getiterator() for c in p)
    iterator = list(root.getiterator('configuration'))
    file_change = False
    for a_cmd in cmd_dict.keys():
        for item in iterator:
            matched_items = item.find(("./[@description='{0}']/sourceEntries/entry").format(a_cmd))
            if matched_items == None:
                matched_items = item.find(("./[@name='{0}']/sourceEntries/entry").format(a_cmd))
            if not matched_items == None and 'excluding' in matched_items.attrib.keys():
                if any([x for x in env['COMPILE_RULE'] if search('fbl', x.lower())]):
                    if a_cmd.lower() in ('buildfbl', 'rebuildfbl'):
                        matched_items.attrib['excluding'] = ('|').join([s.replace(os.sep, '/') for s in env['BUILD_EXCLUDE'] if os.path.exists(s)])
                        tmp_list = matched_items.attrib['excluding'].split('|')
                        tmp_list = list(set(sorted(tmp_list)))
                        matched_items.attrib['excluding'] = ('|').join(tmp_list)
                        file_change = True
                    elif a_cmd.lower() in ('compilefbl', ):
                        matched_items.attrib['excluding'] = ('|').join([s.replace(os.sep, '/') for s in env['COMPILE_EXCLUDE'] if os.path.exists(s)])
                        tmp_list = matched_items.attrib['excluding'].split('|')
                        tmp_list = list(set(sorted(tmp_list)))
                        matched_items.attrib['excluding'] = ('|').join(tmp_list)
                        file_change = True
                    elif a_cmd.lower() in ('releasefbl', 'debugfbl'):
                        matched_items.attrib['excluding'] = ('|').join([s.replace(os.sep, '/') for s in env['RELEASE_EXCLUDE'] if os.path.exists(s)])
                        tmp_list = matched_items.attrib['excluding'].split('|')
                        tmp_list = list(set(sorted(tmp_list)))
                        matched_items.attrib['excluding'] = ('|').join(tmp_list)
                        file_change = True
                elif a_cmd.lower() in ('build', 'rebuild'):
                    matched_items.attrib['excluding'] = ('|').join([s.replace(os.sep, '/') for s in env['BUILD_EXCLUDE'] if os.path.exists(s)])
                    tmp_list = matched_items.attrib['excluding'].split('|')
                    tmp_list = list(set(sorted(tmp_list)))
                    matched_items.attrib['excluding'] = ('|').join(tmp_list)
                    file_change = True
                elif a_cmd.lower() in ('compile', ):
                    matched_items.attrib['excluding'] = ('|').join([s.replace(os.sep, '/') for s in env['COMPILE_EXCLUDE'] if os.path.exists(s)])
                    tmp_list = matched_items.attrib['excluding'].split('|')
                    tmp_list = list(set(sorted(tmp_list)))
                    matched_items.attrib['excluding'] = ('|').join(tmp_list)
                    file_change = True
                elif a_cmd.lower() in ('release', 'debug'):
                    matched_items.attrib['excluding'] = ('|').join([s.replace(os.sep, '/') for s in env['RELEASE_EXCLUDE'] if os.path.exists(s)])
                    tmp_list = matched_items.attrib['excluding'].split('|')
                    tmp_list = list(set(sorted(tmp_list)))
                    matched_items.attrib['excluding'] = ('|').join(tmp_list)
                    file_change = True

    if file_change == True:
        with open(cproject_file, 'wb') as f:
            f.write('<?xml version="1.0" encoding="UTF-8" standalone="no"?><?fileVersion 4.0.0?>')
            tree.write(f, encoding='UTF-8', xml_declaration=False)
    return


def get_generation_option_by_arxml(arxmlfile):
    module_list = []
    try:
        rootElement = parse(arxmlfile).getroot()
        tag_prefix = rootElement.tag.split('}')[0] + '}'
        for a in rootElement.iter(tag_prefix + 'ECUC-MODULE-CONFIGURATION-VALUES-REF'):
            module_list.append(a.text.split('/')[-1])

    except Exception as e:
        print e.message

    return module_list


def _search_by_tagname_with_attrib(arxml_file, t_name, attrib_name, first_match=False):
    name_list = []
    try:
        arxml_file = os.path.normpath(arxml_file)
        rootElement = parse(arxml_file).getroot()
        tag_prefix = rootElement.tag.split('}')[0] + '}'
        for a in rootElement.iter(tag_prefix + t_name):
            if a.attrib['DEST'] == attrib_name:
                name_list += [a.text.split('/')[-1]]
                if first_match:
                    break

    except KeyError:
        pass
    except Exception as e:
        print e.message

    return name_list


def get_value_by_tagname_with_attrib(arxml_file, t_name, attrib_name, param):
    f_value = []
    child_ele = []
    try:
        rootElement = parse(arxml_file).getroot()
        tag_prefix = rootElement.tag.split('}')[0] + '}'
        for a in rootElement.iter(tag_prefix + t_name):
            for k in a.getchildren():
                if k.attrib == {}:
                    continue
                if k.attrib['DEST'] == attrib_name and k.text.split('/')[-1] == param:
                    f_value.append([a.text for a in a.getchildren() if a.tag == tag_prefix + 'VALUE'][-1])

    except Exception as e:
        print e.message

    return f_value


def _get_value_from_element_name(arxml_file, ele_name):
    tree = parse(arxml_file)
    rootElement = tree.getroot()
    tag_prefix = rootElement.tag.split('}')[0] + '}'
    for a in rootElement.iter(tag_prefix + ele_name):
        return a.text

    return


def _get_config_from_ecud(arxml_file):
    my_dict = []
    arxml_tree = parse(arxml_file)
    arxml_root = arxml_tree.getroot()
    arxml_tag_prefix = arxml_root.tag.split('}')[0] + '}'
    arxml_parent_map = dict((c, p) for p in arxml_tree.getiterator() for c in p)
    arxml_iterator = list(arxml_root.getiterator(('{0}{1}').format(arxml_tag_prefix, 'ECUC-CONTAINER-VALUE')))
    for item in arxml_iterator:
        my_dict += [{'name': '', 'def': '', 'param': []}]
        _name = item.find(('{0}SHORT-NAME').format(arxml_tag_prefix))
        _def = item.find(('{0}DEFINITION-REF').format(arxml_tag_prefix))
        _par = item.find(('{0}PARAMETER-VALUES').format(arxml_tag_prefix))
        if not _name == None and not _def == None and not _par == None and not _name.text == '' and not _def.text == '':
            my_dict[-1]['name'] = _name.text
            my_dict[-1]['def'] = _def.text
            for v_item in _par.getchildren():
                my_dict[-1]['param'] += [{'path': '', 'val': ''}]
                _ref = v_item.find(('{0}DEFINITION-REF').format(arxml_tag_prefix))
                _val = v_item.find(('{0}VALUE').format(arxml_tag_prefix))
                if not _ref == None and not _val == None and not _ref.text == '' and not _val.text == '':
                    my_dict[-1]['param'][-1]['path'] = _ref.text
                    my_dict[-1]['param'][-1]['val'] = _val.text

    return my_dict


def _get_config_from_bswmd(arxml_file):
    element_dict = {}
    return element_dict


def _get_config_from_swcd(arxml_file):
    element_dict = {
     'SHORT-NAME', 'DEFINITION-REF', 'PARAMETER-VALUES', 'SUB-CONTAINERS'}
    return element_dict


def get_element_from_shortname(arxml_file, type):
    ele_dict = {}
    if type == 'Ecud':
        ele_dict = _get_config_from_ecud(arxml_file)
    elif type == 'Bswmd':
        ele_dict = _get_config_from_bswmd(arxml_file)
    elif type == 'Swc':
        ele_dict = _get_config_from_swcd(arxml_file)
    return ele_dict


def get_modules_from_arxml(arxml_file):
    mod_list = []
    bsw_list = _search_by_tagname_with_attrib(arxml_file, 'ECUC-VALUES', 'ECUC-MODULE-CONFIGURATION-VALUES-REF')
    for a in bsw_list:
        if a != 'DoIP':
            mod_list += [os.path.join(env['OUTPUTDIR'], 'inc', 'PduR_' + a + '.h')]

    return mod_list


def get_bsw_config_from_arxml(env, arxml_file):
    expect_file_list = []
    bsw_list = _search_by_tagname_with_attrib(arxml_file, 'VALUE-REF', 'ECUC-MODULE-CONFIGURATION-VALUES')
    for a in bsw_list:
        if a != 'DoIP':
            expect_file_list += [os.path.join(env['OUTPUTDIR'], 'inc', 'PduR_' + a + '.h')]

    return expect_file_list


def get_component_from_arxml(env, extract_file, rte_file):
    expect_file_list = []
    gen_output_dir = env['OUTPUTDIR']
    try:
        swc_list = _search_by_tagname_with_attrib(extract_file, 'TYPE-TREF', 'APPLICATION-SW-COMPONENT-TYPE')
        swc_list += _search_by_tagname_with_attrib(extract_file, 'TYPE-TREF', 'SERVICE-SW-COMPONENT-TYPE')
        swc_list += _search_by_tagname_with_attrib(extract_file, 'TYPE-TREF', 'COMPLEX-DEVICE-DRIVER-SW-COMPONENT-TYPE')
        swc_list += _search_by_tagname_with_attrib(extract_file, 'TYPE-TREF', 'ECU-ABSTRACTION-SW-COMPONENT-TYPE')
        for a in swc_list:
            m_name = a + '_MemMap.h'
            n_name = 'Rte_' + a + '.h'
            t_name = 'Rte_' + a + '_Type.h'
            expect_file_list += [os.path.join(gen_output_dir, 'inc', m_name),
             os.path.join(gen_output_dir, 'inc', n_name),
             os.path.join(gen_output_dir, 'inc', t_name)]

        bsw_list = _search_by_tagname_with_attrib(rte_file, 'VALUE-REF', 'BSW-MODULE-DESCRIPTION')
        for a in bsw_list:
            gen_path = os.path.dirname(gen_output_dir)
            post_fix = '_'
            if a == 'Wdg_76_Acw':
                a = 'Wdg_76_Acw_76_Acw'
                post_fix = ''
            elif any([f for f in env['files'] if f.endswith('Bswmd_' + a + '.arxml') and not env['files'][f].startswith(gen_path)]):
                bswmd_file = env['files']['Bswmd_' + a + '.arxml']
                if os.path.isfile(bswmd_file):
                    vendor_API = _get_value_from_element_name(bswmd_file, 'VENDOR-API-INFIX')
                    if vendor_API != None:
                        vendor_ID = _get_value_from_element_name(bswmd_file, 'VENDOR-ID')
                        a = a + '_' + vendor_ID + '_' + vendor_API
                        post_fix = ''
            t_name = 'SchM_' + a + post_fix + 'Type.h'
            s_name = 'SchM_' + a + '.h'
            expect_file_list += [os.path.join(gen_output_dir, 'inc', s_name),
             os.path.join(gen_output_dir, 'inc', t_name)]

    except Exception as e:
        try:
            err_msg = ('{0}: Error in line {1}, {2} ').format(e.filename, e.lineno, e.msg)
        except:
            err_msg = e.message

        print ('Please check your settings', err_msg)

    return expect_file_list


def do_indent(line, n):
    blank = ''
    for x in range(n):
        blank = blank + '   '

    return blank + line


def creat_yml_from_input(env, m_name, ver, options, yml_file, input_list):
    format_dot_arxml = '.arxml'
    input_file = ''
    old_lines = []
    if os.path.exists(yml_file):
        with open(yml_file, 'r') as f:
            old_lines = f.readlines()
    src_lines = []
    if not creat_yml_from_input.needFileDictionary:
        creat_yml_from_input.needFileDictionary = True
        for _path, _dir, _files in os.walk(os.getcwd()):
            for _filename in _files:
                creat_yml_from_input.fileDictionary[_filename] = _path

    input_list = [l.strip() for l in input_list]
    for s_input in input_list:
        file_found = False
        if s_input.find('.') == -1:
            s_input += format_dot_arxml
        rootdir = os.getcwd()
        if creat_yml_from_input.fileDictionary.get(s_input):
            input_file = os.path.join(creat_yml_from_input.fileDictionary.get(s_input), s_input)
            input_file = input_file.replace(rootdir + '\\', '')
            file_found = True
        if not file_found:
            if search('bswmd_', s_input.lower()):
                input_file = os.path.join(env['OUTPUTDIR'], 'bswmd', s_input)
                file_found = True
            elif search('swcd_', s_input.lower()):
                input_file = os.path.join(env['OUTPUTDIR'], 'swcd', s_input)
                file_found = True
            elif search('bsw_md', s_input.lower()):
                input_file = os.path.join(env['OUTPUTDIR'], 'xml', s_input)
                file_found = True
            elif s_input.lower().split('.')[-1] in env['MATCH_PATTERN']:
                input_file = os.path.join(env['OUTPUTDIR'], 'xml', s_input)
                file_found = True
        if file_found == True:
            src_line = '- ' + input_file.replace('/', os.sep)
            src_line = do_indent(src_line.strip(), 3)
            src_lines.append(src_line)

    new_lines = []
    if len(old_lines) == 0:
        ruleIdPath = ''
        ruleIdFound = False
        for _path, _dir, _files in os.walk(os.getcwd()):
            for _filename in _files:
                if _filename == 'ruleID.csv':
                    ruleIdPath = os.path.join(_path, _filename)
                    ruleIdPath = ruleIdPath.replace(rootdir + '\\', '')
                    ruleIdFound = True

        new_lines.append('modules:')
        if ruleIdFound:
            new_lines.append('   GenericValidationPath: ' + ruleIdPath)
    if m_name == 'Os_Common':
        m_name = 'OsCommon'
    new_lines.append(do_indent(m_name + ':', 1))
    option_lines = []
    for o in options:
        option_lines.append(do_indent(o.strip(), 3))

    if len(option_lines) > 0:
        new_lines.append(do_indent('ModuleOptions:', 2))
        new_lines.extend(option_lines)
    if ver == '':
        new_lines.append(do_indent('DefaultInputs:', 2))
    else:
        new_lines.append(do_indent(ver + ':', 2))
    new_lines.extend(src_lines)
    write_string = ('').join(old_lines) + '\n'
    write_string += ('\n').join(new_lines)
    with open(yml_file, 'w+') as f:
        f.write(write_string)


creat_yml_from_input.needFileDictionary = False
creat_yml_from_input.fileDictionary = {}

class OptionViaFile(object):

    def __init__(self, option, cmd):
        self.option = option
        self.cmd = cmd

    def __call__(self, target, source, env, for_signature):
        if for_signature:
            return self.option + self.cmd
        else:
            source = sorted(source, key=(lambda src: src.path))
            import SCons
            cmd = env.subst_list(self.cmd, SCons.Subst.SUBST_CMD, target, source)[0]
            if self.option == '$LINK_OPTION_FILE_PREFIX':
                prefix = env.subst('$LINK_OPTION_FILE_PREFIX')
                suffix = env.subst('$LINK_OPTION_FILE_SUFFIX')
            else:
                prefix = env.subst('$OPTION_FILE_PREFIX')
                suffix = env.subst('$OPTION_FILE_SUFFIX')
            cmd_str = ('\n').join(map(str, cmd))
            new_lib_dict = {}
            tmp_cmd_list = []
            if self.option == '$LINK_OPTION_FILE_PREFIX':
                if env['COMPILER_TYPE'] == 'ti':
                    if len(env['LIBPATH']) > 0 and len(env['LIBS']) > 0:
                        for p in env['LIBPATH']:
                            for root, dirs, files in os.walk(p):
                                for _lib in env['LIBS']:
                                    _lib_name = ('').join([env['LIBPREFIX'], _lib, env['LIBSUFFIX']])
                                    if _lib_name in files:
                                        new_lib_dict[_lib] = os.path.join(root, _lib_name)

                    tmp_cmd_list = cmd_str.split('\n')
                    for idx, a_cmd in enumerate(tmp_cmd_list):
                        tmp_lib = a_cmd.split(env['LIBLINKPREFIX'])[-1]
                        if tmp_lib in new_lib_dict.keys():
                            tmp_cmd_list.remove(a_cmd)
                            a_cmd = ('').join([env['LIBLINKPREFIX'], new_lib_dict[tmp_lib]])
                            tmp_cmd_list.insert(idx - 1, a_cmd)

                    cmd_str = ('\n').join([cmd for cmd in tmp_cmd_list if not cmd.startswith(env['LIBDIRPREFIX'])])
            option_filename = str(target.path.replace(os.sep, '/')) + suffix
            if len(os.getcwd() + option_filename) > 250:
                print 'Error : Path and file name exceeds 250 characters!'
                return -1
            try:
                with open(option_filename, 'w') as option_file:
                    cmd_str = cmd_str.replace(os.sep, '/')
                    option_file.write(cmd_str)
                    env.SideEffect(option_filename, target)
                    env.Clean(target, option_filename)
            except IOError:
                print "Can't open option file '%s'" % option_filename
                return -1

            return [prefix + option_filename]
