setlocal
set BUILD_TYPE=Release
set ACTION=
if "%1" == "/debug" set BUILD_TYPE=Debug
if "%2" == "/debug" set BUILD_TYPE=Debug
if "%1" == "/clean" set ACTION=/clean
if "%2" == "/clean" set ACTION=/clean

setlocal
call setup-msvc6
echo on
msdev example_py22.dsw /make "example - Win32 %BUILD_TYPE%" %ACTION%
msdev example_py23.dsw /make "example - Win32 %BUILD_TYPE%" %ACTION%
msdev example_py23.dsw /make "pycxx_iter - Win32 %BUILD_TYPE%" %ACTION%
endlocal

setlocal
if "%ACTION%" == "" set ACTION=/build
call setup-msvc71
echo on
devenv example_py24.sln %ACTION% "%BUILD_TYPE%"  /project "example"
devenv example_py24.sln %ACTION% "%BUILD_TYPE%"  /project "pycxx_iter"
devenv example_py24.sln %ACTION% "%BUILD_TYPE%"  /project "simple"
devenv example_py25.sln %ACTION% "%BUILD_TYPE%"  /project "example"
devenv example_py25.sln %ACTION% "%BUILD_TYPE%"  /project "pycxx_iter"
devenv example_py25.sln %ACTION% "%BUILD_TYPE%"  /project "simple"
devenv example_py26.sln %ACTION% "%BUILD_TYPE%"  /project "example"
devenv example_py26.sln %ACTION% "%BUILD_TYPE%"  /project "pycxx_iter"
devenv example_py26.sln %ACTION% "%BUILD_TYPE%"  /project "simple"
endlocal

endlocal
