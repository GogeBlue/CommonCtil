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
#ifdef CMT_ENV_WINDOWS
#include <Windows.h>
#else
#include <pthread.h>
#endif

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
}cmtProcessInfo;

//���̲���
extern cmtUint64 cmtCreateProcess(cmtWchar* cmd, cmtProcessInfo* info);

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
extern cmtUint64 cmtCreateThread(cmtUint32(*proc)(void*), void* param, cmtThreadInfo* info);
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

//ԭ�Ӳ���
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
* @brief ���Խ���������
* @param[in] lock ��
* @attention lockΪ0ʱ��������������������Ե�һ�ε���ǰ�뽫lock����
* @date 2021-08-12
* @author Dexnab
*/
extern void __fastcall cmtSpinLockEnter(cmtUint8* lock);
/**
* @brief �˳�������
* @param[in] lock ��
* @date 2021-08-12
* @author Dexnab
*/
extern void __fastcall cmtSpinLockLeave(cmtUint8* lock);