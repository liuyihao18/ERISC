#include "input.h"
#include <fstream>
#include <iostream>

static void trim(std::string& str) {
	if (str.empty()) {
		return;
	}
	while (!str.empty() && *str.begin() == ' ') {
		str.erase(str.begin());
	}
	while (!str.empty() && *str.end() == ' ') {
		str.erase(str.end());
	}
}

static std::vector<std::string> split(const std::string& str) {
	if (str.empty()) {
		return std::vector<std::string>();
	}
	std::string s{};
	std::vector<std::string> ss{};
	for (auto iter = str.cbegin(); iter != str.cend(); ++iter) {
		if (*iter != ' ') {
			s.insert(s.end(), *iter);
		}
		else {
			ss.push_back(s);
			s.clear();
		}
	}
	return ss;
}

static void toUpper(std::string& str) {
	for (auto iter = str.begin(); iter != str.end(); ++iter) {
		*iter = toupper(*iter);
	}
}

/**
* @brief 构造函数，根据输入的文件名构造整个行结构
* @param filename: 输入文件名
*/
Input::Input(std::string filename) {
	std::ifstream in(filename);
	if (!in.is_open()) {
		std::cerr << "Failed to open file!" << std::endl;
		exit(-1);
	}
	while (in) {
		std::string line{};
		Line line_struct{};
		std::getline(in, line);
		trim(line);
		if (!line.empty()) {
			m_current_index++;
			if (line[line.size() - 1] == ':') { //结尾为:,行标识符或者函数
				std::string s{};
				for (int i = 0; i <= line.size() - 2; i++) {
					s += line[i];
				}
				line_struct.type = LINE_LABLE;
				line_struct.op1 = s;
				m_lines.push_back(line_struct);
				LineLable line_label { s, m_current_index + 1 };
				m_linelabels.push_back(line_label);
			}
			else {
				auto split_result = split(line);
				std::string a1 = split_result[0];
				toUpper(a1); // 把a1转化为大写
				if (a1 == "LOAD") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					line_struct.type = LOAD;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "STORE") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					line_struct.type = STORE;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "PUSH") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					line_struct.type = PUSH;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "POP") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					line_struct.type = POP;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "MOV") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					line_struct.type = MOV;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "ADD") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = ADD;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "SUB") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = SUB;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "MUL") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = MUL;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "DIV") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = DIV;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "REM") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = REM;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "AND") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = AND;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "OR") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = OR;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "JAL") {
					std::string a2 = split_result[1];
					line_struct.type = JAL;
					line_struct.op1 = a2;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "BEQ") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = BEQ;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "BNE") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = BNE;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "BLT") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = BLT;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "BGE") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = BGE;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "CALL") {
					std::string a2 = split_result[1];
					line_struct.type = CALL;
					line_struct.op1 = a2;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "RET") {
					line_struct.type = RET;
					LineLable line_label = m_linelabels[m_linelabels.size() - 1];
					Function function{};
					function.name = line_label.label;
					function.index = m_current_index + 1;
					m_lines.push_back(line_struct);
					m_functions.push_back(function);
				}
				else if (a1 == "DRAW") {
					line_struct.type = DRAW;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "END") {
					line_struct.type = END;
					m_lines.push_back(line_struct);
				}
				else {
					std::cerr << "输入文件错误！" << std::endl;
					exit(-1);
				}
			}
		}
	}
	in.close();
}

/**
* @brief 获取当前的行号
* @return 当前的行号
*/
int Input::getCurrentIndex() {
	return m_current_index;
}

/**
* @brief 获取当前的行
* @return 当前行的信息
*/
Line Input::getCurrentLine() {
	return m_lines[m_current_index];
}

/**
* @brief 转到下一行
*/
void Input::nextLine() {
	m_current_index++;
	if (m_lines[m_current_index].type == LINE_LABLE) {
		for (auto iter = m_functions.begin(); iter != m_functions.end(); ++iter) {
			if (iter->name == m_lines[m_current_index].op1) {
				m_current_index = iter->index; // ret之后的下一行
				return;
			}
		}
		m_current_index++; // 行标识的下一行
	}
}

/**
* @brief 跳到行标识的下一行
* @param label: 行标识
*/
void Input::jumpLine(std::string label) {
	std::vector<LineLable>::iterator it = m_linelabels.begin();
	for (it = m_linelabels.begin(); it != m_linelabels.end(); it++) {
		if (it->label == label) {
			m_current_index = it->index; // 跳到行标识的下一行
			break;
		}
	}
}

/**
* @brief 跳到某一行
* @param index: 行号
*/
void Input::jumpLine(int index) {
	m_current_index = index;
}

/**
* @brief 是否还有更多的输入
* @return 判断结果
*/
bool Input::hasMoreInput() {
	return m_current_index < m_lines.size();
}