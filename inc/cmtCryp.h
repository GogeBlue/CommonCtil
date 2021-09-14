/**
* @file cmtCryp.h
* @brief ����֧�ֿ�ƽ̨�ļ����ð汾AES���ܺ����� (to GogeBlue: �����ø�һ��,���ڿ����ĳ�cmtCryp��,�������ǰ�������������ѧ������(sha,md,aes,rsa��))
* @data 2021-09-13
* @author GogeBlue
*/

//��ֹ�ظ�����
#pragma once
#ifndef _INC_CMTCRYP
#define _INC_CMTCRYP
#include <cmtType.h>
#include <cmtCore.h>

/*******************************SHA 256 �궨�忪ʼ*********************************/
#define SHA256_BLOCK_SIZE 32 //SHA256�������һ������Ϊ32λ��ժҪ��256Bits��

#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
/*******************************SHA 256 �궨�����*********************************/

/*******************************SHA 256 �������忪ʼ*********************************/
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
/*******************************SHA 256 �����������*********************************/

/*******************************SHA 256 ���� �ṹ�嶨�忪ʼ*********************************/
/**
* @struct cmtSHA256
* @brief SHA256�ṹ��
* @date 2021-09-14
* @author GogeBlue
*/
typedef struct cmtSHA256_ {
	cmtUint8 data[64];
	cmtUint32 datalen;
	cmtUint64 bitlen;
	cmtUint32 state[8];
} cmtSHA256;
/*******************************SHA 256 ���� �ṹ�嶨�����*********************************/

/**
* @brief �������������,����buf����һ��64λ�޷�����������ָ�룬len��ƫ�Ƴ��ȡ�����������н�����ָ�����ȵ������ (0~2^64-1)
* @date 2021-09-13
* @author Dexnab
*/
void cmtRealRand(cmtUint64* buf, cmtUint64 len);


/**
*   ʾ�����룺
*   //�ַ���"abcabcabc" ��sha256ֵΪ��76b99ab4be8521d78b19bcff7d1078aabeb477bd134f404094c92cd39f051c3e
	cmtUint8 strTest[] = { "abcabcabc" };

	//���ڽ���sha256�����buffer
	cmtUint8 rlt[SHA256_BLOCK_SIZE] = {NULL};

	//��ȡ�ַ����ĳ���
	size_t len = strlen(strTest);

	//����sha256�ṹ��
	cmtSHA256* test = (cmtSHA256*)malloc(sizeof(cmtSHA256));

	//��ʼ���ṹ��
	cmtSHA256Init(test);

	//��ʼ����sha256
	cmtSHA256Update(test, strTest, len);

	//��ȡsha256���
	cmtSHA256Get(test, rlt);

	//�鿴sha256���
	for (;i<32;i++)
	{
		printf_s("%x", rlt[i]);
	}
**/
/*******************************SHA 256 ����������ʼ*********************************/
/**
* @brief ��ʼ��cmtSHA256�ṹ��
* @date 2021-09-14
* @author GogeBlue
*/
void cmtSHA256Init(cmtSHA256* ctx);

/**
* @brief ��data��Ϊsha256������������� data��ֵ��lenΪdata�ĳ��ȡ�
* @date 2021-09-14
* @author GogeBlue
*/
void cmtSHA256Update(cmtSHA256* ctx, const cmtUint8 data[], size_t len);

/**
* @brief ������õ�hashֵ���浽ָ���������У��������Ŀ��ó��Ȳ���С��32���ֽڣ���SHA256_BLOCK_SIZE��
* @date 2021-09-14
* @author GogeBlue
*/
void cmtSHA256Get(cmtSHA256* ctx, cmtUint8 hash[]);

/**
* @brief ���������ڲ�ʹ��
* @date 2021-09-14
* @author GogeBlue
*/
void cmtSha256Transform_(cmtSHA256* ctx, const cmtUint8 data[]);
/*******************************SHA 256 ������������*********************************/

#endif