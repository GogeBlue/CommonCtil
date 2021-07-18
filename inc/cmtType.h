/**
* @file cmtType.h
* @brief cmtType ����������ͱ�׼�����ļ�������ļ��涨�˴�������������͵ı���
* @par Windows �����⣺
* @par Linux �����⣺
* @data 2021-07-16
* @author GogeBlue
* @author Dexnab
*/

#pragma once
#ifndef _INC_CMTTYPE
#define _INC_CMTTYPE
#include "CommonCtil.h"

//����CommonCtil��������

//��׼����
typedef unsigned char         cmtU8;
typedef unsigned short        cmtU16;
typedef unsigned int          cmtU32;
typedef char                  cmtS8;
typedef short                 cmtS16;
typedef int                   cmtS32;

//ָ��
typedef unsigned char*		  cmtU8ptr;
typedef unsigned short*       cmtU16ptr;
typedef unsigned int*         cmtU32ptr;
typedef char*                 cmtS8ptr;
typedef short*                cmtS16ptr;
typedef int*                  cmtS32ptr;

//����
typedef float				  cmt32f;
typedef double		          cmt64f;

//64λ
typedef unsigned long long    cmtU64;
typedef long long             cmtS64;

//64λָ��
typedef long long*            cmtS64ptr;
typedef unsigned long long*   cmtU64ptr;
#endif