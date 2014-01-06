/********************************************************************
	created:	2012/03/07
	author:		Huang Liang Jiang
	purpose:	∑‚◊∞ ˝æ›◊™ªª¿‡
*********************************************************************/
#include "DataConvert.h"

#include <vector>
#include <string>

#ifdef WIN32
#include "platform/third_party/win32/iconv/iconv.h"
#else
#include <iconv.h>//"platform/third_party/win32/iconv/iconv.h"
#endif
#include <algorithm>
#include <stdarg.h>
#include "cocos2d.h"
#define RtlZeroMemory(Destination, Length) memset((Destination), 0, (Length))
#define ZeroMemory RtlZeroMemory

bool Code_Convert(const char* from_chartset, const  char* to_chartset,const char* pSrc,int srcLen,char* lpRec, int recSize)
{
	if(lpRec==NULL)
	{
		return false;
	}

	iconv_t cd=0;

	size_t iInLen=srcLen;
	size_t iOutLen = recSize;

	const char **pin = &pSrc;
	char **pout = &lpRec;
	cd = iconv_open(to_chartset,from_chartset);
	if (cd==0) 
	{
		return false;
	}
	memset(lpRec,0,recSize);

	bool bRet = false;

#ifndef WIN32
#ifdef DEBUG1
	bRet = ((iconv(cd,(const char **)pin,(size_t*)&iInLen,pout,&iOutLen) == -1) ? false : true);
#else
	bRet = ((iconv(cd,(char **)pin,&iInLen,pout,&iOutLen) == -1) ? false : true);
#endif
#else
	bRet = ((iconv(cd,(const char **)pin,&iInLen,pout,&iOutLen) == -1) ? false : true);
#endif
	iconv_close(cd);
	return bRet;
}

CDataConvert::CDataConvert(void)
{
	Init();
}

CDataConvert::CDataConvert( int nValue )
{
	Init();
	sprintf(m_szBuff, "%d", nValue);
}

CDataConvert::CDataConvert( float fValue )
{
	Init();
	sprintf(m_szBuff, "%f", fValue);
}

CDataConvert::CDataConvert( double fValue )
{
	Init();
	sprintf(m_szBuff, "%f", fValue);
}

CDataConvert::CDataConvert( char* pValue )
{
	Init();
	if(pValue != NULL)
	{
		strncpy(m_szBuff, pValue, sizeof(m_szBuff)-1);
	}
	
}

CDataConvert::CDataConvert( const char* pcValue )
{
	Init();
	if(pcValue != NULL)
	{
		strncpy(m_szBuff, pcValue, sizeof(m_szBuff)-1);
	}
}

CDataConvert::~CDataConvert(void)
{
	if (m_pBigBuff != NULL)
	{
		delete [] m_pBigBuff;
		m_pBigBuff = NULL;
	}
}

CDataConvert::operator char*()
{
	return m_szBuff;
}

CDataConvert::operator const char*()
{
	return m_szBuff;
}

CDataConvert::operator int()
{
	return atoi(m_szBuff);
}

CDataConvert::operator float()
{
	return (float)atof(m_szBuff);
}

CDataConvert::operator double()
{
	return atof(m_szBuff);
}

char* CDataConvert::Format( const char* pcFormat, ... )
{
	va_list args;
	va_start (args, pcFormat);
	int nRet = vsnprintf (m_szBuff, sizeof(m_szBuff)-1, pcFormat, args);
	va_end (args);
	if (nRet == -1)
	{
		while (nRet == -1)//Buff Not enough
		{
			if (m_pBigBuff != NULL)
			{
				delete [] m_pBigBuff;
				m_nBigBuffSize *= 10;
			}
			else
			{
				m_nBigBuffSize = 1024;
			}
			m_pBigBuff = new char[m_nBigBuffSize];
			ZeroMemory(m_pBigBuff, m_nBigBuffSize);
			va_start (args, pcFormat);
			nRet = vsnprintf(m_pBigBuff, m_nBigBuffSize-1, pcFormat, args);
			va_end (args);
		}
		return m_pBigBuff;
	}
	
	return m_szBuff;
}

int CDataConvert::ToInt(const  char* pValue )
{
	if (pValue == NULL)
	{
		pValue = "";
	}
	strncpy(m_szBuff, pValue, sizeof(m_szBuff)-1);
	return atoi(pValue);
}

float CDataConvert::ToFloat( const char* pValue )
{
	if (pValue == NULL)
	{
		pValue = "";
	}
	strncpy(m_szBuff, pValue, sizeof(m_szBuff)-1);
	return (float)atof(pValue);
}

double CDataConvert::ToDouble( const char* pValue )
{
	if (pValue == NULL)
	{
		pValue = "";
	}
	strncpy(m_szBuff, pValue, sizeof(m_szBuff)-1);
	return atof(pValue);
}

char* CDataConvert::ToString( int nValue)
{
	sprintf(m_szBuff, "%d", nValue);
	return m_szBuff;
}

char* CDataConvert::ToString( float fValue)
{
	sprintf(m_szBuff, "%f", fValue);
	return m_szBuff;
}

char* CDataConvert::toString( double dValue)
{
	sprintf(m_szBuff, "%f", dValue);
	return m_szBuff;
}

char* CDataConvert::UTF8ToUnicode( const char* pcUTF8Value )
{
	return CharSet_Conver(pcUTF8Value, "UTF-8", "UCS-2-INTERNAL");
}

char* CDataConvert::UTF8ToGB( const char* pcUTF8Value )
{
	return CharSet_Conver(pcUTF8Value, "UTF-8", "GB18030");
}

char* CDataConvert::UnicodeToUTF8( const char* pcUniValue )
{
	return CharSet_Conver(pcUniValue, "UCS-2-INTERNAL", "UTF-8");
}

char* CDataConvert::UnicodeToGB( const char* pcUniValue )
{
	return CharSet_Conver(pcUniValue, "UCS-2-INTERNAL", "GB18030");
}

char* CDataConvert::GBToUTF8( const char* pcGBValue )
{
	return CharSet_Conver(pcGBValue, "GB18030", "UTF-8");
}

char* CDataConvert::GBToUnicode( const char* pcGBValue )
{
	return CharSet_Conver(pcGBValue, "GB18030", "UCS-2-INTERNAL");
}

void CDataConvert::SetBuffSize( int nSize )
{
	if (nSize > sizeof(m_szBuff))
	{
		if (nSize > m_nBigBuffSize)
		{
			if (m_pBigBuff != NULL)
			{
				delete m_pBigBuff;
				m_pBigBuff = NULL;
			}
			m_nBigBuffSize = nSize;
			m_pBigBuff = new char[m_nBigBuffSize];
		}
	}
}

typedef const wchar_t* LPCWSTR;
char* CDataConvert::CharSet_Conver( const char* pSrc, const char* pSrcCharSet, const char* pDstCharSet )
{
	char* pBuff = m_szBuff;
	int nBuffLen = sizeof(m_szBuff)-1;
	int nSrcLen = strlen(pSrc);
	int nNeedLen = nSrcLen * sizeof(wchar_t);

	if (nNeedLen > sizeof(m_szBuff)-1)
	{
// 		if (nNeedLen >= m_nBigBuffSize)
// 		{
			if (m_pBigBuff != NULL)
			{
				delete [] m_pBigBuff;
				m_pBigBuff = NULL;
			}
			nBuffLen = nNeedLen;
			m_pBigBuff = new char[nBuffLen];
			pBuff = m_pBigBuff;
			m_nBigBuffSize = nBuffLen;

/*		}*/
	}

	//if (sizeof(wchar_t) == 2)
	//{
		if(!Code_Convert(pSrcCharSet, pDstCharSet, pSrc, nSrcLen, pBuff,nBuffLen))
		{
			return NULL;
		}
	//}
	return pBuff;
}

void CDataConvert::ResetBuff()
{
	ZeroMemory(m_szBuff, sizeof(m_szBuff));
	if (m_pBigBuff != NULL)
	{
		ZeroMemory(m_pBigBuff, m_nBigBuffSize);
	}
}

void CDataConvert::Init()
{
	ZeroMemory(m_szBuff, sizeof(m_szBuff));
	m_nBigBuffSize = 0;
	m_pBigBuff = NULL;
}