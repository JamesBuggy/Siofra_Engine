@ECHO OFF
SetLocal EnableDelayedExpansion

SET sourceFiles=
FOR /R %%f IN (*.cpp) DO SET sourceFiles=!sourceFiles! %%f

SET cppStandard=c++17
SET compiler=clang++
SET compilerFlags=-shared -g -std=%cppStandard%
SET linkerFlags=-luser32 -l./libs/SDL2-2.0.20/lib/x64/SDL2.lib
SET includes=-I./include -I./source -I./libs/SDL2-2.0.20/include
SET output=-o ../bin/SiofraEngine.dll
SET defines=-DDEBUG -DSE_EXPORT -DSE_PLATFORM_WINDOWS

%compiler% %sourceFiles% %output% %includes% %compilerFlags% %linkerFlags% %defines%