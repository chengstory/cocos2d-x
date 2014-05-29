

#include "CheckBoxReader.h"
#include "../../../GUI/UIWidgets/UICheckBox.h"

NS_CC_EXT_BEGIN

static CheckBoxReader* instanceCheckBoxReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(CheckBoxReader)

CheckBoxReader::CheckBoxReader()
{
    
}

CheckBoxReader::~CheckBoxReader()
{
    
}

CheckBoxReader* CheckBoxReader::getInstance()
{
    if (!instanceCheckBoxReader)
    {
        instanceCheckBoxReader = new CheckBoxReader();
    }
    return instanceCheckBoxReader;
}

void CheckBoxReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    

    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    ui::CheckBox* checkBox = (ui::CheckBox*)widget;
    
    const rapidjson::Value& backGroundDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxData");
    int backGroundType = DICTOOL->getIntValue_json(backGroundDic, "resourceType");
    switch (backGroundType)
    {
        case 0:
        {
            std::string tp_b = jsonPath;
            const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
            const char* backGroundFileName_tp = NULL; //backGroundFilePath.c_str(); //(backGroundFileName && (strcmp(backGroundFileName, "") != 0))?tp_b.append(backGroundFileName).c_str():NULL;
            std::string backGroundFilePath;
			if (backGroundFileName && (strcmp(backGroundFileName, "") != 0))
            {
                backGroundFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(backGroundFileName);
				backGroundFileName_tp = backGroundFilePath.c_str();
            }
			checkBox->loadTextureBackGround(backGroundFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
            checkBox->loadTextureBackGround(backGroundFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& backGroundSelectedDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxSelectedData");
    int backGroundSelectedType = DICTOOL->getIntValue_json(backGroundSelectedDic, "resourceType");
    switch (backGroundSelectedType)
    {
        case 0:
        {
            std::string tp_bs = jsonPath;
			std::string backGroundSelectedFilePath;
            const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
            const char* backGroundSelectedFileName_tp = NULL; //backGroundSelectedFilePath.c_str(); //(backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))?tp_bs.append(backGroundSelectedFileName).c_str():NULL;
            if (backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))
            {
                backGroundSelectedFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(backGroundSelectedFileName);
				backGroundSelectedFileName_tp = backGroundSelectedFilePath.c_str();
            }
			checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
            checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& frontCrossDic = DICTOOL->getSubDictionary_json(options, "frontCrossData");
    int frontCrossType = DICTOOL->getIntValue_json(frontCrossDic, "resourceType");
    switch (frontCrossType)
    {
        case 0:
        {
            std::string tp_c = jsonPath;
			std::string frontCrossFilePath;
            const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
            const char* frontCrossFileName_tp = NULL; //frontCrossFilePath.c_str(); //(frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))?tp_c.append(frontCrossFileName).c_str():NULL;
            if (frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))
            {
                frontCrossFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(frontCrossFileName);
				frontCrossFileName_tp = frontCrossFilePath.c_str();
            }
			checkBox->loadTextureFrontCross(frontCrossFileName_tp);
            break;
        }
        case 1:
        {
            const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
            checkBox->loadTextureFrontCross(frontCrossFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& backGroundDisabledDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxDisabledData");
    int backGroundDisabledType = DICTOOL->getIntValue_json(backGroundDisabledDic, "resourceType");
    switch (backGroundDisabledType)
    {
        case 0:
        {
            std::string tp_bd = jsonPath;
			std::string backGroundDisabledFilePath;
            const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
            const char* backGroundDisabledFileName_tp = NULL; //backGroundDisabledFilePath.c_str(); //(backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))?tp_bd.append(backGroundDisabledFileName).c_str():NULL;
			if (backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))
			{
                backGroundDisabledFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(backGroundDisabledFileName);
				backGroundDisabledFileName_tp = backGroundDisabledFilePath.c_str();
			}
			checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
            checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& frontCrossDisabledDic = DICTOOL->getSubDictionary_json(options, "frontCrossDisabledData");
    int frontCrossDisabledType = DICTOOL->getIntValue_json(frontCrossDisabledDic, "resourceType");
    switch (frontCrossDisabledType)
    {
        case 0:
        {
            std::string tp_cd = jsonPath;
			std::string frontCrossDisableFilePath;
            const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
            const char* frontCrossDisabledFileName_tp = NULL; //frontCrossDisableFilePath.c_str(); //(frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))?tp_cd.append(frontCrossDisabledFileName).c_str():NULL;
            if (frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))
            {
                frontCrossDisableFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(frontCrossDisabledFileName);
				frontCrossDisabledFileName_tp = frontCrossDisableFilePath.c_str();
            }
			checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
            checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }

    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}



NS_CC_EXT_END
