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

#include "CCTimeLine.h"
#include "CCFrame.h"

using namespace cocos2d;

namespace cocostudio {
namespace animation {

Timeline* Timeline::create()
{
    Timeline* object = new Timeline();
    if (object && object->init())
    {
        object->autorelease();
        return object;
    }
    CC_SAFE_DELETE(object);
    return nullptr;
}

Timeline::Timeline()
    : _frames(nullptr)
    , _currentKeyFrame(nullptr)
    , _currentKeyFrameIndex(0)
    , _fromIndex(0)
    , _toIndex(0)
    , _betweenDuration(0)
    , _actionTag(0)
    , _node(nullptr)
{
}

Timeline::~Timeline()
{
    CC_SAFE_DELETE(_frames);
}

bool Timeline::init()
{
    _frames = new cocos2d::CCArray();
    return _frames->init();
}

void Timeline::gotoFrame(int frameIndex)
{
    updateCurrentKeyFrame(frameIndex);

    if (_currentKeyFrame)
    {
        float currentPercent = _betweenDuration == 0 ? 0 : (frameIndex - _currentKeyFrameIndex) / (float)_betweenDuration;
        _currentKeyFrame->apply(currentPercent);
    }
}

Timeline* Timeline::clone()
{
    Timeline* timeline = Timeline::create();
    timeline->_actionTag = _actionTag;

    CCObject* object = nullptr;
    CCARRAY_FOREACH(_frames, object)
    {
        Frame* frame = static_cast<Frame*>(object);
        Frame* newFrame = frame->clone();
        timeline->getFrames()->addObject(newFrame);
    }

    return timeline;
}

void Timeline::setNode(cocos2d::CCNode* node)
{
    CCObject* object = nullptr;
    CCARRAY_FOREACH(_frames, object)
    {
        Frame* frame = static_cast<Frame*>(object);
        frame->setNode(node);
    }
}

cocos2d::CCNode* Timeline::getNode()
{
    return _node;
}

void Timeline::updateCurrentKeyFrame(int frameIndex)
{
    //! If play to current frame's front or back, then find current frame again
    if (frameIndex < _currentKeyFrameIndex || frameIndex >= _currentKeyFrameIndex + _betweenDuration)
    {
        Frame *from = nullptr;
        Frame *to = nullptr;

        do 
        {
            Frame **frames = (Frame **)_frames->data->arr;

            long length = _frames->count();

            if (frameIndex < frames[0]->getFrameIndex())
            {
                from = to = frames[0];
                break;
            }
            else if(frameIndex >= frames[length - 1]->getFrameIndex())
            {
                from = to = frames[length - 1];
                _currentKeyFrameIndex = 0;
                _betweenDuration = 0;
                break;
            }

            do
            {
                _fromIndex = _toIndex;
                from = frames[_fromIndex];
                _currentKeyFrameIndex  = from->getFrameIndex();

                _toIndex = _fromIndex + 1;
                if (_toIndex >= length)
                {
                    _toIndex = 0;
                }

                to = frames[_toIndex];

                if (frameIndex == from->getFrameIndex())
                {
                    break;
                }
            }
            while (frameIndex < from->getFrameIndex() || frameIndex >= to->getFrameIndex());

            _betweenDuration = to->getFrameIndex() - from->getFrameIndex();

        } while (0);

        _currentKeyFrame = from;
        _currentKeyFrame->onEnter(to);
    }
}

}
}
