#include "src/include/ImageRenderer.h"
#include "src/include/SDL_Utils.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"

ImageRenderer::ImageRenderer() {

}
ImageRenderer::~ImageRenderer() {

}
void ImageRenderer::update(float dt) {
    if (image != nullptr) {
        Transform* tr = gameObject->getTransform();
        SDL_Rect src = { 0, 0, image->width, image->height };

        SDL_Rect dest = { tr->getPosition().x , tr->getPosition().y ,
            tr->getSize().x, tr->getSize().y };

        if (SDL_RenderCopyEx(SDL_Utils::Instance()->Renderer(), 
            image->_tex, &src, &dest, tr->getRotation(), 
            NULL, SDL_RendererFlip::SDL_FLIP_NONE)) {
                std::cout << "Error en ImageRenderer update: " << SDL_GetError() << "\n";
        }
    }
}
void ImageRenderer::start() {

}
void ImageRenderer::SetImage(const std::string& textureName) {
    image = SDL_Utils::Instance()->CreateOrGetImage(textureName);
}