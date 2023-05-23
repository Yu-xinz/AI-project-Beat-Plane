#include "GameObjects.h"
#include <cmath>
#include <ctime>
#ifndef M_PI
#define M_PI 3.1415926
#endif
#define MAX_DISTANCE 1082.0
const double SPEED = 8.0;
const time_t now = time(0);

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
Dawnbreaker::Dawnbreaker(GameWorld* wrd):GameObject(IMGID_DAWNBREAKER,300,300,0,0,1.0,wrd){
    hp=100;
    energy=10;
    num_met=0;
    level=0;
    set_life(true);
    settype(1);
}

void Dawnbreaker::Update(){
    writeTrainingData(get_world());
    Astar(get_world(), 3);
    if((GetX()+x_move*4)>=0&&(GetX()+x_move*4)<=(WINDOW_WIDTH-1))
        MoveTo(GetX()+x_move*SPEED,GetY());
    if((GetY()+y_move*4)>=50&&(GetY()+y_move*4)<=(WINDOW_HEIGHT-1))
        MoveTo(GetX(),GetY()+y_move*SPEED); 
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
bool Dawnbreaker::jud_meteor(GameWorld *world, bool fire2){
    auto objects = world->get_ob();
    for (auto each : objects){
        if (
            each->gettype() == 4
            || each->gettype() == 5
            || each->gettype() == 6 
            || each->gettype() == 7
        )
            if (num_met > 0 && track(
                each->GetX(), GetX(), each->GetX(), GetY(), 
                2 * each->GetSize(), 2 * GetSize()
            ))
            {
                num_met--;
                return true;
            }
    }
    return false;
}
int Dawnbreaker::get_level(){
    return level;
}
void Dawnbreaker::add_level(){level++;}
int Dawnbreaker::get_meteor(){return num_met;}
void Dawnbreaker::add_meteor(){num_met++;}
double Dawnbreaker::get_hp(){return hp;}
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
/// @brief An astar search to find the path with maximum value in `depth` steps
/// @param world a pointer to the gameworld
/// @param depth >= 1, the depth of astar search 
void Dawnbreaker::Astar(GameWorld *world, int depth){
    /*double result=evaluatefunction();
    if(result > get_world()->GetScore()){
        targetforalpha();
    }
    else{
        dodgebullet();
    }
    return;*/
    double decay = 0.9;
    std::vector<std::pair<double, State>> base_pq;
    auto cmp = [](
        std::pair<double, State> l, 
        std::pair<double, State> r
        ) 
        { 
            //std::cout << l.first << " " << r.first << std::endl;
            return (l.first) < (r.first); 
        };
    std::priority_queue pq(base_pq.begin(), base_pq.end(), cmp);

    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            State state{i, j, GetX() + i*SPEED, GetY() + j*SPEED, get_hp(), 1};
            double eval = getEvaluation(state);
            if (eval < -9999999)
                continue;
            //std::cout << "eval = " << eval << " i " << i << " j " << j << std::endl;
            std::pair<double, State> temp(eval, state);
            //< do not act when nothing get considered (eval == 0)
            if (
                GetX() + i*SPEED > WINDOW_WIDTH - 2*SPEED
                || GetX() + i*SPEED < 2*SPEED
                || GetY() + j*SPEED > WINDOW_HEIGHT - 2*SPEED
                || GetY() + j*SPEED < 2*SPEED
            )
                continue;
            pq.push(temp);
            //std::cout << "eval = " << eval << std::endl;
        }
    }
    x_move=0;
    y_move=0;

    while (!pq.empty()){
        State top = pq.top().second;
        auto top_eval = pq.top().first;
        pq.pop();
        if (top.depth == depth)
        {
            //std::cout << x_move << " " << y_move << std::endl;
            x_move = top.x_origin;
            y_move = top.y_origin;
            //std::cout << "Utimate eval: " << top_eval 
            //    << " x,y: " << GetX() + x_move*SPEED << " " << GetY() + y_move*SPEED 
            //    << std::endl
            //    << std::endl; 
            break;
        }
        if (top.depth < depth)
        {
            for(int i=-1;i<=1;i++){
                for(int j=-1;j<=1;j++){
                    State state{
                        top.x_origin, top.y_origin, 
                        top.x_pos + i*SPEED, top.y_pos + j*SPEED,
                        get_hp(), top.depth+1
                    };
                    if (
                        top.x_pos + i*SPEED > WINDOW_WIDTH - 2*SPEED
                        || top.x_pos + i*SPEED < 2*SPEED
                        || top.y_pos + j*SPEED > WINDOW_HEIGHT - 2*SPEED
                        || top.y_pos + j*SPEED < 2*SPEED
                    )
                        continue;
                    if(
                        evaluateBulletDirection(world, state) == 0
                        && evaluateEnemyDirection(world, state) == 0
                        && evaluateEnemyDistance(world, 600, state) == 0
                        && evaluateGoodieDistance(world, state) == 0
                    )
                        continue;
                    auto eval = getEvaluation(state) + top_eval;
                    if (eval < -9999999)
                        continue;
                    eval *= decay;
                    std::pair<double, State> temp(eval, state);
                    pq.push(temp);
                    // std::cout << "eval = " << eval << " i " << i << " j " << j << " origin " << top.y_origin << std::endl;
                }
            }
        }
    }
    return;
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
    double eval = 0;
    double tmp;
    double weightByDistance;
    auto objects = world->get_ob();
    auto x_pos = state.x_pos;
    auto y_pos = state.y_pos;
    double depth = state.depth;
    int cnt = 0;
    for (auto each : objects)
    {
        if (each->gettype() != 7) /**< not a bullet*/
            continue;
        double bulletX = each->GetX();
        double bulletY = each->GetY(); 
        if (track(
            bulletX, x_pos, bulletY, y_pos, 
            (1+ 0.3 * depth) * each->GetSize(), (1 + 0.3 * depth) * GetSize()
        ))
        {
            eval = -999999.0;
            break;
        }
        double eucDis = pow((each->GetX() - x_pos)*(each->GetX() - x_pos) + (each->GetY() - y_pos)*(each->GetY() - y_pos), 0.5);
        double dot;
        if (eucDis > 0.25 * WINDOW_HEIGHT)
        {
            dot = 0.75;
            weightByDistance = 1.0;
        }
        else {
            auto vecDisX = (x_pos - each->GetX()) / (1+eucDis); 
            auto vecDisY = (y_pos - each->GetY()) / (1+eucDis);
            double bulletDirectionX = cos((90 - each->GetDirection()) * M_PI / 180);
            double bulletDirectionY = sin((90 - each->GetDirection()) * M_PI / 180);
            //std::cout << "Bullet: (" << bulletDirectionX << "," << bulletDirectionY << ")" << "  Position: (" << each->GetX() << "," << each->GetY() << ")" << " Direction: " << each->GetDirection() << std::endl << std::endl;
            dot = (vecDisX * bulletDirectionX) + (vecDisY * bulletDirectionY);
            weightByDistance = 1.0 + ((0.25 * WINDOW_HEIGHT) - eucDis)/(0.25 * WINDOW_HEIGHT);
            //std::cout << "Dot: " << dot << "  Position: (" << x_pos << "," << y_pos << ")" << " vec: " <<vecDisX << ","<< vecDisY<< std::endl << std::endl;
        }
        //eval += std::max(0.3 * WINDOW_HEIGHT, eucDis) - MAX_DISTANCE;
        //eval += -1000000 / std::max(0.3 * WINDOW_HEIGHT, eucDis); 
        eval += (-(1000 * dot) - 1000) * weightByDistance;
        cnt++;
    }   
    // if(eval)    std::cout << "Eval: " << eval << std::endl;
    return eval;
}

/// @brief 
/// @param world 
/// @param state 
/// @return evaluation
double Dawnbreaker::evaluateEnemyDirection(GameWorld *world, State state)
{
    double eval = 0.0;
    double weightByDistance;
    auto objects = world->get_ob();
    auto x_pos = state.x_pos;
    auto y_pos = state.y_pos;
    int cnt = 0;
    for (auto each : objects)
    {
        
        if (each->gettype() != 4 && each->gettype() != 5 && each->gettype() != 6) /**< not a bullet*/
            continue;
        auto bulletX = each->GetX();
        auto bulletY = each->GetY(); 
        if (track(
            bulletX, x_pos, bulletY, y_pos, 
            (1 * state.depth) * each->GetSize(), (1 * state.depth)* GetSize()
        ))
        {
            eval = -999999.0;
            break;
        }

        double eucDis = pow((bulletX - x_pos)*(bulletX- x_pos) + (bulletY - y_pos)*(bulletY - y_pos), 0.5);
        double dot;
        if (eucDis > 0.4 * WINDOW_HEIGHT)
        {
            dot = 0.75; //<maximum punishment
            weightByDistance = 1.0;
        }
        else {
            auto vecDisX = (x_pos - each->GetX()) / (1+eucDis); 
            auto vecDisY = (y_pos - each->GetY()) / (1+eucDis);
            auto bulletDirectionX = cos((90 - each->GetDirection()) * M_PI / 180);
            auto bulletDirectionY = sin((90 - each->GetDirection()) * M_PI / 180);
            dot = vecDisX * bulletDirectionX + vecDisY * bulletDirectionY;
            weightByDistance = 1.0 + ((0.4 * WINDOW_HEIGHT) - eucDis)/(0.4 * WINDOW_HEIGHT);
        }
        //eval += 100 * (std::max(0.3 * WINDOW_HEIGHT, eucDis) - MAX_DISTANCE);
        //eval += -200000 / std::max(0.3 * WINDOW_HEIGHT, eucDis); 
        weightByDistance = 1.0;
        eval += (-(1000 * dot) - 1000)*weightByDistance;
        //std::cout << "Dot: " << eval << "  Position: (" << vecDisX << "," << vecDisY << ")" << std::endl;
        cnt++;
    }   
    return eval;
}

/// @brief Get an *WEIGHTED* evaluation based on the X distances between
/// @param world, threshold
/// @return 
double Dawnbreaker::evaluateEnemyDistance(GameWorld *world, double threshold, State state)
{
    double eval = 0;
    double eval_tmp = 0;
    auto objects = world->get_ob();
    auto x_pos = state.x_pos;
    auto y_pos = state.y_pos;
    double weightByDistance;
    int cnt = 0;
    for (auto each : objects)
    {
        if (each->gettype() != 4  & each->gettype() != 6) //< not an enemy
            continue;
        auto bulletX = each->GetX();
        auto bulletY = each->GetY(); 
        double eucDis = pow((bulletX - x_pos)*(bulletX- x_pos) + (bulletY - y_pos)*(bulletY - y_pos), 0.5);
        if (eucDis < 0.35 * WINDOW_HEIGHT)
        {
            weightByDistance = -1;
        }
        else
        {
            weightByDistance = 1.0 + (eucDis)/(WINDOW_HEIGHT);
        }
        eval_tmp =  weightByDistance * 100000/(1 + abs(each->GetX() - x_pos));
        eval = eval > eval_tmp ? eval: eval_tmp;
        cnt++;
    }   
    if (cnt) eval += -1 * (WINDOW_WIDTH)/(1 + (0.5 * WINDOW_WIDTH - abs(0.5 * WINDOW_WIDTH - x_pos)));
    return eval;
}

/// @brief block the invalid actions when Dawnbreaker is on the border
/// @param world 
/// @param state 
/// @return 
double Dawnbreaker::evaluateBorder(GameWorld *world, State state)
{
    auto x_pos = state.x_pos;
    auto y_pos = state.y_pos;
    if (x_pos < 4* SPEED && state.x_origin <= 0)
        return -99999999;
    if (WINDOW_WIDTH - x_pos < 4 * SPEED && state.x_origin >= 0)
        return -99999999;
    if (y_pos < 4 *  SPEED && state.y_origin <= 0)
        return -99999999;
    if (WINDOW_HEIGHT - y_pos < 4 * SPEED && state.y_origin >= 0)
        return -99999999;
    return 0.0;
}

double Dawnbreaker::evaluateMove(State state)
{
    if (state.x_origin != 0 || state.y_origin != 0)
        return -1.0;
    return 0.0;
}

double Dawnbreaker::evaluatePosition(State state)
{
    auto x_dist = state.x_pos > 0.5 * WINDOW_WIDTH? 
                    WINDOW_WIDTH - state.x_pos:
                    state.x_pos;
    auto eval = 
        - 10000000 / (1 + (WINDOW_HEIGHT - state.y_pos) * (WINDOW_HEIGHT - state.y_pos))
        - 10000 / x_dist * x_dist;
    return eval;
}

double Dawnbreaker::evaluateGoodieDistance(GameWorld *world, State state)
{
    double eval = 0;
    double eval_tmp = 0;
    auto objects = world->get_ob();
    auto x_pos = state.x_pos;
    auto y_pos = state.y_pos;
    double weightByDistance;
    int cnt = 0;
    for (auto each : objects)
    {
        if (each->gettype() != 8 & each->gettype() != 9 & each->gettype() != 12) //< not an enemy
            continue;
        eval_tmp = 1000000/(abs(each->GetY() - y_pos) + abs(each->GetX() - x_pos));
        eval = eval > eval_tmp? eval: eval_tmp;
    }
    return eval;
}
/// @brief 
/// @return retval:double
double Dawnbreaker::getEvaluation(State state)
{
    auto world = get_world();
    auto bullet = evaluateBulletDirection(world, state); 
    auto enemy1 = evaluateEnemyDirection(world, state);
    auto enemy2 = evaluateEnemyDistance(world, 600, state);
    auto border = evaluateBorder(world, state);
    auto move = evaluateMove(state);
    auto position = evaluatePosition(state);
    auto goodie = evaluateGoodieDistance(world, state);
    auto retval = 100 * bullet
                + 10 * enemy1
                + 1 * enemy2
                + 10 * border
                + 10 * move
                + 3 * position
                + 2000 * goodie;

    
    //std::cout << "| "   << bullet 
    //            << " | "<< enemy1
    //            << " | "<< enemy2
    //            << " | "<< border
    //            << " | "<< move
    //            << " | "<< position
    //            << " | "<< goodie
    //            <<std::endl;
    
    /*
    auto retval = 10 * evaluateBulletDirection(world, state) 
                + 0.1 * evaluateEnemyDistance(world, 600, state)
                + 1 * evaluateBorder(world, state);*/
    // if (abs(retval) > 0.00001)
    // std::cout << "Eval: " << retval << "  Position: (" << state.x_pos << "," << state.y_pos << ")" << std::endl;
    return retval;
}

bool Dawnbreaker::writeTrainingData(GameWorld *world)
{
    Json::FastWriter writer;
    Json::Value state;

    Json::Value move;
    move["x"] = x_move;
    move["y"] = y_move;
    state["move"] = move;

    Json::Value position;
    position["x"] = GetY();
    position["y"] = GetY();
    state["position"] = position;

    Json::Value HP = get_hp();
    state["hp"] = HP;

    Json::Value score = world->GetScore();
    state["score"] = score;

    Json::Value level = world->GetLevel();
    state["level"] = get_level();

    Json::Value objects_array;
    Json::Value objectValue;
    auto objects = world->get_ob();
    int cnt = 0;
    for (auto each: objects)
    {
        if (
            each->gettype() == 4
            || each->gettype() == 5
            || each->gettype() == 6
            || each->gettype() == 7
            || each->gettype() == 8
            || each->gettype() == 9
            || each->gettype() == 12)
        {
            objectValue[0] = each->gettype();
            objectValue[1] = each->GetX();
            objectValue[2] = each->GetY();
            objects_array[cnt] = objectValue;
            cnt++;   
        }
    } 
    state["objects"] = objects_array;

    std::string json_file = writer.write(state);
    std::ofstream outfile;
    outfile.open("../../../data/" + std::to_string(now) +".json", std::ios::app);
    outfile << json_file;
    outfile << ",";
    outfile.close();
    return true;
}

State Dawnbreaker::stateInit(GameWorld *world)
{
    ObjectList objects;
    auto objects = world->get_obs();
    for (auto each: objects)
    {
	if (
            each->gettype() == 4
	    || each -> gettype() == 5
	    || each -> gettype() == 6
	    || each -> gettype() == 7
	    || each -> gettype() == 8
	    || each -> gettype() == 9
	    || each -> gettype() == 12
	)
        ObjectStatus status = {
            each->gettype();
	    each->GetX();
	    each->GetY();
	}
	objects.push_back(status); 
    }
    int x_origin = 0;
    int y_origin = 0;
    double x_pos = GetX();
    double y_pos = GetY();
    double health = gethp();
    int depth = 0;
    State ret = {
       x_origin, y_origin,
       x_pos, y_pos,
       health, depth,
       objects
    }
    return ret;
}

bool Dawnbreaker::stateUpdate(GameWorld *world, State *state)
{
    ObjectList objects;
    auto objects = state -> objects;
    for (auto each: objects)
    {
	if (
            each->type == 4
	    || each->type  == 5
	    || each->type  == 6
	    || each->type  == 7
	    || each->type  == 8
	    || each->type  == 9
	    || each->type  == 12
	)
	{
            ObjectStatus status = {
                each->type;
	        each->x_pos;
	        each->y_pos;
	    }
	    objects.push_back(status);
	}
    }
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
                        get_world()->IncreaseScore(50);
                        //get_world()->IncreaseScore(1);
                    else if(i->gettype()==5)
                        get_world()->IncreaseScore(100);
                        //get_world()->IncreaseScore(1);
                    else if(i->gettype()==6)
                        get_world()->IncreaseScore(200);
                        //get_world()->IncreaseScore(1);
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
                        get_world()->IncreaseScore(50);
                        //get_world()->IncreaseScore(1);
                    else if(i->gettype()==5)
                        get_world()->IncreaseScore(100);
                        //get_world()->IncreaseScore(1);
                    else if(i->gettype()==6)
                        get_world()->IncreaseScore(200);
                        //get_world()->IncreaseScore(1);
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
double Alphatron::get_hp(){return hp;}
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
            get_world()->IncreaseScore(50);
            //get_world()->IncreaseScore(1);
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
            get_world()->IncreaseScore(50);
            //get_world()->IncreaseScore(1);
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
double Sigmatron::get_hp(){return hp;}
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
            get_world()->IncreaseScore(100);
            //get_world()->IncreaseScore(1);
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
            get_world()->IncreaseScore(100);
            //get_world()->IncreaseScore(1);
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
double Omegatron::get_hp(){return hp;}
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
            get_world()->IncreaseScore(200);
            //get_world()->IncreaseScore(1);
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
            get_world()->IncreaseScore(200);
            //get_world()->IncreaseScore(1);
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
