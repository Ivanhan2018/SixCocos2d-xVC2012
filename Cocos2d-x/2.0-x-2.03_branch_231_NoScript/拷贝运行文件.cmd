@echo off

set curPath=%cd%

set srcDebugExePath=%curPath%\Debug.win32
set decDebugExePath=%curPath%\bin\client_debug
set srcReleaseExePath=%curPath%\Release.win32
set decReleaseExePath=%curPath%\bin\client_Release
set ResourcePath=%curPath%\samples\HelloCpp\Resources

echo 源执行文件与DLL目录：%srcDebugExePath%
echo 目标执行文件与DLL目录：%decDebugExePath%
echo 资源目录：%ResourcePath%

echo 请按任意键，开始拷贝！！！
pause

rd %decDebugExePath% /q /s
mkdir %decDebugExePath%

title 拷贝运行文件
color 70

copy %srcDebugExePath%\*.exe			%decDebugExePath%\*.exe
copy %srcDebugExePath%\*.dll				%decDebugExePath%\*.dll
xcopy %ResourcePath%					%decDebugExePath%\  /s /e /h

pause