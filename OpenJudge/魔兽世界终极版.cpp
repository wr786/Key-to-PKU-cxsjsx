#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cassert>
#include<vector>
#include<cmath>
using namespace std;
// 全局变量
int INIT_HEALTH, CITY_NUM, LOYALTY_COST, TIME_LIMIT, ARROW_ATK;

class Ticker {
private:
    int curTime;
    int curEvent;
public:
    Ticker(): curTime(0), curEvent(1) {}
    void init_time() {curTime = 0; curEvent = 1;}
    bool nxt_event() {
        if(curEvent < 10) {
            curEvent++;
            return true;
        } else {
            curEvent = 1;
            nxt_minute();
            return false;
        }
    } //// 返回false的时候，停止遍历
    void nxt_minute() {curTime++;}
    int get_time() {
        int ret = curTime * 60;
        switch(curEvent) {
            case 1: ret += 0; break;
            case 2: ret += 5; break;
            case 3: ret += 10; break;
            case 4: ret += 20; break;
            case 5: ret += 30; break;
            case 6: ret += 35; break;
            case 7: ret += 38; break;
            case 8: ret += 40; break;
            case 9: ret += 50; break;
            case 10: ret += 55; break;
        }
        return ret;
    }
    void print_time() {
        printf("%03d:", curTime);
        switch(curEvent) {
            case 1: printf("00 "); break;
            case 2: printf("05 "); break;
            case 3: printf("10 "); break;
            case 4: printf("20 "); break;
            case 5: printf("30 "); break;
            case 6: printf("35 "); break;
            case 7: printf("38 "); break;
            case 8: printf("40 "); break;
            case 9: printf("50 "); break;
            case 10: printf("55 "); break;
        }
    } //* 输出形如"001:55 "
//    string get_print_time() {
//        string ret = string(itoa(curTime));
//        while(ret.size() < 3) ret = "0" + ret;
//        switch(curEvent) {
//            case 1: return ret + ":00 ";
//            case 2: return ret + ":05 ";
//            case 3: return ret + ":10 ";
//            case 4: return ret + ":20 ";
//            case 5: return ret + ":30 ";
//            case 6: return ret + ":35 ";
//            case 7: return ret + ":38 ";
//            case 8: return ret + ":40 ";
//            case 9: return ret + ":50 ";
//            case 10: return ret + ":55 ";
//        }
//    }
} globalTicker;

class Weapon; // 提前声明
class Sword;
class Arrow;
class Bomb;
class Warrior; // 提前声明
class HeadQuarter{
protected:
    int curTypeIdx; // 现在要制造哪个
    string color;
public:
    int typeNum[5]; // 对应着5种类型存在了多少个
    int health;
    int totalIdx;
    bool canGenerate; // 能否继续生产
    HeadQuarter(const char* _color):
            canGenerate(true), health(INIT_HEALTH), color(string(_color)), totalIdx(0) {
        fill(typeNum, typeNum+5, 0);
        if(color == "red") curTypeIdx = 2; // initialize
        else curTypeIdx = 3;
    }
    void nxtTypeIdx() {
        if(color == "red") {
            switch (curTypeIdx) {
                case 0: curTypeIdx=2;break;
                case 1: curTypeIdx=0;break;
                case 2: curTypeIdx=3;break;
                case 3: curTypeIdx=4;break;
                case 4: curTypeIdx=1;break;
            }
        } else {
            switch (curTypeIdx) {
                case 0: curTypeIdx=1;break;
                case 1: curTypeIdx=2;break;
                case 2: curTypeIdx=4;break;
                case 3: curTypeIdx=0;break;
                case 4: curTypeIdx=3;break;
            }
        }
    }
    Warrior* generateWarrior();
    Warrior* tryGenerateNxt();
    string getColor() {return color;}
    void print_health_info() {
        printf("%d elements in %s headquarter\n", health, color.c_str());
    }
    friend class Warrior;
} RED("red"), BLUE("blue");

//! 默认type顺序是dragon、ninja、iceman、lion、wolf
//                 0       1      2      3     4
class Warrior {
protected:
    int typeIdx;
    int health;
    int attack;
    HeadQuarter* belong;
    int ID; // 在所属阵营里的编号
    // 因为终极版之中每种武器最多只有一个，所以这样写
public:
    Sword* sword;
    Arrow* arrow;
    Bomb* bomb;
    bool killed_by_arrow;
//    Weapon_List weaponList;
    static string Type[5];
    static int initialHealthOf[5];
    static int initialAttackOf[5];
    string get_type() {return Type[typeIdx];}
    void deal_damage(int damage) {health -= damage;};
    bool attack_and_if_has_sword(Warrior* other) {other->deal_damage(attack); return sword != nullptr;}
    bool fightback_and_if_has_sword(Warrior* other) {
        if(typeIdx == 1) return false; // ninja不会反击
        other->deal_damage(attack/2);
        return sword != nullptr;
    }

    bool is_dead() {return health <= 0;}
    void get_bonus(int val=8) {
        if(belong->health >= val) {
            health += val;
            belong->health -= val;
        }
    }
    void giveback_health(int val) {belong->health += val;}
    virtual void add_morale(double delta) {return;}
    virtual double get_morale() {return 786;}
    virtual void loyalty_down(int downVal=LOYALTY_COST) {return;}
    virtual void do_move_cost() = 0;
    virtual int get_loyalty() = 0;
    virtual void print_info() = 0;
    Warrior(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            typeIdx(_tid), health(_h), attack(_a), belong(&_b), ID(_id) {
        sword = nullptr;
        bomb = nullptr;
        arrow = nullptr;
    }
    Warrior(const Warrior& other) {
        typeIdx = other.typeIdx;
        health = other.health;
        attack = other.attack;
        belong = other.belong;
        ID = other.ID;
        killed_by_arrow = false;
    }
    friend class BattleGround;
};
string Warrior::Type[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Warrior::initialHealthOf[5];
int Warrior::initialAttackOf[5];
//! 默认顺序是sword,bomb,arrow; 编号分别是0,1,2
class Weapon {
protected:
    int idx;
    int durability; //* 耐久，用到 0 之后要消失
public:
    int w_attack;
    static string Type[3];
    virtual void cause_weapon_damage(Warrior* self, Warrior* other) = 0;
    Weapon(int _id, int w_atk, int _d):
            idx(_id), w_attack(w_atk), durability(_d) {}
    virtual void delete_weapon_from(Warrior* owner) = 0;
    void durability_down(Warrior* owner) {
        durability--;
        if(durability == 0)
            delete_weapon_from(owner);
        else {
            if(idx == 0) {
                w_attack = w_attack * 8 / 10;
                if(w_attack == 0) delete_weapon_from(owner);
            }
        }
    }
    friend class BattleGround;
    friend class Warrior;
    friend bool cmp1 (Weapon* A , Weapon* B);
    friend bool cmp2 (Weapon* A , Weapon* B);
};
string Weapon::Type[3] = {"sword", "bomb", "arrow"};
class Sword: public Weapon {
public:
    Sword(int _a): Weapon(0, _a * 2 / 10, -1) {} // -1意味着能使用无限次
    Sword(const Sword& other): Weapon(other.idx, other.w_attack, other.durability) {}
    void cause_weapon_damage(Warrior* self, Warrior* other) {
        other->deal_damage(w_attack);
        durability_down(self);
    }
    void delete_weapon_from(Warrior* owner) {
        owner->sword = nullptr;
    }
};
class Bomb: public Weapon { // 新版本实际上是秒杀效果，所以可删去很多行
public:
    Bomb(int _a): Weapon(1, _a * 4 / 10, 1) {}
    Bomb(const Bomb& other): Weapon(other.idx, other.w_attack, other.durability) {}
    void cause_weapon_damage(Warrior* self, Warrior* other) {return;}
    void delete_weapon_from(Warrior* owner) {
        owner->bomb = nullptr;
    }
};
class Arrow: public Weapon {
public:
    Arrow(int _a): Weapon(2, ARROW_ATK, 3) {}
    void cause_weapon_damage(Warrior* self, Warrior* other) {
        other->deal_damage(w_attack);
        durability_down(self);
    }
    void delete_weapon_from(Warrior* owner) {
        owner->arrow = nullptr;
    }
};

inline int _4out5in(double a){
    return (a*2+1)/2;
} // 四舍五入

class Dragon: public Warrior {
private:
    double morale;
public:
    Dragon(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            Warrior(_tid, _h, _a, _b, _id) {
        switch(ID%3) {
            case 0: sword = new Sword(_a); break;
            case 1: bomb = new Bomb(_a); break;
            case 2: arrow = new Arrow(_a); break;
        }
        if(sword!=nullptr && sword->w_attack == 0) sword = nullptr;
        morale = _b.health * 1.0 / (double)_h;
    }
    void do_move_cost() {return;}
    int get_loyalty() {return 1;} // 就是为了方便编写而已，没别的，下同。
    void print_info() {
        globalTicker.print_time();
        printf("%s %s %d born\n", belong->getColor().c_str(), Warrior::Type[typeIdx].c_str(), ID);
        int tmp = _4out5in(morale*100);
        printf("Its morale is %d.%02d\n", tmp/100, tmp%100); // 四舍五入
    }
    void add_morale(double delta) {morale += delta;}
    double get_morale() {return morale;}
    virtual void loyalty_down(int downVal=LOYALTY_COST) {return;}
};
class Ninja: public Warrior {
public:
    Ninja(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            Warrior(_tid, _h, _a, _b, _id) {
        switch(ID%3) {
            case 0: sword = new Sword(_a); break;
            case 1: bomb = new Bomb(_a); break;
            case 2: arrow = new Arrow(_a); break;
        }
        switch((ID+1)%3) {
            case 0: sword = new Sword(_a); break;
            case 1: bomb = new Bomb(_a); break;
            case 2: arrow = new Arrow(_a); break;
        }
        if(sword!=nullptr && sword->w_attack == 0) sword = nullptr;
    }
    virtual void do_move_cost() {return;}
    virtual int get_loyalty() {return 1;} // 就是为了方便编写而已，没别的，下同。
    void print_info() {
        globalTicker.print_time();
        printf("%s %s %d born\n", belong->getColor().c_str(), Warrior::Type[typeIdx].c_str(), ID);
    }
    virtual void add_morale(double delta) {return;}
    virtual double get_morale() {return 786;}
    virtual void loyalty_down(int downVal=LOYALTY_COST) {return;}
};
class Iceman: public Warrior {
private:
    bool paceCnt;
public:
    Iceman(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            Warrior(_tid, _h, _a, _b, _id) {
        switch(ID%3) {
            case 0: sword = new Sword(_a); break;
            case 1: bomb = new Bomb(_a); break;
            case 2: arrow = new Arrow(_a); break;
        }
        if(sword!=nullptr && sword->w_attack == 0) sword = nullptr;
        paceCnt = false;
    }
    void do_move_cost() {
        paceCnt = ! paceCnt;
        if(! paceCnt) {
            attack += 20;
            deal_damage(min(9, health-1));
        }
    }
    virtual int get_loyalty() {return 1;} // 就是为了方便编写而已，没别的，下同。
    void print_info() {
        globalTicker.print_time();
        printf("%s %s %d born\n", belong->getColor().c_str(), Warrior::Type[typeIdx].c_str(), ID);
    }
    virtual void add_morale(double delta) {return;}
    virtual double get_morale() {return 786;}
    virtual void loyalty_down(int downVal=LOYALTY_COST) {return;}
};
class Lion: public Warrior {
private:
    int loyalty;
public:
    Lion(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            Warrior(_tid, _h, _a, _b, _id) {
        loyalty = belong->health;
    }
    void do_move_cost() {return;}
    int get_loyalty() {return loyalty;}
    virtual void add_morale(double delta) {return;}
    virtual double get_morale() {return 786;}
    void loyalty_down(int downVal=LOYALTY_COST) {loyalty -= downVal;}
    void print_info() {
        globalTicker.print_time();
        printf("%s %s %d born\n", belong->getColor().c_str(), Warrior::Type[typeIdx].c_str(), ID);
        printf("Its loyalty is %d\n", loyalty);
    }
};
class Wolf: public Warrior {
public:
    Wolf(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            Warrior(_tid, _h, _a, _b, _id) {}
    virtual void do_move_cost() {return;}
    virtual int get_loyalty() {return 1;} // 就是为了方便编写而已，没别的，下同。
    void print_info() {
        globalTicker.print_time();
        printf("%s %s %d born\n", belong->getColor().c_str(), Warrior::Type[typeIdx].c_str(), ID);
    }
    virtual void add_morale(double delta) {return;}
    virtual double get_morale() {return 786;}
    virtual void loyalty_down(int downVal=LOYALTY_COST) {return;}
};

Warrior* HeadQuarter::tryGenerateNxt() {
//    int archive = curTypeIdx;
    if(health < Warrior::initialHealthOf[curTypeIdx]) {
//        canGenerate = false;
        return nullptr;
    } // health >= typeCost[curTypeIdx]
    return generateWarrior();
}
Warrior* HeadQuarter::generateWarrior() {
    totalIdx++;
    typeNum[curTypeIdx]++;
    health -= Warrior::initialHealthOf[curTypeIdx];
    Warrior* ret = nullptr;
    switch(curTypeIdx) {
        case 0:
            ret = new Dragon(curTypeIdx, Warrior::initialHealthOf[curTypeIdx], Warrior::initialAttackOf[curTypeIdx], *this, totalIdx);
            break;
        case 1:
            ret = new Ninja(curTypeIdx, Warrior::initialHealthOf[curTypeIdx], Warrior::initialAttackOf[curTypeIdx], *this, totalIdx);
            break;
        case 2:
            ret = new Iceman(curTypeIdx, Warrior::initialHealthOf[curTypeIdx], Warrior::initialAttackOf[curTypeIdx], *this, totalIdx);
            break;
        case 3:
            ret = new Lion(curTypeIdx, Warrior::initialHealthOf[curTypeIdx], Warrior::initialAttackOf[curTypeIdx], *this, totalIdx);
            break;
        case 4:
            ret = new Wolf(curTypeIdx, Warrior::initialHealthOf[curTypeIdx], Warrior::initialAttackOf[curTypeIdx], *this, totalIdx);
            break;
        default:
            printf("[ERROR] Type越界!\n");
            assert(1 < 0); // 为了跳出程序用
            break;
    }
    assert(ret != nullptr);
    ret->print_info(); // 报告生成
    nxtTypeIdx();
    return ret;
}
void do_attack(Warrior* from, Warrior* to) {
    if(from->attack_and_if_has_sword(to)) {
        from->sword->cause_weapon_damage(from, to);
    }
    if(!to->is_dead()) {
        if(to->fightback_and_if_has_sword(from)) {
            to->sword->cause_weapon_damage(to, from);
        }
    }
}

// 注意到一个城市中最多只有两个不同阵营的武士
// 当其中一个武士不存在时，记为nullptr即可。
class BattleGround {
private:
    // 懒得再写一个City类了，就这样吧。
    Warrior* redSide[22]; // 记录从0~N+1城市中现在的红方/蓝方
    Warrior* blueSide[22];
    Warrior* already_red;
    Warrior* already_blue;
    int health_hold[22]; // 存储的生命元
    int flag[22]; // 0代表无旗帜，1代表红旗，2代表蓝旗
    int last_win[22]; // 0代表平局，1代表红赢，2代表蓝赢
    int mem_red[22]; // 记录lion战前的生命值
    int mem_blue[22];
    int over_cnt_red;
    int over_cnt_blue;
    int giveback_red; // lazyTag
    int giveback_blue;
//    vector<string> cache[22]; // 用来缓存要输出的字符串
public:
    BattleGround() {init();}
    void init() { // 初始化
        for(int i=0; i<22; i++) {
            redSide[i] = blueSide[i] = nullptr;
            flag[i] = last_win[i] = health_hold[i] = 0;
        }
        over_cnt_blue = over_cnt_red = 0;
        giveback_blue = giveback_red = 0;
        already_blue = already_red = 0;
    }
    int judge_first_attack(int idx) {
        if(flag[idx]) return flag[idx];
        return idx % 2? 1:2;
    } // 1 red , 2 blue
    void insert_warrior() {
        redSide[0] = RED.tryGenerateNxt();
        // 返回为nullptr也正确
        blueSide[CITY_NUM+1] = BLUE.tryGenerateNxt();
    }
    void flee_lion() {
        //* 已经到达敌人司令部的lion不会逃跑。lion在己方司令部可能逃跑。
        for(int i=0; i<=CITY_NUM; i++) {
            if(redSide[i] != nullptr && redSide[i]->typeIdx == 3 && redSide[i]->get_loyalty() <= 0) {
                globalTicker.print_time();
                printf("red lion %d ran away\n", redSide[i]->ID); // 懒得编写虚函数了
                redSide[i] = nullptr;
            }
        }
        for(int i=CITY_NUM+1; i; i--) {
            if(blueSide[i] != nullptr && blueSide[i]->typeIdx == 3 && blueSide[i]->get_loyalty() <= 0) {
                globalTicker.print_time();
                printf("blue lion %d ran away\n", blueSide[i]->ID); // 懒得编写虚函数了
                blueSide[i] = nullptr;
            }
        }
    }
    void do_march() { // 从西向东依次输出信息。
        for(int i=CITY_NUM; i>=0; i--) {
            if(i == CITY_NUM && redSide[i+1] != nullptr) already_red = redSide[i+1];
            redSide[i+1] = redSide[i]; // 右移
            if(redSide[i+1] != nullptr) {
                redSide[i+1]->do_move_cost();
                if(redSide[i+1]->is_dead()) { // 移动过程中死亡
                    redSide[i+1] = nullptr; // 删除之
                }
            }
        }
        redSide[0] = nullptr;
        for(int i=1; i<=CITY_NUM+1; i++) {
            if(i == 1 && blueSide[i-1] != nullptr) already_blue = blueSide[i-1];
            blueSide[i-1] = blueSide[i]; // 左移
            if(blueSide[i-1] != nullptr) {
                blueSide[i-1]->do_move_cost();
                if(blueSide[i-1]->is_dead()) {
                    blueSide[i-1] = nullptr;
                }
            }
        }
        blueSide[CITY_NUM+1] = nullptr;
        // 先特判红方司令部
        if(blueSide[0] != nullptr) {
            globalTicker.print_time();
            printf("blue %s %d reached red headquarter with %d elements and force %d\n",
                   blueSide[0]->get_type().c_str(),
                   blueSide[0]->ID,
                   blueSide[0]->health,
                   blueSide[0]->attack);
            over_cnt_red++;
            if(over_cnt_red == 2) {
                globalTicker.print_time();
                printf("red headquarter was taken\n");
            }
        }
        // 再输出普通城市
        for(int i=1; i<=CITY_NUM; i++) {
            if(redSide[i] != nullptr) {
                globalTicker.print_time();
                printf("red %s %d marched to city %d with %d elements and force %d\n",
                       redSide[i]->get_type().c_str(), redSide[i]->ID, i, redSide[i]->health, redSide[i]->attack);
            }
            if(blueSide[i] != nullptr) {
                globalTicker.print_time();
                printf("blue %s %d marched to city %d with %d elements and force %d\n",
                       blueSide[i]->get_type().c_str(), blueSide[i]->ID, i, blueSide[i]->health, blueSide[i]->attack);
            }
        }
        // 再特判蓝方司令部
        if(redSide[CITY_NUM+1] != nullptr) {
            globalTicker.print_time();
            printf("red %s %d reached blue headquarter with %d elements and force %d\n",
                   redSide[CITY_NUM+1]->get_type().c_str(),
                   redSide[CITY_NUM+1]->ID,
                   redSide[CITY_NUM+1]->health,
                   redSide[CITY_NUM+1]->attack);
            over_cnt_blue++;
            if(over_cnt_blue == 2) {
                globalTicker.print_time();
                printf("blue headquarter was taken\n");
            }
        }
    }
    void generate_health() {
        for(int i=1; i<=CITY_NUM; i++)
            health_hold[i] += 10;
    } // 城市生成生命元
    void grab_health() {
        for(int i=1; i<=CITY_NUM; i++) {
            if(redSide[i] != nullptr && blueSide[i] == nullptr) {
                redSide[i]->giveback_health(health_hold[i]);
                globalTicker.print_time();
                printf("red %s %d earned %d elements for his headquarter\n",
                       redSide[i]->get_type().c_str(), redSide[i]->ID, health_hold[i]);
                health_hold[i] = 0;
            } else if(blueSide[i] != nullptr && redSide[i] == nullptr) {
                blueSide[i]->giveback_health(health_hold[i]);
                globalTicker.print_time();
                printf("blue %s %d earned %d elements for his headquarter\n",
                       blueSide[i]->get_type().c_str(), blueSide[i]->ID, health_hold[i]);
                health_hold[i] = 0;
            }
        }
    }
    void shoot_the_arrow() {
        for(int i=0; i<=1; i++) {
            if(redSide[i] != nullptr && blueSide[i+1] != nullptr) {
                if(redSide[i]->arrow != nullptr) {
                    redSide[i]->arrow->cause_weapon_damage(redSide[i], blueSide[i+1]);
                    globalTicker.print_time();
                    printf("red %s %d shot", redSide[i]->get_type().c_str(), redSide[i]->ID);
                    assert(blueSide[i+1] != nullptr);
                    if(blueSide[i+1]->is_dead()) {
                        printf(" and killed blue %s %d\n", blueSide[i+1]->get_type().c_str(), blueSide[i+1]->ID);
                        blueSide[i+1]->killed_by_arrow = true;
                    } else printf("\n");
//                    if(redSide[i+1] == nullptr) {
//                        if(blueSide[i+1]->is_dead())
//                            blueSide[i+1] = nullptr; // 处理死亡时间
//                    }
                }
            }
        }
        for(int i=2; i<CITY_NUM; i++) { // red
            if(redSide[i] != nullptr && blueSide[i+1] != nullptr) {
                if(redSide[i]->arrow != nullptr) {
                    redSide[i]->arrow->cause_weapon_damage(redSide[i], blueSide[i+1]);
                    globalTicker.print_time();
                    printf("red %s %d shot", redSide[i]->get_type().c_str(), redSide[i]->ID);
                    assert(blueSide[i+1] != nullptr);
                    if(blueSide[i+1]->is_dead()) {
                        printf(" and killed blue %s %d\n", blueSide[i+1]->get_type().c_str(), blueSide[i+1]->ID);
                        blueSide[i+1]->killed_by_arrow = true;
                    } else printf("\n");
//                    if(redSide[i+1] == nullptr) {
//                        if(blueSide[i+1]->is_dead())
//                            blueSide[i+1] = nullptr; // 处理死亡时间
//                    }
                }
            }
            if(redSide[i-1] != nullptr && blueSide[i] != nullptr) {
                if(blueSide[i]->arrow != nullptr) {
                    blueSide[i]->arrow->cause_weapon_damage(blueSide[i], redSide[i-1]);
                    globalTicker.print_time();
                    printf("blue %s %d shot", blueSide[i]->get_type().c_str(), blueSide[i]->ID);
                    assert(redSide[i-1] != nullptr);
                    if(redSide[i-1]->is_dead()) {
                        printf(" and killed red %s %d\n", redSide[i-1]->get_type().c_str(), redSide[i-1]->ID);
                        redSide[i-1]->killed_by_arrow = true;
                    } else printf("\n");
//                    if(blueSide[i-1] == nullptr) {
//                        if(redSide[i-1]->is_dead())
//                            redSide[i-1] = nullptr; // 处理死亡时间
//                    }
                }
            }
        }
        for(int i=CITY_NUM; i<=CITY_NUM+1; i++) { // blue
            if(redSide[i-1] != nullptr && blueSide[i] != nullptr) {
                if(blueSide[i]->arrow != nullptr) {
                    blueSide[i]->arrow->cause_weapon_damage(blueSide[i], redSide[i-1]);
                    globalTicker.print_time();
                    printf("blue %s %d shot", blueSide[i]->get_type().c_str(), blueSide[i]->ID);
                    assert(redSide[i-1] != nullptr);
                    if(redSide[i-1]->is_dead()) {
                        printf(" and killed red %s %d\n", redSide[i-1]->get_type().c_str(), redSide[i-1]->ID);
                        redSide[i-1]->killed_by_arrow = true;
                    } else printf("\n");
//                    if(blueSide[i-1] == nullptr) {
//                        if(redSide[i-1]->is_dead())
//                            redSide[i-1] = nullptr; // 处理死亡时间
//                    }
                }
            }
        }
        // 可能同时射死对方，所以要这样处理
        for(int i=0; i<=CITY_NUM+1; i++) {
            if(redSide[i] != nullptr && blueSide[i] == nullptr) {
                if(redSide[i]->is_dead()) redSide[i] = nullptr;
            }
            if(blueSide[i] != nullptr && redSide[i] == nullptr) {
                if(blueSide[i]->is_dead()) blueSide[i] = nullptr;
            }
        }
    }
    void boom() {
        for(int i=1; i<=CITY_NUM; i++) {
            if(redSide[i] != nullptr && blueSide[i] != nullptr && !redSide[i]->is_dead() && !blueSide[i]->is_dead()) { // 特判防止arrow死
                bool BOOM = false;
                int tmp_red[3], tmp_blue[3]; // 分别是血、攻、剑攻
                bool isninja_red = false, isninja_blue = false;
                tmp_red[0] = redSide[i]->health, tmp_red[1] = redSide[i]->attack, tmp_red[2] = redSide[i]->sword!=nullptr? redSide[i]->sword->w_attack: 0;
                tmp_blue[0] = blueSide[i]->health, tmp_blue[1] = blueSide[i]->attack, tmp_blue[2] = blueSide[i]->sword!=nullptr?blueSide[i]->sword->w_attack: 0;
                if(redSide[i]->get_type() == "ninja") isninja_red = true;
                if(blueSide[i]->get_type() == "ninja") isninja_blue = true;
                if(judge_first_attack(i) == 1) {
                    tmp_blue[0] -= tmp_red[1] + tmp_red[2];
                    if(!isninja_blue && tmp_blue[0]>0)
                        tmp_red[0] -= tmp_blue[1]/2 + tmp_blue[2];
                }
                else {
                    tmp_red[0] -= tmp_blue[1] + tmp_blue[2];
                    if(!isninja_red && tmp_red[0]>0)
                        tmp_blue[0] -= tmp_red[1]/2 + tmp_red[2];
                }
                if(redSide[i]->bomb!=nullptr && tmp_red[0] <= 0) {
                    globalTicker.print_time();
                    printf("red %s %d used a bomb and killed blue %s %d\n",
                           redSide[i]->get_type().c_str(), redSide[i]->ID,
                           blueSide[i]->get_type().c_str(), blueSide[i]->ID);
                    BOOM = true;
                }
                if(blueSide[i]->bomb!=nullptr && tmp_blue[0] <= 0) {
                    if(!BOOM) {
                        globalTicker.print_time();
                        printf("blue %s %d used a bomb and killed red %s %d\n",
                               blueSide[i]->get_type().c_str(), blueSide[i]->ID,
                               redSide[i]->get_type().c_str(), redSide[i]->ID);
                    }
                    BOOM = true;
                }
                if(BOOM) redSide[i] = blueSide[i] = nullptr;
            }
        }
    }
    void perform_attack(int idx) {
        if(judge_first_attack(idx) == 1) {
//            cache[idx].push_back(globalTicker.get_print_time() + "red " + redSide[idx]->get_type() + " " + to_string(redSide[idx]->ID) + " attacked blue " +
//            blueSide[idx]->get_type() + " " + to_string(blueSide[idx]->ID) + " in city " + to_string(idx) + " with " + to_string(redSide[idx]->health) + " elements and force " + to_string(redSide[idx]->attack + "\n"));
            globalTicker.print_time();
            printf("red %s %d attacked blue %s %d in city %d with %d elements and force %d\n",
                   redSide[idx]->get_type().c_str(), redSide[idx]->ID, blueSide[idx]->get_type().c_str(), blueSide[idx]->ID,
                   idx, redSide[idx]->health, redSide[idx]->attack);
            do_attack(redSide[idx], blueSide[idx]);
            if(!blueSide[idx]->is_dead() && blueSide[idx]->get_type() != "ninja") { // 能反击
                globalTicker.print_time();
                printf("blue %s %d fought back against red %s %d in city %d\n",
                       blueSide[idx]->get_type().c_str(), blueSide[idx]->ID, redSide[idx]->get_type().c_str(), redSide[idx]->ID, idx);
            }
        } else {
            globalTicker.print_time();
            printf("blue %s %d attacked red %s %d in city %d with %d elements and force %d\n",
                   blueSide[idx]->get_type().c_str(), blueSide[idx]->ID, redSide[idx]->get_type().c_str(), redSide[idx]->ID,
                   idx, blueSide[idx]->health, blueSide[idx]->attack);
            do_attack(blueSide[idx], redSide[idx]);
            if(!redSide[idx]->is_dead() && redSide[idx]->get_type() != "ninja") {
                globalTicker.print_time();
                printf("red %s %d fought back against blue %s %d in city %d\n",
                       redSide[idx]->get_type().c_str(), redSide[idx]->ID, blueSide[idx]->get_type().c_str(), blueSide[idx]->ID, idx);
            }
        }
    }
    void do_battle() { // 战斗环节
        for(int i=1; i<=CITY_NUM; i++) {
            if(redSide[i] != nullptr && blueSide[i] != nullptr) {
                mem_red[i] = max(redSide[i]->health, 0);
                mem_blue[i] = max(blueSide[i]->health, 0);
                if (!redSide[i]->is_dead() && !blueSide[i]->is_dead()) {
                    perform_attack(i);
                } // 即没有人被arrow射死
                // 判断士气
                if (redSide[i]->get_type() == "dragon") {
                    if (blueSide[i]->is_dead()) redSide[i]->add_morale(0.2);
                    else redSide[i]->add_morale(-0.2);
                }
                if (blueSide[i]->get_type() == "dragon") {
                    if (redSide[i]->is_dead()) blueSide[i]->add_morale(0.2);
                    else blueSide[i]->add_morale(-0.2);
                }
                if (redSide[i]->get_type() == "lion" && !blueSide[i]->is_dead())
                    redSide[i]->loyalty_down();
                if (blueSide[i]->get_type() == "lion" && !redSide[i]->is_dead())
                    blueSide[i]->loyalty_down();
                // 战死
                assert(redSide[i] != nullptr);
                assert(blueSide[i] != nullptr);
                if (redSide[i]->is_dead() && !blueSide[i]->is_dead()) {
                    // blue win
                    if (blueSide[i]->get_type() == "wolf") {
                        if (blueSide[i]->sword == nullptr) blueSide[i]->sword = redSide[i]->sword;
                        if (blueSide[i]->bomb == nullptr) blueSide[i]->bomb = redSide[i]->bomb;
                        if (blueSide[i]->arrow == nullptr) blueSide[i]->arrow = redSide[i]->arrow;
                    }
                    if(!redSide[i]->killed_by_arrow) {
                        globalTicker.print_time();
                        printf("red %s %d was killed in city %d\n", redSide[i]->get_type().c_str(), redSide[i]->ID, i);
                    }
                } else if (blueSide[i]->is_dead() && !redSide[i]->is_dead()) {
                    // red win
                    if (redSide[i]->get_type() == "wolf") {
                        if (redSide[i]->sword == nullptr) redSide[i]->sword = blueSide[i]->sword;
                        if (redSide[i]->bomb == nullptr) redSide[i]->bomb = blueSide[i]->bomb;
                        if (redSide[i]->arrow == nullptr) redSide[i]->arrow = blueSide[i]->arrow;
                    }
                    if(!blueSide[i]->killed_by_arrow) {
                        globalTicker.print_time();
                        printf("blue %s %d was killed in city %d\n", blueSide[i]->get_type().c_str(), blueSide[i]->ID, i);
                    }
                } else {
                    // 平局
//                    last_win[i] = 0;
                    if (redSide[i]->is_dead() && !redSide[i]->killed_by_arrow) {
                        globalTicker.print_time();
                        printf("red %s %d was killed in city %d\n", redSide[i]->get_type().c_str(), redSide[i]->ID, i);
                    }
                    if (blueSide[i]->is_dead() && !blueSide[i]->killed_by_arrow) {
                        globalTicker.print_time();
                        printf("blue %s %d was killed in city %d\n", blueSide[i]->get_type().c_str(), blueSide[i]->ID,
                               i);
                    }
                }
                // 欢呼
                if (redSide[i] != nullptr && blueSide[i] != nullptr && redSide[i]->get_type() == "dragon" &&
                    judge_first_attack(i) == 1 && !redSide[i]->is_dead()) {
                    if (redSide[i]->get_morale() > 0.8) {
                        globalTicker.print_time();
                        printf("red dragon %d yelled in city %d\n", redSide[i]->ID, i);
                    }
                }
                if (blueSide[i] != nullptr && redSide[i] != nullptr && blueSide[i]->get_type() == "dragon" &&
                    judge_first_attack(i) != 1 && !blueSide[i]->is_dead()) {
                    if (blueSide[i]->get_morale() > 0.8) {
                        globalTicker.print_time();
                        printf("blue dragon %d yelled in city %d\n", blueSide[i]->ID, i);
                    }
                }
                // 获取生命元
                if (!redSide[i]->is_dead() && blueSide[i]->is_dead()) {
                    giveback_red += health_hold[i];
                    //                    redSide[i]-> giveback_health(health_hold[i]);
                    if (health_hold[i] != 0) {
                        globalTicker.print_time();
                        printf("red %s %d earned %d elements for his headquarter\n",
                               redSide[i]->get_type().c_str(), redSide[i]->ID, health_hold[i]);
                        health_hold[i] = 0;
                    }
                }
                if (!blueSide[i]->is_dead() && redSide[i]->is_dead()) {
                    //                    blueSide[i]->giveback_health(health_hold[i]);
                    giveback_blue += health_hold[i];
                    if (health_hold[i] != 0) {
                        globalTicker.print_time();
                        printf("blue %s %d earned %d elements for his headquarter\n",
                               blueSide[i]->get_type().c_str(), blueSide[i]->ID, health_hold[i]);
                        health_hold[i] = 0;
                    }
                }
                // 升旗
                if (!redSide[i]->is_dead() && blueSide[i]->is_dead()) {
                    if (blueSide[i]->get_type() == "lion") redSide[i]->health += mem_blue[i];
//                blueSide[i] = nullptr;
                    if (last_win[i] == 1 && flag[i] != 1) {
                        flag[i] = 1;
                        globalTicker.print_time();
                        printf("red flag raised in city %d\n", i);
                    }
                    last_win[i] = 1;
                } else if (redSide[i]->is_dead() && !blueSide[i]->is_dead()) {
                    if (redSide[i]->get_type() == "lion") blueSide[i]->health += mem_red[i];
//                redSide[i] = nullptr;
                    if (last_win[i] == 2 && flag[i] != 2) {
                        flag[i] = 2;
                        globalTicker.print_time();
                        printf("blue flag raised in city %d\n", i);
                    }
                    last_win[i] = 2;
                } else {
                    if(!(redSide[i]->is_dead() && blueSide[i]->is_dead()))
                        last_win[i] = 0;
//                if(redSide[i]->is_dead()) redSide[i] = nullptr;
//                if(blueSide[i]->is_dead()) blueSide[i] = nullptr;
                }
            }
        }
    }
    void after_battle() {
        // 发布奖励
        // red
        for(int i=CITY_NUM; i>=0; i--) {
            if(redSide[i] != nullptr && blueSide[i] != nullptr) {
                if(blueSide[i]->is_dead() && !redSide[i]->is_dead())
                    redSide[i]->get_bonus();
            }
        }
        // blue
        for(int i=1; i<=CITY_NUM+1; i++) {
            if(blueSide[i] != nullptr && redSide[i] != nullptr) {
                if(redSide[i]->is_dead() && !blueSide[i]->is_dead())
                    blueSide[i]->get_bonus();
            }
        }
        // 传递生命元
        RED.health += giveback_red;
        BLUE.health += giveback_blue;
        giveback_red = giveback_blue = 0;
        for(int i=1; i<=CITY_NUM; i++) {
            if(redSide[i] != nullptr && redSide[i]->is_dead()) redSide[i] = nullptr;
            if(blueSide[i] != nullptr && blueSide[i]->is_dead()) blueSide[i] = nullptr;
        }
    }
    static void print_headquarter_info() {
        globalTicker.print_time();
        RED.print_health_info();
        globalTicker.print_time();
        BLUE.print_health_info();
    }
    void print_warrior_info() {
        for(int i=0; i<=CITY_NUM+1; i++) {
            if(redSide[i] != nullptr) {
                globalTicker.print_time();
                printf("red %s %d has ", redSide[i]->get_type().c_str(), redSide[i]->ID);
                bool output_flag = false;
                if(redSide[i]->arrow != nullptr) {
                    printf("arrow(%d)", redSide[i]->arrow->durability);
                    output_flag = true;
                }
                if(redSide[i]->bomb != nullptr) {
                    if(output_flag) printf(",");
                    printf("bomb");
                    output_flag = true;
                }
                if(redSide[i]->sword != nullptr) {
                    if(output_flag) printf(",");
                    printf("sword(%d)", redSide[i]->sword->w_attack);
                    output_flag = true;
                }
                if(!output_flag) printf("no weapon");
                printf("\n");
            }
        }
        if(already_red != nullptr) {
            globalTicker.print_time();
            printf("red %s %d has ", already_red->get_type().c_str(), already_red->ID);
            bool output_flag = false;
            if(already_red->arrow != nullptr) {
                printf("arrow(%d)", already_red->arrow->durability);
                output_flag = true;
            }
            if(already_red->bomb != nullptr) {
                if(output_flag) printf(",");
                printf("bomb");
                output_flag = true;
            }
            if(already_red->sword != nullptr) {
                if(output_flag) printf(",");
                printf("sword(%d)", already_red->sword->w_attack);
                output_flag = true;
            }
            if(!output_flag) printf("no weapon");
            printf("\n");
        }
        if(already_blue != nullptr) {
            globalTicker.print_time();
            printf("blue %s %d has ", already_blue->get_type().c_str(), already_blue->ID);
            bool output_flag = false;
            if(already_blue->arrow != nullptr) {
                printf("arrow(%d)", already_blue->arrow->durability);
                output_flag = true;
            }
            if(already_blue->bomb != nullptr) {
                if(output_flag) printf(",");
                printf("bomb");
                output_flag = true;
            }
            if(already_blue->sword != nullptr) {
                if(output_flag) printf(",");
                printf("sword(%d)", already_blue->sword->w_attack);
                output_flag = true;
            }
            if(!output_flag) printf("no weapon");
            printf("\n");
        }
        for(int i=0; i<=CITY_NUM+1; i++) {
            if(blueSide[i] != nullptr) {
                globalTicker.print_time();
                printf("blue %s %d has ", blueSide[i]->get_type().c_str(), blueSide[i]->ID);
                bool output_flag = false;
                if(blueSide[i]->arrow != nullptr) {
                    printf("arrow(%d)", blueSide[i]->arrow->durability);
                    output_flag = true;
                }
                if(blueSide[i]->bomb != nullptr) {
                    if(output_flag) printf(",");
                    printf("bomb");
                    output_flag = true;
                }
                if(blueSide[i]->sword != nullptr) {
                    if(output_flag) printf(",");
                    printf("sword(%d)", blueSide[i]->sword->w_attack);
                    output_flag = true;
                }
                if(!output_flag) printf("no weapon");
                printf("\n");
            }
        }
    }
    void do_the_battle() {
        while(true) {
            insert_warrior(); // 0分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;

            flee_lion(); // 5分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;

            do_march(); // 10分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;
            if(over_cnt_blue == 2 || over_cnt_red == 2) return;

            generate_health(); // 2o分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;

            grab_health(); // 30分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;

            shoot_the_arrow(); // 35分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;

            boom(); // 38分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;

            do_battle(); // 40分
            after_battle();
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;

            print_headquarter_info(); // 50分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;

            print_warrior_info(); // 55分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;
        }
    } // 进行整个battle
} battleground;

inline void init_main() {
    // 读入数据
    scanf("%d%d%d%d%d", &INIT_HEALTH, &CITY_NUM, &ARROW_ATK, &LOYALTY_COST, &TIME_LIMIT);
    for(int i=0; i<5; i++) scanf("%d", &Warrior::initialHealthOf[i]);
    for(int i=0; i<5; i++) scanf("%d", &Warrior::initialAttackOf[i]);
    // 初始化
    globalTicker.init_time();
    battleground.init();
    RED = HeadQuarter("red"), BLUE = HeadQuarter("blue");
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    int _T; scanf("%d", &_T);
    for(int _t=1; _t<=_T; _t++) {
        printf("Case %d:\n", _t);
        init_main();
        battleground.do_the_battle();
    }
    return 0;
}