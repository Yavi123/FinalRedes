#ifndef _COLLISSIONMANAGER_H_
#define _COLLISSIONMANAGER_H_

class GameObject;
#include <vector>

class CollissionManager{
    public:

        static CollissionManager* getInstance();
        static CollissionManager* init();
        static void clear();
        void checkCollissions();
        void registerObject(GameObject* go); 
        void deregisterObject(GameObject* go);
        void reset();

    private:
        inline CollissionManager() : colliders(){};
        inline ~CollissionManager(){
            colliders.clear();
        };
        std::vector<GameObject*> colliders;
        static CollissionManager* instance;
};
#endif