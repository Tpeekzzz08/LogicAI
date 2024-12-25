#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

bool BieuThucHL(const string& BieuThuc) {
    stack<char> s;
    for (char ch : BieuThuc) {
        if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

bool DanhGiaBT(const string& BieuThuc, const unordered_map<char, bool>& giatri){
    stack<bool> s;
    for (char ch : BieuThuc) {
        if (isalpha(ch)) {
            s.push(giatri.at(ch));
        } else if (ch == '¬') {
            bool gt = s.top(); s.pop();
            s.push(!gt);
        } else if (ch == '∧' || ch == '∨' || ch == '->') {
            bool b = s.top(); s.pop();
            bool a = s.top(); s.pop();
            if (ch == '∧') {
                s.push(a && b);
            } else if (ch == '∨') {
                s.push(a || b);
            } else if (ch == '->') {
                s.pop();
                bool b = s.top(); s.pop();
                bool a = s.top(); s.pop();
                s.push(!a || b);
            }
        }
    }
    return s.top();
}

vector<char> TimBien(const string& BieuThuc){
    vector<char> Bien;
    for (char ch : BieuThuc) {
        if (isalpha(ch) && find(Bien.begin(), Bien.end(), ch) == Bien.end()) {
            Bien.push_back(ch);
        }
    }
    return Bien;
}

void InBangChanLy(const string& BieuThuc){
    if (!BieuThucHL(BieuThuc)){
        cout << "Bieu thuc khong hop le!" << endl;
        return;
    }

    vector<char> Bien = TimBien(BieuThuc);
    int SLbien = Bien.size();
    int SLhang = pow(2, SLbien);

    for (char var : Bien) {
        cout << var << " ";
    }
    cout << "Ket qua" << endl;

    for (int i = 0; i < SLhang; ++i) {
        unordered_map<char, bool> giatri;
        for (int j = 0; j < SLbien; ++j) {
            giatri[Bien[j]] = (i & (1 << j)) != 0;
            cout << (giatri[Bien[j]] ? "T " : "F ");
        }
        bool result = DanhGiaBT(BieuThuc, giatri);
        cout << (result ? "T" : "F") << endl;
    }
}

int main() {
    string BieuThuc;
    cout << "Nhap bieu thuc logic: ";
    getline(cin, BieuThuc);
    InBangChanLy(BieuThuc);

    return 0;
}
