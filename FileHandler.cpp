#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Xe {
    string bienso;
    char hang;
    int vitri;
    long long thoigian;
};

// Đọc file dữ liệu
bool docFile(const string& tenFile, int &n, int &m, vector<Xe> &ds) {
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong mo duoc file!\n";
        return false;
    }

    file >> n >> m;

    Xe x;
    while (file >> x.bienso >> x.hang >> x.vitri >> x.thoigian) {
        ds.push_back(x);
    }

    file.close();
    return true;
}

// Ghi file dữ liệu
bool ghiFile(const string& tenFile, int n, int m, const vector<Xe> &ds) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << "Loi ghi file!\n";
        return false;
    }

    file << n << " " << m << endl;

    for (auto &x : ds) {
        file << x.bienso << " "
             << x.hang << " "
             << x.vitri << " "
             << x.thoigian << endl;
    }

    file.close();
    return true;
}

// Test nhanh
int main() {
    int n, m;
    vector<Xe> ds;

    if (docFile("TestData_Nhom05.txt", n, m, ds)) {
        cout << "Doc file thanh cong!\n";
        cout << "So hang: " << n << ", so vi tri: " << m << endl;

        for (auto &x : ds) {
            cout << x.bienso << " " << x.hang << x.vitri << endl;
        }
    }

    return 0;
}
