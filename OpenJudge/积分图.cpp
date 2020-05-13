#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class IntegralImage{
// 在此处补充你的代码
public:
	int h;
	int w;
	int curLine=0;
	int* data;
	IntegralImage(int _h, int _w) : h(_h), w(_w) { data = new int[h*w]; }
	void operator() (int* line) {
		*(data + curLine*w) = line[0];
		for(int i=1; i<w; i++)
			*(data + curLine*w + i) = line[i] + *(data + curLine*w + i -1);
		if(curLine) {
			for(int i=w; i>=0; i--) {
				*(data + curLine*w + i) += *(data + (curLine-1)*w + i);
			}
		}
		curLine++;
	}
	int* operator [] (int idx) {return data + idx*w;}
};
int main(){
    int H, W;
    cin >> H >> W;
    int ** image = new int*[H];
    for(int i=0;i<H;++i){
        image[i]=new int[W];
    }
    for(int i=0;i<H;++i)
    for(int j=0;j<W;++j)
        cin >> image[i][j];
    IntegralImage it(H,W);
    for_each(image, image+H, it);
    for(int i=0;i<H;++i){
        for(int j=0;j<W;++j)
            cout<<it[i][j]<<" ";
        cout<<endl;
    }
   
}