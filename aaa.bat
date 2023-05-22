FOR /l %%A in (0,1,10) DO (
	.\build\bin\Release\Dawnbreaker.exe
	echo %%A
)
pause