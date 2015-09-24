#include <cocos2d.h>
#include <ui/UILayout.h>
#include <vector>

USING_NS_CC;
using namespace cocos2d::ui;
#pragma once
class FScrollList : public Node
{	
public:
	enum SCROLL_TYPE{
		BOTH,
		VERTICAL,
		HORIZONTAL
	};
	~FScrollList();
	CREATE_FUNC(FScrollList);	
	void initView(Size viewSize, float spacing, float updateInterval, SCROLL_TYPE direction, int row = -1, int col = -1, bool snapToPage =false);
	void addAutoPosItem(Node* node);
	void addItem(Node* node, Vec2 pos);
	void updateView();
	void clearAllItems();
	bool checkItemVisible(Node* node);
	float spacing;
	Vector<Node*> getAllItems();
	Node* getContainer();
	int getCurrentPage();
	int getTotalPage();
private:	
	const int BOUNDING_BACK;
	int maxCol;
	int maxRow;
    bool snapToPage;
	float rate;
	float updateInterval;
	bool initAlready;
	Vec2 goalOffset;
	Vec2 beganOffset;
	Vec2 offset;	
	SCROLL_TYPE direction;
	Size realSize;
	bool onTouchBegan(Touch* t, Event* e);
	void onTouchMoved(Touch* t, Event* e);
	void onTouchEnded(Touch* t, Event* e);
	void calculateRealSize();
	Node* container;
	Layout* viewPort;
	FScrollList();
};