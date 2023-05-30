#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>

class Texture {
public:
    Texture(SDL_Texture* texture, u_int32_t w, u_int32_t h);
    ~Texture();
    SDL_Texture* _tex;
    int32_t width;
    int32_t height;
};

class SDL_Utils {
public:
    static void Init();
    static SDL_Utils* Instance();
    static void Clear();

    SDL_Window* Window();
    SDL_Renderer* Renderer();
    Texture* CreateOrGetImage(const std::string& file);
    void DrawRect(const SDL_Rect& rect, const SDL_Color& c);

private:

    SDL_Utils();
    ~SDL_Utils();

    void Create();

    static SDL_Utils* _instance;

    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::unordered_map<std::string, Texture*> _images;

};

#endif