#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i] + b[i]);
    }
    printf("\n");
}