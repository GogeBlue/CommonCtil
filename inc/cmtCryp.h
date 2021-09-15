/**
* @file cmtCryp.h
* @brief ����֧�ֿ�ƽ̨�ļ����ð汾����ѧ��
* @data 2021-09-13
* @author GogeBlue
*/

//��ֹ�ظ�����
#pragma once
#ifndef _INC_CMTCRYP
#define _INC_CMTCRYP
#include <cmtType.h>
#include <cmtCore.h>

/*--------------------------------�궨�� ��ʼ--------------------------------*/

//SHA256���ժҪ���ȣ�32�ֽڣ�256λ��
#define CMT_SHA256_BLOCK_SIZE 32

//SHA1�����ժҪ���ȣ�20�ֽڣ�160λ��
#define CMT_SHA1_BLOCK_SIZE 20

#define CMT_ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define CMT_ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CMT_CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define CMT_MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define CMT_EP0(x) (CMT_ROTRIGHT(x,2) ^ CMT_ROTRIGHT(x,13) ^ CMT_ROTRIGHT(x,22))
#define CMT_EP1(x) (CMT_ROTRIGHT(x,6) ^ CMT_ROTRIGHT(x,11) ^ CMT_ROTRIGHT(x,25))
#define CMT_SIG0(x) (CMT_ROTRIGHT(x,7) ^ CMT_ROTRIGHT(x,18) ^ ((x) >> 3))
#define CMT_SIG1(x) (CMT_ROTRIGHT(x,17) ^ CMT_ROTRIGHT(x,19) ^ ((x) >> 10))
/*--------------------------------�궨�� ����--------------------------------*/


/*--------------------------------���������� ��ʼ--------------------------------*/

static const cmtUint32 k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};
/*--------------------------------���������� ����--------------------------------*/

/*--------------------------------�ṹ�嶨�� ��ʼ--------------------------------*/

/**
* @struct cmtSHA256
* @brief SHA256�ṹ��
* @date 2021-09-14
* @author GogeBlue
*/
typedef struct _CMTSHA256
{
	cmtUint8 data[64];
	cmtUint32 datalen;
	cmtUint64 bitlen;
	cmtUint32 state[8];
}cmtSHA256;

/**
* @struct cmtSHA1
* @brief SHA1�ṹ��
* @date 2021-09-15
* @author GogeBlue
*/
typedef struct _CMTSHA1
{
	cmtUint8 data[64];
	cmtUint32 datalen;
	cmtUint64 bitlen;
	cmtUint32 state[5];
	cmtUint32 k[4];
}cmtSHA1;
/*--------------------------------�ṹ�嶨�� ����--------------------------------*/

/*--------------------------------��������� ��ʼ--------------------------------*/

/**
* @brief �����������
* @param[out] ���������
* @param[in] ���������ȣ������������������
* @date 2021-09-13
* @author Dexnab
*/
void cmtRealRand(cmtUint64* buf, cmtUint64 len);
/*--------------------------------��������� ����--------------------------------*/

/*--------------------------------���� ��ʼ--------------------------------*/

/**
* @brief ��ʼ��cmtSHA256�ṹ��
* @param[out] ����ṹ��
* @par ʾ��:
* @code
	//���գ��ַ���"abcabcabc" ��sha256ֵΪ��76b99ab4be8521d78b19bcff7d1078aabeb477bd134f404094c92cd39f051c3e
	cmtChar str[] = "abcabcabc";
	cmtUint8 result[CMT_SHA256_BLOCK_SIZE];
	cmtSHA256 ctx;

	//��ʼ��sha256�ṹ��
	cmtSHA256Init(&ctx);

	//д�����ݣ�����sha256�ṹ��
	cmtSHA256Update(&ctx, str, sizeof(str) - 1);//�ų���β��'\0'

	//��ȡ���
	cmtSHA256Get(&ctx, result);

	//���
	for (int i = 0; i < 32; i++)
	{
		printf("%hhx", result[i]);
	}
* @endcode
* @date 2021-09-15
* @author GogeBlue
*/
void cmtSHA256Init(cmtSHA256* ctx);

/**
* @brief д�����ݣ�����sha256�ṹ��
* @param[in] sha256�ṹ��
* @param[in] ����
* @param[in] �����ֽ���
* @date 2021-09-15
* @author GogeBlue
*/
void cmtSHA256Update(cmtSHA256* ctx, cmtUint8* data, cmtUint64 size);

/**
* @brief ���㲢ȡֵ
* @param[in] sha256�ṹ��
* @param[out] ���ܻ�����
* @attention ���ܻ��������Ȳ���С��CMT_SHA256_BLOCK_SIZE, �����һ�ε�update��abc���ڶ��ε�update��123�������get���൱�ڼ���abc123��hash256
* @date 2021-09-15
* @author GogeBlue
*/
void cmtSHA256Get(cmtSHA256* ctx, cmtUint8* hash);

/**
* @brief ���������ڲ�ʹ��
* @date 2021-09-15
* @author GogeBlue
*/
void cmtSHA256Transform(cmtSHA256* ctx, cmtUint8* data);

/**
* @brief ��ʼ��cmtSHA1�ṹ��
* @param[out] ����ṹ��
* @par ʾ��:
* @code
	//���գ��ַ���"abcabcabc" ��sha1ֵΪ��0b6f5dae7f8d68348f7d56ac05ea20a55f652d91
	cmtChar str[] = "abcabcabc";
	cmtUint8 result[CMT_SHA1_BLOCK_SIZE];
	cmtSHA1 ctx;

	//��ʼ��sha256�ṹ��
	cmtSHA1Init(&ctx);

	//д�����ݣ�����sha256�ṹ��
	cmtSHA1Update(&ctx, str, sizeof(str) - 1);//�ų���β��'\0'

	//��ȡ���
	cmtSHA1Get(&ctx, result);

	//���
	for (int i = 0; i < 20; i++)
	{
		printf("%hhx", result[i]);
	}
* @endcode
* @date 2021-09-15
* @author GogeBlue
*/
void cmtSHA1Init(cmtSHA1* ctx);

/**
* @brief д�����ݣ�����sha1�ṹ��
* @param[in] sha1�ṹ��
* @param[in] ����
* @param[in] �����ֽ���
* @date 2021-09-15
* @author GogeBlue
*/
void cmtSHA1Update(cmtSHA1* ctx, cmtUint8* data, cmtUint64 size);

/**
* @brief ���㲢ȡֵ
* @param[in] sha1�ṹ��
* @param[out] ���ܻ�����
* @attention ���ܻ��������Ȳ���С��CMT_SHA1_BLOCK_SIZE, �����һ�ε�update��abc���ڶ��ε�update��123�������get���൱�ڼ���abc123��hash1
* @date 2021-09-15
* @author GogeBlue
*/
void cmtSHA1Get(cmtSHA1* ctx, cmtUint8* hash);

/**
* @brief ���������ڲ�ʹ��
* @date 2021-09-15
* @author GogeBlue
*/
void cmtSHA1Transform(cmtSHA1* ctx, cmtUint8* data);
/*--------------------------------���� ����--------------------------------*/


#endif