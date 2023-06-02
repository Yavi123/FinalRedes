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
	opponent = "";
}

MainMenu::~MainMenu() {

}

void MainMenu::Init() {

    GameObject* fondo = new GameObject();
    fondo->getTransform()->setPosition(0, 0);
    fondo->getTransform()->setSize(800, 600);
    fondo->addComponent<ImageRenderer>()->SetImage("Assets/fondo.jpg");
	AddGameObject(fondo);
	if(NetManager::Instance()->isHost()){
		GameObject* obj = new GameObject();
		obj->getTransform()->setPosition(300, 250);
		obj->getTransform()->setSize(200, 200);
		obj->addComponent<Button>()->SetOnClick([this]() {
			stMachine->SetState<Playing>();
			MatchStartMessage msg = MatchStartMessage();
			NetManager::Instance()->SendMessage(msg);
		});
		obj->addComponent<ImageRenderer>()->SetImage("Assets/play.png");
		AddGameObject(obj);
	}	
}

void MainMenu::HandleMessage(const Message& msg) {

	switch (msg.type) {
		case LOGIN: {
			LoginMessage lMsg;
			lMsg.from_bin(msg.data());
			if (lMsg.userName != opponent) {
				opponent = lMsg.userName;
				std::cout<<"Login: " << opponent <<"\n";
				LoginMessage msg(NetManager::Instance()->GetNick());
				NetManager::Instance()->SendMessage(msg);
			}
		}
		break;
		case LOGOUT: 
			if(!NetManager::Instance()->isHost()){
				GameObject* obj = new GameObject();
				obj->getTransform()->setPosition(300, 250);
				obj->getTransform()->setSize(200, 200);
				obj->addComponent<Button>()->SetOnClick([this]() {
					stMachine->SetState<Playing>();
					MatchStartMessage msg = MatchStartMessage();
					NetManager::Instance()->SendMessage(msg);
				});
				obj->addComponent<ImageRenderer>()->SetImage("Assets/play.png");
				AddGameObject(obj);
			}
			NetManager::Instance()->setAsHost();
			
	
			break;
		case MATCHSTART:
			stMachine->SetState<Playing>();
		break;
		default:
		break;
	}
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