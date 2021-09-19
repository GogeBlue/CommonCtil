/**
* @file cmtCryp.h
* @brief ����֧�ֿ�ƽ̨�ļ����ð汾����ѧ��
* @data 2021-09-13
* @author Brad Conte
* @author GogeBlue
* @disclaimer: This code is presented "as is" without any guarantees.
*
* Details:
*
			  Implementation of the SHA-256 hashing algorithm.
			  SHA-256 is one of the three algorithms in the SHA2
			  specification. The others, SHA-384 and SHA-512, are not
			  offered in this implementation.
			  For SHA-384 and SHA-512, they require a x64 environment
			  Algorithm specification can be found here:
			   * http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
			  This implementation uses little endian byte order.

			  Implementation of the SHA1 hashing algorithm.
			  Algorithm specification can be found here:
			   * http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
			  This implementation uses little endian byte order.

			  Implementation of the MD5 hashing algorithm.
			  Algorithm specification can be found here:
			   * http://tools.ietf.org/html/rfc1321
			  This implementation uses little endian byte order.

			  The implementation of the AES algorithm and the CTR, CBC, and
			  CCM modes of operation it can be used in.
			   AES is, specified by the NIST in in publication FIPS PUB 197,
			  availible at:
			   * http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf .
			  The CBC and CTR modes of operation are specified by
			  NIST SP 800-38 A, available at:
			   * http://csrc.nist.gov/publications/nistpubs/800-38a/sp800-38a.pdf .
			  The CCM mode of operation is specified by NIST SP80-38 C, available at:
			   * http://csrc.nist.gov/publications/nistpubs/800-38C/SP800-38C_updated-July20_2007.pdf
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

//MD5�����ժҪ���ȣ�16�ֽڣ�128λ��
#define CMT_MD5_BLOCK_SIZE 16 

#define CMT_ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define CMT_ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define CMT_KE_ROTWORD(x) (((x) << 8) | ((x) >> 24))

#define CMT_CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define CMT_MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define CMT_EP0(x) (CMT_ROTRIGHT(x,2) ^ CMT_ROTRIGHT(x,13) ^ CMT_ROTRIGHT(x,22))
#define CMT_EP1(x) (CMT_ROTRIGHT(x,6) ^ CMT_ROTRIGHT(x,11) ^ CMT_ROTRIGHT(x,25))
#define CMT_SIG0(x) (CMT_ROTRIGHT(x,7) ^ CMT_ROTRIGHT(x,18) ^ ((x) >> 3))
#define CMT_SIG1(x) (CMT_ROTRIGHT(x,17) ^ CMT_ROTRIGHT(x,19) ^ ((x) >> 10))

#define CMT_F(x,y,z) ((x & y) | (~x & z))
#define CMT_G(x,y,z) ((x & z) | (y & ~z))
#define CMT_H(x,y,z) (x ^ y ^ z)
#define CMT_I(x,y,z) (y ^ (x | ~z))

#define CMT_FF(a,b,c,d,m,s,t) { a += CMT_F(b,c,d) + m + t; \
                            a = b + CMT_ROTLEFT(a,s); }
#define CMT_GG(a,b,c,d,m,s,t) { a += CMT_G(b,c,d) + m + t; \
                            a = b + CMT_ROTLEFT(a,s); }
#define CMT_HH(a,b,c,d,m,s,t) { a += CMT_H(b,c,d) + m + t; \
                            a = b + CMT_ROTLEFT(a,s); }
#define CMT_II(a,b,c,d,m,s,t) { a += CMT_I(b,c,d) + m + t; \
                            a = b + CMT_ROTLEFT(a,s); }

//AES����һ�β���16Bytes
#define CMT_AES_BLOCK_SIZE 16

#define CMT_AES_128_ROUNDS 10
#define CMT_AES_192_ROUNDS 12
#define CMT_AES_256_ROUNDS 14

//�������Ĵ�С���㲹�벢���ܺ�����Ĵ�С
#define cmtAEScipherSize(PlainSize) ((PlainSize) % CMT_AES_BLOCK_SIZE ? (PlainSize) + CMT_AES_BLOCK_SIZE - (PlainSize) % CMT_AES_BLOCK_SIZE : (PlainSize))
/*--------------------------------�궨�� ����--------------------------------*/

/*--------------------------------�ṹ�嶨�� ��ʼ--------------------------------*/

/**
* @struct cmtSHA256
* @brief SHA256�ṹ��
* @date 2021-09-14
* @author Brad Conte
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
* @author Brad Conte
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

/**
* @struct cmtMD5
* @brief MD5�ṹ��
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
typedef struct _CMTMD5
{
	cmtUint8 data[64];
	cmtUint32 datalen;
	cmtUint64 bitlen;
	cmtUint32 state[4];
}cmtMD5;
/*--------------------------------�ṹ�嶨�� ����--------------------------------*/

/*--------------------------------��������� ��ʼ--------------------------------*/

/**
* @brief �����������
* @param[out] ���������
* @param[in] ���������ȣ������������������
* @attention 32λģʽ�£�ÿ�������Ϊ32�ֽڣ�64λģʽ�£�ÿ�������Ϊ64�ֽ�
* @date 2021-09-19
* @author Dexnab
*/
void CMT_FASTCALL cmtRealRand(cmtUint64* buf, cmtUint64 len);
/*--------------------------------��������� ����--------------------------------*/

/*--------------------------------ɢ�к��� ��ʼ--------------------------------*/

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
* @author Brad Conte
* @author GogeBlue
*/
void cmtSHA256Init(cmtSHA256* ctx);

/**
* @brief д�����ݣ�����sha256�ṹ��
* @param[in] sha256�ṹ��
* @param[in] ����
* @param[in] �����ֽ���
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
void cmtSHA256Update(cmtSHA256* ctx, cmtUint8* data, cmtUint64 size);

/**
* @brief ���㲢ȡֵ
* @param[in] sha256�ṹ��
* @param[out] ���ܻ�����
* @attention ���ܻ��������Ȳ���С��CMT_SHA256_BLOCK_SIZE, �����һ�ε�update��abc���ڶ��ε�update��123�������get���൱�ڼ���abc123��hash256
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
void cmtSHA256Get(cmtSHA256* ctx, cmtUint8* hash);

/**
* @brief ���������ڲ�ʹ��
* @date 2021-09-15
* @author Brad Conte
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
* @author Brad Conte
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
* @author Brad Conte
* @author GogeBlue
*/
void cmtSHA1Get(cmtSHA1* ctx, cmtUint8* hash);

/**
* @brief ���������ڲ�ʹ��
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
void cmtSHA1Transform(cmtSHA1* ctx, cmtUint8* data);

/**
* @brief ��ʼ��cmtMD5�ṹ��
* @param[out] ����ṹ��
* @par ʾ��:
* @code
	//���գ��ַ���"abcabcabc" ��MD5ֵΪ��97ac82a5b825239e782d0339e2d7b910
	cmtChar str[] = "abcabcabc";
	cmtUint8 result[CMT_MD5_BLOCK_SIZE];
	cmtMD5 ctx;

	//��ʼ��MD5�ṹ��
	cmtMD5Init(&ctx);

	//д�����ݣ�����MD5�ṹ��
	cmtMD5Update(&ctx, str, sizeof(str) - 1);//�ų���β��'\0'

	//��ȡ���
	cmtMD5Get(&ctx, result);

	//���
	for (int i = 0; i < 16; i++)
	{
		printf("%hhx", result[i]);
	}
* @endcode
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
void cmtMD5Init(cmtMD5* ctx);

/**
* @brief д�����ݣ�����MD5�ṹ��
* @param[in] MD5�ṹ��
* @param[in] ����
* @param[in] �����ֽ���
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
void cmtMD5Update(cmtMD5* ctx, cmtUint8* data, cmtUint64 size);

/**
* @brief ���㲢ȡֵ
* @param[in] MD5�ṹ��
* @param[out] ���ܻ�����
* @attention ���ܻ��������Ȳ���С��CMT_MD5_BLOCK_SIZE, �����һ�ε�update��abc���ڶ��ε�update��123�������get���൱�ڼ���abc123��MD5
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
void cmtMD5Get(cmtMD5* ctx, cmtUint8* hash);

/**
* @brief ���������ڲ�ʹ��
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
void cmtMD5Transform(cmtMD5* ctx, cmtUint8* data);
/*--------------------------------ɢ�к��� ����--------------------------------*/


/*--------------------------------�ԳƼ��ܺ��� ��ʼ--------------------------------*/
/*
* ע������
1���������е�AES����������Կ���ú�����������ڼ��ܽ���ǰִ��
2����Կ��λ��ֻ����128λ��cmtUint8 key[16]����192λ��cmtUint8 key[24]��������256λ��cmtUint8 key[32]����
3�����ڿ�����Կλ�������ķ������Ƕ��û����������hash���㣬�磺keyInit(sha256(userInput)) //����һ��256λAES��Կ��
4��Ĭ�ϵ�cmtAESKeyInit�������ص�AES������ʽ��ECBģʽ������ģʽ�����Ƿǳ��İ�ȫ�������е��ظ�������������Ҳ���ظ����Ƽ�ʹ��CBCģʽ
5��ECBģʽ�²���Ҫʹ�ó�ʼ��������IV������ΪECBģʽ�������������뱾����ʽ���ܵģ������أ�����ģʽ��IV�ͱ����Ҫ�����ˣ������Ը��ļ�����һ�����ƫ����������ͬ���ļ����ܵõ���ͬ�����ġ�
*/

/**
* @brief AES��Կ��ʼ��������ʹ���ַ�����
* @param[in] keystr ����������Կ���ַ���
* @param[in] sKeystr keystr�ֽ���
* @param[out] w ������Կ����󣬴�СΪ60��32λint��240�ֽڣ�
* @param[in] keysize ���ɵ���Կ���ȣ���AES-256����д256��
* @attention keystr��������в���ʶ���κ���ֹ��
* @date 2021-09-19
* @author Brad Conte
* @author GogeBlue
*/
void cmtAESkeyInit(cmtUint8* keystr, cmtUint8* sKeystr, cmtUint32* w, cmtUint16 keysize);

/**
* @brief AES��Կ��ʼ��������ʹ�ö�����Կ���飩
* @param[in] key ������Կ���飬��СΪkeysize
* @param[out] w ������Կ����󣬴�СΪ60��32λint��240�ֽڣ�
* @param[in] keysize ��Կ���ȣ���AES-256����д256��
* @date 2021-09-19
* @author Brad Conte
* @author GogeBlue
*/
void cmtAESRestrictkeyInit(cmtUint8* key, cmtUint32* w, cmtUint16 keysize);

/**
* @brief AESƫ���������ɺ���
* @param[out] iv ƫ����������СΪCMT_AES_BLOCK_SIZE�ֽ�
* @attention ����ر���ƫ������������Կһ����Ҫ����Ϊ�ڽ��ܵ�ʱ����Ҫƫ����������Կ��ͬ���ܡ�
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
void cmtAESInitialVectorInit(cmtUint8* iv);

/**
* @brief AES-ECBģʽ���ܺ�����ÿ�ο��Դ���16��Bytes
* @param[in] in ����
* @param[out] out ���ģ���СΪCMT_AES_BLOCK_SIZE�ֽ�
* @param[in] key ������Կ�����
* @param[in] keysize ��Կ����
* @attention ����һ��ֻ����CMT_AES_BLOCK_SIZE�ֽ�
* @date 2021-09-19
* @author Brad Conte
* @author GogeBlue
*/
void cmtAESecbEnc(cmtUint8* in, cmtUint8* out, cmtUint32* key, cmtUint16 keysize);

/**
* @brief AES-ECBģʽ���ܺ�����ÿ�ο��Դ���16��Bytes
* @param[in] in ����
* @param[out] out ���ģ���СΪCMT_AES_BLOCK_SIZE�ֽ�
* @param[in] key ������Կ�����
* @param[in] keysize ��Կ����
* @attention ����һ��ֻ����CMT_AES_BLOCK_SIZE�ֽ�
* @date 2021-09-19
* @author Brad Conte
* @author GogeBlue
*/
void cmtAESecbDec(cmtUint8* in, cmtUint8* out, cmtUint32* key, cmtUint16 keysize);

/**
* @brief AES-ECBģʽ���ܺ�����ÿ�ο��Դ��������ֽ�
* @param[in] in ����
* @param[out] out ����
* @param[in] size ���Ĵ�С
* @param[in] key ������Կ�����
* @param[in] keysize ��Կ����
* @date 2021-09-19
* @arthur dexnab
*/
void cmtAESecbEncEx(cmtUint8* in, cmtUint64 size, cmtUint8* out, cmtUint32* key, cmtUint16 keysize);

/**
* @brief AES-ECBģʽ���ܺ�����ÿ�ο��Դ��������ֽ�
* @param[in] in ����
* @param[out] out ����
* @param[in] size ���Ĵ�С
* @param[in] key ������Կ�����
* @param[in] keysize ��Կ����
* @date 2021-09-19
* @arthur dexnab
*/
void cmtAESecbDecEx(cmtUint8* in, cmtUint64 size, cmtUint8* out, cmtUint32* key, cmtUint16 keysize);

/**
* @brief AES-CBCģʽ���ܺ�����ÿ�ο��Դ���n * CMT_AES_BLOCK_SIZE���ֽڵ�����
* @param[in] in ����
* @param[in] size �����ֽ���
* @param[out] out ���ģ���СΪsize
* @param[in] key ������Կ�����
* @param[in] keysize ��Կ����
* @param[in] iv ƫ������
* @attention size����ΪCMT_AES_BLOCK_SIZE��������
* @date 2021-09-19
* @author Brad Conte
* @author GogeBlue
*/
void cmtAEScbcEnc(cmtUint8* in, cmtUint64 size, cmtUint8* out, cmtUint32* key, cmtUint16 keysize, cmtUint8* iv);

/**
* @brief AES-CBC-���MACģʽ���ܺ�����ÿ�ο��Դ���n * CMT_AES_BLOCK_SIZE���ֽڵ�����
* @param[in] in ����
* @param[in] size �����ֽ���
* @param[out] out ���MAC����СΪCMT_AES_BLOCK_SIZE
* @param[in] key ������Կ�����
* @param[in] keysize ��Կ����
* @param[in] iv ƫ������
* @date 2021-09-19
* @author Brad Conte
* @author GogeBlue
*/
void cmtAEScbcEncMac(cmtUint8* in, cmtUint64 size, cmtUint8* out, cmtUint32* key, cmtUint16 keysize, cmtUint8* iv);

/**
* @brief AES-CBCģʽ���ܺ�����ÿ�ο��Դ���n * CMT_AES_BLOCK_SIZE�ֽڵ�����
* @param[in] in ����
* @param[in] size �����ֽ���
* @param[out] out ���ģ���СΪsize
* @param[in] key ������Կ�����
* @param[in] keysize ��Կ����
* @param[in] iv ƫ������
* @attention size����ΪCMT_AES_BLOCK_SIZE��������
* @date 2021-09-19
* @author Brad Conte
* @author GogeBlue
*/
void cmtAEScbcDec(cmtUint8* in, cmtUint64 size, cmtUint8* out, cmtUint32* key, cmtUint16 keysize, cmtUint8* iv);

/**
* @brief AES-CTRģʽ���ܺ�����ÿ�ο��Դ���n * CMT_AES_BLOCK_SIZE���ֽڵ�����
* @param[in] in ����
* @param[in] size �����ֽ���
* @param[out] out ���ģ���СΪsize
* @param[in] key ������Կ�����
* @param[in] keysize ��Կ����
* @param[in] iv ƫ������
* @attention size����ΪCMT_AES_BLOCK_SIZE��������
* @date 2021-09-19
* @author Brad Conte
* @author GogeBlue
*/
void cmtAESctrEnc(cmtUint8* in, cmtUint64 size, cmtUint8* out, cmtUint32* key, cmtUint16 keysize, cmtUint8* iv);

/**
* @brief AES-CBCģʽ���ܺ�����ÿ�ο��Դ���n * CMT_AES_BLOCK_SIZE�ֽڵ�����
* @param[in] in ����
* @param[in] size �����ֽ���
* @param[out] out ���ģ���СΪsize
* @param[in] key ������Կ�����
* @param[in] keysize ��Կ����
* @param[in] iv ƫ������
* @attention size����ΪCMT_AES_BLOCK_SIZE��������
* @date 2021-09-19
* @author Brad Conte
* @author GogeBlue
*/
void cmtAESctrDec(cmtUint8* in, cmtUint64 size, cmtUint8* out, cmtUint32* key, cmtUint16 keysize, cmtUint8* iv);

/**
* @brief AES��غ����������ڲ�ʹ�ã�����дע���ˣ�const��ȥ��
* @date 2021-09-15
* @author Brad Conte
* @author GogeBlue
*/
void cmtAESincrIV(cmtUint8 iv[], int counter_size);
void cmtAESpreFirCTRblock(cmtUint8 counter[], const cmtUint8 nonce[], int nonceLen, int payloadLenStoreSize);
void cmtAESccmPreFirFormatBlock(cmtUint8 buf[], int assocLen, int payloadLen, int payloadLenStoreSize, int macLen, const cmtUint8 nonce[], int nonceLen);
void cmtCCMdataFormat(cmtUint8 buf[], int* endOfBuffer, const cmtUint8 assoc[], int assocLen);
void cmtCCMdataPreload(cmtUint8 buf[], int* endOfBuffer, const cmtUint8 payload[], int payloadLen);
void cmtXorBuffer(const cmtUint8 in[], cmtUint8 out[], cmtUint64 size);
void cmtAESpreFirCTRblock(cmtUint8 counter[], const cmtUint8 nonce[], int nonceLen, int payloadLenStoreSize);
void cmtAESccmPreFirFormatBlock(cmtUint8 buf[], int assocLen, int payloadLen, int payloadLenStoreSize, int macLen, const cmtUint8 nonce[], int nonceLen);
void cmtCCMdataFormat(cmtUint8 buf[], int* endOfBuffer, const cmtUint8 assoc[], int assocLen);
void cmtCCMdataPreload(cmtUint8 buf[], int* endOfBuffer, const cmtUint8 payload[], int payloadLen);
cmtUint32 cmtAESSubWord(cmtUint32 word);
void cmtAESRoundKeyInit(cmtUint8 state[][4], const cmtUint32 w[]);
void cmtAESSubBytes(cmtUint8 state[][4]);
void cmtInvSubBytes(cmtUint8 state[][4]);
void cmtShiftRows(cmtUint8 state[][4]);
void cmtInvShiftRows(cmtUint8 state[][4]);
void cmtMixColumns(cmtUint8 state[][4]);
void cmtInvMixColumns(cmtUint8 state[][4]);
/*--------------------------------�ԳƼ��ܺ��� ����--------------------------------*/


#endif