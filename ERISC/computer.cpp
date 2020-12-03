#include "computer.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <memory.h>
#include <stdlib.h>
#include <fstream>

#pragma pack(2)
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long    LONG;
typedef struct {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER;

/**
* @brief 程序运行主函数
*/
void Computer::main() {
	// 主循环
	while (input.hasMoreInput()) {
		Line current_line = input.getCurrentLine();
		int temp{ 0 };
		switch (current_line.type)
		{
		case LOAD:
			m_memory.load(m_register[current_line.op1], m_register[current_line.op2]);
			m_register.setStatus(current_line.op1, WRITE);
			m_register.setStatus(current_line.op2, READ);
			input.nextLine();
			break;
		case STORE:
			m_memory.store(m_register[current_line.op1], m_register[current_line.op2]);
			m_register.setStatus(current_line.op1, READ);
			m_register.setStatus(current_line.op2, READ);
			input.nextLine();
			break;
		case PUSH:
			m_stack.push(m_register[current_line.op1]);
			m_register.setStatus(current_line.op1, READ);
			input.nextLine();
			break;
		case POP:
			m_stack.pop(m_register[current_line.op1]);
			m_register.setStatus(current_line.op1, WRITE);
			input.nextLine();
			break;
		case MOV:
			m_register.mov(current_line.op1, current_line.op2);
			input.nextLine();
			break;
		case ADD:
			m_register.add(current_line.op1, current_line.op2, current_line.op3);
			input.nextLine();
			break;
		case SUB:
			m_register.sub(current_line.op1, current_line.op2, current_line.op3);
			input.nextLine();
			break;
		case MUL:
			m_register.mul(current_line.op1, current_line.op2, current_line.op3);
			input.nextLine();
			break;
		case DIV:
			m_register.div(current_line.op1, current_line.op2, current_line.op3);
			input.nextLine();
			break;
		case REM:
			m_register.rem(current_line.op1, current_line.op2, current_line.op3);
			input.nextLine();
			break;
		case AND:
			m_register.AND(current_line.op1, current_line.op2, current_line.op3);
			input.nextLine();
			break;
		case OR:
			m_register.OR(current_line.op1, current_line.op2, current_line.op3);
			input.nextLine();
			break;
		case LINE_LABLE:
			input.nextLine();
			break;
		case JAL:
			input.jumpLine(current_line.op1);
			break;
		case BEQ:
			if (m_register.beq(current_line.op1, current_line.op2)) {
				input.jumpLine(current_line.op3);
			}
			else {
				input.nextLine();
			}
			break;
		case BNE:
			if (m_register.bne(current_line.op1, current_line.op2)) {
				input.jumpLine(current_line.op3);
			}
			else {
				input.nextLine();
			}
			break;
		case BLT:
			if (m_register.blt(current_line.op1, current_line.op2)) {
				input.jumpLine(current_line.op3);
			}
			else {
				input.nextLine();
			}
			break;
		case BGE:
			if (m_register.bge(current_line.op1, current_line.op2)) {
				input.jumpLine(current_line.op3);
			}
			else {
				input.nextLine();
			}
			break;
		case CALL:
			temp = input.getCurrentIndex() + 1;
			m_stack.push(&temp);
			input.jumpLine(current_line.op1);
			break;
		case RET:
			m_stack.pop(&temp);
			input.jumpLine(temp);
			break;
		case DRAW:
			draw();
			input.nextLine();
			break;
		case END:
			write();
			return;
		default:
			std::cerr << "未知行种类！" << std::endl;
			exit(-1);
			break;
		}
	}
}


/**
* @brief 绘图
*/
void Computer::draw() {
	++draw_times;
	// Define BMP Size
	const int height = 300;
	const int width = 1040;
	const int size = height * width * 3;
	int x, y;
	int index;

	// Part.1 Create Bitmap File Header
	BITMAPFILEHEADER fileHeader;

	fileHeader.bfType = 0x4D42;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size;
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// Part.2 Create Bitmap Info Header
	BITMAPINFOHEADER bitmapHeader = { 0 };

	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biHeight = height;
	bitmapHeader.biWidth = width;
	bitmapHeader.biPlanes = 3;
	bitmapHeader.biBitCount = 24;
	bitmapHeader.biSizeImage = size;
	bitmapHeader.biCompression = 0; //BI_RGB

	// Part.3 Create Data
	BYTE* bits = (BYTE*)malloc(size);

	// Clear
	memset(bits, 0xFF, size);

	// 上下两条边框线
	for (x = 0; x < width; x += 1)
	{
		for (int i = 0; i <= 1; i++) {
			y = 200 * i;
			index = (int)y * width * 3 + (int)x * 3;

			bits[index + 0] = 0; // Blue
			bits[index + 1] = 0;   // Green
			bits[index + 2] = 0;   // Red
		}
	}
	//中间三条边框线
	for (x = 0; x < width - 240; x += 1)
	{
		for (int j = 1; j <= 3; j++) {
			y = 50 * j;
			index = (int)y * width * 3 + (int)x * 3;
			bits[index + 0] = 0; // Blue
			bits[index + 1] = 0;   // Green
			bits[index + 2] = 0;   // Red
		}
	}
	//寄存器部分竖线
	for (y = 0; y < height - 100; y += 1)
	{
		for (x = 0; x <= width - 240 - 200; x += 75) {
			index = (int)y * width * 3 + (int)x * 3;

			bits[index + 0] = 0; // Blue
			bits[index + 1] = 0;   // Green
			bits[index + 2] = 0;   // Red
		}
	}
	//栈空间部分竖线
	for (y = 0; y < height - 100; y += 1)
	{
		for (x = 600; x <= width - 240; x += 50) {
			index = (int)y * width * 3 + (int)x * 3;

			bits[index + 0] = 0; // Blue
			bits[index + 1] = 0;   // Green
			bits[index + 2] = 0;   // Red
		}
	}
	//最右端竖线
	for (y = 0; y < height - 100; y += 1)
	{
		x = width - 1;
		index = (int)y * width * 3 + (int)x * 3;

		bits[index + 0] = 0; // Blue
		bits[index + 1] = 0;   // Green
		bits[index + 2] = 0;   // Red
	}
	//寄存器绘制
	for (int i = 0; i < 32; i++) {
		int x_start, y_start;
		x_start = 75 * (i % 8) + 1;
		y_start = 200 - 50 * (i / 8) - 1;
		int x_end, y_end;
		x_end = x_start + 73;
		y_end = y_start - 48;
		switch (m_register.getStatus(i)) {
		case NO_OPERATE:
			break;
		case WRITE:
			for (x = x_start; x <= x_end; x++) {
				for (y = y_start; y >= y_end; y--) {
					index = y * width * 3 + x * 3;
					bits[index + 0] = 0;	//blue
					bits[index + 1] = 0;	//green
					bits[index + 2] = 255;	//red
				}
			}
			break;
		case READ:
			for (x = x_start; x <= x_end; x++) {
				for (y = y_start; y >= y_end; y--) {
					index = y * width * 3 + x * 3;
					bits[index + 0] = 255;	//blue
					bits[index + 1] = 0;	//green
					bits[index + 2] = 0;	//red
				}
			}
			break;
		case READ_WRITE:
			for (x = x_start; x <= x_end; x++) {
				for (y = y_start; y >= y_end; y--) {
					index = y * width * 3 + x * 3;
					bits[index + 0] = 255;	//blue
					bits[index + 1] = 0;	//green
					bits[index + 2] = 255;	//red
				}
			}
			break;
		}
	}
	//寄存器绘制完成

	//内存空间绘制
	for (int i = 0; i < 16; i++) {
		int x_start, y_start;
		x_start = 600 + (i % 4) * 50 + 1;
		y_start = 200 - 50 * (i / 4) - 1;
		int x_end, y_end;
		x_end = x_start + 48;
		y_end = y_start - 48;
		switch (m_memory.getStatus(i)) {
		case NO_OPERATE:
			break;
		case VISITED:
			for (x = x_start; x <= x_end; x++) {
				for (y = y_start; y >= y_end; y--) {
					index = y * width * 3 + x * 3;
					bits[index + 0] = 0;	//blue
					bits[index + 1] = 255;	//green
					bits[index + 2] = 0;	//red
				}
			}
			break;
		}
	}
	//内存绘制完成
	//栈空间绘制
	{
		int x_start, y_start;
		x_start = 800 + 1;
		y_start = 200 - 1;
		int x_end, y_end;
		x_end = width - 2;
		y_end = 1;
		if (m_stack.getStatus() == STACK_OPERATE) {
			for (x = x_start; x <= x_end; x++) {
				for (y = y_start; y >= y_end; y--) {
					index = y * width * 3 + x * 3;
					bits[index + 0] = 0;	//blue
					bits[index + 1] = 192;	//green
					bits[index + 2] = 255;	//red
				}
			}
		}
	}
	//栈空间绘制完成
	// Write to file
	char num_str[50];
	sprintf(num_str, "%x", draw_times);
	strcat(num_str, ".bmp");
	FILE* output = fopen(num_str, "wb");

	std::ofstream file(num_str);
	if (!file.is_open()) {
		std::cerr << "绘制bmp图像到文件时错误";
		exit(-1);
	}
	if (output == NULL)
	{
		printf("Cannot open file!\n");
	}
	else
	{
		fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, output);
		fwrite(&bitmapHeader, sizeof(BITMAPINFOHEADER), 1, output);
		fwrite(bits, size, 1, output);
		fclose(output);
	}
	//重置状态
	m_memory.reset();
	m_stack.reset();
	m_register.reset();
}

/**
* @brief 把寄存器、内存中的值写到文件result.txt中
*/
void Computer::write() {
	std::ofstream file("result.txt");
	if (!file.is_open()) {
		std::cerr << "end命令输出文件时出现错误" << std::endl;
		exit(-1);
	}
	file << m_register << std::endl;
	file << m_memory;
	file.close();
}