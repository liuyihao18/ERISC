#include "memory.h"
#include <iostream>
#include <iomanip>

/**
* @brief ����״̬
*/
void Memory::reset() {
	for (auto& status : m_status) {
		status = NO_OPERATE;
	}
}

/**
* @brief ��������������Ӧ״̬
* @param i: ����
* @return �ڴ��״̬
*/
Status Memory::getStatus(int i) const {
	return m_status[i];
}

/**
* @brief ��rs�Ĵ���ָ����ڴ��е�ֵ�������Ĵ���rd��
* @param rd: Ŀ��Ĵ�����ַ���Ĵ����д洢����һ��ֵ
* @param rs: Դ�Ĵ�����ַ���Ĵ����д洢�����ڴ�ĵ�ַ
*/
void Memory::load(int32_t* rd, int32_t* rs) {
	if (*rs < 0 || *rs >= MEMORY_SIZE - 4) {
		std::cerr << "�ڴ����Խ�磡" << std::endl;
		exit(-1);
	}
	std::memcpy(rd, m_memory + *rs, sizeof(int32_t));
	m_status[*rs >> 18] = VISITED;
}

/**
* @brief �ѼĴ���rs�е�ֵ������rd�Ĵ���ָ����ڴ���
* @param rs: Դ�Ĵ�����ַ���Ĵ����д洢����һ��ֵ
* @param rd: Ŀ��Ĵ�����ַ���Ĵ����д洢�����ڴ�ĵ�ַ
*/
void Memory::store(int32_t* rs, int32_t* rd) {
	if (*rd < 0 || *rs >= MEMORY_SIZE - 4) {
		std::cerr << "�ڴ����Խ�磡" << std::endl;
		exit(-1);
	}
	std::memcpy(m_memory + *rd, rs, sizeof(int32_t));
	m_status[*rd >> 18] = VISITED;
}

/**
* @brief ����ڴ������
* @param out: ���������
* @param reg: �����Memory����
* @return ���������
*/
std::ostream& operator<<(std::ostream& out, const Memory& memory) {
	for (int i = 0; i < MEMORY_SIZE; i++) {
		if (i != 0 && i % 64 == 0) {
			out << std::endl;
		}
		out << std::hex << std::setw(2) << std::setfill('0') << memory.m_memory[i] << " ";
	}
	return out;
}