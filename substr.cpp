#include <bits/stdc++.h>
using namespace std;

const int maxn = 100002;

string s;
int gap, sa[maxn], lcp[maxn], tmp[maxn], pos[maxn];

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
            lcp[i] = k;
            if (k)
                --k;
        }
    }
}

void solve() {
    int64_t res = 1LL * s.size() * (s.size() + 1) / 2;
    for (int i=0; i<s.size(); ++i) {
        res -= lcp[i];
    }
    cout << res;
}

int main() {
    freopen("substr.inp", "r", stdin);
    freopen("substr.out", "w", stdout);
    cin >> s;
    //cerr << s << '\n';
    buildSA();
    buildLCP();
    solve();
}
