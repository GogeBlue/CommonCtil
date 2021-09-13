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
#include <stdlib.h>//malloc
#include <string.h>//memset

/**
* @struct cmtQueue
* @brief ���нṹ��
* @date 2021-07-30
* @author GogeBlue
* @author Dexnab
*/
typedef struct _CMTQUEUE
{
	cmtUint8* base;//<��ַ
	cmtUint64 size;//<��������С
	cmtUint64 bgn;//<���ݻ����ֽ�ƫ��
	cmtUint64 end;//<���ݻ���ֹ�ֽ�ƫ�ƣ����������һ���ֽڣ�
	cmtBool empty;//<�Ƿ�Ϊ�գ�TRUE���գ�
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
<<<<<<< HEAD
extern void cmtQueueClean(cmtQueue* queue);
extern cmtUint8 cmtQueueAppend(cmtQueue* queue, cmtUint8* data, cmtUint64 size);
extern cmtUint8 cmtQueueGet(cmtQueue* queue, cmtUint8* buffer, cmtUint64 size);
extern void cmtQueueRemove(cmtQueue* q);
extern void* cmtQueueSearch(cmtQueue* q, cmtUint64 index);
extern void cmtFreeIndex(cmtQueue* q, cmtUint64 index);
extern int cmtScanAll(cmtQueue* q, cmtUint64 cmtScanHandler, void* udata);
=======
/**
* @brief ��ն���
* @param[in] queue ����ָ��
* @attention �˺���ֻ��ն��У����ͷ�
* @date 2021-07-30
* @author GogeBlue
* @author Dexnab
*/
#define cmtQueueClean(queue) {queue->bgn = queue->end = 0;}
/**
* @brief �ͷŶ���
* @param[in] queue ����ָ��
* @attention queue�ᱻ����
* @date 2021-07-30
* @author GogeBlue
* @author Dexnab
*/
#define cmtQueueFree(queue) {free(queue->base);free(queue);}
/**
* @brief ���в���
* @param[in] queue ����ָ��
* @param[in] data ����
* @param[in] size ���ݴ�С
* @return ������
* @retval 0x00 ����
* @retval 0xff ���ݹ���
* @date 2021-07-30
* @author GogeBlue
* @author Dexnab
*/
extern cmtUint8 cmtQueueIn(cmtQueue* queue, cmtUint8* data, cmtUint64 size);
/**
* @brief ���в���
* @param[in] queue ����ָ��
* @param[in] data ����
* @param[in] size ���ݴ�С
* @return ������
* @retval 0x00 ����
* @retval 0xff ���ݹ���
* @date 2021-07-30
* @author GogeBlue
* @author Dexnab
*/
extern cmtUint8 cmtQueueOut(cmtQueue* queue, cmtUint8* buffer, cmtUint64 size);
//extern void cmtQueueRemove(cmtQueue* q);
//extern void* cmtQueueSearch(cmtQueue* q, cmtU64 index);
//extern void cmtFreeIndex(cmtQueue* q, cmtU64 index);
//extern int cmtScanAll(cmtQueue* q, cmtScan cmtScanHandler, void* udata);
>>>>>>> ftu_queue
#endif