#pragma once
#include "../base/DlgMgr.h"
#include <vector>

class MultiBtDlg : public Dlg
{
protected:	
	bool alreadyCB;
	void onBtClick(int idx);
public:
	CREATE_FUNC(MultiBtDlg);
	std::function<void(int idx)> onBtClickCB;
    void setData(const std::string& title, const std::string& msg,  std::vector<std::string> bts, std::vector<bool> disable = {});
	virtual void show();
	void removeFromParentAndCleanup(bool clean) override;
};