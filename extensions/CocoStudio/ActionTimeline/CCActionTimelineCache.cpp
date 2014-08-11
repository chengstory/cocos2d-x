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

#include "CCActionTimelineCache.h"
#include "CCActionTimeline.h"
#include "CCFrame.h"
#include "../Json/CSParseBinary.pb.h"

#include <fstream>

using namespace cocos2d;
using namespace cocos2d::extension;

NS_TIMELINE_BEGIN

static const char* FrameType_VisibleFrame       = "VisibleFrame";
static const char* FrameType_PositionFrame      = "PositionFrame";
static const char* FrameType_ScaleFrame         = "ScaleFrame";
static const char* FrameType_RotationFrame      = "RotationFrame";
static const char* FrameType_SkewFrame          = "SkewFrame";
static const char* FrameType_RotationSkewFrame  = "RotationSkewFrame";
static const char* FrameType_AnchorFrame        = "AnchorFrame";
static const char* FrameType_InnerActionFrame   = "InnerActionFrame";
static const char* FrameType_ColorFrame         = "ColorFrame";
static const char* FrameType_TextureFrame       = "TextureFrame";
static const char* FrameType_EventFrame         = "EventFrame";
static const char* FrameType_ZOrderFrame        = "ZOrderFrame";



static const char* ACTION           = "action";
static const char* NAME             = "name";
static const char* DURATION         = "duration";
static const char* NODES            = "nodes";
static const char* TIMELINES        = "timelines";
static const char* FRAME_TYPE       = "frameType";
static const char* FRAMES           = "frames";
static const char* FRAME_INDEX      = "frameIndex";
static const char* VISIBLE          = "visible";
static const char* TWEEN            = "tween";
static const char* TIME_SPEED       = "speed";
static const char* ACTION_TAG       = "actionTag";
static const char* INNER_ACTION     = "innerActionType";
static const char* START_FRAME      = "startFrame";

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
static const char* Value            = "value";



// FrameCreateCallFunc
FrameCreateCallFunc* FrameCreateCallFunc::create(CCObject* target, FrameCreateCallback callback)
{
    FrameCreateCallFunc* func = new FrameCreateCallFunc();
    if (func && func->init(target, callback))
    {
        func->autorelease();
        return func;
    }
    CC_SAFE_DELETE(func);
    return NULL;
}

FrameCreateCallFunc::FrameCreateCallFunc()
    : _target(NULL)
    , _callback(NULL)
{
}

FrameCreateCallFunc::~FrameCreateCallFunc()
{
    CC_SAFE_RELEASE_NULL(_target);
}

bool FrameCreateCallFunc::init(CCObject* target, FrameCreateCallback callback)
{
    if(target == NULL)
        return false;

    _target = target;
    _target->retain();
    _callback = callback;

    return true;
}

Frame* FrameCreateCallFunc::excute(const rapidjson::Value& json)
{
    return (_target->*_callback)(json);
}



// ActionTimelineCache

static ActionTimelineCache* _sharedActionCache = NULL;

ActionTimelineCache* ActionTimelineCache::getInstance()
{
    if (! _sharedActionCache)
    {
        _sharedActionCache = new ActionTimelineCache();
        _sharedActionCache->init();
    }

    return _sharedActionCache;
}

void ActionTimelineCache::destroyInstance()
{
    CC_SAFE_DELETE(_sharedActionCache);
}

ActionTimelineCache::~ActionTimelineCache()
{
    CC_SAFE_DELETE(_funcs);
    CC_SAFE_DELETE(_timelineActions);
}

void ActionTimelineCache::purge()
{
    _timelineActions->removeAllObjects();
}

void ActionTimelineCache::init()
{
    _funcs = new cocos2d::CCDictionary();
    _timelineActions = new cocos2d::CCDictionary();

    
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadVisibleFrame)),     FrameType_VisibleFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadPositionFrame)),    FrameType_PositionFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadScaleFrame)),       FrameType_ScaleFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadRotationFrame)),    FrameType_RotationFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadSkewFrame)),        FrameType_SkewFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadRotationSkewFrame)),FrameType_RotationSkewFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadAnchorPointFrame)), FrameType_AnchorFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadInnerActionFrame)), FrameType_InnerActionFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadColorFrame)),       FrameType_ColorFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadTextureFrame)),     FrameType_TextureFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadEventFrame)),       FrameType_EventFrame);
    _funcs->setObject(FrameCreateCallFunc::create(this, FrameCreateCallback_selector(ActionTimelineCache::loadZOrderFrame)),      FrameType_ZOrderFrame);

}

void ActionTimelineCache::removeAction(const std::string& fileName)
{
    _timelineActions->removeObjectForKey(fileName);
}

ActionTimeline* ActionTimelineCache::createAction(const std::string& fileName)
{
    ActionTimeline* action = static_cast<ActionTimeline*>(_timelineActions->objectForKey(fileName));
    if (action == NULL)
    {
        action = loadAnimationActionWithFile(fileName);
    }
    return action->clone();
}

ActionTimeline* ActionTimelineCache::loadAnimationActionWithFile(const std::string& fileName)
{
    // Read content from file
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
    unsigned long size = 0;
    std::string contentStr((const char*)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size), size);

    return loadAnimationActionWithContent(fileName, contentStr);
}

ActionTimeline* ActionTimelineCache::loadAnimationActionWithContent(const std::string&fileName, const std::string& content)
{
    // if already exists an action with filename, then return this action
    ActionTimeline* action = static_cast<ActionTimeline*>(_timelineActions->objectForKey(fileName));
    if(action)
        return action;

    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());
    if (doc.HasParseError()) 
    {
        CCLOG("GetParseError %s\n", doc.GetParseError());
    }

    const rapidjson::Value& json = DICTOOL->getSubDictionary_json(doc, ACTION);

    action = ActionTimeline::create();

    action->setDuration(DICTOOL->getIntValue_json(json, DURATION));
    action->setTimeSpeed(DICTOOL->getFloatValue_json(json, TIME_SPEED, 1.0f));

    int timelineLength = DICTOOL->getArrayCount_json(json, TIMELINES);
    for (int i = 0; i<timelineLength; i++)
    {
        const rapidjson::Value& dic = DICTOOL->getSubDictionary_json(json, TIMELINES, i);
        Timeline* timeline = loadTimeline(dic);

        if(timeline)
            action->addTimeline(timeline);
    }

    _timelineActions->setObject(action, fileName);

    return action;
}

ActionTimeline* ActionTimelineCache::createActionFromProtocolBuffers(const std::string &fileName)
{
    ActionTimeline* action = static_cast<ActionTimeline*>(_timelineActions->objectForKey(fileName));
    if (action == NULL)
    {
        action = loadAnimationActionWithFileFromProtocolBuffers(fileName);
    }
    return action->clone();
}

ActionTimeline* ActionTimelineCache::loadAnimationActionWithFileFromProtocolBuffers(const std::string &fileName)
{
    // if already exists an action with filename, then return this action
    ActionTimeline* action = static_cast<ActionTimeline*>(_timelineActions->objectForKey(fileName));
    if (action)
        return action;
    
    std::string path = fileName;
    int pos = path.find_last_of('/');
    //	_protocolBuffersPath = path.substr(0, pos + 1);
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
    std::fstream in(fullPath.c_str(), std::ios::in | std::ios::binary);
    protocolbuffers::CSParseBinary gpbwp;
    //    protocolbuffers::GUIProtocolBuffersProtobuf gpbwp;
    if (!gpbwp.ParseFromIstream(&in))
    {
        return NULL;
    }
    in.close();
    
    
    const protocolbuffers::NodeAction& actionProtobuf = gpbwp.action();
    
    action = ActionTimeline::create();
    
    action->setDuration(actionProtobuf.duration());
    action->setTimeSpeed((actionProtobuf.has_speed()) ? actionProtobuf.speed() : 1.0f);
    
    int timelineLength = actionProtobuf.timelines_size();
    for (int i = 0; i < timelineLength; i++)
    {
        const protocolbuffers::TimeLine& timelineProtobuf = actionProtobuf.timelines(i);
        Timeline* timeline = loadTimelineFromProtocolBuffers(timelineProtobuf);
        
        if (timeline)
            action->addTimeline(timeline);
    }
    
    _timelineActions->setObject(action, fileName);
    
    return action;
}


Timeline* ActionTimelineCache::loadTimeline(const rapidjson::Value& json)
{
    Timeline* timeline = NULL;

    // get frame type 
    const char* frameType = DICTOOL->getStringValue_json(json, FRAME_TYPE);
	if(frameType == NULL)
		return NULL;

    FrameCreateCallFunc* func = static_cast<FrameCreateCallFunc*>(_funcs->objectForKey(frameType));

    if(frameType && func)
    {
        timeline = Timeline::create();

        int actionTag = DICTOOL->getIntValue_json(json, ACTION_TAG);
        timeline->setActionTag(actionTag);


        int length = DICTOOL->getArrayCount_json(json, FRAMES);
        for (int i = 0; i<length; i++)
        {
            const rapidjson::Value& dic = DICTOOL->getSubDictionary_json(json, FRAMES, i);

            Frame* frame = NULL;
            frame = func->excute(dic);

            int frameIndex = DICTOOL->getIntValue_json(dic, FRAME_INDEX);
            frame->setFrameIndex(frameIndex);

            bool tween = DICTOOL->getBooleanValue_json(dic, TWEEN, false);
            frame->setTween(tween);

            timeline->addFrame(frame);
        }
    }

    return timeline;
}

Frame* ActionTimelineCache::loadVisibleFrame(const rapidjson::Value& json)
{
    VisibleFrame* frame = VisibleFrame::create();

    bool visible = DICTOOL->getBooleanValue_json(json, Value);
    frame->setVisible(visible);

    return frame;
}

Frame* ActionTimelineCache::loadPositionFrame(const rapidjson::Value& json)
{
    PositionFrame* frame = PositionFrame::create();

    float x = DICTOOL->getFloatValue_json(json, X);
    float y = DICTOOL->getFloatValue_json(json, Y);
    frame->setPosition(CCPoint(x,y));

    return frame;
}

Frame* ActionTimelineCache::loadScaleFrame(const rapidjson::Value& json)
{
   ScaleFrame* frame = ScaleFrame::create();

   float scalex = DICTOOL->getFloatValue_json(json, X);
   float scaley = DICTOOL->getFloatValue_json(json, Y);

   frame->setScaleX(scalex);
   frame->setScaleY(scaley);

    return frame;
}

Frame* ActionTimelineCache::loadSkewFrame(const rapidjson::Value& json)
{
    SkewFrame* frame = SkewFrame::create();

    float skewx = DICTOOL->getFloatValue_json(json, X);
    float skewy = DICTOOL->getFloatValue_json(json, Y);

    frame->setSkewX(skewx);
    frame->setSkewY(skewy);

    return frame;
}

Frame* ActionTimelineCache::loadRotationSkewFrame(const rapidjson::Value& json)
{
    RotationSkewFrame* frame = RotationSkewFrame::create();

    float skewx = DICTOOL->getFloatValue_json(json, X);
    float skewy = DICTOOL->getFloatValue_json(json, Y);

    frame->setSkewX(skewx);
    frame->setSkewY(skewy);

    return frame;
}

Frame* ActionTimelineCache::loadRotationFrame(const rapidjson::Value& json)
{
    RotationFrame* frame = RotationFrame::create();

    float rotation = DICTOOL->getFloatValue_json(json, ROTATION);
    frame->setRotation(rotation);

    return frame;
}

Frame* ActionTimelineCache::loadAnchorPointFrame (const rapidjson::Value& json)
{
    AnchorPointFrame* frame = AnchorPointFrame::create();

    float anchorx = DICTOOL->getFloatValue_json(json, X);
    float anchory = DICTOOL->getFloatValue_json(json, Y);

    frame->setAnchorPoint(CCPoint(anchorx, anchory));

    return frame;
}

Frame* ActionTimelineCache::loadInnerActionFrame(const rapidjson::Value& json)
{
    InnerActionFrame* frame = InnerActionFrame::create();

    InnerActionType type = (InnerActionType)DICTOOL->getIntValue_json(json, INNER_ACTION);
    int startFrame       = DICTOOL->getIntValue_json(json, START_FRAME); 

    frame->setInnerActionType(type);
    frame->setStartFrameIndex(startFrame);

    return frame;
}

Frame* ActionTimelineCache::loadColorFrame(const rapidjson::Value& json)
{
    ColorFrame* frame = ColorFrame::create();

    GLubyte alpha = (GLubyte)DICTOOL->getIntValue_json(json, ALPHA);
    GLubyte red   = (GLubyte)DICTOOL->getIntValue_json(json, RED);
    GLubyte green = (GLubyte)DICTOOL->getIntValue_json(json, GREEN);
    GLubyte blue  = (GLubyte)DICTOOL->getIntValue_json(json, BLUE);

    frame->setAlpha(alpha);
    frame->setColor(ccc3(red, green, blue));

    return frame;
}


Frame* ActionTimelineCache::loadTextureFrame(const rapidjson::Value& json)
{
    TextureFrame* frame = TextureFrame::create();

    const char* texture = DICTOOL->getStringValue_json(json, Value);

    if(texture != NULL)
        frame->setTextureName(texture);

    return frame;
}

Frame* ActionTimelineCache::loadEventFrame(const rapidjson::Value& json)
{
    EventFrame* frame = EventFrame::create();

    const char* evnt = DICTOOL->getStringValue_json(json, Value);

    if(evnt != NULL)
        frame->setEvent(evnt);

    return frame;
}

Frame* ActionTimelineCache::loadZOrderFrame(const rapidjson::Value& json)
{
    ZOrderFrame* frame = ZOrderFrame::create();

    int zorder = DICTOOL->getIntValue_json(json, Value);
    frame->setZOrder(zorder);

    return frame;
}


Timeline*  ActionTimelineCache::loadTimelineFromProtocolBuffers(const protocolbuffers::TimeLine &timelineProtobuf)
{
    Timeline* timeline = NULL;
    
    // get frame type
    const char* frameType = timelineProtobuf.frametype().c_str();
    if(frameType == NULL)
        return NULL;
    
    CCLOG("frameType = %s", frameType);
    
    if(frameType)
    {
        timeline = Timeline::create();
        
        int actionTag = timelineProtobuf.actiontag();
        timeline->setActionTag(actionTag);
        
        
        int length = timelineProtobuf.frames_size();
        for (int i = 0; i < length; i++)
        {
			const protocolbuffers::Frame& frameProtobuf = timelineProtobuf.frames(i);
            
            Frame* frame = NULL;
            
            if (strcmp(FrameType_VisibleFrame, frameType) == 0)
            {
                const protocolbuffers::TimeLineBoolFrame& visibleFrame = frameProtobuf.visibleframe();
                frame = loadVisibleFrameFromProtocolBuffers(visibleFrame);
            }
            else if (strcmp(FrameType_PositionFrame, frameType) == 0)
            {
                const protocolbuffers::TimeLinePointFrame& positionFrame = frameProtobuf.positionframe();
                frame = loadPositionFrameFromProtocolBuffers(positionFrame);
            }
            else if (strcmp(FrameType_ScaleFrame, frameType) == 0)
            {
                const protocolbuffers::TimeLinePointFrame& scaleFrame = frameProtobuf.scaleframe();
                frame = loadScaleFrameFromProtocolBuffers(scaleFrame);
            }
			else if (strcmp(FrameType_RotationSkewFrame, frameType) == 0)
            {
                const protocolbuffers::TimeLinePointFrame& rotationSkewFrame = frameProtobuf.rotationskewframe();
                frame = loadRotationSkewFrameFromProtocolBuffers(rotationSkewFrame);
            }
            else if (strcmp(FrameType_AnchorFrame, frameType) == 0)
            {
                const protocolbuffers::TimeLinePointFrame& anchorFrame = frameProtobuf.anchorpointframe();
                frame = loadAnchorPointFrameFromProtocolBuffers(anchorFrame);
            }
            else if (strcmp(FrameType_ColorFrame, frameType) == 0)
            {
                const protocolbuffers::TimeLineColorFrame& colorFrame = frameProtobuf.colorframe();
                frame = loadColorFrameFromProtocolBuffers(colorFrame);
            }
            else if (strcmp(FrameType_TextureFrame, frameType) == 0)
            {
                const protocolbuffers::TimeLineTextureFrame& textureFrame = frameProtobuf.textureframe();
                frame = loadTextureFrameFromProtocolBuffers(textureFrame);
            }
            else if (strcmp(FrameType_EventFrame, frameType) == 0)
            {
                const protocolbuffers::TimeLineStringFrame& eventFrame = frameProtobuf.eventframe();
                frame = loadEventFrameFromProtocolBuffers(eventFrame);
            }
            else if (strcmp(FrameType_ZOrderFrame, frameType) == 0)
            {
                const protocolbuffers::TimeLineIntFrame& zOrderFrame = frameProtobuf.zorderframe();
                frame = loadZOrderFrameFromProtocolBuffers(zOrderFrame);
            }
            
            timeline->addFrame(frame);
        }
    }
    
    return timeline;
}

Frame* ActionTimelineCache::loadVisibleFrameFromProtocolBuffers(const protocolbuffers::TimeLineBoolFrame &frameProtobuf)
{
    VisibleFrame* frame = VisibleFrame::create();
    
    bool visible = frameProtobuf.value();
    frame->setVisible(visible);
    
    CCLOG("visible = %d", visible);
    
	int frameIndex = frameProtobuf.has_frameindex() ? frameProtobuf.frameindex() : 0;
    frame->setFrameIndex(frameIndex);
    
    bool tween = (frameProtobuf.has_tween() ? frameProtobuf.tween() : false);
    frame->setTween(tween);
    
    return frame;
}

Frame* ActionTimelineCache::loadPositionFrameFromProtocolBuffers(const protocolbuffers::TimeLinePointFrame &frameProtobuf)
{
    PositionFrame* frame = PositionFrame::create();
    
    float x = frameProtobuf.x();
    float y = frameProtobuf.y();
    frame->setPosition(ccp(x,y));
    
    CCLOG("x = %f", x);
    CCLOG("y = %f", y);
    
	int frameIndex = frameProtobuf.has_frameindex() ? frameProtobuf.frameindex() : 0;
    frame->setFrameIndex(frameIndex);
    
    bool tween = (frameProtobuf.has_tween() ? frameProtobuf.tween() : false);
    frame->setTween(tween);
    
    return frame;
}

Frame* ActionTimelineCache::loadScaleFrameFromProtocolBuffers(const protocolbuffers::TimeLinePointFrame &frameProtobuf)
{
    ScaleFrame* frame = ScaleFrame::create();
    
    float scalex = frameProtobuf.x();
    float scaley = frameProtobuf.y();
    
    frame->setScaleX(scalex);
    frame->setScaleY(scaley);
    
    CCLOG("scalex = %f", scalex);
    CCLOG("scaley = %f", scaley);
    
	int frameIndex = frameProtobuf.has_frameindex() ? frameProtobuf.frameindex() : 0;
    frame->setFrameIndex(frameIndex);
    
    bool tween = (frameProtobuf.has_tween() ? frameProtobuf.tween() : false);
    frame->setTween(tween);
    
    return frame;
}

Frame* ActionTimelineCache::loadRotationSkewFrameFromProtocolBuffers(const protocolbuffers::TimeLinePointFrame &frameProtobuf)
{
	RotationSkewFrame* frame = RotationSkewFrame::create();
    
    float skewx = frameProtobuf.x();
    float skewy = frameProtobuf.y();
    
    frame->setSkewX(skewx);
    frame->setSkewY(skewy);
    
	int frameIndex = frameProtobuf.has_frameindex() ? frameProtobuf.frameindex() : 0;
    frame->setFrameIndex(frameIndex);
    
    bool tween = (frameProtobuf.has_tween() ? frameProtobuf.tween() : false);
    frame->setTween(tween);
    
    return frame;
}

Frame* ActionTimelineCache::loadAnchorPointFrameFromProtocolBuffers(const protocolbuffers::TimeLinePointFrame &frameProtobuf)
{
    AnchorPointFrame* frame = AnchorPointFrame::create();
    
    float anchorx = frameProtobuf.x();
    float anchory = frameProtobuf.y();
    
    frame->setAnchorPoint(ccp(anchorx, anchory));
    
    CCLOG("anchorx = %f", anchorx);
    CCLOG("anchory = %f", anchory);
    
	int frameIndex = frameProtobuf.has_frameindex() ? frameProtobuf.frameindex() : 0;
    frame->setFrameIndex(frameIndex);
    
    bool tween = (frameProtobuf.has_tween() ? frameProtobuf.tween() : false);
    frame->setTween(tween);
    
    return frame;
}

Frame* ActionTimelineCache::loadColorFrameFromProtocolBuffers(const protocolbuffers::TimeLineColorFrame &frameProtobuf)
{
    ColorFrame* frame = ColorFrame::create();
    
    GLubyte alpha = (GLubyte)frameProtobuf.alpha();
    GLubyte red   = (GLubyte)frameProtobuf.red();
    GLubyte green = (GLubyte)frameProtobuf.green();
    GLubyte blue  = (GLubyte)frameProtobuf.blue();
    
    frame->setAlpha(alpha);
    frame->setColor(ccc3(red, green, blue));
    
    CCLOG("alpha = %d", alpha);
    CCLOG("red = %d", red);
    CCLOG("green = %d", green);
    CCLOG("blue = %d", blue);
    
	int frameIndex = frameProtobuf.has_frameindex() ? frameProtobuf.frameindex() : 0;
    frame->setFrameIndex(frameIndex);
    
    bool tween = (frameProtobuf.has_tween() ? frameProtobuf.tween() : false);
    frame->setTween(tween);
    
    return frame;
}

Frame* ActionTimelineCache::loadTextureFrameFromProtocolBuffers(const protocolbuffers::TimeLineTextureFrame &frameProtobuf)
{
    TextureFrame* frame = TextureFrame::create();
    
    const char* texture = frameProtobuf.filepath().c_str();
    
    if (texture != NULL)
        frame->setTextureName(texture);
    
    CCLOG("texture = %s", texture);
    
	int frameIndex = frameProtobuf.has_frameindex() ? frameProtobuf.frameindex() : 0;
    frame->setFrameIndex(frameIndex);
    
    bool tween = (frameProtobuf.has_tween() ? frameProtobuf.tween() : false);
    frame->setTween(tween);
    
    return frame;
}

Frame* ActionTimelineCache::loadEventFrameFromProtocolBuffers(const protocolbuffers::TimeLineStringFrame &frameProtobuf)
{
    EventFrame* frame = EventFrame::create();
    
    const char* evnt = frameProtobuf.value().c_str();
    
    if (evnt != NULL)
        frame->setEvent(evnt);
    
    CCLOG("evnt = %s", evnt);
    
	int frameIndex = frameProtobuf.has_frameindex() ? frameProtobuf.frameindex() : 0;
    frame->setFrameIndex(frameIndex);
    
    bool tween = (frameProtobuf.has_tween() ? frameProtobuf.tween() : false);
    frame->setTween(tween);
    
    return frame;
}

Frame* ActionTimelineCache::loadZOrderFrameFromProtocolBuffers(const protocolbuffers::TimeLineIntFrame &frameProtobuf)
{
    ZOrderFrame* frame = ZOrderFrame::create();
    
    int zorder = frameProtobuf.value();
    frame->setZOrder(zorder);
    
    CCLOG("zorder = %d", zorder);
    
	int frameIndex = frameProtobuf.has_frameindex() ? frameProtobuf.frameindex() : 0;
    frame->setFrameIndex(frameIndex);
    
    bool tween = (frameProtobuf.has_tween() ? frameProtobuf.tween() : false);
    frame->setTween(tween);
    
    return frame;
}

NS_TIMELINE_END
