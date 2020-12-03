#pragma once
#ifndef __STACK_H__
#define __STACK_H__
#include "status.h"
#include <cstdint>

constexpr int STACK_SIZE = 1024 * 1024; // ջ�Ĵ�С

class Stack {

private:

	int32_t* m_stack; // ջ�洢������
	Status m_status{ Status::NO_OPERATE }; // ջ�ķ���
	int m_ptr{ STACK_SIZE }; // ջ��ָ��

public:

	Stack() :m_stack(new int32_t[STACK_SIZE]()) {}

	~Stack() { delete[] m_stack; }

	/**
	* @brief ����״̬
	*/
	void reset();

	/**
	* @brief ����ջ��״̬
	* @return ջ��״̬
	*/
	Status getStatus() const;

	/**
	* @brief ��rs�Ĵ����е�ֵ��ջ
	* @param rs: �Ĵ����ĵ�ַ
	*/
	void push(int32_t* rs);

	/**
	* @brief ��ջ����ֵ����rd�Ĵ�����
	* @param rd: �Ĵ����ĵ�ַ
	*/
	void pop(int32_t* rd);

};

#endif // !__STACK_H__
