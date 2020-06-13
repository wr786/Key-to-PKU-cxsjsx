#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
int field[5001][5001];
int n, m;
int cropsNum;
int ans = 1;

class Crop {
public:
    int x;
    int y;
    Crop(int _x=0, int _y=0): x(_x), y(_y) {}
    bool operator < (const Crop& other) const {
        return x == other.x? y < other.y : x < other.x;
    }
    bool operator == (const Crop& other) const {
        return x == other.x && y == other.y;
    }
};

vector<Crop> crops;

int track(int curPoint, int dirx, int diry) {
    int cnt = 1;    // origin
    while(true) {
        int nx = crops[curPoint].x + dirx;
        int ny = crops[curPoint].y + diry;
        if(binary_search(crops.begin(), crops.end(), Crop(nx, ny))) {
            // exists
            cnt++;
            auto it = find(crops.begin(), crops.end(), Crop(nx, ny));
            curPoint = (int)distance(crops.begin(), it);   // get idx
        } else {
            // do not exist
            if(nx > n || nx < 1 || ny > m || ny < 1) {  // out of range, which means the frog jump out of the field
                return cnt;
            } else {
                return 0;   // can not form a path
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> cropsNum;;
    for(int i=0; i<cropsNum; i++) {
        int xpos, ypos;
        cin >> xpos >> ypos;
        crops.push_back(Crop(xpos, ypos));
    }
    sort(crops.begin(), crops.end());
    for(int i=0; i<cropsNum-1; i++) {
        for(int j=i+1; j<cropsNum; j++) {
            int dirx = crops[j].x-crops[i].x, diry = crops[j].y-crops[i].y;
            if(crops[i].x - dirx >= 1 && crops[i].y - diry >= 1 && crops[i].x - dirx <= n && crops[i].y - diry <= m) {
                continue;   // prune, start with a boundary
            }
            if(crops[i].x + (ans-1)*dirx > n) { // sorted by row
                break;   // must be less
            }
            if(crops[i].y + (ans-1)*diry > m || crops[i].y + (ans-1)*diry < 1) {
                continue;
            }
            int steps = track(i, dirx, diry);
            if(steps >= 3) ans = max(ans, steps);
        }
    }
    cout << (ans==1?0:ans) << endl;
    return 0;
}