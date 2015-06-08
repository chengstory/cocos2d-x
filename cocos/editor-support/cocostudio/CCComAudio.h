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
@brief @~english audio component @~chinese �������
@details @~english save the sound file path, packaging play background music, effects interface, easy to assembly programming, and support export data of cocos studio 1.x Scene Editor @~chinese ���������ļ�·������װ���ű������֣�Ч���ӿڣ����������ʽ��̣���Ͻ���cocos studio 1.x�����༭������������
@group @~english component @~chinese ���
*/
class CC_STUDIO_DLL ComAudio : public cocos2d::Component
{

    DECLARE_CLASS_COMPONENT_INFO

public:
    /**
     * @js ctor
     */
    /**
    @brief @~english ComAudio constructor @~chinese ����������캯��
    */
    ComAudio(void);
    /**
     * @js NA
     * @lua NA
     */
    /**
    @brief @~english ComAudio destructor @~chinese ���������������
    */
    virtual ~ComAudio(void);
    
public:
    /**
    @brief @~english ComAudio object initialization function @~chinese ��ʼ���������
    @return @~english true  initialization successfully false failed to initialize @~chinese true ��ʼ���ɹ�������false
    */
    virtual bool init() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @���� node����onEnter��ʱ�򣬻���������onEnter
    @���� ��
    */

    /**
    @brief @~english calls component's onEnter when node calls onEnter @~chinese node����onEnter��ʱ�򣬻���������onEnter
    @return @~english void @~chinese ��
    */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @brief @~english calls component's onExit when node calls onExit @~chinese node����onExit��ʱ�򣬻���������onExit
    @return @~english void @~chinese ��
    */
    virtual void onExit() override;
    /**
    @brief @~english get whether audio component is available @~chinese �ж���������Ƿ����
    @return @~english return true if audio component is available,else return false @~chinese ���÷���true�����򷵻�false
    */
    virtual bool isEnabled() const override;
    /**
    @brief @~english get whether audio component is available @~chinese ���õ�ǰ��������Ƿ����
    @param b @~english set whether audio component is available, true available false not available @~chinese  trueΪ���ã�falseΪ������
    @return @~english void @~chinese ��
    */
    virtual void setEnabled(bool b) override;
    /**
    @brief @~english de-serialization export data of scene editor in cocos studio 1.x  @~chinese �����л�cocos studio 1.x �����༭������������
    @param r @~english serialization data point @~chinese �����л�����
    @return @~english true  initialization successfully false failed to initialize @~chinese true ��ʼ���ɹ�������false
    */
    virtual bool serialize(void* r) override;
    /**
    @brief @~english ComAudio object create function @~chinese ���������������
    @return point of ComAudio object
    */
    static ComAudio* create(void);
   
public:
    /**
    @brief @~english release audio engine object, stop playing all the audio of background and effects @~chinese �ͷ������������ֹͣ�������б���������Ч
    @return @~english void @~chinese ��
    */
    void end();
    /**
    @brief @~english pre-load background music @~chinese Ԥ���ر�������
    @param pszFilePath @~english background music path @~chinese ��������·��
    @return @~english void @~chinese ��
    */
    void preloadBackgroundMusic(const char* pszFilePath);
    /**
    @brief @~english play background music @~chinese ���ű�������
    @param pszFilePath @~english background music path @~chinese ��������·��
    @param bLoop @~english set whether play background music is loop @~chinese bLoop true ѭ������ false ����һ��
    @return @~english void @~chinese ��
    */
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);
    /**
    @brief @~english play background music @~chinese ���ű�������
    @param pszFilePath @~english background music path @~chinese ��������·��
    @return @~english void @~chinese ��
    */
    void playBackgroundMusic(const char* pszFilePath);
    /**
    @brief @~english play background music @~chinese ���ű�������
    @return @~english void @~chinese ��
    */
    void playBackgroundMusic();
    /**
    @brief @~english stop background music @~chinese ֹͣ���ű�������
    @param bReleaseData @~english true stop and release background music buffer  false only stop background music @~chinese true ֹͣ���ͷŻ��� false ��ֹͣ����
    @return @~english void @~chinese ��
    */
    void stopBackgroundMusic(bool bReleaseData);
    /**
    @brief @~english stop background music @~chinese ֹͣ���ű�������
    @return @~english void @~chinese ��
   */
    void stopBackgroundMusic();
    /**
    @brief @~english pause background music @~chinese ��ͣ���ű�������
    @return @~english void @~chinese ��
    */
    void pauseBackgroundMusic();
    /**
    @brief @~english resume background music @~chinese �ظ����ű�������
    @return @~english void @~chinese ��
    */
    void resumeBackgroundMusic();
    /**
    @brief @~english rewind background music @~chinese �������ű�������
    @return @~english void @~chinese ��
    */
    void rewindBackgroundMusic();
    /**
    @brief @~english whether the background music can be played @~chinese ���������Ƿ񽫿��Բ���
    @return @~english true it will can be played false it can't be played @~chinese true ���Բ��� false �����ܲ���
   */
    bool willPlayBackgroundMusic();

    /**
    @brief @~english whether the background music is playing @~chinese ���������Ƿ����ڲ���
    @return @~english true it is playing false it isn't playing  @~chinese true ���ڲ��� false û�����ڲ���
    */
    bool isBackgroundMusicPlaying();
    /**
    @brief @~english get the volume of background music  @~chinese ��ȡ�������ֵ�����
    @return @~english the volume of background music @~chinese true �������ֵ�����
    */
    float getBackgroundMusicVolume();
    /**
    @brief @~english set volume of background music @~chinese ���ñ�����������
    @prama volume @~english volume of background music @~chinese ������������
    @return @~english void @~chinese ��
    */
    void setBackgroundMusicVolume(float volume);
    /**
    @brief @~english get the volume of effects  @~chinese ��ȡЧ�����ֵ�����
    @return @~english the volume of effects @~chinese true Ч�����ֵ�����
    */
    float getEffectsVolume();
    /**
    @brief @~english set volume of effects @~chinese ����Ч����������
    @prama volume @~english volume of effects @~chinese Ч����������
    @return @~english void @~chinese ��
    */
    void setEffectsVolume(float volume);
    /**
    @brief @~english play effect @~chinese ����Ч������
    @param pszFilePath @~english effect path @~chinese Ч��·��
    @param bLoop @~english set whether play effect is loop @~chinese bLoop true ѭ������ false ����һ��
    @return @~english effect ID @~chinese Ч������ID
    */
    unsigned int playEffect(const char* pszFilePath, bool bLoop);
    /**
    @���� ����Ч�����֣��������û��Ԥ���ش����֣�����Ԥ���أ�Ȼ�󲥷ţ����ݳ�Ա����_loop�ж��Ƿ�ѭ������
    @���� pszFilePath ��������·��
    @���� Ч������ID
    */
    unsigned int playEffect(const char* pszFilePath);
    /**
    @���� ����_filePath��_loop�����Ų�������
    @���� Ч������ID
    */
    unsigned int playEffect();
    /**
    @���� ��ͣ����Ч������
    @���� nSoundID Ч������ID
    @���� ��
    */
    void pauseEffect(unsigned int nSoundId);
    /**
    @���� ��ͣ����Ч������
    @���� ��
    */
    void pauseAllEffects();
    /**
    @���� �ָ���ͣЧ�����֣���������
    @���� nSoundID Ч������ID
    @���� ��
    */
    void resumeEffect(unsigned int nSoundId);
    /**
    @���� �ָ���ͣ������Ч�����֣���������
    @���� ��
    */
    void resumeAllEffects();
    /**
    @���� ֹͣ����Ч������
    @���� nSoundID Ч������ID
    @���� ��
    */
    void stopEffect(unsigned int nSoundId);
    /**
    @���� ֹͣ����Ч������
    @���� ��
    */
    void stopAllEffects();
    /**
    @���� Ԥ����Ч������
    @���� pszFilePath ��������·��
    @���� ��
    */
    void preloadEffect(const char* pszFilePath);
    /**
    @���� �ͷ�Ԥ����Ч�����ֻ���
    @���� pszFilePath ��������·��
    @���� ��
    */
    void unloadEffect(const char* pszFilePath);
    /**
    @���� ��������·��
    @���� pszFilePath ����·��
    @���� ��
    */
    void setFile(const char* pszFilePath);
    /**
    @���� ��ȡ����·��
    @���� _filePath ����·��
    */
    const char* getFile();
    /**
    @���� �����Ƿ�ѭ��
    @���� bLoop �Ƿ�ѭ��
    @���� ��
    */
    void setLoop(bool bLoop);
    /**
    @���� �ж��Ƿ�ѭ��
    @���� true ѭ�� false ��ѭ��
    */
    bool isLoop();
private:
	std::string _filePath;
	bool _loop;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
