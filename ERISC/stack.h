#pragma once
#ifndef __STACK_H__
#define __STACK_H__
#include "status.h"
#include <cstdint>

constexpr int STACK_SIZE = 1024 * 1024; // 栈的大小

class Stack {

private:

	int32_t* m_stack; // 栈存储的内容
	Status m_status{ Status::NO_OPERATE }; // 栈的访问
	int m_ptr{ STACK_SIZE }; // 栈顶指针

public:

	Stack() :m_stack(new int32_t[STACK_SIZE]()) {}

	~Stack() { delete[] m_stack; }

	/**
	* @brief 重置状态
	*/
	void reset();

	/**
	* @brief 返回栈的状态
	* @return 栈的状态
	*/
	Status getStatus() const;

	/**
	* @brief 把rs寄存器中的值入栈
	* @param rs: 寄存器的地址
	*/
	void push(int32_t* rs);

	/**
	* @brief 把栈顶的值存入rd寄存器中
	* @param rd: 寄存器的地址
	*/
	void pop(int32_t* rd);

};

#endif // !__STACK_H__
