@echo off

pushd %0\..\..
setlocal
set PYTHON_HOME=C:\ts_mirr\python\Portable_Python_2.7.6.1\App
set SCONS_HOME=C:\ts_mirr\scons\scons-local-2.3.4
set PATH=%PATH%;%PYTHON_HOME%;%SCONS_HOME%
set gentoolfw_version=1.1.5
%PYTHON_HOME%\python Build\site_scons\build.pyc %*
endlocal
popd
exit /B %ERRORLEVEL%
::pause