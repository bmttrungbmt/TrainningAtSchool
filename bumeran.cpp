#include <bits/stdc++.h>
#define f1(i,n) for (int i=1; i<=n; i++)
#define f0(i,n) for (int i=0; i<n; i++)
#define fi first
#define se second
#define sz size()
#define pb push_back

using namespace std;
typedef double DB;
typedef long long LL;
const long long MOD = 1e9 +7;
const long long NMAX = 1e6 + 7;
const string NAME = "bumeran";
template <class T> int getbit(T x,int y) {return x >> (y-1) & 1;}
template <class T> T offbit(T x, int y) {return x | 1 <<(y-1);}
template <class T> T onbit(T x, int y) {return x & (~1<<(y-1));}
template <class T> T sqr(T x) {return x*x;}
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

typedef vector<int> vi;
const int BASE=10;

void fix(vi &a){
    a.push_back(0);
    f0(i,a.size()-1) {
        a[i+1]+=a[i]/BASE; a[i]%=BASE;
        if (a[i]<0) { a[i]+=BASE; a[i+1]--; }
    }
    while (a.size()>=2 && a.back()==0) a.pop_back();
}

void operator += (vi &a, const vi &b) {
    a.resize(max(a.size(), b.size()));
    f0(i,b.size()) a[i]+=b[i];
    fix(a);
}

vi operator * (const vi &a, const vi &b){
    vi c(a.size()+b.size());
    f0(i,a.size()) f0(j,b.size()) c[i+j]+=a[i]*b[j];
    return fix(c), c;
}

vi to_vi(int x) // x<BASE
    { return vi(1,x); }

void operator -= (vi &a, const vi &b)
    { f0(i,b.size()) a[i]-=b[i]; fix(a); }
void operator *= (vi &a, int x) // x<BASE
    { f0(i,a.size()) a[i]*=x; fix(a); }
vi operator + (vi a, const vi &b)
    { a+=b; return a; }
vi operator - (vi a, const vi &b)
    { a-=b; return a; }
vi operator * (vi a, int x) // x<BASE
    { a*=x; return a; }

bool operator < (const vi &a, const vi &b){
    if (a.size() != b.size()) return a.size()<b.size();
    for (int i=a.size()-1; i>=0; i--)
    if (a[i]!=b[i]) return a[i]<b[i];
    return false;
}

void divide(const vi &a, int x, vi &q, int &r) {
    q.clear(); r=0;
    for (int i=a.size()-1; i>=0; i--) {
        r=r*BASE+a[i];
        q.push_back(r/x); r%=x;
    }
    reverse(q.begin(), q.end());
    fix(q);
}

vi operator / (const vi &a, int x)
    { vi q; int r; divide(a, x, q, r); return q; }
int operator % (const vi &a, int x)
    { vi q; int r; divide(a, x, q, r); return r; }

istream& operator >> (istream& cin, vi &a){
    string s; cin >> s;
    a.clear(); a.resize(s.size()/4+1);
    f0(i,s.size()) {
        int x = (s.size()-1-i)/4; // <- log10(BASE)=4
        a[x]=a[x]*10+(s[i]-'0');
    }
    return fix(a), cin;
}

ostream& operator << (ostream& cout, const vi &a){
    printf("%d", a.back());
    for (int i=(int)a.size()-2; i>=0; i--)
    printf("%d", a[i]);
    return cout;
}

string s;
vi f[500][4];

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen((NAME + ".inp").c_str(), "r", stdin);
    freopen((NAME + ".out").c_str(), "w", stdout);
    cin >> s;
    f[0][0].push_back(1);
    //f[0][0] = 1;
    for(int step = 0; step < s.sz; ++step) {
        if(s[step] == 'F') {
            for(int i = s.sz; i > 0; --i) {
                f[i][2] = f[i][2] + f[i][0];
                f[i][0] = f[i-1][1] + f[i-1][0];
                f[i][3] = f[i][1] + f[i][3];
                f[i][1].clear();
                //f[i][1] = 0;
            }
            f[0][3] = f[0][3] + f[0][1];
            f[0][2] = f[0][2] + f[0][0];
            f[0][0].clear(); f[0][1].clear();
            //f[0][0] = f[0][1] = 0;
        } else {
            for(int i = 0; i < s.sz; ++i) {
                f[i][3] = f[i][2] * (i > 0) + f[i][3];
                f[i][1] = f[i][0] * (i > 0) + f[i][1];
                f[i][0] = f[i+1][0] + f[i+1][2] + f[i][0] * (i == 0);
                if(i > 0)
                f[i][2].clear();
                //f[i][2] = 0;
            }
            f[s.sz][3] = f[s.sz][3] + f[s.sz][2];
            f[s.sz][1] = f[s.sz][1] + f[s.sz][0];
            f[s.sz][0].clear(); f[s.sz][2].clear();
            //f[s.sz][0] = f[s.sz][2] = 0;
        }
    }
    //cerr << f[0][0] << endl;
    vi tmp; tmp.push_back(1);
    //int tmp = 1;
    vi res; res.clear();
    for(int i = 0; i <= 3; ++i) res = res + f[0][i];
    //cout << f[0][0] + f[0][1] + f[0][2] + f[0][3] - tmp;
    cout << res - tmp;
    return 0;
}
