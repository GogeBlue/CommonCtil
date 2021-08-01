/**
* @file cmtQueue.c
* @data 2021-07-16
* @author GogeBlue
* @author Dexnab
*/

#include <cmtQueue.h>

cmtQueue* cmtQueueInit(cmtUint64 size)
{
	cmtQueue* queue;

	//�ṹ��
	queue = malloc(sizeof(cmtQueue));
	if (!queue) return 0;

	//���ݿռ�
	queue->base = malloc(size);
	if (!queue->base)
	{
		free(queue);
		return 0;
	}

	//��ʼ��ֵ
	queue->size = size;
	queue->bgn = 0;
	queue->end = 0;

	return queue;
}