

#include "UILayoutTest_Editor.h"
#include "VisibleRect.h"


// UILayoutTest_Editor

UILayoutTest_Editor::UILayoutTest_Editor()
{
    
}

UILayoutTest_Editor::~UILayoutTest_Editor()
{
    
}

void UILayoutTest_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Editor/windows_ui_layout_editor_1.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Editor/windows_ui_layout_editor_1.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UILayout_Editor/UILayout_Editor/crossplatform_UILayout_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UILayout_Editor/UILayout_Editor/crossplatform_UILayout_Editor_1.csb");
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

void UILayoutTest_Editor::configureGUIScene()
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
                                 left_button->getSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}


bool UILayoutTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Editor/windows_ui_layout_editor_1.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
        
        CCMenu* menu = static_cast<CCMenu*>(getChildByTag(1));
        CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menu->getChildByTag(1));
        CCMenuItem* selectedItem = menuItemToggle->selectedItem();
        menuItemToggle->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 3.75f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Color_Editor

UILayoutTest_Color_Editor::UILayoutTest_Color_Editor()
{
    
}

UILayoutTest_Color_Editor::~UILayoutTest_Color_Editor()
{
    
}

void UILayoutTest_Color_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Color_Editor/windows_ui_layout_color_editor_1.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Color_Editor/windows_ui_layout_color_editor_1.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UILayout_Editor/UILayout_Color_Editor/crossplatform_UILayout_Color_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UILayout_Editor/UILayout_Color_Editor/crossplatform_UILayout_Color_Editor_1.csb");
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

void UILayoutTest_Color_Editor::configureGUIScene()
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
                                 left_button->getSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}


bool UILayoutTest_Color_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Color_Editor/windows_ui_layout_color_editor_1.json"));
        _touchGroup->addWidget(_layout);
       
        this->configureGUIScene();
        
        CCMenu* menu = static_cast<CCMenu*>(getChildByTag(1));
        CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menu->getChildByTag(1));
        CCMenuItem* selectedItem = menuItemToggle->selectedItem();
        menuItemToggle->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 3.75f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Gradient_Editor

UILayoutTest_Gradient_Editor::UILayoutTest_Gradient_Editor()
{
    
}

UILayoutTest_Gradient_Editor::~UILayoutTest_Gradient_Editor()
{
    
}

void UILayoutTest_Gradient_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Gradient_Color_Editor/windows_ui_layout_gradient_color_editor_1_0.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Gradient_Color_Editor/windows_ui_layout_gradient_color_editor_1_0.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UILayout_Editor/UILayout_Gradient_Color_Editor/crossplatform_UILayout_Gradient_Color_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UILayout_Editor/UILayout_Gradient_Color_Editor/crossplatform_UILayout_Gradient_Color_Editor_1.csb");
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

void UILayoutTest_Gradient_Editor::configureGUIScene()
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
                                 left_button->getSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}


bool UILayoutTest_Gradient_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Gradient_Color_Editor/windows_ui_layout_gradient_color_editor_1_0.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
        
        CCMenu* menu = static_cast<CCMenu*>(getChildByTag(1));
        CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menu->getChildByTag(1));
        CCMenuItem* selectedItem = menuItemToggle->selectedItem();
        menuItemToggle->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 3.75f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_BackGroundImage_Editor

UILayoutTest_BackGroundImage_Editor::UILayoutTest_BackGroundImage_Editor()
{
    
}

UILayoutTest_BackGroundImage_Editor::~UILayoutTest_BackGroundImage_Editor()
{
    
}

void UILayoutTest_BackGroundImage_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_BackgroundImage_Editor/windows_ui_layout_backgroundimage_editor_1_0_0.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_BackgroundImage_Editor/windows_ui_layout_backgroundimage_editor_1_0_0.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UILayout_Editor/UILayout_BackgroundImage_Editor/crossplatform_UILayout_BackgroundImage_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UILayout_Editor/UILayout_BackgroundImage_Editor/crossplatform_UILayout_BackgroundImage_Editor_1.csb");
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

void UILayoutTest_BackGroundImage_Editor::configureGUIScene()
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
                                 left_button->getSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}

bool UILayoutTest_BackGroundImage_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_BackgroundImage_Editor/windows_ui_layout_backgroundimage_editor_1_0_0.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
        
        CCMenu* menu = static_cast<CCMenu*>(getChildByTag(1));
        CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menu->getChildByTag(1));
        CCMenuItem* selectedItem = menuItemToggle->selectedItem();
        menuItemToggle->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 3.75f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_BackGroundImage_Scale9_Editor

UILayoutTest_BackGroundImage_Scale9_Editor::UILayoutTest_BackGroundImage_Scale9_Editor()
{
    
}

UILayoutTest_BackGroundImage_Scale9_Editor::~UILayoutTest_BackGroundImage_Scale9_Editor()
{
    
}

void UILayoutTest_BackGroundImage_Scale9_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Scale9_BackgroundImage_Editor/windows_ui_layout_scale9_backgroundimage_editor.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Scale9_BackgroundImage_Editor/windows_ui_layout_scale9_backgroundimage_editor.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UILayout_Editor/UILayout_Scale9_BackgroundImage_Editor/crossplatform_UILayout_Scale9_BackgroundImage_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UILayout_Editor/UILayout_Scale9_BackgroundImage_Editor/crossplatform_UILayout_Scale9_BackgroundImage_Editor_1.csb");
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

void UILayoutTest_BackGroundImage_Scale9_Editor::configureGUIScene()
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
                                 left_button->getSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}


bool UILayoutTest_BackGroundImage_Scale9_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Scale9_BackgroundImage_Editor/windows_ui_layout_scale9_backgroundimage_editor.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
        
        CCMenu* menu = static_cast<CCMenu*>(getChildByTag(1));
        CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menu->getChildByTag(1));
        CCMenuItem* selectedItem = menuItemToggle->selectedItem();
        menuItemToggle->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.15f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Layout_Linear_Vertical_Editor

UILayoutTest_Layout_Linear_Vertical_Editor::UILayoutTest_Layout_Linear_Vertical_Editor()
{
    
}

UILayoutTest_Layout_Linear_Vertical_Editor::~UILayoutTest_Layout_Linear_Vertical_Editor()
{
    
}

void UILayoutTest_Layout_Linear_Vertical_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Vertical_Layout_Editor/windows_ui_layout_linear_vertical_layout_editor.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Vertical_Layout_Editor/windows_ui_layout_linear_vertical_layout_editor.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Vertical_Layout_Editor/crossplatform_UILayout_Linear_Vertical_Layout_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Vertical_Layout_Editor/crossplatform_UILayout_Linear_Vertical_Layout_Editor_1.csb");
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

void UILayoutTest_Layout_Linear_Vertical_Editor::configureGUIScene()
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
                                 left_button->getSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}

bool UILayoutTest_Layout_Linear_Vertical_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Vertical_Layout_Editor/windows_ui_layout_linear_vertical_layout_editor.json"));
        _touchGroup->addWidget(_layout);
        this->configureGUIScene();
        
        CCMenu* menu = static_cast<CCMenu*>(getChildByTag(1));
        CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menu->getChildByTag(1));
        CCMenuItem* selectedItem = menuItemToggle->selectedItem();
        menuItemToggle->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.15f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Layout_Linear_Horizontal_Editor

UILayoutTest_Layout_Linear_Horizontal_Editor::UILayoutTest_Layout_Linear_Horizontal_Editor()
{
    
}

UILayoutTest_Layout_Linear_Horizontal_Editor::~UILayoutTest_Layout_Linear_Horizontal_Editor()
{
    
}

void UILayoutTest_Layout_Linear_Horizontal_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Horizontal_Layout_Editor/windows_ui_layout_linear_horizontal_layout_editor.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Horizontal_Layout_Editor/windows_ui_layout_linear_horizontal_layout_editor.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Horizontal_Layout_Editor/crossplatform_UILayout_Linear_Horizontal_Layout_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Horizontal_Layout_Editor/crossplatform_UILayout_Linear_Horizontal_Layout_Editor_1.csb");
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

void UILayoutTest_Layout_Linear_Horizontal_Editor::configureGUIScene()
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
                                 left_button->getSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}

bool UILayoutTest_Layout_Linear_Horizontal_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Horizontal_Layout_Editor/windows_ui_layout_linear_horizontal_layout_editor.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
        
        CCMenu* menu = static_cast<CCMenu*>(getChildByTag(1));
        CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menu->getChildByTag(1));
        CCMenuItem* selectedItem = menuItemToggle->selectedItem();
        menuItemToggle->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.15f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Layout_Relative_Align_Parent_Editor

UILayoutTest_Layout_Relative_Align_Parent_Editor::UILayoutTest_Layout_Relative_Align_Parent_Editor()
{
    
}

UILayoutTest_Layout_Relative_Align_Parent_Editor::~UILayoutTest_Layout_Relative_Align_Parent_Editor()
{
    
}

void UILayoutTest_Layout_Relative_Align_Parent_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Parent_Editor/windows_ui_layout_relative_align_parent_editor.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Parent_Editor/windows_ui_layout_relative_align_parent_editor.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Parent_Editor/crossplatform_UILayout_Relative_Align_Parent_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Parent_Editor/crossplatform_UILayout_Relative_Align_Parent_Editor_1.csb");
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

void UILayoutTest_Layout_Relative_Align_Parent_Editor::configureGUIScene()
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
                                 left_button->getSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}

bool UILayoutTest_Layout_Relative_Align_Parent_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Parent_Editor/windows_ui_layout_relative_align_parent_editor.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
        
        CCMenu* menu = static_cast<CCMenu*>(getChildByTag(1));
        CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menu->getChildByTag(1));
        CCMenuItem* selectedItem = menuItemToggle->selectedItem();
        menuItemToggle->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.15f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Layout_Relative_Location_Editor

UILayoutTest_Layout_Relative_Location_Editor::UILayoutTest_Layout_Relative_Location_Editor()
{
    
}

UILayoutTest_Layout_Relative_Location_Editor::~UILayoutTest_Layout_Relative_Location_Editor()
{
    
}

void UILayoutTest_Layout_Relative_Location_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Location_Editor/windows_ui_layout_relative_align_location_editor.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Location_Editor/windows_ui_layout_relative_align_location_editor.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Location_Editor/crossplatform_UILayout_Relative_Align_Location_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Location_Editor/crossplatform_UILayout_Relative_Align_Location_Editor_1.csb");
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

void UILayoutTest_Layout_Relative_Location_Editor::configureGUIScene()
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
                                 left_button->getSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
    left_button->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(ccp(_layout->getSize().width / 2 + right_button->getSize().width,
                                  right_button->getSize().height));
    right_button->setTouchEnabled(true);
    right_button->setZOrder(_layout->getZOrder() + 1);
    right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
    _layout->addChild(right_button);
}

bool UILayoutTest_Layout_Relative_Location_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Location_Editor/windows_ui_layout_relative_align_location_editor.json"));
        _touchGroup->addWidget(_layout);
        this->configureGUIScene();
        
        CCMenu* menu = static_cast<CCMenu*>(getChildByTag(1));
        CCMenuItemToggle* menuItemToggle = static_cast<CCMenuItemToggle*>(menu->getChildByTag(1));
        CCMenuItem* selectedItem = menuItemToggle->selectedItem();
        menuItemToggle->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.15f));
        
        return true;
    }
    
    return false;
}
