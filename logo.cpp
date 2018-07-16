#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef double DB;
const LL MOD = 1e9+7;
const LL NMAX = 1e6+7;
const DB PI = acos(-1);
const string NAME = "logo";

int T, n;
DB x, y, radnow;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen((NAME + ".inp").c_str(), "r", stdin);
    //freopen((NAME + ".out").c_str(), "w", stdout);
    cin >> T;
    while(T--) {
        x = y = 0.0f;
        radnow = 90;
        cin >> n;
        for(int i = 1; i <= n; ++i) {
            string type;
            DB val;
            cin >> type >> val;
            if(type == "lt") radnow += val;
            if(type == "rt") radnow -= val;
            if(type == "fd") {
                x += cos(radnow * PI/180) * val;
                y += sin(radnow * PI/180) * val;
            }
            if(type == "bk") {
                x -= cos(radnow * PI/180) * val;
                y -= sin(radnow * PI/180) * val;
            }
        }
        printf("%0.0f \n", sqrt(x*x + y*y));
    }
    return 0;
}
