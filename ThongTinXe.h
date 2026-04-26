#pragma once
#include <string>
using namespace std;

class ThongTinXe {
private:
    string bienSo;
    char hang;
    int viTri;
    long long timeIn;

public:
    ThongTinXe(string bs = "", char h = 'A', int vt = -1, long long t = 0) {
        bienSo = bs;
        hang = h;
        viTri = vt;
        timeIn = t;
    }

    string getBienSo() const { return bienSo; }
    char getHang() const { return hang; }
    int getViTri() const { return viTri; }
    long long getTimeIn() const { return timeIn; }

    void set(string bs, char h, int vt, long long t) {
        bienSo = bs;
        hang = h;
        viTri = vt;
        timeIn = t;
    }
};