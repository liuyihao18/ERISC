#pragma once
#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "memory.h"
#include "stack.h"
#include "register.h"
#include "input.h"
#include <cstring>
#include <string>
#include <iostream>
#if defined WINDOWS
#include <io.h>
#include <direct.h>
#elif defined LINUX || defined UNIX
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#endif

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
		:m_memory(), m_stack(), m_register(), m_input(filename), m_draw_times(0) {
		if ( // 判断输出文件夹是否存在
#if defined WINDOWS
			_access("output", 0) != 0
#elif defined LINUX || defined UNIX
			access("output", 0) != 0
#else 
			false
#endif
			) {
			if ( // 如果不存在则创建
#if defined WINDOWS
				_mkdir("output") != 0
#elif defined LINUX || defined UNIX
				mkdir("output", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0
#else
				false
#endif
				) {
				std::cerr << "创建输出文件夹失败！" << std::endl;
				std::exit(-1);
			}
		}
		else { // 如果存在则删除原先的输出文件
#if defined WINDOWS
			_finddata_t file;
			auto handle = _findfirst("output/*", &file);
			while (handle != 0 && _findnext(handle, &file) == 0) {
				if (std::strcmp(file.name, "..") != 0 && std::strcmp(file.name, ".") != 0) {
					std::string filename{ "output/" };
					filename += file.name;
					if (remove(filename.c_str()) != 0) {
						std::cerr << "删除旧文件失败！" << std::endl;
						std::exit(-1);
					}
				}
			}
#elif defined LINUX || defined UNIX
			dirent* entry{ nullptr };
			DIR* dir = opendir("output");
			if (!dir) {
				std::cerr << "打开输出文件夹失败！" << std::endl;
				exit(-1);
			}
			while (entry = readdir(dir)) {
				if (std::strcmp(entry->d_name, ".") == 0 || std::strcmp(entry->d_name, "..") == 0)
				{
					continue;
				}
				std::string filename{ "output/" };
				filename += entry->d_name;
				if (remove(filename.c_str()) != 0) {
					std::cerr << "删除旧文件失败！" << std::endl;
					std::exit(-1);
				}
			}
#endif
		}
	}

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