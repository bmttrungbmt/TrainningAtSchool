#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef double DB;
typedef long long LL;
typedef pair <DB, DB> pdd;
const LL MOD = 1e9+7;
const LL Nmax = 1e6+7;
const string name = "apple";

pdd p1, p2, p3, p;
int n, res;

DB sqr(DB x) {return x * x;}

DB area(pdd A, pdd B, pdd C) {
    return fabs(A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y)) / 2;
}

int cw(pdd p1, pdd p2, pdd p3) {
    //return (p1.X - p3.X) * (p2.Y - p3.Y) - (p2.X - p3.X) * (p1.Y - p3.Y);
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen((name + ".inp").c_str(), "r", stdin);
    //freopen((name + ".out").c_str(), "w", stdout);
    cin >> p1.X >> p1.Y;
    cin >> p2.X >> p2.Y;
    cin >> p3.X >> p3.Y;
    DB s = area(p1, p2, p3);
    printf("%0.1f\n", s);
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        DB s1, s2, s3;
        cin >> p.X >> p.Y;
        s1 = area(p, p1, p2);
        s2 = area(p, p2, p3);
        s3 = area(p, p1, p3);
        //cout << s1 + s2 + s3 - s << endl;
        if((s1 + s2 + s3 - s) == 0) res++;
    }
    printf("%d", res);
    return 0;
}
