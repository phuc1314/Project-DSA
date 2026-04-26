#include<iostream>
#include"ThongTinXe.h"
#include "HashTable.h"
#include "LinkedList.h"
#include <iomanip>
using namespace std;

ThongTinXe** p;

HashTable ht(101);

LinkedList dsChoTrong;

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

#include <ctime>

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
    ghiFile("data.txt");

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