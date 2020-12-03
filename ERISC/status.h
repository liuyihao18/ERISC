#pragma once
#ifndef __STATUS_H__
#define __STATUS_H__

enum class Status
{
	NO_OPERATE = 0, // 没有操作，白色
	WRITE, // 写入，红
	READ, // 读取，蓝
	READ_WRITE, // 又读又写，紫
	VISITED, // 内存访问，绿
	STACK_OPERATE // 栈读写，橙
};

#endif // !__STATUS_H__
