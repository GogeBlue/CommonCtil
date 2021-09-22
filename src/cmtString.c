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

	while (rAs < ansi->size)
	{
		if (!ansi->data[rAs])
		{
			rAs++;
			u8size++;
		}
		else
		{
			chsize = mblen(ansi->data + rAs, ansi->size - rAs);
			mbtowc(u16temp, ansi->data + rAs, chsize);

		}
	}
}