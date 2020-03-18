#include <iostream>
#include <string>

using namespace std;
template <class T>
class CMyistream_iterator
{
// 在此处补充你的代码
private:
    T array[4];
    istream& is;
    int index;
    int curIndex;
public:
    explicit CMyistream_iterator<T>(istream& _is): is(_is), index(0), curIndex(0) {
        is >> array[index++];
    }
    friend T operator * (CMyistream_iterator<T>& CM) {
        return CM.array[CM.curIndex];
    }

    void operator ++ (int x) {
        curIndex++;
        is >> array[index++];
    }
};



int main()
{
    int t;
    cin >> t;
    while( t -- ) {
        CMyistream_iterator<int> inputInt(cin);
        int n1,n2,n3;
        n1 = * inputInt; //读入 n1
        int tmp = * inputInt;
        cout << tmp << endl;
        inputInt ++;
        n2 = * inputInt; //读入 n2
        inputInt ++;
        n3 = * inputInt; //读入 n3
        cout << n1 << " " << n2<< " " << n3 << " ";
        CMyistream_iterator<string> inputStr(cin);
        string s1,s2;
        s1 = * inputStr;
        inputStr ++;
        s2 = * inputStr;
        cout << s1 << " " << s2 << endl;
    }
    return 0;
}