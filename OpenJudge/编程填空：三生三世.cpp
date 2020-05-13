#include<iostream>
#include<cstring>
#include<list>
#include<algorithm>
using namespace std;

class TV_Drama{
	public:
	char name[100];
	int actor;
	int story;
	int acting_skill;
// 在此处补充你的代码
	TV_Drama(const char* _name, int _actor, int _story, int _acting_skill): actor(_actor), story(_story), acting_skill(_acting_skill) {
		strcpy(name, _name);
	}
	bool operator < (const TV_Drama& other) {
		return actor > other.actor;
	}
};
bool comparator_1(const TV_Drama& A, const TV_Drama& B) {
	return A.story > B.story;
}
class comparator_2 {
public:
	bool operator () (const TV_Drama& A, const TV_Drama& B) {
		return A.acting_skill > B.acting_skill;
	}
};
void Printer(const TV_Drama& A) {
	cout << A.name << ";" ;
}
////////////////////
int main(){
	list<TV_Drama> lst;
	int n;
	
	cin>>n;
	char  _name[100];
	int _actor, _story, _acting_skill;
	for (int i=0; i<n; i++){
        cin.ignore();
        cin.getline(_name,100);
        cin>>_actor>>_story>>_acting_skill;
		lst.push_back(TV_Drama(_name, _actor, _story, _acting_skill));
	}

	lst.sort();
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_1);
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_2());
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	return 0;
}