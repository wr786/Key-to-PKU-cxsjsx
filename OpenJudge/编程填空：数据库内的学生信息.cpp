#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;
//// 在此处补充你的代码
template <typename _T1, typename _T2, typename Pred=greater<_T1> >
class MyMultimap {
private:
    multimap<_T1, _T2, Pred> data;
public:
    typedef typename multimap<_T1, _T2>::iterator iterator; // 这样能让它被MyMultimap<..>::iterator声明
    void insert(pair<_T1, _T2> p) {
        data.insert(p);
    }
    iterator begin() {
        return data.begin();
    }
    iterator end() {
        return data.end();
    }
    void Set(_T1 target, _T2 setVal) {
        auto p = data.equal_range(target);
        for(iterator it = p.first; it != p.second; ++it)
            it->second = setVal;
    }
    void clear() {data.clear();}
    iterator find(_T1 target) {return data.find(target);}
};

template <typename _T1, typename _T2>
ostream& operator << (ostream& os, pair<_T1, _T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}
/////////////////////////////
struct Student
{
    string name;
    int score;
};
template <class T>
void Print(T first,T last) {
    for(;first!= last; ++ first)
        cout << * first << ",";
    cout << endl;
}
int main()
{

    Student s[] = { {"Tom",80},{"Jack",70},
                    {"Jone",90},{"Tom",70},{"Alice",100} };

    MyMultimap<string,int> mp;
    for(int i = 0; i<5; ++ i)
        mp.insert(make_pair(s[i].name,s[i].score));
    Print(mp.begin(),mp.end()); //按姓名从大到小输出

    mp.Set("Tom",78); //把所有名为"Tom"的学生的成绩都设置为78
    Print(mp.begin(),mp.end());



    MyMultimap<int,string,less<int> > mp2;
    for(int i = 0; i<5; ++ i)
        mp2.insert(make_pair(s[i].score,s[i].name));

    Print(mp2.begin(),mp2.end()); //按成绩从小到大输出
    mp2.Set(70,"Error");          //把所有成绩为70的学生，名字都改为"Error"
    Print(mp2.begin(),mp2.end());
    cout << "******" << endl;

    mp.clear();

    string name;
    string cmd;
    int score;
    while(cin >> cmd ) {
        if( cmd == "A") {
            cin >> name >> score;
            if(mp.find(name) != mp.end() ) {
                cout << "erroe" << endl;
            }
            mp.insert(make_pair(name,score));
        }
        else if(cmd == "Q") {
            cin >> name;
            MyMultimap<string,int>::iterator p = mp.find(name);
            if( p!= mp.end()) {
                cout << p->second << endl;
            }
            else {
                cout << "Not Found" << endl;
            }
        }
    }
    return 0;
}