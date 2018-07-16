#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()

using namespace std;
typedef double DB;
typedef long long LL;
typedef pair<LL, LL> pLL;
const LL MOD = 1e9+7;
const LL NMAX = 1e6+7;
const string name = "rafting";
template <class T> T sqr(T x) {return x * x;}

struct Point{
    DB X, Y;
    DB dis_PvP(const Point &p) {
        return sqrt((p.X - X) * (p.X - X) + (p.Y - Y) * (p.Y - Y));
    }
};

struct Line{
    DB A, B, C;
    DB dis_LvP(const Point &p) {
        return fabs(A * p.X + B * p.Y + C) / sqrt(A * A + B * B);
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

DB Calc(Point x, Point a, Point b) {
    Line line = make_line(a, b);
    DB dis = line.dis_LvP(x);
    DB disa = x.dis_PvP(a);
    DB disb = x.dis_PvP(b);
    DB ab = a.dis_PvP(b);
    DB u = sqrt(sqr(disa) - sqr(dis));
    DB v = sqrt(sqr(disb) - sqr(dis));
    if(fabs(u + v - ab) <= 1e-9) return dis;
    return min(disa, disb);
}

int n, m;
Point outrd[NMAX], inrd[NMAX];
DB res;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen((name + ".inp").c_str(), "r", stdin);
    //freopen((name + ".out").c_str(), "w", stdout);
    int T; cin >> T;
    while(T--) {
        res = 10000;
        cin >> n;
        for(int i = 1; i <= n; ++i) cin >> outrd[i].X >> outrd[i].Y;
        cin >> m;
        for(int i = 1; i <= m; ++i) cin >> inrd[i].X >> inrd[i].Y;
        outrd[n + 1] = outrd[1];
        inrd[m + 1] = inrd[1];
        for(int i = 1; i <= m; ++i)
        for(int j = 1; j <= n; ++j) {
            res = min(res, Calc(inrd[i], outrd[j], outrd[j + 1]));
            res = min(res, Calc(outrd[j], inrd[i], inrd[i + 1]));
        }
        //cerr << Calc(outrd[1], inrd[4], inrd[5]) << endl;
        printf("%0.7f\n", res/2);
    }
    return 0;
}
