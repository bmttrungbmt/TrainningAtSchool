#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()

using namespace std;
typedef double DB;
typedef long long LL;
const LL MOD = 1e9+7;
const LL NMAX = 1e6+7;
const string NAME = "clopair";

struct Point{
    LL X, Y, ps;
};

int n, s, t;
Point a[NMAX];
LL minn = LL(1e18);

bool cmp_x(Point a, Point b) {
    if(a.X == b.X) return a.Y < b.Y;
    return a.X < b.X;
}

bool cmp_y(Point a, Point b) {
    if(a.Y == b.Y) return a.X < b.X;
    return a.Y < b.Y;
}

void update(Point a, Point b) {
    LL dist = (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y);
    if(dist < minn) {
        minn = dist;
        s = a.ps;
        t = b.ps;
    }
}

void solve(int l, int r) {
    if(r <= l) return;
    if(r == l + 1) {
        update(a[l], a[r]);
        if(!cmp_y(a[l], a[r])) swap(a[l], a[r]);
        return;
    }
    int mid = (l + r) / 2;
    LL midx = a[mid].X;
    solve(l, mid);
    solve(mid + 1, r);

    static Point t[NMAX];
    merge(a + l, a + mid + 1, a + mid + 1, a + r + 1, t, cmp_y);
    copy(t, t + r - l + 1, a + l);

    int tm = 0;
    for(int i = l; i <= r; ++i)
    if(abs(a[i].X - midx) < minn) {
        for(int j = tm - 1; j >= 0 && a[i].Y - t[j].Y < minn; --j)
            update(a[i], t[j]);
        t[tm++] = a[i];
    }
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen((NAME + ".inp").c_str(), "r", stdin);
    //freopen((name + ".out").c_str(), "w", stdout);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> a[i].X >> a[i].Y;
        a[i].ps = i;
    }
    sort(a, a + n, cmp_x);
    solve(0, n-1);
    if(s > t) swap(s, t);
    //cout << s << ' ' << t << ' ' << sqrt(minn);
    printf("%d %d %0.6f", s, t, sqrt(DB(minn)));
    return 0;
}
