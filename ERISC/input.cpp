#include "input.h"
#include <fstream>
#include <iostream>

/**
* @brief 去除字符串的首尾空格
* @param str: 需要去除首尾空格的字符串
*/
static void trim(std::string& str) {
	if (str.empty()) {
		return;
	}
	while (!str.empty() && *str.begin() == ' ') {
		str.erase(str.begin());
	}
	while (!str.empty() && *(str.end() - 1) == ' ') {
		str.erase(str.end() - 1);
	}
}

/**
* @brief 把字符串以空格或逗号分割为向量
* @param str: 待分割的字符串
* @return 分割的字符串向量
*/
static std::vector<std::string> split(const std::string& str) {
	if (str.empty()) {
		return std::vector<std::string>();
	}
	std::string s{};
	std::vector<std::string> ss{};
	for (auto iter = str.cbegin(); iter != str.cend(); ++iter) {
		if (*iter != ' ' && *iter != ',') {
			s.insert(s.end(), *iter);
		}
		else {
			ss.push_back(s);
			s.clear();
		}
	}
	ss.push_back(s);
	return ss;
}

/**
* @brief: 把str转化为大写
* @param: str: 待转化的字符串
*/
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
			if (line[line.size() - 1] == ':') { //结尾为:,行标识符或者函数
				std::string s{};
				for (decltype(line.size()) i = 0; i <= line.size() - 2; i++) {
					s += line[i];
				}
				line_struct.type = Type::LINE_LABLE;
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
					line_struct.type = Type::LOAD;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "STORE") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					line_struct.type = Type::STORE;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "PUSH") {
					std::string a2 = split_result[1];
					line_struct.type = Type::PUSH;
					line_struct.op1 = a2;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "POP") {
					std::string a2 = split_result[1];
					line_struct.type = Type::POP;
					line_struct.op1 = a2;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "MOV") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					line_struct.type = Type::MOV;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "ADD") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::ADD;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "SUB") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::SUB;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "MUL") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::MUL;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "DIV") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::DIV;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "REM") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::REM;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "AND") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::AND;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "OR") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::OR;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "JAL") {
					std::string a2 = split_result[1];
					line_struct.type = Type::JAL;
					line_struct.op1 = a2;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "BEQ") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::BEQ;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "BNE") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::BNE;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "BLT") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::BLT;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "BGE") {
					std::string a2 = split_result[1];
					std::string a3 = split_result[2];
					std::string a4 = split_result[3];
					line_struct.type = Type::BGE;
					line_struct.op1 = a2;
					line_struct.op2 = a3;
					line_struct.op3 = a4;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "CALL") {
					std::string a2 = split_result[1];
					line_struct.type = Type::CALL;
					line_struct.op1 = a2;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "RET") {
					line_struct.type = Type::RET;
					LineLable line_label = m_linelabels[m_linelabels.size() - 1];
					Function function{};
					function.name = line_label.label;
					function.index = m_current_index + 1;
					m_lines.push_back(line_struct);
					m_functions.push_back(function);
				}
				else if (a1 == "DRAW") {
					line_struct.type = Type::DRAW;
					m_lines.push_back(line_struct);
				}
				else if (a1 == "END") {
					line_struct.type = Type::END;
					m_lines.push_back(line_struct);
				}
				else {
					std::cerr << "输入文件错误！" << std::endl;
					exit(-1);
				}
			}
		}
		m_current_index++;
	}
	in.close();
	m_current_index = 0;
}

/**
* @brief 获取当前的行号
* @return 当前的行号
*/
int32_t Input::getCurrentIndex() {
	return static_cast<int32_t>(m_current_index);
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
	if (m_lines[m_current_index].type == Type::LINE_LABLE) {
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