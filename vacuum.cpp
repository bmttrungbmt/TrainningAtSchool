#include <bits/stdc++.h>
#define PI 3.141592653589793238462643383279502884

using namespace std;
typedef double DB;
typedef long long LL;
const LL MOD = 1e9+7;
const LL Nmax = 1e6+7;
const string name = "vacuum";

int T, n;
DB x, y, radnow;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen((name + ".inp").c_str(), "r", stdin);
    //freopen((name + ".out").c_str(), "w", stdout);
    cin >> T;
    while(T--) {
        x = y = 0;
        radnow = 90;
        cin >> n;
        for(int i = 1; i <= n; ++i) {
            DB rad, dis;
            cin >> rad >> dis;
            if(rad < 0) rad += 360;
            radnow += rad;
            x += cos(radnow * PI/180) * dis;
            y += sin(radnow * PI/180) * dis;
        }
        printf("%0.8f %0.8f\n", x, y);
    }
    return 0;
}
