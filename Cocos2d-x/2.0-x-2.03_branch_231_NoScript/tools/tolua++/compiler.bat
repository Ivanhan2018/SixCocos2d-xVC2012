@echo off 
echo ----------------------------------------------------
echo Project:PKG Auto Compiler
echo Author:Cool.Cat@2013/3/26 16:28:35
echo ----------------------------------------------------
tolua++.exe -v
echo ----------------------------------------------------
set curdir=%~dp0
cd /d %curdir%
echo ���ڽ��� %1 ...
tolua++.exe -n %~n1 -P %1
echo ���ڱ��� %1 ...
tolua++.exe -n %~n1 -o L_%~n1.h %1 && move L_%~n1.h ..\..\Utility\Lua_Interface
echo ������ɣ�
@pause