#include <iostream>
using namespace std;
int a[7], n;

bool dfs(int array[], int len) {
    if(len == 1 && array[1] == 42)
        return true;
    for(int i=1; i<len; i++) {
        for(int j=i+1; j<=len; j++) {
            int b[7], idx=0;
            for(int k=1; k<=len; k++)
                if(k!=i && k!=j)
                    b[++idx] = array[k];
            // 枚举二元操作
            b[++idx] = array[i] + array[j];
            if(dfs(b, len-1)) return true;
            b[idx] = array[i] - array[j];
            if(dfs(b, len-1)) return true;
            b[idx] = array[j] - array[i];
            if(dfs(b, len-1)) return true;
            b[idx] = array[i] * array[j];
            if(dfs(b, len-1)) return true;
            if(array[j] && array[i] % array[j] == 0) {
                b[idx] = array[i] / array[j];
                if(dfs(b, len-1)) return true;
            }
            if(array[i] && array[j] % array[i] == 0) {
                b[idx] = array[j] / array[i];
                if(dfs(b, len-1)) return true;
            }
        }
    }
    return  false;
}

int main() {
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> a[i];
    cout << (dfs(a, n)?"YES":"NO") << endl;
}