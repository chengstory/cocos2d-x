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

#ifndef __CC_EXTENTIONS_CCCOMAUDIO_H__
#define __CC_EXTENTIONS_CCCOMAUDIO_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/**
@class @~english ComAudio @~chinese ComAudio
@brief @~english audio component @~chinese 声音组件
@details @~english save the sound file path, packaging play background music, effects interface, easy to assembly programming, and support export data of cocos studio 1.x Scene Editor @~chinese 保存声音文件路径，封装播放背景音乐，效果接口，方便以组件式编程，配合解析cocos studio 1.x场景编辑器导出的数据
@group @~english component @~chinese 组件
*/
class CC_STUDIO_DLL ComAudio : public cocos2d::Component
{

    DECLARE_CLASS_COMPONENT_INFO

public:
    /**
     * @js ctor
     */
    /**
    @brief @~english ComAudio constructor @~chinese 声音组件构造函数
    */
    ComAudio(void);
    /**
     * @js NA
     * @lua NA
     */
    /**
    @brief @~english ComAudio destructor @~chinese 声音组件析构函数
    */
    virtual ~ComAudio(void);
    
public:
    /**
    @brief @~english ComAudio object initialization function @~chinese 初始化声音组件
    @return @~english true  initialization successfully false failed to initialize @~chinese true 初始化成功，否则false
    */
    virtual bool init() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @主题 node调用onEnter的时候，会调用组件的onEnter
    @返回 无
    */

    /**
    @brief @~english calls component's onEnter when node calls onEnter @~chinese node调用onEnter的时候，会调用组件的onEnter
    @return @~english void @~chinese 无
    */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @brief @~english calls component's onExit when node calls onExit @~chinese node调用onExit的时候，会调用组件的onExit
    @return @~english void @~chinese 无
    */
    virtual void onExit() override;
    /**
    @brief @~english get whether audio component is available @~chinese 判断声音组件是否可用
    @return @~english return true if audio component is available,else return false @~chinese 可用返回true，否则返回false
    */
    virtual bool isEnabled() const override;
    /**
    @brief @~english get whether audio component is available @~chinese 设置当前声音组件是否可用
    @param b @~english set whether audio component is available, true available false not available @~chinese  true为可用，false为不可用
    @return @~english void @~chinese 无
    */
    virtual void setEnabled(bool b) override;
    /**
    @brief @~english de-serialization export data of scene editor in cocos studio 1.x  @~chinese 反序列化cocos studio 1.x 场景编辑器导出的数据
    @param r @~english serialization data point @~chinese 反序列化数据
    @return @~english true  initialization successfully false failed to initialize @~chinese true 初始化成功，否则false
    */
    virtual bool serialize(void* r) override;
    /**
    @brief @~english ComAudio object create function @~chinese 声音组件创建方法
    @return point of ComAudio object
    */
    static ComAudio* create(void);
   
public:
    /**
    @brief @~english release audio engine object, stop playing all the audio of background and effects @~chinese 释放声音引擎对象，停止播放所有背景音与音效
    @return @~english void @~chinese 无
    */
    void end();
    /**
    @brief @~english pre-load background music @~chinese 预加载背景音乐
    @param pszFilePath @~english background music path @~chinese 背景音乐路径
    @return @~english void @~chinese 无
    */
    void preloadBackgroundMusic(const char* pszFilePath);
    /**
    @brief @~english play background music @~chinese 播放背景音乐
    @param pszFilePath @~english background music path @~chinese 背景音乐路径
    @param bLoop @~english set whether play background music is loop @~chinese bLoop true 循环播放 false 播放一次
    @return @~english void @~chinese 无
    */
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);
    /**
    @brief @~english play background music @~chinese 播放背景音乐
    @param pszFilePath @~english background music path @~chinese 背景音乐路径
    @return @~english void @~chinese 无
    */
    void playBackgroundMusic(const char* pszFilePath);
    /**
    @brief @~english play background music @~chinese 播放背景音乐
    @return @~english void @~chinese 无
    */
    void playBackgroundMusic();
    /**
    @brief @~english stop background music @~chinese 停止播放背景音乐
    @param bReleaseData @~english true stop and release background music buffer  false only stop background music @~chinese true 停止并释放缓存 false 仅停止播放
    @return @~english void @~chinese 无
    */
    void stopBackgroundMusic(bool bReleaseData);
    /**
    @brief @~english stop background music @~chinese 停止播放背景音乐
    @return @~english void @~chinese 无
   */
    void stopBackgroundMusic();
    /**
    @brief @~english pause background music @~chinese 暂停播放背景音乐
    @return @~english void @~chinese 无
    */
    void pauseBackgroundMusic();
    /**
    @brief @~english resume background music @~chinese 回复播放背景音乐
    @return @~english void @~chinese 无
    */
    void resumeBackgroundMusic();
    /**
    @brief @~english rewind background music @~chinese 倒带播放背景音乐
    @return @~english void @~chinese 无
    */
    void rewindBackgroundMusic();
    /**
    @brief @~english whether the background music can be played @~chinese 背景音乐是否将可以播放
    @return @~english true it will can be played false it can't be played @~chinese true 可以播放 false 将不能播放
   */
    bool willPlayBackgroundMusic();

    /**
    @brief @~english whether the background music is playing @~chinese 背景音乐是否正在播放
    @return @~english true it is playing false it isn't playing  @~chinese true 正在播放 false 没有正在播放
    */
    bool isBackgroundMusicPlaying();
    /**
    @brief @~english get the volume of background music  @~chinese 获取背景音乐的音量
    @return @~english the volume of background music @~chinese true 背景音乐的音量
    */
    float getBackgroundMusicVolume();
    /**
    @brief @~english set volume of background music @~chinese 设置背景音乐音量
    @prama volume @~english volume of background music @~chinese 背景音乐音量
    @return @~english void @~chinese 无
    */
    void setBackgroundMusicVolume(float volume);
    /**
    @brief @~english get the volume of effects  @~chinese 获取效果音乐的音量
    @return @~english the volume of effects @~chinese true 效果音乐的音量
    */
    float getEffectsVolume();
    /**
    @brief @~english set volume of effects @~chinese 设置效果音乐音量
    @prama volume @~english volume of effects @~chinese 效果音乐音量
    @return @~english void @~chinese 无
    */
    void setEffectsVolume(float volume);
    /**
    @brief @~english play effect @~chinese 播放效果音乐
    @param pszFilePath @~english effect path @~chinese 效果路径
    @param bLoop @~english set whether play effect is loop @~chinese bLoop true 循环播放 false 播放一次
    @return @~english effect ID @~chinese 效果音乐ID
    */
    unsigned int playEffect(const char* pszFilePath, bool bLoop);
    /**
    @主题 播放效果音乐，如果发现没有预加载此音乐，会先预加载，然后播放，根据成员变量_loop判断是否循环播放
    @参数 pszFilePath 背景音乐路径
    @返回 效果音乐ID
    */
    unsigned int playEffect(const char* pszFilePath);
    /**
    @主题 根据_filePath与_loop来播放播放音乐
    @返回 效果音乐ID
    */
    unsigned int playEffect();
    /**
    @主题 暂停播放效果音乐
    @参数 nSoundID 效果音乐ID
    @返回 无
    */
    void pauseEffect(unsigned int nSoundId);
    /**
    @主题 暂停所有效果音乐
    @返回 无
    */
    void pauseAllEffects();
    /**
    @主题 恢复暂停效果音乐，继续播放
    @参数 nSoundID 效果音乐ID
    @返回 无
    */
    void resumeEffect(unsigned int nSoundId);
    /**
    @主题 恢复暂停的所有效果音乐，继续播放
    @返回 无
    */
    void resumeAllEffects();
    /**
    @主题 停止播放效果音乐
    @参数 nSoundID 效果音乐ID
    @返回 无
    */
    void stopEffect(unsigned int nSoundId);
    /**
    @主题 停止所有效果音乐
    @返回 无
    */
    void stopAllEffects();
    /**
    @主题 预加载效果音乐
    @参数 pszFilePath 背景音乐路径
    @返回 无
    */
    void preloadEffect(const char* pszFilePath);
    /**
    @主题 释放预加载效果音乐缓存
    @参数 pszFilePath 背景音乐路径
    @返回 无
    */
    void unloadEffect(const char* pszFilePath);
    /**
    @主题 设置音乐路径
    @参数 pszFilePath 音乐路径
    @返回 无
    */
    void setFile(const char* pszFilePath);
    /**
    @主题 获取音乐路径
    @返回 _filePath 音乐路径
    */
    const char* getFile();
    /**
    @主题 设置是否循环
    @参数 bLoop 是否循环
    @返回 无
    */
    void setLoop(bool bLoop);
    /**
    @主题 判断是否循环
    @返回 true 循环 false 不循环
    */
    bool isLoop();
private:
	std::string _filePath;
	bool _loop;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
