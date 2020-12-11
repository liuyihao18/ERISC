#include "stack.h"
#include <iostream>
#include <cstring>

/**
* @brief ����״̬
*/
void Stack::reset() {
	m_status = Status::NO_OPERATE;
}

/**
* @brief ����ջ��״̬
* @return ջ��״̬
*/
Status Stack::getStatus() const {
	return m_status;
}

/**
* @brief ��rs�Ĵ����е�ֵ��ջ
* @param rs: �Ĵ����ĵ�ַ
*/
void Stack::push(int32_t* rs) {
	if (m_ptr <= 0) {
		throw std::string("Stack Overflow!");
	}
	std::memcpy(m_stack + (--m_ptr), rs, sizeof(int32_t));
	m_status = Status::STACK_OPERATE;
}

/**
* @brief ��ջ����ֵ����rd�Ĵ�����
* @param rd: �Ĵ����ĵ�ַ
*/
void Stack::pop(int32_t* rd) {
	if (m_ptr >= STACK_SIZE) {
		throw std::string("Stack Underflow!");
	}
	std::memcpy(rd, m_stack + (m_ptr++), sizeof(int32_t));
	m_status = Status::STACK_OPERATE;
}