setlocal enabledelayedexpansion

if not exist "obj" (
 	mkdir obj
)

for /f %%f in ('dir /s/b ./assets/bank2/*.c') do ..\bin\lcc -Wa-l -Wf-bo2 -c -o .\obj\%%~nf.o %%f
for /f %%f in ('dir /s/b ./assets/bank3/*.c') do ..\bin\lcc -Wa-l -Wf-bo3 -c -o .\obj\%%~nf.o %%f

..\bin\lcc.exe -Wa-l -c -o .\obj\border.o ./assets/border.c
..\bin\lcc.exe -Wa-l -c -o .\obj\sprites.o ./assets/sprites.c
..\bin\lcc.exe -Wa-l -c -o .\obj\window.o ./assets/window.c

for /f %%f in ('dir /b obj\*.o') do set objectList=!objectList! %%f

cd obj

..\..\bin\lcc.exe -Wl-m -Wl-yt1 -Wl-yo4 -Wl-yp0x143=0x80 -o ..\perautarpg.gbc !objectList!

cd ..

..\bgbw64\bgb64.exe perautarpg.gbc
