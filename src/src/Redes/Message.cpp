#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "src/include/Redes/Serializable.h"
#include "src/include/Redes/Socket.h"
#include "src/include/Redes/Message.h"
#include "src/include/Transform.h"
#include "src/include/RenderCube.h"


Message::Message(MessageType a) : type(a){
    _data = nullptr;
};
Message::Message(const Message& msg){
    alloc_data(MAX_SIZE);
    memcpy(_data, msg._data, MAX_SIZE);
    type = msg.type;
}

void Message::to_bin() {
    alloc_data(MAX_SIZE);
    memset(_data, 0, MAX_SIZE);
    memcpy(_data, &type, sizeof(MessageType));
}

int Message::from_bin(char * bobj) {
    alloc_data(MAX_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MAX_SIZE);
    memcpy(&type, bobj, sizeof(MessageType));
    return 0;
}



LoginMessage::LoginMessage() : Message(LOGIN), userName("SinNombre"), nameLength(strlen(userName.c_str()))
{ MESSAGE_SIZE = strlen(userName.c_str()) + sizeof(uint8_t) + sizeof(size_t); };

LoginMessage::LoginMessage(std::string name) : Message(LOGIN), userName(name), nameLength(strlen(userName.c_str()))
{ MESSAGE_SIZE = strlen(userName.c_str()) + sizeof(uint8_t) + sizeof(size_t); };

void LoginMessage::to_bin() {
    alloc_data(MAX_SIZE);
    memset(_data, 0, MAX_SIZE);
    char* aux = _data;
    memcpy(aux, &type, sizeof(MessageType));
    aux += sizeof(MessageType);

   

    memcpy(aux, &nameLength, sizeof(size_t));
    aux += sizeof(size_t);

    

    const char* a = userName.c_str();
        memcpy(aux, a, nameLength);

  
}

int LoginMessage::from_bin(char * bobj) {

    alloc_data(MAX_SIZE);
    char* aux = bobj;
    memcpy(static_cast<void*>(_data), aux, MAX_SIZE);
    memcpy(&type, aux, sizeof(MessageType));
    aux += sizeof(uint8_t);

  

    memcpy(&nameLength, aux, sizeof(size_t));
    aux += sizeof(size_t);


    char user[nameLength];
    memcpy(user, aux, nameLength);
    userName = std::string(user);


    return 0;
}



TransformMessage::TransformMessage() : TransformMessage(0, {0, 0}, 0){ }

TransformMessage::TransformMessage(u_int16_t gOId, const Vector2& pos, float rot): Message(TRANSFORM) {
    gObjectId = gOId;
    position = pos;
    rotation = rot;
}

void TransformMessage::to_bin() {

    alloc_data(MAX_SIZE);
    memset(_data, 0, MAX_SIZE);
    char* aux = _data;

    memcpy(aux, &type, sizeof(MessageType));
    aux += sizeof(MessageType);

    memcpy(aux, &gObjectId, sizeof(u_int16_t));
    aux += sizeof(u_int16_t);

    memcpy(aux, &position.x, sizeof(float));
    aux += sizeof(float);

    memcpy(aux, &position.y, sizeof(float));

    aux += sizeof(float);
    memcpy(aux, &rotation, sizeof(float));

}

int TransformMessage::from_bin(char * bobj) {

    char* aux = bobj;
    alloc_data(MAX_SIZE);
    memcpy(static_cast<void*>(_data), aux, MAX_SIZE);

    memcpy(&type, aux, sizeof(MessageType));
    aux += sizeof(MessageType);
    
    memcpy(&gObjectId, aux, sizeof(u_int16_t));
    aux += sizeof(u_int16_t);

    float newX = 0, newY = 0;
    memcpy(&newX, aux, sizeof(float));
    aux += sizeof(float);
    memcpy(&newY, aux, sizeof(float));
    aux += sizeof(float);
    memcpy(&rotation, aux, sizeof(float));
    aux += sizeof(float);

    position = {newX, newY};
    return 0;
}


NewObjectMessage::NewObjectMessage(GameObject* toSend) : Message(NEWOBJECT){
    result = toSend;
}

void NewObjectMessage::to_bin() {
    alloc_data(MAX_SIZE);
    memset(_data, 0, MAX_SIZE);
    char* aux = _data;

    memcpy(aux, &type, sizeof(MessageType));
    aux += sizeof(MessageType);

    memcpy(aux, &result->id, sizeof(u_int16_t));
    aux += sizeof(u_int16_t);

    float auxVal = result->getTransform()->getPosition().x;
    memcpy(aux, &auxVal, sizeof(float));
    aux += sizeof(float);

    auxVal = result->getTransform()->getPosition().y;
    memcpy(aux, &auxVal, sizeof(float));
    aux += sizeof(float);

    auxVal = result->getTransform()->getSize().x;
    memcpy(aux, &auxVal, sizeof(float));
    aux += sizeof(float);

    auxVal = result->getTransform()->getSize().y;
    memcpy(aux, &auxVal, sizeof(float));
    aux += sizeof(float);

    auxVal = result->getTransform()->getRotation();
    memcpy(aux, &auxVal, sizeof(float));
    aux += sizeof(float);

    Uint32 col = 0x00000000;
    if (result->getComponent<RenderCube>() != nullptr) {
        col = SDL_Utils::Instance()->ColourToUint(result->getComponent<RenderCube>()->GetColor());
    }

    memcpy(aux, &col, sizeof(Uint32));
    aux += sizeof(Uint32);
}

int NewObjectMessage::from_bin(char * bobj) {

    result = new GameObject();

    alloc_data(MAX_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MAX_SIZE);

    memcpy(&type, bobj, sizeof(MessageType));
    bobj += sizeof(MessageType);
    
    memcpy(&result->id, bobj, sizeof(u_int16_t));
    bobj += sizeof(u_int16_t);

    float newX = 0, newY = 0;
    memcpy(&newX, bobj, sizeof(float));
    bobj += sizeof(float);
    memcpy(&newY, bobj, sizeof(float));
    bobj += sizeof(float);
    result->getTransform()->setPosition({newX, newY});

    memcpy(&newX, bobj, sizeof(float));
    bobj += sizeof(float);
    memcpy(&newY, bobj, sizeof(float));
    bobj += sizeof(float);
    result->getTransform()->setSize({newX, newY});

    memcpy(&newX, bobj, sizeof(float));
    bobj += sizeof(float);
    result->getTransform()->setRotation(newX);

    Uint32 newCol;
    memcpy(&newCol, bobj, sizeof(Uint32));
    bobj += sizeof(Uint32);
    result->addComponent<RenderCube>()->setColor(SDL_Utils::Instance()->build_sdlcolor(newCol));
    return 0;

}


DestroyObjectMessage::DestroyObjectMessage(u_int16_t id) : Message(DESTROYOBJECT) {
    idToKill = id;
}

void DestroyObjectMessage::to_bin() {
    alloc_data(MAX_SIZE);
    memset(_data, 0, MAX_SIZE);
    char* aux = _data;

    memcpy(aux, &type, sizeof(MessageType));
    aux += sizeof(MessageType);

    memcpy(aux, &idToKill, sizeof(u_int16_t));
    aux += sizeof(u_int16_t);
}

int DestroyObjectMessage::from_bin(char * bobj) {

    alloc_data(MAX_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MAX_SIZE);

    memcpy(&type, bobj, sizeof(MessageType));
    bobj += sizeof(MessageType);
    
    memcpy(&idToKill, bobj, sizeof(u_int16_t));
    bobj += sizeof(u_int16_t);
    return 0;
}


ReduceHealthMessage::ReduceHealthMessage(u_int16_t idHit, u_int16_t newValue) : ReduceHealthMessage() {
    idToCheck = idHit;
    newHealth = newValue;
}

void ReduceHealthMessage::to_bin() {
    alloc_data(MAX_SIZE);
    memset(_data, 0, MAX_SIZE);
    char* aux = _data;

    memcpy(aux, &type, sizeof(MessageType));
    aux += sizeof(MessageType);

    memcpy(aux, &idToCheck, sizeof(u_int16_t));
    aux += sizeof(u_int16_t);

    memcpy(aux, &newHealth, sizeof(u_int16_t));
    aux += sizeof(u_int16_t);
}

int ReduceHealthMessage::from_bin(char * bobj) {

    alloc_data(MAX_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MAX_SIZE);

    memcpy(&type, bobj, sizeof(MessageType));
    bobj += sizeof(MessageType);
    
    memcpy(&idToCheck, bobj, sizeof(u_int16_t));
    bobj += sizeof(u_int16_t);
    
    memcpy(&newHealth, bobj, sizeof(u_int16_t));
    bobj += sizeof(u_int16_t);
    return 0;
}