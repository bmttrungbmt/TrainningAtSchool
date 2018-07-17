#include <bits/stdc++.h>
using namespace std;

const int maxn = 100002;

string s;
int n, gap, k, sa[maxn], lcp[maxn], tmp[maxn], pos[maxn];
deque<int> dq;

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

int main() {
    freopen("reps.inp", "r", stdin);
    freopen("reps.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> s >> k;
    n = s.size();
    buildSA();
    buildLCP();
    int res = 0, pos = 0;
    for (int i=0; i<n; ++i) {
        if (i+1>=k && lcp[dq.front()]>res) {
            res = lcp[dq.front()];
            pos = sa[i];
        }
        while (dq.size() && lcp[dq.back()]>lcp[i])
            dq.pop_back();
        dq.push_back(i);
        while (i-dq.front()+1>=k)
            dq.pop_front();
    }
    for (int i=pos; i<=pos+res-1; ++i)
        cout << s[i];
}
