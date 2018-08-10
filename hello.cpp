#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
//#include <SDL2_ttf/SDL_ttf.h>

#include "Texture.h"

#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int personXPosition = 240;
int personYPosition = 190;

enum keyPressSurfaces
{
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

// These are function declarations!
void initializeSDL();
void loadMedia();
SDL_Texture* loadTexture(std::string path);
void close();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
SDL_Texture* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

Texture personTexture;
Texture backgroundTexture;

void initializeSDL()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");  // Texture hinting?
  window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  // Create renderer for window
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // Initialize with a solid color?

  // Be able to load PNG files 
  IMG_Init(IMG_INIT_PNG);
}

void loadMedia()
{
  personTexture.setRenderer(renderer);
  personTexture.loadFromFile("images/person.png");
  backgroundTexture.setRenderer(renderer);
  backgroundTexture.loadFromFile("images/background.png");
}

void close()
{
  personTexture.free();
  backgroundTexture.free();

  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;

  IMG_Quit();
  SDL_Quit();
}

// Don't change main function arguments for compatibility reasons
int main(int argc, char* args[])  
{
  initializeSDL();
  loadMedia();

  // Loop
  bool quit = false;
  SDL_Event e;
  while(!quit)
  {
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        quit = true;
      }
    }

    // Key state!
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates[SDL_SCANCODE_RIGHT])  { personXPosition++; }
    if(currentKeyStates[SDL_SCANCODE_LEFT])   { personXPosition--; }
    if(currentKeyStates[SDL_SCANCODE_UP])     { personYPosition--; }
    if(currentKeyStates[SDL_SCANCODE_DOWN])   { personYPosition++; }

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Render images!
    backgroundTexture.render(0,0);
    personTexture.render(personXPosition, personYPosition);

    // Update screen
    SDL_RenderPresent(renderer);
  }

  close();
  printf("Bye!\n");
  return 0;
}