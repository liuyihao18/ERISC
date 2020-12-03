#pragma once
#ifndef __INPUT_H__
#define __INPUT_H__
#include <string>
#include <vector>

// ������
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

// ��
struct Line
{
	Type type{ NONE };
	std::string op1{};
	std::string op2{};
	std::string op3{};
};

// �б�ʶ
struct LineLable {
	std::string label{ 0 }; // �б�ʶ
	int index{ 0 };  // �б�ʶ�����е���һ��
};

// ������ʶ
struct Function {
	std::string name{}; // ������
	int index{ 0 }; // ret�����е���һ��
};

class Input {

private:

	std::vector<Line> m_lines{}; // �洢��������
	std::vector<LineLable> m_linelabels{}; // �洢�������б�ʶ
	std::vector<Function> m_functions{}; // �洢���еĺ�����ʶ
	int m_current_index{ 0 }; // ��ǰ�к�

public:
	
	/**
	* @brief ���캯��������������ļ������������нṹ
	* @param filename: �����ļ���
	*/
	Input(std::string filename);

	/**
	* @brief ��ȡ��ǰ���к�
	* @return ��ǰ���к�
	*/
	int getCurrentIndex();

	/**
	* @brief ��ȡ��ǰ����
	* @return ��ǰ�е���Ϣ
	*/
	Line getCurrentLine();

	/**
	* @brief ת����һ��
	*/
	void nextLine();

	/**
	* @brief �����б�ʶ����һ��
	* @param label: �б�ʶ
	*/
	void jumpLine(std::string label);

	/**
	* @brief ����ĳһ��
	* @param index: �к�
	*/
	void jumpLine(int index);

	/**
	* @brief �Ƿ��и��������
	* @return �жϽ��
	*/
	bool hasMoreInput();
};

#endif // !__INPUT_H__
