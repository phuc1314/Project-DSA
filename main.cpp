#include <iostream>
#include <fstream>
#include <cstdlib>
#include"ThongTinXe.h"
#include "HashTable.h"
#include "LinkedList.h"
#include <iomanip>
#include <ctime>

using namespace std;

ThongTinXe** p;
int soHang = 0, soCot = 0;
HashTable ht(101);
LinkedList dsChoTrong;

string sinhBienSo() {
    return to_string(rand() % 90 + 10) + char('A' + rand() % 26) + "-" + to_string(rand() % 90000 + 10000);
}

// sinh dữ liệu test
void sinhData(string tenFile, int n, int m, int soLuong) {
    ofstream file(tenFile);

    if (!file) {
        cout << "Loi mo file!\n";
        return;
    }

    file << n << " " << m << endl;

    for (int i = 0; i < soLuong; i++) {
        string bs = sinhBienSo();
        char hang = 'A' + rand() % n;
        int vitri = rand() % m + 1;
        long long t = 1700000000 + rand() % 100000;

        file << bs << " " << hang << " " << vitri << " " << t << endl;
    }

    file.close();
}

void ghiFile(string tenFile) {
    ofstream file(tenFile);
    file << soHang << " " << soCot << endl;

    for (int i = 0; i < soHang; i++) {
        for (int j = 0; j < soCot; j++) {
            if (p[i][j].getBienSo() != "") {
                file << p[i][j].getBienSo() << " "
                    << char('A' + i) << " "
                    << j + 1 << " "
                    << p[i][j].getTimeIn() << endl;
            }
        }
    }

    file.close();
}

long long tinhTien(long long in, long long out) {
    long long d = out - in;
    double g = d * 1.0/ 3600;

    if (g <= 4) {
        return 6000;
    }
    else if (g > 4 && g <= 8) {
        return 12000;
    }
    else if(g > 8 && g <= 16){
        return 22000;
    }
    else {
        return 32000;
    }
}

void traXe() {
    string bs;
    cout << "Nhap bien so: ";
    cin >> bs;

    ThongTinXe xe;

    if (!ht.find(bs, xe)) {
        cout << "Khong tim thay xe!\n";
        return;
    }
    long long timeIn = xe.getTimeIn();
    time_t t = timeIn;
    tm* in = localtime(&t);

    long long timeOut = time(0);
    time_t t2 = timeOut;
    tm* out = localtime(&t2);

    long long tien = tinhTien(xe.getTimeIn(), timeOut);

    cout << "\n===== HOA DON =====\n";
    cout << "Bien so: " << xe.getBienSo() << endl;
    cout << "Vi tri: " << xe.getHang() << xe.getViTri() << endl;
    cout << "Thoi gian vao: " << in->tm_hour << ":" << in->tm_min << ":" << in->tm_sec  << endl;
    cout << "Thoi gian ra: " << out->tm_hour << ":" << out->tm_min << ":" << out->tm_sec << endl;
    cout << "Tien: " << tien << endl;

    ht.remove(bs);
    p[xe.getHang() - 'A'][xe.getViTri() - 1] = ThongTinXe();
    dsChoTrong.addSorted(xe.getHang(), xe.getViTri());
    ghiFile("DemoData_MaNhom.txt");
    cout << "Tra xe thanh cong!\n";
}

// Ham gui xe
void guiXe() {
    string bs;
    cout << "Nhap bien so: ";
    cin >> bs;

    // 1. kiem tra trung
    ThongTinXe tmp;
    if (ht.find(bs, tmp)) {
        cout << "Xe dang o trong bai!\n";
        return;
    }

    // 2. lay cho trong gan nhat
    char hang;
    int viTri;

    if (!dsChoTrong.getFirst(hang, viTri)) {
        cout << "Bai da day!\n";
        return;
    }

    // 3. thoi gian vao
    long long timeIn = time(0);

    // 4. tao xe
    ThongTinXe xe(bs, hang, viTri, timeIn);

    // 5. luu vao hash table
    ht.insert(xe);

    // 6. cap nhat mang 2D
    p[hang - 'A'][viTri - 1] = xe;

    // 7. ghi file 
    ghiFile("DemoData_MaNhom.txt");

    // 8. tgian dang HH:MM:SS
    time_t t = timeIn;
    tm* now = localtime(&t);

    cout << "\nXe da gui tai hang " << hang
        << ", vi tri " << viTri
        << ". Thoi gian vao: "
        << setfill('0')
        << setw(2) << now->tm_hour << ":"
        << setw(2) << now->tm_min << ":"
        << setw(2) << now->tm_sec
        << endl;
}

int main() {

    return 0;
}
