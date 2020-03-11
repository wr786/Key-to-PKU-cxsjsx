#include<cstdio>
#include<algorithm>
#include<string>
#include<cassert>
using namespace std;
// 全局变量
int CITY_NUM, LOYALTY_COST;

class Ticker {
	private:
		int curTime;
		int curEvent;
	public:
		Ticker(): curTime(0), curEvent(1) {}
		void init_time() {curTime = 0;}
		bool nxt_event() {
			if(curEvent < 10) {
				curEvent++;
				return true;
			} else {
				curEvent = 1;
				return false;
			}
		} //* 返回false的时候，停止遍历
		void nxt_minute() {curTime++;}
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
			ls = new Weapon*[10];
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
					break;
				}
			}	
		}
		Weapon* operator [] (int idx) {assert(idx<size); return ls[idx];}
		int length() {return size;}
		friend class Warrior;
}; // 用来存储weapon的数据结构类

class HeadQuater{ // 提前声明
	protected:
		int curTypeIdx; // 现在要制造哪个
		string color;
	public:
		static int INIT_HEALTH;
		int typeNum[5]; // 对应着5种类型存在了多少个
		int health;
		int totalIdx;
		bool canGenerate; // 能否继续生产
		HeadQuater(const string& _color):
			canGenerate(true), health(INIT_HEALTH), color(_color), totalIdx(0) {
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
		void generateWarrior() {
			//! 需要补全
		}
		void tryGenerateNxt();
		friend class Warrior;
};
int HeadQuater::INIT_HEALTH;

//! 默认type顺序是dragon、ninja、iceman、lion、wolf
//                 0       1      2      3     4
class Warrior {
	protected:
		int typeIdx;
		int health;
		int attack;
		HeadQuater* belong;
		int ID; // 在所属阵营里的编号
		Weapon_List weaponList;
	public:
		static string Type[5];
		static int initialHealthOf[5];
		static int initialAttackOf[5];
		Weapon* get_weapon_of_ID(int wID);
		void add_weapon(Weapon* wp) {weaponList.push_back(wp);}
		void delete_weapon(Weapon* wp) {weaponList.remove(wp);}
		void deal_damage(int damage, bool isBomb=false) {
			if(isBomb && typeIdx == 1) return; // ninja使用bomb不会让自己受伤。
			health -= damage;
		};
		bool is_dead() {return health > 0;}
		void sort1_weaponList();
		void sort2_weaponList();
		virtual void print_info() = 0;
		virtual void do_move_cost() = 0;
		//todo 编写派生类对应虚函数
		Warrior(int _tid, int _h, int _a, HeadQuater& _b, int _id):
			typeIdx(_id), health(_h), attack(_a), belong(&_b), ID(_id) {}
	friend class BattleGround;
};
string Warrior::Type[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Warrior::initialHealthOf[5];
int Warrior::initialAttackOf[5];
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
			durability_down(self);
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
	return new Sword(attack); //// 为了解除编译warning，无视就好
}
void Warrior::sort1_weaponList() {
	sort(weaponList.ls, weaponList.ls+weaponList.size, cmp1);
}
void Warrior::sort2_weaponList() {
	sort(weaponList.ls, weaponList.ls+weaponList.size, cmp2);
}

class Dragon: public Warrior {
	public:
		Dragon(int _tid, int _h, int _a, HeadQuater& _b, int _id):
			Warrior(_tid, _h, _a, _b, _id) {
				add_weapon(get_weapon_of_ID(ID%3));
			}
		void do_move_cost() {return;}
};

class Ninja: public Warrior {
	public:
		Ninja(int _tid, int _h, int _a, HeadQuater& _b, int _id):
			Warrior(_tid, _h, _a, _b, _id) {
				add_weapon(get_weapon_of_ID(ID%3));
				add_weapon(get_weapon_of_ID((ID+1)%3));
			}
		void do_move_cost() {return;}
};

class Iceman: public Warrior {
	public:
		Iceman(int _tid, int _h, int _a, HeadQuater& _b, int _id):
			Warrior(_tid, _h, _a, _b, _id) {
				add_weapon(get_weapon_of_ID(ID%3));
			}
		void do_move_cost() {deal_damage(health/10);}
};

class Lion: public Warrior {
	private:
		int loyalty;
	public:
		Lion(int _tid, int _h, int _a, HeadQuater& _b, int _id):
			Warrior(_tid, _h, _a, _b, _id) {
				add_weapon(get_weapon_of_ID(ID%3));
				loyalty = belong->health;
			}
		void do_move_cost() {loyalty -= LOYALTY_COST;}
};

class Wolf: public Warrior {
	public:
		Wolf(int _tid, int _h, int _a, HeadQuater& _b, int _id):
			Warrior(_tid, _h, _a, _b, _id) {}
		void do_move_cost() {return;}
};

void HeadQuater::tryGenerateNxt() {
	int archive = curTypeIdx;
	while(health < Warrior::initialHealthOf[curTypeIdx]) {
		nxtTypeIdx();
		if(archive == curTypeIdx) {
			// printf("%03d %s headquarter stops making warriors\n",
			// 				globalTicker.getTime(), color.c_str());
			canGenerate = false;
			return;
		}
	} // health >= typeCost[curTypeIdx]
	generateWarrior();
}

// 注意到一个城市中最多只有两个不同阵营的武士
// 当其中一个武士不存在时，记为NULL即可。
class BattleGround {
	private:
		Warrior* redSide[22]; // 记录从0~N+1城市中现在的红方/蓝方
		Warrior* blueSide[22];
	public:
		BattleGround() {
			for(int i=0; i<22; i++)
				redSide[i] = blueSide[i] = NULL;
		} // 初始化
		void flee_lion() {
			//todo 待添加狮子逃跑环节
		}
		void do_march() {
			for(int i=CITY_NUM; i>=0; i--) {
				redSide[i+1] = redSide[i]; // 右移
				redSide[i+1]->do_move_cost();
			}
			for(int i=1; i<=CITY_NUM+1; i++) {
				blueSide[i-1] = blueSide[i]; // 左移
				blueSide[i+1]->do_move_cost();
			}
		}
		void do_battle() {
			// 战斗环节
			for(int i=1; i<=CITY_NUM; i++) { // 显然，司令部之中是不需要发生战斗的
				if(redSide != NULL && blueSide != NULL) { // 双方都有武士在
					// Wolf的抢夺环节
					redSide[i]->sort2_weaponList(); blueSide[i]->sort2_weaponList();
					if(redSide[i]->typeIdx == 4 || blueSide[i]->typeIdx == 4) { 
						if(!(redSide[i]->typeIdx == 4 && blueSide[i]->typeIdx == 4)) { // 不都为狼
							Warrior*& theWolf = (redSide[i]->typeIdx == 4)? redSide[i] : blueSide[i];
							Warrior*& theOther = (blueSide[i]->typeIdx == 4)? redSide[i] : blueSide[i];
							if(theOther->weaponList.length()) {
								int wp_id = theOther->weaponList[0]->idx;
								if(wp_id != 2) {
									while(theOther->weaponList.length() && theWolf->weaponList.length() <= 10) {
										if(theOther->weaponList[0]->idx != wp_id) break;
										theWolf->weaponList.push_back(theOther->weaponList[0]);
										theOther->weaponList.remove(theOther->weaponList[0]);
									}
								} else { // 是Arrow，优先抢新的
									while(theOther->weaponList.length() && theWolf->weaponList.length() <= 10) {
										if(theOther->weaponList[theOther->weaponList.length() - 1]->idx != wp_id) break;
										theWolf->weaponList.push_back(theOther->weaponList[theOther->weaponList.length() - 1]);
										theOther->weaponList.remove(theOther->weaponList[theOther->weaponList.length() - 1]);
									}
								}
							}
						}
					} 
					// 战斗环节
					redSide[i]->sort1_weaponList(); blueSide[i]->sort1_weaponList();
					int battleType = (i%2)? 1:2; //* 判断现在是谁攻击谁，1代表红打蓝，2代表蓝打红
					int cur_weapon_id_red = 0, cur_weapon_id_blue = 0;
					int lr = redSide[i]->weaponList.length(), lb = blueSide[i]->weaponList.length();
					while(!redSide[i]->is_dead() && !blueSide[i]->is_dead()
						&& !(lr == 0 && lb == 0)) {
						if(battleType == 1) {
							if(lr) { // 有武器
								redSide[i]->weaponList[cur_weapon_id_red]->cause_weapon_damage(redSide[i], blueSide[i]);
							}
							if(lr != redSide[i]->weaponList.length()) { // 有武器坏了
								lr = redSide[i]->weaponList.length();
							} else {
								if(cur_weapon_id_red < lr-1) {cur_weapon_id_red++;}
								else {cur_weapon_id_red = 0;}
							}
						} else {
							if(lb) { // 有武器
								blueSide[i]->weaponList[cur_weapon_id_blue]->cause_weapon_damage(blueSide[i], redSide[i]);
							}
							if(lb != blueSide[i]->weaponList.length()) {
								lb = blueSide[i]->weaponList.length();
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
					// 删除死者环节
					if(redSide[i]->is_dead()) redSide[i] = NULL;
					if(blueSide[i]->is_dead()) blueSide[i] = NULL;
				}
			}
		}
};

int main() {
	//! 待补充
	return 0;
}