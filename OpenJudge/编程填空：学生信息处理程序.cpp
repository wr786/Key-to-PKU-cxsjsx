#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
private:
	string name;
	int age;
	int stuID;
	int grades[4];
	double avgGrade;
	void readIn(string& str) {
		char c = getchar();
		while(c != ',' && c != EOF) {
			str = str + c;
			c = getchar();
		}
	}
	void readIn(int& num) {
		char c = getchar();	
		while(c != ',' && c != '\n' && c != EOF) {
			num = num * 10 + c - '0';
			c = getchar();
		}
	}
public:
	Student() {
		name = "";
		age = stuID = avgGrade = 0;
		for(int _i=0; _i<4; _i++) grades[_i] = 0;
	}
	void input() {
		readIn(name);
		readIn(age);
		readIn(stuID);
		for(int _i=0; _i<4; _i++) readIn(grades[_i]);
	};
	void calculate() {
		int sumGrade = 0;
		for(int _i=0; _i<4; _i++) sumGrade += grades[_i];
		avgGrade = sumGrade / 4.0;
	};
	void output() {
		cout << name << "," << age << "," << stuID << "," << avgGrade << endl;
	};
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}
