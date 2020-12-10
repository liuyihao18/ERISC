#pragma once
#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "memory.h"
#include "stack.h"
#include "register.h"
#include "input.h"
#include <string>

class Computer {

private:

	Memory m_memory;
	Stack m_stack;
	Register m_register;
	Input m_input;
	int m_draw_times;

public:

	Computer(std::string filename) 
		:m_memory(), m_stack(), m_register(), m_input(filename), m_draw_times(0) {}

	/**
	* @brief ��������������
	*/
	void main();

	/**
	* @brief ��ͼ
	*/
	void draw();

	/**
	* @brief �ѼĴ������ڴ��е�ֵд���ļ�result.txt��
	*/
	void write();

};

#endif // !__COMPUTER_H__