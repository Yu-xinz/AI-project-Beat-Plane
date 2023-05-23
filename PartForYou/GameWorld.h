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

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  std::list <GameObject*> get_ob();

  void push(GameObject* obj);
  
  void change_on();

  void change_raquire();

  void change_have_destroyed();

  GameWorld* copy_world(GameWorld* world);



private:
  std::list <GameObject*> object;
  int love;
  int require;
  int max_on,on;
  int have_destroyed;
};

#endif // !GAMEWORLD_H__
