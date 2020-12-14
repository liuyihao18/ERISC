#include "register.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>

// 寄存器的名字
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
* @brift 判断一个字符串是否是立即数
* @param str: 输入字符串
* @return 是否是立即数
*/
static bool isImm(const std::string& str) {
	if (str.empty()) {
		throw std::string("空字符串错误！");
	}
	return std::isdigit(str[0]);
}

/**
* @brief 把字符串根据十六进制或十进制转化为数字
* @param str: 字符串
* @return 转化成的数字
*/
static int32_t str2num(const std::string& str) {
	int32_t result{ 0 };
	std::istringstream is(str);
	if (str.size() >= 3 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
		// 确认数据中间没有出错
		for (decltype(str.size()) i = 2; i < str.size(); i++) {
			if (!std::isdigit(str[i]) && str[i] != 'a' && str[i] != 'b' && str[i] != 'c'
				&& str[i] != 'd' && str[i] != 'e' && str[i] != 'f') {
				throw std::string(str + " -- 立即数输入错误！");
			}
		}
		// 输入数据
		if (!(is >> std::hex >> result)) {
			throw std::string(str + " -- 立即数输入错误！");
		}		
	}
	else {
		// 确认数据中间没有出错
		for (decltype(str.size()) i = 0; i < str.size(); i++) {
			if (!std::isdigit(str[i])) {
				throw std::string(str + " -- 立即数输入错误！");
			}
		}
		// 输入数据
		if (!(is >> result)) {
			throw std::string(str + " -- 立即数输入错误！");
		}
	}
	return result;
}

/**
* @brief 根据名字获取寄存器的索引
* @param 寄存器的名字
* @return 寄存器的索引
*/
int Register::lookup(const std::string& name) const {
	for (int i = 0; i < 64; i++) {
		if (name == names[i]) {
			return i >> 1;
		}
	}
	throw std::string(name + " -- 寄存器名字错误！");
}

/**
* @brief 重置状态
*/
void Register::reset() {
	for (auto& status : m_status) {
		status = Status::NO_OPERATE;
	}
}

/**
* @brief 设置状态，针对在Register类外调用operator[]时
* param name: 寄存器的名字
* param status: 状态
*/
void Register::setStatus(const std::string& name, Status status) {
	int index = lookup(name);
	switch (status) {
	case Status::WRITE:
		switch (m_status[index]) {
		case Status::NO_OPERATE:
			m_status[index] = Status::WRITE;
			break;
		case Status::READ:
			m_status[index] = Status::READ_WRITE;
			break;
		default:
			break;
		}
		break;
	case Status::READ:
		switch (m_status[index]) {
		case Status::NO_OPERATE:
			m_status[index] = Status::READ;
			break;
		case Status::WRITE:
			m_status[index] = Status::READ_WRITE;
			break;
		default:
			break;
		}
		break;
	case Status::READ_WRITE:
		m_status[index] = Status::READ_WRITE;
		break;
	default:
		throw std::string("寄存器状态设置错误");
	}
}

/**
* @brief 根据名字返回相应寄存器的地址
* @param name: 寄存器的名字
* @return 寄存器的地址
*/
int32_t* Register::operator[](const std::string& name) {
	return m_register + lookup(name);
}

/**
* @brief 根据索引返回相应状态
* @param i: 索引
* @return 寄存器的状态
*/
Status Register::getStatus(int i) const {
	if (i < 0 || i >= REGISTER_SIZE) {
		throw std::string("寄存器状态越界访问！");
	}
	return m_status[i];
}

/**
* @brief 将寄存器rs的值或立即数imm赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs_or_imm: 源寄存器的名字或者立即数
*/
void Register::mov(const std::string& rd, const std::string& rs_or_imm) {
	if (isImm(rs_or_imm)) {
		int32_t imm = str2num(rs_or_imm);
		m_register[lookup(rd)] = imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs_or_imm)];
		setStatus(rs_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
}

/**
* @brief 将寄存器rs1的值加上寄存器rs2的值或立即数imm后赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs1: 源寄存器1的名字
* @param rs2_or_imm: 源寄存器2的名字或者立即数
*/
void Register::add(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] + imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] + m_register[lookup(rs2_or_imm)];
		setStatus(rs2_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
	setStatus(rs1, Status::READ);
}

/**
* @brief 将寄存器rs1的值减去寄存器rs2的值或立即数imm后赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs1: 源寄存器1的名字
* @param rs2_or_imm: 源寄存器2的名字或者立即数
*/
void Register::sub(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] - imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] - m_register[lookup(rs2_or_imm)];
		setStatus(rs2_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
	setStatus(rs1, Status::READ);
}

/**
* @brief 将寄存器rs1的值乘上寄存器rs2的值或立即数imm后赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs1: 源寄存器1的名字
* @param rs2_or_imm: 源寄存器2的名字或者立即数
*/
void Register::mul(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] * imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] * m_register[lookup(rs2_or_imm)];
		setStatus(rs2_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
	setStatus(rs1, Status::READ);
}

/**
* @brief 将寄存器rs1的值除去寄存器rs2的值或立即数imm后赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs1: 源寄存器1的名字
* @param rs2_or_imm: 源寄存器2的名字或者立即数
*/
void Register::div(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] / imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] / m_register[lookup(rs2_or_imm)];
		setStatus(rs2_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
	setStatus(rs1, Status::READ);
}

/**
* @brief 将寄存器rs1的值模上寄存器rs2的值或立即数imm后赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs1: 源寄存器1的名字
* @param rs2_or_imm: 源寄存器2的名字或者立即数
*/
void Register::rem(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] % imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] % m_register[lookup(rs2_or_imm)];
		setStatus(rs2_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
	setStatus(rs1, Status::READ);
}

/**
* @brief 将寄存器rs1的值与寄存器rs2的值或立即数imm位与后赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs1: 源寄存器1的名字
* @param rs2_or_imm: 源寄存器2的名字或者立即数
*/
void Register::AND(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] & imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] & m_register[lookup(rs2_or_imm)];
		setStatus(rs2_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
	setStatus(rs1, Status::READ);
}

/**
* @brief 将寄存器rs1的值与寄存器rs2的值或立即数imm位或后赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs1: 源寄存器1的名字
* @param rs2_or_imm: 源寄存器2的名字或者立即数
*/
void Register::OR(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] | imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] | m_register[lookup(rs2_or_imm)];
		setStatus(rs2_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
	setStatus(rs1, Status::READ);
}

/**
* @brief 将寄存器rs1的值与寄存器rs2的值或立即数imm异或后赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs1: 源寄存器1的名字
* @param rs2_or_imm: 源寄存器2的名字或者立即数
*/
void Register::XOR(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {
	if (isImm(rs2_or_imm)) {
		int32_t imm = str2num(rs2_or_imm);
		m_register[lookup(rd)] = m_register[lookup(rs1)] ^ imm;
	}
	else {
		m_register[lookup(rd)] = m_register[lookup(rs1)] ^ m_register[lookup(rs2_or_imm)];
		setStatus(rs2_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
	setStatus(rs1, Status::READ);
}

/**
* @brief 将寄存器rs1的值或立即数imm取反后赋给寄存器rd
* @param rd: 目标寄存器的名字
* @param rs1_or_imm: 源寄存器1的名字或者立即数
*/
void Register::NOT(const std::string& rd, const std::string& rs1_or_imm) {
	if (isImm(rs1_or_imm)) {
		int32_t imm = str2num(rs1_or_imm);
		m_register[lookup(rd)] = ~imm;
	}
	else {
		m_register[lookup(rd)] = ~m_register[lookup(rs1_or_imm)];
		setStatus(rs1_or_imm, Status::READ);
	}
	setStatus(rd, Status::WRITE);
}

/**
* @brief 判断寄存器rs1和寄存器rs2中值是否相等
* @param rs1: 源寄存器1的名字
* @param rs2: 源寄存器2的名字
* @return 判断结果
*/
bool Register::beq(const std::string& rs1, const std::string& rs2) {
	setStatus(rs1, Status::READ);
	setStatus(rs2, Status::READ);
	return m_register[lookup(rs1)] == m_register[lookup(rs2)];
}

/**
* @brief 判断寄存器rs1和寄存器rs2中值是否不等
* @param rs1: 源寄存器1的名字
* @param rs2: 源寄存器2的名字
* @return 判断结果
*/
bool Register::bne(const std::string& rs1, const std::string& rs2) {
	setStatus(rs1, Status::READ);
	setStatus(rs2, Status::READ);
	return m_register[lookup(rs1)] != m_register[lookup(rs2)];
}

/**
* @brief 判断寄存器rs1的值是否小于寄存器rs2中值
* @param rs1: 源寄存器1的名字
* @param rs2: 源寄存器2的名字
* @return 判断结果
*/
bool Register::blt(const std::string& rs1, const std::string& rs2) {
	setStatus(rs1, Status::READ);
	setStatus(rs2, Status::READ);
	return m_register[lookup(rs1)] < m_register[lookup(rs2)];
}

/**
* @brief 判断寄存器rs1的值是否大于等于寄存器rs2中值
* @param rs1: 源寄存器1的名字
* @param rs2: 源寄存器2的名字
* @return 判断结果
*/
bool Register::bge(const std::string& rs1, const std::string& rs2) {
	setStatus(rs1, Status::READ);
	setStatus(rs2, Status::READ);
	return m_register[lookup(rs1)] >= m_register[lookup(rs2)];
}

/**
* @brief 输出寄存器的内容
* @param out: 输出流对象
* @param reg: 输出的Register对象
* @return 输出流对象
*/
std::ostream& operator<<(std::ostream& out, const Register& reg) {
	for (const auto& a_reg : reg.m_register) {
		out << std::hex << std::setw(8) << std::setfill('0') << a_reg << " ";
	}
	return out;
}