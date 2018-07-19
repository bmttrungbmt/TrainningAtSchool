#include <bits/stdc++.h>

using namespace std;
const string NAME = "btn4";

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
    FileIn = "BTN4/test" + iTest + "/btn4.inp";
    FileOu = "btn4.inp";
    if(copyFile(FileIn.c_str(), FileOu.c_str()) == 0) {
        cout << "Copy file error!";
        return 0;
    }

    FileIn = "BTN4/test" + iTest + "/btn4.out";
    FileOu = "btn4.ans";
    if(copyFile(FileIn.c_str(), FileOu.c_str()) == 0) {
        cout << "Copy file error!";
        return 0;
    }
    return 1;
}
bool check() {
    return system(("diff " + NAME + ".out " + NAME + ".ans").c_str()) == 0;
}

int main()
{
    srand(time(NULL));
    for(int i = 1; i <= 8; ++i) {
        if(!copyTest(i)) return 0;
        system(("./" + NAME).c_str());
        if(check())
        {
            cout << "Test " << i << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << i << ": CORRECT!\n";
    }
    return 0;

}
