/**
* @file cmtCore.c
* @date 2021-09-22
* @author Dexnab
*/

#include <cmtString.h>

cmtUint8 cmtANSIchSize(cmtChar* ch, cmtChar* locale)
{
	cmtUint8 chsize;
	cmtChar CurLocaleCp[CMT_LOCALE_MAX], * CurLocale;

	//���浱ǰlocale
	/*���Աʼ�:
	* ֮��setlocale��ı�˴�����ֵָ����ڴ�,������Ҫ����һ��
	*/
	memset(CurLocaleCp, 0, sizeof(CurLocaleCp));
	CurLocale = setlocale(LC_ALL, NULL);
	strncpy(CurLocaleCp, CurLocale, sizeof(CurLocaleCp) - 1);
	//����locale
	setlocale(LC_ALL, locale);

	chsize = mblen(ch, MB_CUR_MAX);

	//�ָ�locale
	setlocale(LC_ALL, CurLocaleCp);

	return chsize;
}

cmtUint64 cmtANSIstrSize(cmtChar* str)
{
	cmtUint64 size = 0;

	while (str[size]) size++;

	return size;
}

cmtUint64 cmtANSIlen(cmtANSIstr* str)
{
	cmtUint64 len = 0, r = 0;
	cmtChar CurLocaleCp[CMT_LOCALE_MAX], * CurLocale;

	//���浱ǰlocale
	memset(CurLocaleCp, 0, sizeof(CurLocaleCp));
	CurLocale = setlocale(LC_ALL, NULL);
	strncpy(CurLocaleCp, CurLocale, sizeof(CurLocaleCp) - 1);
	//����locale
	setlocale(LC_ALL, str->locale);

	while (r < str->size)
	{
		//mblen�����'\0'�����ַ���������Ҫ����������
		if (!str->data[r]) r++;
		else r += mblen(str->data + r, str->size - r);
		len++;
	}

	//�ָ�locale
	setlocale(LC_ALL, CurLocaleCp);

	return len;
}

cmtUint64 cmtANSItoU8size(cmtANSIstr* ansi)
{
	cmtUint64 rAs = 0, u8size = 0;
	cmtUint8 chsize;
	cmtWchar u16temp[2];
	cmtChar CurLocaleCp[CMT_LOCALE_MAX], * CurLocale;

	//���浱ǰlocale
	memset(CurLocaleCp, 0, sizeof(CurLocaleCp));
	CurLocale = setlocale(LC_ALL, NULL);
	strncpy(CurLocaleCp, CurLocale, sizeof(CurLocaleCp) - 1);
	//����locale
	setlocale(LC_ALL, ansi->locale);

	while (rAs < ansi->size)
	{
		//'\0'
		if (!ansi->data[rAs])
		{
			rAs++;
			u8size++;
		}
		else
		{
			chsize = mblen(ansi->data + rAs, ansi->size - rAs);
			mbtowc(u16temp, ansi->data + rAs, chsize);
			//������ֲ�Ϊ�㣬��ô�����������֣���ΧΪ[0x010000,0x10ffff]
			if (u16temp[0]) u8size += 4;
			//�������Ϊ�㣬��ô����ֻ��һ���֣��ڶ����֣�
			else
			{
				//[0,0x7f]
				if (u16temp[1] < 0x80) u8size += 1;
				//[0x80,0x07ff]
				else if (u16temp[1] < 0x800) u8size += 2;
				//[0x0800,0xffff]
				else u8size += 3;
			}
			rAs += chsize;
		}
	}

	//�ָ�locale
	setlocale(LC_ALL, CurLocaleCp);

	return u8size;
}

void cmtANSItoU8(cmtANSIstr* ansi, cmtU8str* u8)
{
	cmtUint64 rAs = 0, rU8 = 0;
	cmtUint8 chsize;
	cmtWchar u16temp[2];
	cmtChar CurLocaleCp[CMT_LOCALE_MAX], * CurLocale;

	//���浱ǰlocale
	memset(CurLocaleCp, 0, sizeof(CurLocaleCp));
	CurLocale = setlocale(LC_ALL, NULL);
	strncpy(CurLocaleCp, CurLocale, sizeof(CurLocaleCp) - 1);
	//����locale
	setlocale(LC_ALL, ansi->locale);

	while (rAs < ansi->size)
	{
		//'\0'
		if (!ansi->data[rAs])
		{
			u8->data[rU8] = 0;
			rAs++;
			rU8++;
		}
		else
		{
			chsize = mblen(ansi->data + rAs, ansi->size - rAs);
			mbtowc(u16temp, ansi->data + rAs, chsize);
			//������ֲ�Ϊ�㣬��ô�����������֣���ΧΪ[0x010000,0x10ffff]
			if (u16temp[0])
			{
				u16temp[0] = u16temp[0] - 0xd800 + 0x100;
				u16temp[1] -= 0xdc00;
				//u8�����ֽ�
				u8->data[rU8 + 3] = 0x80 + (cmtUint8)u16temp[1] & 0x3f;
				//u8�����ֽ�
				u16temp[1] >>= 6;
				u8->data[rU8 + 2] = 0x80 + (cmtUint8)u16temp[1] + ((cmtUint8)u16temp[0] & 0x3) << 4;
				//u8�ڶ��ֽ�
				u16temp[0] >>= 2;
				u8->data[rU8 + 1] = 0x80 + (cmtUint8)u16temp[0] & 0x3f;
				//u8��һ�ֽ�
				u16temp[0] >>= 6;
				u8->data[rU8] = 0xf0 + (cmtUint8)u16temp[0];
				rU8 += 4;
			}
			//�������Ϊ�㣬��ô����ֻ��һ���֣��ڶ����֣�
			else
			{
				//[0,0x7f]
				if (u16temp[1] < 0x80)
				{
					u8->data[rU8] = (cmtUint8)u16temp[1];
					rU8 += 1;
				}
				//[0x80,0x07ff]
				else if (u16temp[1] < 0x800)
				{
					//u8�ڶ��ֽ�
					u8->data[rU8 + 1] = 0x80 + (cmtUint8)u16temp[1] & 0x3f;
					//u8��һ�ֽ�
					u16temp[1] >>= 6;
					u8->data[rU8] = 0xc0 + (cmtUint8)u16temp[1];
					rU8 += 2;
				}
				//[0x0800,0xffff]
				else
				{
					//u8�����ֽ�
					u8->data[rU8 + 2] = 0x80 + (cmtUint8)u16temp[1] & 0x3f;
					//u8�ڶ��ֽ�
					u16temp[1] >>= 6;
					u8->data[rU8 + 1] = 0x80 + (cmtUint8)u16temp[1] & 0x3f;
					//u8�����ֽ�
					u16temp[1] >>= 6;
					u8->data[rU8] = 0xe0 + (cmtUint8)u16temp[1];
					rU8 += 3;
				}
			}
			rAs += chsize;
		}
	}

	//�ָ�locale
	setlocale(LC_ALL, CurLocaleCp);
}

cmtUint64 cmtANSItoU16size(cmtANSIstr* ansi)
{
	cmtUint64 rAs = 0, u16size = 0;
	cmtUint8 chsize;
	cmtWchar u16temp[2];
	cmtChar CurLocaleCp[CMT_LOCALE_MAX], * CurLocale;

	//���浱ǰlocale
	memset(CurLocaleCp, 0, sizeof(CurLocaleCp));
	CurLocale = setlocale(LC_ALL, NULL);
	strncpy(CurLocaleCp, CurLocale, sizeof(CurLocaleCp) - 1);
	//����locale
	setlocale(LC_ALL, ansi->locale);

	while (rAs < ansi->size)
	{
		//'\0'
		if (!ansi->data[rAs])
		{
			rAs++;
			u16size += 2;
		}
		else
		{
			chsize = mblen(ansi->data + rAs, ansi->size - rAs);
			mbtowc(u16temp, ansi->data + rAs, chsize);
			//������ֲ�Ϊ�㣬��ô�����������֣���ΧΪ[0x010000,0x10ffff]
			if (u16temp[0]) u16size += 4;
			//�������Ϊ�㣬��ô����ֻ��һ���֣��ڶ����֣�
			else u16size += 2;
			rAs += chsize;
		}
	}

	//�ָ�locale
	setlocale(LC_ALL, CurLocaleCp);

	return u16size;
}

void cmtANSItoU16(cmtANSIstr* ansi, cmtU16str* u16)
{
	cmtUint64 rAs = 0, rU16 = 0;
	cmtUint8 chsize;
	cmtChar CurLocaleCp[CMT_LOCALE_MAX], * CurLocale;

	//���浱ǰlocale
	memset(CurLocaleCp, 0, sizeof(CurLocaleCp));
	CurLocale = setlocale(LC_ALL, NULL);
	strncpy(CurLocaleCp, CurLocale, sizeof(CurLocaleCp) - 1);
	//����locale
	setlocale(LC_ALL, ansi->locale);

	while (rAs < ansi->size)
	{
		//'\0'
		if (!ansi->data[rAs])
		{
			u16->data[rU16] = 0;
			rAs++;
			rU16 += 2;
		}
		else
		{
			chsize = mblen(ansi->data + rAs, ansi->size - rAs);
			mbtowc(u16->data + rU16, ansi->data + rAs, chsize);
			//������ֲ�Ϊ�㣬��ô�����������֣���ΧΪ[0x010000,0x10ffff]
			if (u16->data[rU16]) rU16 += 4;
			//�������Ϊ�㣬��ô����ֻ��һ���֣��ڶ����֣�
			else rU16 += 2;
			rAs += chsize;
		}
	}

	//�ָ�locale
	setlocale(LC_ALL, CurLocaleCp);
}