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

#include "CCNodeReader.h"
#include "CCActionTimelineCache.h"
#include "CCFrame.h"
#include "../Reader/GUIReader.h"
#include "../GUI/BaseClasses/UIWidget.h"
#include "../Json/CSParseBinary.pb.h"

#include <fstream>

using namespace cocos2d;
using namespace cocos2d::extension;

NS_TIMELINE_BEGIN


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
static const char* TAG         = "tag";

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
static const char* ALPHA            = "opacity";
static const char* RED              = "colorR";
static const char* GREEN            = "colorG";
static const char* BLUE             = "colorB";
static const char* ZORDER           = "ZOrder";
static const char* FLIPX            = "flipX";
static const char* FLIPY            = "flipY";
static const char* VISIBLE          = "visible";

static const char* TEXTURES     = "textures";
static const char* TEXTURES_PNG = "texturesPng";

static const char* MONO_COCOS2D_VERSION     = "cocos2dVersion";

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



// TimelineActionData
TimelineActionData* TimelineActionData::create(int actionTag)
{
    TimelineActionData * ret = new TimelineActionData();
    if (ret && ret->init(actionTag))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

TimelineActionData::TimelineActionData()
    : _actionTag(0)
{
}

bool TimelineActionData::init(int actionTag)
{
    _actionTag = actionTag;
    return true;
}



// NodeReader

static NodeReader* _sharedNodeReader = NULL;

NodeReader* NodeReader::getInstance()
{
    if (! _sharedNodeReader)
    {
        _sharedNodeReader = new NodeReader();
        _sharedNodeReader->init();
    }

    return _sharedNodeReader;
}

void NodeReader::destroyInstance()
{
    CC_SAFE_DELETE(_sharedNodeReader);
}

NodeReader::NodeReader()
    : _recordJsonPath(true)
    , _jsonPath("")
    , _recordProtocolBuffersPath(true)
    , _protocolBuffersPath("")
    , _monoCocos2dxVersion("")
{
}

NodeReader::~NodeReader()
{
    CC_SAFE_DELETE(_funcs);
}

void NodeReader::purge()
{
}

void NodeReader::init()
{
    _funcs = new cocos2d::CCDictionary();
    
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadSimpleNode)), ClassName_Node);
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadSprite)),     ClassName_Sprite);
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadParticle)),   ClassName_Particle);


	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Button);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_CheckBox);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_ImageView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_LabelAtlas);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_LabelBMFont);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Text);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_LoadingBar);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Slider);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Layout);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_ScrollView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_ListView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_PageView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Widget);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Panel);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Label);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_TextField);
	

	_guiReader = new WidgetPropertiesReader0300();
}

cocos2d::CCNode* NodeReader::createNode(const std::string& filename)
{
    if(_recordJsonPath)
    {
        std::string jsonPath = filename.substr(0, filename.find_last_of('/') + 1);
        GUIReader::shareReader()->setFilePath(jsonPath);

        _jsonPath = jsonPath;
    }
    else
    {
        GUIReader::shareReader()->setFilePath("");
        _jsonPath = "";
    }

    cocos2d::CCNode* node = loadNodeWithFile(filename);

    return node;
}

cocos2d::CCNode* NodeReader::loadNodeWithFile(const std::string& fileName)
{
    // Read content from file
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
    unsigned long size;
    const char* data = (const char*)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size);
    std::string contentStr(data, size);

    cocos2d::CCNode* node = loadNodeWithContent(contentStr);

    // Load animation data from file
    ActionTimelineCache::getInstance()->loadAnimationActionWithContent(fileName, contentStr);

    return node;
}

cocos2d::CCNode* NodeReader::loadNodeWithContent(const std::string& content)
{
    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());
    if (doc.HasParseError()) 
    {
        CCLOG("GetParseError %s\n", doc.GetParseError());
    }
    
    // cocos2d version that mono editor is based on
    _monoCocos2dxVersion = DICTOOL->getStringValue_json(doc, MONO_COCOS2D_VERSION, "");
    
    // decode plist 
    int length = DICTOOL->getArrayCount_json(doc, TEXTURES);
    for(int i=0; i<length; i++)
    {
        std::string plist = DICTOOL->getStringValueFromArray_json(doc, TEXTURES, i);
        std::string png   = DICTOOL->getStringValueFromArray_json(doc, TEXTURES_PNG, i);
        plist = _jsonPath + plist;
        png   = _jsonPath + png;
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist.c_str(), png.c_str());
    }

    // decode node tree
    const rapidjson::Value& subJson = DICTOOL->getSubDictionary_json(doc, NODE);
    return loadNode(subJson);
}

cocos2d::CCNode* NodeReader::loadNode(const rapidjson::Value& json, cocos2d::CCNode* parent)
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
            if (!parent)
            {
                return widget;
            }
            else
            {
                cocos2d::ui::TouchGroup* group = cocos2d::ui::TouchGroup::create();
                group->setZOrder(widget->getZOrder());
                group->setTag(widget->getTag());
                group->addWidget(widget);
                parent->addChild(group);
            }
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

void NodeReader::initNode(cocos2d::CCNode* node, const rapidjson::Value& json)
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
    int zorder          = DICTOOL->getIntValue_json(json, ZORDER);
    int tag             = DICTOOL->getIntValue_json(json, TAG);
    int actionTag       = DICTOOL->getIntValue_json(json, ACTION_TAG);
    bool visible        = DICTOOL->getBooleanValue_json(json, VISIBLE);

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
    if(zorder != 0)
        node->setZOrder(zorder);
    if(visible != true)
        node->setVisible(visible);

    CCRGBAProtocol *rgbaProtocaol = dynamic_cast<CCRGBAProtocol *>(node);
    if(rgbaProtocaol)
    {
        if(alpha != 255)
        {
            rgbaProtocaol->setOpacity(alpha); 
        }
        if(red != 255 || green != 255 || blue != 255)
        {
            rgbaProtocaol->setColor(ccc3(red, green, blue));
        }
    }

    node->setTag(tag);
	node->setUserObject(TimelineActionData::create(actionTag));
}


CCNode* NodeReader::loadSimpleNode(const rapidjson::Value& json, cocos2d::CCNode* parent)
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

CCNode* NodeReader::loadSprite(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);

    CCSprite *sprite = NULL;

	if(filePath != NULL)
	{
        std::string path = filePath;
		CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path.c_str());
		if(!spriteFrame)
        {
            path = _jsonPath + path;
			sprite = CCSprite::create(path.c_str());
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

    bool flipX          = DICTOOL->getBooleanValue_json(json, FLIPX);
    bool flipY          = DICTOOL->getBooleanValue_json(json, FLIPY);

    if(flipX != false)
        sprite->setFlipX(flipX);
    if(flipY != false)
        sprite->setFlipY(flipY);

    return sprite;
}

CCNode* NodeReader::loadParticle(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
	const char* filePath = DICTOOL->getStringValue_json(json, PLIST_FILE);

	CCParticleSystemQuad* particle = CCParticleSystemQuad::create(filePath);

	initNode(particle, json);

	return particle;
}

CCNode* NodeReader::loadWidget(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    WidgetPropertiesReader* pReader = new WidgetPropertiesReader0300();
    cocos2d::ui::Widget* widget = pReader->widgetFromJsonDictionary(json);

    const rapidjson::Value& options = DICTOOL->getSubDictionary_json(json, OPTIONS);
    initNode(widget, options);
    
    CC_SAFE_DELETE(pReader);

    return widget;
}

bool NodeReader::isUiWidget(const std::string &type)
{    
    return (type == ClassName_Button
        || type == ClassName_CheckBox
        || type == ClassName_ImageView
        || type == ClassName_LabelAtlas
        || type == ClassName_LabelBMFont
        || type == ClassName_LoadingBar
        || type == ClassName_TextField
        || type == ClassName_Slider
        || type == ClassName_Layout
        || type == ClassName_ScrollView
        || type == ClassName_ListView        
        || type == ClassName_PageView
        || type == ClassName_Widget
        || type == ClassName_Panel
        || type == ClassName_Label);
}

cocos2d::CCNode* NodeReader::createNodeFromProtocolBuffers(const std::string &filename)
{
    if(_recordProtocolBuffersPath)
    {
        std::string protocolBuffersPath = filename.substr(0, filename.find_last_of('/') + 1);
        CCLog("protocolBuffersPath = %s", protocolBuffersPath.c_str());
        GUIReader::shareReader()->setFilePath(protocolBuffersPath);
        
        _protocolBuffersPath = protocolBuffersPath;
    }
    else
    {
        GUIReader::shareReader()->setFilePath("");
        _protocolBuffersPath = "";
    }
    
    cocos2d::CCNode* node = nodeFromProtocolBuffersFile(filename);
    
    return node;
}

cocos2d::CCNode* NodeReader::nodeFromProtocolBuffersFile(const std::string &fileName)
{
    std::string path = fileName;
    int pos = path.find_last_of('/');
    //	_protocolBuffersPath = path.substr(0, pos + 1);
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());

	unsigned long size = 0;
	unsigned char *content = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "rt", &size);
    protocolbuffers::CSParseBinary gpbwp;
    //    protocolbuffers::GUIProtocolBuffersProtobuf gpbwp;
	if (!gpbwp.ParseFromArray(content, size))
    {
        return NULL;
    }
	CC_SAFE_DELETE_ARRAY(content);
    /*
     CCLog("dataScale = %d", gpbwp.datascale());
     CCLog("designHeight = %d", gpbwp.designheight());
     CCLog("designWidth = %d", gpbwp.designwidth());
     CCLog("version = %s", gpbwp.version().c_str());
     */
    
    // decode plist
    int textureSize = gpbwp.textures_size();
    CCLog("textureSize = %d", textureSize);
    for (int i = 0; i < textureSize; ++i)
    {
        std::string plist = gpbwp.textures(i);
        CCLog("plist = %s", plist.c_str());
        std::string png = gpbwp.texturespng(i);
        CCLog("png = %s", png.c_str());
        plist = _protocolBuffersPath + plist;
        png = _protocolBuffersPath + png;
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist.c_str(), png.c_str());
    }
    int fileDesignWidth = gpbwp.designwidth();
    int fileDesignHeight = gpbwp.designheight();
    if (fileDesignWidth <= 0 || fileDesignHeight <= 0)
    {
        CCLog("Read design size error!\n");
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        GUIReader::shareReader()->storeFileDesignSize(fileName.c_str(), winSize);
    }
    else
    {
        GUIReader::shareReader()->storeFileDesignSize(fileName.c_str(),
                                                      CCSizeMake(fileDesignWidth, fileDesignHeight));
    }
    
    protocolbuffers::NodeTree rootNodeTree = gpbwp.nodetree();
    CCNode* node = nodeFromProtocolBuffers(rootNodeTree);
    
    return node;
}

cocos2d::CCNode* NodeReader::nodeFromProtocolBuffers(const protocolbuffers::NodeTree &nodetree)
{
    CCNode* node = NULL;
    
    std::string classname = nodetree.classname();
    CCLog("classname = %s", classname.c_str());
    
    if (classname == "Node")
    {
        node = CCNode::create();
        const protocolbuffers::WidgetOptions& options = nodetree.widgetoptions();
        setPropsForNodeFromProtocolBuffers(node, options);
    }
    else if (classname == "Sprite")
    {
        node = CCSprite::create();
        const protocolbuffers::WidgetOptions& nodeOptions = nodetree.widgetoptions();
        const protocolbuffers::SpriteOptions& options = nodetree.spriteoptions();
        setPropsForSpriteFromProtocolBuffers(node, options, nodeOptions);
    }
    else
    {
        WidgetPropertiesReader* pReader = new WidgetPropertiesReader0300();
        cocos2d::ui::Widget* widget = pReader->widgetFromProtocolBuffers(nodetree);
        cocos2d::ui::TouchGroup* group = cocos2d::ui::TouchGroup::create();
        group->setZOrder(widget->getZOrder());
        group->setTag(widget->getTag());
        group->addWidget(widget);
        node = group;
            
        CC_SAFE_DELETE(pReader);
        
        return node;
    }
    
    int size = nodetree.children_size();
    CCLog("size = %d", size);
    for (int i = 0; i < size; ++i)
    {
        protocolbuffers::NodeTree subNodeTree = nodetree.children(i);
        CCNode* child = nodeFromProtocolBuffers(subNodeTree);
        CCLog("child = %p", child);
        if (child)
        {
            node->addChild(child);
        }
    }
    
    return node;
}

void NodeReader::initNodeFromProtocolBuffers(cocos2d::CCNode *node, const protocolbuffers::WidgetOptions &nodeOptions)
{
    const protocolbuffers::WidgetOptions& options = nodeOptions;
    
    float x             = options.x();
    float y             = options.y();
    CCLog("x = %f, y = %f", x, y);
    float scalex        = options.has_scalex() ? options.scalex() : 1;
    float scaley        = options.has_scaley() ? options.scaley() : 1;
    float rotation      = options.rotation();
    float anchorx       = options.has_anchorpointx() ? options.anchorpointx() : 0.5f;
    float anchory       = options.has_anchorpointy() ? options.anchorpointy() : 0.5f;
    int zorder          = options.zorder();
    int tag             = options.tag();
    int actionTag       = options.actiontag();
    bool visible        = options.visible();
    
    if(x != 0 || y != 0)
        node->setPosition(CCPoint(x, y));
    if(scalex != 1)
        node->setScaleX(scalex);
    if(scaley != 1)
        node->setScaleY(scaley);
    if (rotation != 0)
        node->setRotation(rotation);
    if(anchorx != 0.5f || anchory != 0.5f)
        node->setAnchorPoint(CCPoint(anchorx, anchory));
    if(zorder != 0)
        node->setZOrder(zorder);
    if(visible != true)
        node->setVisible(visible);
    
    node->setTag(tag);
    if (actionTag != -1)
    {
        node->setUserObject(cocostudio::timeline::TimelineActionData::create(actionTag));
    }
}

void NodeReader::setPropsForNodeFromProtocolBuffers(cocos2d::CCNode *node,
                                                    const protocolbuffers::WidgetOptions &nodeOptions)
{
    initNodeFromProtocolBuffers(node, nodeOptions);
}

void NodeReader::setPropsForSpriteFromProtocolBuffers(cocos2d::CCNode *node,
                                                      const protocolbuffers::SpriteOptions &spriteOptions,
                                                      const protocolbuffers::WidgetOptions &nodeOptions)
{
    CCSprite* sprite = static_cast<CCSprite*>(node);
    const protocolbuffers::SpriteOptions& options = spriteOptions;
    
    std::string protocolBuffersPath = _protocolBuffersPath;
    
    if (options.has_filename())
    {
        const char* filePath = options.filename().c_str();
        
        CCLOG("filePath = %s", filePath);
        
        if (filePath && strcmp("", filePath) != 0)
        {
            std::string path = filePath;
            CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path.c_str());
            if(!spriteFrame)
            {
                path = protocolBuffersPath + path;
                sprite->initWithFile(path.c_str());
            }
            else
            {
                sprite->initWithSpriteFrame(spriteFrame);
            }
            
            if(sprite == NULL)
                CCLOG("create sprite with file name : %s  failed.", filePath);
        }
    }
    
    setPropsForNodeFromProtocolBuffers(sprite, nodeOptions);
    
    GLubyte alpha       = (GLubyte)nodeOptions.has_opacity() ? nodeOptions.opacity() : 255;
	GLubyte red         = (GLubyte)nodeOptions.has_colorr() ? nodeOptions.colorr() : 255;
	GLubyte green       = (GLubyte)nodeOptions.has_colorg() ? nodeOptions.colorg() : 255;
	GLubyte blue        = (GLubyte)nodeOptions.has_colorb() ? nodeOptions.colorb() : 255;
    
    CCRGBAProtocol *rgbaProtocaol = dynamic_cast<CCRGBAProtocol *>(sprite);
    if(rgbaProtocaol)
    {
        if(alpha != 255)
        {
            rgbaProtocaol->setOpacity(alpha);
            rgbaProtocaol->setCascadeOpacityEnabled(true);
        }
        if(red != 255 || green != 255 || blue != 255)
        {
            rgbaProtocaol->setColor(ccc3(red, green, blue));
            rgbaProtocaol->setCascadeColorEnabled(true);
        }
    }
    
    bool flipX          = nodeOptions.flipx();
    bool flipY          = nodeOptions.flipy();
    
    if(flipX != false)
        sprite->setFlipX(flipX);
    if(flipY != false)
        sprite->setFlipY(flipY);
}

NS_TIMELINE_END
