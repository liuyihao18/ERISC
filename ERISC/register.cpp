#include "register.h"

/**
* @brief ����״̬
*/
void Register::reset() {

}

/**
* @brief �������ַ�����Ӧ�Ĵ����ĵ�ַ
* @param name: �Ĵ���������
* @return �Ĵ����ĵ�ַ
*/
int32_t* Register::operator[](const std::string& name) {

}

/**
* @brief ��������������Ӧ״̬
* @param i: ����
* @return �Ĵ�����״̬
*/
Status Register::getStatus(int i) const {

}

/**
* @brief ���Ĵ���rs��ֵ��������imm�����Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs_or_imm: Դ�Ĵ��������ֻ���������
*/
void Register::mov(const std::string& rd, const std::string& rs_or_imm) {

}

/**
* @brief ���Ĵ���rs1��ֵ���ϼĴ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::add(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {

}

/**
* @brief ���Ĵ���rs1��ֵ��ȥ�Ĵ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::sub(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {

}

/**
* @brief ���Ĵ���rs1��ֵ���ϼĴ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::mul(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {

}

/**
* @brief ���Ĵ���rs1��ֵ��ȥ�Ĵ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::div(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {

}

/**
* @brief ���Ĵ���rs1��ֵģ�ϼĴ���rs2��ֵ��������imm�󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::rem(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {

}

/**
* @brief ���Ĵ���rs1��ֵ��Ĵ���rs2��ֵ��������immλ��󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::AND(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {

}

/**
* @brief ���Ĵ���rs1��ֵ��Ĵ���rs2��ֵ��������immλ��󸳸��Ĵ���rd
* @param rd: Ŀ��Ĵ���������
* @param rs1: Դ�Ĵ���1������
* @param rs2_or_imm: Դ�Ĵ���2�����ֻ���������
*/
void Register::OR(const std::string& rd, const std::string& rs1, const std::string& rs2_or_imm) {

}

/**
* @brief �жϼĴ���rs1�ͼĴ���rs2��ֵ�Ƿ����
* @param rs1: Դ�Ĵ���1������
* @param rs2: Դ�Ĵ���2������
* @return �жϽ��
*/
bool Register::beq(const std::string& rs1, const std::string& rs2) const {

}

/**
* @brief �жϼĴ���rs1�ͼĴ���rs2��ֵ�Ƿ񲻵�
* @param rs1: Դ�Ĵ���1������
* @param rs2: Դ�Ĵ���2������
* @return �жϽ��
*/
bool Register::bne(const std::string& rs1, const std::string& rs2) const {

}

/**
* @brief �жϼĴ���rs1��ֵ�Ƿ�С�ڼĴ���rs2��ֵ
* @param rs1: Դ�Ĵ���1������
* @param rs2: Դ�Ĵ���2������
* @return �жϽ��
*/
bool Register::blt(const std::string& rs1, const std::string& rs2) const {

}

/**
* @brief �жϼĴ���rs1��ֵ�Ƿ���ڵ��ڼĴ���rs2��ֵ
* @param rs1: Դ�Ĵ���1������
* @param rs2: Դ�Ĵ���2������
* @return �жϽ��
*/
bool Register::bge(const std::string& rs1, const std::string& rs2) const {

}

/**
* @brief ����Ĵ���������
* @param out: ���������
* @param reg: �����Register����
* @return ���������
*/
std::ostream& operator<<(std::ostream& out, const Register& reg) {

}