#include "register.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>

// �Ĵ���������
static const std::string names[64]{
	"x0", "zero",
	"x1", "ra",
	"x2", "sp",
"x3", "gp",
"x4", "tp",
"x5", "t0",
"x6", "t1",
"x7", "t2",
"x8", "fp",
"x9", "s1",
"x10", "a0",
"x11", "a1",
"x12", "a2",
"x13", "a3",
"x14", "a4",
"x15", "a5",
"x16", "a6",
"x17", "a7",
"x18", "s2",
"x19", "s3",
"x20", "s4",
"x21", "s5",
"x22", "s6",
"x23", "s7",
"x24", "s8",
"x25", "s9",
"x26", "s10",
"x27", "s11",
"x28", "t3",
"x29", "t4",
"x30", "t5",
"x31", "t6"
};

/**
* @brift �ж�һ���ַ����Ƿ���������
* @param str: �����ַ���
* @return �Ƿ���������
*/
static bool isImm(const std::string& str) {
	if (str.empty()) {
		std::cerr << "���ַ�������" << std::endl;
		std::exit(-1);
	}
	return std::isdigit(str[0]);
}

/**
* @brief ���ַ�������ʮ�����ƻ�ʮ����ת��Ϊ����
* @param str: �ַ���
* @return ת���ɵ�����
*/
static int32_t str2num(const std::string& str) {
	int32_t result{ 0 };
	std::istringstream is(str);
	if (str.size() >= 2 && str[0] == '0' && str[1] == 'x') {
		if (!(is >> std::hex >> result)) {
			std::cerr << "ʮ�����������������" << std::endl;
			std::exit(-1);
		}
	}
	else {
		if (!(is >> result)) {
			std::cerr << "ʮ���������������" << std::endl;
			std::exit(-1);
		}
	}
	return result;
}

/**
* @brief �������ֻ�ȡ�Ĵ���������
* @param �Ĵ���������
* @return �Ĵ���������
*/
int Register::lookup(const std::string& name) const {
	for (int i = 0; i < 64; i++) {
		if (name == names[i]) {
			return i >> 1;
		}
	}
	std::cerr << "�Ĵ������ִ���" << std::endl;
	std::exit(-1);
}

/**
* @brief ����״̬
*/
void Register::reset() {
	for (auto& status : m_status) {
		status = NO_OPERATE;
	}
}

/**
* @brief ����״̬�������Register�������operator[]ʱ
* param name: �Ĵ���������
* param status: ״̬
*/
void Register::setStatus(const std::string& name, Status status) {
	int index = lookup(name);
	switch (status) {
	case WRITE:
		switch (m_status[index]) {
		case NO_OPERATE:
			m_status[index] = WRITE;
			break;
		case READ:
			m_status[index] = READ_WRITE;
			break;
		default:
			break;
		}
		break;
	case READ:
		switch (m_status[index]) {
		case NO_OPERATE:
			m_status[index] = READ;
			break;
		case WRITE:
			m_status[index] = READ_WRITE;
			break;
		default:
			break;
		}
		break;
	case READ_WRITE:
		m_status[index] = READ_WRITE;
		break;
	default:
		std::cerr << "�Ĵ���״̬���ô���" << std::endl;
		exit(-1);
	}
}

/**
* @brief �������ַ�����Ӧ�Ĵ����ĵ�ַ
* @param name: �Ĵ���������
* @return �Ĵ����ĵ�ַ
*/
int32_t* Register::operator[](const std::string& name) {
	return m_register + lookup(name);
}

/**
* @brief ��������������Ӧ״̬
* @param i: ����
* @return �Ĵ�����״̬
*/
Status Register::getStatus(int i) const {
	return m_status[i];
}

/**
* @brief ���Ĵ���rs��ֵ��������imm�����Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs_or_imm: Դ�Ĵ��������ֻ���������
*/
void Register::mov(const std::string& rd, const std::string& rs_or_imm) {
	if (isImm(rs_or_imm)) {
		int32_t imm = str2num(rs_or_imm);
		m_register[lookup(rd)] = imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs_or_imm)];
	}
}

/**
* @brief ���Ĵ���rs1��ֵ���ϼĴ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::add(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] + imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] + m_register[lookup(rs2_or_imm)];
	}
}

/**
* @brief ���Ĵ���rs1��ֵ��ȥ�Ĵ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::sub(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] - imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] - m_register[lookup(rs2_or_imm)];
	}
}

/**
* @brief ���Ĵ���rs1��ֵ���ϼĴ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::mul(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] * imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] * m_register[lookup(rs2_or_imm)];
	}
}

/**
* @brief ���Ĵ���rs1��ֵ��ȥ�Ĵ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::div(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] / imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] / m_register[lookup(rs2_or_imm)];
	}
}

/**
* @brief ���Ĵ���rs1��ֵģ�ϼĴ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::rem(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] % imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] % m_register[lookup(rs2_or_imm)];
	}
}

/**
* @brief ���Ĵ���rs1��ֵ��Ĵ���rs2��ֵ��������immλ��󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::AND(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] & imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] & m_register[lookup(rs2_or_imm)];
	}
}

/**
* @brief ���Ĵ���rs1��ֵ��Ĵ���rs2��ֵ��������immλ��󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::OR(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] | imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] | m_register[lookup(rs2_or_imm)];
	}
}

/**
* @brief �жϼĴ���rs1�ͼĴ���rs2��ֵ�Ƿ����
* @param rs1: Դ�Ĵ���1������
* @param rs2: Դ�Ĵ���2������
* @return �жϽ��
*/
bool Register::beq(const std::string& rs1, const std::string& rs2) const {
	return m_register[lookup(rs1)] == m_register[lookup(rs2)];
}

/**
* @brief �жϼĴ���rs1�ͼĴ���rs2��ֵ�Ƿ񲻵�
* @param rs1: Դ�Ĵ���1������
* @param rs2: Դ�Ĵ���2������
* @return �жϽ��
*/
bool Register::bne(const std::string& rs1, const std::string& rs2) const {
	return m_register[lookup(rs1)] != m_register[lookup(rs2)];
}

/**
* @brief �жϼĴ���rs1��ֵ�Ƿ�С�ڼĴ���rs2��ֵ
* @param rs1: Դ�Ĵ���1������
* @param rs2: Դ�Ĵ���2������
* @return �жϽ��
*/
bool Register::blt(const std::string& rs1, const std::string& rs2) const {
	return m_register[lookup(rs1)] < m_register[lookup(rs2)];
}

/**
* @brief �жϼĴ���rs1��ֵ�Ƿ���ڵ��ڼĴ���rs2��ֵ
* @param rs1: Դ�Ĵ���1������
* @param rs2: Դ�Ĵ���2������
* @return �жϽ��
*/
bool Register::bge(const std::string& rs1, const std::string& rs2) const {
	return m_register[lookup(rs1)] >= m_register[lookup(rs2)];
}

/**
* @brief ����Ĵ���������
* @param out: ���������
* @param reg: �����Register����
* @return ���������
*/
std::ostream& operator<<(std::ostream& out, const Register& reg) {
	for (const auto& a_reg : reg.m_register) {
		out << std::hex << std::setw(8) << std::setfill('0') << a_reg << " ";
	}
	return out;
}