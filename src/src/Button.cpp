#include "src/include/Button.h"
#include "src/include/InputManager.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"


Button::Button() {

}
Button::~Button() {

}
void Button::update(float dt) {
    if (Input()->MouseClick())
    {
        auto mousePos = Input()->MousePosition();
        auto gObjPos = gameObject->getTransform()->getPosition();
        auto gObjSize = gameObject->getTransform()->getSize();

        if (mousePos.x > gObjPos.x && mousePos.x < gObjPos.x + gObjSize.x &&
            mousePos.y > gObjPos.y && mousePos.y < gObjPos.y + gObjSize.y )

            if (onClick) {
                onClick();
            }
    }
}
void Button::start() {

}
void Button::SetOnClick(const std::function<void()>& onClick) {
    this->onClick = onClick;
}