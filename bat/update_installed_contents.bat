@echo off



cd "%~dp0..\"



echo Building... ( This take a few minutes )



"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath>msbuild_root_path.txt
(set /p MSBUILD_ROOT_PATH=)<msbuild_root_path.txt
del msbuild_root_path.txt
set MSBUILD_PATH= "%MSBUILD_ROOT_PATH%\MSBuild\Current\Bin\MSBuild.exe"

powershell "get-wmiobject win32_process -filter processid=$pid | foreach-object {$_.parentprocessid;}">self_process_id.txt
(set /p SELF_PROCESS_ID=)<self_process_id.txt
del self_process_id.txt



start /min "Building: Debug x86"   %MSBUILD_PATH% GraphicsLib.sln /m /t:build /p:BuildInParallel=true;Configuration=Debug;Platform="x86"
start /min "Building: Release x84" %MSBUILD_PATH% GraphicsLib.sln /m /t:build /p:BuildInParallel=true;Configuration=Release;Platform="x86"
start /min "Building: Debug x64"   %MSBUILD_PATH% GraphicsLib.sln /m /t:build /p:BuildInParallel=true;Configuration=Debug;Platform="x64"
start /min "Building: Release x64" %MSBUILD_PATH% GraphicsLib.sln /m /t:build /p:BuildInParallel=true;Configuration=Release;Platform="x64"



call :monitoring



rmdir /s/q "%GRAPHICS_LIB%"
mkdir "%GRAPHICS_LIB%"
mkdir "%GRAPHICS_LIB%\inc"
mkdir "%GRAPHICS_LIB%\lib"



echo Copying...



xcopy /s/e/y "inc" "%GRAPHICS_LIB%\inc" > nul
xcopy /s/e/y "lib" "%GRAPHICS_LIB%\lib" > nul



for /r "%GRAPHICS_LIB%\lib" %%p in (*.pdb) do (
	del "%%p"
)



exit /b










:monitoring
timeout /t 1 > nul
wmic process get name,parentprocessid | findstr "%SELF_PROCESS_ID%" | findstr "MSBuild.exe">childs.txt
for %%F in (childs.txt) do (
	if %%~zF==0 (
	    break
	) else (
		goto monitoring
	)
)
del childs.txt
exit /b
