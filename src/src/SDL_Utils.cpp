#include "src/include/SDL_Utils.h"
#include <iostream>

Texture::Texture(SDL_Texture* texture, u_int32_t w, u_int32_t h) {
    _tex = texture;
    width = w;
    height = h;
}

Texture::~Texture() {
    delete _tex;
}

SDL_Utils::SDL_Utils() {
    _window = nullptr;
    _renderer = nullptr;
    _images = std::unordered_map<std::string, Texture>();
}

SDL_Utils::~SDL_Utils() {
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void SDL_Utils::Create() {

    if(SDL_Init(0)!=0){
        std::cout << "Error en la inicialización de SDL: " << SDL_GetError();
    }

    _window = SDL_CreateWindow("Prueba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if(_window == NULL){
        std::cout << "Error en la creación de la ventana SDL: " << SDL_GetError();
        SDL_Quit();
    }

    _renderer = SDL_GetRenderer(_window);

    SDL_Surface* windowSurface = SDL_GetWindowSurface(_window);
    int x,y;
    SDL_GetWindowSize(_window, &x, &y);
    SDL_Rect rect = {0, 0, x, y};
    SDL_FillRect(windowSurface, &rect, SDL_MapRGB(windowSurface->format, 255, 255, 255));
    SDL_UpdateWindowSurface(_window);
}

void SDL_Utils::Init() {

    if (!_instance) {
        _instance = new SDL_Utils();
        _instance->Create();
    }
}

SDL_Utils* SDL_Utils::Instance() {
    return _instance;
}

void SDL_Utils::Clear() {

    if (!_instance) {
        delete _instance;
        _instance = nullptr;
    }
}

SDL_Window* SDL_Utils::Window() {
    return _window;
}
SDL_Renderer* SDL_Utils::Renderer() {
    return _renderer;
}
Texture* SDL_Utils::CreateOrGetImage(std::string file) {
    if (_images.at(file)._tex != nullptr)
        return &_images.at(file);

    else {
        SDL_Surface *surface = IMG_Load(file.c_str());
        if (surface == nullptr)
            return nullptr;

        _images.insert(std::pair<std::string, Texture>(file, Texture(SDL_CreateTextureFromSurface(_renderer, surface), surface->w, surface->h)));
        if (_images.at(file)._tex == nullptr) {
            SDL_FreeSurface(surface);
            std::cout << "Couldn't load image: " + file;
            return nullptr;
        }

        SDL_FreeSurface(surface);
    }
}