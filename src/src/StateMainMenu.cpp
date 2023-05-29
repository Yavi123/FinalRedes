#include "src/include/StateMainMenu.h"
#include "src/include/NetManager.h"
#include "src/include/Redes/Message.h"
#include "src/include/SDL_Utils.h"
#include "src/include/InputManager.h"
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

	NetManager::Instance()->SetOnLogin([](const LoginMessage&login) { std::cout << login.userName << "\n";});
}

void MainMenu::Update(float deltaTime) {
	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_1)) {
		LoginMessage msg("pito");
		NetManager::Instance()->SendMessage(msg);
	}
}

void MainMenu::Render() {
	/*
	SDL_Rect src = {0, 0, 1000, 1000};
	SDL_RenderCopy(sdl->Renderer(), img->_tex, &src, &dest);
	*/
}