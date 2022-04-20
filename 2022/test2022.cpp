//
// Created by Tou on 2022/3/15.
//

#include "ctime"
#include "iostream"

using namespace std;

string abc() {
    string a = "2321";
    return a;
}
typedef struct {
    string hour;
}TT;
int main() {
    time_t now_time;
    now_time = time(nullptr);
    cout << ctime(&now_time);
    for (int i = 0; i < 2; ++i) {
        string b = abc();
//        TT *t = (TT *) malloc(sizeof (TT));
        TT *t =new TT;
        t->hour = b;
        cout << t->hour;
    }
    return 0;
}