#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

#include "SDL_Utils.h"
#include "Component.h"

class Transform;

class ImageRenderer: public Component
{
public:
    __CMPID_DECL__(CMP_IMAGERENDERER)
    ImageRenderer();
    ~ImageRenderer();
    void update(float dt) override;
    void start() override;
    void SetImage(const std::string& textureName);
    void awake(){};
private:
    Texture* image;
};

#endif