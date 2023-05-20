#include "GameObjects.h"
#include <cmath>
#include <queue>
#define M_PI 3.1415926

GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* wrd):ObjectBase(imageID,x,y,direction,layer,size){
    world=wrd;
}
void GameObject::set_life(bool lf){life=lf;}
bool GameObject::jud_life(){return life;}
int GameObject::gettype(){return type;}
void GameObject::settype(int ty){type=ty;}
GameWorld* GameObject::get_world(){return world;}
/*GameWorld* GameObject::get_world_copy(GameWorld *world){
    GameWorld* new_world;
    new_world->get_ob()=world->get_ob();
    return new_world;
}*/
GameWorld* GameObject::getnextworld(GameWorld *world,int x_move,int y_move){
    for(auto i:world->get_ob()){
        (i)->set_move(x_move,y_move);
        (i)->Update();
    }
    return world;
}
bool GameObject::track(int x1,int x2,int y1,int y2,double s1,double s2) {
    double d=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    if(d<30.0*(s1+s2))
        return true;
    else
        return false;
}
double GameObject::evaluatefunction(){
    int min_x_alpha=114514;
    int min_x_bullet=114514;
    int cnt_bullet=0;
    int cnt_alpha=0;
    int x_distance;
    int hp;
    int dawnposx;
    for(auto i:get_world()->get_ob()){
        if((i)->gettype()==1){
            hp=(i)->get_hp();
            dawnposx=(i)->GetX();
        }
    }
    double result=(double)get_world()->GetScore();
    for(auto i:get_world()->get_ob()){
        if(((i)->gettype()==4) && (i)->jud_life()){
            cnt_alpha++;
            x_distance=(i)->GetX()-dawnposx;
            if(x_distance <= 0)
                x_distance=(-1)*x_distance;
            if(x_distance <= min_x_alpha)
                min_x_alpha=x_distance;
        }
        if(((i)->gettype()==7) && (i)->jud_life()){
            cnt_bullet++;
            x_distance=(i)->GetX()-dawnposx;
            if(x_distance <= 0)
                x_distance=(-1)*x_distance;
            if(x_distance <= min_x_bullet)
                min_x_bullet=x_distance;
        }
    }
    if(min_x_alpha>0 && min_x_bullet>0 && hp>0){
        result+=-400/min_x_bullet+100/min_x_alpha;
    }
    else if(cnt_bullet==0 && cnt_alpha>0 && min_x_alpha>0){
        result+=100/min_x_alpha;
    }
    else if(cnt_alpha==0 && cnt_bullet>0 && min_x_bullet>0){
        result+=-100/min_x_bullet;
    }
    return result;
}


//Dawnbreaker
Dawnbreaker::Dawnbreaker(GameWorld* wrd):GameObject(IMGID_DAWNBREAKER,300,100,0,0,1.0,wrd){
    hp=100;
    energy=10;
    num_met=0;
    level=0;
    set_life(true);
    settype(1);
    depth=10;
}

void Dawnbreaker::Update(){
    Astar(get_world());
    if((GetX()+x_move*4)>=0&&(GetX()+x_move*4)<=(WINDOW_WIDTH-1))
        MoveTo(GetX()+x_move*4,GetY());
    if((GetY()+y_move*4)>=50&&(GetY()+y_move*4)<=(WINDOW_HEIGHT-1))
        MoveTo(GetX(),GetY()+y_move*4); 
}
void Dawnbreaker::set_move(int x1, int y1){x_move=x1;y_move=y1;}
bool Dawnbreaker::jud_bullet(bool fire){
    if(energy==10&&fire==true){
        energy-=9;
        return true;
    }
    if(energy<10)
        energy++;
    return false;
}
bool Dawnbreaker::jud_meteor(bool fire2){
    if(num_met>0&&fire2==true){
        num_met--;
        return true;
    }
    return false;
}
int Dawnbreaker::get_level(){
    return level;
}
void Dawnbreaker::add_level(){level++;}
int Dawnbreaker::get_meteor(){return num_met;}
void Dawnbreaker::add_meteor(){num_met++;}
int Dawnbreaker::get_hp(){return hp;}
void Dawnbreaker::set_hp(int dg){hp-=dg;}
void Dawnbreaker::dodgebullet(){
    int min_x_distance=114514;
    int min_y_distance=114514;
    int x_distance,y_distance;
    int dawnposx=GetX();
    int dawnposy=GetY();
    int rl=2; //right or left turn_right=0 turn_left=1
    int ud=2; //up or down turn_up=0 turn_down=1
    for(auto i:get_world()->get_ob()){
        if(((i)->gettype()==7) && (i)->jud_life()){
        //if(((i)->gettype()==7 || (i)->gettype()==4) && (i)->jud_life()){
            x_distance=(i)->GetX()-dawnposx;
            y_distance=(i)->GetY()-dawnposy;
            if(x_distance <= 0)
                x_distance=(-1)*x_distance;
            if(y_distance <= 0)
                y_distance=(-1)*y_distance;
            if(x_distance <= min_x_distance){
                min_x_distance=x_distance;
                if((i)->GetX()-dawnposx >= 100 || (i)->GetX()-dawnposx <= -100){
                    rl=2; //dawnbreaker will stay still
                }
                else if((i)->GetX()-dawnposx >=0 && (i)->GetX()-dawnposx <= 100){
                    rl=true; //dawnbreaker will turn left
                }
                else{
                    rl=false; //turn right
                }
            }
            if(y_distance <= min_y_distance){
                min_y_distance=y_distance;
                if((i)->GetY()-dawnposy >= 100 || (i)->GetY()-dawnposy <= -100){
                    ud=2; //dawnbreaker will stay still
                }
                else if((i)->GetY()-dawnposy >=0 && (i)->GetY()-dawnposy <= 100){
                    ud=true; //dawnbreaker will turn left
                }
                else{
                    ud=false; //turn right
                }
            }
        }
    }
    if(rl==2 && ud==2){
        x_move=0;
        y_move=0;
    }
    if(rl==true){ //dawnbreaker will turn left
        x_move=-1;
        if(dawnposx-4<0)
            x_move=1;
    }
    if(rl==false){ //turn right
        x_move=1;
        if(dawnposx+4>(WINDOW_WIDTH-1))
            x_move=-1;
    }
    if(ud==true){ //dawnbreaker will turn down
        y_move=-1;
        if(dawnposy-4<50)
            y_move=1;
    }
    if(ud==false){ //turn up
        y_move=1;
        if(dawnposy+4>(WINDOW_HEIGHT-1))
            y_move=-1;
    }
}
void Dawnbreaker::targetforalpha(){
    int min_x_distance=114514;
    int min_y_distance=114514;
    int x_distance,y_distance;
    int dawnposx=GetX();
    int dawnposy=GetY();
    int rl=2; //right or left turn_right=0 turn_left=1
    int ud=2; //up or down turn_up=0 turn_down=1
    for(auto i:get_world()->get_ob()){
        if(((i)->gettype()==4) && (i)->jud_life()){
            x_distance=(i)->GetX()-dawnposx;
            y_distance=(i)->GetY()-dawnposy;
            if(x_distance <= 0)
                x_distance=(-1)*x_distance;
            if(y_distance <= 0)
                y_distance=(-1)*y_distance;
            if(x_distance <= min_x_distance){
                min_x_distance=x_distance;
                if((i)->GetX()-dawnposx >= 100 || (i)->GetX()-dawnposx <= -100){
                    if((i)->GetX()-dawnposx >= 100){
                        rl=false;
                    }
                    else{
                        rl=true;
                    }
                }
                else if((i)->GetX()-dawnposx >=0 && (i)->GetX()-dawnposx <= 100){
                    rl=true; //dawnbreaker will turn left
                }
                else{
                    rl=false; //turn right
                }
            }
            if(y_distance <= min_y_distance){
                min_y_distance=y_distance;
                if((i)->GetY()-dawnposy >= 100 || (i)->GetY()-dawnposy <= -100){
                    ud=2; //dawnbreaker will stay still
                }
                else if((i)->GetY()-dawnposy >=0 && (i)->GetY()-dawnposy < 100){
                    ud=true; //dawnbreaker will turn down
                    rl=randInt(0,1);
                }
                else{
                    ud=false; //turn up
                    rl=randInt(0,1);
                }
            }
        }
    }
    if(rl==2 && ud==2){
        x_move=0;
        y_move=0;
    }
    if(rl==true){ //dawnbreaker will turn left
        x_move=-1;
        if(dawnposx-4<0)
            x_move=1;
    }
    if(rl==false){ //turn right
        x_move=1;
        if(dawnposx+4>(WINDOW_WIDTH-1))
            x_move=-1;
    }
    if(ud==true){ //dawnbreaker will turn down
        y_move=-1;
        if(dawnposy-4<50)
            y_move=1;
    }
    if(ud==false){ //turn up
        y_move=1;
        if(dawnposy+4>(WINDOW_HEIGHT-1))
            y_move=-1;
    }
    if(dawnposx <= 2*(WINDOW_WIDTH-1)/10 && rl==true){
        x_move=1;
    }
    if(dawnposx >= 8*(WINDOW_WIDTH-1)/10 && rl==false){
        x_move=-1;
    }
    if(dawnposy <= 20 && ud==true){
        y_move=1;
    }
}
void Dawnbreaker::Astar(GameWorld *world){
    /*double result=evaluatefunction();
    if(result > get_world()->GetScore()){
        targetforalpha();
    }
    else{
        dodgebullet();
    }
    return;*/
    std::priority_queue<std::pair<double,std::pair<int,int>>> pq;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            State state{i*4, j*4, get_hp()};
            double eval = getEvaluation(state);
            std::pair<int,int> move(i,j);
            std::pair<double,std::pair<int,int>> temp(eval, move);
            if (eval) //< do not act when nothing get considered (eval == 0)
                pq.push(temp);
            std::cout << "eval = " << eval << std::endl;
        }
    }
    if(!pq.empty()){
        std::pair<int,int> result=pq.top().second;
        x_move=result.first;
        y_move=result.second;
    }
    else{
        x_move=0;
        y_move=0;
    }
}
void Dawnbreaker::Q_iteration(GameWorld *world){
    double alpha=1;
    double lamda=1;
    double max_qval=-114514.0;
    double max_next_qval=-114514.0;
    int max_action;
    int x,y,s1,change_hp,last_hp,reward=0;
    int s=0;
    for(int m=0;m<99;m++){
        for(int i=0;i<9;i++){
            if(Qtable[s][i]>=max_qval){
                max_qval=Qtable[s][i];
                max_action=i;
            }
        }
        if(max_action==0){x=0;y=1;}
        else if(max_action==1){x=1;y=0;}
        else if(max_action==2){x=0;y=-1;}
        else if(max_action==3){x=-1;y=0;}
        else if(max_action==4){x=1;y=1;}
        else if(max_action==5){x=-1;y=1;}
        else if(max_action==6){x=1;y=-1;}
        else if(max_action==7){x=-1;y=-1;}
        else if(max_action==8){x=0;y=0;}
        set_move(x,y);
        GameWorld* new_world=getnextworld(world,x,y);
        s1=5;
        for(auto i:world->get_ob()){
            if((i)->gettype()==1){
                change_hp=(-1)*(i)->get_hp();
            }
        }
        for(auto i:new_world->get_ob()){
            if((i)->gettype()==1){
                change_hp+=(i)->get_hp();
                last_hp=(i)->get_hp();
            }
        }
        if(change_hp==-5){s1=1;reward=-5;}
        if(change_hp==-10){s1=2;reward=-10;}
        if(change_hp==-15){s1=3;reward=-15;}
        if(new_world->GetScore()>world->GetScore()){s1=4;reward=50;}
        if(last_hp==0){s1=6;reward=-200;}
        for(int i=0;i<9;i++){
            if(Qtable[s1][i]>=max_next_qval){
                max_next_qval=Qtable[s1][i];
            }
        }
        Qtable[s][max_action]=Qtable[s][max_action]+alpha*(reward+lamda*max_next_qval-Qtable[s][max_action]);
        s=s1;
        if(last_hp==0){break;}
    }

}
void Dawnbreaker::Reinforcement(GameWorld *world){
    
}
/// @brief Get an *WEIGHTED* evaluation based on the directions between bullets and dawnbreaker
/// @param world
/// @param state description
/// @return evaluation 
double Dawnbreaker::evaluateBulletDirection(GameWorld *world, State state)
{
    double eval = 0.0;
    double tmp;
    double weightByDistance;
    auto objects = world->get_ob();
    auto x_pos = GetX() + state.x_move;
    auto y_pos = GetY() + state.y_move;
    int cnt = 0;
    for (auto each : objects)
    {
        if (each->gettype() != 7) /**< not a bullet*/
            continue;
        if (each->GetY() - y_pos > 0.3 * WINDOW_HEIGHT || each->GetY() - y_pos < 0)
            continue;
        auto dawnToBullet = atan2(each->GetX() - x_pos, each->GetY() - y_pos) * 180 / M_PI; //
        auto bulletDirection = each->GetDirection() - 270;
        weightByDistance = 500 / (1 + abs(each->GetX() - x_pos) + abs(each->GetY() - y_pos));
        eval += 
            90 > abs(dawnToBullet - bulletDirection) ? 
            -1 * abs(dawnToBullet - bulletDirection) 
            : -1 * (180 - abs(dawnToBullet - bulletDirection));
        eval *= weightByDistance;
        cnt++;
    }   
    return eval;
}

/// @brief 
/// @param world 
/// @param state 
/// @return evaluation
double Dawnbreaker::evaluateEnemyDirection(GameWorld *world, State state)
{
    double eval = 0.0;
    double tmp;
    auto objects = world->get_ob();
    auto x_pos = GetX() + state.x_move;
    auto y_pos = GetY() + state.y_move;
    int cnt = 0;
    for (auto each : objects)
    {
        if (each->gettype() != 5 && each->gettype() != 6 && each->gettype() != 7) /**< not a bullet*/
            continue;
        if (each->GetY() - y_pos > 0.15 * WINDOW_HEIGHT || each->GetY() - y_pos < 0)
            continue;
        auto dawnToBullet = atan2(each->GetX() - x_pos, each->GetY() - y_pos) * 180 / M_PI; //
        auto bulletDirection = each->GetDirection() - 270;
        eval = 
            90 > abs(dawnToBullet - bulletDirection) ? 
            -1 * abs(dawnToBullet - bulletDirection) 
            : -1 * (180 - abs(dawnToBullet - bulletDirection));
        cnt++;
    }   
    return eval;
}

/// @brief Get an *WEIGHTED* evaluation based on the X distances between
/// @param world, threshold
/// @return 
double Dawnbreaker::evaluateEnemyDistance(GameWorld *world, double threshold, State state)
{
    double eval = 0.0;
    auto objects = world->get_ob();
    double weightByDistance;
    auto x_pos = GetX() + state.x_move;
    auto y_pos = GetY() + state.y_move;
    int cnt = 0;
    for (auto each : objects)
    {
        if (each->gettype() != 4 & each->gettype() != 5 & each->gettype() != 6) /**< not a bullet*/
            continue;
        if (abs(each->GetY() - y_pos) < 0.3 * WINDOW_HEIGHT) //< too close
            continue;
        if (abs(each->GetX() - x_pos) > threshold) //< x too far
            continue;    
        weightByDistance = 500 / (1 + abs(each->GetX() - x_pos) + abs(each->GetY() - y_pos));
        eval += 1/(0.1 + abs(each->GetX() - x_pos)) + 0.05 * abs(each->GetY() - y_pos) * weightByDistance; 
        cnt++;
    }   
    return eval;
}

/// @brief Make dawnbreaker not to stay at the border of the screen when idle (a tiny weight)
/// @param world 
/// @param state 
/// @return 
double Dawnbreaker::evaluateBorder(GameWorld *world, State state)
{
    auto x_pos = (GetX() + state.x_move);
    auto y_pos = (GetY() + state.y_move);
    if (x_pos < 8 && state.x_move < 0)
        return -597325;
    if (WINDOW_WIDTH - x_pos < 8 && state.x_move > 0)
        return -597325;
    if (x_pos < 8 && state.y_move < 0)
        return -597325;
    if (WINDOW_WIDTH - y_pos < 8 && state.y_move > 0)
        return -597325;
    return 0.0;
}

/// @brief 
/// @return retval:double
double Dawnbreaker::getEvaluation(State state)
{
    auto world = get_world();
    auto retval = 1 * evaluateBulletDirection(world, state) 
                + 3 * evaluateEnemyDirection(world, state)
                + 1 * evaluateEnemyDistance(world, 600, state);
    /*auto world = get_world();
    auto retval = 10 * evaluateBulletDirection(world, state) 
                + 0.1 * evaluateEnemyDistance(world, 600, state)
                + 1 * evaluateBorder(world, state);*/
    return retval;
}



//Star
Star::Star(int x, int y, double size, GameWorld* wrd):GameObject(IMGID_STAR,x,y,0,4,size,wrd){
    set_life(true);
    settype(2);
}
void Star::Update(){
    if(GetY()<0)
        set_life(false);
    else
        MoveTo(GetX(),GetY()-1);
}


//B_bullet
B_bullet::B_bullet(int x, int y, double size, int dmg, GameWorld* wrd):GameObject(IMGID_BLUE_BULLET,x,y,0,1,size,wrd){
    set_life(true);
    settype(3);
    damage=dmg;
}
int B_bullet::get_dmg(){return damage;}
void B_bullet::Update(){
    if(!jud_life())
        return;
    if(GetY()>=WINDOW_HEIGHT){
        set_life(false);
        return;
    }
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==4||(i)->gettype()==5||(i)->gettype()==6) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                (i)->set_hp(get_dmg());
                if((i)->get_hp()<=0) {
                    (i)->set_life(false);
                    get_world()->change_on();
                    get_world()->change_raquire();
                    get_world()->change_have_destroyed();
                    GameObject* e=new Explosion((i)->GetX(),(i)->GetY(),get_world());
                    get_world()->push(e);
                    if(i->gettype()==4)
                        //get_world()->IncreaseScore(50);
                        get_world()->IncreaseScore(1);
                    else if(i->gettype()==5)
                        //get_world()->IncreaseScore(100);
                        get_world()->IncreaseScore(1);
                    else if(i->gettype()==6)
                        //get_world()->IncreaseScore(200);
                        get_world()->IncreaseScore(1);
                    if((i)->gettype()==5&&randInt(1,10)<=2){
                        GameObject* he=new Heal((i)->GetX(),(i)->GetY(),get_world());
                        get_world()->push(he);
                    }
                    else if(i->gettype()==6&&randInt(1,10)<=4){
                        if(randInt(1,10)<=8){
                            GameObject* po=new Power(i->GetX(),i->GetY(),get_world());
                            get_world()->push(po);
                        }
                        else {
                            GameObject* me=new Meteor_goodie(i->GetX(),i->GetY(),get_world());
                            get_world()->push(me);
                        }
                    }
                }
                return;
            }
        }
    }
    MoveTo(GetX(),GetY()+6);
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==4||(i)->gettype()==5||(i)->gettype()==6) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                (i)->set_hp(get_dmg());
                if((i)->get_hp()<=0) {
                    (i)->set_life(false);
                    get_world()->change_on();
                    get_world()->change_raquire();
                    get_world()->change_have_destroyed();
                    GameObject* e=new Explosion((i)->GetX(),(i)->GetY(),get_world());
                    get_world()->push(e);
                    if(i->gettype()==4)
                        //get_world()->IncreaseScore(50);
                        get_world()->IncreaseScore(1);
                    else if(i->gettype()==5)
                        //get_world()->IncreaseScore(100);
                        get_world()->IncreaseScore(1);
                    else if(i->gettype()==6)
                        //get_world()->IncreaseScore(200);
                        get_world()->IncreaseScore(1);
                    if((i)->gettype()==5&&randInt(1,10)<=2){
                        GameObject* he=new Heal((i)->GetX(),(i)->GetY(),get_world());
                        get_world()->push(he);
                    }
                    else if(i->gettype()==6&&randInt(1,10)<=4){
                        if(randInt(1,10)<=8){
                            GameObject* po=new Power(i->GetX(),i->GetY(),get_world());
                            get_world()->push(po);
                        }
                        else {
                            GameObject* me=new Meteor_goodie(i->GetX(),i->GetY(),get_world());
                            get_world()->push(me);
                        }
                    }
                }
                return;
            }
        }
    }
}


//Alphatron
Alphatron::Alphatron(int x, int y,int hp0,int dmg,int spd,GameWorld* wrd):GameObject(IMGID_ALPHATRON,x,y,180,0,1.0, wrd){
    energy=25;
    hp=hp0;
    damage=dmg;
    speed=spd;
    time=0;
    move_dir=0;
    set_life(true);
    settype(4);
}
int Alphatron::get_hp(){return hp;}
void Alphatron::set_hp(int dg){hp-=dg;}
int Alphatron::get_dmg(){return damage;}
void Alphatron::Update(){
    if(!jud_life())
        return ;
    if(GetY()<0) {
        get_world()->change_on();
        set_life(false);
        return ;
    }
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1||(i)->gettype()==3||(i)->gettype()==10) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                if((i)->gettype()==1) {
                    (i)->set_hp(20);
                    set_hp(get_hp());
                    if(i->get_hp()<=0)
                        i->set_life(false);
                }
                else if(i->gettype()==3) {
                    i->set_life(false);
                    set_hp(i->get_dmg());
                }
                else if(i->gettype()==10)
                    set_hp(get_hp());
            }
        }
        if(get_hp()<=0) {
            set_life(false);
            get_world()->change_on();
            get_world()->change_raquire();
            get_world()->change_have_destroyed();
            GameObject* e=new Explosion(GetX(),GetY(),get_world());
            get_world()->push(e);
            //get_world()->IncreaseScore(50);
            get_world()->IncreaseScore(1);
            return ;
        }
    }
    for(auto i:get_world()->get_ob())
        if(i->gettype()==1){
            int diff=(i)->GetX()-GetX();
            if(diff<=0){
                diff=(-1)*diff;
            }
            if(energy>=25&&randInt(1,100)<=50&&diff<=30) {
            //if(energy>=25&&randInt(1,100)<=25) {
                energy-=25;
                GameObject* r=new R_bullet(GetX(),GetY()-50,180,damage,get_world());
                get_world()->push(r);
            }
            break;
        }
    if(energy<25)
        energy++;
    if(time<=0) {
        move_dir=randInt(1,3);
        time=randInt(10,50);    
    }
    else if(GetX()<0) {
        move_dir=3;
        time=randInt(10,50);
    }
    else if(GetX()>=WINDOW_WIDTH) {
        move_dir=2;
        time=randInt(10,50);
    }
    time--;
    if(move_dir==1)
        MoveTo(GetX(),GetY()-speed);
    else if(move_dir==2)
        MoveTo(GetX()-speed,GetY()-speed);
    else if(move_dir==3)
        MoveTo(GetX()+speed,GetY()-speed);
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1||(i)->gettype()==3||(i)->gettype()==10) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                if((i)->gettype()==1) {
                    (i)->set_hp(20);
                    set_hp(get_hp());
                    if(i->get_hp()<=0)
                        i->set_life(false);
                }
                else if(i->gettype()==3) {
                    i->set_life(false);
                    set_hp(i->get_dmg());
                }
                else if(i->gettype()==10)
                    set_hp(get_hp());
            }
        }
        if(get_hp()<=0) {
            set_life(false);
            get_world()->change_on();
            get_world()->change_raquire();
            get_world()->change_have_destroyed();
            GameObject* e=new Explosion(GetX(),GetY(),get_world());
            get_world()->push(e);
            //get_world()->IncreaseScore(50);
            get_world()->IncreaseScore(1);
            return ;
        }
    }
}



//Sigmatron
Sigmatron::Sigmatron(int x, int y, int hp0,int spd,GameWorld* wrd):GameObject(IMGID_SIGMATRON,x,y,180,0,1.0,wrd){
    hp=hp0;
    speed=spd;
    time=0;
    move_dir=0;
    set_life(true);
    settype(5);
}
int Sigmatron::get_hp(){return hp;}
void Sigmatron::set_hp(int dg){hp-=dg;}
void Sigmatron::Update(){
    if(!jud_life())
        return ;
    if(GetY()<0) {
        get_world()->change_on();
        set_life(false);
        return ;
    }
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1||(i)->gettype()==3||(i)->gettype()==10) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                if((i)->gettype()==1) {
                    (i)->set_hp(20);
                    set_hp(get_hp());
                    if(i->get_hp()<=0)
                        i->set_life(false);
                }
                else if(i->gettype()==3) {
                    i->set_life(false);
                    set_hp(i->get_dmg());
                }
                else if(i->gettype()==10)
                    set_hp(get_hp());
            }
        }
        if(get_hp()<=0) {
            set_life(false);
            get_world()->change_on();
            get_world()->change_raquire();
            GameObject* e=new Explosion(GetX(),GetY(),get_world());
            get_world()->push(e);
            //get_world()->IncreaseScore(100);
            get_world()->IncreaseScore(1);
            if(randInt(1,10)<=2){
                GameObject* he=new Heal(GetX(),GetY(),get_world());
                get_world()->push(he);
            }
            return ;
        }
    }
    for(auto i:get_world()->get_ob())
        if(i->gettype()==1){
            if(abs(GetX()-i->GetX())<=10) {
                time=WINDOW_HEIGHT;
                move_dir=1;
                speed=10;
            }
            break;
        }
    if(time<=0) {
        move_dir=randInt(1,3);
        time=randInt(10,50);    
    }
    else if(GetX()<0) {
        move_dir=3;
        time=randInt(10,50);
    }
    else if(GetX()>=WINDOW_WIDTH) {
        move_dir=2;
        time=randInt(10,50);
    }
    time--;
    if(move_dir==1)
        MoveTo(GetX(),GetY()-speed);
    else if(move_dir==2)
        MoveTo(GetX()-speed,GetY()-speed);
    else if(move_dir==3)
        MoveTo(GetX()+speed,GetY()-speed);
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1||(i)->gettype()==3||(i)->gettype()==10) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                if((i)->gettype()==1) {
                    (i)->set_hp(20);
                    set_hp(get_hp());
                    if(i->get_hp()<=0)
                        i->set_life(false);
                }
                else if(i->gettype()==3) {
                    i->set_life(false);
                    set_hp(i->get_dmg());
                }
                else if(i->gettype()==10)
                    set_hp(get_hp());
            }
        }
        if(get_hp()<=0) {
            set_life(false);
            get_world()->change_on();
            get_world()->change_raquire();
            GameObject* e=new Explosion(GetX(),GetY(),get_world());
            get_world()->push(e);
            //get_world()->IncreaseScore(100);
            get_world()->IncreaseScore(1);
            if(randInt(1,10)<=2){
                GameObject* he=new Heal(GetX(),GetY(),get_world());
                get_world()->push(he);
            }
            return ;
        }
    }
}


//Omegatron
Omegatron::Omegatron(int x, int y, int hp0,int dmg,int spd,GameWorld* wrd):GameObject(IMGID_OMEGATRON,x,y,180,0,1.0,wrd){
    hp=hp0;
    energy=50;
    damage=dmg;
    speed=spd;
    time=0;
    move_dir=0;
    set_life(true);
    settype(6);
}
int Omegatron::get_hp(){return hp;}
void Omegatron::set_hp(int dg){hp-=dg;}
int Omegatron::get_dmg(){return damage;}
void Omegatron::Update(){
    if(!jud_life())
        return ;
    if(GetY()<0) {
        get_world()->change_on();
        set_life(false);
        return ;
    }
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1||(i)->gettype()==3||(i)->gettype()==10) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                if((i)->gettype()==1) {
                    (i)->set_hp(20);
                    set_hp(get_hp());
                    if(i->get_hp()<=0)
                        i->set_life(false);
                }
                else if(i->gettype()==3) {
                    i->set_life(false);
                    set_hp(i->get_dmg());
                }
                else if(i->gettype()==10)
                    set_hp(get_hp());
            }
        }
        if(get_hp()<=0) {
            set_life(false);
            get_world()->change_on();
            get_world()->change_raquire();
            GameObject* e=new Explosion(GetX(),GetY(),get_world());
            get_world()->push(e);
            //get_world()->IncreaseScore(200);
            get_world()->IncreaseScore(1);
            if(randInt(1,10)<=4){
                if(randInt(1,10)<=8){
                    GameObject* po=new Power(GetX(),GetY(),get_world());
                    get_world()->push(po);
                }
                else {
                    GameObject* me=new Meteor_goodie(GetX(),GetY(),get_world());
                    get_world()->push(me);
                }
            }
            return ;
        }
    }
    if(energy>=50) {
        energy-=50;
        GameObject* r1=new R_bullet(GetX(),GetY()-50,162,damage,get_world());
        GameObject* r2=new R_bullet(GetX(),GetY()-50,198,damage,get_world());
        get_world()->push(r1);
        get_world()->push(r2);
    }
    if(energy<=50)
        energy++;
    if(time<=0) {
        move_dir=randInt(1,3);
        time=randInt(10,50);    
    }
    else if(GetX()<0) {
        move_dir=3;
        time=randInt(10,50);
    }
    else if(GetX()>=WINDOW_WIDTH) {
        move_dir=2;
        time=randInt(10,50);
    }
    time--;
    if(move_dir==1)
        MoveTo(GetX(),GetY()-speed);
    else if(move_dir==2)
        MoveTo(GetX()-speed,GetY()-speed);
    else if(move_dir==3)
        MoveTo(GetX()+speed,GetY()-speed);
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1||(i)->gettype()==3||(i)->gettype()==10) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                if((i)->gettype()==1) {
                    (i)->set_hp(20);
                    set_hp(get_hp());
                    if(i->get_hp()<=0)
                        i->set_life(false);
                }
                else if(i->gettype()==3) {
                    i->set_life(false);
                    set_hp(i->get_dmg());
                }
                else if(i->gettype()==10)
                    set_hp(get_hp());
            }
        }
        if(get_hp()<=0) {
            set_life(false);
            get_world()->change_on();
            get_world()->change_raquire();
            GameObject* e=new Explosion(GetX(),GetY(),get_world());
            get_world()->push(e);
            //get_world()->IncreaseScore(200);
            get_world()->IncreaseScore(1);
            if(randInt(1,10)<=4){
                if(randInt(1,10)<=8){
                    GameObject* po=new Power(GetX(),GetY(),get_world());
                    get_world()->push(po);
                }
                else {
                    GameObject* me=new Meteor_goodie(GetX(),GetY(),get_world());
                    get_world()->push(me);
                }
            }
            return ;
        }
    }
}


//R_bullet
R_bullet::R_bullet(int x, int y, int direction, int dmg, GameWorld* wrd):GameObject(IMGID_RED_BULLET,x,y,direction,1,0.5,wrd){
    set_life(true);
    settype(7);
    damage=dmg;
}
int R_bullet::get_dmg(){return damage;}
void R_bullet::Update(){
    if(!jud_life())
        return ;
    if(GetY()<0) {
        set_life(false);
        return ;
    }
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                (i)->set_hp(get_dmg());
                if(i->get_hp()<=0)
                        i->set_life(false);
                return ;
            }
            break;
        }
    }
    if(GetDirection()==180)
        MoveTo(GetX(),GetY()-6);
    else if(GetDirection()==162)
        MoveTo(GetX()+2,GetY()-6);
    else if(GetDirection()==198)
        MoveTo(GetX()-2,GetY()-6);
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                (i)->set_hp(get_dmg());
                if(i->get_hp()<=0)
                        i->set_life(false);
                return ;
            }
            break;
        }
    }
}


//Power
Power::Power(int x, int y, GameWorld* wrd):GameObject(IMGID_POWERUP_GOODIE,x,y,0,2,0.5,wrd){
    set_life(true);
    settype(8);
}
void Power::Update(){
    if(!jud_life())
        return ;
    if(GetY()<0) {
        set_life(false);
        return ;
    }
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                get_world()->IncreaseScore(20);
                i->add_level();
                return ;
            }
            break;
        }
    }
    MoveTo(GetX(),GetY()-2);
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                get_world()->IncreaseScore(20);
                i->add_level();
                return ;
            }
            break;
        }
    }
}


//Meteor_goodie
Meteor_goodie::Meteor_goodie(int x, int y, GameWorld* wrd):GameObject(IMGID_METEOR_GOODIE,x,y,0,2,0.5,wrd){
    set_life(true);
    settype(9);
}
void Meteor_goodie::Update(){
    if(!jud_life())
        return ;
    if(GetY()<0) {
        set_life(false);
        return ;
    }
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                get_world()->IncreaseScore(20);
                i->add_meteor();
                return ;
            }
            break;
        }
    }
    MoveTo(GetX(),GetY()-2);
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                get_world()->IncreaseScore(20);
                i->add_meteor();
                return ;
            }
            break;
        }
    }
}


Meteor::Meteor(int x,int y,GameWorld* wrd):GameObject(IMGID_METEOR,x,y,0,1,2.0,wrd){
    set_life(true);
    settype(10);
}
void Meteor::Update(){
    if(!jud_life())
        return ;
    if(GetY()>=WINDOW_HEIGHT){
        set_life(false);
        return ;
    }
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==4||(i)->gettype()==5||(i)->gettype()==6) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                (i)->set_hp(i->get_hp());
                if((i)->get_hp()<=0) {
                    (i)->set_life(false);
                    get_world()->change_on();
                    get_world()->change_raquire();
                    GameObject* e=new Explosion((i)->GetX(),(i)->GetY(),get_world());
                    get_world()->push(e);
                    if(i->gettype()==4)
                        get_world()->IncreaseScore(50);
                    else if(i->gettype()==5)
                        get_world()->IncreaseScore(100);
                    else if(i->gettype()==6)
                        get_world()->IncreaseScore(200);
                    if((i)->gettype()==5&&randInt(1,10)<=2){
                        GameObject* he=new Heal((i)->GetX(),(i)->GetY(),get_world());
                        get_world()->push(he);
                    }
                    else if(i->gettype()==6&&randInt(1,10)<=4){
                        if(randInt(1,10)<=8){
                            GameObject* po=new Power(i->GetX(),i->GetY(),get_world());
                            get_world()->push(po);
                        }
                        else {
                            GameObject* me=new Meteor_goodie(i->GetX(),i->GetY(),get_world());
                            get_world()->push(me);
                        }
                    }
                }
                return ;
            }
        }
    }
    MoveTo(GetX(),GetY()+2);
    SetDirection(GetDirection()+5);
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==4||(i)->gettype()==5||(i)->gettype()==6) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                (i)->set_hp(i->get_hp());
                if((i)->get_hp()<=0) {
                    (i)->set_life(false);
                    get_world()->change_on();
                    get_world()->change_raquire();
                    GameObject* e=new Explosion((i)->GetX(),(i)->GetY(),get_world());
                    get_world()->push(e);
                    if(i->gettype()==4)
                        get_world()->IncreaseScore(50);
                    else if(i->gettype()==5)
                        get_world()->IncreaseScore(100);
                    else if(i->gettype()==6)
                        get_world()->IncreaseScore(200);
                    if((i)->gettype()==5&&randInt(1,10)<=2){
                        GameObject* he=new Heal((i)->GetX(),(i)->GetY(),get_world());
                        get_world()->push(he);
                    }
                    else if(i->gettype()==6&&randInt(1,10)<=4){
                        if(randInt(1,10)<=8){
                            GameObject* po=new Power(i->GetX(),i->GetY(),get_world());
                            get_world()->push(po);
                        }
                        else {
                            GameObject* me=new Meteor_goodie(i->GetX(),i->GetY(),get_world());
                            get_world()->push(me);
                        }
                    }
                }
                return ;
            }
        }
    }
}


//Explosion
Explosion::Explosion(int x, int y, GameWorld* wrd):GameObject(IMGID_EXPLOSION,x,y,0,3,4.5,wrd){
    set_life(true);
    settype(11);
}
void Explosion::Update(){
    SetSize(GetSize()-0.2);
    if(GetSize()<=0.5)
        set_life(false);
}


//Heal
Heal::Heal(int x, int y, GameWorld* wrd):GameObject(IMGID_HP_RESTORE_GOODIE,x,y,0,2,0.5,wrd){
    set_life(true);
    settype(12);
}
void Heal::Update(){
    if(!jud_life())
        return ;
    if(GetY()<0) {
        set_life(false);
        return ;
    }
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                get_world()->IncreaseScore(20);
                if((i)->get_hp()>=50)
                    i->set_hp(i->get_hp()-100);
                else
                    (i)->set_hp(-50);
                return ;
            }
            break;
        }
    }
    MoveTo(GetX(),GetY()-2);
    for(auto i:get_world()->get_ob()) {
        if((i)->gettype()==1) {
            if((i)->jud_life()&&track(GetX(),(i)->GetX(),GetY(),(i)->GetY(),GetSize(),(i)->GetSize())) {
                set_life(false);
                get_world()->IncreaseScore(20);
                if((i)->get_hp()>=50)
                    i->set_hp(i->get_hp()-100);
                else
                    (i)->set_hp(-50);
                return ;
            }
            break;
        }
    }
}