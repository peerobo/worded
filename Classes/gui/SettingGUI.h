#pragma once
#include "OneBtDlg.h"

class SettingGUI : public OneBtDlg
{
private:
	SettingGUI();
	void onTouchedHard(bool isTouchedHard);
public:
	CREATE_FUNC(SettingGUI);	
	void show() override;
};
