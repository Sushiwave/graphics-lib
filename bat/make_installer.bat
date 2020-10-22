cd %~dp0..\

mkdir installer\inc
mkdir installer\lib

echo set graphics_lib_=%%USERPROFILE%%\Documents\GraphicsLib> installer\install.bat
echo if "%%1" == "del_temp" ^(>> installer\install.bat
echo 	del /A:H "%%~dp0temp.bat">> installer\install.bat
echo ^) else ^(>> installer\install.bat
echo 	echo setx GRAPHICS_LIB "%%graphics_lib_%%"^> temp.bat>> installer\install.bat
echo 	attrib +h temp.bat>> installer\install.bat
echo 	echo call "%%%%%%%%~dp0install.bat" del_temp^>^> temp.bat>> installer\install.bat
echo 	powershell start-process temp.bat -verb runas>> installer\install.bat
echo 	mkdir "%%graphics_lib_%%\inc">> installer\install.bat
echo 	mkdir "%%graphics_lib_%%\lib">> installer\install.bat
echo 	cd "%%~dp0"^>^> temp.bat>> installer\install.bat
echo 	xcopy /s/e/y "inc" "%%graphics_lib_%%\inc">> installer\install.bat
echo 	xcopy /s/e/y "lib" "%%graphics_lib_%%\lib">> installer\install.bat
echo 	for /r "%%graphics_lib_%%\lib" %%%%p in ^(*.zip^) do ^(>> installer\install.bat
echo 	 	powershell expand-archive -Force -Path '%%%%p' -DestinationPath '%%%%~dpp'>> installer\install.bat
echo 	 	del "%%%%p">> installer\install.bat
echo 	 ^)>> installer\install.bat
echo ^)>> installer\install.bat

echo if "%%1" == "del_temp" ^(> installer\uninstall.bat
echo 	del /A:H "%%~dp0temp.bat">> installer\uninstall.bat
echo ^) else ^(>> installer\uninstall.bat
echo 	rmdir /s/q "%%GRAPHICS_LIB%%">> installer\uninstall.bat
echo 	del "%%USERPROFILE%%\Documents\Visual Studio 2019\Templates\ProjectTemplates\GraphicsLib.zip">> installer\uninstall.bat
echo 	echo REG delete HKCU\Environment /F /V GRAPHICS_LIB^> temp.bat>> installer\uninstall.bat
echo 	attrib +h temp.bat>> installer\uninstall.bat
echo 	echo call "%%%%%%%%~dp0uninstall.bat" del_temp^>^> temp.bat>> installer\uninstall.bat
echo 	powershell start-process temp.bat -verb runas>> installer\uninstall.bat
echo ^)>> installer\uninstall.bat

xcopy /s/e/y "inc" "installer\inc"
xcopy /s/e/y "lib" "installer\lib"

for /r installer\lib %%p in (*.lib) do (
	powershell compress-archive -Force -Path '%%p' -DestinationPath '%%~dpp%%~np'
	del "%%p"
)
