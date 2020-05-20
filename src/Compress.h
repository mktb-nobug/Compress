//
// Created by mktb-gnome on 5/17/20.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include "Huffman.h"

struct HEAD {
    char type[4];       //�ļ�����
    int length;         //ԭ�ļ�����
    int weight[256];    //Ȩֵ��ֵ
};

char str2byte(const char* pStr);

int Compress(const char*, HuffmanTree&);

int Encode(const char*, HuffmanTree&, char*, const int);

int WriteFile(const char*, const HEAD, const char*, const int);

int InitHead(const char*, HEAD&);

#endif //HUFFMAN_COMPRESS_H
