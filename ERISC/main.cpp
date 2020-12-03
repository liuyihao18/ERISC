#include "computer.h"
#include <iostream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout << "请输入你要运行的ERISC文件：" << endl;
	string filename;
	cin >> filename;
	Computer computer(filename);
	computer.main();
	return 0;
}