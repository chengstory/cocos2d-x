

#include "ScrollViewReader.h"
#include "../../../GUI/UIWidgets/ScrollWidget/UIScrollView.h"
#include "../../../Json/CSParseBinary.pb.h"

NS_CC_EXT_BEGIN

static ScrollViewReader* instanceScrollViewReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(ScrollViewReader)

ScrollViewReader::ScrollViewReader()
{
    
}

ScrollViewReader::~ScrollViewReader()
{
    
}

ScrollViewReader* ScrollViewReader::getInstance()
{
    if (!instanceScrollViewReader)
    {
        instanceScrollViewReader = new ScrollViewReader();
    }
    return instanceScrollViewReader;
}



void ScrollViewReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    LayoutReader::setPropsFromJsonDictionary(widget, options);
    
    
    ui::ScrollView* scrollView = (ui::ScrollView*)widget;
    
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth",200);
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight",200);
    scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
    
	int direction = DICTOOL->getFloatValue_json(options, "direction",1);
	scrollView->setDirection((ui::SCROLLVIEW_DIR)direction);
    
    scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
    
    
    LayoutReader::setColorPropsFromJsonDictionary(widget, options);
}

void ScrollViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    //TODO::need to refactor...
    LayoutReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
    
    ui::ScrollView* scrollView = static_cast<ui::ScrollView*>(widget);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    float innerWidth = 0.0f;
    float innerHeight = 0.0f;
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue(pCocoLoader);
        if (key == "innerWidth") {
            innerWidth = valueToFloat(value);
        }
        else if(key == "innerHeight"){
            innerHeight = valueToFloat(value);
        }else if(key == "direction"){
            scrollView->setDirection((ui::SCROLLVIEW_DIR)valueToInt(value));
        }else if(key == "bounceEnable"){
            scrollView->setBounceEnabled(valueToBool(value));
        }
        
    } //end of for loop
    scrollView->setInnerContainerSize(CCSize(innerWidth, innerHeight));
    
}

void ScrollViewReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
{
    WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
    
    ui::ScrollView* scrollView = static_cast<ui::ScrollView*>(widget);
    const protocolbuffers::ScrollViewOptions& options = nodeTree.scrollviewoptions();
    
    
    std::string protocolBuffersPath = GUIReader::shareReader()->getFilePath();
    
    bool backGroundScale9Enable = options.backgroundscale9enable();
    scrollView->setBackGroundImageScale9Enabled(backGroundScale9Enable);
    
    int cr;
    int cg;
    int cb;
    int scr;
    int scg;
    int scb;
    int ecr;
    int ecg;
    int ecb;
    
    cr = options.has_bgcolorr() ? options.bgcolorr() : 255;
    cg = options.has_bgcolorg() ? options.bgcolorg() : 150;
    cb = options.has_bgcolorb() ? options.bgcolorb() : 100;
    
    scr = options.has_bgstartcolorr() ? options.bgstartcolorr() : 255;
    scg = options.has_bgstartcolorg() ? options.bgstartcolorg() : 255;
    scb = options.has_bgstartcolorb() ? options.bgstartcolorb() : 255;
    
    ecr = options.has_bgendcolorr() ? options.bgendcolorr() : 255;
    ecg = options.has_bgendcolorg() ? options.bgendcolorg() : 150;
    ecb = options.has_bgendcolorb() ? options.bgendcolorb() : 100;
    
    
    float bgcv1 = options.vectorx();
    float bgcv2 = options.has_vectory() ? options.vectory() : -0.5f;
    scrollView->setBackGroundColorVector(ccp(bgcv1, bgcv2));
    
    int co = options.bgcoloropacity();
    
    int colorType = options.colortype();
    
    scrollView->setBackGroundColorType((ui::LayoutBackGroundColorType)colorType);
    scrollView->setBackGroundColor(ccc3(scr, scg, scb),ccc3(ecr, ecg, ecb));
    scrollView->setBackGroundColor(ccc3(cr, cg, cb));
    scrollView->setBackGroundColorOpacity(co);
    
    
    const protocolbuffers::ResourceData& imageFileNameDic = options.backgroundimagedata();
    int imageFileNameType = imageFileNameDic.resourcetype();
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_b = protocolBuffersPath;
            const char* imageFileName = imageFileNameDic.path().c_str();
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
            scrollView->setBackGroundImage(imageFileName_tp);
            break;
        }
        case 1:
        {
            const char* imageFileName = imageFileNameDic.path().c_str();
            scrollView->setBackGroundImage(imageFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
            
        default:
            break;
    }
    
    
    const protocolbuffers::WidgetOptions& widgetOptions = nodeTree.widgetoptions();
    int bgimgcr = widgetOptions.has_colorr() ? widgetOptions.colorr() : 255;
    int bgimgcg = widgetOptions.has_colorg() ? widgetOptions.colorg() : 255;
    int bgimgcb = widgetOptions.has_colorb() ? widgetOptions.colorb() : 255;
    scrollView->setBackGroundImageColor(ccc3(bgimgcr, bgimgcg, bgimgcb));
    
    int bgimgopacity = widgetOptions.opacity();
    scrollView->setBackGroundImageOpacity(bgimgopacity);
    
    if (backGroundScale9Enable)
    {
        float cx = options.capinsetsx();
        float cy = options.capinsetsy();
        float cw = options.has_capinsetswidth() ? options.capinsetswidth() : 1;
        float ch = options.has_capinsetsheight() ? options.capinsetsheight() : 1;
        scrollView->setBackGroundImageCapInsets(CCRectMake(cx, cy, cw, ch));
        
        scrollView->setLayoutType((ui::LayoutType)options.layouttype());
    }
    
    
    
    
    float innerWidth = options.has_innerwidth() ? options.innerwidth() : 200;
    float innerHeight = options.has_innerheight() ? options.innerheight() : 200;
    scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
    
	int direction = options.has_direction() ? options.direction() : 1;
	scrollView->setDirection((ui::SCROLLVIEW_DIR)direction);
    
    scrollView->setBounceEnabled(options.bounceenable());
}

NS_CC_EXT_END
