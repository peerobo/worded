#include "DlgMgr.h"
#include "Util.h"

DlgMgr* DlgMgr::self = NULL;

DlgMgr::DlgMgr()
{
	dlgs = std::vector<Dlg*>();
}

DlgMgr* DlgMgr::getInstance()
{
	if (self == NULL)
	{
		self = new DlgMgr();
	}
	return self;
}

Dlg* DlgMgr::getCurrentDlg()
{
	size_t length = dlgs.size();
	if (length > 0)
		return dlgs.at(length-1);
	else
		return NULL;
}

std::vector<Dlg*> DlgMgr::getDlgsList()
{
	return dlgs;
}

bool DlgMgr::removeFromList(Dlg* dlg)
{
	std::vector<Dlg*>::iterator index = std::find(dlgs.begin(), dlgs.end(), dlg);
	if (index != dlgs.end())
	{
		dlgs.erase(index);
		return true;
	}
	else
	{
		return false;
	}
}

void DlgMgr::clearAll()
{
	dlgs.clear();
}

void DlgMgr::closeDlg(Dlg* dlg, bool withAnimation)
{		
	if (!withAnimation)
	{
		dlg->removeFromParent();
	}
	else
	{
		auto targetPos = dlg->getPosition();
		targetPos.x += util::graphic::getScreenSize().width;
		auto action = Sequence::create(EaseOut::create(MoveTo::create(0.3f, targetPos), 0.5f),
			CallFunc::create(CC_CALLBACK_0(Dlg::removeFromParent,dlg)),
			NULL);
		dlg->runAction(action);
	}	
}

void DlgMgr::showDlg(Dlg* dlg, int layer, bool withAnimation, bool withModalBG)
{	
	removeFromList(dlg);
	dlgs.push_back(dlg);
	util::graphic::showDisp(dlg,withModalBG,true,layer);

	// animation
	if (withAnimation)
	{
		auto targetPos = dlg->getPosition();
		dlg->setPositionX(targetPos.x + util::graphic::getScreenSize().width);
		dlg->runAction(EaseIn::create(MoveTo::create(0.3f, targetPos), 0.5f));
	}
	
} 