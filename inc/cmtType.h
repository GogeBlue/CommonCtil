/**
* @file cmtType.h
* @brief cmtType ����������ͱ�׼�����ļ�������ļ��涨�˴�������������͵ı���
* @par Windows �����⣺
* @par Linux �����⣺
* @date 2021-09-14
* @author GogeBlue
* @author Dexnab
*/

#pragma once
#ifndef _INC_CMTTYPE
#define _INC_CMTTYPE

//����ϵͳ����
#if defined(__linux__)
#define CMT_ENV_LINUX
#elif defined(_WIN32)
#define CMT_ENV_WINDOWS
#elif defined(__APPLE__)
#define CMT_ENV_APPLE
#endif

//����λ��
#if defined(_WIN64)
#define CMT_ENV_x64
#elif defined(__x86_64__)
#define CMT_ENV_x64
#else
#define CMT_ENV_x86
#endif

//c/c++
#if defined(__cplusplus)
#define CMT_ENV_CPP
#endif

//����Լ��
#if defined(CMT_ENV_x64)
#define CMT_CDECL
#define CMT_STDCALL
#define CMT_FASTCALL
#else
#if defined(CMT_ENV_WINDOWS)
#define CMT_CDECL __cdecl
#define CMT_STDCALL __stdcall
#define CMT_FASTCALL __fastcall
#elif defined(CMT_ENV_LINUX)
#define CMT_CDECL __attribute__((cdecl))
#define CMT_STDCALL __attribute__((stdcall))
#define CMT_FASTCALL __attribute__((fastcall))
#endif
#endif

//��������
#define CMT_FLOAT_TOL 0.00001
#define CMT_PI 3.141592653589793
#define TRUE 1
#define FALSE 0

//��������
typedef unsigned char cmtUint8;
typedef unsigned short cmtUint16;
typedef unsigned int cmtUint32;
typedef char cmtInt8;
typedef short cmtInt16;
typedef int cmtInt32;
#if defined(CMT_ENV_x64)
typedef unsigned long long cmtUint64;//ע�⣺32λģʽ�¸�������cmtUint32��ͬ
typedef long long cmtInt64;//ע�⣺32λģʽ�¸�������cmtInt32��ͬ
#else
typedef cmtUint32 cmtUint64;//ע�⣺32λģʽ�¸�������cmtUint32��ͬ
typedef cmtInt32 cmtInt64;//ע�⣺32λģʽ�¸�������cmtInt32��ͬ
#endif
typedef cmtUint8 cmtBool;

//�ַ�����
typedef cmtUint8 cmtChar;
typedef cmtUint16 cmtWchar;
typedef cmtUint32 cmtFchar;

#endif