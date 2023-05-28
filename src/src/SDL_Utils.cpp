#include "src/include/SDL_Utils.h"
#include <iostream>

SDL_Utils* SDL_Utils::_instance = nullptr;

Texture::Texture(SDL_Texture* texture, u_int32_t w, u_int32_t h) {
    _tex = texture;
    width = w;
    height = h;
}

Texture::~Texture() {
    SDL_DestroyTexture(_tex);
}

SDL_Utils::SDL_Utils() {
    _window = nullptr;
    _renderer = NULL;
    _images = std::unordered_map<std::string, Texture>();
}

SDL_Utils::~SDL_Utils() {
	SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void SDL_Utils::Create() {

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        std::cout << "Error en la inicialización de SDL: " << SDL_GetError();
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0) {
        std::cout << "Error en la inicialización de SDL_images: " << SDL_GetError();
    }

    _window = SDL_CreateWindow("Prueba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if(_window == NULL){
        std::cout << "Error en la creación de la ventana SDL: " << SDL_GetError();
        SDL_Quit();
        return;
    }

    const char* err = SDL_GetError();
    std::cout << err << "\n";

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (_renderer == NULL)
        std::cout<< "Error creando el renderer\n";

    const char* errRend = SDL_GetError();
    std::cout << errRend << "\n";
}

void SDL_Utils::Init() {

    if (_instance == nullptr) {
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
    if (_images.find(file) != _images.end())
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
    return &_images.at(file);
}