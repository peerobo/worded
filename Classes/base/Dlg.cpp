#include "Dlg.h"
#include "DlgMgr.h"

void Dlg::removeFromParent()
{	
	Node::removeFromParent();	
}

void Dlg::removeFromParentAndCleanup(bool cleanup)
{
	DlgMgr::getInstance()->removeFromList(this);
	Node::removeFromParentAndCleanup(cleanup);
}