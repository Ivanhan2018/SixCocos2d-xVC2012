@echo off

set curPath=%cd%

set srcDebugExePath=%curPath%\Debug.win32
set decDebugExePath=%curPath%\bin\client_debug
set srcReleaseExePath=%curPath%\Release.win32
set decReleaseExePath=%curPath%\bin\client_Release
set ResourcePath=%curPath%\samples\HelloCpp\Resources

echo Դִ���ļ���DLLĿ¼��%srcDebugExePath%
echo Ŀ��ִ���ļ���DLLĿ¼��%decDebugExePath%
echo ��ԴĿ¼��%ResourcePath%

echo �밴���������ʼ����������
pause

rd %decDebugExePath% /q /s
mkdir %decDebugExePath%

title ���������ļ�
color 70

copy %srcDebugExePath%\*.exe			%decDebugExePath%\*.exe
copy %srcDebugExePath%\*.dll				%decDebugExePath%\*.dll
xcopy %ResourcePath%					%decDebugExePath%\  /s /e /h

pause