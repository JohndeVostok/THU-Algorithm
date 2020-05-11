#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int mods = 10007;

struct edge {
    int y, c, next;
};

int bfs1(int s, vector<int> &idx, vector<edge> &edge, vector<int> &visited) {
    vector<int> q(idx.size());
    int l = 0, r = 0;
    q[0] = s;
    while (l <= r) {
        for (int i = idx[q[l]]; i != -1; i = edge[i].next) {
            if (!visited[edge[i].y]) {
                r++;
                q[r] = edge[i].y;
                visited[edge[i].y] = 1;
            }
        }
        l++;
    }
}

int bfs2(int s, vector<int> &idx, vector<edge> &edge, vector<vector<int> > &f, vector<int> &cnt) {
    vector<int> q(idx.size());
    int l = 0, r = 0;
    q[0] = s;
    while (l <= r) {
        int x = q[l];
        for (int i = idx[q[l]]; i != -1; i = edge[i].next) {
            int y = edge[i].y, c = edge[i].c;
            f[y][c] = (f[y][c] + f[x][!c]) % mods;
            cnt[y]--;
            if (cnt[y] == 0) {
                r++;
                q[r] = y;
            }
        }
        l++;
    }
}

int main() {
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    vector<int> idx(n, -1);
    vector<edge> edge(m);
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d%d%d", &x, &edge[i].y, &edge[i].c);
        edge[i].next = idx[x];
        idx[x] = i;
    }
    vector<int> visited(n);
    visited[s] = 1;
    bfs1(s, idx, edge, visited);
    vector<int> cnt(n, 0);
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            for (int j = idx[i]; j != -1; j = edge[j].next) {
                if (visited[edge[j].y]) {
                    cnt[edge[j].y]++;
                }
            }            
        }
    }
    vector<vector<int> > f(n, vector<int>(2));
    f[s][0] = 1;
    f[s][1] = 1;
    bfs2(s, idx, edge, f, cnt);
    int ans = (f[t][0] + f[t][1]) % mods;
    printf("%d\n", ans);
}