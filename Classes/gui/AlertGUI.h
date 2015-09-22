//
//  AlertGUI.hpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/22/15.
//
//

#ifndef AlertGUI_hpp
#define AlertGUI_hpp

#include "OneBtDlg.h"
#include "../base/Util.h"

USING_NS_CC;

class AlertGUI : public OneBtDlg
{
public:
    CREATE_FUNC(AlertGUI);
    void setMsg(CONST_STR msg);
};

#endif /* AlertGUI_hpp */
