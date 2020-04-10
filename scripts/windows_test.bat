pushd ..\bin\
..\.build\bin\Debug\test.range-d.exe
if errorlevel 1 exit 1
..\.build\bin\Debug\test.refptr-d.exe
if errorlevel 1 exit 1
popd
