#include<iostream>
#include"ThongTinXe.h"
#include "HashTable.h"
using namespace std;

ThongTinXe** p;

HashTable ht(101);

long long tinhTien(long long in, long long out) {
    long long d = out - in;
    long long m = d / 60;

    if (m <= 30) {
        return 5000;
    }

    long long themGio = (m - 30) / 60;
    return 5000 + themGio * 10000;
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

    long long timeOut = time(0);

    long long tien = tinhTien(xe.getTimeIn(), timeOut);

    cout << "\n===== HOA DON =====\n";
    cout << "Bien so: " << xe.getBienSo() << endl;
    cout << "Vi tri: " << xe.getHang() << xe.getViTri() << endl;
    cout << "Thoi gian vao: " << xe.getTimeIn() << endl;
    cout << "Thoi gian ra: " << timeOut << endl;
    cout << "Tien: " << tien << endl;

    ht.remove(bs);

    p[xe.getHang() - 'A'][xe.getViTri() - 1] = ThongTinXe();


    cout << "Tra xe thanh cong!\n";
}

int main() {

    return 0;
}