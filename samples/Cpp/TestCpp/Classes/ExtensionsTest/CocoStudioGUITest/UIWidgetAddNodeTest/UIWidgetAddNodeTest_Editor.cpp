

#include "UIWidgetAddNodeTest_Editor.h"


// UIWidgetAddNodeTest_Editor

UIWidgetAddNodeTest_Editor::UIWidgetAddNodeTest_Editor()
{
    
}

UIWidgetAddNodeTest_Editor::~UIWidgetAddNodeTest_Editor()
{
    
}

void UIWidgetAddNodeTest_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeAllChildrenWithCleanup(true);
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/windows_ui_widget_add_node_editor.json"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeAllChildrenWithCleanup(true);
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/windows_ui_widget_add_node_editor.csb"));
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNode("cocosui/UIEditorTest/UIWidgetAddNode_Editor/crossplatform_UIWidgetAddNode_Editor_1.ExportJson");
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
            
            CCNode* node = cocostudio::timeline::NodeReader::getInstance()->createNodeFromProtocolBuffers("cocosui/UIEditorTest/UIWidgetAddNode_Editor/crossplatform_UIWidgetAddNode_Editor_1.csb");
            TouchGroup* temp = static_cast<TouchGroup*>(node->getChildByTag(5));
            Layout* tempLayout = static_cast<Layout*>(temp->getWidgetByTag(5));
            tempLayout->removeFromParent();
            _layout = tempLayout;
            _touchGroup->addWidget(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
            /*
             case 2:
             {
             _layout->removeAllChildrenWithCleanup(true);
             _layout->removeFromParentAndCleanup(true);
             
             _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/ui_widget_add_node_editor.csb"));
             _touchGroup->addWidget(_layout);
             
             this->configureGUIScene();
             
             break;
             }
             */
            
        default:
            break;
    }
}

void UIWidgetAddNodeTest_Editor::configureGUIScene()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSize rootSize = _layout->getSize();
    _touchGroup->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                     (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));
    
    ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
    
    _sceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "UItest"));
    
    
    // Create the ui widget
    Widget* widget = Widget::create();
    widget->setPosition(ccp(rootSize.width / 2.0f, rootSize.height / 2.0f));
    widget->setZOrder(_layout->getZOrder() + 1);
    _layout->addChild(widget);
    
    CCSprite* sprite = CCSprite::create("cocosui/ccicon.png");
    widget->addNode(sprite);

}

bool UIWidgetAddNodeTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/windows_ui_widget_add_node_editor.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
        return true;
    }
    
    return false;
}

