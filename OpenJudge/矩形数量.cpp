#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <cctype>
using namespace std;
int n;
int idx;
int cnt;

struct Point {
    int x;
    int y;
    bool operator < (const Point& other) const {
        return x == other.x? y < other.y : x < other.x;
    }
    Point(int _x=0, int _y=0):x(_x),y(_y){}
} p[51], tp[51];

int main() {
    int t; cin >> t;
    while(t--) {
      cin >> n;
      for(int i=1; i<=n; i++)
          cin >> p[i].x >> p[i].y;
      sort(p+1, p+1+n);
      idx = cnt = 0;
      // unique
      for(int i=1; i<=n; i++) {
          if(p[i].x != p[i+1].x || p[i].y != p[i+1].y) {
              tp[++idx].x = p[i].x;
              tp[idx].y = p[i].y;
          }
      }
//      for(int i=1; i<=idx; i++) {
//          cout << "(" << tp[i].x << ", " << tp[i].y << ")\n";
//      }
      for(int i=1; i<=idx; i++) {
          for(int j=i+1; j<=idx; j++) {
              if(tp[i].x != tp[j].x) break;
              for(int k=j+1; k<=idx; k++) {
                  if(tp[k].y == tp[i].y) {
                      for(int l=k+1; l<=idx; l++) {
                          if(tp[l].x != tp[k].x) break;
                          if(tp[l].y == tp[j].y) {
//                              cout << tp[i].x << " " << tp[i].y << endl;
//                              cout << tp[j].x << " " << tp[j].y << endl;
//                              cout << tp[k].x << " " << tp[k].y << endl;
//                              cout << tp[l].x << " " << tp[l].y << endl;
//                              cout << "----------" << endl;
                              cnt++;
                          }
                      }
                  }
              }
          }
      }
      cout << cnt << endl;
    }
}