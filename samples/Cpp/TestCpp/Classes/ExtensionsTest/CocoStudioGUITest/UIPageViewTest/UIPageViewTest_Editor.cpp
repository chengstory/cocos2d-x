

#include "UIPageViewTest_Editor.h"
#include "../../../VisibleRect.h"


// UIPageViewTest_Editor

UIPageViewTest_Editor::UIPageViewTest_Editor()
: _displayValueLabel(NULL)
{
    
}

UIPageViewTest_Editor::~UIPageViewTest_Editor()
{
    
}


void UIPageViewTest_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeAllChildrenWithCleanup(true);
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UIPageView_Editor/windows_ui_pageview_editor_1.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeAllChildrenWithCleanup(true);
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UIPageView_Editor/windows_ui_pageview_editor_1.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UIPageView_Editor/crossplatform_UIPageView_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UIPageView_Editor/crossplatform_UIPageView_Editor_1.csb");
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

void UIPageViewTest_Editor::configureGUIScene()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSize rootSize = _layout->getSize();
    _touchGroup->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                     (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));
    
    ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
    
    _sceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "UItest"));
    
    Button* left_button = Button::create();
    left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
    left_button->setPosition(ccp(_layout->getSize().width / 2 - left_button->getSize().width,
                                 left_button->getSize().height * 0.625));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height * 0.625));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}


bool UIPageViewTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UIPageView_Editor/windows_ui_pageview_editor_1.json"));
        _touchGroup->addWidget(_layout);
       
        this->configureGUIScene();
        return true;
    }
    
    return false;
}