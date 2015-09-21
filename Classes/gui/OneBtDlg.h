#pragma once
#include "../base/DlgMgr.h"

class OneBtDlg : public Dlg
{
private:
	OneBtDlg();	
	void onBtClick();
public:
	CREATE_FUNC(OneBtDlg);
	std::function<void()> onBtClickCB;
	void setData(const std::string& title, const std::string& btName);
	void show();
};
