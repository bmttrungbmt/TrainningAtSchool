#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()

using namespace std;
typedef double DB;
typedef long long LL;
typedef pair <int, int> pii;
const LL MOD = 1e9+7;
const LL NMAX = 1e6+7;
const string name = "bulb";

int n, m, k;
pii trace[NMAX];
vector <int> res;
vector <pii> a[NMAX];
string s, t;

void Bfs(int rt) {
    queue <int> qu;
    memset(trace, 0, sizeof(trace));
    qu.push(rt);
    trace[rt].fi = -1;
    int rs = -1;
    while(!qu.empty()) {
        int u = qu.front(); qu.pop();
        for(int i = 0; int v = a[u][i].fi; ++i)
        if(trace[v].fi == 0) {
            trace[v].fi = u;
            trace[v].se = a[u][i].se;
            qu.push(v);
            if(s[v-1] != t[v-1]) {
                rs = v;
                break;
            }
        }
        if(rs != -1) break;
    }
    if(rs != -1) {
        s[rs - 1] = t[rs - 1];
        s[rt - 1] = t[rt - 1];
        int u = rs;
        while(trace[u].fi > -1) {
            res.push_back(trace[u].se);
            u = trace[u].fi;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
    cin >> n >> m >> k;
    cin  >> s >> t;
    for(int i = 1; i <= k; ++i) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(pii(v + n, i));
        a[v + n].push_back(pii(u, i));
    }
    for(int i = 1; i <= n + m; ++i) a[i].push_back(pii(0, 0));
    for(int i = 1; i <= n + m; ++i)
    if(s[i-1] != t[i-1]) Bfs(i);
    if(s != t) {
        cout << -1;
    } else {
        cout << res.sz << endl;
        for(int i = 0; i < res.sz; ++i) cout << res[i] << ' ';
    }
    return 0;
}
