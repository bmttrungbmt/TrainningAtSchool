#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x << " = " << x << '\n';
#define BP() cerr << "OK!\n";
#define PR(A, n) cerr << #A << " = "; for (int _=1; _<=n; ++_) cerr << A[_] << ' '; cerr << '\n';
#define PR0(A, n) cerr << #A << " = "; for (int _=0; _<n; ++_) cerr << A[_] << ' '; cerr << '\n';

const int maxn = 1000002;
const int64_t MOD = 1000000007;

int n, m, k;
string S, T;
int64_t H[maxn], HT, pw256[maxn];

struct fenwickTree {
	int b[maxn];

	void upd(int id) {
		for (; id<=n; id += id & (-id))
			++b[id];
	}

	int get(int id) {
		int res = 0;
		for (; id>0; id -= id & (-id))
			res += b[id];
		return res;
	}

	int get(int l, int r) {
		if (l>r)
			return 0;
		if (l==1)
			return get(r);
		return get(r) - get(l-1);
	}
} tr;

int64_t get_hash(int l, int r) {
	return (H[r] - H[l-1]*pw256[r-l+1] + MOD*MOD) % MOD;
}

int main() {
	freopen("swindow.inp", "r", stdin);
	freopen("swindow.out", "w", stdout);
	ios::sync_with_stdio(0); cin.tie(0);
	getline(cin, S);
	//cin.ignore();
	getline(cin, T);
	//cin.ignore();
	n = S.size(); m = T.size();
	S = '@' + S;
	T = '@' + T;
	cin >> k;
	//cerr << S << ' ' << T << ' ' << k << '\n';
	pw256[0] = 1;
	for (int i=1; i<=n; ++i) {
		H[i] = (H[i-1] * 256 + S[i]) % MOD;
		pw256[i] = pw256[i-1] * 256 % MOD;
	}
	for (int i=1; i<=m; ++i)
		HT = (HT * 256 + T[i]) % MOD;
	for (int i=1; i+m-1<=n; ++i)
		if (get_hash(i, i+m-1)==HT)
			tr.upd(i);
	int cnt = 0;
	for (int i=1; i+k-1<=n; ++i) {
		int j = i + k - 1;
		cnt += (tr.get(i, j-m+1)>0);
	}
	cout << cnt;
}
