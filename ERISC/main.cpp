#include "computer.h"
#include <iostream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout << "��������Ҫ���е�ERISC�ļ���" << endl;
	string filename;
	cin >> filename;
	Computer computer(filename);
	computer.main();
	return 0;
}