@echo off

echo./*
echo.* Check VC++ environment...
echo.*/
echo.

if defined VS80COMNTOOLS (
    set VSVARS="%VS80COMNTOOLS%vsvars32.bat"
    set VC_VER=80
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
    echo Can't find VC2005, VC2010 or VC2012 installed!
    goto ERROR
)

echo %VSVARS%
echo %VC_VER%
set name=%~n0
call %VSVARS%
vcbuild /MP /M10 "%name%.sln" $ALL
pause