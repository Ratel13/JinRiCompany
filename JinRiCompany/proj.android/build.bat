@echo off

IF NOT EXIST "%~dp0..\..\..\..\dept_tools\python.bat" GOTO :EOF

set PATH=%~dp0..\..\..\..\dept_tools;%PATH%
call python build.py "debug" "yes"
