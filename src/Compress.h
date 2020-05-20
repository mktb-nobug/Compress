//
// Created by mktb-gnome on 5/17/20.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include "Huffman.h"

struct HEAD {
    char type[4];       //文件类型
    int length;         //原文件长度
    int weight[256];    //权值数值
};

char str2byte(const char* pStr);

int Compress(const char*, HuffmanTree&);

int Encode(const char*, HuffmanTree&, char*, const int);

int WriteFile(const char*, const HEAD, const char*, const int);

int InitHead(const char*, HEAD&);

#endif //HUFFMAN_COMPRESS_H
