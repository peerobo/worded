#pragma once
#include "../base/DlgMgr.h"

class SettingGUI : public Dlg
{
private:
	SettingGUI();
public:
	CREATE_FUNC(SettingGUI);
	void show();
};
