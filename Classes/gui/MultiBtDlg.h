#pragma once
#include "../base/DlgMgr.h"
#include <vector>

class MultiBtDlg : public Dlg
{
protected:	
	void onBtClick(int idx);
public:
	CREATE_FUNC(MultiBtDlg);
	std::function<void(int idx)> onBtClickCB;
	void setData(const std::string& title, const std::string& msg,  std::vector<std::string> bts);
	virtual void show();
};