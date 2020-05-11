#include <cstdio>
#include <cstring>

int t, m, n;
char str[100010], res[100010];

int main() {
    int t;
    scanf("%d", &t);
    for (int k = 0; k < t; k++) {
        scanf("%s%d", str, &m);
        n = strlen(str);
        int p = 1, cnt = m;
        res[0] = str[0];
        for (int i = 1; i < n; i++) {
            while (cnt > 0 && p > 0 && str[i] > res[p - 1]) {
                p--;
                cnt--;
            }
            res[p] = str[i];
            p++;
        }
        res[p - cnt] = '\0';
        printf("%s\n", res);
    }
}