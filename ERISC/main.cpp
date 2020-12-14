#include "computer.h"
#include <ctime>
#include <iostream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout << "��������Ҫ���е�ERISC�ļ���";
	string filename;
	cin >> filename;
	Computer computer(filename);
	auto begin = clock();
	computer.main();
	auto end = clock();
#if defined WINDOWS
	cout << "��������ʱ�䣺" << (end - begin) / 1000 << "s" << endl;
#elif defined LINUX || defined UNIX
	cout << "��������ʱ�䣺" << end - begin << "s" << endl;
#endif
	return 0;
}