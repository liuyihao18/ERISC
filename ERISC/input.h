#pragma once
#ifndef __INPUT_H__
#define __INPUT_H__
#include <string>
#include <vector>

// 行种类
enum Type {
	NONE = 0,
	LOAD,
	STORE,
	PUSH,
	POP,
	MOV,
	ADD,
	SUB,
	MUL,
	DIV,
	REM,
	AND,
	OR,
	LINE_LABLE,
	JAL,
	BEQ,
	BNE,
	BLT,
	BGE,
	CALL,
	RET,
	DRAW,
	END,
	TYPE_SIZE
};

// 行
struct Line
{
	Type type{ NONE };
	std::string op1{};
	std::string op2{};
	std::string op3{};
};

// 行标识
struct LineLable {
	std::string label{ 0 }; // 行标识
	int index{ 0 };  // 行标识所在行的下一行
};

// 函数标识
struct Function {
	std::string name{}; // 函数名
	int index{ 0 }; // ret所在行的下一行
};

class Input {

private:

	std::vector<Line> m_lines{}; // 存储的所有行
	std::vector<LineLable> m_linelabels{}; // 存储的所有行标识
	std::vector<Function> m_functions{}; // 存储所有的函数标识
	int m_current_index{ 0 }; // 当前行号

public:
	
	/**
	* @brief 构造函数，根据输入的文件名构造整个行结构
	* @param filename: 输入文件名
	*/
	Input(std::string filename);

	/**
	* @brief 获取当前的行号
	* @return 当前的行号
	*/
	int getCurrentIndex();

	/**
	* @brief 获取当前的行
	* @return 当前行的信息
	*/
	Line getCurrentLine();

	/**
	* @brief 转到下一行
	*/
	void nextLine();

	/**
	* @brief 跳到行标识的下一行
	* @param label: 行标识
	*/
	void jumpLine(std::string label);

	/**
	* @brief 跳到某一行
	* @param index: 行号
	*/
	void jumpLine(int index);

	/**
	* @brief 是否还有更多的输入
	* @return 判断结果
	*/
	bool hasMoreInput();
};

#endif // !__INPUT_H__
