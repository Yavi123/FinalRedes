#include "src/include/StateMainMenu.h"
#include "src/include/SDL_Utils.h"
#include <iostream>

MainMenu::MainMenu() {
	sdl = nullptr;
	img = nullptr;
	dest = {30, 30, 600, 400};
}

MainMenu::~MainMenu() {

}

void MainMenu::Init() {
	sdl = SDL_Utils::Instance();
    img = sdl->CreateOrGetImage("Assets/a.png");
}

void MainMenu::Update(float deltaTime) {
	
}

void MainMenu::Render() {
	SDL_Rect src = SDL_Rect({0, 0, img->width, img->height});
	SDL_RenderCopy(sdl->Renderer(), img->_tex, &src, &dest);
}