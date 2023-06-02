#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "Serializable.h"
#include "Socket.h"
#include "src/include/Vector2.h"
#include "src/include/GameObject.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 *  Mensaje del protocolo de la aplicación de Chat
 *
 *  +-------------------+
 *  | Tipo: uint8_t     | 0 (login), 1 (mensaje), 2 (logout)
 *  +-------------------+
 *  | Nick: char[8]     | Nick incluido el char terminación de cadena '\0'
 *  +-------------------+
 *  |                   |
 *  | Mensaje: char[80] | Mensaje incluido el char terminación de cadena '\0'
 *  |                   |
 *  +-------------------+
 *
 */

enum MessageType : uint8_t
{
    EMPTY               = 0,
    LOGIN               = 1,
    MATCHSTART          = 2,
    POSITION            = 3,
    ONTURNEND           = 4,
    NEWOBJECT           = 5,
    DESTROYOBJECT       = 6,
    MATCHEND            = 7,
    REDUCEHEALTH        = 8,
    LOGOUT              = 9
};

class Message: public Serializable
{
public:
    u_int8_t MESSAGE_SIZE = sizeof(uint8_t);

    const static u_int16_t MAX_SIZE = 1024;

    Message(MessageType a);

    virtual void to_bin() override;

    virtual int from_bin(char * bobj) override;

    MessageType type;
};

class LoginMessage : public Message {
public:
    LoginMessage();
        
    LoginMessage(std::string name);

    void to_bin() override;

    int from_bin(char * bobj) override;

    std::string userName;
    size_t nameLength;
};

class MatchStartMessage : public Message {
public:
    MatchStartMessage() : Message(MATCHSTART){};
};

class PositionMessage : public Message {
public:
    PositionMessage();

    PositionMessage(u_int16_t gOId, const Vector2& pos);

    void to_bin() override;

    int from_bin(char * bobj) override;

    u_int16_t gObjectId;
    Vector2 position;
};

class TurnEndMessage : public Message {
public:
    TurnEndMessage() : Message(ONTURNEND){};
};

class NewObjectMessage : public Message {
public:
    NewObjectMessage() : Message(NEWOBJECT){};
    NewObjectMessage(GameObject* toSend);

    void to_bin() override;

    int from_bin(char * bobj) override;

    GameObject* result;
};

class DestroyObjectMessage : public Message {
public:
    DestroyObjectMessage() : Message(DESTROYOBJECT){};
    DestroyObjectMessage(u_int16_t idDestroyed);

    void to_bin() override;

    int from_bin(char * bobj) override;

    u_int16_t idToKill;
};

class ReduceHealthMessage : public Message {
public:
    ReduceHealthMessage() : Message(REDUCEHEALTH){};
    ReduceHealthMessage(u_int16_t idHit, u_int16_t newValue);

    void to_bin() override;

    int from_bin(char * bobj) override;

    u_int16_t idToCheck;
    u_int16_t newHealth;
};


