/**
* @file cmtAES.h
* @brief ����֧�ֿ�ƽ̨�ļ����ð汾AES���ܺ�����\n
* @data 2021-09-13
* @author GogeBlue
*/

#include <cmtType.h>
#include "cmtCore.h"
#if defined(CMT_ENV_WINDOWS)
#include <Windows.h>
#elif defined(CMT_ENV_LINUX)
#include <pthread.h>
#endif

#pragma once
#ifndef _INC_CMTAES
#define _INC_CMTAES

#endif