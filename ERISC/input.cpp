#include "input.h"

/**
	* @brief 构造函数，根据输入的文件名构造整个行结构
	* @param filename: 输入文件名
	*/
Input::Input(std::string filename) {
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("failed to open file!\n");
	}
	char buf[512];
	while (!feof(fp)) {
		char* line1 = fgets(buf, 512, fp);
		string line = line1;
		if (line) {
			m_current_indx++;
			if (line[strlen(line) - 1] == ':') { //结尾为:,行标识符或者函数
				string s;
				for (int i = 0; i <= strlen(line) - 2; i++) {
					s += line[i];
				}
				line.type = LINE_LABLE;
				m_lines.push_back(line);
				struct LineLable line_l { s, m_current_indx + 1 };
				m_linelabels.push_back(line_l);
			}
			else {
				//string [] a = line.split(" ");
				string a1;
				int i = 0;
				while (line[i] != ' ') a1 += line[i++];
				if (a1 == "NONE") {};
				else if (a1 == "LOAD") {
					string a2, a3;
					line.type = 1;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.type = 1;
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "STORE") {
					string a2, a3;
					line.type = 2; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.type = 2;
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "PUSH") {
					string a2, a3;
					line.type = 3; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.type = 3;
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "POP") {
					string a2, a3;
					line.type = 4; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "MOV") {
					string a2, a3;
					line.type = 5; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "ADD") {
					string a2, a3;
					line.type = 6; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "SUB") {
					string a2, a3;
					line.type = 7; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "MUL") {
					string a2, a3;
					line.type = 8; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "DIV") {
					string a2, a3;
					line.type = 9; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "REM") {
					string a2, a3;
					line.type = 10; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "AND") {
					string a2, a3;
					line.type = 11; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "OR") {
					string a2, a3;
					line.type = 12; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "LINE_LABLE") {
					string a2, a3;
					line.type = 13; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "JAL") {
					string a2, a3;
					line.type = 14; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "BEQ") {
					string a2, a3;
					line.type = 15; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "BNE") {
					string a2, a3;
					line.type = 16; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "BLT") {
					string a2, a3;
					line.type = 17; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "BGE") {
					string a2, a3;
					line.type = 18; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "CALL") {
					string a2, a3;
					line.type = 19; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "RET") {
					string a2, a3;
					line.type = 20; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
					for (int i = m_current_indx;; i--) {
						if (m_lines[i].type == LINE_LABLE) {
							m_lines[i].type = Function;
							struct m_l = m_linelabels.pop();
							string m_s = m_l.label;
							int m_n = m_l.index;
							struct Function m_Function { m_s, m_n };
							m_functions.push_back(m_Function);
							break;
						}
					}
				};
				else if (a1 == "DRAW") {
					string a2, a3;
					line.type = 21; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "END") {
					string a2, a3;
					line.type = 22; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				else if (a1 == "TYPE_SIZE") {
					string a2, a3;
					line.type = 23; ;
					i++;
					while (line[i] != ',') a2 += line[i++];
					i++;
					while (i < line.size()) a3 += line[i++];
					line.op1 = a2;
					line.op3 = a3;
					m_lines.push_back(line);
				};
				//m_lines.push_back(line);

			}

		}
	}
	fclose(fp);
}

/**
* @brief 获取当前的行号
* @return 当前的行号
*/
int Input::getCurrentIndex() {
	return m_current_indx;
}

/**
* @brief 获取当前的行
* @return 当前行的信息
*/
Line Input::getCurrentLine() {
	return m_lines[m_current_indx];
}

/**
* @brief 转到下一行
*/
void Input::nextLine() {
	m_current_indx++;
}

/**
* @brief 跳到行标识的下一行
* @param label: 行标识
*/
void Input::jumpLine(std::string lable) {
	std::vector<LineLable>::iterator it = m_linelabels.begin();
	for (it = m_linelabels.begin(); it != m_linelabels.end(); it++) {
		if (it.label == label) {
			m_current_indx = it.index;
			break;
		}
	}
}

/**
* @brief 跳到某一行
* @param index: 行号
*/
void Input::jumpLine(int index) {
	m_current_indx = index;
}

/**
* @brief 是否还有更多的输入
* @return 判断结果
*/
bool Input::hasMoreInput() {
	return m_current_indx < m_lines.size();
}