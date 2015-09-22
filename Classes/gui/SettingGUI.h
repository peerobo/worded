#pragma once
#include "OneBtDlg.h"

class SettingGUI : public OneBtDlg
{
private:
	SettingGUI();
	void onTouchedHard(bool isTouchedHard, bool isTouchText);
public:
	CREATE_FUNC(SettingGUI);	
	void show() override;
};
