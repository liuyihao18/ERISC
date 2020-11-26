#pragma once
#ifndef __REGISTER_H__
#define __REGISTER_H__
#include "status.h"
#include <cstdint>
#include <string>
#include <ostream>

constexpr int REGISTER_SIZE = 32; // 寄存器大小

class Register {

private:

	int32_t m_register[REGISTER_SIZE]{ 0 }; // 寄存器存储的内容
	Status m_status[REGISTER_SIZE]{ NO_OPERATE }; // 寄存器的访问

	/**
	* @brief 根据名字获取寄存器的索引
	* @param 寄存器的名字
	* @return 寄存器的索引
	*/
	int lookup(const std::string& name);

public:

	/**
	* @brief 重置状态
	*/
	void reset();

	/**
	* @brief 根据名字返回相应寄存器的地址
	* @param name: 寄存器的名字
	* @return 寄存器的地址
	*/
	int32_t* operator[](const std::string& name);

	/**
	* @brief 根据索引返回相应状态
	* @param i: 索引
	* @return 寄存器的状态
	*/
	Status getStatus(int i) const;

	/**
	* @brief 将寄存器rs的值或立即数imm赋给寄存器rd
	* @param rd: 目标寄存器的名字
	* @param rs_or_imm: 源寄存器的名字或者立即数
	*/
	void mov(const std::string& rd, const std::string& rs_or_imm);

	/**
	* @brief 将寄存器rs1的值加上寄存器rs2的值或立即数imm后赋给寄存器rd
	* @param rd: 目标寄存器的名字
	* @param rs1: 源寄存器1的名字
	* @param rs2_or_imm: 源寄存器2的名字或者立即数
	*/
	void add(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief 将寄存器rs1的值减去寄存器rs2的值或立即数imm后赋给寄存器rd
	* @param rd: 目标寄存器的名字
	* @param rs1: 源寄存器1的名字
	* @param rs2_or_imm: 源寄存器2的名字或者立即数
	*/
	void sub(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief 将寄存器rs1的值乘上寄存器rs2的值或立即数imm后赋给寄存器rd
	* @param rd: 目标寄存器的名字
	* @param rs1: 源寄存器1的名字
	* @param rs2_or_imm: 源寄存器2的名字或者立即数
	*/
	void mul(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief 将寄存器rs1的值除去寄存器rs2的值或立即数imm后赋给寄存器rd
	* @param rd: 目标寄存器的名字
	* @param rs1: 源寄存器1的名字
	* @param rs2_or_imm: 源寄存器2的名字或者立即数
	*/
	void div(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief 将寄存器rs1的值模上寄存器rs2的值或立即数imm后赋给寄存器rd
	* @param rd: 目标寄存器的名字
	* @param rs1: 源寄存器1的名字
	* @param rs2_or_imm: 源寄存器2的名字或者立即数
	*/
	void rem(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief 将寄存器rs1的值与寄存器rs2的值或立即数imm位与后赋给寄存器rd
	* @param rd: 目标寄存器的名字
	* @param rs1: 源寄存器1的名字
	* @param rs2_or_imm: 源寄存器2的名字或者立即数
	*/
	void AND(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief 将寄存器rs1的值与寄存器rs2的值或立即数imm位或后赋给寄存器rd
	* @param rd: 目标寄存器的名字
	* @param rs1: 源寄存器1的名字
	* @param rs2_or_imm: 源寄存器2的名字或者立即数
	*/
	void OR(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief 判断寄存器rs1和寄存器rs2中值是否相等
	* @param rs1: 源寄存器1的名字
	* @param rs2: 源寄存器2的名字
	* @return 判断结果
	*/
	bool beq(const std::string& rs1, const std::string& rs2) const;

	/**
	* @brief 判断寄存器rs1和寄存器rs2中值是否不等
	* @param rs1: 源寄存器1的名字
	* @param rs2: 源寄存器2的名字
	* @return 判断结果
*/
	bool bne(const std::string& rs1, const std::string& rs2) const;

	/**
	* @brief 判断寄存器rs1的值是否小于寄存器rs2中值
	* @param rs1: 源寄存器1的名字
	* @param rs2: 源寄存器2的名字
	* @return 判断结果
	*/
	bool blt(const std::string& rs1, const std::string& rs2) const;

	/**
	* @brief 判断寄存器rs1的值是否大于等于寄存器rs2中值
	* @param rs1: 源寄存器1的名字
	* @param rs2: 源寄存器2的名字
	* @return 判断结果
	*/
	bool bge(const std::string& rs1, const std::string& rs2) const;

	/**
	* @brief 输出寄存器的内容
	* @param out: 输出流对象
	* @param reg: 输出的Register对象
	* @return 输出流对象
	*/
	friend std::ostream& operator<<(std::ostream& out, const Register& reg);
};

#endif // !__REGISTER_H__
