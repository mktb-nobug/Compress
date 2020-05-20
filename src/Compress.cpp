//
// Created by mktb-gnome on 5/17/20.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include "Compress.h"

using namespace std;

char str2byte(const char* pStr) {
    unsigned char b = 0x00;
    for (int i = 0; i < 8; ++i) {
        b = b << 1;
        if (pStr[i] == '1') {
            b = b | 0x01;
        }
    }
    return b;
}

int Compress(const char* pFilename, HuffmanTree& ht) {
    int nSize = 0;
    int n = ht.getNodeNum();
    for (int i = 1; i <= n; ++i) {
        nSize += ht.getWeight(i) * strlen(ht.getHuffmanCode(i));
    }
    nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
    char* pBuffer;
    pBuffer = new char[nSize];
    Encode(pFilename, ht, pBuffer, nSize);
    HEAD sHead;
    InitHead(pFilename, sHead);
    int newSize = WriteFile(pFilename, sHead, pBuffer, nSize);
    delete[] pBuffer;
    cout << "ѹ��ǰ��С��" << sHead.length << "�ֽ�" << endl;
    cout << "ѹ�����С��" << newSize << "�ֽ�" << endl;
    cout << "ѹ��������" << newSize * 1.0 / sHead.length * 100 << "%" << endl;
    return 0;
}

int Encode(const char* pFilename, HuffmanTree& ht, char* pBuffer, const int nSize) {

    char cd[256] = { 0 };
    int pos = 0;
    int length = 0;
    char ch;

    ifstream fin;
    fin.open(pFilename, ios::in | ios::binary);

    if (!fin.is_open()) {
        cout << "ѹ������ʱ�ļ���ʧ�ܣ�����" << endl;
        return 0;
    }

    while (fin.read(&ch, 1)) {
        strcat_s(cd, ht.getHuffmanCode((unsigned char)ch + 1));

        while (strlen(cd) >= 8) {
            pBuffer[pos++] = str2byte(cd);
            for (int i = 0; i < 248; ++i) {
                cd[i] = cd[i + 8];
            }
        }
    }

    if (strlen(cd) > 0) {
        pBuffer[pos++] = str2byte(cd);
    }

    fin.close();

    return 0;
}

int InitHead(const char* pFilename, HEAD& sHead) {
    //��ʼ���ļ�ͷ
    strcpy_s(sHead.type, "huf");
    sHead.length = 0;
    for (int& i : sHead.weight) {
        i = 0;
    }

    ifstream fin;
    fin.open(pFilename, ios::in | ios::binary);

    if (!fin.is_open()) {
        cout << "��ʼ���ļ�ͷʱ�ļ���ʧ�ܣ�����" << endl;
        return 0;
    }

    char ch;
    while (fin.read(&ch, 1)) {
        sHead.weight[(unsigned char)ch]++;
        sHead.length++;
    }

    fin.close();
    return 0;
}

int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize) {
    //�����ļ���
    char filename[256] = { 0 };
    strcpy_s(filename, pFilename);
    strcat_s(filename, ".huf");

    //�Զ���������ʽ���ļ�
    ofstream fout;
    fout.open(filename, ios::out | ios::binary);

    if (!fout.is_open()) {
        cout << "д�ļ�ʱ�ļ���ʧ�ܣ�����" << endl;
        return 0;
    }

    //д�ļ�ͷ
    fout.write((char*)&sHead, sizeof(HEAD));
    //дѹ����ı���
    fout.write(pBuffer, sizeof(char) * nSize);

    fout.close();
    cout << "����ѹ���ļ���" << filename << endl;
    int len = sizeof(HEAD) + nSize;

    return len;
}
