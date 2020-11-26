#pragma once
#ifndef __MEMORY_H__
#define __MEMORY_H__
#include "status.h"
#include <cstdint>
#include <ostream>

constexpr int MEMORY_SIZE = 4 * 1024 * 1024; // 内存大小
constexpr int MEMORY_STATUS_SIZE = 16; // 内存状态大小

class Memory {

private:

	int8_t* m_memory; // 内存存储的内容
	Status m_status[MEMORY_STATUS_SIZE]{ NO_OPERATE }; // 内存的访问

public:
	
	Memory() :m_memory(new int8_t[MEMORY_SIZE]()) {}

	~Memory() { delete[] m_memory; }

	/**
	* @brief 重置状态
	*/
	void reset();

	/**
	* @brief 根据索引返回相应状态
	* @param i: 索引
	* @return 内存的状态
	*/
	Status getStatus(int i) const;

	/**
	* @brief 把rs寄存器指向的内存中的值拷贝到寄存器rd中
	* @param rd: 目标寄存器地址，寄存器中存储的是一个值
	* @param rs: 源寄存器地址，寄存器中存储的是内存的地址
	*/
	void load(int32_t* rd, int32_t* rs);

	/**
	* @brief 把寄存器rs中的值拷贝到rd寄存器指向的内存中
	* @param rs: 源寄存器地址，寄存器中存储的是一个值
	* @param rd: 目标寄存器地址，寄存器中存储的是内存的地址
	*/
	void store(int32_t* rs, int32_t* rd);

	/**
	* @brief 输出内存的内容
	* @param out: 输出流对象
	* @param reg: 输出的Memory对象
	* @return 输出流对象
	*/
	friend std::ostream& operator<<(std::ostream& out, const Memory& memory);
};

#endif // !__MEMORY_H__
