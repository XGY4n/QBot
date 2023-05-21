#include "UIAMsg.h"

UIAMsg::UIAMsg()
{
    CoInitialize(NULL);

    CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**)&pAutomation);

    pAutomation->GetRootElement(&pRootElement);

    VARIANT varProp1;
    varProp1.vt = VT_BSTR;
    varProp1.bstrVal = SysAllocString(L"TXGuiFoundation");
    pAutomation->CreatePropertyCondition(UIA_ClassNamePropertyId, varProp1, &pNameCondition);

    VARIANT varProp2;
    varProp2.vt = VT_BSTR;
    varProp2.bstrVal = SysAllocString(L"消息管理器");
    pAutomation->CreatePropertyCondition(UIA_NamePropertyId, varProp2, &pClassNameCondition);

    pAutomation->CreateAndCondition(pNameCondition, pClassNameCondition, &pAndCondition);

    pRootElement->FindFirst(TreeScope_Children, pAndCondition, &pWindow);

    VARIANT varProp;
    varProp.vt = VT_BSTR;
    varProp.bstrVal = SysAllocString(L"IEMsgView");
    pAutomation->CreatePropertyCondition(UIA_NamePropertyId, varProp, &pCondition);

    pRootElement->FindFirst(TreeScope_Descendants, pCondition, &pListElement);

}

UIAMsg::~UIAMsg()
{
    pRootElement->Release();
    pAutomation->Release();
    CoUninitialize();
}

std::string UIAMsg::UIAGet_Msg_String()
{
    std::string error = "error";
    if (pListElement != NULL)
    {
        // 获取列表控件的子元素
        IUIAutomationTreeWalker* pControlWalker;
        pAutomation->get_ControlViewWalker(&pControlWalker);
        IUIAutomationElement* pItemElement;
        pControlWalker->GetLastChildElement(pListElement, &pItemElement);
        if (pItemElement != NULL)
        {
            // 获取并处理最后一个列表项的信息
            BSTR bstrName;
            pItemElement->get_CurrentName(&bstrName);
            //wprintf(L"%s\n", bstrName);

            std::wstring ws(bstrName, ::SysStringLen(bstrName));
            ::SysFreeString(bstrName);
            int bstrLength = SysStringLen(bstrName);
            int stringLength = WideCharToMultiByte(CP_ACP, 0, bstrName, bstrLength, NULL, 0, NULL, NULL);
            char* buffer = new char[stringLength + 1];

            WideCharToMultiByte(CP_ACP, 0, bstrName, bstrLength, buffer, stringLength, NULL, NULL);

            buffer[stringLength] = '\0';
            std::string str(buffer);
            pItemElement->Release();
            delete[] buffer;
            SysFreeString(bstrName);
            return str;
        }
    }
    return error;
}
