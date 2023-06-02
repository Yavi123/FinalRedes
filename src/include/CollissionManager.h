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
        bool wasColliding(int i, int j);
        void setWasColliding(int i, int j, bool value);

    private:
        inline CollissionManager() : colliders(){};
        inline ~CollissionManager(){
            colliders.clear();
        };
        std::vector<GameObject*> colliders;
        static CollissionManager* instance;
        struct Collission{
            int i;
            int j;
        };
        std::vector<Collission> collissions;
};
#endif