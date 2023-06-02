#include "src/include/StateMainMenu.h"
#include "src/include/NetManager.h"
#include "src/include/Redes/Message.h"
#include "src/include/SDL_Utils.h"
#include "src/include/InputManager.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"
#include "src/include/Button.h"
#include "src/include/ImageRenderer.h"
#include "src/include/StateMachine.h"
#include "src/include/StatePlaying.h"
#include <iostream>

MainMenu::MainMenu() {
	
}

MainMenu::~MainMenu() {

}

void MainMenu::Init() {

    GameObject* fondo = new GameObject();
    fondo->getTransform()->setPosition(0, 0);
    fondo->getTransform()->setSize(800, 600);
    fondo->addComponent<ImageRenderer>()->SetImage("Assets/fondo.jpg");

    GameObject* obj = new GameObject();
    obj->getTransform()->setPosition(300, 250);
    obj->getTransform()->setSize(200, 100);
    obj->addComponent<Button>()->SetOnClick([this]() { stMachine->SetState<Playing>();});
    obj->addComponent<ImageRenderer>()->SetImage("Assets/play.png");
	
	AddGameObject(fondo);
	AddGameObject(obj);

	NetManager::Instance()->SetOnLogin([](const LoginMessage& a) 
	{
		std::cout<<"Login: "<<a.userName<<"\n";
		LoginMessage msg("Xx_MiNombre_xX");
		NetManager::Instance()->SendMessage(msg);
		NetManager::Instance()->SetOnLogin(nullptr);
	});
}

void MainMenu::ChangeState() {
	stMachine->SetState<Playing>();
}
/*
void MainMenu::Update(float deltaTime) {
	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_1)) {
		LoginMessage msg("Xx_MiNombre_xX");
		NetManager::Instance()->SendMessage(msg);
	}
}

void MainMenu::Render() {
	SDL_Rect src = {0, 0, 1000, 1000};
	//std::cout << img->_tex << "\n";
	if (SDL_RenderCopy(sdl->Renderer(), img->_tex, &src, &dest) != 0) {
		std::cout << "MainMenu::Render(): Error RenderCopy: " << SDL_GetError() << "\n";
		SDL_ClearError();
	}
}
*/