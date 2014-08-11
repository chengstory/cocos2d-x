

#include "ListViewReader.h"
#include "../../../GUI/UIWidgets/ScrollWidget/UIListView.h"
#include "../../../Json/CSParseBinary.pb.h"

NS_CC_EXT_BEGIN

static ListViewReader* instanceListViewReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(ListViewReader)

ListViewReader::ListViewReader()
{
    
}

ListViewReader::~ListViewReader()
{
    
}

ListViewReader* ListViewReader::getInstance()
{
    if (!instanceListViewReader)
    {
        instanceListViewReader = new ListViewReader();
    }
    return instanceListViewReader;
}

void ListViewReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    ScrollViewReader::setPropsFromJsonDictionary(widget, options);
    
    
    ui::ListView* listView = (ui::ListView*)widget;
    
	int direction = DICTOOL->getFloatValue_json(options, "direction",2);
	listView->setDirection((ui::SCROLLVIEW_DIR)direction);
    
    ui::ListViewGravity gravity = (ui::ListViewGravity)DICTOOL->getIntValue_json(options, "gravity",3);
    listView->setGravity(gravity);
    
    float itemMargin = DICTOOL->getFloatValue_json(options, "itemMargin");
    listView->setItemsMargin(itemMargin);
}

void ListViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    ScrollViewReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
    
    ui::ListView* listView = static_cast<ui::ListView*>(widget);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue(pCocoLoader);
        
        if (key == "direction") {
            listView->setDirection((ui::SCROLLVIEW_DIR)valueToInt(value));
        }
        else if(key == "gravity"){
            listView->setGravity((ui::ListViewGravity)valueToInt(value));
        }else if(key == "itemMargin"){
            listView->setItemsMargin(valueToFloat(value));
        }
        
    } //end of for loop
}

void ListViewReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
{
    WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
    
    ui::ListView* listView = static_cast<ui::ListView*>(widget);
    const protocolbuffers::ListViewOptions& options = nodeTree.listviewoptions();
    
    
    
    std::string protocolBuffersPath = GUIReader::shareReader()->getFilePath();
    
    
    bool backGroundScale9Enable = options.backgroundscale9enable();
    listView->setBackGroundImageScale9Enabled(backGroundScale9Enable);
    
    int cr;
    int cg;
    int cb;
    int scr;
    int scg;
    int scb;
    int ecr;
    int ecg;
    int ecb;
    
    cr = options.has_bgcolorr() ? options.bgcolorr() : 150;
    cg = options.has_bgcolorg() ? options.bgcolorg() : 150;
    cb = options.has_bgcolorb() ? options.bgcolorb() : 255;
    
    scr = options.has_bgstartcolorr() ? options.bgstartcolorr() : 255;
    scg = options.has_bgstartcolorg() ? options.bgstartcolorg() : 255;
    scb = options.has_bgstartcolorb() ? options.bgstartcolorb() : 255;
    
    ecr = options.has_bgendcolorr() ? options.bgendcolorr() : 150;
    ecg = options.has_bgendcolorg() ? options.bgendcolorg() : 150;
    ecb = options.has_bgendcolorb() ? options.bgendcolorb() : 255;
    
    
    float bgcv1 = options.vectorx();
    float bgcv2 = options.has_vectory() ? options.vectory() : -0.5f;
    listView->setBackGroundColorVector(ccp(bgcv1, bgcv2));
    
    int co = options.bgcoloropacity();
    
    int colorType = options.colortype();
    
    listView->setBackGroundColorType((ui::LayoutBackGroundColorType)colorType);
    listView->setBackGroundColor(ccc3(scr, scg, scb),ccc3(ecr, ecg, ecb));
    listView->setBackGroundColor(ccc3(cr, cg, cb));
    listView->setBackGroundColorOpacity(co);
    
    
    const protocolbuffers::ResourceData& imageFileNameDic = options.backgroundimagedata();
    int imageFileNameType = imageFileNameDic.resourcetype();
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_b = protocolBuffersPath;
            const char* imageFileName = imageFileNameDic.path().c_str();
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
            listView->setBackGroundImage(imageFileName_tp);
            break;
        }
        case 1:
        {
            const char* imageFileName = imageFileNameDic.path().c_str();
            listView->setBackGroundImage(imageFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
            
        default:
            break;
    }
    
    
    const protocolbuffers::WidgetOptions& widgetOptions = nodeTree.widgetoptions();
    int bgimgcr = widgetOptions.has_colorr() ? widgetOptions.colorr() : 255;
    int bgimgcg = widgetOptions.has_colorg() ? widgetOptions.colorg() : 255;
    int bgimgcb = widgetOptions.has_colorb() ? widgetOptions.colorb() : 255;
    listView->setBackGroundImageColor(ccc3(bgimgcr, bgimgcg, bgimgcb));
    
    int bgimgopacity = widgetOptions.opacity();
    listView->setBackGroundImageOpacity(bgimgopacity);
    
    if (backGroundScale9Enable)
    {
        float cx = options.capinsetsx();
        float cy = options.capinsetsy();
        float cw = options.has_capinsetswidth() ? options.capinsetswidth() : 1;
        float ch = options.has_capinsetsheight() ? options.capinsetsheight() : 1;
        listView->setBackGroundImageCapInsets(CCRectMake(cx, cy, cw, ch));
    }
    
    
    
    
    float innerWidth = options.has_innerwidth() ? options.innerwidth() : 200;
    float innerHeight = options.has_innerheight() ? options.innerheight() : 200;
    listView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
    listView->setBounceEnabled(options.bounceenable());
    
    
    int direction = options.has_direction() ? options.direction() : 2;
	listView->setDirection((ui::SCROLLVIEW_DIR)direction);
    
    int gravityValue = options.has_gravity() ? options.gravity() : 3;
    ui::ListViewGravity gravity = ((ui::ListViewGravity)gravityValue);
    listView->setGravity(gravity);
    
    float itemMargin = options.itemmargin();
    listView->setItemsMargin(itemMargin);
}


NS_CC_EXT_END
