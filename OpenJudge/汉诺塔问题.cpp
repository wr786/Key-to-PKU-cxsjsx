#include<cstdio>

void fn(int num, char cur, char tar, char med) {
    if(num == 1) {
        printf("%c->1->%c\n", cur, tar);
        return;
    }
    fn(num-1, cur, med, tar);
    printf("%c->%d->%c\n", cur, num, tar);
    fn(num-1, med, tar, cur);
}

int main() {
    int n; char a, b, c;
    scanf("%d %c %c %c", &n, &a, &b, &c);
    fn(n, a, b, c);
    return 0;
}