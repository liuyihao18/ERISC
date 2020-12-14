#pragma once
#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "memory.h"
#include "stack.h"
#include "register.h"
#include "input.h"
#include <string>
#include <iostream>
#if defined WINDOWS
#include <io.h>
#elif defined LINUX || defined UNIX
#include <unistd.h>
#endif
#include <direct.h>

class Computer {

private:

	Memory m_memory;
	Stack m_stack;
	Register m_register;
	Input m_input;
	int m_draw_times;

public:

	/**
	* @brief ���캯��
	* @param filename: �����ERISC�ļ���
	*/
	Computer(std::string filename) 
		:m_memory(), m_stack(), m_register(), m_input(filename), m_draw_times(0) {
		if (_access("output", 0) != 0) {
			if (_mkdir("output") != 0) {
				std::cerr << "��������ļ���ʧ�ܣ�" << std::endl;
			}
		}
	}

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