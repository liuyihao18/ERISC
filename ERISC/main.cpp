#include "computer.h"
#include <ctime>
#include <iostream>
using namespace std;

int main() {
#if !defined(WINDOWS) && !defined(LINUX)
	cerr << "请在编译时定义宏变量WINDOWS或LINUX！" << endl;
	exit(-1);
#endif
	ios::sync_with_stdio(false);
	cout << "请输入你要运行的ERISC文件：";
	string filename;
	cin >> filename;
	Computer computer(filename);
	auto begin = clock();
	computer.main();
	auto end = clock();
#if defined(WINDOWS)
	cout << "程序运行时间：" << end - begin << "ms" << endl;
#elif defined(LINUX)
	cout << "程序运行时间：" << (end - begin) / 1000 << "ms" << endl;
#endif
	return 0;
}