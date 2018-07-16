#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef double DB;
const LL MOD = 1e9+7;
const DB EPS = 1e-9;
const LL NMAX = 1e6+7;
const string NAME = "mosqui";

struct Point {
    DB X, Y;
};
Point operator + (const Point &a, const Point &b) {
    Point c;
    c.X = a.X + b.X;
    c.Y = a.Y + b.Y;
    return c;
}
Point operator - (const Point &a, const Point &b) {
    Point c;
    c.X = a.X - b.X;
    c.Y = a.Y - b.Y;
    return c;
}
DB abs(Point a) {
    return sqrt(a.X * a.X + a.Y * a.Y);
}
Point normalize(Point a, DB d) {
    Point b;
    b.X = a.X * d / abs(a);
    b.Y = a.Y * d / abs(a);
    //cerr << a.X * d / abs(a) << ' ' << a.Y * d / abs(a) << endl;
    //cerr << b.X << ' ' << b.Y << endl;
    return b;
}
Point rotatePoint(Point a) {
    Point b;
    b.Y = a.X;
    b.X = -a.Y;
    return b;
}

struct Circle {
    Point P;
    DB R;
};
Circle makeCircle(Point a, DB b) {
    Circle rs;
    rs.P = a;
    rs.R = b;
    return rs;
}

int intersect(Circle A, Circle B, Point & res1 , Point & res2) {
    double d = abs(B.P - A.P);
    if (A.R + B.R <   d - EPS || d < abs(A.R - B.R) - EPS){
        return  0;
    }
    double a = (A.R * A.R - B.R * B.R + d * d) / (2 * d);
    double h = sqrt(A.R * A.R - a*a);
    //cerr << a << ' ' << h << ' ' << d << endl;
    Point v = normalize(B.P - A.P, a);
    //cerr << v.X << ' ' << v.Y << endl;
    Point u = normalize(rotatePoint(B.P - A.P), h);
    //cerr << u.X << ' ' << u.Y << endl;
    res1 = A.P + v + u;
    res2 = A.P + v - u;
    if (abs(u) < EPS){
        return  1;
    }
    return  2;
}

Point a[NMAX];
int n, res;
DB d;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen((NAME + ".inp").c_str(), "r", stdin);
    freopen((NAME + ".out").c_str(), "w", stdout);
    int T; cin >> T;
    while(T--) {
        cin >> n >> d;
        d /= 2;
        for(int i = 1; i <= n; ++i) cin >> a[i].X >> a[i].Y;
        Point p1, p2;
        res = 1;
        //Solve
        for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
        if(i != j) {
            int cs = intersect(makeCircle(a[i], d), makeCircle(a[j], d), p1, p2);
            //cerr << p1.X << ' ' << p1.Y << ' ' << p2.X << ' ' << p2.Y << endl;
            if(cs == 0) continue;
            int s1 = 0, s2 = 0;
            for(int k = 1; k <= n; ++k) {
                if(abs(p1 - a[k]) <= d) s1++;
                if(abs(p2 - a[k]) <= d) s2++;
            }
            res = max(res, max(s1, s2));
            //cerr << s1 << ' ' << s2 << ' ' << i << ' ' << j << endl;
        }
        cout << res << endl;
        //.
        //intersect(makeCircle(a[1], d), makeCircle(a[3], d), p1, p2);
        //cerr << p1.X << ' ' << p1.Y << ' ' << p2.X << ' ' << p2.Y;
    }
    return 0;
}
