"""
    armgcc.py

    Tool-specific initialization for the armgcc compiler.

    Copyright (c) 2014 Hyundai-Autron
"""
from SCons import Action
from SCons import Builder
from SCons import Util
from SCons import Warnings
from SCons import Errors
from SCons import Defaults
from SCons import Tool
import os, common, sys

class ToolArmGccWarning(Warnings.Warning):
    pass


class ArmGccGeneratorNotFound(ToolArmGccWarning):
    pass


Warnings.enableWarningClass(ToolArmGccWarning)

def _detect(env):
    try:
        gcc_compiler = env.WhereIs(os.path.basename(env['CC']))
        if gcc_compiler:
            return gcc_compiler
        print 'Please check your configuration, //SCons//Build//Compile//CompilerPath'
        sys.exit(-1)
    except KeyError:
        raise Errors.StopError(ArmGccGeneratorNotFound, 'Please check your configuration, //SCons//Build//Compile//CompilerPath')

    return os.path.exists(env['CC'])


moduleList = dict()
moduleList['bsw'] = [
 15, 16, 17, 18, 19, 20, 21, 22, 23,
 24, 25, 26, 27, 28, 29, 30,
 31, 32,
 33, 34, 35, 36, 37, 38, 39]
moduleList['mcal'] = [
 41, 42, 43, 44, 45, 46, 42, 41, 47, 48, 49, 50, 51,
 52, 53, 54,
 55, 56, 57, 58, 59]

def _make_lnk_file(target, source, env):
    try:
        f = open(env['_OPTIONFILE'], 'w')
    except IOError:
        print "scansrcs: Can't open Object list file '%s'" % env['_OPTIONFILE']
        return -1

    input_files = []
    input_files.extend(list(set(source)))
    input_files.sort()
    for aSource in input_files:
        f.write(aSource.path.replace(os.sep, '/') + '\n')

    f.close()
    return 0


def _is_ram(string):
    if string.startswith('4'):
        return 'RAM'
    return 'ROM'


def _getsize(size_str):
    size_str = size_str.split('+')[1]
    return int(size_str, 16)


def _print_memory_info(memory_info):
    print 'bsw : ' + str(memory_info['bsw'])
    print 'mcal : ' + str(memory_info['mcal'])
    print 'ETC : ' + str(memory_info['ETC'])
    print 'Total : ' + str(memory_info['Total'])


def _parse_armgcc_map(filename):
    memory_info = {'bsw': {module: {'ROM': 0, 'RAM': 0} for module in moduleList['bsw']}, 'mcal': {module: {'ROM': 0, 'RAM': 0} for module in moduleList['mcal']}, 'ETC': {'ROM': 0, 'RAM': 0}, 'Total': {'ROM': 0, 'RAM': 0}}
    map_file = open(filename, 'r')
    start_flag = False
    symbols = []
    not_assigned_list = []
    for aLine in map_file:
        if start_flag:
            if aLine.startswith(' .'):
                symbols += [aLine.split()]
            elif aLine.startswith(chr(12) + chr(10)):
                break
        if 'Global Symbols' in aLine:
            start_flag = True

    for aSymbol in symbols:
        find_flag = False
        ram_flag = _is_ram(aSymbol[1])
        size = _getsize(aSymbol[1])
        for key in moduleList.keys():
            for aModule in moduleList[key]:
                if aSymbol[2].lower().startswith(aModule.lower()):
                    find_flag = True
                    memory_info[key][aModule][ram_flag] += size
                    break

            if find_flag:
                break

        if not find_flag:
            not_assigned_list += [aSymbol[2]]
            memory_info['ETC'][ram_flag] += size
        memory_info['Total'][ram_flag] += size

    _print_memory_info(memory_info)


def _parse_map_file(target, source, env):
    options = env['LINKCOM_OPTION']
    if not isinstance(env['LINKCOM_OPTION'], list):
        options = options.split()
    for aFlag in options:
        if '-map' in aFlag:
            filename = env['DEBUG_DIR'] + os.sep + env['PROJECT'] + '.map'
            if os.path.exists(filename):
                _parse_armgcc_map(filename)
            break


def _modify_source_n_target(target, source, env):
    new_target = []
    for aSource in source:
        for aCSuffix in env['CSuffixes']:
            if not aCSuffix.startswith('.'):
                aCSuffix = '.' + aCSuffix
            if aSource.path.endswith(aCSuffix):
                new_path = os.path.join(env['DEBUG_DIR'], aSource.path[:-len(aCSuffix)] + env['OBJSUFFIX'])
                new_target += [new_path]
                break

    return (
     new_target, source)


def _armgcc_compile_func(env, source, **kw):
    _armgcc_compiler = Builder.Builder(action=[
     Action.Action('$CCCOM', strfunction=common.print_compile_command)], emitter=_modify_source_n_target, prefix='$OBJPREFIX', suffix='$OBJSUFFIX', src_builder=[
     'CFile', 'CXXFile'], src_suffix=env['CSuffixes'], source_scanner=Tool.SourceFileScanner, single_source=1)
    result = _armgcc_compiler.__call__(env, None, source, **kw)
    return result


def _armgcc_archive_func(env, target, source, **kw):
    _library_action = Action.Action('$ARCHIVE_COM', '$ARCHIVE_COMSTR')
    _armgcc_archiver = Builder.Builder(action=[
     Action.Action(_make_lnk_file, (lambda *arg: 'Making obj list for library'), varlist=['_OPTIONFILE']),
     Action.Action(_library_action, 'Making library')], prefix='$LIBPREFIX', suffix='$LIBSUFFIX', src_suffix='$OBJSUFFIX', ensure_suffix=True)
    kw['_OPTIONFILE'] = env['DEBUG_DIR'] + os.sep + env['_LIBLIST']
    result = _armgcc_archiver.__call__(env, target, source, **kw)
    env.Clean(result, kw['_OPTIONFILE'])
    return result


def _armgcc_link_func(env, target, source, **kw):
    try:
        linkscript_file = env['LINKSCRIPT']
        linkscript_file = linkscript_file.replace('\\', '/')
    except KeyError:
        linkscript_file = kw['LINKSCRIPT']

    _armgcc_linker = Builder.Builder(action=[
     Action.Action(_make_lnk_file, (lambda *arg: 'Making object list file')),
     Defaults.LinkAction,
     Action.Action('$OBJCOPY_COM', 'Making binary file')], emitter='$PROGEMITTER', prefix='$PROGPREFIX', suffix='$PROGSUFFIX', src_suffix='$OBJSUFFIX', src_builder='Object', target_scanner=Tool.ProgramScanner, ensure_suffix=True)
    kw['_OPTIONFILE'] = os.path.join(env['DEBUG_DIR'], env['_ELFLIST'])
    result = _armgcc_linker.__call__(env, target, source, **kw)
    env.Depends(result, linkscript_file)
    env.Clean(result, env['DEBUG_DIR'])
    env.Clean(result, kw['_OPTIONFILE'])
    return result


def generate(env, **kw):
    """Add Builders and construction variables to the Environment."""
    env['CC'] = kw['CC']
    _detect(env)
    if not kw['AR']:
        env['AR'] = os.path.join(os.path.dirname(kw['CC']), 'arm-none-eabi-ar.exe')
    else:
        env['AR'] = kw['AR']
    if not kw['LINK']:
        env['LINK'] = os.path.join(os.path.dirname(kw['CC']), 'arm-none-eabi-ld.exe')
    else:
        env['LINK'] = kw['LINK']
    env['AS'] = os.path.join(os.path.dirname(kw['CC']), 'arm-none-eabi-as.exe')
    env['OBJCOPY'] = os.path.join(os.path.dirname(kw['CC']), 'arm-none-eabi-objcopy.exe')
    env['OPTION_FILE_SUFFIX'] = '.opt'
    env['OPTION_FILE_PREFIX'] = '@'
    env['LINK_OPTION_FILE_PREFIX'] = '-cmd='
    env['OPTION_VIA_FILE'] = common.OptionViaFile
    env['CCFLAGS'] = []
    if not env['CSuffixes']:
        env['CSuffixes'] = [
         '.c', '.C', '.s', '.S']
    env['ASMSuffixes'] = [
     '.s']
    env['CPPDEFPREFIX'] = '-D'
    env['CPPDEFINES'] = []
    env['LIBSUFFIX'] = '.a'
    env['OBJSUFFIX'] = '.o'
    env['PROGSUFFIX'] = '.elf'
    env['CPPPATH'] = [
     '.',
     '$INCLUDE_PATH']
    env['INCPREFIX'] = '-I'
    env['_CPPINCFLAGS'] = '${_concat(INCPREFIX, CPPPATH, INCSUFFIX, __env__)}'
    env['_CCCOMCOM'] = '$CPPFLAGS $_CPPDEFFLAGS $_CPPINCFLAGS'
    env['CCCOM_OPTION'] = [
     42,
     43,
     44,
     45,
     46,
     47]
    env['CCCOM'] = '$CC ${OPTION_VIA_FILE("$OPTION_FILE_PREFIX", "$CCCOM_OPTION")}'
    env['ARCHIVE_COM_OPTION'] = [
     'rscv $TARGET',
     '$SOURCES']
    env['ENTRYPOINT'] = 'Reset_Handler'
    env['ARCHIVE_COM'] = '$AR ${OPTION_VIA_FILE("$OPTION_FILE_PREFIX", "$ARCHIVE_COM_OPTION")}'
    env['ARCHIVE_COMSTR'] = 'Making library($TARGETS.file)'
    env['ASCOM'] = '$AS -mcpu=cortex-m7 -o $TARGET @${DEBUG_DIR}/$_ASMLIST'
    env['ASCOMSTR'] = 'Making library($TARGETS.file)'
    env['OBJCOPY_COM'] = '$OBJCOPY -O binary $DEBUG_DIR/${PROJECT}.elf $DEBUG_DIR/${PROJECT}.bin'
    if not env['LINKFLAGS']:
        env['LINKFLAGS'] = []
    if not env['LIBS']:
        env['LIBS'] = []
    if not env['LIBPATH']:
        env['LIBPATH'] = []
    env['_LIBLIST'] = 'listForLib'
    env['_ELFLIST'] = 'listForElf'
    env['LINKCOM_OPTION'] = [
     47,
     71,
     72,
     73,
     74,
     75,
     76,
     42]
    env['LINKCOM'] = '$LINK ${OPTION_VIA_FILE("$LINK_OPTION_FILE_PREFIX", "$LINKCOM_OPTION")}'
    env['LINKCOMSTR'] = 'Making binary($TARGETS.file)'
    env['LIBDIRPREFIX'] = '-L'
    env['LIBDIRSUFFIX'] = ''
    env['_LIBDIRFLAGS'] = '${_concat(LIBDIRPREFIX, LIBPATH, LIBDIRSUFFIX, __env__)}'
    env['LIBLINKPREFIX'] = '-l'
    env['LIBLINKSUFFIX'] = ''
    env.AddMethod(_armgcc_compile_func, 'Object')
    env.AddMethod(_armgcc_archive_func, 'Library')
    env.AddMethod(_armgcc_link_func, 'Program')


def exists(env):
    _detect(env)