#pragma once
#ifndef __MEMORY_H__
#define __MEMORY_H__
#include "status.h"
#include <cstdint>
#include <ostream>

constexpr int MEMORY_SIZE = 4 * 1024 * 1024; // �ڴ��С
constexpr int MEMORY_STATUS_SIZE = 16; // �ڴ�״̬��С

class Memory {

private:

	int8_t* m_memory; // �ڴ�洢������
	Status m_status[MEMORY_STATUS_SIZE]{ NO_OPERATE }; // �ڴ�ķ���

public:
	
	Memory() :m_memory(new int8_t[MEMORY_SIZE]()) {}

	~Memory() { delete[] m_memory; }

	/**
	* @brief ����״̬
	*/
	void reset();

	/**
	* @brief ��������������Ӧ״̬
	* @param i: ����
	* @return �ڴ��״̬
	*/
	Status getStatus(int i) const;

	/**
	* @brief ��rs�Ĵ���ָ����ڴ��е�ֵ�������Ĵ���rd��
	* @param rd: Ŀ��Ĵ�����ַ���Ĵ����д洢����һ��ֵ
	* @param rs: Դ�Ĵ�����ַ���Ĵ����д洢�����ڴ�ĵ�ַ
	*/
	void load(int32_t* rd, int32_t* rs);

	/**
	* @brief �ѼĴ���rs�е�ֵ������rd�Ĵ���ָ����ڴ���
	* @param rs: Դ�Ĵ�����ַ���Ĵ����д洢����һ��ֵ
	* @param rd: Ŀ��Ĵ�����ַ���Ĵ����д洢�����ڴ�ĵ�ַ
	*/
	void store(int32_t* rs, int32_t* rd);

	/**
	* @brief ����ڴ������
	* @param out: ���������
	* @param reg: �����Memory����
	* @return ���������
	*/
	friend std::ostream& operator<<(std::ostream& out, const Memory& memory);
};

#endif // !__MEMORY_H__
