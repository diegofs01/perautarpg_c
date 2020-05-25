setlocal enabledelayedexpansion

if not exist "obj" (
 	mkdir obj
)

for /f %%f in ('dir /s/b *.c') do ..\bin\lcc -Wa-l -c -o .\obj\%%~nf.o %%f

for /f %%f in ('dir /b obj\*.o') do set objectList=!objectList! %%f

cd obj

..\..\bin\lcc.exe -Wl-m -Wl-yp0x143=0x80 -o ..\perautarpg.gbc !objectList!

cd ..

..\bgbw64\bgb64.exe perautarpg.gbc
