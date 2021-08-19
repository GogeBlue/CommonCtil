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

typedef struct _CMTLOCK
{
	cmtUint64 MaxSpin;
	cmtBool semaphore;
	cmtUint64 handle;
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
* @brief ��ȡ������
* @param[in] value ������
* @param[in] MaxSpin �����ѡ����-1Ϊ���ޣ�
* @attention valueΪ0ʱ��������������������Ե�һ�ε���ǰ�뽫value����
* @par ʾ��:
* @code
* cmtUint8 lock = 0;
* cmtSpinLockEnter(&lock);
* //xxxxxx
* cmtSpinLockLeave(&lock);
* @endcode
* @date 2021-08-12
* @author Dexnab
*/
extern void cmtSpinLockEnter(cmtUint8* value, cmtUint64 MaxSpin);
/**
* @brief �ͷ�������
* @param[in] value ������
* @par ʾ��:
* @code
* cmtUint8 lock = 0;
* cmtSpinLockEnter(&lock);
* //xxxxxx
* cmtSpinLockLeave(&lock);
* @endcode
* @date 2021-08-12
* @author Dexnab
*/
#define cmtSpinLockLeave(value) *value = 0
extern cmtUint64 cmtSysLockInit();
extern void cmtSysLockEnter(cmtUint64 handle);
extern void cmtSysLockLeave(cmtUint64 handle);
extern void cmtSysLockFree(cmtUint64 handle);
extern void cmtLockInit(cmtLock* lock, cmtUint64 MaxSpin);
extern void cmtLockEnter(cmtLock* lock);
extern void cmtLockLeave(cmtLock* lock);
extern void cmtLockFree(cmtLock* lock);