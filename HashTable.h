#pragma once
#include "ThongTinXe.h"

class HashTable {
private:
    struct Node {
        ThongTinXe data;
        Node* next;
    };

    int size;
    Node** table;

    int hashFunc(const string& key) const {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % size;
    }

public:
    HashTable(int s = 101) {
        size = s;
        table = new Node * [size];
        for (int i = 0; i < size; i++)
            table[i] = nullptr;
    }

    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Node* cur = table[i];
            while (cur) {
                Node* t = cur;
                cur = cur->next;
                delete t;
            }
        }
        delete[] table;
    }

    bool find(const string& bs, ThongTinXe& out) const {
        int i = hashFunc(bs);
        Node* cur = table[i];

        while (cur) {
            if (cur->data.getBienSo() == bs) {
                out = cur->data;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    bool insert(const ThongTinXe& xe) {
        ThongTinXe tmp;
        if (find(xe.getBienSo(), tmp)) return false;

        int i = hashFunc(xe.getBienSo());
        Node* p = new Node{ xe, table[i] };
        table[i] = p;
        return true;
    }

    bool remove(const string& bs) {
        int i = hashFunc(bs);
        Node* cur = table[i];
        Node* prev = nullptr;

        while (cur) {
            if (cur->data.getBienSo() == bs) {
                if (!prev) table[i] = cur->next;
                else prev->next = cur->next;

                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }
};