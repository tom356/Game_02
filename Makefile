OBJS = Main.cpp Utils.cpp Utils.h Game.cpp Game.h
OBJ_NAME = Main
SDL_LIB = C:\Programowanie\C++\libs\SDL2-2.0.5\i686-w64-mingw32\lib
SDL_INCLUDE = C:\Programowanie\C++\libs\SDL2-2.0.5\i686-w64-mingw32\include
MINGW = -static-libgcc -static-libstdc++
all : $(OBJS)
	c++ $(OBJS) $(MINGW) -I$(SDL_INCLUDE) -L$(SDL_LIB) -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o $(OBJ_NAME)
