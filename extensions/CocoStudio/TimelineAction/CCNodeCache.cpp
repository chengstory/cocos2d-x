/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCNodeCache.h"
#include "CCTimelineActionCache.h"
#include "CCFrame.h"
#include "../Reader/GUIReader.h"
#include "../GUI/BaseClasses/UIWidget.h"

using namespace cocos2d;
using namespace cocos2d::extension;

namespace cocostudio {
namespace animation {


static const char* ClassName_Node     = "Node";
static const char* ClassName_Sprite   = "Sprite";
static const char* ClassName_Particle = "Particle";

static const char* ClassName_Button     = "Button";
static const char* ClassName_CheckBox   = "CheckBox";
static const char* ClassName_ImageView  = "ImageView";
static const char* ClassName_LabelAtlas = "LabelAtlas";
static const char* ClassName_LabelBMFont= "LabelBMFont";
static const char* ClassName_Text       = "Text";
static const char* ClassName_LoadingBar = "LoadingBar";
static const char* ClassName_TextField  = "TextField";
static const char* ClassName_Slider     = "Slider";
static const char* ClassName_Layout     = "Layout";
static const char* ClassName_ScrollView = "ScrollView";
static const char* ClassName_ListView   = "ListView";
static const char* ClassName_PageView   = "PageView";
static const char* ClassName_Widget     = "Widget";
static const char* ClassName_Panel      = "Panel";
static const char* ClassName_Label      = "Label";



static const char* NODE        = "nodeTree";
static const char* CHILDREN    = "children";
static const char* NODETYPE    = "classname";
static const char* FILE_PATH   = "fileName";
static const char* PLIST_FILE  = "plistFile";
static const char* ACTION_TAG  = "actionTag";

static const char* OPTIONS     = "options";

static const char* X                = "x";
static const char* Y                = "y";
static const char* SCALE_X          = "scaleX";
static const char* SCALE_Y          = "scaleY";
static const char* SKEW_X           = "skewX";
static const char* SKEW_Y           = "skewY";
static const char* ROTATION         = "rotation";
static const char* ROTATION_SKEW_X  = "rotationSkewX";
static const char* ROTATION_SKEW_Y  = "rotationSkewY";
static const char* ANCHOR_X         = "anchorPointX";
static const char* ANCHOR_Y         = "anchorPointY";
static const char* ALPHA            = "alpha";
static const char* RED              = "red";
static const char* GREEN            = "green";
static const char* BLUE             = "blue";



// NodeCreateCallFunc
NodeCreateCallFunc* NodeCreateCallFunc::create(CCObject* target, NodeCreateCallback callback)
{
    NodeCreateCallFunc* func = new NodeCreateCallFunc();
    if (func && func->init(target, callback))
    {
        func->autorelease();
        return func;
    }
    CC_SAFE_DELETE(func);
    return NULL;
}

NodeCreateCallFunc::NodeCreateCallFunc()
    : _target(NULL)
    , _callback(NULL)
{
}

NodeCreateCallFunc::~NodeCreateCallFunc()
{
    CC_SAFE_RELEASE_NULL(_target);
}

bool NodeCreateCallFunc::init(CCObject* target, NodeCreateCallback callback)
{
    if(target == NULL)
        return false;

    _target = target;
    _target->retain();
    _callback = callback;

    return true;
}

CCNode* NodeCreateCallFunc::excute(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    return (_target->*_callback)(json, parent);
}



// NodeCache

static NodeCache* _sharedNodeCache = NULL;

NodeCache* NodeCache::getInstance()
{
    if (! _sharedNodeCache)
    {
        _sharedNodeCache = new NodeCache();
        _sharedNodeCache->init();
    }

    return _sharedNodeCache;
}

void NodeCache::destroyInstance()
{
    CC_SAFE_DELETE(_sharedNodeCache);
}

NodeCache::NodeCache()
    : _recordJsonPath(true)
{
}

NodeCache::~NodeCache()
{
    CC_SAFE_DELETE(_funcs);
    CC_SAFE_DELETE(_nodes);
}

void NodeCache::purge()
{
    _nodes->removeAllObjects();
}

void NodeCache::init()
{
    _funcs = new cocos2d::CCDictionary();
    _nodes = new cocos2d::CCDictionary();

    
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadSimpleNode)), ClassName_Node);
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadSprite)),     ClassName_Sprite);
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadParticle)),   ClassName_Particle);


	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_Button);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_CheckBox);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_ImageView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_LabelAtlas);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_LabelBMFont);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_Text);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_LoadingBar);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_Slider);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_Layout);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_ScrollView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_ListView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_PageView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_Widget);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_Panel);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_Label);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadWidget)),   ClassName_TextField);
	

	_guiReader = new WidgetPropertiesReader0300();
}

cocos2d::CCNode* NodeCache::createNode(const std::string& filename)
{
    cocos2d::CCNode* node = static_cast<cocos2d::CCNode*>(_nodes->objectForKey(filename.c_str()));
    if (node == NULL)
    {
        if(_recordJsonPath)
        {
            std::string jsonPath = filename.substr(0, filename.find_last_of('/') + 1);
            cocos2d::extension::GUIReader::shareReader()->setFilePath(jsonPath);
        }
        
        node = loadNodeWithFile(filename);

//         if(cache)
//             _nodes.insert(filename, node);
    }

    return node;
}

cocos2d::CCNode* NodeCache::loadNodeWithFile(const std::string& fileName)
{
    // Read content from file
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
    unsigned long size;
    const char* data = (const char*)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size);
    std::string contentStr(data, size);

    // Load animation data from file
    TimelineActionCache::getInstance()->loadAnimationActionWithContent(fileName, contentStr);

    return loadNodeWithContent(contentStr);
}

cocos2d::CCNode* NodeCache::loadNodeWithContent(const std::string& content)
{
    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());
    if (doc.HasParseError()) {
        CCLOG("GetParseError %s\n", doc.GetParseError());
    }
    
    const rapidjson::Value& subJson = DICTOOL->getSubDictionary_json(doc, NODE);
    return loadNode(subJson);
}

cocos2d::CCNode* NodeCache::loadNode(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    cocos2d::CCNode* node = NULL;

    std::string nodeType = DICTOOL->getStringValue_json(json, NODETYPE);

    NodeCreateCallFunc* func = static_cast<NodeCreateCallFunc*>(_funcs->objectForKey(nodeType));
    if (func != NULL)
    {
        if (isUiWidget(nodeType))
        {
            node = func->excute(json, parent);
        }
        else
        {
            const rapidjson::Value& options = DICTOOL->getSubDictionary_json(json, OPTIONS);
            node = func->excute(options, parent);
        }
    }

    if (node)
    {
        cocos2d::ui::Widget* widget = dynamic_cast<cocos2d::ui::Widget*>(node);
        if (widget)
        {
            cocos2d::ui::TouchGroup* group = cocos2d::ui::TouchGroup::create();
            group->addWidget(widget);
            parent->addChild(group);
        }
        else
        {
            int length = DICTOOL->getArrayCount_json(json, CHILDREN, 0);
            for (int i = 0; i < length; i++)
            {
                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, CHILDREN, i);
                cocos2d::CCNode* child = loadNode(dic, node);
                if (child && child->getParent() == NULL)
                {
                    node->addChild(child);
                }
            }
        }
    }
    else
    {
        CCLOG("Not supported NodeType: %s", nodeType.c_str());
    }

    return node;
}

void NodeCache::initNode(cocos2d::CCNode* node, const rapidjson::Value& json)
{
    float x             = DICTOOL->getFloatValue_json(json, X);
    float y             = DICTOOL->getFloatValue_json(json, Y);
    float scalex        = DICTOOL->getFloatValue_json(json, SCALE_X, 1);
    float scaley        = DICTOOL->getFloatValue_json(json, SCALE_Y, 1);
    float rotation      = DICTOOL->getFloatValue_json(json, ROTATION);
    float rotationSkewX = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_X);
    float rotationSkewY = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_X);
    float skewx         = DICTOOL->getFloatValue_json(json, SKEW_X);
    float skewy         = DICTOOL->getFloatValue_json(json, SKEW_Y);
    float anchorx       = DICTOOL->getFloatValue_json(json, ANCHOR_X, 0.5f);
    float anchory       = DICTOOL->getFloatValue_json(json, ANCHOR_Y, 0.5f);
    GLubyte alpha       = (GLubyte)DICTOOL->getIntValue_json(json, ALPHA, 255);
    GLubyte red         = (GLubyte)DICTOOL->getIntValue_json(json, RED, 255);
    GLubyte green       = (GLubyte)DICTOOL->getIntValue_json(json, GREEN, 255);
    GLubyte blue        = (GLubyte)DICTOOL->getIntValue_json(json, BLUE, 255);
	int tag				= DICTOOL->getIntValue_json(json, ACTION_TAG);

    if(x != 0 || y != 0)
        node->setPosition(CCPoint(x, y));
    if(scalex != 1)
        node->setScaleX(scalex);
    if(scaley != 1)
        node->setScaleY(scaley);
    if (rotation != 0)
        node->setRotation(rotation);
    if(rotationSkewX != 0)
        node->setRotationX(rotationSkewX);
    if(rotationSkewY != 0)
        node->setRotationY(rotationSkewY);
    if(skewx != 0)
        node->setSkewX(skewx);
    if(skewy != 0)
        node->setSkewY(skewy);
    if(anchorx != 0.5f || anchory != 0.5f)
        node->setAnchorPoint(CCPoint(anchorx, anchory));

    CCRGBAProtocol *rgbaProtocaol = dynamic_cast<CCRGBAProtocol *>(node);
    if(rgbaProtocaol)
    {
        if(alpha != 255)
            rgbaProtocaol->setOpacity(alpha); rgbaProtocaol->setCascadeOpacityEnabled(true);
        if(red != 255 || green != 255 || blue != 255)
            rgbaProtocaol->setColor(ccc3(red, green, blue));
    }

	node->setTag(tag);
}


CCNode* NodeCache::loadSimpleNode(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);

    CCNode* node = NULL;
    if(filePath)
    {
        node = createNode(filePath);
    }
    else
    {
        node = CCNodeRGBA::create();
    }

    initNode(node, json);

    return node;
}

CCNode* NodeCache::loadSprite(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);

    CCSprite *sprite = NULL;

	if(filePath != NULL)
	{
		CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filePath);
		if(!spriteFrame)
		{
			sprite = CCSprite::create(filePath);
		}
		else
		{
			sprite = CCSprite::createWithSpriteFrame(spriteFrame);
		}

		if(sprite == NULL)
			CCLOG("create sprite with file name : %s  failed.", filePath);
	}
	else
	{
		sprite = CCSprite::create();
	}

    initNode(sprite, json);

    return sprite;
}

CCNode* NodeCache::loadParticle(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
	const char* filePath = DICTOOL->getStringValue_json(json, PLIST_FILE);

	CCParticleSystemQuad* particle = CCParticleSystemQuad::create(filePath);

	initNode(particle, json);

	return particle;
}

CCNode* NodeCache::loadWidget(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    WidgetPropertiesReader* pReader = new WidgetPropertiesReader0300();
    cocos2d::ui::Widget* widget = pReader->widgetFromJsonDictionary(json);

    return widget;
}

bool NodeCache::isUiWidget(const std::string &type)
{
    return (type == ClassName_Button
        || type == ClassName_CheckBox
        || type == ClassName_ImageView
        || type == ClassName_Layout
        || type == ClassName_ListView
        || type == ClassName_LoadingBar
        || type == ClassName_PageView
        || type == ClassName_Panel
        || type == ClassName_Text
        || type == ClassName_LabelAtlas
        || type == ClassName_LabelBMFont
        || type == ClassName_TextField
        || type == ClassName_Widget);
}

}
}