#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()

using namespace std;
typedef double DB;
typedef long long LL;
typedef pair<DB, DB> pLL;
const LL MOD = 1e9+7;
const LL Nmax = 1e6+7;
const DB PI = acos(-1);
const string name = "board";

bool cw(pLL a, pLL b, pLL c) { return a.fi*(b.se - c.se) + b.fi*(c.se - a.se) + c.fi*(a.se - b.se) < 0.0f; }
bool cww(pLL a, pLL b, pLL c) { return a.fi*(b.se - c.se) + b.fi*(c.se - a.se) + c.fi*(a.se - b.se) > 0.0f; }

bool cmp(pLL a, pLL b) {
    if(a.se != b.se) return a.se < b.se;
    return a.fi < b.fi;
}

void convex(vector<pLL> a, vector<pLL> &rs){
    sort(a.begin(), a.end(), cmp);
    pLL s, t;
    s = a[0]; t = a.back();
    vector<pLL> U, D;
    U.push_back(s); D.push_back(s);
    for(int i = 1; i < a.sz; ++i) {
        if(i == a.sz - 1 || cw(s, a[i], t)) {
            while(U.sz > 1 && !cw(U[U.sz - 2], U[U.sz - 1], a[i])) U.pop_back();
            U.push_back(a[i]);
        }
        if(i == a.sz - 1 || cww(s, a[i], t)) {
            while(D.sz > 1 && !cww(D[D.sz - 2], D[D.sz - 1], a[i])) D.pop_back();
            D.push_back(a[i]);
        }
    }
    for(int i = 0; i < D.sz; ++i) rs.push_back(D[i]);
    for(int i = int(U.sz) - 2; i >= 0; --i) rs.push_back(U[i]);
}

DB get_S(vector<pLL> rs){
    DB tmp = 0;
    for(int i = 0; i < (int)rs.sz - 1; ++i) tmp += (rs[i].fi - rs[i+1].fi) * (rs[i].se + rs[i+1].se);
    tmp += (rs[rs.sz - 1].fi - rs[0].fi) * (rs[rs.sz - 1].se + rs[0].se);
    tmp = abs(tmp);
    //if(tmp%2 == 0) cout<<tmp/2<<".0"<<endl;
    //else cout<<tmp/2<<".5"<<endl;
    return tmp;
}

int n;
DB S1, S2;
vector <pLL> a, rs;

void Process(DB x, DB y, DB w, DB h, DB v) {
    S1 += h * w;
    //printf("%0.8f\n", h * w);
    v = v / 180 * PI;
    DB sqrR = w/2*w/2 + h/2*h/2;
    DB ang = atan((h/2) / (w/2)); //cout << (h/2) / (w/2) << " " << ang << endl;
    DB tempt = PI - (ang + v);
    pLL pt;
    pt.fi = x + sqrt(sqrR) * cos(tempt);
    pt.se =  y + sqrt(sqrR) * sin(tempt);
    //cerr <<a.x << ' ' << a.y << endl;
    a.push_back(pt); ///trai tren

    tempt += 2 * ang;
    pt.fi = x + sqrt(sqrR) * cos(tempt);
    pt.se =  y + sqrt(sqrR) * sin(tempt);
    //cerr <<a.x << ' ' << a.y << endl;
    a.push_back(pt); ///trai duoi

    tempt += PI;
    pt.fi = x + sqrt(sqrR) * cos(tempt);
    pt.se =  y + sqrt(sqrR) * sin(tempt);
    //cerr <<a.x << ' ' << a.y << endl;
    a.push_back(pt); /// phai tren

    tempt -= 2 * ang;
    pt.fi = x + sqrt(sqrR) * cos(tempt);
    pt.se =  y + sqrt(sqrR) * sin(tempt);
    //cerr <<a.x << ' ' << a.y << endl;
    a.push_back(pt); /// phai duoi
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen((name + ".inp").c_str(), "r", stdin);
    //freopen((name + ".out").c_str(), "w", stdout);
    int T; cin >> T;
    while(T--) {
        a.clear();
        S1 = S2 = 0.0f;
        cin >> n;
        for(int i = 1; i <= n; ++i) {
            DB x, y, h, w, v;
            cin >> x >> y >> w >> h >> v;
            //cerr << x << ' ' << y << ' ' << w << ' ' << h  << ' ' << v << endl;
            Process(x, y, w, h, v);
        }
        convex(a, rs);
        S2 = get_S(rs) / 2;
        //printf("%0.6f \n", S1);
        //printf("%0.6f \n", S2);
        printf("%0.1f% \n", S1 / S2 * 100.0f);
    }
    return 0;
}
