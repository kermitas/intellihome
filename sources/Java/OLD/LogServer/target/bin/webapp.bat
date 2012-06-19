@REM ----------------------------------------------------------------------------
@REM Copyright 2001-2004 The Apache Software Foundation.
@REM
@REM Licensed under the Apache License, Version 2.0 (the "License");
@REM you may not use this file except in compliance with the License.
@REM You may obtain a copy of the License at
@REM
@REM      http://www.apache.org/licenses/LICENSE-2.0
@REM
@REM Unless required by applicable law or agreed to in writing, software
@REM distributed under the License is distributed on an "AS IS" BASIS,
@REM WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
@REM See the License for the specific language governing permissions and
@REM limitations under the License.
@REM ----------------------------------------------------------------------------
@REM

@echo off

set ERROR_CODE=0

:init
@REM Decide how to startup depending on the version of windows

@REM -- Win98ME
if NOT "%OS%"=="Windows_NT" goto Win9xArg

@REM set local scope for the variables with windows NT shell
if "%OS%"=="Windows_NT" @setlocal

@REM -- 4NT shell
if "%eval[2+2]" == "4" goto 4NTArgs

@REM -- Regular WinNT shell
set CMD_LINE_ARGS=%*
goto WinNTGetScriptDir

@REM The 4NT Shell from jp software
:4NTArgs
set CMD_LINE_ARGS=%$
goto WinNTGetScriptDir

:Win9xArg
@REM Slurp the command line arguments.  This loop allows for an unlimited number
@REM of arguments (up to the command line limit, anyway).
set CMD_LINE_ARGS=
:Win9xApp
if %1a==a goto Win9xGetScriptDir
set CMD_LINE_ARGS=%CMD_LINE_ARGS% %1
shift
goto Win9xApp

:Win9xGetScriptDir
set SAVEDIR=%CD%
%0\
cd %0\..\.. 
set BASEDIR=%CD%
cd %SAVEDIR%
set SAVE_DIR=
goto repoSetup

:WinNTGetScriptDir
set BASEDIR=%~dp0\..

:repoSetup


if "%JAVACMD%"=="" set JAVACMD=java

if "%REPO%"=="" set REPO=%BASEDIR%\repo

set CLASSPATH="%BASEDIR%"\etc;"%REPO%"\org\apache\derby\derby\10.8.2.2\derby-10.8.2.2.jar;"%REPO%"\javax\servlet\servlet-api\3.0-alpha-1\servlet-api-3.0-alpha-1.jar;"%REPO%"\org\eclipse\jetty\jetty-webapp\8.1.3.v20120416\jetty-webapp-8.1.3.v20120416.jar;"%REPO%"\org\eclipse\jetty\jetty-xml\8.1.3.v20120416\jetty-xml-8.1.3.v20120416.jar;"%REPO%"\org\eclipse\jetty\jetty-util\8.1.3.v20120416\jetty-util-8.1.3.v20120416.jar;"%REPO%"\org\eclipse\jetty\jetty-servlet\8.1.3.v20120416\jetty-servlet-8.1.3.v20120416.jar;"%REPO%"\org\eclipse\jetty\jetty-security\8.1.3.v20120416\jetty-security-8.1.3.v20120416.jar;"%REPO%"\org\eclipse\jetty\jetty-server\8.1.3.v20120416\jetty-server-8.1.3.v20120416.jar;"%REPO%"\org\eclipse\jetty\orbit\javax.servlet\3.0.0.v201112011016\javax.servlet-3.0.0.v201112011016.jar;"%REPO%"\org\eclipse\jetty\jetty-continuation\8.1.3.v20120416\jetty-continuation-8.1.3.v20120416.jar;"%REPO%"\org\eclipse\jetty\jetty-http\8.1.3.v20120416\jetty-http-8.1.3.v20120416.jar;"%REPO%"\org\eclipse\jetty\jetty-io\8.1.3.v20120416\jetty-io-8.1.3.v20120416.jar;"%REPO%"\com\sun\jersey\jersey-bundle\1.13-b01\jersey-bundle-1.13-b01.jar;"%REPO%"\com\sun\jersey\jersey-core\1.13-b01\jersey-core-1.13-b01.jar;"%REPO%"\com\sun\jersey\jersey-servlet\1.13-b01\jersey-servlet-1.13-b01.jar;"%REPO%"\com\sun\jersey\jersey-server\1.13-b01\jersey-server-1.13-b01.jar;"%REPO%"\asm\asm\3.1\asm-3.1.jar;"%REPO%"\com\sun\jersey\jersey-json\1.13-b01\jersey-json-1.13-b01.jar;"%REPO%"\org\codehaus\jettison\jettison\1.1\jettison-1.1.jar;"%REPO%"\stax\stax-api\1.0.1\stax-api-1.0.1.jar;"%REPO%"\com\sun\xml\bind\jaxb-impl\2.2.3-1\jaxb-impl-2.2.3-1.jar;"%REPO%"\javax\xml\bind\jaxb-api\2.2.2\jaxb-api-2.2.2.jar;"%REPO%"\javax\xml\stream\stax-api\1.0-2\stax-api-1.0-2.jar;"%REPO%"\javax\activation\activation\1.1\activation-1.1.jar;"%REPO%"\org\codehaus\jackson\jackson-core-asl\1.9.2\jackson-core-asl-1.9.2.jar;"%REPO%"\org\codehaus\jackson\jackson-mapper-asl\1.9.2\jackson-mapper-asl-1.9.2.jar;"%REPO%"\org\codehaus\jackson\jackson-jaxrs\1.9.2\jackson-jaxrs-1.9.2.jar;"%REPO%"\org\codehaus\jackson\jackson-xc\1.9.2\jackson-xc-1.9.2.jar;"%REPO%"\javax\ws\rs\jsr311-api\1.1.1\jsr311-api-1.1.1.jar;"%REPO%"\as\interllihouse\LogServer\0.1\LogServer-0.1.jar
set EXTRA_JVM_ARGUMENTS=
goto endInit

@REM Reaching here means variables are defined and arguments have been captured
:endInit

%JAVACMD% %JAVA_OPTS% %EXTRA_JVM_ARGUMENTS% -classpath %CLASSPATH_PREFIX%;%CLASSPATH% -Dapp.name="webapp" -Dapp.repo="%REPO%" -Dbasedir="%BASEDIR%" as.intellihouse.Main %CMD_LINE_ARGS%
if ERRORLEVEL 1 goto error
goto end

:error
if "%OS%"=="Windows_NT" @endlocal
set ERROR_CODE=1

:end
@REM set local scope for the variables with windows NT shell
if "%OS%"=="Windows_NT" goto endNT

@REM For old DOS remove the set variables from ENV - we assume they were not set
@REM before we started - at least we don't leave any baggage around
set CMD_LINE_ARGS=
goto postExec

:endNT
@endlocal

:postExec

if "%FORCE_EXIT_ON_ERROR%" == "on" (
  if %ERROR_CODE% NEQ 0 exit %ERROR_CODE%
)

exit /B %ERROR_CODE%
