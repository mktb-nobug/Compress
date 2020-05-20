//
// Created by mktb-gnome on 5/17/20.
//

#include <cstring>
#include "Huffman.h"


void HuffmanTree::selectTwo(int n, int& a1, int& a2) {
    int min1 = the_int_max;
    int min2 = the_int_max;

    for (int i = 1; i <= n; ++i) {
        if (hT[i].parent == 0 && hT[i].weight < min1) {
            min1 = hT[i].weight;
            a1 = i;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (i == a1) {
            continue;
        }
        if (hT[i].parent == 0 && hT[i].weight < min2) {
            min2 = hT[i].weight;
            a2 = i;
        }
    }
}

HuffmanTree::HuffmanTree(int* weights, int n) {
    nodeNum = n;
    hT = new HTNode[2 * n];
    hTCode = new char* [n + 1];
    HTNode* p = hT + 1;
    int i, a1 = -1, a2 = -1;
    for (i = 1; i <= n; ++i, ++p, ++weights) {
        *p = { *weights, 0, 0, 0 };
    }
    for (; i < 2 * n; ++i, ++p) {
        *p = { 0, 0, 0, 0 };
    }
    for (i = n + 1; i < 2 * n; ++i) {
        selectTwo(i - 1, a1, a2);
        hT[a1].parent = i;
        hT[a2].parent = i;
        hT[i].lchild = a1;
        hT[i].rchild = a2;
        hT[i].weight = hT[a1].weight + hT[a2].weight;
    }
    huffmanCoding(n);
}



HuffmanTree& HuffmanTree::operator=(const HuffmanTree& oldT) {
    if (this != &oldT) {
        if (hT != nullptr) {
            delete[] hT;
            hT = nullptr;
        }

        if (hTCode != nullptr) {
            for (int i = 1; i < nodeNum + 1; ++i) {
                delete[] hTCode[i];
            }
            delete[] hTCode;
            hTCode = nullptr;
        }

        nodeNum = oldT.nodeNum;
        hT = new HTNode[2 * nodeNum];
        hTCode = new char* [nodeNum + 1];
        for (int i = 1; i < 2 * nodeNum; ++i) {
            hT[i] = oldT.hT[i];
        }
        for (int j = 1; j < nodeNum + 1; ++j) {
            strcpy_s(hTCode[j], strlen(oldT.hTCode[j]) + 1, oldT.hTCode[j]);
        }
    }
    return *this;
}

int HuffmanTree::getWeight(int i) {
    return hT[i].weight;
}

void HuffmanTree::huffmanCoding(int n) {
    char* code = new char[n];
    code[n - 1] = '\0';
    int i, j, fath, start;
    char ch = 0;
    for (i = 1; i <= n; i++) {
        start = n - 1;
        for (j = i, fath = hT[i].parent; fath != 0; j = fath, fath = hT[fath].parent) {
            if (hT[fath].lchild == j) {
                code[--start] = '0';
            }
            else {
                code[--start] = '1';
            }
        }
        hTCode[i] = new char[n - start];
        strcpy_s(hTCode[i], strlen(&code[start]) + 1, &code[start]);
    }
    delete[] code;
}

char* HuffmanTree::getHuffmanCode(int i) {
    return hTCode[i];
}

int HuffmanTree::getNodeNum() {
    return nodeNum;
}

HuffmanTree::HuffmanTree(const HuffmanTree& oldT) {
    nodeNum = oldT.nodeNum;
    hT = new HTNode[2 * nodeNum];
    hTCode = new char* [nodeNum + 1];
    for (int i = 1; i < 2 * nodeNum; ++i) {
        hT[i] = oldT.hT[i];
    }
    for (int j = 1; j < nodeNum + 1; ++j) {
        hTCode[j] = new char[strlen(oldT.hTCode[j])];
        strcpy_s(hTCode[j], strlen(oldT.hTCode[j]) + 1, oldT.hTCode[j]);
    }
}

int HuffmanTree::getChild(int i, char c) {
    if (c == '0' && hT[i].lchild != 0) {
        return hT[i].lchild;
    }
    else if (c == '1' && hT[i].rchild != 0) {
        return hT[i].rchild;
    }
    return 0;
}
