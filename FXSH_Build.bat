@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.

if exist debug\*.obj  del debug\*.obj
if exist PERIODIX.G1A  del PERIODIX.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"C:\CASIO\fx9860SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"C:\CASIO\fx9860SDK\Tools\MakeAddinHeader363.exe" "C:\c9860proj\periodix-fx-9860"
if not exist PERIODIX.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

