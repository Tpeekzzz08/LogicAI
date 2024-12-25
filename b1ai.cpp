#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cctype>
#include <sstream>

using namespace std;

bool BieuThucHL(const string& Bieuthuc) {
    stack<char> s;
    for (char ch : Bieuthuc) {
        if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            if (s.empty())
                return false;
            s.pop();
        }
    }
    return s.empty();
}

bool DanhGiaBT(const string& BieuThuc, const unordered_map<char, bool>& giatri) {
    stack<bool> s;
    for (char ch : BieuThuc) {
        if (isalpha(ch)) {
            s.push(giatri.at(ch));
        } else if (ch == '¬') {
            bool gt = s.top(); s.pop();
            s.push(!gt);
        } else if (ch == '∧' || ch == 'V' || ch == '-') {
            bool b = s.top(); s.pop();
            bool a = s.top(); s.pop();
            if (ch == '∧') s.push(a && b);
            else if (ch == 'V') s.push(a || b);
            else if (ch == '-') {
                s.pop(); 
                bool b = s.top(); s.pop();
                bool a = s.top(); s.pop();
                s.push(!a || b);
            }
        }
    }
    return s.top();
}

int main() {
    string BieuThuc;
    cout << "Nhap bieu thuc logic: ";
    getline(cin, BieuThuc);

    int n;
    cout << "Nhap so luong bien: ";
    cin >> n;
    unordered_map<char, bool> giatri;
    for (int i = 0; i < n; ++i) {
        char bien;
        string giatri_str;
        cout << "Nhap bien thu " << i + 1 << ": ";
        cin >> bien;
        cout << "Nhap gia tri (True/False) cua bien " << bien << ": ";
        cin >> giatri_str;
        giatri[bien] = (giatri_str == "True");
    }

    if (!BieuThucHL(BieuThuc)) {
        cout << "Bieu thuc khong hop le!" << endl;
        return 1;
    }

    bool kq = DanhGiaBT(BieuThuc, giatri);
    cout << "Ket qua bieu thuc: " << (kq ? "True" : "False") << endl;

    return 0;
}