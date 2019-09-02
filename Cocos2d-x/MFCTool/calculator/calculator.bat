@echo off

echo./*
echo.* Check VC++ environment...
echo.*/
echo.

if defined VS110COMNTOOLS (
    set VSVARS="%VS110COMNTOOLS%vsvars32.bat"
    set VC_VER=110
) else if defined VS100COMNTOOLS (
    set VSVARS="%VS100COMNTOOLS%vsvars32.bat"
    set VC_VER=100
) else if defined VS90COMNTOOLS (
    set VSVARS="%VS90COMNTOOLS%vsvars32.bat"
    set VC_VER=90
) else if defined VS120COMNTOOLS (
    set VSVARS="%VS120COMNTOOLS%vsvars32.bat"
    set VC_VER=120
) else if defined VS140COMNTOOLS (
    set VSVARS="%VS140COMNTOOLS%vsvars32.bat"
    set VC_VER=140
) 

if not defined VSVARS (
    echo Can't find VC2008, VC2010 or VC2012 installed!
    goto ERROR
)

echo %VSVARS%
echo %VC_VER%
set name=%~n0
call %VSVARS%
msbuild "%name%.sln" /t:Clean
msbuild "%name%.sln" /p:Configuration="Debug" /m
msbuild "%name%.sln" /p:Configuration="Release" /m

pause