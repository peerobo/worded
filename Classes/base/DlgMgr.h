#include <cocos2d.h>
#include "Dlg.h"
#pragma once
USING_NS_CC;

class DlgMgr
{
private:
	static DlgMgr* self;
	std::vector<Dlg*> dlgs;
	DlgMgr();
public:	
	static DlgMgr* getInstance();
	Dlg* getCurrentDlg();
	void showDlg(Dlg* dlg, int layer = 100, bool withAnimation = false, bool withModalBG = true);
	std::vector<Dlg*> getDlgsList();
	void closeDlg(Dlg* dlg, bool withAnimation = false);
	bool removeFromList(Dlg* dlg);
	void clearAll();
};