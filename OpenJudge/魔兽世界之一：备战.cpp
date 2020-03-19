// author: wr786
# include<cstdio>
# include<iostream>
# include<string>
using namespace std;
# define FOR(o,start,end) for(int o=start; o<=end; o++)

class Ticker {
private:
	int curTime;
public:
	Ticker(int _t=0):curTime(_t) {}
	int getTime() {return curTime;}
	void setTime(int t) {curTime = t;}
	int nxtSec() {return ++curTime;}
} globalTicker;

class HeadQuarter {
private:
	static const char* redType[5];
	static const char* blueType[5];
	int totalIdx;
	int curTypeIdx;
	int typeMemberCnt[5]; // idx对应上面的Type
	int totalHealth;
	string color;
	void nxtTypeIdx() {curTypeIdx = (curTypeIdx + 1) % 5;}
	const char* getTypeName() {return color=="red"? redType[curTypeIdx]:blueType[curTypeIdx];}
public:
	int typeCost[5];
	bool canGenerate;
	HeadQuarter(string _color):
		color(_color), curTypeIdx(0), canGenerate(true), totalIdx(0) {
		fill(typeMemberCnt, typeMemberCnt+5, 0);
	}
	void setHealth(int hp) {totalHealth = hp;}
	void causeDamage(int damage) {totalHealth -= damage;}
	void generateWarrier(int typeIdx) {
		typeMemberCnt[typeIdx]++;
		totalIdx++;
		causeDamage(typeCost[typeIdx]);
		printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						globalTicker.getTime(),
						color.c_str(),
						getTypeName(),
						totalIdx,
						typeCost[typeIdx],
						typeMemberCnt[typeIdx],
						getTypeName(),
						color.c_str()
					);
		nxtTypeIdx();
	}
	void tryGenerateNxtWarrier() {
		int startTypeIdx = curTypeIdx;
		while(totalHealth < typeCost[curTypeIdx]) {
			nxtTypeIdx();
			if(startTypeIdx == curTypeIdx) {
				printf("%03d %s headquarter stops making warriors\n",
								globalTicker.getTime(), color.c_str());
				canGenerate = false;
				return;
			} // 五个都不能造
		}
		if(totalHealth >= typeCost[curTypeIdx]) {
			generateWarrier(curTypeIdx);
			return;
		}
	}
};

const char* HeadQuarter::redType[5] = {"iceman", "lion", "wolf", "ninja", "dragon"};
const char* HeadQuarter::blueType[5] = {"lion", "dragon", "ninja", "iceman", "wolf"};

int main() {
	int _T; scanf("%d", &_T); FOR(_t, 1, _T) {
		printf("Case:%d\n", _t);
		globalTicker.setTime(0);
		HeadQuarter red("red"), blue("blue");
		int tmp;
		scanf("%d", &tmp); red.setHealth(tmp), blue.setHealth(tmp);
		scanf("%d", &tmp); red.typeCost[4] = blue.typeCost[1] = tmp;
		scanf("%d", &tmp); red.typeCost[3] = blue.typeCost[2] = tmp;
		scanf("%d", &tmp); red.typeCost[0] = blue.typeCost[3] = tmp;
		scanf("%d", &tmp); red.typeCost[1] = blue.typeCost[0] = tmp;
		scanf("%d", &tmp); red.typeCost[2] = blue.typeCost[4] = tmp;
		do {
			if(red.canGenerate) {red.tryGenerateNxtWarrier();}
			if(blue.canGenerate) {blue.tryGenerateNxtWarrier();}
			if(!red.canGenerate && !blue.canGenerate) break;
		} while(globalTicker.nxtSec());
	}
}
