#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef double DB;
const LL MOD = 1e9+7;
const LL NMAX = 500;
const string NAME = "cntab1";

string s;
int n, a[NMAX][NMAX], b[NMAX][NMAX], cl[5][NMAX * 2], res;

int dfs(int u, int type) {
    int ans = 0;
    if(u <= n) {
        for(int j = 1; j <= n; ++j)
        if(a[u][j] != -1) {
            int clv, v;
            v = j + n;
            clv = (a[u][j] + b[u][j] + cl[type][u]) % 2;
            if(cl[type][v] != -1) {
                if(cl[type][v] != clv) return INT_MAX;
            } else {
                cl[type][v] = clv;
                ans += clv;
                int tmp = dfs(v, type);
                if(tmp == INT_MAX) return INT_MAX;
                ans += tmp;
            }
        }
    } else {
        for(int i = 1; i <= n; ++i)
        if(a[i][u - n] != -1) {
            int clv, v;
            v = i;
            clv = (a[i][u - n] + b[i][u - n] + cl[type][u]) % 2;
            if(cl[type][v] != -1) {
                if(cl[type][v] != clv) return INT_MAX;
            } else {
                cl[type][v] = clv;
                ans += clv;
                int tmp = dfs(v, type);
                if(tmp == INT_MAX) return INT_MAX;
                ans += tmp;
            }
        }
    }
    return ans;
}

bool init() {
    for(int i = 1; i <= 2*n; ++i)
        cl[1][i] = cl[2][i] = cl[3][i] = -1;
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j) {
        if((a[i][j] == 0 && b[i][j] != 0) || (a[i][j] != 0 && b[i][j] == 0)) return false;

        if(a[i][j] == -1) a[i][j] = 0;
        else if(a[i][j] == 0) a[i][j] = -1;
        if(b[i][j] == 0) b[i][j] = -1;
        else if(b[i][j] == -1) b[i][j] = 0;
    }
    //for(int i = 1; i <= n; ++i) { for(int j = 1; j <= n; ++j) cerr << a[i][j] << ' '; cerr << endl;} cerr << endl;
    //for(int i = 1; i <= n; ++i) { for(int j = 1; j <= n; ++j) cerr << b[i][j] << ' '; cerr << endl;} cerr << endl;
    return true;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen((NAME + ".inp").c_str(), "r", stdin);
    freopen((NAME + ".out").c_str(), "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
        cin >> a[i][j];
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
        cin >> b[i][j];
    if(!init()) {cout << -1; return 0;}
    int res = 0;
    for(int i = 1; i <= 2*n; ++i)
    if(cl[3][i] == -1) {
        cl[1][i] = 0;
        int rs1 = dfs(i, 1);
        if(rs1 == INT_MAX) {cout << -1; return 0;}

        cl[2][i] = 1;
        int rs2 = dfs(i, 2) + 1;
        if(rs2 == INT_MAX) {cout << -1; return 0;}

        for(int j = 1;  j <= 2*n; ++j)
        if(cl[1][j] != -1 && cl[3][j] == -1)
            cl[3][j] = (rs1 < rs2 ? cl[1][j] : cl[2][j]);
        res += min(rs1, rs2);
    }
    cout << res << endl;
    for(int i = 1; i <= 2*n; ++i)
    if(cl[3][i] == 1) {
        if(i <= n) cout << "1 " << i << endl;
        if(i > n) cout << "2 " << i - n << endl;
    }
    //for(int i = 1; i <= 2*n; ++i) cerr << cl[1][i] << ' ' << cl[2][i] << ' ' << cl[3][i] << endl;
    return 0;
}
