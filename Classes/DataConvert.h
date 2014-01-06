/*
封装数据转换类
*/
#ifndef __DATACONVER__HEADER__
#define __DATACONVER__HEADER__


class CDataConvert
{
public:
	CDataConvert(void);
	~CDataConvert(void);

	CDataConvert(int nValue);
	CDataConvert(float fValue);
	CDataConvert(double dValue);
	CDataConvert(char* pValue);
	CDataConvert(const char* pcValue);

	operator char*();
	operator const char*();
	operator int();
	operator float();
	operator double();
	
	int		ToInt(const char* pValue);
	float	ToFloat(const char* pValue);
	double	ToDouble(const char* pValue);

	char*	ToString(int nValue);
	char*	ToString(float fValue);
	char*	toString(double dValue);

	char*	Format(const char* pcFormat, ...);

	char*	UTF8ToUnicode(const char* pcUTF8Value);

	//注意:返回的值要保存起来,如果连续调用两次本函数,第二次调用时有可能将第一次得到的char*值改变
	char*	UTF8ToGB(const char* pcUTF8Value);
	
	char*	UnicodeToUTF8(const char* pcUniValue);
	char*	UnicodeToGB(const char* pcUniValue);

	char*	GBToUTF8(const char* pcGBValue);
	char*	GBToUnicode(const char* pcGBValue);
	
	char*	CharSet_Conver(const char* pSrc, const char* pSrcCharSet, const char* pDstCharSet);

	void	SetBuffSize(int nSize);
	void	ResetBuff();
protected:
	
	void	Init();
	char	m_szBuff[1000];

	int		m_nBigBuffSize;
	char*	m_pBigBuff;
};

#endif