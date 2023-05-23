#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"
#include "GameWorld.h"
#include <unordered_map>

/// @brief A state for Dawnbreaker
typedef struct state {
    int x_move;
    int y_move;
    int health;
} State;

typedef struct q_state {
    int self_x;
    int self_y;
    int density_plane[4]; //0:low  1:middle  2:high
    int density_bullet[4]; //0:low  1:middle  2:high
    int nearest_bullet_direction; //Different direction
    int nearest_plane_direction;
    int nearest_bullet_distance; //0: far away  1: near
    int nearest_plane_distance;

} Q_state;

struct HashFunction {
    std::size_t operator()(const Q_state& state) const {
        std::size_t hash = 0;
        hash = hash * 37 + std::hash<int>{}(state.self_x);
        hash = hash * 37 + std::hash<int>{}(state.self_y);
        hash = hash * 37 + std::hash<int>{}(state.density_plane[0]);
        hash = hash * 37 + std::hash<int>{}(state.density_plane[1]);
        hash = hash * 37 + std::hash<int>{}(state.density_plane[2]);
        hash = hash * 37 + std::hash<int>{}(state.density_plane[3]);
        hash = hash * 37 + std::hash<int>{}(state.density_bullet[0]);
        hash = hash * 37 + std::hash<int>{}(state.density_bullet[1]);
        hash = hash * 37 + std::hash<int>{}(state.density_bullet[2]);
        hash = hash * 37 + std::hash<int>{}(state.density_bullet[3]);
        hash = hash * 37 + std::hash<int>{}(state.nearest_bullet_direction);
        hash = hash * 37 + std::hash<int>{}(state.nearest_plane_direction);
        hash = hash * 37 + std::hash<int>{}(state.nearest_bullet_distance);
        hash = hash * 37 + std::hash<int>{}(state.nearest_plane_distance);
        return hash;
    }
};
inline bool operator==(const Q_state& lhs, const Q_state& rhs) {
    return (lhs.self_x == rhs.self_x &&
            lhs.self_y == rhs.self_y &&
            std::equal(std::begin(lhs.density_plane), std::end(lhs.density_plane), std::begin(rhs.density_plane)) &&
            std::equal(std::begin(lhs.density_bullet), std::end(lhs.density_bullet), std::begin(rhs.density_bullet)) &&
            lhs.nearest_bullet_direction == rhs.nearest_bullet_direction &&
            lhs.nearest_plane_direction == rhs.nearest_plane_direction &&
            lhs.nearest_bullet_distance == rhs.nearest_bullet_distance &&
            lhs.nearest_plane_distance == rhs.nearest_plane_distance);
}
/*
type:
1. Downbreaker
2. Star
3. Blue_Bullet
4. Alphatron
5. Sigmatron
6. Omegatron
7. Red_Bullet
8. Power_goodie
9. Meteor_goodie
10. Meteor
11. Explosion
12. Heal_goodie
*/

class GameWorld;
//Gameobject
class GameObject : public ObjectBase {
public:
    GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* wrd);
    void set_life(bool lf);
    bool jud_life();
    virtual void set_move(int x1, int y1)=0;
    virtual bool jud_bullet(bool fire)=0;
    virtual bool jud_meteor(bool fire2)=0;
    virtual int get_meteor(){return 0;}
    virtual void add_meteor(){}
    virtual int get_level(){return 0;}
    virtual void add_level(){}
    virtual int get_hp(){return 0;}
    virtual int get_dmg(){return 0;}
    virtual void set_hp(int dg){}
    virtual void set_depth(int dep){}
    virtual int get_depth(){return 0;};
    virtual void dodgebullet()=0;
    virtual void targetforalpha()=0;
    virtual void Astar(GameWorld *world)=0;
    virtual void Q_iteration(GameWorld *world)=0;
    virtual int Q_get_action(Q_state *ste)=0;
    virtual double Q_get_value(Q_state *ste)=0;
    virtual void Q_table_init(const std::string& filename)=0;
    virtual double evaluatefunction();
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename)=0;
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
    virtual bool jud_meteor(bool fire2);
    virtual int get_meteor();
    virtual int get_level();
    virtual void add_level();
    virtual void add_meteor();
    virtual int get_hp();
    virtual void set_hp(int dg);
    virtual void dodgebullet();
    virtual void targetforalpha();
    virtual void Astar(GameWorld *world);
    virtual void Q_iteration(GameWorld *world);
    virtual int Q_get_action(Q_state *ste);
    virtual double Q_get_value(Q_state *ste);
    virtual void Q_table_init(const std::string& filename);
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename);
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
    int hp,energy;
    int depth;
    int x_move,y_move;
    int num_met,level;
    //double Qtable[7][9];
    std::unordered_map<Q_state, std::vector<double>, HashFunction> q_table;
    Q_state state_before;
    double evaluateBulletDirection(GameWorld *world, State state);
    double evaluateEnemyDirection(GameWorld *world, State state);
    double evaluateEnemyDistance(GameWorld *world, double threshold, State state);
    double evaluateBorder(GameWorld *world, State state);
    double getEvaluation(State state);
};


//Star
class Star : public GameObject {
public:
    Star(int x, int y, double size, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;}
    virtual bool jud_meteor(bool fire2){return false;}
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
};


//B_bullet
class B_bullet : public GameObject {
public:
    B_bullet(int x, int y, double size, int dmg, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;}
    virtual bool jud_meteor(bool fire2){return false;}
    virtual int get_dmg();
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
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
    virtual bool jud_meteor(bool fire2){return false;}
    virtual int get_hp();
    virtual void set_hp(int dg);
    virtual int get_dmg();
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
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
    virtual bool jud_meteor(bool fire2){return false;}
    virtual int get_hp();
    virtual void set_hp(int dg);
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
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
    virtual bool jud_meteor(bool fire2){return false;}
    virtual int get_hp();
    virtual void set_hp(int dg);
    virtual int get_dmg();
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
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
    virtual bool jud_meteor(bool fire2){return false;}
    virtual int get_dmg();
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
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
    virtual bool jud_meteor(bool fire2){return false;}
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
};


//Meteor_goodie
class Meteor_goodie : public GameObject {
public:
    Meteor_goodie(int x, int y, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;} 
    virtual bool jud_meteor(bool fire2){return false;}
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
};


//meteor
class Meteor : public GameObject {
public:
    Meteor(int x, int y, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;} 
    virtual bool jud_meteor(bool fire2){return false;}
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
};


//Explosion
class Explosion : public GameObject {
public:
    Explosion(int x, int y, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;} 
    virtual bool jud_meteor(bool fire2){return false;}
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
};


//Heal
class Heal : public GameObject {
public:
    Heal(int x, int y, GameWorld* wrd);
    virtual void Update();
    virtual void set_move(int x1, int y1){}
    virtual bool jud_bullet(bool fire){return false;} 
    virtual bool jud_meteor(bool fire2){return false;}
    virtual void dodgebullet(){return;}
    virtual void targetforalpha(){return;}
    virtual void Astar(GameWorld *world){return;}
    virtual void Q_iteration(GameWorld *world){return;}
    virtual int Q_get_action(Q_state *ste){return -1;}
    virtual double Q_get_value(Q_state *ste){return 0.f;}
    virtual void Q_table_init(const std::string& filename){return;}
    virtual void saveQTableToCSV(std::unordered_map<Q_state, std::vector<double>, HashFunction>& qTable, const std::string& filename){return ;}
};
#endif // GAMEOBJECTS_H__