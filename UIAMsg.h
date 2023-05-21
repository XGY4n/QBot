#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <UIAutomation.h>
#include <iostream>
class UIAMsg
{
public:
    UIAMsg();
    ~UIAMsg();
public:
    std::string UIAGet_Msg_String();

public:
    IUIAutomationElement* pRootElement;
    IUIAutomation* pAutomation;
    IUIAutomationCondition* pNameCondition;
    IUIAutomationCondition* pAndCondition;
    IUIAutomationCondition* pClassNameCondition;
    IUIAutomationCondition* pCondition;
    IUIAutomationElement* pListElement;
    IUIAutomationElement* pWindow;
};

