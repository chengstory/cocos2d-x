

#include "UISliderTest_Editor.h"


// UISliderTest_Editor

UISliderTest_Editor::UISliderTest_Editor()
: _displayValueLabel(NULL)
{
    
}

UISliderTest_Editor::~UISliderTest_Editor()
{
    
}

void UISliderTest_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeAllChildrenWithCleanup(true);
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UISlider_Editor/windows_ui_slider_editor_1.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeAllChildrenWithCleanup(true);
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UISlider_Editor/windows_ui_slider_editor_1.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UISlider_Editor/crossplatform_UISlider_Editor_1.ExportJson");
            TouchGroup* temp = static_cast<TouchGroup*>(node->getChildByTag(5));
            Layout* tempLayout = static_cast<Layout*>(temp->getWidgetByTag(5));
            tempLayout->removeFromParent();
            _layout = tempLayout;
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 3:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UISlider_Editor/crossplatform_UISlider_Editor_1.csb");
            TouchGroup* temp = static_cast<TouchGroup*>(node->getChildByTag(5));
            Layout* tempLayout = static_cast<Layout*>(temp->getWidgetByTag(5));
            tempLayout->removeFromParent();
            _layout = tempLayout;
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        default:
            break;
    }
}

void UISliderTest_Editor::configureGUIScene()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSize rootSize = _layout->getSize();
    _touchGroup->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                     (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));
    
    ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
    
    _sceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "UItest"));
    
    
    Slider* slider = static_cast<Slider*>(UIHelper::seekWidgetByName(root, "Slider_738"));
    slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest_Editor::sliderEvent));
    
    Slider* scale9_slider = static_cast<Slider*>(UIHelper::seekWidgetByName(root, "Slider_740"));
    scale9_slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest_Editor::sliderEvent));
    

}

bool UISliderTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UISlider_Editor/windows_ui_slider_editor_1.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
        
        
        _displayValueLabel = ui::Label::create();
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setText("No event");
        _displayValueLabel->setPosition(ccp(_layout->getSize().width / 2,
                                            _layout->getSize().height - _displayValueLabel->getSize().height * 1.75f));
        _touchGroup->addWidget(_displayValueLabel);
        
        return true;
    }
    
    return false;
}

void UISliderTest_Editor::sliderEvent(cocos2d::CCObject *pSender, SliderEventType type)
{
    switch (type)
    {
        case SLIDER_PERCENTCHANGED:
        {
            Slider* slider = static_cast<Slider*>(pSender);
            _displayValueLabel->setText(CCString::createWithFormat("percent %d", slider->getPercent())->getCString());
        }
            break;
            
        default:
            break;
    }
}
