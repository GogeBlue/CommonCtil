/**
* @file cmtQueue.c
* @date 2021-07-16
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
	queue->empty = TRUE;

	return queue;
}

cmtUint8 cmtQueueIn(cmtQueue* queue, cmtUint8* data, cmtUint64 size)
{
	cmtUint64 rData;

	//����
	if (queue->end > queue->bgn || queue->empty)
	{
		//ʣ��ռ�
		if (queue->end - queue->bgn + size > queue->size) return 0xff;

		//����Ҫ��ת
		if (size <= queue->size - queue->end)
			for (rData = 0; rData < size; rData++, queue->end++)
				queue->base[queue->end] = data[rData];
		//��Ҫ��ת
		else
		{
			for (rData = 0; queue->end <= queue->size; rData++, queue->end++)
				queue->base[queue->end] = data[rData];
			for (queue->end = 0; rData < size; rData++, queue->end++)
				queue->base[queue->end] = data[rData];
		}
	}
	//����
	else
	{
		//ʣ��ռ�
		if (size > queue->bgn - queue->end) return 0xff;

		//���Բ����ܷ�ת
		for (rData = 0; rData < size; rData++, queue->end++)
			queue->base[queue->end] = data[rData];
	}

	queue->empty = FALSE;
	return 0x00;
}