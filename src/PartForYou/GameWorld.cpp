#include "GameWorld.h"
#include <cstring>

GameWorld::GameWorld() {
  love=5;
}

GameWorld::~GameWorld() {

}


void GameWorld::Init() {
  std::cout << "Init" << std::endl;
  object.push_back(new Dawnbreaker(this));
  std::cout << "Init2" << std::endl;
  for(int i=0;i<30;i++){
    int x=randInt(0,WINDOW_WIDTH-1);
    int y=randInt(0,WINDOW_HEIGHT-1);
    double sz=((double)randInt(10,40))/100;
    object.push_back(new Star(x,y,sz,this));
  }
  //require=3*GetLevel();
  require = 3 * 5;
  std::cout << "Init3" << std::endl;
  max_on=3;
  on=0;
  have_destroyed=0;
}

LevelStatus GameWorld::Update() {
  if(randInt(1,30)==1){
    int x=randInt(0,WINDOW_WIDTH-1);
    double sz=((double)randInt(10,40))/100;
    GameObject* s=new Star(x,WINDOW_HEIGHT-1,sz,this);
    object.push_back(s);
  }
  if(on<max_on && randInt(1,100)<=(max_on-on)) {
    int possible=randInt(1,3);
    GameObject* p;
    switch (possible)
    {
    case 1:
      p=new Alphatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+2*5,4+5,2+5/5,this);
      object.push_back(p);
      on++;
      break;
    case 2:
      p=new Sigmatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,25+5*5,2+5/5,this);
      object.push_back(p);
      on++;
      break;
    case 3:
      p=new Omegatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+5,2+2*5,3+5/4,this);
      object.push_back(p);
      on++;
      break;
    default:
      break;
    }
  }
  std::list <GameObject*>::iterator bg=object.begin();
  double result=(*bg)->evaluatefunction();
  for(std::list <GameObject*>::iterator i=object.begin();i!=object.end();++i)
  {
    (*i)->Update();
    if((*i)->jud_bullet(1)){
      GameObject* b=new B_bullet((*i)->GetX(),(*i)->GetY()+50,0.5+0.1*(*i)->get_level(),5+3*(*i)->get_level(),this);
      object.push_back(b);
    }
  }
  (*bg)->Q_iteration(this);
  if((*bg)->get_hp()<=0) {
    love--;
    return LevelStatus::DAWNBREAKER_DESTROYED;
  }

  //if(require<=0)
    //return LevelStatus::LEVEL_CLEARED;

  for(std::list <GameObject*>::iterator i=object.begin();i!=object.end();)
  {
    if(!(*i)->jud_life())
    {
      delete *i;
      i=object.erase(i);
    }
    else
      i++;
  }
  std::string s = "HP: " + std::to_string((*bg)->get_hp()) + "/100" + "   Life: " + std::to_string(love) + "   Enemies(have destroyed / on screen): " + std::to_string(have_destroyed) + "/" + std::to_string(on) + "   Score: " + std::to_string(GetScore());
  SetStatusBarMessage(s);
  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  for(std::list <GameObject*>::iterator i=object.begin();i!=object.end();)
  {
    delete *i;
    i=object.erase(i);
  }
}


bool GameWorld::IsGameOver() const {
  if(love<=0)
    return true;
  return false;
}


std::list <GameObject*> GameWorld::get_ob() {
  return object;
}


void GameWorld::push(GameObject* obj) {
  object.push_back(obj);
}

void GameWorld::change_on() {on--;}

void GameWorld::change_raquire() {require--;}

void GameWorld::change_have_destroyed() {have_destroyed++;}

GameWorld* GameWorld::copy_world(GameWorld* world){
  GameWorld* new_world=new GameWorld();
  std::list <GameObject*> new_object;
  for(std::list <GameObject*>::iterator i=world->object.begin();i!=world->object.end();++i){
    if((*i)->gettype()==1 || (*i)->gettype()==4 || (*i)->gettype()==5 || (*i)->gettype()==6 || (*i)->gettype()==7){
      new_object.push_back((*i));
    }
  }
  new_world->object=new_object;
  new_world->love=world->love;
  new_world->require=world->require;
  new_world->max_on=world->max_on;
  new_world->on=world->on;
  new_world->have_destroyed=world->have_destroyed;
  return new_world;
}

