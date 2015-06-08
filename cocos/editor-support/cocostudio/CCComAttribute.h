/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_EXTENTIONS_CCCOMATTRIBUTE_H__
#define __CC_EXTENTIONS_CCCOMATTRIBUTE_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "base/CCValue.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

 /** 
 @class @~english ComAttribute @~chinese ComAttribute
 @brief @~english custom attribute component @~chinese �Զ����������
 @details @~english set and get data by key-value in data, and support export data of cocos studio 1.x Scene Editor @~chinese ��key-value��ֵ�Է�ʽ�洢���ȡ����, ��Ͻ���cocos studio 1.x�����༭������������
 @group @~english component @~chinese ���
 */
class CC_STUDIO_DLL ComAttribute : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
public:
    /**
     * @js ctor
     */
    /**
    @brief @~english ComAttribute constructor @~chinese �Զ�������������캯��
    */
    ComAttribute(void);
    /**
     * @js NA
     * @lua NA
     */
    /**
    @brief @~english ComAttribute destructor @~chinese �Զ������������������
    */
    virtual ~ComAttribute(void);
    
public:
   /**
    @brief @~english ComAttribute object create function @~chinese �Զ������������������
    @return point of ComAttribute object
    */
    static ComAttribute* create(void);
    /**
    @brief @~english ComAttribute object initialization function @~chinese �Զ������������������
    @return @~english true  initialization successfully false failed to initialize @~chinese true ��ʼ���ɹ�������false
    */
    virtual bool init() override;
    /**
    @brief @~english de-serialization export data of scene editor in cocos studio 1.x  @~chinese �����л�cocos studio 1.x �����༭������������
    @param r @~english serialization data point @~chinese �����л�����
    @return @~english true  initialization successfully false failed to initialize @~chinese true ��ʼ���ɹ�������false
    */
    virtual bool serialize(void* r) override;

    /**
    @brief @~english set value of int type based on key of string  @~chinese ����������Ϊkey������Ϊint����ֵ
    @param key @~english property name @~chinese ��������
    @param value @~english value of int type @~chinese ����Ϊint����ֵ
    @return @~english void @~chinese ��
    */
    void setInt(const std::string& key, int value);
    /**
    @brief @~english set value of float type based on key of string  @~chinese ����������Ϊkey������Ϊfloat����ֵ
    @param key @~english property name @~chinese ��������
    @param value @~english value of float type @~chinese ����Ϊfloat����ֵ
    @return @~english void @~chinese ��
    */
    void setFloat(const std::string& key, float value);
    /**
    @brief @~english set value of bool type based on key of string  @~chinese ����������Ϊkey������Ϊbool����ֵ
    @param key @~english property name @~chinese ��������
    @param value @~english value of bool type @~chinese ����Ϊbool����ֵ
    @return @~english void @~chinese ��
    */
    void setBool(const std::string& key, bool value);
    /**
    @brief @~english set value of string type based on key of string  @~chinese ����������Ϊkey������Ϊstring����ֵ
    @param key @~english property name @~chinese ��������
    @param value @~english value of string type @~chinese ����Ϊstring����ֵ
    @return @~english void @~chinese ��
    */
    void setString(const std::string& key, const std::string& value);
    /**
    @brief @~english get value of int type based on key of string and default value @~chinese  ����������ΪΪkey������Ϊint����ֵ
    @param key @~english property name @~chinese ��������
    @param def @~english default value of int type, default is 0 @~chinese def ����Ϊint����ֵ��Ĭ��Ϊ0
    @return @~english return value of int type if key is found in ComAttribute, else return default @~chinese ����ҵ����ض�Ӧ����ֵ�����򷵻�def 
    */
    int getInt(const std::string& key, int def = 0) const;
    /**
    @brief @~english get value of float type based on key of string and default value @~chinese  ����������ΪΪkey������Ϊfloat����ֵ
    @param key @~english property name @~chinese ��������
    @param def @~english default value of float type, default is 0.0f @~chinese def ����Ϊfloat����ֵ��Ĭ��Ϊ0.0f
    @return @~english return value of float type if key is found in ComAttribute, else return default @~chinese ����ҵ����ض�Ӧ����ֵ�����򷵻�def
    */
    float getFloat(const std::string& key, float def = 0.0f) const;
    /**
    @brief @~english get value of bool type based on key of string and default value @~chinese  ����������ΪΪkey������Ϊbool����ֵ
    @param key @~english property name @~chinese ��������
    @param def @~english default value of bool type, default is false @~chinese def ����Ϊbool����ֵ��Ĭ��Ϊfalse
    @return @~english return value of bool type if key is found in ComAttribute, else return default @~chinese ����ҵ����ض�Ӧ����ֵ�����򷵻�def
    */
    bool getBool(const std::string& key, bool def = false) const;
    /**
    @brief @~english get value of string type based on key of string and default value @~chinese  ����������ΪΪkey������Ϊstring����ֵ
    @param key @~english property name @~chinese ��������
    @param def @~english default value of string type, default is "" @~chinese def ����Ϊstring����ֵ��Ĭ��Ϊ""
    @return @~english return value of string type if key is found in ComAttribute, else return default @~chinese ����ҵ����ض�Ӧ����ֵ�����򷵻�def
    */
    std::string getString(const std::string& key, const std::string& def = "") const;
    
    /**
    @brief @~english parse json export data of scene editor in cocos studio 1.x, judge the validity of the json and assigned to _doc @~chinese ����cocos studio 1.x�����༭��������json���ݣ��ж�json����Ч�ԣ���_doc��ֵ
    @param jsonFile @~english json file path @~chinese cocos studio 1.x�����༭��������json·��
    @return @~english true parse json successfully false failed to parse @~chinese true ����json�ɹ�������false
    */
    bool parse(const std::string &jsonFile);
private:
   cocos2d::ValueMap _dict;
   rapidjson::Document _doc;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
