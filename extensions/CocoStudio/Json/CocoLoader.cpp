#include "CocoLoader.h"
#include <tchar.h>
#include <windows.h>
const	char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
const   char* kObjKeyName[] = { "__type" , "classname" };
char	g_Buff[2048];

//取类型
Type	stExpCocoNode::GetType(CocoLoader*		pCoco)
{
	Type	tType = kObjectType;
	if(m_ObjIndex >= 0)
	{
		stExpCocoObjectDesc*	tpCocoObjectDesc = pCoco->GetCocoObjectDescArray();
		if( m_AttribIndex >= 0 )
		{
			stExpCocoAttribDesc* tpAttribDescArray = (stExpCocoAttribDesc*) tpCocoObjectDesc[m_ObjIndex].m_pAttribDescArray;
			tType = tpAttribDescArray[m_AttribIndex].m_Type;
			
			if(kFalseType == tType || kTrueType == tType)
			{
				char* szValue = (char*)m_szValue;
				if(szValue[0] == '0')
				{
					return kFalseType;
				}
				else
				{
					return kTrueType;
				}
			}

		}
		else
		{
			tType = kObjectType;
		}
	}
	else
	{
		if(m_AttribIndex >= 0)
		{
			tType   = (Type)m_ChildNum;

			if(kFalseType == tType || kTrueType == tType)
			{
				char* szValue = (char*)m_szValue;
				if(szValue[0] == '0')
				{
					return kFalseType;
				}
				else
				{
					return kTrueType;
				}
			}
		}
		else
		{
			tType = kArrayType;
		}
	}
	return tType;
}
//取名称
char*	stExpCocoNode::GetName(CocoLoader*		pCoco)
{
	char*   szName  = NULL ;
	if(m_ObjIndex >= 0)
	{
		stExpCocoObjectDesc*	tpCocoObjectDesc = pCoco->GetCocoObjectDescArray();
		if( m_AttribIndex >= 0 )
		{
			stExpCocoAttribDesc* tpAttribDescArray = (stExpCocoAttribDesc*) tpCocoObjectDesc[m_ObjIndex].m_pAttribDescArray;
			szName = (char*)tpAttribDescArray[m_AttribIndex].m_szName;
		}
		else
		{
			//如果名字与类名称不同，则按真实值设置
			char* szValue = (char*)m_szValue;
			if(szValue[0])
			{
				//数组
				szName = (char*)m_szValue;
			}
			else
			{
				//结构
				szName = (char*)tpCocoObjectDesc[m_ObjIndex].m_szName;
			}
		}
	}
	else
	{
		if(m_AttribIndex >= 0)
		{
			char*   pStringAddr = (char*)pCoco->GetCocoObjectDescArray() + pCoco->GetFileHeader()->m_lStringMemAddr ;
			szName  = m_ChildArray + pStringAddr;	
		}
		else
		{
			szName = (char*)m_szValue;
		}
	}
	return szName ;
}
//取值
char*	stExpCocoNode::GetValue()
{
	return (char*)m_szValue;
}
//取得子结点数量
int		stExpCocoNode::GetChildNum()
{
	return m_ChildNum;
}
//取得子结点数组
stExpCocoNode*		stExpCocoNode::GetChildArray()
{
	return (stExpCocoNode*)m_ChildArray;
}
//重建
void	stExpCocoNode::ReBuild(char* pCocoNodeAddr,char* pStringMemoryAddr)
{
	m_szValue = m_szValue + (uint64_t)pStringMemoryAddr;
	//如果是物体或数组，分组子结点
	if( -1 == m_AttribIndex )
	{
		if(m_ChildNum > 0)
		{
			m_ChildArray = m_ChildArray + (uint64_t)pCocoNodeAddr;
		
			stExpCocoNode* tpChildArray = (stExpCocoNode*)m_ChildArray;
			for(int i = 0 ; i < m_ChildNum ; i++)
			{
				tpChildArray[i].ReBuild(pCocoNodeAddr,pStringMemoryAddr);
			}
		}
	}

}

//构造
CocoLoader::CocoLoader()
{
	m_pRootNode = NULL;
	m_pObjectDescArray = NULL;
}
//析构
CocoLoader::~CocoLoader()
{

}

//从二进制文件中读取
bool	CocoLoader::ReadCocoBinBuff(char* pBinBuff)
{
	//Type
	char*	pTempBuff = pBinBuff;

	//头信息
	m_pFileHeader = (stCocoFileHeader*)pTempBuff;
	pTempBuff += sizeof(stCocoFileHeader);

	//遍历类
	char*   pStartAddr = pTempBuff;
	m_pObjectDescArray = (stExpCocoObjectDesc*)pStartAddr;

	char*   pAttrAddr = pStartAddr + m_pFileHeader->m_lAttribMemAddr ;
	char*	pCocoMemAddr = pStartAddr + m_pFileHeader->m_CocoNodeMemAddr;
	char*   pStringAddr = pStartAddr + m_pFileHeader->m_lStringMemAddr ;

	m_pRootNode = (stExpCocoNode*)pCocoMemAddr;

	if(1 == m_pFileHeader->m_nFirstUsed)
	{	
		for(int i = 0 ; i < m_pFileHeader->m_ObjectCount ; i++)
		{
			m_pObjectDescArray[i].ReBuild(pAttrAddr,pStringAddr)	;
		}
		m_pRootNode->ReBuild(pCocoMemAddr,pStringAddr);

		m_pFileHeader->m_nFirstUsed = 0;
	}

	return true;
}
//取得相应的类描述 
stExpCocoObjectDesc*	CocoLoader::GetCocoObjectDesc(const char* szObjDesc)
{
	for(int i = 0 ; i < m_pFileHeader->m_ObjectCount ; i++)
	{
		if(0 == strcmp((char*)m_pObjectDescArray[i].m_szName,szObjDesc))
		{
			return	&m_pObjectDescArray[i];
		}
	}
	return NULL;
}