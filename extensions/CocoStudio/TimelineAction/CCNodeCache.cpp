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

using namespace cocos2d;
using namespace cocos2d::extension;

namespace cocostudio {
namespace animation {


static const char* NodeType_Node     = "Node";
static const char* NodeType_Sprite   = "Sprite";
static const char* NodeType_Particle = "Particle";


static const char* NODE        = "node";
static const char* CHILDREN    = "children";
static const char* NODETYPE    = "nodeType";
static const char* FILE_PATH   = "filePath";
static const char* ACTION_TAG  = "actionTag";

static const char* X                = "x";
static const char* Y                = "y";
static const char* SCALE_X          = "scalex";
static const char* SCALE_Y          = "scaley";
static const char* SKEW_X           = "skewx";
static const char* SKEW_Y           = "skewy";
static const char* ROTATION         = "rotation";
static const char* ROTATION_SKEW_X  = "rotationSkewX";
static const char* ROTATION_SKEW_Y  = "rotationSkewY";
static const char* ANCHOR_X         = "anchorx";
static const char* ANCHOR_Y         = "anchory";
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

CCNode* NodeCreateCallFunc::excute(const rapidjson::Value& json)
{
    return (_target->*_callback)(json);
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

    
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadSimpleNode)), NodeType_Node);
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadSprite)),     NodeType_Sprite);
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeCache::loadParticle)),   NodeType_Particle);
}

cocos2d::CCNode* NodeCache::createNode(const std::string& filename)
{
    cocos2d::CCNode* node = static_cast<cocos2d::CCNode*>(_nodes->objectForKey(filename.c_str()));
    if (node == NULL)
    {
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

cocos2d::CCNode* NodeCache::loadNode(const rapidjson::Value& json)
{
    cocos2d::CCNode* node = NULL;

    std::string nodeType = DICTOOL->getStringValue_json(json, NODETYPE);

    NodeCreateCallFunc* func = static_cast<NodeCreateCallFunc*>(_funcs->objectForKey(nodeType));
    if (func != NULL)
    {
        node = func->excute(json);
    }

    int tag = DICTOOL->getIntValue_json(json, ACTION_TAG);
    node->setTag(tag);

    int length = DICTOOL->getArrayCount_json(json, CHILDREN, 0);
    for (int i = 0; i<length; i++)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, CHILDREN, i);
        cocos2d::CCNode* child = loadNode(dic);
        node->addChild(child);
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

}


CCNode* NodeCache::loadSimpleNode(const rapidjson::Value& json)
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

CCNode* NodeCache::loadSprite(const rapidjson::Value& json)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);

    CCSprite *sprite = NULL;
    CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filePath);
    if(!spriteFrame)
    {
        sprite = CCSprite::create(filePath);
    }
    else
    {
        sprite = CCSprite::createWithSpriteFrame(spriteFrame);
    }

    if(!sprite)
        CCLOG("create sprite with file name : %s  failed.", filePath);

    initNode(sprite, json);

    return sprite;
}

CCNode* NodeCache::loadParticle(const rapidjson::Value& json)
{
    return NULL;
}

}
}