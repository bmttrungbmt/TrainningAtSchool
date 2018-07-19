#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef double DB;
const int MOD = 1e9+7;
const int NMAX = 3*1e5+7;
const string NAME = "btn4";

int readInt() {
    char c;
    for (c = getchar(); c<'0' || c>'9'; c = getchar());
    int res = c - '0';
    for (c = getchar(); '0'<=c && c<='9'; c = getchar())
        res = res * 10 + c - '0';
    return res;
}

struct Node {
    int lazy_add, lazy_mul, min_val, max_val;
    Node() {}
    Node(int lazy_add, int lazy_mul, int min_val, int max_val):
    lazy_add(lazy_add), lazy_mul(lazy_mul), min_val(min_val), max_val(max_val) {}
};

struct SegmentTree {
    int n;
    Node node[NMAX*4];

    SegmentTree() {
        for(int i = 0; i < 4*NMAX; ++i)
            node[i] = Node(0, 1, 0, 0);
    }

    void updateChild(int id, int mul_val, int add_val) {
        node[id].lazy_add = node[id].lazy_add * mul_val + add_val;
        node[id].lazy_mul = node[id].lazy_mul * mul_val;
        node[id].min_val = node[id].min_val * mul_val + add_val;
        node[id].max_val = node[id].max_val * mul_val + add_val;
        if(node[id].max_val < node[id].min_val)
            swap(node[id].max_val, node[id].min_val);
    }

    void down(int id) {
        int mul_val = node[id].lazy_mul, add_val = node[id].lazy_add;
        node[id].lazy_add = 0;
        node[id].lazy_mul = 1;
        updateChild(id * 2, mul_val, add_val);
        updateChild(id * 2 + 1, mul_val, add_val);
    }

    void add(int id, int l, int r, int u, int v, int val) {
        if(v < l || r < u) return;
        if(u <= l && r <= v) {
            node[id].lazy_add += val;
            node[id].max_val += val;
            node[id].min_val += val;
            return;
        }
        down(id);
        int mid = (l + r) / 2;
        add(id * 2, l, mid, u, v, val);
        add(id * 2 + 1, mid + 1, r, u, v, val);
        node[id].min_val = min(node[id * 2].min_val, node[id * 2 + 1].min_val);
        node[id].max_val = max(node[id * 2].max_val, node[id * 2 + 1].max_val);
    }

    void mul(int id, int l, int r, int u, int v, int val) {
        if(v < l || r < u) return;
        if(u <= l && r <= v) {
            node[id].lazy_mul *= val;
            node[id].lazy_add *= val;
            node[id].max_val *= val;
            node[id].min_val *= val;
            if(node[id].max_val < node[id].min_val)
                swap(node[id].max_val, node[id].min_val);
            return;
        }
        int mid = (l + r) / 2;
        mul(id * 2, l, mid, u, v, val);
        mul(id * 2 + 1, mid + 1, r, u, v, val);
        node[id].min_val = min(node[id * 2].min_val, node[id * 2 + 1].min_val);
        node[id].max_val = max(node[id * 2].max_val, node[id * 2 + 1].max_val);
    }

    int getMin(int id, int l, int r, int u, int v) {
        if(v == 0) return 0;
        if(v < l || r < u) return INT_MAX;
        if(u <= l && r <= v) return node[id].min_val;
        down(id);
        int mid = (l + r) / 2;
        return min(getMin(id * 2, l, mid, u, v),
                   getMin(id * 2 + 1, mid + 1, r, u, v));
    }

    int getMax(int id, int l, int r, int u, int v) {
        if(v < l || r < u) return INT_MIN;
        if(u <= l && r <= v) return node[id].max_val;
        down(id);
        int mid = (l + r) / 2;
        return max(getMax(id * 2, l, mid, u, v),
                   getMax(id * 2 + 1, mid + 1, r, u, v));
    }

    void add(int u, int v, int val) {
        add(1, 1, n, u, v, val);
    }
    void mul(int u, int v, int val) {
        mul(1, 1, n, u, v, val);
    }
    int getMin(int u, int v) {
        if(v == 0) return 0;
        return getMin(1, 1, n, u, v);
    }
    int getMax(int u, int v) {
        return getMax(1, 1, n, u, v);
    }

} T;

string s;

void update(int l, int r) {
    int tmp = T.getMin(l-1, l-1);
    int tmp2 = T.getMin(r, r);
    T.add(l, r, -tmp);
    T.mul(l, r, -1);
    T.add(l , r, tmp);
    T.add(r+1, T.n, -tmp2);
    T.add(r+1, T.n, T.getMin(r, r));
}

int solve(int l, int r) {
    int tmp = T.getMin(l-1, l-1);
    int Max = T.getMax(l, r), Min = T.getMin(l, r), last = T.getMin(r, r);
    if (Min<tmp || last!=tmp)
        return -1;
    return Max-tmp;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen((NAME + ".inp").c_str(), "r", stdin);
    freopen((NAME + ".out").c_str(), "w", stdout);
    char c;
    while(c = getchar()) {
        s += c;
        if(c == '\n') break;
    }
    T.n = s.size();
    int ps = 0;
    for(int i = 0; i < s.size(); ++i) {
        ps += (s[i] == '(' ? 1 : -1);
        T.add(i + 1, i + 1, ps);
    }
    int query;
    query = readInt();
    while(query--) {
        int tp, lt, rt;
        tp = readInt();
        lt = readInt();
        rt = readInt();
        if(tp == 1) update(lt, rt);
        else cout << solve(lt, rt) << endl;
    }
    return 0;
}
