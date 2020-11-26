#include "input.h"

/**
	* @brief 构造函数，根据输入的文件名构造整个行结构
	* @param filename: 输入文件名
	*/
Input::Input(std::string filename) {

}

/**
* @brief 获取当前的行号
* @return 当前的行号
*/
int Input::getCurrentIndex() { 
	return m_current_indx; 
}

/**
* @brief 获取当前的行
* @return 当前行的信息
*/
Line Input::getCurrentLine() {

}

/**
* @brief 转到下一行
*/
void Input::nextLine() {

}

/**
* @brief 跳到行标识的下一行
* @param label: 行标识
*/
void Input::jumpLine(std::string lable) {

}

/**
* @brief 跳到某一行
* @param index: 行号
*/
void Input::jumpLine(int index) {

}

/**
* @brief 是否还有更多的输入
* @return 判断结果
*/
bool Input::hasMoreInput() {

}