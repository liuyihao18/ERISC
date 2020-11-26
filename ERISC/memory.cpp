#include "memory.h"

/**
	* @brief 重置状态
	*/
void Memory::reset() {

}

/**
* @brief 根据索引返回相应状态
* @param i: 索引
* @return 内存的状态
*/
Status Memory::getStatus(int i) const {

}

/**
* @brief 把rs寄存器指向的内存中的值拷贝到寄存器rd中
* @param rd: 目标寄存器地址，寄存器中存储的是一个值
* @param rs: 源寄存器地址，寄存器中存储的是内存的地址
*/
void Memory::load(int32_t* rd, int32_t* rs) {

}

/**
* @brief 把寄存器rs中的值拷贝到rd寄存器指向的内存中
* @param rs: 源寄存器地址，寄存器中存储的是一个值
* @param rd: 目标寄存器地址，寄存器中存储的是内存的地址
*/
void Memory::store(int32_t* rs, int32_t* rd) {

}

/**
* @brief 输出内存的内容
* @param out: 输出流对象
* @param reg: 输出的Memory对象
* @return 输出流对象
*/
std::ostream& operator<<(std::ostream& out, const Memory& memory) {

}