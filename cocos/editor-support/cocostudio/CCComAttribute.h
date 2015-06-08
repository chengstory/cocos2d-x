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
 @brief @~english custom attribute component @~chinese 自定义属性组件
 @details @~english set and get data by key-value in data, and support export data of cocos studio 1.x Scene Editor @~chinese 以key-value键值对方式存储与获取数据, 配合解析cocos studio 1.x场景编辑器导出的数据
 @group @~english component @~chinese 组件
 */
class CC_STUDIO_DLL ComAttribute : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
public:
    /**
     * @js ctor
     */
    /**
    @brief @~english ComAttribute constructor @~chinese 自定义属性组件构造函数
    */
    ComAttribute(void);
    /**
     * @js NA
     * @lua NA
     */
    /**
    @brief @~english ComAttribute destructor @~chinese 自定义属性组件析构函数
    */
    virtual ~ComAttribute(void);
    
public:
   /**
    @brief @~english ComAttribute object create function @~chinese 自定义属性组件创建方法
    @return point of ComAttribute object
    */
    static ComAttribute* create(void);
    /**
    @brief @~english ComAttribute object initialization function @~chinese 自定义属性组件创建方法
    @return @~english true  initialization successfully false failed to initialize @~chinese true 初始化成功，否则false
    */
    virtual bool init() override;
    /**
    @brief @~english de-serialization export data of scene editor in cocos studio 1.x  @~chinese 反序列化cocos studio 1.x 场景编辑器导出的数据
    @param r @~english serialization data point @~chinese 反序列化数据
    @return @~english true  initialization successfully false failed to initialize @~chinese true 初始化成功，否则false
    */
    virtual bool serialize(void* r) override;

    /**
    @brief @~english set value of int type based on key of string  @~chinese 设置属性名为key，类型为int的数值
    @param key @~english property name @~chinese 属性名称
    @param value @~english value of int type @~chinese 类型为int的数值
    @return @~english void @~chinese 无
    */
    void setInt(const std::string& key, int value);
    /**
    @brief @~english set value of float type based on key of string  @~chinese 设置属性名为key，类型为float的数值
    @param key @~english property name @~chinese 属性名称
    @param value @~english value of float type @~chinese 类型为float的数值
    @return @~english void @~chinese 无
    */
    void setFloat(const std::string& key, float value);
    /**
    @brief @~english set value of bool type based on key of string  @~chinese 设置属性名为key，类型为bool的数值
    @param key @~english property name @~chinese 属性名称
    @param value @~english value of bool type @~chinese 类型为bool的数值
    @return @~english void @~chinese 无
    */
    void setBool(const std::string& key, bool value);
    /**
    @brief @~english set value of string type based on key of string  @~chinese 设置属性名为key，类型为string的数值
    @param key @~english property name @~chinese 属性名称
    @param value @~english value of string type @~chinese 类型为string的数值
    @return @~english void @~chinese 无
    */
    void setString(const std::string& key, const std::string& value);
    /**
    @brief @~english get value of int type based on key of string and default value @~chinese  返回属性名为为key，类型为int的数值
    @param key @~english property name @~chinese 属性名称
    @param def @~english default value of int type, default is 0 @~chinese def 类型为int的数值，默认为0
    @return @~english return value of int type if key is found in ComAttribute, else return default @~chinese 如果找到返回对应的数值，否则返回def 
    */
    int getInt(const std::string& key, int def = 0) const;
    /**
    @brief @~english get value of float type based on key of string and default value @~chinese  返回属性名为为key，类型为float的数值
    @param key @~english property name @~chinese 属性名称
    @param def @~english default value of float type, default is 0.0f @~chinese def 类型为float的数值，默认为0.0f
    @return @~english return value of float type if key is found in ComAttribute, else return default @~chinese 如果找到返回对应的数值，否则返回def
    */
    float getFloat(const std::string& key, float def = 0.0f) const;
    /**
    @brief @~english get value of bool type based on key of string and default value @~chinese  返回属性名为为key，类型为bool的数值
    @param key @~english property name @~chinese 属性名称
    @param def @~english default value of bool type, default is false @~chinese def 类型为bool的数值，默认为false
    @return @~english return value of bool type if key is found in ComAttribute, else return default @~chinese 如果找到返回对应的数值，否则返回def
    */
    bool getBool(const std::string& key, bool def = false) const;
    /**
    @brief @~english get value of string type based on key of string and default value @~chinese  返回属性名为为key，类型为string的数值
    @param key @~english property name @~chinese 属性名称
    @param def @~english default value of string type, default is "" @~chinese def 类型为string的数值，默认为""
    @return @~english return value of string type if key is found in ComAttribute, else return default @~chinese 如果找到返回对应的数值，否则返回def
    */
    std::string getString(const std::string& key, const std::string& def = "") const;
    
    /**
    @brief @~english parse json export data of scene editor in cocos studio 1.x, judge the validity of the json and assigned to _doc @~chinese 解析cocos studio 1.x场景编辑器导出的json数据，判断json的有效性，给_doc赋值
    @param jsonFile @~english json file path @~chinese cocos studio 1.x场景编辑器导出的json路径
    @return @~english true parse json successfully false failed to parse @~chinese true 解析json成功，否则false
    */
    bool parse(const std::string &jsonFile);
private:
   cocos2d::ValueMap _dict;
   rapidjson::Document _doc;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
