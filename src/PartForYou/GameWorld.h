#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>

#include "WorldBase.h"
#include "GameObjects.h"

class GameObject;

class GameWorld : public WorldBase {
public:
  GameWorld(); 

  virtual ~GameWorld();

  virtual void Init() override; // initialize the world

  virtual LevelStatus Update() override; 

  virtual void CleanUp() override; //clean up the world

  virtual bool IsGameOver() const override; // whether game over or not

  std::list <GameObject*> get_ob();

  void push(GameObject* obj);
  
  void change_on();

  void change_require();

  void change_have_destroyed();



private:
  std::list <GameObject*> object;
  int love; // life
  int require;
  int max_on; // maximum number of enemies on the screen
  int on; // the number of enemies on the screen now
  int have_destroyed; // the number of enemies which have been destroyed
};

#endif // !GAMEWORLD_H__
