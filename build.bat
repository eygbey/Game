@echo off

cls

set CommonCompilerFlags= -MT -EHsc -nologo -Gm- -GR- -EHa- -Od -Oi -W4 -wd4201 -wd4100 -wd4189 -FC -Z7 -FeGame.exe
set CommonLinkerFlags= -opt:ref user32.lib gdi32.lib winmm.lib opengl32.lib

IF NOT EXIST build mkdir build
pushd build
cl "../code/main.cpp" /I "../../common" /I "C:\\Users\\Tanner Trotter\\Desktop\\Library" -Zi /link "C:\Users\Tanner Trotter\Desktop\Library\opengl\lib\glew32.lib" %CommonLinkerFlags%
popd