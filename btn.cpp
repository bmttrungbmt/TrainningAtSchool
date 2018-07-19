#include <bits/stdc++.h>

using namespace std;
typedef double DB;
typedef long long LL;
const LL MOD = 1e9+7;
const LL NMAX = 101;
const string name = "btn";

LL n, k, res,type[NMAX], f[NMAX][NMAX][NMAX], s[NMAX][NMAX];

LL solve(int i, int j, int t) {
    if(f[i][j][t] > -1) return f[i][j][t];
    if(j < i) return 1;
    f[i][j][t] = 0;
    if(!t) return 0;
    f[i][j][t] += s[i][j] * solve(i + 1, j - 1, t - 1);
    //cerr << i << ' ' << j << ' ' << t << ' ' << f[i][j][t] << endl;
    for(int ii = i + 1; ii <= j - 2; ii += 2) {
        f[i][j][t] += s[i][ii] * solve(i + 1, ii - 1, t - 1) * solve(ii + 1, j, t);
    }
    return f[i][j][t];
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        char ckt;
        cin >> ckt;
        if(ckt == '(') type[i] = 1;
        if(ckt == ')') type[i] = -1;
        if(ckt == '[') type[i] = 2;
        if(ckt == ']') type[i] = -2;
        if(ckt == '{') type[i] = 3;
        if(ckt == '}') type[i] = -3;
        if(ckt == '?') type[i] = 0;
    }
    for(int i = 1; i <= n; ++i)
    for(int j = i + 1; j <= n; j += 1) {
        if(type[i] < 0 || type[j] > 0) {s[i][j] = 0; continue;}
        if(type[i] == 0 && type[j] == 0) {s[i][j] = 3; continue;}
        if(type[i] + type[j] == 0) {s[i][j] = 1; continue;}
        if(type[i] == 0 || type[j] == 0) s[i][j] = 1;
    }
    //cerr << s[3][4] << endl;
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
    for(int t = 0; t <= n; ++t)
        f[i][j][t] = -1;

    //cerr << solve(3, 6, k - 2) << endl;
    cout << solve(1, n, k) - solve(1, n, k - 1);
    return 0;
}
