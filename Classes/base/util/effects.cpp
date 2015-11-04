#include "effects.h"
#include "graphic.h"

USING_NS_CC;

namespace util
{
	void effects::blink(Node* node, float delay, std::function<void()> cb)
	{		
		Vector<FiniteTimeAction*> v;
        if(delay > 0)
            v.pushBack(DelayTime::create(delay));
		v.pushBack(FadeOut::create(0.3f));
		v.pushBack(FadeIn::create(0.3f));
		v.pushBack(FadeOut::create(0.3f));
		v.pushBack(FadeIn::create(0.3f));
		if (cb)
			v.pushBack(CallFunc::create(cb));
		node->runAction(Sequence::create(v));
	}
	
	void effects::reveal(Node* node, float delay, std::function<void()> cb)
	{
		node->setOpacity(0);
		Vector<FiniteTimeAction*> v;
		if (delay > 0)
			v.pushBack(DelayTime::create(delay*0.2f));
		v.pushBack(FadeIn::create(0.6f));
		if (cb)
			v.pushBack(CallFunc::create(cb));
		node->runAction(Sequence::create(v));
		node->setPositionY(node->getPositionY() -100);
		node->runAction(MoveBy::create(0.6f + delay*0.2f, Vec2(0, 100)));
	}
    
    void effects::fadeAndRemove(cocos2d::Node* node, float time, std::function<void()> cb)
    {
        Vector<FiniteTimeAction*> v;
        v.pushBack(FadeOut::create(time));
		if (cb)
			v.pushBack(CallFunc::create(cb));
        v.pushBack(RemoveSelf::create());        
        node->runAction(Sequence::create(v));
    }

	void effects::zoomTo(cocos2d::Node * node, float delay, float startScale, float endScale, std::function<void()> cb)
	{
		Vector<FiniteTimeAction*> v;
		if (delay > 0)
			v.pushBack(DelayTime::create(delay));
		node->setScale(startScale);
		v.pushBack(ScaleTo::create(0.25f, endScale));
		if (cb)
			v.pushBack(CallFunc::create(cb));
		if (v.size() == 1)
			node->runAction(ScaleTo::create(0.25f, endScale));
		else
			node->runAction(Sequence::create(v));
	}
    
	void effects::disappear(Node* node, float delay, std::function<void()> cb)
	{
		Size s = graphic::getScreenSize();
		Vector<FiniteTimeAction*> v;
		if (delay > 0)
			v.pushBack(DelayTime::create(delay*0.2f));
		v.pushBack(MoveBy::create(0.7f, Vec2(-s.width, 0)));
		if (cb)
			v.pushBack(CallFunc::create(cb));
		v.pushBack(RemoveSelf::create());		
		node->runAction(Sequence::create(v));

		node->runAction(FadeOut::create(0.4f + delay*0.2f));
	}
}