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
	Input input;
	int draw_times = 0;

public:

	Computer(std::string filename) 
		:m_memory(), m_stack(), m_register(), input(filename) {}

	/**
	* @brief 程序运行主函数
	*/
	void main();

	/**
	* @brief 绘图
	*/
	void draw();

};

#endif // !__COMPUTER_H__