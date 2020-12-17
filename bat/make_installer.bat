@echo off



echo Start creating installer



cd %~dp0..\



if EXIST installer (
	rd /s/q installer
)
mkdir installer\inc
mkdir installer\lib
mkdir installer\template



if EXIST lib (
	rd /s/q lib
)



echo @echo off> installer\install.bat
echo echo Installing...>> installer\install.bat
echo set graphics_lib_=%%USERPROFILE%%\Documents\GraphicsLib>> installer\install.bat
echo if "%%1" == "del_temp" ^(>> installer\install.bat
echo 	del /A:H "%%~dp0temp.bat">> installer\install.bat
echo ^) else ^(>> installer\install.bat
echo     echo @echo off^> temp.bat>> installer\install.bat
echo 	attrib +h temp.bat>> installer\install.bat
echo 	echo setx GRAPHICS_LIB "%%graphics_lib_%%"^>^> temp.bat>> installer\install.bat
echo 	echo call "%%%%%%%%~dp0install.bat" del_temp^>^> temp.bat>> installer\install.bat
echo 	powershell start-process temp.bat -verb runas>> installer\install.bat
echo 	mkdir "%%graphics_lib_%%\inc">> installer\install.bat
echo 	mkdir "%%graphics_lib_%%\lib">> installer\install.bat
echo 	cd "%%~dp0"^>^> temp.bat>> installer\install.bat
echo 	copy "template\GraphicsLib.zip" "%%USERPROFILE%%\Documents\Visual Studio 2019\Templates\ProjectTemplates"^> nul>> installer\install.bat
echo 	xcopy /s/e/y "inc" "%%graphics_lib_%%\inc"^> nul>> installer\install.bat
echo 	xcopy /s/e/y "lib" "%%graphics_lib_%%\lib"^> nul>> installer\install.bat
echo ^)>> installer\install.bat

echo @echo off> installer\uninstall.bat
echo echo Uninstalling...>> installer\uninstall.bat
echo if "%%1" == "del_temp" ^(>> installer\uninstall.bat
echo 	del /A:H "%%~dp0temp.bat">> installer\uninstall.bat
echo ^) else ^(>> installer\uninstall.bat
echo 	rmdir /s/q "%%GRAPHICS_LIB%%">> installer\uninstall.bat
echo 	del "%%USERPROFILE%%\Documents\Visual Studio 2019\Templates\ProjectTemplates\GraphicsLib.zip">> installer\uninstall.bat
echo     echo @echo off^> temp.bat>> installer\uninstall.bat
echo 	echo REG delete HKCU\Environment /F /V GRAPHICS_LIB^>^> temp.bat>> installer\uninstall.bat
echo 	attrib +h temp.bat>> installer\uninstall.bat
echo 	echo call "%%%%%%%%~dp0uninstall.bat" del_temp^>^> temp.bat>> installer\uninstall.bat
echo 	powershell start-process temp.bat -verb runas>> installer\uninstall.bat
echo ^)>> installer\uninstall.bat



echo Building... ( This take a few minutes )



"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath>msbuild_root_path.txt
(set /p MSBUILD_ROOT_PATH=) < msbuild_root_path.txt
del msbuild_root_path.txt
set MSBUILD_PATH= "%MSBUILD_ROOT_PATH%\MSBuild\Current\Bin\MSBuild.exe"

powershell "get-wmiobject win32_process -filter processid=$pid | foreach-object {$_.parentprocessid;}" > self_process_id.txt
(set /p SELF_PROCESS_ID=) < self_process_id.txt
del self_process_id.txt



start /min "Building DirectXTex:  Debug x86"   %MSBUILD_PATH% ThirdParty\DirectXTex\DirectXTex_Desktop_2019_Win10.vcxproj /t:clean;rebuild /m /p:BuildInParallel=true;Configuration=Debug;Platform="x86"
start /min "Building DirectXTex:  Release x84" %MSBUILD_PATH% ThirdParty\DirectXTex\DirectXTex_Desktop_2019_Win10.vcxproj /t:clean;rebuild /m /p:BuildInParallel=true;Configuration=Release;Platform="x86"
start /min "Building DirectXTex:  Debug x64"   %MSBUILD_PATH% ThirdParty\DirectXTex\DirectXTex_Desktop_2019_Win10.vcxproj /t:clean;rebuild /m /p:BuildInParallel=true;Configuration=Debug;Platform="x64"
start /min "Building DirectXTex:  Release x64" %MSBUILD_PATH% ThirdParty\DirectXTex\DirectXTex_Desktop_2019_Win10.vcxproj /t:clean;rebuild /m /p:BuildInParallel=true;Configuration=Release;Platform="x64"
start /min "Building GraphicsLib: Debug x86"   %MSBUILD_PATH% GraphicsLib.sln /t:clean;rebuild /m /p:BuildInParallel=true;Configuration=Debug;Platform="x86"
start /min "Building GraphicsLib: Release x84" %MSBUILD_PATH% GraphicsLib.sln /t:clean;rebuild /m /p:BuildInParallel=true;Configuration=Release;Platform="x86"
start /min "Building GraphicsLib: Debug x64"   %MSBUILD_PATH% GraphicsLib.sln /t:clean;rebuild /m /p:BuildInParallel=true;Configuration=Debug;Platform="x64"
start /min "Building GraphicsLib: Release x64" %MSBUILD_PATH% GraphicsLib.sln /t:clean;rebuild /m /p:BuildInParallel=true;Configuration=Release;Platform="x64"

call :monitoring



echo Copying...



xcopy /s/e/y "inc" "installer\inc" > nul
xcopy /s/e/y "lib" "installer\lib" > nul
xcopy /s/e/y "template" "installer\template" > nul



for /r installer\lib %%p in (*.pdb) do (
	del "%%p"
)



exit /b










:monitoring
timeout /t 1 > nul
wmic process get name,parentprocessid | findstr "%SELF_PROCESS_ID%" | findstr "MSBuild.exe" > childs.txt
for %%F in (childs.txt) do (
	if %%~zF==0 (
	    break
	) else (
		goto monitoring
	)
)
del childs.txt
exit /b
