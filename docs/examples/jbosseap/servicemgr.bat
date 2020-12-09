@echo off
rem
rem ---------------------------------------------------------------
rem JBoss EAP Service Management Tool
rem
rem Usage: servicemgr.bat create/delete/rotate/dump [service_name]
rem
rem ---------------------------------------------------------------
rem
setlocal
rem
if "x%~2" == "x" goto Einval
set "SERVICE_NAME=%~2"

if "x%~3" == "x" (
  set "JBOSSEAP_SERVER_MODE=standalone"
) else (
  set "JBOSSEAP_SERVER_MODE=%~3"
)
rem
if /i "x%~1" == "xcreate" goto doCreate
if /i "x%~1" == "xdelete" goto doDelete
if /i "x%~1" == "xrotate" goto doRotate
if /i "x%~1" == "xdump"   goto doDumpStacks
rem Unknown option
echo %~nx0: Unknown option '%~1'
goto Einval

rem
rem Create service
:doCreate
set "SERVICE_BASE=%cd%"
pushd ..
rem Location for Logs\SvcBatch.log[.n] files
set "SERVICE_HOME=%cd%\%JBOSSEAP_SERVER_MODE%"
popd
rem
rem Change to actual JBoss EAP version
set "JBOSSEAP_DISPLAY=JBoss EAP 7.4"
rem
sc create "%SERVICE_NAME%" binPath= ""%SERVICE_BASE%\svcbatch.exe" -o "%SERVICE_HOME%\log" -b -s -c winservice.bat"
sc config "%SERVICE_NAME%" DisplayName= "%JBOSSEAP_DISPLAY% %SERVICE_NAME% Service"

rem Ensure the networking services are running
rem and that service is started on system startup
sc config "%SERVICE_NAME%" depend= Tcpip/Afd start= auto

rem Set required privileges so we can kill process tree
rem even if Jvm created multiple child processes.
sc privs "%SERVICE_NAME%" SeCreateSymbolicLinkPrivilege/SeDebugPrivilege
rem Description is from JBoss EAP distribution version.txt file
sc description "%SERVICE_NAME%" "JBoss EAP continuous delivery - Version 7.4.0.CD21"
goto End

rem
rem Delete service
:doDelete
rem
sc stop "%SERVICE_NAME%" >NUL
sc delete "%SERVICE_NAME%"
goto End

rem
rem Rotate SvcBatch logs
:doRotate
rem
sc control "%SERVICE_NAME%" 234
goto End

rem
rem Send CTRL_BREAK_EVENT
rem Jvm will dump full thread stack to log file
:doDumpStacks
rem
sc control "%SERVICE_NAME%" 233
goto End

:Einval
echo Usage: %~nx0 create/delete/rotate/dump [service_name]
echo.
exit /b 1

:End
