#pragma once
#ifndef __STATUS_H__
#define __STATUS_H__

enum class Status
{
	NO_OPERATE = 0, // û�в�������ɫ
	WRITE, // д�룬��
	READ, // ��ȡ����
	READ_WRITE, // �ֶ���д����
	VISITED, // �ڴ���ʣ���
	STACK_OPERATE // ջ��д����
};

#endif // !__STATUS_H__
