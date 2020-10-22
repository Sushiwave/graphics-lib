cd "%~dp0..\"

rmdir /s/q "%GRAPHICS_LIB%"
mkdir "%GRAPHICS_LIB%"
mkdir "%GRAPHICS_LIB%\inc"
mkdir "%GRAPHICS_LIB%\lib"

for /r lib %%p in (*.pdb) do (
	del "%%p"
)

xcopy /s/e/y "inc" "%GRAPHICS_LIB%\inc"
xcopy /s/e/y "lib" "%GRAPHICS_LIB%\lib"
