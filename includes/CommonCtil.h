/**
* @file CommonCtil.h
* @brief ComonCtil ���ͷ�ļ���ͨ���������Ŀ�а�����ͷ�ļ���ʹ��������߿�
* @par Windows �����⣺
* @par Linux �����⣺
* @data 2021-07-15
* @author GogeBlue <mail>
* @author Dexnab
*/

//��ֹ���ذ���
#pragma once
#ifndef _INC_COMMONCTIL
#define _INC_COMMONCTIL

//����ϵͳ����
#ifdef __linux__
#define CMT_ENV_LINUX
#elif _WIN32
#define CMT_ENV_WINDOWS
#elif __APPLE__
#define CMT_ENV_APPLE
#elif __arm__
#define CMT_ENV_ARM
#elif i386
#define CMT_ENV_I386
#endif

//����λ��
#ifdef _WIN64
#define CMT_ENV_x64
#elif __x86_64__
#define CMT_ENV_x64
#else
#define CMT_ENV_x86
#endif

//c/c++
#ifdef __cplusplus
#define CMT_ENV_CPP
#endif

//��������
#define CMT_FLOAT_TOL		 0.00001
#define CMT_PI				 3.141592653589793
#define TRUE 1
#define FALSE 0

//��׼�����
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//����CommonCtil��������
typedef unsigned char         cmtU8;
typedef unsigned short        cmtU16;
typedef unsigned int          cmtU32;
typedef char                  cmtS8;
typedef short                 cmtS16;
typedef int                   cmtS32;

#if defined(CMT_ENV_I386) || defined(CMT_ENV_ARM) || defined(CMT_ENV_WINDOWS)
typedef unsigned long long    cmtU64;
typedef long long             cmtS64;
#else
typedef unsigned long         cmtU64;
typedef long                  cmtS64;
#endif
typedef unsigned char*		  cmtU8ptr;
typedef unsigned short*       cmtU16ptr;
typedef unsigned int*         cmtU32ptr;
typedef char*				  cmtS8ptr;
typedef short*				  cmtS16ptr;
typedef int*                  cmtS32ptr;

#if defined(CMT_ENV_I386) || defined(CMT_ENV_ARM) || defined(CMT_ENV_WINDOWS)
typedef long long*            cmtS64ptr;
typedef unsigned long long*   cmtU64ptr;
#else
typedef long*                 cmtS64ptr;
typedef unsigned long*		  cmtU64ptr;
#endif
#endif