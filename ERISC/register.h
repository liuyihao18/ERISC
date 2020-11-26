#pragma once
#ifndef __REGISTER_H__
#define __REGISTER_H__
#include "status.h"
#include <cstdint>
#include <string>
#include <ostream>

constexpr int REGISTER_SIZE = 32; // �Ĵ�����С

class Register {

private:

	int32_t m_register[REGISTER_SIZE]{ 0 }; // �Ĵ����洢������
	Status m_status[REGISTER_SIZE]{ NO_OPERATE }; // �Ĵ����ķ���

	/**
	* @brief �������ֻ�ȡ�Ĵ���������
	* @param �Ĵ���������
	* @return �Ĵ���������
	*/
	int lookup(const std::string& name);

public:

	/**
	* @brief ����״̬
	*/
	void reset();

	/**
	* @brief �������ַ�����Ӧ�Ĵ����ĵ�ַ
	* @param name: �Ĵ���������
	* @return �Ĵ����ĵ�ַ
	*/
	int32_t* operator[](const std::string& name);

	/**
	* @brief ��������������Ӧ״̬
	* @param i: ����
	* @return �Ĵ�����״̬
	*/
	Status getStatus(int i) const;

	/**
	* @brief ���Ĵ���rs��ֵ��������imm�����Ĵ���rd
	* @param rd: Ŀ��Ĵ���������
	* @param rs_or_imm: Դ�Ĵ��������ֻ���������
	*/
	void mov(const std::string& rd, const std::string& rs_or_imm);

	/**
	* @brief ���Ĵ���rs1��ֵ���ϼĴ���rs2��ֵ��������imm�󸳸��Ĵ���rd
	* @param rd: Ŀ��Ĵ���������
	* @param rs1: Դ�Ĵ���1������
	* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
	*/
	void add(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief ���Ĵ���rs1��ֵ��ȥ�Ĵ���rs2��ֵ��������imm�󸳸��Ĵ���rd
	* @param rd: Ŀ��Ĵ���������
	* @param rs1: Դ�Ĵ���1������
	* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
	*/
	void sub(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief ���Ĵ���rs1��ֵ���ϼĴ���rs2��ֵ��������imm�󸳸��Ĵ���rd
	* @param rd: Ŀ��Ĵ���������
	* @param rs1: Դ�Ĵ���1������
	* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
	*/
	void mul(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief ���Ĵ���rs1��ֵ��ȥ�Ĵ���rs2��ֵ��������imm�󸳸��Ĵ���rd
	* @param rd: Ŀ��Ĵ���������
	* @param rs1: Դ�Ĵ���1������
	* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
	*/
	void div(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief ���Ĵ���rs1��ֵģ�ϼĴ���rs2��ֵ��������imm�󸳸��Ĵ���rd
	* @param rd: Ŀ��Ĵ���������
	* @param rs1: Դ�Ĵ���1������
	* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
	*/
	void rem(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief ���Ĵ���rs1��ֵ��Ĵ���rs2��ֵ��������immλ��󸳸��Ĵ���rd
	* @param rd: Ŀ��Ĵ���������
	* @param rs1: Դ�Ĵ���1������
	* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
	*/
	void AND(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief ���Ĵ���rs1��ֵ��Ĵ���rs2��ֵ��������immλ��󸳸��Ĵ���rd
	* @param rd: Ŀ��Ĵ���������
	* @param rs1: Դ�Ĵ���1������
	* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
	*/
	void OR(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm);

	/**
	* @brief �жϼĴ���rs1�ͼĴ���rs2��ֵ�Ƿ����
	* @param rs1: Դ�Ĵ���1������
	* @param rs2: Դ�Ĵ���2������
	* @return �жϽ��
	*/
	bool beq(const std::string& rs1, const std::string& rs2) const;

	/**
	* @brief �жϼĴ���rs1�ͼĴ���rs2��ֵ�Ƿ񲻵�
	* @param rs1: Դ�Ĵ���1������
	* @param rs2: Դ�Ĵ���2������
	* @return �жϽ��
*/
	bool bne(const std::string& rs1, const std::string& rs2) const;

	/**
	* @brief �жϼĴ���rs1��ֵ�Ƿ�С�ڼĴ���rs2��ֵ
	* @param rs1: Դ�Ĵ���1������
	* @param rs2: Դ�Ĵ���2������
	* @return �жϽ��
	*/
	bool blt(const std::string& rs1, const std::string& rs2) const;

	/**
	* @brief �жϼĴ���rs1��ֵ�Ƿ���ڵ��ڼĴ���rs2��ֵ
	* @param rs1: Դ�Ĵ���1������
	* @param rs2: Դ�Ĵ���2������
	* @return �жϽ��
	*/
	bool bge(const std::string& rs1, const std::string& rs2) const;

	/**
	* @brief ����Ĵ���������
	* @param out: ���������
	* @param reg: �����Register����
	* @return ���������
	*/
	friend std::ostream& operator<<(std::ostream& out, const Register& reg);
};

#endif // !__REGISTER_H__
