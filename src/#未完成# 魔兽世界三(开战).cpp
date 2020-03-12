#include<cstdio>
#include<algorithm>
#include<string>
#include<cassert>
#include<vector>
using namespace std;
// 全局变量
int INIT_HEALTH, CITY_NUM, LOYALTY_COST, TIME_LIMIT;

class Ticker {
private:
    int curTime;
    int curEvent;
public:
    Ticker(): curTime(0), curEvent(1) {}
    void init_time() {curTime = 0; curEvent = 1;}
    bool nxt_event() {
        if(curEvent < 7) {
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
            case 4: ret += 35; break;
            case 5: ret += 40; break;
            case 6: ret += 50; break;
            case 7: ret += 55; break;
        }
        return ret;
    }
    void print_time() {
        printf("%03d:", curTime);
        switch(curEvent) {
            case 1: printf("00 "); break;
            case 2: printf("05 "); break;
            case 3: printf("10 "); break;
            case 4: printf("35 "); break;
            case 5: printf("40 "); break;
            case 6: printf("50 "); break;
            case 7: printf("55 "); break;
        }
    } //* 输出形如"001:55 "
} globalTicker;

class Weapon; // 提前声明
class Weapon_List {
private:
    Weapon** ls;
    int size;
public:
    Weapon_List(): size(0) {
        ls = new Weapon*[11];
    }
    void push_back(Weapon* newWeapon) {
        ls[size++] = newWeapon;
    }
    void remove(Weapon* wp) {
        for(int i=0; i<size; i++) {
            if(ls[i] == wp){  // 地址相同
                for(int j=i; j<size-1; j++) // 删除操作
                    swap(ls[j], ls[j+1]);
                size--;
                assert(size >= 0);
                break;
            }
        }
    }
    void remove_first() {
        for(int j=0; j<size-1; j++) // 删除操作
            swap(ls[j], ls[j+1]);
        size--;
        assert(size >= 0);
    }
    Weapon* operator [] (int idx) {
        if(idx >= size)
            printf("[ERROR] idx: %d >= size: %d\n", idx, size);
        assert(idx < size);
        return ls[idx];
    }
    int length() {return size;}
    friend class Warrior;
}; // 用来存储weapon的数据结构类
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
public:
    Weapon_List weaponList;
    static string Type[5];
    static int initialHealthOf[5];
    static int initialAttackOf[5];
    friend bool cmp_warrior(Warrior* A, Warrior* B);
    Weapon* get_weapon_of_ID(int wID);
    string get_type() {return Type[typeIdx];}
    void add_weapon(Weapon* wp) {weaponList.push_back(wp);}
    void delete_weapon(Weapon* wp) {weaponList.remove(wp);}
    void deal_damage(int damage, bool isBomb=false) {
        if(isBomb && typeIdx == 1) return; // ninja使用bomb不会让自己受伤。
        health -= damage;
    };
    bool is_dead() {return health <= 0;}
    void sort1_weaponList();
    void sort2_weaponList();
    virtual void do_move_cost() = 0;
    virtual int get_loyalty() = 0;
    virtual void print_info() = 0;
    Warrior(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            typeIdx(_tid), health(_h), attack(_a), belong(&_b), ID(_id) {}
    friend class BattleGround;
};
string Warrior::Type[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Warrior::initialHealthOf[5];
int Warrior::initialAttackOf[5];
bool cmp_warrior(Warrior* A, Warrior* B) {
    return A->ID < B->ID;
}
//! 默认顺序是sword,bomb,arrow; 编号分别是0,1,2
class Weapon {
protected:
    int idx;
    int w_attack;
    int durability; //* 耐久，用到 0 之后要消失
public:
    static string Type[3];
    virtual void cause_weapon_damage(Warrior* self, Warrior* other) = 0;
    Weapon(int _id, int w_atk, int _d):
            idx(_id), w_attack(w_atk), durability(_d) {}
    void delete_weapon_from(Warrior* owner) {
        owner->delete_weapon(this);
    }
    void durability_down(Warrior* owner) {
        durability--;
        if(durability == 0)
            delete_weapon_from(owner);
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
    void cause_weapon_damage(Warrior* self, Warrior* other) {
        other->deal_damage(w_attack);
//        durability_down(self);
    }
};
class Bomb: public Weapon {
public:
    Bomb(int _a): Weapon(1, _a * 4 / 10, 1) {}
    void cause_weapon_damage(Warrior* self, Warrior* other) {
        other->deal_damage(w_attack);
        self->deal_damage(w_attack / 2, true);
        durability_down(self);
    }
};
class Arrow: public Weapon {
public:
    Arrow(int _a): Weapon(2, _a * 3 / 10, 2) {}
    void cause_weapon_damage(Warrior* self, Warrior* other) {
        other->deal_damage(w_attack);
        durability_down(self);
    }
};

bool cmp1 (Weapon* A , Weapon* B) {
    if(A->idx != B->idx) return A->idx < B->idx;
    else return A->durability < B->durability;
}
bool cmp2 (Weapon* A , Weapon* B) {
    if(A->idx != B->idx) return A->idx < B->idx;
    else return A->durability > B->durability;
}
Weapon* Warrior::get_weapon_of_ID(int wID) {
    switch(wID) {
        case 0: return new Sword(attack);
        case 1: return new Bomb(attack);
        case 2: return new Arrow(attack);
    }
    printf("[ERROR] 获取武器失败！\n");
    return new Sword(attack); // 为了解除编译warning，无视就好
}
void Warrior::sort1_weaponList() {
    sort(weaponList.ls, weaponList.ls+weaponList.size, cmp1);
}
void Warrior::sort2_weaponList() {
    sort(weaponList.ls, weaponList.ls+weaponList.size, cmp2);
}

class Dragon: public Warrior {
public:
    Dragon(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            Warrior(_tid, _h, _a, _b, _id) {
        add_weapon(get_weapon_of_ID(ID%3));
    }
    void do_move_cost() {return;}
    int get_loyalty() {return 1;} // 就是为了方便编写而已，没别的，下同。
    void print_info() {
        globalTicker.print_time();
        printf("%s %s %d born\n", belong->getColor().c_str(), Warrior::Type[typeIdx].c_str(), ID);
    }
};
class Ninja: public Warrior {
public:
    Ninja(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            Warrior(_tid, _h, _a, _b, _id) {
        add_weapon(get_weapon_of_ID(ID%3));
        add_weapon(get_weapon_of_ID((ID+1)%3));
    }
    virtual void do_move_cost() {return;}
    virtual int get_loyalty() {return 1;} // 就是为了方便编写而已，没别的，下同。
    void print_info() {
        globalTicker.print_time();
        printf("%s %s %d born\n", belong->getColor().c_str(), Warrior::Type[typeIdx].c_str(), ID);
    }
};
class Iceman: public Warrior {
public:
    Iceman(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            Warrior(_tid, _h, _a, _b, _id) {
        add_weapon(get_weapon_of_ID(ID%3));
    }
    void do_move_cost() {deal_damage(health/10);}
    virtual int get_loyalty() {return 1;} // 就是为了方便编写而已，没别的，下同。
    void print_info() {
        globalTicker.print_time();
        printf("%s %s %d born\n", belong->getColor().c_str(), Warrior::Type[typeIdx].c_str(), ID);
    }
};
class Lion: public Warrior {
private:
    int loyalty;
public:
    Lion(int _tid, int _h, int _a, HeadQuarter& _b, int _id):
            Warrior(_tid, _h, _a, _b, _id) {
        add_weapon(get_weapon_of_ID(ID%3));
        loyalty = belong->health;
    }
    void do_move_cost() {loyalty -= LOYALTY_COST;}
    int get_loyalty() {return loyalty;}
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
};

Warrior* HeadQuarter::tryGenerateNxt() {
//    int archive = curTypeIdx;
    if(health < Warrior::initialHealthOf[curTypeIdx]) {
        canGenerate = false;
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

// 注意到一个城市中最多只有两个不同阵营的武士
// 当其中一个武士不存在时，记为nullptr即可。
class BattleGround {
private:
    Warrior* redSide[22]; // 记录从0~N+1城市中现在的红方/蓝方
    Warrior* blueSide[22];
    bool isFinished;
public:
    BattleGround() {init();}
    void init() { // 初始化
        isFinished = false;
        for(int i=0; i<22; i++)
            redSide[i] = blueSide[i] = nullptr;
    }
    void insert_warrior() {
        if(RED.canGenerate) {
            redSide[0] = RED.tryGenerateNxt();
        } // 返回为nullptr也正确
        if(BLUE.canGenerate) {
            blueSide[CITY_NUM+1] = BLUE.tryGenerateNxt();
        }
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
            globalTicker.print_time();
            printf("red headquarter was taken\n");
            isFinished = true;
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
            globalTicker.print_time();
            printf("blue headquarter was taken\n");
            isFinished = true;
        }
    }
    void grab_weapons() {
        // Wolf的抢夺环节
        for(int i=1; i<=CITY_NUM; i++) {
            if(redSide[i] != nullptr && blueSide[i] != nullptr) {
                redSide[i]->sort2_weaponList(); blueSide[i]->sort2_weaponList();
                if(redSide[i]->typeIdx == 4 || blueSide[i]->typeIdx == 4) {
                    if(!(redSide[i]->typeIdx == 4 && blueSide[i]->typeIdx == 4)) { // 不都为狼
                        Warrior* theWolf = (redSide[i]->typeIdx == 4)? redSide[i] : blueSide[i];
                        Warrior* theOther = (blueSide[i]->typeIdx == 4)? redSide[i] : blueSide[i];
                        int grab_cnt = 0, wp_id = 0;
                        if(theOther->weaponList.length() > 0) {
                            assert(theOther->weaponList[0] != nullptr);
                            wp_id = theOther->weaponList[0]->idx;
                            while(theOther->weaponList.length() > 0 && theWolf->weaponList.length() < 10) {
                                assert(theOther->weaponList.length() > 0);
                                if(theOther->weaponList[0]->idx != wp_id) break;
                                theWolf->weaponList.push_back(theOther->weaponList[0]);
                                theOther->weaponList.remove_first();
                                grab_cnt++;
                            }
                        }
                        if(grab_cnt) { // 打印信息
                            globalTicker.print_time();
                            printf("%s %s %d took %d %s from %s %s %d in city %d\n",
                                   theWolf->belong->getColor().c_str(),
                                   theWolf->get_type().c_str(),
                                   theWolf->ID,
                                   grab_cnt,
                                   Weapon::Type[wp_id].c_str(),
                                   theOther->belong->getColor().c_str(),
                                   theOther->get_type().c_str(),
                                   theOther->ID,
                                   i
                            );
                        }
                    }
                }
            }
        }
    }
    void do_battle() {
        // 战斗环节
        for(int i=1; i<=CITY_NUM; i++) { // 显然，司令部之中是不需要发生战斗的
            if(redSide[i] != nullptr && blueSide[i] != nullptr) { // 双方都有武士在
                // 战斗环节
                redSide[i]->sort1_weaponList(); blueSide[i]->sort1_weaponList();
                int battleType = (i%2)? 1:2; //* 判断现在是谁攻击谁，1代表红打蓝，2代表蓝打红
                int cur_weapon_id_red = 0, cur_weapon_id_blue = 0;
                int lr = redSide[i]->weaponList.length(), lb = blueSide[i]->weaponList.length();
                while(!redSide[i]->is_dead() && !blueSide[i]->is_dead()
                      && !(lr == 0 && lb == 0)) {
                    if(battleType == 1) {
                        if(lr) { // 有武器
                            assert(cur_weapon_id_red < lr);
                            redSide[i]->weaponList[cur_weapon_id_red]->cause_weapon_damage(redSide[i], blueSide[i]);
                        }
                        if(lr != redSide[i]->weaponList.length()) { // 有武器坏了
                            lr = redSide[i]->weaponList.length();
                            if(cur_weapon_id_red >= lr) cur_weapon_id_red = 0;
                        } else {
                            if(cur_weapon_id_red < lr-1) {cur_weapon_id_red++;}
                            else {cur_weapon_id_red = 0;}
                        }
                    } else {
                        if(lb) { // 有武器
                            assert(cur_weapon_id_blue < lb);
                            blueSide[i]->weaponList[cur_weapon_id_blue]->cause_weapon_damage(blueSide[i], redSide[i]);
                        }
                        if(lb != blueSide[i]->weaponList.length()) {
                            lb = blueSide[i]->weaponList.length();
                            if(cur_weapon_id_blue >= lb) cur_weapon_id_blue = 0;
                        } else {
                            if(cur_weapon_id_blue < lb-1) {cur_weapon_id_blue++;}
                            else {cur_weapon_id_blue = 0;}
                        }
                    }
                    bool canContinue = false;
                    for(int j=0; j<redSide[i]->weaponList.length(); j++) {
                        if(redSide[i]->weaponList[j]->idx != 0 || redSide[i]->weaponList[j]->w_attack != 0) {
                            canContinue = true;
                            break;
                        }
                    }
                    for(int j=0; j<blueSide[i]->weaponList.length(); j++) {
                        if(blueSide[i]->weaponList[j]->idx != 0 || blueSide[i]->weaponList[j]->w_attack != 0) {
                            canContinue = true;
                            break;
                        }
                    }
                    if(!canContinue) break;
                    battleType = 3 - battleType; // 换回合
                }
                // 战利品环节
                if(redSide[i]->is_dead() && !blueSide[i]->is_dead()) {
                    redSide[i]->sort2_weaponList();
                    for(int j=0; j<redSide[i]->weaponList.length(); j++) {
                        if(blueSide[i]->weaponList.length() == 10) break;
                        blueSide[i]->weaponList.push_back(redSide[i]->weaponList[j]);
                    }
                } // 蓝抢红
                if(blueSide[i]->is_dead() && !redSide[i]->is_dead()) {
                    blueSide[i]->sort2_weaponList();
                    for(int j=0; j<blueSide[i]->weaponList.length(); j++) {
                        if(redSide[i]->weaponList.length() == 10) break;
                        redSide[i]->weaponList.push_back(blueSide[i]->weaponList[j]);
                    }
                } // 红抢蓝
                // 战后处理环节 is_dead()
                if(redSide[i]->is_dead() && !blueSide[i]->is_dead()) { // blue win
                    globalTicker.print_time();
                    printf("blue %s %d killed red %s %d in city %d remaining %d elements\n",
                           blueSide[i]->get_type().c_str(),
                           blueSide[i]->ID,
                           redSide[i]->get_type().c_str(),
                           redSide[i]->ID,
                           i,
                           blueSide[i]->health);
                } else if(blueSide[i]->is_dead() && !redSide[i]->is_dead()) { // red win
                    globalTicker.print_time();
                    printf("red %s %d killed blue %s %d in city %d remaining %d elements\n",
                           redSide[i]->get_type().c_str(),
                           redSide[i]->ID,
                           blueSide[i]->get_type().c_str(),
                           blueSide[i]->ID,
                           i,
                           redSide[i]->health);
                } else if(blueSide[i]->is_dead() && redSide[i]->is_dead()) { // both dead
                    globalTicker.print_time();
                    printf("both red %s %d and blue %s %d died in city %d\n",
                           redSide[i]->get_type().c_str(),
                           redSide[i]->ID,
                           blueSide[i]->get_type().c_str(),
                           blueSide[i]->ID,
                           i);
                } else { // both alive
                    globalTicker.print_time();
                    printf("both red %s %d and blue %s %d were alive in city %d\n",
                           redSide[i]->get_type().c_str(),
                           redSide[i]->ID,
                           blueSide[i]->get_type().c_str(),
                           blueSide[i]->ID,
                           i);
                }
                // 删除死者
                if(redSide[i]->is_dead()) {redSide[i] = nullptr;}
                else if(redSide[i]->get_type() == "dragon") {
                    globalTicker.print_time();
                    printf("red dragon %d yelled in city %d\n", redSide[i]->ID, i);
                }
                if(blueSide[i]->is_dead()) {blueSide[i] = nullptr;}
                else if(blueSide[i]->get_type() == "dragon") {
                    globalTicker.print_time();
                    printf("blue dragon %d yelled in city %d\n", blueSide[i]->ID, i);
                }
            }
        }
    }
    static void print_headquarter_info() {
        globalTicker.print_time();
        RED.print_health_info();
        globalTicker.print_time();
        BLUE.print_health_info();
    }
    void print_warrior_info() {
        for(int i=1; i<=CITY_NUM; i++) { // 显然，到达对方总部的家伙不需要报道，且经过位移之后，没有人还呆在自己司令部里
            if(redSide[i] != nullptr) {
                globalTicker.print_time();
                printf("red %s %d has ", redSide[i]->get_type().c_str(), redSide[i]->ID);
                // 输出武器
                int sword_cnt = 0, bomb_cnt = 0, arrow_cnt = 0;
                for(int _i=0; _i<redSide[i]->weaponList.length(); _i++) {
                    switch (redSide[i]->weaponList[_i]->idx) {
                        case 0: sword_cnt++; break;
                        case 1: bomb_cnt++; break;
                        case 2: arrow_cnt++; break;
                        default: printf("[ERROR] 打印武器时发生错误\n"); break;
                    }
                }
                printf("%d sword %d bomb %d arrow ", sword_cnt, bomb_cnt, arrow_cnt);
                printf("and %d elements\n", redSide[i]->health);
            }
            if(blueSide[i] != nullptr) {
                globalTicker.print_time();
                printf("blue %s %d has ", blueSide[i]->get_type().c_str(), blueSide[i]->ID);
                // 输出武器
                int sword_cnt = 0, bomb_cnt = 0, arrow_cnt = 0;
                for(int _i=0; _i<blueSide[i]->weaponList.length(); _i++) {
                    switch (blueSide[i]->weaponList[_i]->idx) {
                        case 0: sword_cnt++; break;
                        case 1: bomb_cnt++; break;
                        case 2: arrow_cnt++; break;
                        default: printf("[ERROR] 打印武器时发生错误\n"); break;
                    }
                }
                printf("%d sword %d bomb %d arrow ", sword_cnt, bomb_cnt, arrow_cnt);
                printf("and %d elements\n", blueSide[i]->health);
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
            if(isFinished) return;

            grab_weapons(); // 35分
            globalTicker.nxt_event();
            if(globalTicker.get_time() > TIME_LIMIT) return;

            do_battle(); // 40分
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
    scanf("%d%d%d%d", &INIT_HEALTH, &CITY_NUM, &LOYALTY_COST, &TIME_LIMIT);
    for(int i=0; i<5; i++) scanf("%d", &Warrior::initialHealthOf[i]);
    for(int i=0; i<5; i++) scanf("%d", &Warrior::initialAttackOf[i]);
    // 初始化
    globalTicker.init_time();
    battleground.init();
    RED = HeadQuarter("red"), BLUE = HeadQuarter("blue");
}

int main() {
    int _T; scanf("%d", &_T);
    for(int _t=1; _t<=_T; _t++) {
        printf("Case %d:\n", _t);
        init_main();
        battleground.do_the_battle();
    }
    return 0;
}