/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   11:44
	filename: 	C:\GoodFrame\common\MsgBlock.h
	file path:	C:\GoodFrame\common
	file base:	MsgBlock
	file ext:	h
	author:		hgj
	
	purpose:	消息池中的消息块
*********************************************************************/

#ifndef MEM_BLOCK_H
#define MEM_BLOCK_H

// 屏蔽一些警告
#pragma warning(disable:4995)
#pragma warning(disable:4996)
#pragma warning(disable:4251)

// 解决 <windows.h>中包含了<winsock.h>头文件从而与 #include "Winsock2.h" 相冲突的问题
// 一定要放在 #include <windows.h> 之前
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class __declspec(dllexport) CMemBlock
{
public:
	enum {	MSG_BLOCK_SIZE = 2048, // 默认的数据块长度
		 };

	enum{	TEXT_MARK_LEN = 64,	// 文字标识的长度，目的是在查询未释放的内存是知道是程序的哪一句申请的
		};
	enum{
		STATE_IN_POOL = 0,	// 在池内
		STATE_OUT_POOL		// 在池外
	};
public:
	
	/* ----------------------------------------------------------
	传入参数：
		iDataSize		分配给 pData 的空间，即数据块的 BUFSIZ
		pszTextMark		文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的
		                这个参数对效率影响非常大，如下：
						    若为 NULL ：release、多线程、ThreadGuardEx 下每毫秒 7500 次
							若为字串  ：release、多线程、ThreadGuardEx 下每毫秒 1118 次。
						建议：在内核代码里，因为写代码者比较有把握，用 NULL ；
						      在应用层里，因为人比较杂，为安全起见，用函数名作为字串；
							  或者先用字串，待程序经过时间验证很稳定后，再改成 NULL
	-----------------------------------------------------------*/
	CMemBlock(int iDataSize, char* pszTextMark=NULL, int iTextLen=0);

	CMemBlock(void);
	~CMemBlock(void);

	// 分配给消息块的整个空间长度
	int size()	{	return m_iDataSize;	}

	// 有效内容的长度，即 wr_ptr() 与 rd_ptr() 的差距值 
	int length() {	return (m_iWdPtr - m_iRdPtr);  }

	// 还没有写内容的空间，即 wr_ptr 及其之后的空间长度
	int space()	{	return (m_iDataSize - m_iWdPtr);	}	

	// 指向消息块的头
	BYTE* base(){	return m_pData;	}	

	/* --------------------------------------------------------------------------
	函数说明：移动读指针
	传入参数：
		iMove	移动的距离
	传出参数：
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	超出写指针的长度了
			20	iMove 的负值过大
	--------------------------------------------------------------------------*/
	int rd_ptr(int iMove);

	// 获得读指针
	BYTE* rd_ptr();

	// wd_ptr 移到了起点，但 m_pData 中的数据内容并没清零（可节约CPU的清零时间）
	// 比 clear 函数快了将近一倍，说明 memset 是很耗时的
	void reset ()
	{	
		m_iRdPtr = 0;
		m_iWdPtr = 0; 
		m_pData[m_iDataSize-1] = 0; // 保险起见，仅仅最后一个元素清0	
	}

	// wd_ptr 移到了起点，且 m_pData 中的数据内容清零
	// 比 reset 函数慢了将近一倍，说明 memset 是很耗时的
	void clear()
	{	
		memset(m_pData, 0, m_iDataSize); 
		m_iRdPtr = 0; 
		m_iWdPtr = 0;	
	}

	// 向消息块中考入内容
	int copy(CMemBlock* pMemBlock);

	/* ----------------------------------------------------------
	函数说明：向消息块中考入内容
	传入参数：
		pData		要考入的内容
		iDataLen	要考入内容的长度
	返回值：
		成功则返回 0，否则返回错误码如下：
			1  要考入的内容为空
			2  要考入内容的长度为0
			3  要考入内容的长度超长
	-----------------------------------------------------------*/
	int copy(const BYTE* pData, int iDataLen);

	/* ----------------------------------------------------------
	函数说明：移动写指针
	传入参数：
		iLen	移动的长度
	返回值：
		成功则返回 0，否则返回错误码如下：
			3  移动的长度超长
	-----------------------------------------------------------*/
	int write(int iLen);


	// 将残余的内容移到头
	int remains_move_to_head();

	// 获得文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的
	void get_text_mark(char* pszTextMark, int iMaxLen);

	// 设置文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的
	void set_text_mark(char* pszTextMark, int iTextLen);

	// 清空文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的
	void clear_text_mark();

private:

	BOOL create();

	// 释放所有的资源
	BOOL release();

	// 判断是有效的指针
	BOOL is_valid_point(const VOID* pPointer);

public:
	BOOL		m_bInPool;		// TRUE 表示在池内，FALSE 表示在池外
	long long	timeOutPool;	// 出池时间，若为零值表示在池内

private:

	int	m_iDataSize;	// 分配给 pData 的空间，即数据块的 BUFSIZ
	int m_iRdPtr;		// 读串的起点
	int m_iWdPtr;		// 写串的起点

	BYTE* m_pData;	

	char	m_szTextMark[TEXT_MARK_LEN];	// 文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的。通常是调用的函数名。
	int		m_sizeTextMark;					// 文字标识的长度
};

#endif