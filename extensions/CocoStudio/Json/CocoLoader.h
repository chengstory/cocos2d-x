#ifndef _COCOLOADER_H
#define _COCOLOADER_H
//=========================================================================
//File:CocoLoader.h
//Author: Bianan@chukong-inc.com
//Desc:加载Coco的导出文件的类
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
//导出用节点属性描述
struct  stExpCocoAttribDesc
{
	Type		m_Type;					//对应的类型
	uint64_t	m_szName;				//对应的名称
	uint64_t	m_szDefaultValue;		//对应的默认值
public:
	//重建
	void	ReBuild(char* pStringMemoryAddr)
	{
		m_szName = m_szName + (uint64_t)pStringMemoryAddr;
		m_szDefaultValue = m_szDefaultValue + (uint64_t)pStringMemoryAddr;
	}
}
;
//导出用Coco类描述节点
struct  stExpCocoObjectDesc
{
	uint32_t		m_nAttribNum;			//属性数量
	uint64_t		m_szName;				//对应的名称字符串的位置,默认为0
	uint64_t		m_pAttribDescArray;		//属性数组
public:
	//重建
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
	
	//取得索引
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
//Coco节点类型
struct  stExpCocoNode
{
protected:
	int32_t						m_ObjIndex;				//对应的物体索引
	int32_t						m_AttribIndex;			//属性的物体索引
	uint32_t					m_ChildNum;				//子节点数量
	uint64_t					m_szValue;				//对应的默认值
	uint64_t					m_ChildArray;			//对应的子节点数组
public:

	//取类型
	Type				GetType(CocoLoader*		pCoco);
	//取名称
	char*				GetName(CocoLoader*		pCoco);
	//取值
	char*				GetValue();
	//取得子结点数量
	int					GetChildNum();
	//取得子结点数组
	stExpCocoNode*		GetChildArray();
public:
	//重建
	inline  void	ReBuild(char* pCocoNodeAddr,char* pStringMemoryAddr);
	//打印
	void	WriteJson(CocoLoader*		pCoco,void*	pFileName = NULL,int vLayer = 0,bool bEndNode = false,bool bParentNodeIsArray = false);
}
;

//二进制头文件
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
	//头信息
	stCocoFileHeader*			m_pFileHeader;
	//根结点
	stExpCocoNode*				m_pRootNode;
	//类结点容器
	stExpCocoObjectDesc*		m_pObjectDescArray;

public:
	//构造
	CocoLoader();
	//析构
	~CocoLoader();

public:

	//从二进制文件中读取
	bool					ReadCocoBinBuff(char* pBinBuff);
	//头信息
	stCocoFileHeader*		GetFileHeader(){return m_pFileHeader;}
	//根结点
	stExpCocoNode*			GetRootCocoNode(){return	m_pRootNode;}
	//类结点容器
	stExpCocoObjectDesc*	GetCocoObjectDescArray(){return	m_pObjectDescArray;}
	//取得相应的类描述 
	stExpCocoObjectDesc*	GetCocoObjectDesc(const char* szObjDesc);
			
};
#pragma pack ()
#endif