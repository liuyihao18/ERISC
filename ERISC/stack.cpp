#include "stack.h"
#include <iostream>
#include <cstring>

/**
* @brief 重置状态
*/
void Stack::reset() {
	m_status = Status::NO_OPERATE;
}

/**
* @brief 返回栈的状态
* @return 栈的状态
*/
Status Stack::getStatus() const {
	return m_status;
}

/**
* @brief 把rs寄存器中的值入栈
* @param rs: 寄存器的地址
*/
void Stack::push(int32_t* rs) {
	if (m_ptr <= 0) {
		throw std::string("Stack Overflow!");
	}
	std::memcpy(m_stack + (--m_ptr), rs, sizeof(int32_t));
	m_status = Status::STACK_OPERATE;
}

/**
* @brief 把栈顶的值存入rd寄存器中
* @param rd: 寄存器的地址
*/
void Stack::pop(int32_t* rd) {
	if (m_ptr >= STACK_SIZE) {
		throw std::string("Stack Underflow!");
	}
	std::memcpy(rd, m_stack + (m_ptr++), sizeof(int32_t));
	m_status = Status::STACK_OPERATE;
}