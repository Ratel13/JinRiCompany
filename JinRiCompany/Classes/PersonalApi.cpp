//
//  PersonalApi.cpp
//  GreTest
//
//  Created by lyy on 13-6-14.
//
//

#include "PersonalApi.h"
#include "cocos2d.h"
#include "ScriptParser.h"

using namespace cocos2d;

 vector<string> PersonalApi::split(string str,string pattern)
{
    string::size_type pos;
    vector<string> result;
    str+=pattern;
    int size=str.size();
    
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}


bool PersonalApi::isContantString(string sourceStr,string patternStr)
{
    const char *show;
    
    show=strstr(sourceStr.c_str(),patternStr.c_str()); 
    
    bool isContant;
    if (show == NULL)
    {
        isContant = false;
    }
    else
    {
        isContant = true;
    }
    
    return isContant;
}

size_t PersonalApi::SafeStringCopy(void* dest,size_t destLen,const char* src)
{
	size_t stringLen = strlen(src);
	size_t size=min(destLen-1,stringLen);
	memcpy(dest,src,size);
	((char*)dest)[size]='\0';
	return size;
}

string PersonalApi::string_replace(string & strBig, const string & strsrc, const string &strdst)
{
    string::size_type pos=0;
    string::size_type srclen=strsrc.size();
    string::size_type dstlen=strdst.size();
    
    while( (pos=strBig.find(strsrc, pos)) != string::npos)
    {
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
    
    return strBig;
}

string PersonalApi::convertIntToString (int aNum) //int ?? string
{
    ostringstream oss;
    oss<<aNum;
    return oss.str();
}
string PersonalApi::convertfloatToString (float aNum) //int ?? string
{
    ostringstream oss;
    oss<<aNum;
    return oss.str();
}
int PersonalApi::convertStringToInt (string aStr) //string ?? int
{
    return  atoi( aStr.c_str());
}

string PersonalApi::getRealImageName (const char * imageName,const char * defaultName)
{
    CCFileUtils* aCCFileUtils = CCFileUtils::sharedFileUtils();
    string  str=(aCCFileUtils->getWritablePath()+imageName).c_str();
    
    FILE *fp =fopen((aCCFileUtils->getWritablePath()+imageName).c_str(),"r");//����·�����ļ�

    if (fp)
    {
        fclose(fp);
        return str;
    }
    else
    {
        return defaultName;
    }
  
}

void PersonalApi::wirteVecToXml(map<string, string> aMap,string fileName)
{
    string xmlStr;
    for (int i =0; i<aMap.size(); i++)
    {
        xmlStr += aMap[PersonalApi::convertIntToString(i+1)]+"\n";
    }
   
    const char * aChar = xmlStr.c_str();
    
    //ȡ���ļ������λ��
    CCFileUtils* aCCFileUtils = CCFileUtils::sharedFileUtils();
    std::string documentPath = aCCFileUtils->getWritablePath();

    
    string filePath = documentPath + fileName;
    
    //�����ַ���Ϊxml�ļ�
    string path = filePath;
    FILE *fp =fopen(path.c_str(),"w");
    
    
    fputs(aChar, fp);
    fclose(fp);
    
}

map<string, string> PersonalApi::readXmlToVec(const char * key)
{
    CCFileUtils* aCCFileUtils = CCFileUtils::sharedFileUtils();
    std::string documentPath = aCCFileUtils->getWritablePath();
    string fileName = key;
    
    string filePath = documentPath + fileName;
    //2,��ȡxml�ļ�Ϊstring
    
    string path = filePath;
    FILE *fp =fopen(path.c_str(),"r");//����·�����ļ�
    
    map<string, string> resultMap;
    if (!fp)
    {
        return resultMap;
    }
    
    
    char *pchBuf = NULL;//��Ҫȡ�õ��ַ���
    int  nLen = 0;//��Ҫȡ�õ��ַ�������
    fseek(fp,0,SEEK_END);//�ļ�ָ���Ƶ��ļ�β
    nLen =ftell(fp); //�õ���ǰָ��λ��,�����ļ��ĳ���
    rewind(fp);   //�ļ�ָ��ָ����ļ�ͷλ��
    
    //��̬����ռ�,Ϊ�����ַ�����β��־\0,������һ���ַ��Ŀռ�
    pchBuf = (char*)malloc(sizeof(char)*nLen+1);
    if(!pchBuf)
    {
        //perror("�ڴ治��!\n");
        exit(0);
    }
    
    //��ȡ�ļ�����//��ȡ�ĳ��Ⱥ�Դ�ļ������п����г��룬�����Զ����� nLen
    nLen =fread(pchBuf,sizeof(char), nLen, fp);
    
    pchBuf[nLen] ='\0';//����ַ�����β��־
    
    //printf("sss==%s\n", pchBuf);//�Ѷ�ȡ�������������Ļ����
    string detailStr = pchBuf;
    fclose(fp); //�ر��ļ�
    free(pchBuf);//�ͷſռ�
    
    vector<string> resultVec = PersonalApi::split(detailStr,"\n");
    for (int i = 0; i<resultVec.size(); i++)
    {
        resultMap[PersonalApi::convertIntToString(i+1)] = resultVec[i];
    }
  
    return resultMap;
}
map<string, string> PersonalApi::getRealGroupImageMap(CCDictionary * plistDictionary,const char * mapName,const char * preMapName)
{
    map<string, string> aMap;
    if (PersonalApi::readXmlToVec(mapName).size()>0)
    {
        aMap = PersonalApi::readXmlToVec(mapName);
    }
    else
    {
       
        aMap =  ScriptParser::getGroupImageFromPlist(plistDictionary,preMapName);
    }
    
    return aMap;
}
map<string, string> PersonalApi::getRealGroupStringMap(CCDictionary * plistDictionary,const char * mapName,const char * preMapName)
{
    map<string, string> aMap;
    if (PersonalApi::readXmlToVec(mapName).size()>0)
    {
        aMap = PersonalApi::readXmlToVec(mapName);
    }
    else
    {
        aMap =  ScriptParser::getGroupStringFromPlist(plistDictionary,preMapName);
    }
    
    return aMap;
}
