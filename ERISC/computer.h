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

	/**
	* @brief 构造函数
	* @param filename: 输入的ERISC文件名
	*/
	Computer(std::string filename) 
		:m_memory(), m_stack(), m_register(), m_input(filename), m_draw_times(0) {}

	/**
	* @brief 程序运行主函数
	*/
	void main();

	/**
	* @brief 绘图
	*/
	void draw();

	/**
	* @brief 把寄存器、内存中的值写到文件result.txt中
	*/
	void write();

};

#endif // !__COMPUTER_H__