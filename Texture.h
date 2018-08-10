#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class Texture
{
  private:
    SDL_Texture* _texture;
    SDL_Renderer* _renderer;
    TTF_Font* _font;
    int _width;
    int _height;
    
  public:
    Texture();
    ~Texture();
    void setRenderer(SDL_Renderer* renderer);
    void setFont(TTF_Font* font);
    void loadFromFile(std::string path);
    void loadFromText(std::string text, SDL_Color textColor);
    void free();
    void render(int x, int y);
    int getWidth();
    int getHeight();
};