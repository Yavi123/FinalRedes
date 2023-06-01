//Execute rendercube

#include "src/include/RenderCube.h"
#include "src/include/SDL_Utils.h"
#include "src/include/Transform.h"
#include "src/include/GameObject.h"

RenderCube::RenderCube() {
    color = {255, 0, 255, 255};
    _cube = nullptr;
    tr = nullptr;
}

RenderCube::~RenderCube() {
    delete _cube;
}


void RenderCube::start() {
    tr = gameObject->getTransform();

    setColor(color);
}

void RenderCube::update(float dt) {
    SDL_Rect src = { 0, 0, _cube->width, _cube->height };

    SDL_Rect dest = { tr->getPosition().x , tr->getPosition().y ,
        tr->getSize().x, tr->getSize().y };

    if (SDL_RenderCopyEx(SDL_Utils::Instance()->Renderer(), 
        _cube->_tex, &src, &dest, tr->getRotation(), 
        NULL, SDL_RendererFlip::SDL_FLIP_NONE)) {
            std::cout << "Error en rendercube update: " << SDL_GetError() << "\n";
        }
}

void RenderCube::setColor(const SDL_Color& c) {

    color = c;
    delete _cube;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 10;
    rect.h = 10;

    SDL_Surface* dst = SDL_CreateRGBSurface(0, 10, 10, 32, 0, 0, 0, 0);
    SDL_SetSurfaceBlendMode(dst, SDL_BLENDMODE_BLEND);

    if (SDL_FillRect(dst, &rect, SDL_Utils::Instance()->ColourToUint(c))) {
        std::cout << "Error en rendercube start: " << SDL_GetError() << "\n";
    }

    _cube = new Texture(SDL_CreateTextureFromSurface(SDL_Utils::Instance()->Renderer(), dst), dst->w, dst->h);

    SDL_FreeSurface(dst);
}
