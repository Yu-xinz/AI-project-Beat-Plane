#include "GameWorld.h"
#include <cstring>
// #include <omp.h>

GameWorld::GameWorld() {
  love=5;
}

GameWorld::~GameWorld() {

}

void GameWorld::Init() {
  object.push_back(new Dawnbreaker(this));
  for(int i=0;i<30;i++){
    int x=randInt(0,WINDOW_WIDTH-1);
    int y=randInt(0,WINDOW_HEIGHT-1);
    double sz=((double)randInt(10,40))/100;
    object.push_back(new Star(x,y,sz,this));
  }
  //require=3*GetLevel();
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
    GameObject* p=new Alphatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+2*GetLevel(),4+GetLevel(),2+GetLevel()/5,this);
    object.push_back(p);
    on++;
  }
  std::list <GameObject*>::iterator bg=object.begin();
  double result=(*bg)->evaluatefunction();
  // #pragma omp parallel for
  for(std::list <GameObject*>::iterator i=object.begin();i!=object.end();++i)
  {
    /*if(result>GetScore()){
      (*i)->targetforalpha();
    }
    else{
      (*i)->dodgebullet();
    }*/
    (*i)->Update();
    if((*i)->jud_bullet(1)){
      GameObject* b=new B_bullet((*i)->GetX(),(*i)->GetY()+50,0.5+0.1*(*i)->get_level(),5+3*(*i)->get_level(),this);
      object.push_back(b);
    }
  }

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
  std::string s = "HP: " + std::to_string((*bg)->get_hp()) 
  + "/100" + "   Life: " + std::to_string(love) 
  + "   Enemies(have destroyed / on screen): " 
  + std::to_string(have_destroyed) + "/" + std::to_string(on) 
  + "   Score: " + std::to_string(GetScore()) + "  evaluate"+std::to_string(result);
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

