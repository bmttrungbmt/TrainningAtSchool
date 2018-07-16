#include <bits/stdc++.h>
#define FOR(i, u, v) for(int i= u; i<=v; ++i)
#define FORD(i, u, v) for(int i = u; i>=v; --i)
#define fi first
#define se second
#define sz size()
#define pb push_back

using namespace std;
typedef double DB;
typedef long long LL;
const long long MOD = 1e9 +7;
const long long NMAX = 1e6 + 7;
const string NAME = "linegame";
template <class T> int getbit(T x,int y) {return x >> (y-1) & 1;}
template <class T> T offbit(T x, int y) {return x | 1 <<(y-1);}
template <class T> T onbit(T x, int y) {return x & (~1<<(y-1));}
template <class T> T sqr(T x) {return x*x;}
template <class T> void read_int(T &rs) {
    rs = 0;
    int neg = 1;
    char r;
    for(r = getchar(); r < '0' || r > '9'; r = getchar())
    if(r == '-') neg *= -1;
    rs = r - '0';
    for(r = getchar(); r >= '0' && r <= '9'; r = getchar())
    rs = rs*10 + (r - '0');
    rs *= neg;
}

struct Point{
    DB X, Y;
    DB dis_PvP(const Point &p) {
        return sqrt((p.X - X) * (p.X - X) + (p.Y - Y) * (p.Y - Y));
    }
};

struct Line{
    DB A, B, C;
    DB dis_LvP(const Point &p) {
        return (A * p.X + B * p.Y + C) / sqrt(A * A + B * B);
    }
    Point Intersection(const Line &a) {
        Point inter;
        DB D, Dx, Dy;
        D = A * a.B - B * a.A;
        Dx = a.C * B - C * a.B;
        Dy = C * a.A - a.C * A;
        if(D == 0) {
            if(Dx == 0 && Dy == 0) inter.X = inter.Y = FLT_MAX;
            else inter.X = inter.Y = -FLT_MAX;
        } else {
            inter.X = Dx / D;
            inter.Y = Dy / D;
        }
        return inter;
    }
};

Line make_line(Point a, Point b) {
    Line rs;
    rs.A = b.Y - a.Y;
    rs.B = a.X - b.X;
    rs.C = a.Y * b.X - a.X * b.Y;
    return rs;
}

int n;
DB p;
Point a[NMAX];

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen((NAME + ".inp").c_str(), "r", stdin);
    //freopen((NAME + ".out").c_str(), "w", stdout);
    srand(time(NULL));
    int T; read_int(T);
    while(T--) {
        read_int(n);
        read_int(p);
        for(int i = 1; i <= n; ++i)
        //cin >> a[i].X >> a[i].Y;
        {read_int(a[i].X); read_int(a[i].Y);}
        int ans = 0;
        for(int itest = 1; itest <= 500; ++itest) {
            int i = rand()%n + 1, j = rand()%n + 1;
            if(i == j) continue;
            int cnt = 0;
            if(j != i) {
                Line line  = make_line(a[i], a[j]);
                for(int t = 1; t <= n; ++t)
                if(abs(line.dis_LvP(a[t])) <= 1e-9) cnt++;
            }
            ans = max(ans, cnt);
        }
        if((ans / DB(n) * 100.0f) >= p) cout << "possible\n";
        else cout << "impossible\n";
    }
    return 0;
}
