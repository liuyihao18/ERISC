#include "computer.h"

/**
* @brief 程序运行主函数
*/
void Computer::main() {
	Line current_line;
	while (input.hasMoreInput()) {
		current_line = input.getCurrentLine();
		switch (current_line.type)
		{
		case STORE:
			m_memory.store(m_register[current_line.op1], m_register[current_line.op2]);
			input.nextLine();
			break;
		case JAL:
			input.jumpLine(current_line.op1);
			break;
		default:
			break;
		}
	}
}


/**
* @brief 绘图
*/
void Computer::draw() {

}