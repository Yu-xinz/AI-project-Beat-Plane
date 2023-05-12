#include "GameObjects.h"
#include <cmath>

GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* wrd):ObjectBase(imageID,x,y,direction,layer,size){
    world=wrd;
}
void GameObject::set_life(bool lf){life=lf;}
bool GameObject::jud_life(){return life;}
int GameObject::gettype(){return type;}
void GameObject::settype(int ty){type=ty;}
GameWorld* GameObject::get_world(){return world;}
bool GameObject::track(int x1,int x2,int y1,int y2,double s1,double s2) {
    double d=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    if(d<30.0*(s1+s2))
        return true;
    else
        return false;
}

//Dawnbreaker
Dawnbreaker::Dawnbreaker(GameWorld* wrd):GameObject(IMGID_DAWNBREAKER,300,100,0,0,1.0,wrd){
    hp=100;
    energy=10;
    num_met=0;
    level=0;
    set_life(true);
    settype(1);
}
void Dawnbreaker::Update(){
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
        return ;
    if(GetY()>=WINDOW_HEIGHT){
        set_life(false);
        return ;
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
            GameObject* e=new Explosion(GetX(),GetY(),get_world());
            get_world()->push(e);
            get_world()->IncreaseScore(50);
            return ;
        }
    }
    for(auto i:get_world()->get_ob())
        if(i->gettype()==1){
            if(abs(GetX()-i->GetX())<=10&&energy>=25&&randInt(1,100)<=25) {
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
            GameObject* e=new Explosion(GetX(),GetY(),get_world());
            get_world()->push(e);
            get_world()->IncreaseScore(50);
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
            get_world()->IncreaseScore(100);
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
            get_world()->IncreaseScore(200);
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