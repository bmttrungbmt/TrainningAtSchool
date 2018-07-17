#include <bits/stdc++.h>
using namespace std;

const int maxn = 100002;
const int MOD = 1000000007;
const int offset = 100000;

string s, A, B;
int gap, sa[maxn], lcp[maxn], tmp[maxn], pos[maxn];
int f[maxn], ps[maxn], p[22][maxn], _prev[maxn+offset];

bool sufCmp(int i, int j) {
    if (pos[i]!=pos[j])
        return pos[i]<pos[j];
    i += gap;
    j += gap;
    return (i<s.size() && j<s.size()) ? pos[i]<pos[j] : i>j;
}

void buildSA() {
    for (int i=0; i<s.size(); ++i) {
        sa[i] = i;
        pos[i] = s[i];
    }
    for (gap = 1; ; gap *= 2) {
        sort(sa, sa+s.size(), sufCmp);
        for (int i=1; i<s.size(); ++i)
            tmp[i] = tmp[i-1] + sufCmp(sa[i-1], sa[i]);
        for (int i=0; i<s.size(); ++i)
            pos[sa[i]] = tmp[i];
        if (tmp[s.size()-1]==s.size()-1)
            return;
    }
};

void buildLCP() {
    for (int i=0, k=0; i<s.size(); ++i) {
        if (pos[i]!=s.size()-1) {
            int j = sa[pos[i]+1];
            while (i+k<s.size() && j+k<s.size() && s[i+k]==s[j+k])
                ++k;
            lcp[pos[i]] = k;
            if (k)
                --k;
        }
    }
}

int get(int l, int r) {
    if (l>r)
        return 0;
    return ps[l] - ps[r] + 1;
}

int binaryJump(int i, int l) {
    for (int k=19; k>=0; --k)
        if (p[k][i]!=-1 && p[k][i]-1<=l)
            i = p[k][i];
    while (p[0][i]!=-1 && i-1<=l)
        i = p[0][i];
    if (i-1<=l)
        return maxn;
    return i;
}

void solve() {
    memset(_prev, 0, sizeof(_prev));
    _prev[0+offset] = s.size();
    f[s.size()] = -1;
    ps[s.size()] = 1;
    memset(p, -1, sizeof(p));
    int cnt = 0;
    //cerr << s << '\n';
    for (int i=(int)s.size()-1; i>=0; --i) {
        cnt += (s[i]=='(' ? 1 : -1);
        ps[i] = ps[_prev[cnt+offset]] + 1;
        if (s[i]==')' || _prev[cnt+offset]==0) {
            f[i] = -1;
            p[0][i] = -1;
        }
        else {
            f[i] = max(_prev[cnt+offset], f[_prev[cnt+offset]]);
            p[0][i] = _prev[cnt+offset];
        }
        for (int j=1; j<=19; ++j) {
            if (p[j-1][i]>-1)
                p[j][i] = p[j-1][p[j-1][i]];
            else
                p[j][i] = -1;
        }
        _prev[cnt+offset] = i;
    }
    int64_t res = 0;
    for (int i=0; i<s.size(); ++i) {
        res += get(binaryJump(sa[i], sa[i]+lcp[i]-1), f[sa[i]]);
    }
    cout << res << '\n';
}

int main() {
    freopen("parentheses.inp", "r", stdin);
    freopen("parentheses.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    while (cin >> s) {
        buildSA();
        buildLCP();
        solve();
    }
}
