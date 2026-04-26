#pragma once
#include <iostream>
using namespace std;

class Node {
public:
    char hang;
    int viTri;
    Node* next;

    Node(char h, int v) {
        hang = h;
        viTri = v;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    // Khoi tao
    void add(char h, int v) {
        Node* newNode = new Node(h, v);

        if (!head) {
            head = newNode;
            return;
        }

        Node* cur = head;
        while (cur->next) cur = cur->next;

        cur->next = newNode;
    }

    // Lay cho trong gan nhat
    bool getFirst(char& h, int& v) {
        if (!head) return false;

        Node* temp = head;
        h = temp->hang;
        v = temp->viTri;

        head = head->next;
        delete temp;
        return true;
    }

    // Them lai cho trong co sap xep
    void addSorted(char h, int v) {
        Node* newNode = new Node(h, v);

        // chèn đầu nếu nhỏ hơn head
        if (!head || (h < head->hang) ||
            (h == head->hang && v < head->viTri)) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* cur = head;

        while (cur->next &&
            (cur->next->hang < h ||
                (cur->next->hang == h && cur->next->viTri < v))) {
            cur = cur->next;
        }

        newNode->next = cur->next;
        cur->next = newNode;
    }

    // Hien thi danh sach trong
    void hienThi() {
        if (!head) {
            cout << "Bai da day!\n";
            return;
        }

        Node* cur = head;
        while (cur) {
            cout << cur->hang << cur->viTri << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};