#include <iostream>
using namespace std;
class Point {
	private:
		int x;
		int y;
	public:
		Point() { };
// 在此处补充你的代码
	friend istream& operator >> (istream& is, Point& p) {
		int tmp;
		is >> tmp; p.x = tmp;
		is >> tmp; p.y = tmp;
		return is;
	}
	friend ostream& operator << (ostream& os, const Point& p) {
		os << p.x << ',' << p.y;
		return os;
	}
};
int main()
{
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	 }
	return 0;
}
