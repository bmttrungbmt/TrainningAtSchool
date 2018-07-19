#include <bits/stdc++.h>

using namespace std;
const string NAME = "cntab1";

bool copyFile(const char *SRC, const char* DEST)
{
    std::ifstream src(SRC, std::ios::binary);
    std::ofstream dest(DEST, std::ios::binary);
    dest << src.rdbuf();
    return src && dest;
}
bool copyTest(int i) {
    string FileIn, FileOu;
    string iTest = "";

    //transform i to number of test
    //change this code depend on type of numbering in tests
    while(i > 0) {
        iTest = char(i%10 + '0') + iTest;
        i /= 10;
    }
    while(iTest.size() < 3) iTest = '0' + iTest;
    //.

    //copy test
    FileIn = "CNTab1/test" + iTest + "/CNTab1.inp";
    FileOu = "cntab1.inp";
    if(copyFile(FileIn.c_str(), FileOu.c_str()) == 0) {
        cout << "Copy file error!";
        return 0;
    }
    //.
    return 1;
}

int n, a[500][500], b[500][500], cnt;

bool check() {
    freopen("cntab1.inp", "r", stdin);
    cin >> n;
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j) cin >> a[i][j];
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j) cin >> b[i][j];
    fclose(stdin);
    freopen("cntab1.out", "r", stdin);
    cin >> cnt;
    if(cnt > 100) return false;
    if(cnt < 0) {
        cout << "test -1" << endl;
        return false;
    }
    while(cnt--) {
        int x, y;
        cin >> x >> y;
        if(x == 1) {
            for(int i = 1; i <= n; ++i) {
                if(a[y][i] == -1) a[y][i] = 1;
                else if(a[y][i] == 1) a[y][i] = -1;
            }
        } else {
            for(int i = 1; i <= n; ++i) {
                if(a[i][y] == -1) a[i][y] = 1;
                else if(a[i][y] == 1) a[i][y] = -1;
            }
        }
    }
    fclose(stdin);
    //for(int i = 1; i <= n; ++i) {for(int j = 1; j <= n; ++j) cerr << a[i][j] << ' '; cerr << endl;} cerr << endl;
    //for(int i = 1; i <= n; ++i) {for(int j = 1; j <= n; ++j) cerr << b[i][j] << ' '; cerr << endl;} cerr << endl;
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
    if(a[i][j] != b[i][j]) return false;
    return true;
}

int main()
{
    srand(time(NULL));
    for(int i = 1; i <= 100; ++i) {
        if(!copyTest(i)) return 0;
        system(("./" + NAME).c_str());
        if(!check())
        {
            cout << "Test " << i << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << i << ": CORRECT!\n";
    }
    return 0;

}
