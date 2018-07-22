#include <bits/stdc++.h>

using namespace std;
typedef int64_t LL;
typedef double DB;
typedef pair <LL, LL> pLL;
const LL MOD = 1e9+7;
const LL NMAX = 1e6+7;
const string NAME = "func";

ostream& operator << (ostream& cout, const vi &a){
    printf("%d", a.back());
    for (int i=(int)a.size()-2; i>=0; i--)
    printf("%02d", a[i]);
    return cout;
}

struct Data {
    LL x1, x2, x3, x4;
    Data() {}
    Data(LL x1, LL x2, LL x3, LL x4):
    x1(x1), x2(x2), x3(x3), x4(x4) {}
    void debug() {
        cout << x1 << ' ' << x2 << ' ' << x3 << ' ' << x4 << endl;
    }
};

LL k, r, mod;
LL p, q, num, den, vi0, via1, vi1, vir;
Data res, f[NMAX];

Data mul(Data a, Data b) {
    LL x, y, z, t;
    x = (b.x1 * a.x1 % mod + b.x3 * a.x2 % mod) % mod;
    y = (b.x2 * a.x1 % mod + b.x4 * a.x2 % mod) % mod;
    z = (b.x1 * a.x3 % mod + b.x3 * a.x4 % mod) % mod;
    t = (b.x2 * a.x3 % mod + b.x4 * a.x4 % mod) % mod;
    return Data(x, y, z, t);
}

LL gcd(LL x, LL y) {
    if(x < y) swap(x, y);
    LL tmp, r;
    while(y > vi0) {
        tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}

Data Pow(LL k, int r) {
    if(k < NMAX && f[k].x1 != -1) return f[k];
    if(k == 1) {
        return f[k] = Data(1, 0, 0, 1);
    }
    if(k == 2) {
        return f[k] = Data(0, 1, 1, r);
    }
    Data tmp = Pow(k/2, r);
    tmp = mul(tmp, tmp);
    tmp = mul(tmp, Data(0, 1, 1, r));
    if(k % 2 == 1) tmp = mul(tmp, Data(0, 1, 1, r));
    if(k < NMAX) f[k] = tmp;
    return tmp;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen((NAME + ".inp").c_str(), "r", stdin);
    freopen((NAME + ".out").c_str(), "w", stdout);
    while(cin >> k >> r >> p >> q >> mod) {
        LL d = gcd(p, q);
        p /= d;
        q /= d;
        for(int i = 0; i <= min(k, NMAX-1); ++i) f[i] = Data(-1, -1, -1, -1);
        res = Pow(k, r);
        num = (p * res.x1 % mod + q * res.x2 % mod);
        den = (p * res.x3 % mod + q * res.x4 % mod);
        //res.debug();
        //cerr << num << ' ' << den << ' ' << d << endl;
        cout << num % mod << ' ' << den % mod << '\n';
    }
    return 0;
}
