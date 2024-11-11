# uncompyle6 version 3.9.2
# Python bytecode version base 2.7 (62211)
# Decompiled from: Python 3.10.11 (tags/v3.10.11:7d4cc5a, Apr  5 2023, 00:38:17) [MSC v.1929 64 bit (AMD64)]
# Embedded file name: D:\01_Project\09_R44\05_NGV\01_RTU\02_trunk\rtu_S32K312_R44_app\Build\site_scons\build.py
# Compiled at: 2024-07-24 15:56:59
"""
    build.py

    Tool-specific initialization for build process.

    Copyright (c) 2021 HYUNDAI AUTOEVER Corp.
"""
import subprocess, time, multiprocessing, os, sys, shutil, re
from threading import Thread

def make_dir(dirname):
    if not os.path.exists(dirname):
        os.makedirs(dirname)


def get_log_filename(log_dir):
    time_str = time.strftime('%y-%m-%d_%H-%M-%S', time.localtime())
    time_filename = os.path.join(log_dir, time_str + '.log')
    last_filename = os.path.join(log_dir, 'last_build.log')
    return {'time': time_filename, 'last': last_filename}


def get_scons_path():
    try:
        scons_path = os.environ['SCONS_HOME']
    except KeyError:
        scons_path = 'D:\\ts_mirr\\scons\\scons-local-2.3.4'

    return os.path.join(scons_path, 'scons.py')


def get_python_path():
    try:
        python_path = os.environ['PYTHON_HOME']
    except KeyError:
        python_path = 'D:\\ts_mirr\\python\\Portable_Python_2.7.6.1\\App'

    return os.path.join(python_path, 'python.exe')


def tee_pipe(pipe, output_list):
    for line in pipe:
        for a_output in output_list:
            a_output.write(line)
            a_output.flush()


def tee(infile, files):
    """Print `infile` to `files` in a separate thread."""

    def fanout(infile, files):
        if isinstance(infile, list):
            target = [
             (' ').join(infile) + '\n']
        else:
            target = iter(infile.readline, '')
        for line in target:
            new_line = re.sub('\\r', '', line)
            for f in files:
                f.write(new_line)
                f.flush()

        if not isinstance(infile, list):
            infile.close()

    fanout_thread = Thread(target=fanout, args=(infile, files))
    fanout_thread.daemon = True
    fanout_thread.start()
    return fanout_thread


def teed_call(cmd_args, **kwargs):
    output_files = kwargs.pop('output_files', None)
    p = subprocess.Popen(cmd_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, **kwargs)
    threads = []
    if output_files is not None:
        threads.append(tee(cmd_args, output_files + [sys.stdout]))
        threads.append(tee(p.stdout, output_files + [sys.stdout]))
        threads.append(tee(p.stderr, output_files + [sys.stderr]))
    for t in threads:
        t.join()

    p.wait()
    return p


def build(argument_list=None, option=None):
    log_argument = ''
    if len(argument_list) == 0:
        argument_list = [
         'GenerateAll', 'Build']
    log_filename = get_log_filename('.log')
    scons_path = get_scons_path()
    python_path = get_python_path()
    script_path = sys.argv[:1][0].split('site_scons')[0]
    scons_script = '.\\' + script_path.split(os.getcwd())[-1] + 'site_scons\\SConstruct'
    make_dir('.log')
    with open(log_filename['time'], 'w') as this_time_log:
        with open(log_filename['last'], 'w') as last_log:
            for a_argument in argument_list:
                command = [
                 python_path,
                 scons_path,
                 '-f' + scons_script,
                 a_argument,
                 option['parallel']]
                if option['verbose']:
                    command += [
                     '--debug=explain']
                if len(option['tree']) > 0:
                    command += [
                     '--tree=prune']
                if option['clean']:
                    command += [
                     '-c']
                generate_process = teed_call(command, output_files=[this_time_log, last_log])
                if 0 != generate_process.returncode:
                    return generate_process.returncode

    return generate_process.returncode


def get_value_from_sconstruct(var):
    env = dict()
    script_path = sys.argv[:1][0].split('site_scons')[0]
    scons_script = '.\\' + script_path.split(os.getcwd())[-1] + 'site_scons\\SConstruct'
    with open(scons_script, 'r') as sconstruct:
        for a_line in sconstruct.readlines():
            env_key = a_line.split('=')[0].rstrip()
            if env_key in var:
                env_val = a_line.split('=')[1].rstrip()
                if env_key == "env['CURRENT_PATH']":
                    env['CURRENT_PATH'] = os.getcwd()
                else:
                    exec a_line

    return env


def do_clean():
    if os.path.exists('.sconsign.dblite'):
        os.remove('.sconsign.dblite')
        print "os.remove('.sconsign.dblite')"
    if os.path.exists('Build\\input_files.yml'):
        os.remove('Build\\input_files.yml')
        print "os.remove('Build\\input_files.yml')"
    compare_target = ["env['CURRENT_PATH']",
     "env['DEBUG_DIR']",
     "env['DEBUG_FBL_DIR']",
     "env['GEN_OUTPUT_DIR']"]
    env = get_value_from_sconstruct(compare_target)
    for a_key in env.keys():
        if os.path.exists(env[a_key]):
            if a_key is not 'CURRENT_PATH':
                shutil.rmtree(env[a_key], ignore_errors=True)
                print 'Delete ' + env[a_key]


def handle_argument(argument_list):
    option_dict = {'clean': False, 'verbose': False, 'tree': '', 
       'test': '', 'parallel': ('-j' + str(multiprocessing.cpu_count()))}
    return_args = []
    for a_argument in argument_list:
        if '-verbose' == a_argument:
            option_dict['verbose'] = True
        elif a_argument.startswith('-tree'):
            option_dict['tree'] = a_argument
        elif '-c' == a_argument:
            option_dict['clean'] = True
        elif a_argument.lower().startswith('-j'):
            option_dict['parallel'] = a_argument.lower()
        elif a_argument.lower() == 'rebuild':
            do_clean()
            return_args = ['GenerateFBL', 'BuildFBL', 'GenerateAll', 'Build']
        elif ('').join(a_argument.lower().split()).endswith('build'):
            return_args = [
             'GenerateAll', 'Build']
        elif ('').join(a_argument.lower().split()).endswith('buildfbl'):
            return_args = [
             'GenerateFBL', 'BuildFBL']
        elif ('').join(a_argument.lower().split()).endswith('generateall'):
            return_args = [
             'GenerateAll']
        elif ('').join(a_argument.lower().split()).endswith('generatefbl'):
            return_args = [
             'GenerateFBL']
        elif ('').join(a_argument.lower().split()).endswith('release'):
            return_args = [
             'GenerateAll', 'Build', 'Release']
        elif ('').join(a_argument.lower().split()).endswith('releasefbl'):
            return_args = [
             'GenerateFBL', 'BuildFBL', 'ReleaseFBL']
        elif ('').join(a_argument.lower().split()).endswith('debug'):
            return_args = [
             'GenerateAll', 'Build', 'Debug']
        elif ('').join(a_argument.lower().split()).endswith('debugfbl'):
            return_args = [
             'GenerateFBL', 'BuildFBL', 'DebugFBL']
        elif ('').join(a_argument.lower().split()).endswith('releaseall'):
            return_args = [
             12, 13, 23, 14, 15, 21]
        elif ('').join(a_argument.lower().split()).endswith('debugall'):
            return_args = [
             12, 13, 27, 14, 15, 25]
        else:
            return_args += [a_argument]

    return (
     return_args, option_dict)


if __name__ == '__main__':
    arguments, options = handle_argument(sys.argv[1:])
    script_path = sys.argv[:1][0].split('site_scons')[0]
    scons_script = '.\\' + script_path.split(os.getcwd())[-1] + 'site_scons\\SConstruct'
    ret = build(arguments, options)
    sys.exit(ret)
