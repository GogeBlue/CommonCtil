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
#define CMT_FLOAT_TOL 0.00001
#define CMT_PI 3.141592653589793
#define TRUE 1
#define FALSE 0

//��׼�����
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#endif