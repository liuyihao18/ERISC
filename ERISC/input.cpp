#include "input.h"
#include <iostream>
#include <fstream>

/**
* @brief ȥ���ַ�������β�ո�
* @param str: ��Ҫȥ����β�ո���ַ���
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
* @brief ȥ���ַ����е�ע��
* @param str: ��Ҫȥ��ע�͵��ַ���
*/
static void removeComment(std::string& str) {
	auto iter = str.begin();
	while (iter != str.end() && *iter != '/' && *iter != '#') ++iter;
	if (iter != str.end() && *iter == '/') {
		if ((iter + 1) == str.end() || *(iter + 1) != '/') {
			throw std::string("ע�ʹ���");
		}
	}
	while (iter != str.end()) iter = str.erase(iter);
}

/**
* @brief ���ַ����Կո�򶺺ŷָ�Ϊ����
* @param str: ���ָ���ַ���
* @return �ָ���ַ�������
*/
static std::vector<std::string> split(const std::string& str) {
	if (str.empty()) {
		return std::vector<std::string>();
	}
	std::string s{};
	std::vector<std::string> ss{};
	auto iter = str.cbegin();
	// ��ȡ��һ���ո�֮ǰ���ַ���
	while (iter != str.cend() && *iter != ' ') {
		s.insert(s.end(), *iter);
		++iter;
	}
	if (!s.empty()) {
		ss.push_back(s);
	}
	s.clear();
	// ��ȡ���������ŷָ���ַ�����ȥ����β�ո�
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
		}
	}
	trim(s);
	if (!s.empty()) {
		ss.push_back(s);
	}
	return ss;
}

/**
* @brief: ��strת��Ϊ��д
* @param: str: ��ת�����ַ���
*/
static void toUpper(std::string& str) {
	for (auto iter = str.begin(); iter != str.end(); ++iter) {
		*iter = toupper(*iter);
	}
}

/**
* @brief ���캯��������������ļ������������нṹ
* @param filename: �����ļ���
*/
Input::Input(std::string filename) {
	std::ifstream in(filename);
	if (!in.is_open()) {
		std::cerr << "�޷��������ļ�!" << std::endl;
		exit(-1);
	}
	while (in) {
		std::string line{};
		Line line_struct{};
		std::getline(in, line);
		try {
			trim(line);
			removeComment(line);
			if (!line.empty()) {
				if (line[line.size() - 1] == ':') { //��βΪ:�����б�ʶ�����ߺ���
					std::string s{};
					for (decltype(line.size()) i = 0; i <= line.size() - 2; i++) {
						s += line[i];
					}
					trim(s);
					line_struct.type = Type::LINE_LABLE;
					line_struct.op1 = s;
					LineLable line_label{ s, m_current_index + 1 };
					m_linelabels.push_back(line_label);
				}
				else {
					auto split_result = split(line);
					std::string a1 = split_result[0];
					if (split_result.size() >= 2) line_struct.op1 = split_result[1];
					if (split_result.size() >= 3) line_struct.op2 = split_result[2];
					if (split_result.size() >= 4) line_struct.op3 = split_result[3];
					toUpper(a1); // ��a1ת��Ϊ��д
					if (a1 == "LOAD") {
						if (split_result.size() != 3) throw a1;
						line_struct.type = Type::LOAD;
					}
					else if (a1 == "STORE") {
						if (split_result.size() != 3) throw a1;
						line_struct.type = Type::STORE;
					}
					else if (a1 == "PUSH") {
						if (split_result.size() != 2) throw a1;
						line_struct.type = Type::PUSH;
					}
					else if (a1 == "POP") {
						if (split_result.size() != 2) throw a1;
						line_struct.type = Type::POP;
					}
					else if (a1 == "MOV") {
						if (split_result.size() != 3) throw a1;
						line_struct.type = Type::MOV;
					}
					else if (a1 == "ADD") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::ADD;
					}
					else if (a1 == "SUB") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::SUB;
					}
					else if (a1 == "MUL") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::MUL;
					}
					else if (a1 == "DIV") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::DIV;
					}
					else if (a1 == "REM") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::REM;
					}
					else if (a1 == "AND") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::AND;
					}
					else if (a1 == "OR") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::OR;
					}
					else if (a1 == "JAL") {
						if (split_result.size() != 2) throw a1;
						line_struct.type = Type::JAL;
					}
					else if (a1 == "BEQ") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::BEQ;
					}
					else if (a1 == "BNE") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::BNE;
					}
					else if (a1 == "BLT") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::BLT;
					}
					else if (a1 == "BGE") {
						if (split_result.size() != 4) throw a1;
						line_struct.type = Type::BGE;
					}
					else if (a1 == "CALL") {
						if (split_result.size() != 2) throw a1;
						line_struct.type = Type::CALL;
					}
					else if (a1 == "RET") {
						if (split_result.size() != 1) throw a1;
						line_struct.type = Type::RET;
						LineLable line_label = m_linelabels[m_linelabels.size() - 1];
						Function function{};
						function.name = line_label.label;
						function.index = m_current_index + 1;
						m_functions.push_back(function);
					}
					else if (a1 == "DRAW") {
						if (split_result.size() != 1) throw a1;
						line_struct.type = Type::DRAW;
					}
					else if (a1 == "END") {
						if (split_result.size() != 1) throw a1;
						line_struct.type = Type::END;
					}
					else {
						throw std::string();
					}
				}
			}	
			m_lines.push_back(line_struct);
			m_current_index++;
		}
		catch (const std::string& s) {
			std::cerr << "Line " << m_current_index + 1 << ": " << line << " -- ";
			if (s == "ע�ʹ���") {
				std::cerr << s << std::endl;
			}
			else {
				std::cerr << (s.empty() ? "δ֪" : s) << "ָ�����" << std::endl;
			}
			std::exit(-1);
		}
	}
	in.close();
	m_current_index = 0;
}

/**
* @brief ��ȡ��ǰ���к�
* @return ��ǰ���к�
*/
int32_t Input::getCurrentIndex() {
	return static_cast<int32_t>(m_current_index);
}

/**
* @brief ��ȡ��ǰ����
* @return ��ǰ�е���Ϣ
*/
Line Input::getCurrentLine() {
	return m_lines[m_current_index];
}

/**
* @brief ת����һ��
*/
void Input::nextLine() {
	m_current_index++;
	if (m_lines[m_current_index].type == Type::LINE_LABLE) {
		for (auto iter = m_functions.begin(); iter != m_functions.end(); ++iter) {
			if (iter->name == m_lines[m_current_index].op1) {
				m_current_index = iter->index; // ret֮�����һ��
				return;
			}
		}
		m_current_index++; // �б�ʶ����һ��
	}
}

/**
* @brief �����б�ʶ����һ��
* @param label: �б�ʶ
*/
void Input::jumpLine(std::string label) {
	std::vector<LineLable>::iterator it = m_linelabels.begin();
	for (it = m_linelabels.begin(); it != m_linelabels.end(); it++) {
		if (it->label == label) {
			m_current_index = it->index; // �����б�ʶ����һ��
			break;
		}
	}
}

/**
* @brief ����ĳһ��
* @param index: �к�
*/
void Input::jumpLine(int index) {
	m_current_index = index;
}

/**
* @brief �Ƿ��и��������
* @return �жϽ��
*/
bool Input::hasMoreInput() {
	return m_current_index < m_lines.size();
}