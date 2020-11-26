#include "stack.h"
#include <iostream>

/**
* @brief ����״̬
*/
void Stack::reset() {
	m_status = NO_OPERATE;
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
		std::cerr << "Stack Overflow!" << std::endl;
		exit(-1);
	}
	std::memcpy(m_stack + (--m_ptr), rs, sizeof(int32_t));
	m_status = STACK_OPERATE;
}

/**
* @brief ��ջ����ֵ����rd�Ĵ�����
* @param rd: �Ĵ����ĵ�ַ
*/
void Stack::pop(int32_t* rd) {
	if (m_ptr >= STACK_SIZE) {
		std::cerr << "��ջ��ջ��" << std::endl;
		exit(-1);
	}
	std::memcpy(rd, m_stack + (m_ptr++), sizeof(int32_t));
	m_status = STACK_OPERATE;
}