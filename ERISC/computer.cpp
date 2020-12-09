#include "computer.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>

using BYTE = unsigned char;
using WORD = unsigned short;
using DWORD = unsigned long;
using LONG = long;

#pragma pack(2)
struct BITMAPFILEHEADER {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
};

struct BITMAPINFOHEADER {
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
};

/**
* @brief ��������������
*/
void Computer::main() {
	// ��ѭ��
	while (input.hasMoreInput()) {
		Line current_line = input.getCurrentLine();
		int32_t temp{ 0 };
		try {
			switch (current_line.type)
			{
			case Type::LOAD:
				m_memory.load(m_register[current_line.op1], m_register[current_line.op2]);
				m_register.setStatus(current_line.op1, Status::WRITE);
				m_register.setStatus(current_line.op2, Status::READ);
				input.nextLine();
				break;
			case Type::STORE:
				m_memory.store(m_register[current_line.op1], m_register[current_line.op2]);
				m_register.setStatus(current_line.op1, Status::READ);
				m_register.setStatus(current_line.op2, Status::READ);
				input.nextLine();
				break;
			case Type::PUSH:
				m_stack.push(m_register[current_line.op1]);
				m_register.setStatus(current_line.op1, Status::READ);
				input.nextLine();
				break;
			case Type::POP:
				m_stack.pop(m_register[current_line.op1]);
				m_register.setStatus(current_line.op1, Status::WRITE);
				input.nextLine();
				break;
			case Type::MOV:
				m_register.mov(current_line.op1, current_line.op2);
				input.nextLine();
				break;
			case Type::ADD:
				m_register.add(current_line.op1, current_line.op2, current_line.op3);
				input.nextLine();
				break;
			case Type::SUB:
				m_register.sub(current_line.op1, current_line.op2, current_line.op3);
				input.nextLine();
				break;
			case Type::MUL:
				m_register.mul(current_line.op1, current_line.op2, current_line.op3);
				input.nextLine();
				break;
			case Type::DIV:
				m_register.div(current_line.op1, current_line.op2, current_line.op3);
				input.nextLine();
				break;
			case Type::REM:
				m_register.rem(current_line.op1, current_line.op2, current_line.op3);
				input.nextLine();
				break;
			case Type::AND:
				m_register.AND(current_line.op1, current_line.op2, current_line.op3);
				input.nextLine();
				break;
			case Type::OR:
				m_register.OR(current_line.op1, current_line.op2, current_line.op3);
				input.nextLine();
				break;
			case Type::LINE_LABLE:
				input.nextLine();
				break;
			case Type::JAL:
				input.jumpLine(current_line.op1);
				break;
			case Type::BEQ:
				if (m_register.beq(current_line.op1, current_line.op2)) {
					input.jumpLine(current_line.op3);
				}
				else {
					input.nextLine();
				}
				break;
			case Type::BNE:
				if (m_register.bne(current_line.op1, current_line.op2)) {
					input.jumpLine(current_line.op3);
				}
				else {
					input.nextLine();
				}
				break;
			case Type::BLT:
				if (m_register.blt(current_line.op1, current_line.op2)) {
					input.jumpLine(current_line.op3);
				}
				else {
					input.nextLine();
				}
				break;
			case Type::BGE:
				if (m_register.bge(current_line.op1, current_line.op2)) {
					input.jumpLine(current_line.op3);
				}
				else {
					input.nextLine();
				}
				break;
			case Type::CALL:
				temp = input.getCurrentIndex() + 1;
				m_stack.push(&temp);
				input.jumpLine(current_line.op1);
				break;
			case Type::RET:
				m_stack.pop(&temp);
				input.jumpLine(temp);
				break;
			case Type::DRAW:
				draw();
				input.nextLine();
				break;
			case Type::END:
				write();
				return;
			default:
				throw std::string("δ֪�����࣡");
				break;
			}
		}
		catch (const std::string& s) {
			std::cerr << "Line " << input.getCurrentIndex() + 1 << ": ";
			std::cerr << s << std::endl;
			exit(-1);
		}
	}
}


/**
* @brief ��ͼ
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
	BYTE* bits = new BYTE[size];

	// Clear
	memset(bits, 0xFF, size);

	// ���������߿���
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

	//�м������߿���
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

	//�Ĵ�����������
	for (y = 0; y < height - 100; y += 1)
	{
		for (x = 0; x <= width - 240 - 200; x += 75) {
			index = (int)y * width * 3 + (int)x * 3;

			bits[index + 0] = 0; // Blue
			bits[index + 1] = 0;   // Green
			bits[index + 2] = 0;   // Red
		}
	}

	//ջ�ռ䲿������
	for (y = 0; y < height - 100; y += 1)
	{
		for (x = 600; x <= width - 240; x += 50) {
			index = (int)y * width * 3 + (int)x * 3;

			bits[index + 0] = 0; // Blue
			bits[index + 1] = 0;   // Green
			bits[index + 2] = 0;   // Red
		}
	}

	//���Ҷ�����
	for (y = 0; y < height - 100; y += 1)
	{
		x = width - 1;
		index = (int)y * width * 3 + (int)x * 3;

		bits[index + 0] = 0; // Blue
		bits[index + 1] = 0;   // Green
		bits[index + 2] = 0;   // Red
	}

	//�Ĵ�������
	for (int i = 0; i < 32; i++) {
		int x_start, y_start;
		x_start = 75 * (i % 8) + 1;
		y_start = 200 - 50 * (i / 8) - 1;
		int x_end, y_end;
		x_end = x_start + 73;
		y_end = y_start - 48;
		switch (m_register.getStatus(i)) {
		case Status::NO_OPERATE:
			break;
		case Status::WRITE:
			for (x = x_start; x <= x_end; x++) {
				for (y = y_start; y >= y_end; y--) {
					index = y * width * 3 + x * 3;
					bits[index + 0] = 0;	//blue
					bits[index + 1] = 0;	//green
					bits[index + 2] = 255;	//red
				}
			}
			break;
		case Status::READ:
			for (x = x_start; x <= x_end; x++) {
				for (y = y_start; y >= y_end; y--) {
					index = y * width * 3 + x * 3;
					bits[index + 0] = 255;	//blue
					bits[index + 1] = 0;	//green
					bits[index + 2] = 0;	//red
				}
			}
			break;
		case Status::READ_WRITE:
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
	//�Ĵ����������

	//�ڴ�ռ����
	for (int i = 0; i < 16; i++) {
		int x_start, y_start;
		x_start = 600 + (i % 4) * 50 + 1;
		y_start = 200 - 50 * (i / 4) - 1;
		int x_end, y_end;
		x_end = x_start + 48;
		y_end = y_start - 48;
		switch (m_memory.getStatus(i)) {
		case Status::NO_OPERATE:
			break;
		case Status::VISITED:
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
	//�ڴ�������

	//ջ�ռ����
	{
		int x_start, y_start;
		x_start = 800 + 1;
		y_start = 200 - 1;
		int x_end, y_end;
		x_end = width - 2;
		y_end = 1;
		if (m_stack.getStatus() == Status::STACK_OPERATE) {
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
	//ջ�ռ�������

	// Write to file
	std::ostringstream filename;
	filename << draw_times;
	filename << ".bmp";

	std::ofstream file(filename.str(), std::ios::binary);
	if (!file.is_open()) {
		throw std::string("����bmpͼ���ļ���������");
	}
	else
	{
		file.write((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
		file.write((char*)&bitmapHeader, sizeof(BITMAPINFOHEADER));
		file.write((char*)bits, size);
		file.close();
	}

	//����״̬
	m_memory.reset();
	m_stack.reset();
	m_register.reset();

	// �ͷſռ�
	delete[] bits;
}

/**
* @brief �ѼĴ������ڴ��е�ֵд���ļ�result.txt��
*/
void Computer::write() {
	std::ofstream file("result.txt");
	if (!file.is_open()) {
		throw std::string("����ı��ļ���������");
	}
	file << m_register << std::endl;
	file << m_memory;
	file.close();
}