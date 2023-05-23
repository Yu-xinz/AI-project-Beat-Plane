
#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"
#include "GameWorld.h"
#include "json.h"
#include <queue>
#include <fstream>
#include <sstream>

typedef std::tuple<int, double, double> ObjectStatus;
typedef std::vector<ObjectStatus> ObjectList;

/// @brief A state for Dawnbreaker
typedef struct state {
    int x_origin;
    int y_origin;
    double x_pos;
    double y_pos;
    double health;
    double depth;
    ObjectList objects;
} State;

class GameWorld;
//Gameobject
class GameObject : public ObjectBase {
public:
    GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* wrd);
    void set_life(bool lf);
    bool jud_life();
    virtual void set_move(int x1, int y1)=0;
    virtual bool jud_bullet(bool fire)=0;
    virtual bool jud_meteor(GameWorld *world, bool fire2)=0;
    virtual int get_meteor(){return 0;}
    virtual void add_meteor(){}
    virtual int get_level(){return 0;}
    virtual void add_level(){}
    virtual double get_hp(){return 0;}
    virtual int get_dmg(){return 0;}
    virtual void set_hp(int dg){}
    virtual void set_depth(int dep){}
    virtual int get_depth(){return 0;};
    virtual void dodgebullet()=0;
    virtual void targetforalpha()=0;
    virtual void Reinforcement(GameWorld *world)=0;
    virtual void Q_iteration(GameWorld *world)=0;
    virtual double evaluatefunction();
    int gettype();
    void settype(int ty);
    GameWorld* get_world();
    //GameWorld* get_world_copy(GameWorld* world);
    GameWorld* getnextworld(GameWorld *world,int x_move,int y_move);
    bool track(int x1,int y1,int x2,int y2,double s1,double s2);
private:
    bool life;
    int type;
    GameWorld* world;
};


//Dawnbreaker
class Dawnbreaker : public GameObject {
public:
    Dawnbreaker(GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1,int y1);
    virtual bool jud_bullet(bool fire);
    virtual bool jud_meteor(GameWorld *world, bool fire2);
    virtual int get_meteor();
    virtual int get_level();
    virtual void add_level();
    virtual void add_meteor();
    virtual double get_hp();
    virtual void set_hp(int dg);
    virtual void dodgebullet();
    virtual void targetforalpha();
    virtual void Reinforcement(GameWorld *world);
    virtual void Q_iteration(GameWorld *world);
    /* state space:
            start                                                   0
            crashed by bullet                                       1
            crashed by alpha                                        2
            crashed by alpha and bullet                             3
            x_distance between Dawnbreaker and alpha (beat alpha)   4
            nothing                                                 5
            end (hp=0)                                              6
       directions(actions):
            up (0,1)            0
            right (1,0)         1
            down (0,-1)         2
            left (-1,0)         3       
            up+right (1,1)      4 
            up+left (-1,1)      5  
            down+right (1,-1)   6
            down+left (-1,-1)   7  
            idle (0,0)          8
    */
private:
    double hp,energy;
    int x_move,y_move;
    int num_met,level;
    double Qtable[7][9];
    void Astar(GameWorld *world, int depth);
    double evaluateBulletDirection(GameWorld *world, State state);
    double evaluateEnemyDirection(GameWorld *world, State state);
    double evaluateEnemyDistance(GameWorld *world, double threshold, State state);
    double evaluateBorder(GameWorld *world, State state);
    double evaluateMove(State state);
    double evaluatePosition(State state);
    double evaluateGoodieDistance(GameWorld *world, State state);
    double getEvaluation(State state);
    bool writeTrainingData(GameWorld *world);
    bool stateUpdate(GameWorld *world, *State state);
    State stateInit(GameWorld *world);
};


//Star
class Star : public GameObject {
public:
    Star(int x, int y, double size, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;}
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
};


//B_bullet
class B_bullet : public GameObject {
public:
    B_bullet(int x, int y, double size, int dmg, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;}
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual int get_dmg();
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
private:
    int damage;
};


//Alphatron
class Alphatron : public GameObject {
public:
    Alphatron(int x, int y, int hp0,int dmg,int spd,GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;}
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual double get_hp();
    virtual void set_hp(int dg);
    virtual int get_dmg();
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
private:
    int hp,energy;
    int damage,speed; //speed=2
    int time,move_dir;
};


//Sigmatron
class Sigmatron : public GameObject {
public:
    Sigmatron(int x, int y, int hp0,int spd,GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;}
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual double get_hp();
    virtual void set_hp(int dg);
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
private:
    int hp,speed;
    int time,move_dir;
};


//Omegatron
class Omegatron : public GameObject {
public:
    Omegatron(int x, int y, int hp0,int dmg,int spd,GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;}
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual double get_hp();
    virtual void set_hp(int dg);
    virtual int get_dmg();
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
private:
    int hp,energy;
    int damage,speed;
    int time,move_dir;
};


//R_bullet
class R_bullet : public GameObject {
public:
    R_bullet(int x, int y, int direction, int dmg, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;}
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual int get_dmg();
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
private:
    int damage;
};


//Power
class Power : public GameObject {
public:
    Power(int x, int y, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;}
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
};


//Meteor_goodie
class Meteor_goodie : public GameObject {
public:
    Meteor_goodie(int x, int y, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;} 
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
};


//meteor
class Meteor : public GameObject {
public:
    Meteor(int x, int y, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;} 
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
};


//Explosion
class Explosion : public GameObject {
public:
    Explosion(int x, int y, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;} 
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
};


//Heal
class Heal : public GameObject {
public:
    Heal(int x, int y, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;} 
    virtual bool jud_meteor(GameWorld *world, bool fire2) {return false;};
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Reinforcement(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
};
#endif // GAMEOBJECTS_H__
