#pragma once
#include "../base/DlgMgr.h"

class OneBtDlg : public Dlg
{
protected:
	OneBtDlg();	
	void onBtClick();
public:
	CREATE_FUNC(OneBtDlg);
	std::function<void()> onBtClickCB;
	void setData(const std::string& title, const std::string& btName);
	virtual void show();
};
