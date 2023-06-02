#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>

class Texture {
public:
    Texture(SDL_Texture* texture, u_int32_t w, u_int32_t h);
    Texture();
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
    void DrawRect(const SDL_Rect& rect, const SDL_Color& c, bool fill = true);
    
    Uint32 ColourToUint(SDL_Color color)
    {
        return (Uint32)((color.r << 16) + (color.g << 8) + (color.b << 0) + (color.a << 24));
    }
    SDL_Color build_sdlcolor(Uint32 num) {
        return
        {
        static_cast<Uint8>((num >> 24) & 0xff),
        static_cast<Uint8>((num >> 16) & 0xff),
        static_cast<Uint8>((num >> 8) & 0xff),
        static_cast<Uint8>(num & 0xff)
        };
    }

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