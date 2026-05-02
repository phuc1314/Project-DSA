#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <string>
#include <limits>
#include "ThongTinXe.h"
#include "HashTable.h"
#include "LinkedList.h"

using namespace std;
using namespace chrono;

//  BIEN TOAN CUC
ThongTinXe** p = nullptr;
int soHang = 0, soCot = 0;
HashTable ht(3079);
LinkedList dsChoTrong;

//  SINH DU LIEU TEST (dung de danh gia hieu nang)
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

//KHOI TAO MANG 2D
void khoiTaoMang() {
    p = new ThongTinXe * [soHang];
    for (int i = 0; i < soHang; i++) {
        p[i] = new ThongTinXe[soCot];
    }
}

//TAO DANH SACH CHO TRONG
void khoiTaoChoTrong() {
    for (int i = 0; i < soHang; i++) {
        for (int j = 1; j <= soCot; j++) {
            dsChoTrong.addSorted(char('A' + i), j);
        }
    }
}

//  DOC FILE — xay dung lai mang 2D + HashTable + LinkedList
void docFile(string tenFile) {
    ifstream file(tenFile);

    if (!file) {
        cout << "Khong mo duoc file!\n";
        return;
    }

    file >> soHang >> soCot;

    // 1. cap phat mang
    khoiTaoMang();

    // 2. khoi tao danh sach trong FULL
    khoiTaoChoTrong();

    string bs;
    char hang;
    int viTri;
    long long timeIn;

    while (file >> bs >> hang >> viTri >> timeIn) {

        int row = hang - 'A';
        int col = viTri - 1;

        // validate
        if (row < 0 || row >= soHang || col < 0 || col >= soCot)
            continue;

        // tranh ghi de
        if (p[row][col].getBienSo() != "")
            continue;

        // tranh trung bien so
        ThongTinXe tmp;
        if (ht.find(bs, tmp))
            continue;

        // tao xe
        ThongTinXe xe(bs, hang, viTri, timeIn);

        // cap nhat mang
        p[row][col] = xe;

        // them vao hash
        ht.insert(xe);
    }

    file.close();

    // Build lại danh sách chỗ trống
    LinkedList newList;

    for (int i = 0; i < soHang; i++) {
        for (int j = 0; j < soCot; j++) {
            if (p[i][j].getBienSo() == "") {
                newList.addSorted(char('A' + i), j + 1);
            }
        }
    }

    dsChoTrong = newList; // overwrite list cũ
}

//  DEBUG MANG 
void debugMang() {
    cout << "\n=== TRANG THAI BAI XE ===\n";
    for (int i = 0; i < soHang; i++) {
        for (int j = 0; j < soCot; j++) {
            if (p[i][j].getBienSo() == "")
                cout << "[ ] ";
            else
                cout << "[X] ";
        }
        cout << endl;
    }
}

//  GHI FILE
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

//kiem tra bien so
bool kiemTraBienSo(string bs) {

    if (bs.length() == 0) return false;

    for (char c : bs) {
        if (c == ' ') return false;
    }

    if (bs.length() > 15) return false;

    if (bs.length() < 8 || bs.length() > 9) return false;
    if (!isdigit(bs[0]) || !isdigit(bs[1])) return false;
    if (!isalpha(bs[2])) return false;
    if (bs[3] != '-') return false;

    for (size_t i = 4; i < bs.length(); i++) {
        if (!isdigit(bs[i])) return false;
    }

    return true;
}

//  <= 4h: 6.000d | 4-8h: 12.000d | 8-16h: 22.000d | >16h: 32.000d
long long tinhTien(long long in, long long out) {
    long long d = out - in;
    double g = d * 1.0 / 3600;

    if (g <= 4) {
        return 6000;
    }
    else if (g > 4 && g <= 8) {
        return 12000;
    }
    else if (g > 8 && g <= 16) {
        return 22000;
    }
    else {
        return 32000;
    }
}

//  TRA XE
void traXe() {
    string bs;
    cout << "Nhap bien so: ";
    cin >> bs;

    if (!kiemTraBienSo(bs)) {
        cout << "Bien so khong hop le! Vui long nhap lai.\n";
        return;
    }

    ThongTinXe xe;

    if (!ht.find(bs, xe)) {
        cout << "Khong tim thay xe!\n";
        return;
    }
    long long timeIn = xe.getTimeIn();
    time_t t = timeIn;
    tm in;
    localtime_s(&in, &t);

    long long timeOut = time(0);
    time_t t2 = timeOut;
    tm out;
    localtime_s(&out, &t2);

    long long tien = tinhTien(xe.getTimeIn(), timeOut);

    cout << "\n===== HOA DON =====\n";
    cout << "Bien so: " << xe.getBienSo() << endl;
    cout << "Vi tri: " << xe.getHang() << xe.getViTri() << endl;
    cout << "Thoi gian vao: " << in.tm_hour << ":" << in.tm_min << ":" << in.tm_sec << endl;
    cout << "Thoi gian ra: " << out.tm_hour << ":" << out.tm_min << ":" << out.tm_sec << endl;
    cout << "Tien: " << tien << endl;

    ht.remove(bs);
    p[xe.getHang() - 'A'][xe.getViTri() - 1] = ThongTinXe();
    dsChoTrong.addSorted(xe.getHang(), xe.getViTri());
    ghiFile("DemoData_Nhom05.txt");
    cout << "Tra xe thanh cong!\n";
}

//  GUI XE
void guiXe() {
    string bs;
    cout << "Nhap bien so: ";
    cin >> bs;

    if (!kiemTraBienSo(bs)) {
        cout << "Bien so khong hop le! Vui long nhap lai.\n";
        return;
    }
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
    ghiFile("DemoData_Nhom05.txt");

    // 8. tgian dang HH:MM:SS
    time_t t = timeIn;
    tm now;
    localtime_s(&now, &t);

    cout << "\nXe da gui tai hang " << hang
        << ", vi tri " << viTri
        << ". Thoi gian vao: "
        << setfill('0')
        << setw(2) << now.tm_hour << ":"
        << setw(2) << now.tm_min << ":"
        << setw(2) << now.tm_sec
        << endl;
}


//  XEM CHO TRONG
void xemChoTrong() {
    cout << "\n=== DANH SACH CHO TRONG ===\n";
    dsChoTrong.hienThi();
}

//  DANH GIA HIEU NANG
//  So sanh LinkedList vs HashTable
void danhGiaHieuNang() {
    cout << "\n  Dang thu nghiem voi cac bo du lieu khac nhau...\n";

    int sizes[] = { 100, 500, 1000, 5000, 10000 };
    int k = 5;

    cout << "\n" << string(74, '=') << "\n";
    cout << "        BANG DANH GIA HIEU NANG (don vi: microseconds)\n";
    cout << string(74, '=') << "\n";
    cout << setfill(' ') << left
        << setw(10) << "N"
        << setw(18) << "LL-Them(us)"
        << setw(18) << "LL-Tim(us)"
        << setw(15) << "HT-Them(us)"
        << setw(15) << "HT-Tim(us)" << "\n";
    cout << string(74, '-') << "\n";

    for (int t = 0; t < k; t++) {
        int n = sizes[t];

        // --- LinkedList: them ---
        LinkedList ll;
        auto t1 = high_resolution_clock::now();
        for (int i = 0; i < n; i++)
            ll.add((char)('A' + i % 26), i % 99 + 1);
        auto t2 = high_resolution_clock::now();
        long long llThem = duration_cast<microseconds>(t2 - t1).count();

        // --- LinkedList: tim (getFirst n/2 lan) ---
        LinkedList ll2;
        for (int i = 0; i < n; i++)
            ll2.add((char)('A' + i % 26), i % 99 + 1);
        char h; int v;
        auto t3 = high_resolution_clock::now();
        for (int i = 0; i < n / 2; i++) ll2.getFirst(h, v);
        auto t4 = high_resolution_clock::now();
        long long llTim = duration_cast<microseconds>(t4 - t3).count();

        // --- HashTable: them ---
        HashTable htTest(101);
        auto t5 = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            ThongTinXe xe(sinhBienSo(),
                (char)('A' + i % 26),
                i % 99 + 1,
                1700000000LL + i);
            htTest.insert(xe);
        }
        auto t6 = high_resolution_clock::now();
        long long htThem = duration_cast<microseconds>(t6 - t5).count();

        // --- HashTable: tim ---
        string target = sinhBienSo();
        ThongTinXe found;
        auto t7 = high_resolution_clock::now();
        htTest.find(target, found);
        auto t8 = high_resolution_clock::now();
        long long htTim = duration_cast<microseconds>(t8 - t7).count();

        cout << setfill(' ') << left
            << setw(10) << n
            << setw(18) << llThem
            << setw(18) << llTim
            << setw(15) << htThem
            << setw(15) << htTim << "\n";

        // Sinh TestData tuong ung
       /* sinhData("TestData_Nhom05.txt", );*/
    }

    cout << string(74, '=') << "\n";
    cout << "\n  KET LUAN:\n"
        << "  + Linked List : Them O(1) | Tim O(n) -> cham dan khi N tang.\n"
        << "  + Hash Table  : Them O(1) | Tim O(1) -> nhanh, on dinh.\n"
        << "  => Dung HashTable de TRA CUU xe (find theo bien so).\n"
        << "  => Dung LinkedList de quan ly CHO TRONG (getFirst O(1)).\n"
        << string(74, '=') << "\n";
}

//  IN MENU
void inMenu() {
    cout << "\n" << string(44, '=') << "\n";
    cout << "       HE THONG QUAN LY BAI GIU XE\n";
    cout << string(44, '=') << "\n";
    cout << "  Bai xe: " << soHang << " hang x " << soCot << " vi tri\n";
    cout << string(44, '-') << "\n";
    cout << "  [1] Gui xe\n"
        << "  [2] Tra xe\n"
        << "  [3] Xem danh sach cho trong\n"
        << "  [4] Danh gia hieu nang\n"
        << "  [0] Thoat\n";
    cout << string(44, '=') << "\n";
    cout << "  Chon: ";
}

int main() {
    srand(time(0));
    sinhData("DemoData_Nhom05.txt", 5, 5, 5);
    docFile("DemoData_Nhom05.txt");

    if (soHang == 0 || soCot == 0) {
        cout << "\n=== TAO BAI XE MOI ===\n";
        cout << "Khong tim thay file hoac file bi loi!\n";
        cout << "Nhap so hang: ";
        cin >> soHang;
        cout << "Nhap so vi tri moi hang: ";
        cin >> soCot;

        khoiTaoMang();

        for (int i = 0; i < soHang; i++) {
            for (int j = 1; j <= soCot; j++) {
                dsChoTrong.addSorted(char('A' + i), j);
            }
        }

        ghiFile("DemoData_Nhom05.txt");
        cout << "Da tao bai xe moi " << soHang << "x" << soCot << "!\n";
    }
    int luaChon;
    do {
        inMenu();
        if (!(cin >> luaChon)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            luaChon = -1;
        }
        cout << "\n";
        switch (luaChon) {
        case 1: guiXe();           break;
        case 2: traXe();           break;
        case 3: xemChoTrong();     break;
        case 4: danhGiaHieuNang(); break;
        case 0:
            ghiFile("DemoData_Nhom05.txt");
            cout << "  Da luu. Tam biet!\n";
            break;
        default:
            cout << "  [!] Lua chon khong hop le!\n";
        }
    } while (luaChon != 0);

    // Giai phong bo nho
    for (int i = 0; i < soHang; i++) delete[] p[i];
    delete[] p;
    return 0;
}
