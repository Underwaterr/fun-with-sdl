#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "Texture.h"

#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int personXPosition = 240;
int personYPosition = 190;

// These are function declarations!
void initializeSDL();
void loadMedia();
SDL_Texture* loadTexture(std::string path);
void close();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
SDL_Texture* texture = NULL;

Texture personTexture;
Texture backgroundTexture;
Texture textTexture;

void initializeSDL()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");  // Texture hinting?
  window = SDL_CreateWindow("Fun Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  // Create renderer for window
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // Initialize with a solid color?

  // Be able to load PNG files 
  IMG_Init(IMG_INIT_PNG);

  // Use dem fontzz
  TTF_Init();
}

void loadMedia()
{
  personTexture.setRenderer(renderer);
  personTexture.loadFromFile("images/person.png");
  backgroundTexture.setRenderer(renderer);
  backgroundTexture.loadFromFile("images/background.png");

  font = TTF_OpenFont("fonts/fira-mono.ttf", 32);
  textTexture.setRenderer(renderer);
  textTexture.setFont(font);
  SDL_Color textColor = { 0, 0, 0, 0 };
  textTexture.loadFromRenderedText("Have a great day!", textColor);
}

void close()
{
  personTexture.free();
  backgroundTexture.free();
  textTexture.free();

  TTF_CloseFont(font);
  font = NULL;

  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;

  TTF_Quit();
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
    if(currentKeyStates[SDL_SCANCODE_RIGHT] && personXPosition < (SCREEN_WIDTH - personTexture.getWidth())) 
    {
      personXPosition++; 
    }

    if(currentKeyStates[SDL_SCANCODE_LEFT] && personXPosition > 0) 
    {
      personXPosition--; 
    }

    if(currentKeyStates[SDL_SCANCODE_UP] && personYPosition > 0) 
    {
      personYPosition--; 
    }

    if(currentKeyStates[SDL_SCANCODE_DOWN] && personYPosition < (SCREEN_HEIGHT - personTexture.getHeight())) 
    {
      personYPosition++; 
    }

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Render!
    backgroundTexture.render(0,0);
    personTexture.render(personXPosition, personYPosition);
    textTexture.render((SCREEN_WIDTH-textTexture.getWidth())/2, SCREEN_HEIGHT-textTexture.getHeight()); 

    // Update screen
    SDL_RenderPresent(renderer);
  }

  close();
  printf("Bye!\n");
  return 0;
}