#include "memory.h"
#include <iostream>
#include <iomanip>

/**
* @brief 重置状态
*/
void Memory::reset() {
	for (auto& status : m_status) {
		status = Status::NO_OPERATE;
	}
}

/**
* @brief 根据索引返回相应状态
* @param i: 索引
* @return 内存的状态
*/
Status Memory::getStatus(int i) const {
	if (i < 0 || i >= MEMORY_STATUS_SIZE) {
		std::cerr << "内存状态越界访问！" << std::endl;
		exit(-1);
	}
	return m_status[i];
}

/**
* @brief 把rs寄存器指向的内存中的值拷贝到寄存器rd中
* @param rd: 目标寄存器地址，寄存器中存储的是一个值
* @param rs: 源寄存器地址，寄存器中存储的是内存的地址
*/
void Memory::load(int32_t* rd, int32_t* rs) {
	if (*rs < 0 || *rs > MEMORY_SIZE - 4) {
		std::cerr << "内存访问越界！" << std::endl;
		exit(-1);
	}
	std::memcpy(rd, m_memory + *rs, sizeof(int32_t));
	for (int i = 0; i < 4; i++) {
		m_status[(*rs + i) >> 18] = Status::VISITED;
	}
}

/**
* @brief 把寄存器rs中的值拷贝到rd寄存器指向的内存中
* @param rs: 源寄存器地址，寄存器中存储的是一个值
* @param rd: 目标寄存器地址，寄存器中存储的是内存的地址
*/
void Memory::store(int32_t* rs, int32_t* rd) {
	if (*rd < 0 || *rd > MEMORY_SIZE - 4) {
		std::cerr << "内存访问越界！" << std::endl;
		exit(-1);
	}
	std::memcpy(m_memory + *rd, rs, sizeof(int32_t));
	for (int i = 0; i < 4; i++) {
		m_status[(*rd + i) >> 18] = Status::VISITED;
	}
}

/**
* @brief 输出内存的内容
* @param out: 输出流对象
* @param reg: 输出的Memory对象
* @return 输出流对象
*/
std::ostream& operator<<(std::ostream& out, const Memory& memory) {
	for (int i = 0; i < MEMORY_SIZE; i++) {
		if (i != 0 && i % 64 == 0) {
			out << std::endl;
		}
		out << std::hex << std::setw(2) << std::setfill('0') << (int32_t)memory.m_memory[i] << " ";
	}
	return out;
}