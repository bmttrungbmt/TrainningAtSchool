#include <bits/stdc++.h>
using namespace std;

const int maxn = 200007;
const int MOD = 1000000000;

string s, A, B;
int gap, sa[maxn], lcp[maxn], tmp[maxn], pos[maxn];
int L[maxn], R[maxn], f[maxn], ps[maxn];

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
    r = min(r, (int)A.size());
    if (l>r)
        return 0;
    return (ps[l] - ps[r+1] + MOD) % MOD;
}

void init() {
    for (int i=1; i<s.size(); ++i) {
        if (sa[i]<A.size()) {
            if (sa[i-1]<A.size())
                L[i] = min(lcp[i-1], L[i-1]);
            else
                L[i] = lcp[i-1];
        }
    }
    for (int i=(int)s.size()-2; i>=0; --i) {
        if (sa[i]<A.size()) {
            if (sa[i+1]<A.size())
                R[i] = min(lcp[i], R[i+1]);
            else
                R[i] = lcp[i];
        }
    }
}

int main() {
    freopen("strgcut.inp", "r", stdin);
    freopen("strgcut.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> A >> B;
    s = A + '@' + B;
    buildSA();
    buildLCP();
    init();
    //cerr << s << '\n';
    f[A.size()] = ps[A.size()] = 1;
    for (int i=A.size()-1; i>=0; --i) {
        f[i] = get(i+1, i+max(L[pos[i]], R[pos[i]]));
        ps[i] = (ps[i+1] + f[i]) % MOD;
    }
    cout << f[0];
}
