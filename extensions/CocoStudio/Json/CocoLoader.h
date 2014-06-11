#ifndef _COCOLOADER_H
#define _COCOLOADER_H
//=========================================================================
//File:CocoLoader.h
//Author: Bianan@chukong-inc.com
//Desc:����Coco�ĵ����ļ�����
//=========================================================================

#include <stdio.h>
#include <vector>
#include <cstdio>
#include <stdint.h>
#include "../Json/rapidjson/rapidjson.h"
#include "../Json/rapidjson/document.h"

using namespace std;
using namespace rapidjson;
//const	char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
#pragma pack (4)
//�����ýڵ���������
struct  stExpCocoAttribDesc
{
	Type		m_Type;					//��Ӧ������
	uint64_t	m_szName;				//��Ӧ������
	uint64_t	m_szDefaultValue;		//��Ӧ��Ĭ��ֵ
public:
	//�ؽ�
	void	ReBuild(char* pStringMemoryAddr)
	{
		m_szName = m_szName + (uint64_t)pStringMemoryAddr;
		m_szDefaultValue = m_szDefaultValue + (uint64_t)pStringMemoryAddr;
	}
}
;
//������Coco�������ڵ�
struct  stExpCocoObjectDesc
{
	uint32_t		m_nAttribNum;			//��������
	uint64_t		m_szName;				//��Ӧ�������ַ�����λ��,Ĭ��Ϊ0
	uint64_t		m_pAttribDescArray;		//��������
public:
	//�ؽ�
	void	ReBuild(char* pAttribMemoryAddr,char* pStringMemoryAddr)
	{
		m_szName = m_szName + (uint64_t)pStringMemoryAddr;
		m_pAttribDescArray = m_pAttribDescArray + (uint64_t)pAttribMemoryAddr;
		stExpCocoAttribDesc* tpAttribDescArray = (stExpCocoAttribDesc*)m_pAttribDescArray;
		for(int i = 0 ; i < m_nAttribNum ; i++)
		{
			tpAttribDescArray[i].ReBuild(pStringMemoryAddr);
		}
	}
	
	//ȡ������
	void	GetAttribIndexArray(vector<string>&	vAttribVec_In,vector<int>& vIndexVec_Out)
	{
		vector<string>::iterator tIter;
		for(tIter = vAttribVec_In.begin(); tIter != vAttribVec_In.end(); tIter++)
		{
			bool bFind = false;
			stExpCocoAttribDesc* tpAttribDescArray = (stExpCocoAttribDesc*)m_pAttribDescArray;
			for(int i = 0 ; i < m_nAttribNum ; i++)
			{
				if( 0 == strcmp((char*)tpAttribDescArray[i].m_szName,tIter->c_str()))
				{
					bFind = true;
					vIndexVec_Out.push_back(i);
					break;
				}
			}
			if(false == bFind)
			{
				vIndexVec_Out.push_back(-1);
			}
		}
	}
};

class CocoLoader;
//Coco�ڵ�����
struct  stExpCocoNode
{
protected:
	int32_t						m_ObjIndex;				//��Ӧ����������
	int32_t						m_AttribIndex;			//���Ե���������
	uint32_t					m_ChildNum;				//�ӽڵ�����
	uint64_t					m_szValue;				//��Ӧ��Ĭ��ֵ
	uint64_t					m_ChildArray;			//��Ӧ���ӽڵ�����
public:

	//ȡ����
	Type				GetType(CocoLoader*		pCoco);
	//ȡ����
	char*				GetName(CocoLoader*		pCoco);
	//ȡֵ
	char*				GetValue();
	//ȡ���ӽ������
	int					GetChildNum();
	//ȡ���ӽ������
	stExpCocoNode*		GetChildArray();
public:
	//�ؽ�
	inline  void	ReBuild(char* pCocoNodeAddr,char* pStringMemoryAddr);
	//��ӡ
	void	WriteJson(CocoLoader*		pCoco,void*	pFileName = NULL,int vLayer = 0,bool bEndNode = false,bool bParentNodeIsArray = false);
}
;

//������ͷ�ļ�
struct		stCocoFileHeader
{
	char			m_FileDesc[32];
	char			m_Version[32];
	uint32_t		m_nFirstUsed;
	uint32_t		m_ObjectCount;
	uint64_t		m_lAttribMemAddr;
	uint64_t		m_CocoNodeMemAddr;
	uint64_t		m_lStringMemAddr;
	
};

//CocoLoader
class CocoLoader
{
	//ͷ��Ϣ
	stCocoFileHeader*			m_pFileHeader;
	//�����
	stExpCocoNode*				m_pRootNode;
	//��������
	stExpCocoObjectDesc*		m_pObjectDescArray;

public:
	//����
	CocoLoader();
	//����
	~CocoLoader();

public:

	//�Ӷ������ļ��ж�ȡ
	bool					ReadCocoBinBuff(char* pBinBuff);
	//ͷ��Ϣ
	stCocoFileHeader*		GetFileHeader(){return m_pFileHeader;}
	//�����
	stExpCocoNode*			GetRootCocoNode(){return	m_pRootNode;}
	//��������
	stExpCocoObjectDesc*	GetCocoObjectDescArray(){return	m_pObjectDescArray;}
	//ȡ����Ӧ�������� 
	stExpCocoObjectDesc*	GetCocoObjectDesc(const char* szObjDesc);
			
};
#pragma pack ()
#endif