all:
	g++ .\src\\*.cpp -O3 -Wall -m64 -I include -I C:\SDL2-w64\include\SDL2 -I C:\SDL2_image-w64\include\SDL2 -I C:\SDL2_TTF-w64\include\SDL2 -I C:\SDL2_Mixer-w64\include\SDL2 -s -L C:\SDL2-w64\lib -L C:\SDL2_image-w64\lib -L C:\SDL2_TTF-w64\lib -L C:\SDL2_Mixer-w64\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o .\bin\main.exe
	.\bin\main.exe