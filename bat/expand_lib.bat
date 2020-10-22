cd "%~dp0..\"

for /r lib %%p in (*.zip) do (
	powershell expand-archive -Force -Path '%%p' -DestinationPath '%%~dpp'
	del "%%p"
)
