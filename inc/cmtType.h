/**
* @file cmtType.h
* @brief cmtType ����������ͱ�׼�����ļ�������ļ��涨�˴�������������͵ı���
* @par Windows �����⣺
* @par Linux �����⣺
* @data 2021-07-29
* @author GogeBlue
* @author Dexnab
*/

#pragma once
#ifndef _INC_CMTTYPE
#define _INC_CMTTYPE

//����ϵͳ����
#ifdef __linux__
#define CMT_ENV_LINUX
#elif _WIN32
#define CMT_ENV_WINDOWS
#elif __APPLE__
#define CMT_ENV_APPLE
#endif

//����λ��
#ifdef _WIN64
#define CMT_ENV_x64
#elif __x86_64__
#define CMT_ENV_x64
#else
#define CMT_ENV_x32
#endif

//c/c++
#ifdef __cplusplus
#define CMT_ENV_CPP
#endif

//��������
#define CMT_FLOAT_TOL	0.00001
#define CMT_PI			3.141592653589793
#define TRUE			1
#define FALSE			0

//��������
typedef unsigned char		cmtUint8;
typedef unsigned short		cmtUint16;
typedef unsigned int		cmtUint32;
typedef char				cmtInt8;
typedef short				cmtInt16;
typedef int					cmtInt32;
typedef unsigned long long	cmtUint64;
typedef long long			cmtInt64;
typedef cmtUint8			cmtBool;

#endif