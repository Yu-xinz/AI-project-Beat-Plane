#include "GameWorld.h"
#include <cstring>

GameWorld::GameWorld() {
  love=1;
}

GameWorld::~GameWorld() {

}


void GameWorld::Init() {
  object.push_back(new Dawnbreaker(this)); //generate Dawnbreaker
  for(int i=0;i<30;i++){
    int x=randInt(0,WINDOW_WIDTH-1);
    int y=randInt(0,WINDOW_HEIGHT-1);
    double sz=((double)randInt(10,40))/100;
    object.push_back(new Star(x,y,sz,this)); //generate stars
  }
  //require=3*GetLevel();
  max_on=7;
  //max_on=(5+GetLevel())/2;
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
    int possible=randInt(1,1);
    GameObject* p;
    switch (possible)
    {
    case 1:
      p=new Alphatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+2*GetLevel(),4+GetLevel(),2+GetLevel()/5,this);
      object.push_back(p);
      on++;
      break;
    case 2:
      p=new Sigmatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,25+5*GetLevel(),2+GetLevel()/5,this);
      object.push_back(p);
      on++;
      break;
    case 3:
      p=new Omegatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+GetLevel(),2+2*GetLevel(),3+GetLevel()/4,this);
      object.push_back(p);
      on++;
      break;
    default:
      break;
    }
    /*int p1=6;
    int p2=2*std::max(GetLevel()-1,0);
    int p3=3*std::max(GetLevel()-2,0);
    int ram=randInt(1,p1+p2+p3);
    if(ram<=p1){
      GameObject* p=new Alphatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+2*GetLevel(),4+GetLevel(),2+GetLevel()/5,this);
      //GameObject* p=new Alphatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+2*6,4+6,2+6/5,this);
      object.push_back(p);
    }
    else if(ram>p1 && ram<=p1+p2){
      GameObject* p=new Sigmatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,25+5*GetLevel(),2+GetLevel()/5,this);
      //GameObject* p=new Sigmatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,25+5*6,2+6/5,this);
      object.push_back(p);
    }
    else{
      GameObject* p=new Omegatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+GetLevel(),2+2*GetLevel(),3+GetLevel()/4,this);
      //GameObject* p=new Omegatron(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+6,2+2*6,3+6/4,this);
      object.push_back(p);
    }
    on++;*/
  }
  std::list <GameObject*>::iterator bg=object.begin();
  double result=(*bg)->evaluatefunction();
  for(std::list <GameObject*>::iterator i=object.begin();i!=object.end();++i)
  {
    /*int x_axis=0,y_axis=0;
    if(GetKey(KeyCode::UP))
      y_axis++;
    if(GetKey(KeyCode::DOWN))
      y_axis--;
    if(GetKey(KeyCode::LEFT))
      x_axis--;
    if(GetKey(KeyCode::RIGHT))
      x_axis++;
    (*i)->set_move(x_axis,y_axis);*/
    (*i)->Update();
    if((*i)->jud_bullet(1)){
      GameObject* b=new B_bullet((*i)->GetX(),(*i)->GetY()+50,0.5+0.1*(*i)->get_level(),5+3*(*i)->get_level(),this);
      object.push_back(b);
    }
    if((*i)->jud_meteor(this, 1)){
      GameObject* b=new Meteor((*i)->GetX(),(*i)->GetY()+100,this);
      object.push_back(b);
    }
  }
  (*bg)->Q_iteration(this);

  if((*bg)->get_hp()<=0) {
    love--;
    return LevelStatus::DAWNBREAKER_DESTROYED;
  }

  /*if(require<=0){
    return LevelStatus::LEVEL_CLEARED;
    //return LevelStatus::DAWNBREAKER_DESTROYED;
  }*/

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
  std::string s = "HP: " + std::to_string((*bg)->get_hp()) + "/100" + "   Life: " + std::to_string(love) + "   Enemies(have destroyed / on screen): " + std::to_string(have_destroyed) + "/" + std::to_string(on) + "   Score: " + std::to_string(GetScore())+"   Level: "+std::to_string(GetLevel());
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
  if(love<=0){
    return true;
  }
  return false;
}


std::list <GameObject*> GameWorld::get_ob() {
  return object;
}


void GameWorld::push(GameObject* obj) {
  object.push_back(obj);
}

void GameWorld::change_on() {on--;}

void GameWorld::change_require() {require--;}

void GameWorld::change_have_destroyed() {have_destroyed++;}

