// author: wr786
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
using namespace std;

class Ticker {
private:
	int curTime;
public:
	Ticker(int _t=0):curTime(_t) {}
	int getTime() {return curTime;}
	void setTime(int t) {curTime = t;}
	int nxtSec() {return ++curTime;}
} globalTicker;

class Weapon{
private:
	string type;
public:
	Weapon(int idx) {
		switch (idx) {
			case 0: type = "sword"; break;
			case 1: type = "bomb"; break;
			case 2: type = "arrow"; break;
		}
	}
	string getType() {return type;}
};

class HeadQuater{ // 提前声明
protected:
	int curTypeIdx; // 现在要制造哪个
	string color;
public:
	int typeNum[5]; // 对应着5种类型存在了多少个
	int health;
	int totalIdx;
	bool canGenerate; // 能否继续生产
	HeadQuater(const int& hp, const string& _color);
	void nxtTypeIdx();
	void generateWarrior();
	void tryGenerateNxt();
	friend class Warrior;
};
class Warrior{
protected:
	int type;
	HeadQuater* belong;
	int id;
public:
	static int cost[5]; // 依次是 dragon 、ninja、iceman、lion、wolf
	static string toTypeStr[5];
	Warrior(const int& _t, HeadQuater& _b, const int & _id):
	type(_t), belong(&_b), id(_id) {}
	void printInfo() {
		printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						globalTicker.getTime(),
						belong->color.c_str(),
						toTypeStr[type].c_str(),
						belong->totalIdx,
						cost[type],
						belong->typeNum[type],
						toTypeStr[type].c_str(),
						belong->color.c_str()
					);
	}
};
class Dragon: public Warrior {
private:
	Weapon* weapon;
	double morale;
public:
	void printInfo() {
		Warrior::printInfo();
		printf("It has a %s,and it's morale is %.2lf\n", weapon->getType().c_str(), morale);
	}
	Dragon(const int& _t, HeadQuater& _b, const int& _id):
	Warrior(_t, _b, _id) {
		weapon = new Weapon(id%3);
		morale = belong->health / (double)cost[0];
		printInfo();
	}
};
class Ninja: public Warrior {
private:
	Weapon* weapons[2];
public:
	void printInfo() {
		Warrior::printInfo();
		printf("It has a %s and a %s\n", weapons[0]->getType().c_str(), weapons[1]->getType().c_str());
	}
	Ninja(const int& _t, HeadQuater& _b, const int& _id):
	Warrior(_t, _b, _id) {
		weapons[0] = new Weapon(id%3);
		weapons[1] = new Weapon((id+1)%3);
		printInfo();
	}
};
class Iceman: public Warrior {
private:
	Weapon* weapon;
public:
	void printInfo() {
		Warrior::printInfo();
		printf("It has a %s\n", weapon->getType().c_str());
	}
	Iceman(const int& _t, HeadQuater& _b, const int& _id):
	Warrior(_t, _b, _id) {
		weapon = new Weapon(id%3);
		printInfo();
	}
};
class Lion: public Warrior {
private:
	int loyalty;
public:
	void printInfo() {
		Warrior::printInfo();
		printf("It's loyalty is %d\n", loyalty);
	}
	Lion(const int& _t, HeadQuater& _b, const int& _id):
	Warrior(_t, _b, _id) {
		loyalty = belong->health;
		printInfo();
	}
};
class Wolf: public Warrior {
public:
	void printInfo() {
		Warrior::printInfo();
	}
	Wolf(const int& _t, HeadQuater& _b, const int& _id):
	Warrior(_t, _b, _id) {
		printInfo();
	}
};
// 红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序循环制造武士。
// 蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序循环制造武士。
// dragon 、ninja、iceman、lion、wolf 分别对应：
//   0       1       2      3     4
HeadQuater::HeadQuater(const int& hp, const string& _color):
canGenerate(true), health(hp), color(_color), totalIdx(0) {
	fill(typeNum, typeNum+5, 0);
	if(color == "red") curTypeIdx = 2; // initialize
	else curTypeIdx = 3;
}
void HeadQuater::nxtTypeIdx() {
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
void HeadQuater::generateWarrior() {
	totalIdx++;
	typeNum[curTypeIdx]++;
	health -= Warrior::cost[curTypeIdx];
	switch (curTypeIdx) {
		case 0: {
			Dragon tmpd(curTypeIdx, *this, totalIdx);
			break;
		}
		case 1: {
			Ninja tmpn(curTypeIdx, *this, totalIdx);
			break;
		}
		case 2: {
			Iceman tmpi(curTypeIdx, *this, totalIdx);
			break;
		}
		case 3: {
			Lion tmpl(curTypeIdx, *this, totalIdx);
			break;
		}
		case 4: {
			Wolf tmpw(curTypeIdx, *this, totalIdx);
			break;
		}
		default: {
			printf("[ERROR] Type越界!\n");
			break;
		}
	}
	nxtTypeIdx();
}
void HeadQuater::tryGenerateNxt() {
	int archive = curTypeIdx;
	while(health < Warrior::cost[curTypeIdx]) {
		nxtTypeIdx();
		if(archive == curTypeIdx) {
			printf("%03d %s headquarter stops making warriors\n",
							globalTicker.getTime(), color.c_str());
			canGenerate = false;
			return;
		}
	} // health >= typeCost[curTypeIdx]
	generateWarrior();
}
int Warrior::cost[5] = {0, 0, 0, 0, 0};
string Warrior::toTypeStr[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};

int main() {
	int _T; scanf("%d", &_T); for(int _t=1; _t<=_T; _t++) {
		printf("Case:%d\n", _t);
		globalTicker.setTime(0);
		int HP; scanf("%d", &HP);
		for(int i=0; i<5; i++)
			scanf("%d", &Warrior::cost[i]);
		HeadQuater RED(HP, "red"), BLUE(HP, "blue");
		do {
			if(RED.canGenerate) {RED.tryGenerateNxt();}
			if(BLUE.canGenerate) {BLUE.tryGenerateNxt();}
			if(!RED.canGenerate && !BLUE.canGenerate) break;
		} while(globalTicker.nxtSec());
	}
}
