/*
 * CatChooser.h
 *
 *  Created on: Sep 15, 2015
 *      Author: hachan
 */

#ifndef TABLEMODE_CATCHOOSER_H_
#define TABLEMODE_CATCHOOSER_H_

#include <cocos2d.h>

class CatChooser: public cocos2d::Layer {
private:
	const int LAYER_GUI;
	const int LAYER_LBL;
	CatChooser();
	void animateIn();
    Node* createCatItem(const std::string& cat, int type);
    bool catTouchBegan(cocos2d::Touch* t, cocos2d::Event* e);
    void catTouchEnd(cocos2d::Touch* t, cocos2d::Event* e, std::string cat);
	void onBackScreen();
public:
	CREATE_FUNC(CatChooser);
	void update(float dt) override;

};

#endif /* TABLEMODE_CATCHOOSER_H_ */
