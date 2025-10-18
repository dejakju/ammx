rem winDOOF build script
@echo off

rem CUMpilation
pushd libs\
gcc -c toolbox.c -o toolbox.obj
ar rcs toolbox.lib toolbox.obj
popd
gcc ammx.c -Llibs -ltoolbox -o ammx

rem cleanAPP
del libs\toolbox.lib
del libs\toolbox.obj

