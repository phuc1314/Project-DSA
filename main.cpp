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

// ============================================================
//  BIEN TOAN CUC
// ============================================================
ThongTinXe** p = nullptr;
int soHang = 0, soCot = 0;
HashTable    ht(101);
LinkedList   dsChoTrong;

// ============================================================
//  <= 4h: 6.000d | 4-8h: 12.000d | 8-16h: 22.000d | >16h: 32.000d
// ============================================================
long long tinhTien(long long in, long long out) {
    long long d = out - in;
    double g = d * 1.0 / 3600;
    if (g <= 4)              return 6000;
    else if (g <= 8)         return 12000;
    else if (g <= 16)        return 22000;
    else                     return 32000;
}

// ============================================================
//  GHI FILE (giu nguyen cua team, them kiem tra loi)
// ============================================================
void ghiFile(string tenFile) {
    ofstream file(tenFile);
    if (!file) { cout << "  [!] Loi ghi file!\n"; return; }
    file << soHang << " " << soCot << endl;
    for (int i = 0; i < soHang; i++)
        for (int j = 0; j < soCot; j++)
            if (p[i][j].getBienSo() != "")
                file << p[i][j].getBienSo() << " "
                     << char('A' + i) << " "
                     << j + 1        << " "
                     << p[i][j].getTimeIn() << endl;
    file.close();
}

// ============================================================
//  DOC FILE — xay dung lai mang 2D + HashTable + LinkedList
// ============================================================
bool docFile(string tenFile) {
    ifstream file(tenFile);
    if (!file) return false;

    int n, m;
    if (!(file >> n >> m)) return false;

    // Giai phong bo nho cu
    if (p != nullptr) {
        for (int i = 0; i < soHang; i++) delete[] p[i];
        delete[] p;
    }
    soHang = n; soCot = m;

    // Cap phat mang 2D
    p = new ThongTinXe*[soHang];
    for (int i = 0; i < soHang; i++)
        p[i] = new ThongTinXe[soCot];

    // Danh dau o co xe
    bool** coDXe = new bool*[soHang];
    for (int i = 0; i < soHang; i++) {
        coDXe[i] = new bool[soCot];
        for (int j = 0; j < soCot; j++) coDXe[i][j] = false;
    }

    // Doc tung xe
    string bs; char hang; int viTri; long long tg;
    while (file >> bs >> hang >> viTri >> tg) {
        int hi = hang - 'A', vi = viTri - 1;
        if (hi < 0 || hi >= soHang || vi < 0 || vi >= soCot) continue;
        ThongTinXe xe(bs, hang, viTri, tg);
        p[hi][vi] = xe;
        ht.insert(xe);
        coDXe[hi][vi] = true;
    }
    file.close();

    // Xay dung LinkedList cho trong theo thu tu A->Z, 1->soCot
    for (int i = 0; i < soHang; i++)
        for (int j = 0; j < soCot; j++)
            if (!coDXe[i][j])
                dsChoTrong.add((char)('A' + i), j + 1);

    for (int i = 0; i < soHang; i++) delete[] coDXe[i];
    delete[] coDXe;
    return true;
}

// ============================================================
//  KHOI TAO BAI MOI
// ============================================================
void khoiTaoBai(int n, int m) {
    soHang = n; soCot = m;
    p = new ThongTinXe*[soHang];
    for (int i = 0; i < soHang; i++)
        p[i] = new ThongTinXe[soCot];
    for (int i = 0; i < soHang; i++)
        for (int j = 0; j < soCot; j++)
            dsChoTrong.add((char)('A' + i), j + 1);
}

// ============================================================
//  GUI XE (giu nguyen cua Dinh Hong Phuc, bo sung ghiFile)
// ============================================================
void guiXe() {
    string bs;
    cout << "  Nhap bien so: ";
    cin >> bs;

    // Kiem tra hop le
    if (bs.empty() || bs.size() > 15) {
        cout << "  [!] Bien so khong hop le!\n"; return;
    }

    // 1. Kiem tra xe da trong bai chua — HashTable O(1)
    ThongTinXe tmp;
    if (ht.find(bs, tmp)) {
        cout << "  [!] Xe dang o trong bai!\n"; return;
    }

    // 2. Lay cho trong gan nhat — LinkedList O(1)
    char hang; int viTri;
    if (!dsChoTrong.getFirst(hang, viTri)) {
        cout << "  [!] Bai da day!\n"; return;
    }

    // 3. Thoi gian vao
    long long timeIn = time(0);

    // 4. Tao xe va cap nhat 3 CTDL
    ThongTinXe xe(bs, hang, viTri, timeIn);
    ht.insert(xe);                          // HashTable
    p[hang - 'A'][viTri - 1] = xe;          // Mang 2D

    // 5. Ghi file
    ghiFile("DemoData_Nhom05.txt");

    // 6. Thong bao
    time_t t = timeIn;
    tm* now = localtime(&t);
    cout << "\n  Xe da gui tai hang " << hang
         << ", vi tri " << viTri
         << ". Thoi gian vao: "
         << setfill('0')
         << setw(2) << now->tm_hour << ":"
         << setw(2) << now->tm_min  << ":"
         << setw(2) << now->tm_sec  << "\n";
}

// ============================================================
//  TRA XE (giu nguyen cua Ha Ngoc Phuc)
// ============================================================
void traXe() {
    string bs;
    cout << "  Nhap bien so: ";
    cin >> bs;

    // Tim trong HashTable — O(1) trung binh
    ThongTinXe xe;
    if (!ht.find(bs, xe)) {
        cout << "  [!] Khong tim thay xe!\n"; return;
    }

    long long timeIn  = xe.getTimeIn();
    long long timeOut = time(0);
    long long tien    = tinhTien(timeIn, timeOut);

    time_t t1 = timeIn;  tm* in  = localtime(&t1);
    int h1=in->tm_hour, m1=in->tm_min, s1=in->tm_sec;
    time_t t2 = timeOut; tm* out = localtime(&t2);

    cout << "\n  ===== HOA DON =====\n";
    cout << "  Bien so      : " << xe.getBienSo() << "\n";
    cout << "  Vi tri       : " << xe.getHang() << xe.getViTri() << "\n";
    cout << "  Thoi gian vao: "
         << setfill('0') << setw(2) << h1 << ":"
         << setw(2) << m1 << ":" << setw(2) << s1 << "\n";
    cout << "  Thoi gian ra : "
         << setfill('0') << setw(2) << out->tm_hour << ":"
         << setw(2) << out->tm_min << ":" << setw(2) << out->tm_sec << "\n";
    cout << "  Tien         : " << tien << " dong\n";
    cout << "  ===================\n";

    // Cap nhat 3 CTDL
    ht.remove(bs);                                       // HashTable
    p[xe.getHang()-'A'][xe.getViTri()-1] = ThongTinXe(); // Mang 2D
    dsChoTrong.addSorted(xe.getHang(), xe.getViTri());   // LinkedList

    ghiFile("DemoData_Nhom05.txt");
    cout << "  Tra xe thanh cong!\n";
}

// ============================================================
//  XEM CHO TRONG
// ============================================================
void xemChoTrong() {
    cout << "  Cho trong hien tai: ";
    dsChoTrong.hienThi();
}

// ============================================================
//  SINH DU LIEU TEST (cua team, dung de danh gia hieu nang)
// ============================================================
string sinhBienSo(int i) {
    return to_string(10 + i % 90) + char('A' + i % 26)
           + "-" + to_string(10000 + i);
}

void sinhTestData(string tenFile, int soLuong) {
    ofstream file(tenFile);
    if (!file) { cout << "Loi tao file!\n"; return; }
    file << 5 << " " << (soLuong / 5 + 1) << "\n";
    for (int i = 0; i < soLuong; i++) {
        file << sinhBienSo(i) << " "
             << char('A' + i % 5) << " "
             << i % (soLuong / 5 + 1) + 1 << " "
             << 1700000000 + i << "\n";
    }
    file.close();
}

// ============================================================
//  DANH GIA HIEU NANG
//  Thu nghiem voi bo du lieu kich thuoc khac nhau
//  So sanh LinkedList vs HashTable
// ============================================================
void danhGiaHieuNang() {
    cout << "\n  Dang thu nghiem voi cac bo du lieu khac nhau...\n";

    int sizes[] = {100, 500, 1000, 5000, 10000};
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
        long long llThem = duration_cast<microseconds>(t2-t1).count();

        // --- LinkedList: tim (getFirst n/2 lan) ---
        LinkedList ll2;
        for (int i = 0; i < n; i++)
            ll2.add((char)('A' + i % 26), i % 99 + 1);
        char h; int v;
        auto t3 = high_resolution_clock::now();
        for (int i = 0; i < n/2; i++) ll2.getFirst(h, v);
        auto t4 = high_resolution_clock::now();
        long long llTim = duration_cast<microseconds>(t4-t3).count();

        // --- HashTable: them ---
        HashTable htTest(101);
        auto t5 = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            ThongTinXe xe(sinhBienSo(i),
                          (char)('A' + i%26),
                          i%99+1,
                          1700000000LL + i);
            htTest.insert(xe);
        }
        auto t6 = high_resolution_clock::now();
        long long htThem = duration_cast<microseconds>(t6-t5).count();

        // --- HashTable: tim ---
        string target = sinhBienSo(n/2);
        ThongTinXe found;
        auto t7 = high_resolution_clock::now();
        htTest.find(target, found);
        auto t8 = high_resolution_clock::now();
        long long htTim = duration_cast<microseconds>(t8-t7).count();

        cout << setfill(' ') << left
             << setw(10) << n
             << setw(18) << llThem
             << setw(18) << llTim
             << setw(15) << htThem
             << setw(15) << htTim << "\n";

        // Sinh TestData tuong ung
        sinhTestData("TestData_Nhom05_" + to_string(n) + ".txt", n);
    }

    cout << string(74, '=') << "\n";
    cout << "\n  KET LUAN:\n"
         << "  + Linked List : Them O(1) | Tim O(n) -> cham dan khi N tang.\n"
         << "  + Hash Table  : Them O(1) | Tim O(1) -> nhanh, on dinh.\n"
         << "  => Dung HashTable de TRA CUU xe (find theo bien so).\n"
         << "  => Dung LinkedList de quan ly CHO TRONG (getFirst O(1)).\n"
         << string(74, '=') << "\n";
}

// ============================================================
//  IN MENU
// ============================================================
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

// ============================================================
//  MAIN
// ============================================================
int main() {
    // Thu tai DemoData truoc, neu khong co thi khoi tao moi
    if (!docFile("DemoData_Nhom05.txt")) {
        cout << "Khong co file luu. Khoi tao bai moi.\n";
        int n = 3, m = 5;
        cout << "Nhap so hang (1-26)        : "; cin >> n;
        if (n < 1) n = 1; if (n > 26) n = 26;
        cout << "Nhap so vi tri/hang (1-99) : "; cin >> m;
        if (m < 1) m = 1; if (m > 99) m = 99;
        khoiTaoBai(n, m);
    } else {
        cout << "Da tai du lieu tu 'DemoData_Nhom05.txt'.\n";
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
