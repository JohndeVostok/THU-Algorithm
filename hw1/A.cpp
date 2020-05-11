#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
    int l, r, s, ls, rs;
};

struct value {
    int idx, v, w;
};

bool cmp1(value a, value b) {
    return a.v < b.v;
}

bool cmp2(value a, value b) {
    return a.idx < b.idx;
}

int make_tree(int l, int r, vector<node> &pool) {
    int idx = pool.size();
    pool.push_back(node());
    pool[idx].l = l;
    pool[idx].r = r;
    pool[idx].s = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        int ls = make_tree(l, mid, pool);
        int rs = make_tree(mid + 1, r, pool);
        pool[idx].ls = ls;
        pool[idx].rs = rs;
    } else {
        pool[idx].ls = -1;
        pool[idx].rs = -1;
    }
    return idx;
}

int ins(int idx, int x, vector<node> &pool) {
    int idy = pool.size();
    pool.push_back(node());
    pool[idy].l = pool[idx].l;
    pool[idy].r = pool[idx].r;
    pool[idy].s = pool[idx].s + 1;
    pool[idy].ls = pool[idx].ls;
    pool[idy].rs = pool[idx].rs;
    if (pool[idy].l < pool[idy].r) {
        int mid = (pool[idy].l + pool[idy].r) / 2;
        if (x <= mid) {
            int ls = ins(pool[idy].ls, x, pool);
            pool[idy].ls = ls;
        } else {
            int rs = ins(pool[idy].rs, x, pool);
            pool[idy].rs = rs;
        }
    }
    return idy;
}

int get(int idx, int idy, int s, vector<node> &pool) {
    if (pool[idx].l == pool[idx].r) {
        return pool[idx].l;
    }
    int sl = pool[pool[idy].ls].s - pool[pool[idx].ls].s;
    if (s <= sl) {
        return get(pool[idx].ls, pool[idy].ls, s, pool);
    } else {
        return get(pool[idx].rs, pool[idy].rs, s - sl, pool);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    vector<value> data(n);
    for (int i = 0; i < n; i++) {
        data[i].idx = i;
        scanf("%d", &data[i].v);
    }
    vector<int> value;
    sort(data.begin(), data.end(), cmp1);
    data[0].w = 1;
    value.push_back(data[0].v);
    for (int i = 1; i < n; i++) {
        if (data[i].v == data[i-1].v) {
            data[i].w = data[i-1].w;
        } else {
            data[i].w = data[i-1].w + 1;
            value.push_back(data[i].v);
        }
    }
    int maxn = data[n - 1].w;
    sort(data.begin(), data.end(), cmp2);
    vector<node> pool;
    vector<int> tr;
    tr.push_back(make_tree(1, maxn, pool));
    for (int i = 0; i < n; i++) {
        tr.push_back(ins(tr[i], data[i].w, pool));
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int k, l, r;
        scanf("%d%d%d", &k, &l, &r);
        if (r - l + 1 < k) {
            printf("EMPTY");
        } else {
            for (int t = k; t <= r - l + 1; t += k) {
                int ans = get(tr[l-1], tr[r], t, pool);
                printf("%d ", value[ans-1]);
            }
        }
        printf("\n");
    }
}