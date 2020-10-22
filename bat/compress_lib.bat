cd "%~dp0..\"

for /r lib %%p in (*.pdb) do (
	del "%%p"
)

for /r lib %%p in (*.lib) do (
	powershell compress-archive -Force -Path '%%p' -DestinationPath '%%~dpp%%~np'
	del "%%p"
)