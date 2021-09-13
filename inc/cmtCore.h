/**
* @file cmtCore.h
* @brief ����֧�ֿ�ƽ̨�ĺ��Ŀ�\n
* ���ṩ�������ܣ���������������ܣ������е���ϵͳapi
* @par Windows �����⣺Kernel32.lib 
* @par Linux �����⣺libpthread.a
* @data 2021-08-11
* @author Dexnab
*/
#include <cmtType.h>
#if defined(CMT_ENV_WINDOWS)
#include <Windows.h>
#elif defined(CMT_ENV_LINUX)
#include <pthread.h>
#endif

#pragma once
#ifndef _INC_CMTCORE
#define _INC_CMTCORE

/**
* @struct cmtThreadInfo
* @brief �̶߳�����Ϣ
* @date 2021-08-12
* @author Dexnab
*/
typedef struct _CMTTHREADINFO
{
	cmtBool CreateSuspend;//<����������߳�
	cmtUint64 StackSize;//<��ʼջ��С
	cmtUint32 priority;//<���ȼ�
	cmtBool inherit;//<�Ƿ�̳о��
}cmtThreadInfo;

/**
* @struct cmtProcessInfo
* @brief ���̶�����Ϣ
* @date 2021-08-11
* @author Dexnab
*/
typedef struct _CMTPROCESSINFO
{
	cmtUint32 priority;//<���ȼ�
	cmtBool hide;//<�Ƿ����ش��ڲ��������
	cmtBool inherit;//<�Ƿ�̳о��
}cmtProcessInfo;

/**
* @struct cmtLock
* @brief �Զ����ṹ��
* @date 2021-09-13
* @author Dexnab
*/
typedef struct _CMTLOCK
{
	cmtUint64 MaxSpin;//<���������
	cmtBool state;//<״̬��0������ģʽ��1���ź���ģʽ��
	cmtUint8 value;//<����ģʽ��������
	cmtUint64 handle;//<�ź���ģʽ�¾��
}cmtLock;

//���̲���
extern cmtUint64 cmtCreateProcess(cmtWchar* cmd, cmtProcessInfo* info);
extern cmtUint8 cmtTerminateProcess(cmtWchar* cmd);

//�̲߳���
/**
* @brief �����߳�
* @param[in] proc �̺߳���\n
* ����������ҪΪ��cmtUint32 __stdcall ThreadProc(void* param);
* @param[in] param �������
* @param[in] info �̶߳�����Ϣ��ȱʡNULL
* @return �߳̾��
* @retval 0 ʧ��
* @retval ���� �߳̾��
* @date 2021-08-12
* @author Dexnab
*/
extern cmtUint64 cmtCreateThread(cmtUint32(__stdcall* proc)(void*), void* param, cmtThreadInfo* info);
/**
* @brief ǿ����ֹ�߳�
* @param[in] handle �߳̾��
* @return ������
* @exception 0 �ɹ�
* @exception 0xff ʧ��
* @date 2021-08-12
* @author Dexnab
*/
extern cmtUint8 cmtTerminateThread(cmtUint64 handle);
/**
* @brief �����߳�
* @param[in] handle �߳̾��
* @return ������
* @exception 0 �ɹ�
* @exception 0xff ʧ��
* @date 2021-08-12
* @author Dexnab
*/
extern cmtUint8 cmtSuspendThread(cmtUint64 handle);
/**
* @brief �����߳�
* @param[in] handle �߳̾��
* @return ������
* @exception 0 �ɹ�
* @exception 0xff ʧ��
* @date 2021-08-12
* @author Dexnab
*/
extern cmtUint8 cmtResumeThread(cmtUint64 handle);
/**
* @brief �ȴ��߳̽���
* @param[in] handle �߳̾��
* @param[in] time ��ȴ�ʱ�䣬-1Ϊ���޳�
* @return �̷߳���ֵ
* @date 2021-08-12
* @author Dexnab
*/
extern cmtUint32 cmtWaitForThread(cmtUint64 handle, cmtUint64 time);

//�������
extern cmtUint8 cmtDupHandle(cmtUint64 dst, cmtUint64 src);
/**
* @brief �رվ��
* @param[in] handle ���
* @date 2021-08-12
* @author Dexnab
*/
extern void cmtCloseHandle(cmtUint64 handle);

//ԭ�Ӳ�����δʵ�֣�
//INC
extern void cmtAtomInc8(cmtUint8* num);
extern void cmtAtomInc16(cmtUint16* num);
extern void cmtAtomInc32(cmtUint32* num);
extern void cmtAtomInc64(cmtUint64* num);
//DEC
extern void cmtAtomDec8(cmtUint8* num);
extern void cmtAtomDec16(cmtUint16* num);
extern void cmtAtomDec32(cmtUint32* num);
extern void cmtAtomDec64(cmtUint64* num);

//��
/**
* @brief ����������
* @param[in] value ��������ַ
* @param[in] MaxSpin �����������-1Ϊ���ޣ�
* @return ����ԭ��
* @retval 0 �����ͷ�
* @retval 1 ��������������
* @attention valueΪ0ʱ��������������������Ե�һ�ε���ǰ�뽫value����
* @par ʾ��:
* @code
* cmtUint8 lock = 0;
* cmtSpinLockEnter(&lock, -1);
* //xxxxxx
* cmtSpinLockLeave(lock);
* @endcode
* @date 2021-09-13
* @author Dexnab
*/
extern BOOL CMT_FASTCALL cmtSpinLockEnter(cmtUint8* value, cmtUint64 MaxSpin);
/**
* @brief �뿪������
* @param[in] value ������
* @date 2021-09-13
* @author Dexnab
*/
#define cmtSpinLockLeave(value) value = 0
/**
* @brief ��ʼ������
* @return �����
* @retval 0 ʧ��
* @retval ���� �����
* @date 2021-08-20
* @author Dexnab
*/
extern cmtUint64 cmtSysLockInit();
/**
* @brief ��������
* @param[in] �����
* @date 2021-08-20
* @author Dexnab
*/
extern void cmtSysLockEnter(cmtUint64 handle);
/**
* @brief �뿪����
* @param[in] �����
* @date 2021-08-20
* @author Dexnab
*/
extern void cmtSysLockLeave(cmtUint64 handle);
/**
* @brief �ͷ�����
* @param[in] �����
* @date 2021-08-20
* @author Dexnab
*/
extern void cmtSysLockFree(cmtUint64 handle);
/**
* @brief ��ʼ���Զ���
* @param[in] lock �Զ����ṹ��
* @param[in] MaxSpin ������ǰ�����������-1Ϊ��������ʼ��Ϊ��������
* @date 2021-09-13
* @author Dexnab
*/
extern void cmtLockInit(cmtLock* lock, cmtUint64 MaxSpin);
/**
* @brief �����Զ���
* @param[in] lock �Զ����ṹ��
* @date 2021-08-20
* @author Dexnab
*/
extern void cmtLockEnter(cmtLock* lock);
/**
* @brief �뿪�Զ���
* @param[in] lock �Զ����ṹ��
* @date 2021-08-20
* @author Dexnab
*/
extern void cmtLockLeave(cmtLock* lock);
/**
* @brief �ͷ��Զ���
* @param[in] lock �Զ����ṹ��
* @date 2021-08-20
* @author Dexnab
*/
extern void cmtLockFree(cmtLock* lock);
#endif