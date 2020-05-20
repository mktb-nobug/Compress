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
		cout << "------------Huffman�ļ�ѹ�����ѹ------------" << endl;
		cout << "������ѡ�" << endl;
		cout << "1.ѹ���ļ�" << endl;
		cout << "2.��ѹ�ļ�" << endl;
		cout << "0.�˳�ϵͳ" << endl;
		cin >> flag;
		switch (flag) {
		case 1: {
			cout << "�������ļ�����";
			char filename[256];
			cin >> filename;
			ifstream fin;
			fin.open(filename, ios::in | ios::binary);

			if (!fin.is_open()) {
				cout << "�ļ���ʧ�ܣ�����" << endl;
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
				cout << "ѹ���ɹ�" << endl;
			} else {
				cout << "ѹ��ʧ��" << endl;
			}
			break;
		}
		case 2: {
			cout << "�������ļ�����";
			char filename[256];
			cin >> filename;
			int status = Decompress(filename);
			if (status == 0) {
				cout << "��ѹ�ɹ�" << endl;
			} else {
				cout << "��ѹʧ��" << endl;
			}
			break;
		}
		default:
			break;
		}
	} while (flag != 0);
	
	
	return 0;

}
