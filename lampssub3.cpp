#include <bits/stdc++.h>
#define sz size()

using namespace std;
typedef double DB;
typedef long long LL;
const LL MOD = 1e9+7;
const LL NMAX = 1e4;
const string name = "lamps";
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

int n, c[NMAX], tr[NMAX];
vector <int> f[NMAX][3][3], a[NMAX], way;

void dfs(int u, int par, int sta, int cl) {
    if(f[u][sta][cl].sz != 0) return;
    for(int i = 0; int v = a[u][i]; ++i)
    if(v != par) {
        dfs(v, u, 0, 0);
        dfs(v, u, 0, 1);
        dfs(v, u, 1, 0);
        dfs(v, u, 1, 1);
    }
    int cnt = abs((sta + c[u]) % 2 - cl);
    vector <int> tp0, tp1, tp01;
    tp0.clear(); tp1.clear(); tp01.clear();
    for(int i = 0; int v = a[u][i]; ++i)
    if(v != par) {
        if(f[v][0][1 - sta][0] != -1 && f[v][1][1 - sta][0] == -1) tp0.push_back(v);
        if(f[v][0][1 - sta][0] == -1 && f[v][1][1 - sta][0] != -1) tp1.push_back(v);
        if(f[v][0][1 - sta][0] != -1 && f[v][1][1 - sta][0] != -1) tp01.push_back(v);
    }
    //cerr << u << ' ' << sta << ' ' << cl << ' ' << cnt << endl;
    //cerr << tp0.sz << ' ' << tp1.sz << ' ' << tp01.sz << " " << a[u].sz << endl; cerr << endl;
    if(tp0.sz + tp1.sz + tp01.sz != a[u].sz - 1 - int(u != 1)) {
        f[u][sta][cl].push_back(-1);
        return;
    }
    if((tp1.sz) % 2 != cnt && tp01.sz == 0) {
        f[u][sta][cl].push_back(-1);
        return;
    }
    for(int i = 0; i < tp1.sz; ++i)
        f[u][sta][cl].push_back(tp1[i]);
    if(tp1.sz % 2 != cnt)
        f[u][sta][cl].push_back(tp01[0]);
    if(f[u][sta][cl].sz == 0) f[u][sta][cl].push_back(0);
    //cerr << f[u][sta][cl][0] << endl;
}

void CalcWay(int u, int par, int sta, int cl) {
    for(int i = 0; i < f[u][sta][cl].sz; ++i) {
        if(tr[f[u][sta][cl][i]] == 0 && f[u][sta][cl][i] != 0) way.push_back(f[u][sta][cl][i]);
        tr[f[u][sta][cl][i]] = 1;
    }
    for(int i = 0; int v = a[u][i]; ++i)
    if(v != par) {
        if(tr[v] == 0)
            CalcWay(v, u, 0, 1 - sta);
        else
            CalcWay(v, u, 1, 1 - sta);
    }
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
    int T;
    read_int(n); read_int(T);
    for(int i = 1; i < n; ++i) {
        int u, v;
        read_int(u); read_int(v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i = 1; i <= n; ++i) a[i].push_back(0);

    for(int itest = 1; itest <= T; ++itest) {
        for(int i = 1; i <= n; ++i) read_int(c[i]);
        for(int i = 1; i <= n; ++i)
        for(int sta = 0; sta <= 1; ++sta)
        for(int cl = 0; cl <= 1; ++cl)
            f[i][sta][cl].clear();
        memset(tr, 0 , sizeof(tr));
        way.clear();

        dfs(1, 1, 0, 1);
        if(f[1][0][1][0] !=  -1) {
            CalcWay(1, 1, 0, 1);
            cout << way.sz << ' ';
            for(int i = 0; i < way.sz; ++i) cout << way[i] << ' ';
            cout << '\n';
            continue;
        }

        dfs(1, 0, 1, 1);
        if(f[1][1][1][0] !=  -1) {
            way.push_back(1);
            CalcWay(1, 0, 1, 1);
            cout << way.sz << ' ';
            for(int i = 0; i < way.sz; ++i) cout << way[i] << ' ';
            cout << '\n';
            continue;
        } else cout << "-1\n";
    }
    return 0;
}
