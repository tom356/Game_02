#include <String>
#include <Memory>
#include <vector>
#include <SDL2/SDL.h>
#include "Game.h"
#include "Utils.h"

const int WIDTH = 640, HEIGHT = 480;
bool GameOn = true;

namespace SDLWrapper
{
	struct SDLDeleter
	{
	  void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
	  void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); p = NULL; }
	  
	};
	std::unique_ptr<SDL_Window, SDLDeleter>
	createWindow(char const *title, int x, int y, int w, int h, Uint32 flags)
	{
		return std::unique_ptr<SDL_Window, SDLDeleter>(
				 SDL_CreateWindow(title, x, y, w, h, flags), 
				 SDLDeleter());
	}
	std::unique_ptr<SDL_Surface, SDLDeleter>
	createImage(char const *filename)
	{
		return std::unique_ptr<SDL_Surface, SDLDeleter>(
				 SDL_LoadBMP(filename), 
				 SDLDeleter());
	}
	std::unique_ptr<SDL_Surface, SDLDeleter>
	createWindowSurface(SDL_Window *window)
	{
		auto p = std::unique_ptr<SDL_Surface, SDLDeleter>(
				 SDL_GetWindowSurface(window), 
				 SDLDeleter());
		return p;
	}
}

void game()
{	
//Deklaracja/inicjalizacja SDL
	auto window = SDLWrapper::createWindow("Game_01", 
									SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 
									SDL_WINDOW_ALLOW_HIGHDPI);	
	auto bg             = SDLWrapper::createImage("Bg.bmp");
	auto enemy 			= SDLWrapper::createImage("Enemy.bmp");
	auto window_surface = SDLWrapper::createWindowSurface(window.get());
	SDL_Event windowEvent;
	SDL_Rect enemy_rect;
	
	enemy_rect.x = 0;
	enemy_rect.y = 0;	
	enemy_rect.w = 37;
	enemy_rect.h = 74;
	

	Utils::Keyboard keyboard;
	Utils::Mouse mouse;
	Utils::Timer gameTimer(17); // ~60fps
	Game::Creature creature(10,10,10);
	Utils::MathVector target;	
	
// 	Główna pętla
	gameTimer.reset();	
	while( GameOn )
	{	
		//odczyt eventów
		if(SDL_PollEvent( &windowEvent ))
		{
			switch(windowEvent.type)
			{
				case SDL_QUIT: 
					GameOn = false; 	
				break;
				case SDL_MOUSEBUTTONDOWN :
					if(windowEvent.button.state == SDL_PRESSED)
					{
						mouse.x = windowEvent.button.x;
						mouse.y = windowEvent.button.y;
					}
				break;
				case SDL_KEYDOWN :
					switch(windowEvent.key.keysym.sym)
					{
						case SDLK_w: keyboard.w = true; break;
						case SDLK_s: keyboard.s = true; break;
						case SDLK_a: keyboard.a = true; break;
						case SDLK_d: keyboard.d = true; break;
					}
				break;
				case SDL_KEYUP :
					switch(windowEvent.key.keysym.sym)
					{
						case SDLK_w: keyboard.w = false; break;
						case SDLK_s: keyboard.s = false; break;
						case SDLK_a: keyboard.a = false; break;
						case SDLK_d: keyboard.d = false; break;
					}
				break;
				
			}	
		}
		// logika gry
		if(gameTimer.isTime())
		{
			target.x = mouse.x;
			target.y = mouse.y;
			
			creature.gotoTarget(target);
			
			enemy_rect.x = creature.pos.x;
			enemy_rect.y = creature.pos.y;
		}
		
		// rysowanie obrazu
		SDL_BlitSurface(bg.get(), NULL, window_surface.get(), NULL);
		SDL_BlitSurface(enemy.get(), NULL, window_surface.get(), &enemy_rect);
		// wyświetlanie obrazu
		SDL_UpdateWindowSurface( window.get() );
	}		
}
int main(int argc, char *argv[])
{	
	if(SDL_Init( SDL_INIT_EVERYTHING ) < 0){}
		
	game();

	SDL_Quit();
	
	return EXIT_SUCCESS;
}