@ECHO OFF
SetLocal EnableDelayedExpansion

SET sourceFiles=
FOR /R %%f IN (*.cpp) DO SET sourceFiles=!sourceFiles! %%f

SET cppStandard=c++20
SET compiler=clang++
SET compilerFlags=-g -std=%cppStandard%
SET linkerFlags=-L..\bin\ -lSiofraEngine.lib
SET includes=-I.\include -I..\engine\include
SET output=-o ..\bin\Testbed.exe
SET defines=-D_DEBUG -DSE_IMPORT

%compiler% %sourceFiles% %output% %includes% %compilerFlags% %linkerFlags% %defines%