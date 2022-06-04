@ECHO OFF

PUSHD engine
CALL build.bat
POPD

PUSHD testbed
CALL build.bat
POPD