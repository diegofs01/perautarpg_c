if not exist "obj" (
	mkdir obj
)

..\bin\lcc.exe -Wa-l -c -o .\obj\exterior_01.o .\assets\tilesets\exterior_01.c
..\bin\lcc.exe -Wa-l -c -o .\obj\interior_01.o .\assets\tilesets\interior_01.c 
..\bin\lcc.exe -Wa-l -c -o .\obj\town_01.o .\assets\maps\town_01.c
..\bin\lcc.exe -Wa-l -c -o .\obj\house_01.o .\assets\maps\house_01.c
..\bin\lcc.exe -Wa-l -c -o .\obj\border.o border.c
..\bin\lcc.exe -Wa-l -c -o .\obj\window.o window.c
..\bin\lcc.exe -Wa-l -c -o .\obj\perautarpg.o perautarpg.c

cd obj

..\..\bin\lcc.exe -Wl-m -Wl-yp0x143=0x80 -o ..\perautarpg.gbc perautarpg.o border.o window.o exterior_01.o interior_01.o town_01.o house_01.o

cd ..

..\bgbw64\bgb64.exe perautarpg.gbc