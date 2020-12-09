#include "input.h"
#include <iostream>
#include <fstream>

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
	auto iter = str.cbegin();
	// 读取第一个空格之前的字符串
	while (iter != str.cend() && *iter != ' ') {
		s.insert(s.end(), *iter);
		++iter;
	}
	ss.push_back(s);
	s.clear();
	// 读取接下来逗号分割的字符串并去除首尾空格
	for (; iter != str.cend(); ++iter) {
		if (*iter != ',' && *iter != '/' && *iter != '#') {
			s.insert(s.end(), *iter);
		}
		else {
			trim(s);
			if (!s.empty()) {
				ss.push_back(s);
			}
			s.clear();
			if (*iter == '/') {
				if (*(iter + 1) == '/') {
					break;
				}
				else {
					std::cerr << "注释错误！" << std::endl;
				}
			}
			if (*iter == '#') {
				break;
			}
		}
	}
	trim(s);
	if (!s.empty()) {
		ss.push_back(s);
	}
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
		std::cerr << "无法打开输入文件!" << std::endl;
		exit(-1);
	}
	while (in) {
		std::string line{};
		Line line_struct{};
		std::getline(in, line);
		trim(line);
		if (!line.empty()) {
			if (line[line.size() - 1] == ':') { //结尾为:，则行标识符或者函数
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
				if (split_result.size() >= 2) {
					line_struct.op1 = split_result[1];
				}
				if (split_result.size() >= 3) {
					line_struct.op2 = split_result[2];
				}
				if (split_result.size() >= 4) {
					line_struct.op3 = split_result[3];
				}
				toUpper(a1); // 把a1转化为大写
				try {
					if (a1 == "LOAD") {
						if (split_result.size() != 3) throw a1;
						line_struct.type = Type::LOAD;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "STORE") {
						if (split_result.size() != 3) throw a1;
						line_struct.type = Type::STORE;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "PUSH") {
						if (split_result.size() != 2) throw a1;
						line_struct.type = Type::PUSH;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "POP") {
						if (split_result.size() != 2) throw a1;
						line_struct.type = Type::POP;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "MOV") {
						if (split_result.size() != 3) throw a1;
						line_struct.type = Type::MOV;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "ADD") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::ADD;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "SUB") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::SUB;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "MUL") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::MUL;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "DIV") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::DIV;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "REM") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::REM;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "AND") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::AND;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "OR") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::OR;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "JAL") {
						if (split_result.size() != 2) throw a1;
						line_struct.type = Type::JAL;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "BEQ") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::BEQ;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "BNE") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::BNE;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "BLT") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::BLT;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "BGE") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::BGE;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "CALL") {
						if (split_result.size() != 2) throw a1;
						line_struct.type = Type::CALL;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "RET") {
						if (split_result.size() != 1) throw a1;
						line_struct.type = Type::RET;
						LineLable line_label = m_linelabels[m_linelabels.size() - 1];
						Function function{};
						function.name = line_label.label;
						function.index = m_current_index + 1;
						m_lines.push_back(line_struct);
						m_functions.push_back(function);
					}
					else if (a1 == "DRAW") {
						if (split_result.size() != 1) throw a1;
						line_struct.type = Type::DRAW;
						m_lines.push_back(line_struct);
					}
					else if (a1 == "END") {
						if (split_result.size() != 1) throw a1;
						line_struct.type = Type::END;
						m_lines.push_back(line_struct);
					}
					else {
						throw std::string();
					}
				}
				catch (std::string e) {
					std::cerr << "Line " << m_current_index + 1 << "：" << (e.empty() ? "未知" : e) << "指令错误！" << std::endl;
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