/**
* @file cmtQueue.h
* @brief cmtQueue ���ͷ�ļ���ʵ����Queue���еĲ���
* @par Windows �����⣺
* @par Linux �����⣺
* @data 2021-07-16
* @author GogeBlue
* @author Dexnab
*/

#pragma once
#ifndef _INC_CMTQUEUE
#define _INC_CMTQUEUE
#include <cmtType.h>
#include <stdlib.h>

typedef struct _CMTQUEUE
{
	cmtUint8* base;
	cmtUint64 size;
	cmtUint64 bgn;
	cmtUint64 end;
}cmtQueue;

/**
* @brief ��ʼ��һ������
* @param[in] size ��������С
* @return ����ָ��
* @retval 0 ʧ��
* @retval ���� ����ָ��
* @attention ��Ҫʹ��cmtQueueFree���ͷ�
* @date 2021-07-30
* @author GogeBlue
* @author Dexnab
*/
extern cmtQueue* cmtQueueInit(cmtUint64 size);
extern void cmtQueueClean(cmtQueue* queue);
extern cmtUint8 cmtQueueAppend(cmtQueue* queue, cmtUint8* data, cmtUint64 size);
extern cmtUint8 cmtQueueGet(cmtQueue* queue, cmtUint8* buffer, cmtUint64 size);
extern void cmtQueueRemove(cmtQueue* q);
extern void* cmtQueueSearch(cmtQueue* q, cmtUint64 index);
extern void cmtFreeIndex(cmtQueue* q, cmtUint64 index);
extern int cmtScanAll(cmtQueue* q, cmtUint64 cmtScanHandler, void* udata);
#endif