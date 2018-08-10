#include "Texture.h"

Texture::Texture()
{
  _texture = NULL;
  _renderer = NULL;
  _font = NULL;
  _width = 0;
  _height = 0;
}

Texture::~Texture()
{
  free();
}

void Texture::setRenderer(SDL_Renderer* renderer)
{
  _renderer = renderer;
}

void Texture::setFont(TTF_Font* font)
{
  _font = font;
}

void Texture::loadFromFile(std::string path)
{
  free();
  SDL_Surface* surface = IMG_Load(path.c_str());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);

  _width = surface->w;
  _height = surface->h;
  SDL_FreeSurface(surface);

  _texture = texture;
}

void Texture::loadFromText(std::string text, SDL_Color textColor)
{
  free();
  SDL_Surface* surface = TTF_RenderText_Solid(_font, text.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
  _width = surface->w;
  _height = surface->h;
  SDL_FreeSurface(surface);

  _texture = texture;
}

void Texture::free()
{
  // Free texture if it exists
  if(_texture != NULL)
  {
    SDL_DestroyTexture(_texture);
    _texture = NULL;
    _width = 0;
    _height = 0;
  }
}

void Texture::render(int x, int y)
{
  SDL_Rect renderDimensions = { x, y, _width, _height };
  SDL_RenderCopy(_renderer, _texture, NULL, &renderDimensions);
}

int Texture::getWidth()
{
  return _width;
}

int Texture::getHeight()
{
  return _height;
}