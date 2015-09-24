#include "FScrollList.h"
#include "../Util.h"
#include <math.h>

FScrollList::FScrollList() : BOUNDING_BACK(850)
{
	initAlready = false;
	realSize.width = 0;
	realSize.height = 0;
	rate = -1;
}

bool FScrollList::onTouchBegan(Touch* t, Event* e)
{

    if (util::graphic::checkHit(t, this))
	{
        if(snapToPage)
        {
            beganOffset = goalOffset;
        }
        else
        {
            goalOffset = offset;
            beganOffset = goalOffset;
        }
			
		rate = 0;
		return true;
	}
	return false;
}

void FScrollList::onTouchMoved(Touch* t, Event* e)
{
	Size s = getContentSize();
	if (direction == SCROLL_TYPE::BOTH)
	{
		goalOffset.x = beganOffset.x + (t->getLocation().x - t->getStartLocation().x);
		goalOffset.y = beganOffset.y + (t->getLocation().y - t->getStartLocation().y);				
		goalOffset.x = (realSize.width + goalOffset.x < s.width - BOUNDING_BACK) ?
			(s.width - BOUNDING_BACK - realSize.width) : (goalOffset.x > BOUNDING_BACK ? BOUNDING_BACK : goalOffset.x);
		goalOffset.y = (realSize.height + goalOffset.y < s.height - BOUNDING_BACK) ?
			(s.height - BOUNDING_BACK - realSize.height) : (goalOffset.y > BOUNDING_BACK ? BOUNDING_BACK : goalOffset.y);
	}
	else if (direction == SCROLL_TYPE::HORIZONTAL)
	{
		goalOffset.x = beganOffset.x + (t->getLocation().x - t->getStartLocation().x);		
		goalOffset.x = (realSize.width + goalOffset.x < s.width - BOUNDING_BACK) ?
			(s.width - BOUNDING_BACK - realSize.width) : (goalOffset.x > BOUNDING_BACK ? BOUNDING_BACK : goalOffset.x);
	}
	else
	{
		goalOffset.y = beganOffset.y + (t->getLocation().y - t->getStartLocation().y);				
		goalOffset.y = (realSize.height + goalOffset.y < s.height - BOUNDING_BACK) ?
			(s.height - BOUNDING_BACK - realSize.height) : (goalOffset.y > BOUNDING_BACK ? BOUNDING_BACK : goalOffset.y);
	}	

}

void FScrollList::onTouchEnded(Touch* t, Event* e)
{
    if (util::graphic::checkTouchStill(t))
	{
		e->stopPropagation();
	}
	Vec2 pos = t->getLocation();
	Vec2 posStart = t->getStartLocation();
	pos.subtract(posStart);
	if (rate == 0)
		rate = 0.05f;
	float distance = pos.length();
	float speed = distance / rate;
	float speedFlat = 1500;
	/*if (rate < 1 && distance > 120)
	{*/
	Size s = getContentSize();	
	if (direction == SCROLL_TYPE::BOTH)
	{
		float disX = t->getLocation().x - t->getStartLocation().x;
		float disY = t->getLocation().y - t->getStartLocation().y;
		goalOffset.x = beganOffset.x + disX / (speedFlat / speed);
		goalOffset.y = beganOffset.y + disY / (speedFlat / speed);
		goalOffset.x = realSize.width < s.width ? 0 : ( (realSize.width + goalOffset.x < s.width) ?
			(s.width - realSize.width) : (goalOffset.x > 0 ? 0 : (std::abs(goalOffset.x - beganOffset.x) < std::abs(disX) ? (beganOffset.x + disX) : goalOffset.x)));
		goalOffset.y = realSize.height < s.height ? (s.height - realSize.height) : ((realSize.height + goalOffset.y < s.height) ?
			(s.height - realSize.height) : (goalOffset.y > 0 ? 0 : (std::abs(goalOffset.y - beganOffset.y) < std::abs(disY) ? (beganOffset.y + disY) : goalOffset.y)));
	}
	else if (direction == SCROLL_TYPE::HORIZONTAL)
	{
		float disX = t->getLocation().x - t->getStartLocation().x;
        if(snapToPage)
        {
            if(std::abs(disX) > s.width/3)
            {
                goalOffset.x = goalOffset.x > 0 ? 0 :
                    (beganOffset.x +
                        ( goalOffset.x < beganOffset.x ? (realSize.width > (std::abs(beganOffset.x) + s.width) ? -s.width : 0) : s.width));
//                log("to hon");
            }
            else
            {
                goalOffset.x = beganOffset.x;
//                log("be hon");
            }
        }
        else
        {
            goalOffset.x = beganOffset.x + disX / (speedFlat / speed);
            goalOffset.x = realSize.width < s.width ? 0 : ((realSize.width + goalOffset.x < s.width) ?
                                                           (s.width - realSize.width) : (goalOffset.x > 0 ? 0 : (std::abs(goalOffset.x - beganOffset.x) < std::abs(disX) ? (beganOffset.x + disX) : goalOffset.x)));
        }
	}
	else
	{
       
		float disY = t->getLocation().y - t->getStartLocation().y;
        if(snapToPage)  // not impliment
        {
           
        }
        else
        {
            goalOffset.y = beganOffset.y + disY / (speedFlat/speed);
            goalOffset.y = realSize.height < s.height ? (s.height - realSize.height) : ((realSize.height + goalOffset.y < s.height) ?
                                                                                        (s.height - realSize.height) : (goalOffset.y > 0 ? 0 : (std::abs(goalOffset.y - beganOffset.y) < std::abs(disY) ? (beganOffset.y + disY) : goalOffset.y)));
        }
		
	}		
	rate = -1;	
	//}
}

void FScrollList::calculateRealSize()
{
	float maxX,maxY;
	maxX = maxY = 0;
	Vector<Node*> children = container->getChildren();
	for (auto child : children)
	{
		Size childSize = child->getContentSize();
		childSize.width *= child->getScaleX();
		childSize.height *= child->getScaleY();
		Vec2 anchor = child->getAnchorPoint();
		float tmp = child->getPositionX() + childSize.width*(1-anchor.x);
		maxX = tmp > maxX ? tmp : maxX;
		tmp = child->getPositionY() + childSize.height*(1 - anchor.y);
		maxY = tmp > maxY ? tmp : maxY;
	}
	realSize.width = maxX;
	realSize.height = maxY;
}

void FScrollList::initView(Size viewSize, float spacing, float updateInterval, SCROLL_TYPE direction, int row, int col, bool snapToPage)
{
	if (!initAlready)
	{
		viewPort = Layout::create();
		viewPort->setContentSize(viewSize);
		viewPort->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		viewPort->setClippingEnabled(true);
		this->addChild(viewPort);		
		this->setContentSize(viewSize);
		this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		container = Node::create();
		container->setContentSize(viewSize);
		viewPort->addChild(container);

		EventListenerTouchOneByOne* touchEvtLis = EventListenerTouchOneByOne::create();
		touchEvtLis->onTouchBegan = CC_CALLBACK_2(FScrollList::onTouchBegan, this);
		touchEvtLis->onTouchMoved = CC_CALLBACK_2(FScrollList::onTouchMoved, this);
		touchEvtLis->onTouchEnded = CC_CALLBACK_2(FScrollList::onTouchEnded, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvtLis, this);
        this->snapToPage = snapToPage;
		this->spacing = spacing;
		this->direction = direction;
		maxCol = col;
		maxRow = row;
		auto act = RepeatForever::create(Sequence::create(DelayTime::create(updateInterval),CallFunc::create(CC_CALLBACK_0(FScrollList::updateView,this)),NULL));
		runAction(act);
		this->updateInterval = updateInterval;
	}
	
}

void FScrollList::addAutoPosItem(Node* node)
{
	Vector<Node*> v = container->getChildren();
	long countChildren = v.size();
	Size childSize = node->getContentSize();	
	childSize.width *= node->getScaleX();
	childSize.height *= node->getScaleY();
	Vec2 anchorPt = node->getAnchorPoint();
	Vec2 pos;	
	
	   if(maxRow != -1 || maxCol != -1)
        {
            long currRow = -1;
            long currCol = -1;
            if(maxCol != -1) // not implement top-bottom + left-right
            {
                currRow = countChildren / maxCol;
                currCol = countChildren % maxCol;
            }
            else if(maxRow != -1) // implement top-bottom + left-right
            {
                currCol = countChildren / maxRow;
                currRow = (maxRow-1) - countChildren % maxRow;
            }
            pos.x = childSize.width* anchorPt.x + (spacing + childSize.width)*currCol;
            pos.y = childSize.height* anchorPt.y + (spacing+ childSize.height)*currRow;
        }
        else if (countChildren == 0)
        {
            pos.x = childSize.width*anchorPt.x;
            pos.y = childSize.height*anchorPt.y;
        }
        else
        {
            if (direction == SCROLL_TYPE::HORIZONTAL)
            {
                pos.x = realSize.width + spacing + childSize.width* anchorPt.x;
            }
            else
            {
                float shiftY = spacing + childSize.height;
                for (auto child : container->getChildren())
                {
                    child->setPositionY(child->getPositionY() + shiftY);
                }			
                pos.y = childSize.height*anchorPt.y;
            }
        }
	
	addItem(node, pos);	
}

int FScrollList::getCurrentPage()
{
	if (direction == HORIZONTAL)
	{
		return std::abs(offset.x) / (float)getContentSize().width;
	}
	else if (direction == VERTICAL)
	{
		return std::abs(offset.y) / (float)getContentSize().height;
	}
	else
	{
		return 0;
	}
}

int FScrollList::getTotalPage()
{
	if (direction == HORIZONTAL)
	{
		return std::ceilf(realSize.width / (float)getContentSize().width);
	}
	else if(direction == VERTICAL)
	{
		return std::ceilf(realSize.height / (float)getContentSize().height);
	}
	else
	{
		return 0;
	}
}

void FScrollList::clearAllItems()
{
	offset.x = goalOffset.x = 0;
	offset.y = goalOffset.y = 0;
	realSize.width = 0;
	realSize.height = 0;
	container->removeAllChildren();
}

Node* FScrollList::getContainer()
{
	return container;
}

Vector<Node*> FScrollList::getAllItems()
{
	return container->getChildren();
}

bool FScrollList::checkItemVisible(Node* node)
{
	Rect rect = node->getBoundingBox();
	rect.origin = container->convertToWorldSpace(rect.origin);
	Rect rectContainer = viewPort->getBoundingBox();
	rectContainer.origin = this->convertToWorldSpace(rectContainer.origin);
	return rectContainer.containsPoint(rect.origin)
		&& rectContainer.containsPoint(Vec2(rect.getMinX(),rect.getMaxY()))
		&& rectContainer.containsPoint(Vec2(rect.getMaxX(), rect.getMinY()))
		&& rectContainer.containsPoint(Vec2(rect.getMaxX(), rect.getMaxY()));
}

void FScrollList::addItem(Node* node, Vec2 pos)
{
	container->addChild(node);
	node->setPosition(pos);
	calculateRealSize();
	if (direction == SCROLL_TYPE::VERTICAL)
	{
		offset.y = goalOffset.y = getContentSize().height - realSize.height;
	}
}

void FScrollList::updateView()
{
	if (rate > -1)
	{
		rate += updateInterval;
	}
	Vec2 tmpVec(goalOffset);
	tmpVec.subtract(offset);
	if (tmpVec.length() > 2)
	{
		offset.x += (goalOffset.x - offset.x) / 3;
		offset.y += (goalOffset.y - offset.y) / 3;
	}
	else
	{
		offset = goalOffset;
	}

	container->setPosition(offset);
}

FScrollList::~FScrollList()
{
	viewPort = NULL;
	container = NULL;
}
