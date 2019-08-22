set name=%~n0
Set VC2013ROOT=D:\Program Files\Program Files (x86)\Microsoft Visual Studio 12.0
Set VCROOT=C:\Program Files (x86)\Microsoft Visual Studio 11.0
Set VC2005ROOT=C:\Program Files (x86)\Microsoft Visual Studio 8
Set PATH=%VCROOT%\VC\bin;%VCROOT%\Common7\IDE;%PATH%
Set INCLUDE=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include;%VCROOT%\VC\PlatformSDK\include;%VCROOT%\VC\atlmfc\include;%VCROOT%\VC\include;%INCLUDE%
Set LIB=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib;%VCROOT%\VC\lib;%LIB%
cl  /nologo /O1 /TP /c /GX /GR /GA /GB /w /FAcs /IInclude "%name%.cpp"
link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib shlwapi.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  /nologo /section:.bss,SRW /DLL /SUBSYSTEM:WINDOWS /LIBPATH:Lib /OUT:"%name%.dll" "%name%.obj"
pause