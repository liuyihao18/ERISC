#include "computer.h"
#include <windows.h>
#include <WINGDI.h>
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
			m_register.setStatus(current_line.op1, READ);
			m_register.setStatus(current_line.op2, READ);
			input.nextLine();
			break;
		case PUSH:
			m_stack.push(m_register[current_line.op1]);
			m_register.setStatus(current_line.op1, READ);
			break;
		case POP:
			m_stack.pop(m_register[current_line.op1]);
			m_register.setStatus(current_line.op1,READ);
			break;
		case MOV:
			m_register.mov(current_line.op1, current_line.op2);
			if(current_line.op2[0]!='0'){
				m_register.setStatus(current_line.op2, READ);
			}
			break;
		case ADD:
			m_register.add(current_line.op1, current_line.op2,current_line.op3);
			if (current_line.op3[0] != '0') {
				m_register.setStatus(current_line.op3, READ);
			}
			break;
		case SUB:
			m_register.sub(current_line.op1, current_line.op2,current_line.op3);
			if (current_line.op3[0] != '0') {
				m_register.setStatus(current_line.op3, READ);
			}
			break;
		case MUL:
			m_register.mul(current_line.op1, current_line.op2, current_line.op3);
			if (current_line.op3[0] != '0') {
				m_register.setStatus(current_line.op3, READ);
			}
			break;
		case DIV:
			m_register.div(current_line.op1, current_line.op2, current_line.op3);
			if (current_line.op3[0] != '0') {
				m_register.setStatus(current_line.op3, READ);
			}
			break;
		case REM:
			m_register.rem(current_line.op1, current_line.op2, current_line.op3);
			if (current_line.op3[0] != '0') {
				m_register.setStatus(current_line.op3, READ);
			}
			break;
		case AND:
			m_register.AND(current_line.op1, current_line.op2, current_line.op3);
			if (current_line.op3[0] != '0') {
				m_register.setStatus(current_line.op3, READ);
			}
			break;
		case OR:
			m_register.OR(current_line.op1, current_line.op2, current_line.op3);
			if (current_line.op3[0] != '0') {
				m_register.setStatus(current_line.op3, READ);
			}
			break;
		case LINE_LABLE:
			break;
		case JAL:
			input.jumpLine(current_line.op1);
			break;
		case BEQ:
			if (m_register.beq(current_line.op1, current_line.op2)) {
				input.jumpLine(current_line.op3);
			}
			break;
		case BNE:
			if (m_register.bne(current_line.op1, current_line.op2)) {
				input.jumpLine(current_line.op3);
			}
			break;
		case BLT:
			if (m_register.blt(current_line.op1, current_line.op2)) {
				input.jumpLine(current_line.op3);
			}
			break;
		case BGE:
			if (m_register.bge(current_line.op1, current_line.op2)) {
				input.jumpLine(current_line.op3);
			}
			break;
		case CALL:
			m_stack.push(input.getCurrentIndex+1);
			input.jumpLine(current_line.op1);
			break;
		case RET:
			int* temp=new int();
			m_stack.pop(temp);
			input.jumpLine(*temp);
			delete temp;
		case DRAW:
		case END:
		case TYPE_SIZE:
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