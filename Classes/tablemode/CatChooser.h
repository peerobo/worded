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
	const int LAYER_CAT;
	CatChooser();
	void animateIn();
public:
	CREATE_FUNC(CatChooser);

};

#endif /* TABLEMODE_CATCHOOSER_H_ */
