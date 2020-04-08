#include <cstdio>
char a[5000][5000];

void draw(int x, int y, int depth) {
    if(depth == 1) {
        a[x][y+1] = '/';
        a[x][y+2] = '\\';
        a[x+1][y] = '/';
        a[x+1][y+1] = '_';
        a[x+1][y+2] = '_';
        a[x+1][y+3] = '\\';
    } else {
        draw(x, y+(1<<(depth-1)), depth-1);
        draw(x+(1<<(depth-1)), y, depth-1);
        draw(x+(1<<(depth-1)), y+(1<<(depth)), depth-1);
    }
}

void init_graph(int size) {
    int tmp = 1 << size;
    for(int i=0; i<tmp; i++)
        for(int j=0; j<2*tmp; j++) {
            a[i][j] = ' ';
        }
}

void output_graph(int size) {
    int tmp = 1 << size;
    for(int i=0; i<tmp; i++) {
        for(int j=0; j<2*tmp; j++)
            printf("%c", a[i][j]);
        printf("\n");
    }
}

int main() {
    int n; bool flag=false;
    // freopen("output.txt", "w", stdout);
    while(~scanf("%d", &n) && n) {
        if(flag) printf("\n");
        flag = true;
        init_graph(n);
        draw(0, 0, n);
        output_graph(n);
    }
    return 0;
}