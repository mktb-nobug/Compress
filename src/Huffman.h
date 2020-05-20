//
// Created by mktb-gnome on 5/17/20.
//

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

const int the_int_max = 0x7fffffff;

struct HTNode {
    int weight;     //权值
    int parent;     //父节点
    int lchild;     //左孩子
    int rchild;     //右孩子
};

class HuffmanTree {
private:
    HTNode* hT;
    char** hTCode;
    int nodeNum;
public:
    HuffmanTree(int n) {
        nodeNum = n;
        hT = new HTNode[2 * n];
        hTCode = new char* [n + 1];
        HTNode* p = hT;
        for (int i = 1; i <= 2 * n - 1; ++i, ++p) {
            *p = { 0, 0, 0, 0 };
        }
    }

    HuffmanTree(int* weights, int n);

    HuffmanTree(const HuffmanTree& oldT);

    ~HuffmanTree() {
        delete[] hT;
        for (int i = 1; i < nodeNum + 1; ++i) {
            delete[] hTCode[i];
        }
        delete[] hTCode;
    };

    HuffmanTree& operator=(const HuffmanTree& oldT);

    void selectTwo(int n, int& a1, int& a2);

    void huffmanCoding(int);

    int getWeight(int);
    char* getHuffmanCode(int);
    int getNodeNum();

    int getChild(int, char);
};

#endif //HUFFMAN_HUFFMAN_H
