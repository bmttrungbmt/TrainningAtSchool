#include <bits/stdc++.h>
using namespace std;

const int maxn = 100002;

string s, t;
int gap, sa[maxn], lcp[maxn], tmp[maxn], pos[maxn];
vector<pair<char, int> > p;

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

void solve_encrypt() {
    t.clear();
    s = '@' + s;
    buildSA();
    for (int i=0; i<s.size(); ++i)
        t += s[(sa[i]-1+s.size())%s.size()];
    cout << t << '\n';
}

void dfs(int u, bool fi) {
    if (s[u]=='@' && !fi)
        return;
    if (s[u]!='@')
        cout << s[u];
    dfs(p[u].second, false);
}

void solve_decrypt() {
    p.clear();
    for (int i=0; i<s.size(); ++i)
        p.push_back(make_pair(s[i], i));
    sort(p.begin(), p.end());
    for (int i=0; i<s.size(); ++i)
        if (s[i]=='@')
            dfs(i, true);
    cout << '\n';
}

int main() {
    freopen("bwt.inp", "r", stdin);
    freopen("bwt.out", "w", stdout);
    while (cin >> s) {
        bool encr = true;
        //cerr << s << '\n';
        for (int i=0; i<s.size(); ++i)
            if (s[i]=='@')
                encr = false;
        if (encr)
            solve_encrypt();
        else
            solve_decrypt();
    }
}
