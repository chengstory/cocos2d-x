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

#include "CCTimelineAction.h"

using namespace cocos2d;

namespace cocostudio {
namespace animation {

TimelineAction* TimelineAction::create()
{
    TimelineAction* object = new TimelineAction();
    if (object && object->init())
    {
        object->autorelease();
        return object;
    }
    CC_SAFE_DELETE(object);
    return NULL;
}

TimelineAction::TimelineAction()
    : _timelineList(NULL)
    , _duration(0)
    , _time(0)
    , _timeSpeed(1)
    , _frameInternal(1/60.0f)
    , _playing(false)
    , _currentFrame(0)
    , _endFrame(0)
    , _frameEventCallFunc(NULL)
    , _frameEventTarget(NULL)
{
}

TimelineAction::~TimelineAction()
{
    std::map<int, cocos2d::CCArray*>::const_iterator i = _timelineMap.begin();
    for (; i != _timelineMap.end(); i++)
    {
        CCArray* timelines = i->second;
        CC_SAFE_DELETE(timelines);
    }

    CC_SAFE_DELETE(_timelineList);
}

bool TimelineAction::init()
{
    _timelineList = new cocos2d::CCArray();
    _timelineList->init();

    return true;
}

void TimelineAction::gotoFrameAndPlay(int startIndex)
{
    gotoFrameAndPlay(startIndex, true);
}

void TimelineAction::gotoFrameAndPlay(int startIndex, bool loop)
{
    gotoFrameAndPlay(startIndex, _duration, loop);
}

void TimelineAction::gotoFrameAndPlay(int startIndex, int endIndex, bool loop)
{
    _endFrame = endIndex;
    _loop = loop;
    _currentFrame = startIndex;
    _time = _currentFrame*_frameInternal;

    resume();
    gotoFrame(_currentFrame);
}

void TimelineAction::gotoFrameAndPause(int startIndex)
{
    _time =_currentFrame = startIndex;

    pause();
    gotoFrame(_currentFrame);
}

void TimelineAction::pause()
{
    _playing = false;
}

void TimelineAction::resume()
{
    _playing = true;
}

bool TimelineAction::isPlaying()
{
    return _playing;
}

void TimelineAction::setTimeSpeed(float speed)
{
    _timeSpeed = speed;
}

float TimelineAction::getTimeSpeed()
{
    return _timeSpeed;
}

TimelineAction* TimelineAction::clone() const
{
    TimelineAction* newAction = TimelineAction::create();
    newAction->setDuration(_duration);
    newAction->setTimeSpeed(_timeSpeed);
    
    std::map<int, cocos2d::CCArray*>::const_iterator i = _timelineMap.begin();
    for (; i != _timelineMap.end(); i++)
    {
        CCObject* object = NULL;
        CCARRAY_FOREACH(i->second, object)
        {      
            Timeline* timeline = static_cast<Timeline*>(object);
            Timeline* newTimeline = timeline->clone();
            newAction->addTimeline(newTimeline);
        }
    }

    return newAction;
}

void TimelineAction::step(float delta)
{
    if (!_playing || _timelineMap.size() == 0 || _duration == 0)
    {
        return;
    }

    _time += delta * _timeSpeed;
    _currentFrame = (int)(_time / _frameInternal);

    if (_currentFrame > _endFrame)
    {
        _playing = _loop;
        if(!_playing)
        {
            _currentFrame = _time = _endFrame;
            return;
        }
        else           
            _currentFrame = _time = 0;
    }

    stepToFrame(_currentFrame);
}


void TimelineAction::foreachNodeDescendant(CCNode* parent)
{
    int actionTag = parent->getTag();

    CCObject* object = NULL;

    if(_timelineMap.find(actionTag) != _timelineMap.end())
    {
        CCArray* timelines = this->_timelineMap[actionTag];
        CCARRAY_FOREACH (timelines, object)
        {
            Timeline* timeline = static_cast<Timeline*>(object);
            timeline->setNode(parent);
        }
    }

    CCArray* children = parent->getChildren();
    CCARRAY_FOREACH (children, object)
    {
        CCNode* child = static_cast<CCNode*>(object);
        foreachNodeDescendant(child);
    }
}

void TimelineAction::startWithTarget(CCNode *target)
{
    CCAction::startWithTarget(target);

    foreachNodeDescendant(target);
}

void TimelineAction::addTimeline(Timeline* timeline)
{
    int tag = timeline->getActionTag();
    if (_timelineMap.find(tag) == _timelineMap.end())
    {
        CCArray* timelines = new CCArray();
        timelines->init();
        _timelineMap[tag] = timelines;
    }

    if (!_timelineMap[tag]->containsObject(timeline))
    {
        _timelineList->addObject(timeline);
        _timelineMap[tag]->addObject(timeline);
        timeline->setTimelineAction(this);
    }
}

void TimelineAction::removeTimeline(Timeline* timeline)
{
    int tag = timeline->getActionTag();
    if (_timelineMap.find(tag) != _timelineMap.end())
    {
        if(_timelineMap[tag]->containsObject(timeline))
        {
            _timelineMap[tag]->removeObject(timeline);
            _timelineList->removeObject(timeline);
            timeline->setTimelineAction(NULL);
        }
    }
}

void TimelineAction::setFrameEventCallFunc  (CCObject *target, SEL_FrameEventCallFunc callFunc)
{
    _frameEventTarget   = target;
    _frameEventCallFunc = callFunc;
}

void TimelineAction::clearFrameEventCallFunc()
{
    _frameEventTarget   = NULL;
    _frameEventCallFunc = NULL;
}

void TimelineAction::emitFrameEvent(Frame* frame)
{
    if (_frameEventTarget != NULL && _frameEventCallFunc != NULL)
    {
        (_frameEventTarget->*_frameEventCallFunc)(frame);
    }
}

void TimelineAction::gotoFrame(int frameIndex)
{
    int size = _timelineList->count();
    Timeline** timelines = (Timeline**)_timelineList->data->arr;
    for(int i = 0; i<size; i++)
    {      
        timelines[i]->gotoFrame(frameIndex);
    }
}

void TimelineAction::stepToFrame(int frameIndex)
{
    int size = _timelineList->count();
    Timeline** timelines = (Timeline**)_timelineList->data->arr;
    for(int i = 0; i<size; i++)
    {      
        timelines[i]->stepToFrame(frameIndex);
    }
}

}
}
