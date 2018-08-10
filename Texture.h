#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class Texture
{
  private:
    SDL_Texture* _texture;
    SDL_Renderer* _renderer;
    int _width;
    int _height;
    
  public:
    Texture();
    ~Texture();
    void setRenderer(SDL_Renderer* renderer);
    void loadFromFile(std::string path);
    void free();
    void render(int x, int y);
    int getWidth();
    int getHeight();
};