#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Mat{
	int h,w;
public:
	Mat(int height,int width):h(height),w(width)
// 在此处补充你的代码
	{order = ++totalNum;}
	int** data;
	int order;
	static int totalNum;
	friend istream& operator >> (istream& is, Mat& matrix) {
		int &h=matrix.h, &w = matrix.w;
		matrix.data = new int*[h];
		for(int i=0; i<h; i++) {
			matrix.data[i] = new int[w]; 
			for(int j=0; j<w; j++) {
				is >> matrix.data[i][j];
			}
		}
		return is;
	}
	friend ostream& operator << (ostream& os, const Mat& matrix) {
		for(int i=0; i<matrix.h; i++) {
			bool flag = false;
			for(int j=0; j<matrix.w; j++) {
				if(flag) os << " ";
				os << matrix.data[i][j];
				flag = true;
			}
			os << '\n';
		}
		return os;
	}
	bool operator < (const Mat& other) {
		if(h*w == other.h*other.w) return order > other.order;
		return h*w < other.h * other.w;
	}
	int sum() const {
		int ret = 0;
		for(int i=0; i<h; i++)
			for(int j=0; j<w; j++)
				ret += data[i][j];
		return ret;
	}
};
int Mat::totalNum = 0;
bool comparator_1(const Mat& A, const Mat& B) {
	if(A.sum() == B.sum()) return A.order < B.order;
	return A.sum() < B.sum();
}
class comparator_2 {
	public:
		bool operator() (const Mat& A, const Mat& B) const {return A.order < B.order;}
};
//////////
int main()
{
	vector<Mat> m;
	m.push_back(Mat(2,2));
	m.push_back(Mat(3,4));
	m.push_back(Mat(2,2));
	cin >> m[0] >> m[1] >> m[2];
	sort(m.begin(),m.end());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_1);
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_2());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	return 0;
}