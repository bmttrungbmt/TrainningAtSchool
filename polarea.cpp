#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef double DB;
typedef long long LL;
typedef pair<DB, DB> pdd;
const LL MOD = 1e9+7;
const LL NMAX = 1e6+7;
const string name = "polarea";

int n;
pdd a[NMAX];
DB S;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen((name + ".inp").c_str(), "r", stdin);
    //freopen((name + ".out").c_str(), "w", stdout);
    while(cin >> n) {
        if(n == 0) return 0;
        S = 0;
        for(int i = 1; i <= n; ++i)
            cin >> a[i].X >> a[i].Y;
        a[n + 1] = a[1];
        for(int i = 1; i <= n; ++i)
            S += (a[i + 1].X - a[i].X) * (a[i + 1].Y + a[i].Y);
        S /= 2;
        if(S < 0) printf("CCW %0.1f\n", abs(S));
        else printf("CW %0.1f\n", abs(S));
    }
    return 0;
}
