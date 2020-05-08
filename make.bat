..\bin\lcc.exe -Wa-l -c -o tileset1.o tileset1.c
..\bin\lcc.exe -Wa-l -c -o map1.o map1.c
..\bin\lcc.exe -Wa-l -c -o border.o border.c
..\bin\lcc.exe -Wa-l -c -o window.o window.c
..\bin\lcc.exe -Wa-l -c -o perautarpg.o perautarpg.c
..\bin\lcc.exe -Wl-m -o perautarpg.gbc perautarpg.o map1.o tileset1.o border.o window.o
..\bgbw64\bgb64.exe perautarpg.gbc