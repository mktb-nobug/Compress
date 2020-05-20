#include <iostream>
#include <fstream>
#include <iomanip>

#include "Huffman.h"
#include "Compress.h"
#include "Decompress.h"
using namespace std;

int main() {
	int flag = 0;
	do {
		cout << "------------Huffman文件压缩与解压------------" << endl;
		cout << "请输入选项：" << endl;
		cout << "1.压缩文件" << endl;
		cout << "2.解压文件" << endl;
		cout << "0.退出系统" << endl;
		cin >> flag;
		switch (flag) {
		case 1: {
			cout << "请输入文件名：";
			char filename[256];
			cin >> filename;
			ifstream fin;
			fin.open(filename, ios::in | ios::binary);

			if (!fin.is_open()) {
				cout << "文件打开失败！！！" << endl;
				return 0;
			}

			char ch;
			int oldnSize = 0;
			int weight[256] = { 0 };
			while (fin.read(&ch, 1)) {
				weight[(unsigned char)ch]++;
				oldnSize++;
			}

			fin.close();
			HuffmanTree ht = HuffmanTree(weight, 256);
			int status = Compress(filename, ht);
			if (status == 0) {
				cout << "压缩成功" << endl;
			} else {
				cout << "压缩失败" << endl;
			}
			break;
		}
		case 2: {
			cout << "请输入文件名：";
			char filename[256];
			cin >> filename;
			int status = Decompress(filename);
			if (status == 0) {
				cout << "解压成功" << endl;
			} else {
				cout << "解压失败" << endl;
			}
			break;
		}
		default:
			break;
		}
	} while (flag != 0);
	
	
	return 0;

}
