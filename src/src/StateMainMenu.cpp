#include "src/include/StateMainMenu.h"
#include "src/include/SDL_Utils.h"
#include <iostream>

MainMenu::MainMenu() {
	sdl = nullptr;
	img = nullptr;
	dest = {0, 0, 600, 400};
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
	SDL_Rect src = {0, 0, 1000, 1000};
	SDL_RenderCopy(sdl->Renderer(), img->_tex, &src, &dest);
}