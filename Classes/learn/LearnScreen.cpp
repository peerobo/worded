#include "LearnScreen.h"
#include "../Constants.h"
#include "../IntroScreen.h"
#include "../base/comp/FScrollList.h"
#include "../WordedApp.h"

LearnScreen::LearnScreen() : LAYER_GUI(2), LAYER_LBL(3), LAYER_CAT(4)
{
	auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_ONE);
	Size s = util::graphic::getScreenSize();
	bg->setPosition(s.width / 2, s.height / 2);
	addChild(bg, 1);
	bg->setTag(199);

	std::vector<int> v({ LAYER_GUI,LAYER_LBL,LAYER_CAT });
	util::graphic::generateLayerWithTag(this, v, 2);

	Vector<FiniteTimeAction*> vec;
	vec.pushBack(DelayTime::create(0.3f));
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(LearnScreen::animateIn, this)));
	runAction(Sequence::create(vec));
	cat = "";
	needTut = true;
}

void LearnScreen::animateIn()
{
	util::common::stopMusic(true);
	Size s = util::graphic::getScreenSize();

	auto lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, "Learn");
	lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	lbl->setPosition(s.width / 2, s.height - 100);
	getChildByTag(LAYER_LBL)->addChild(lbl);
    lbl->setTag(10);
	util::effects::reveal(lbl);	

	auto backBt = ui::Button::create();
	getChildByTag(LAYER_GUI)->addChild(backBt);
    backBt->setTag(9);
	backBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_BACK), ui::Widget::TextureResType::PLIST);
	backBt->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	backBt->setPosition(Vec2(100, s.height - 100));
	util::graphic::addClickBtCallback(backBt, CC_CALLBACK_0(LearnScreen::onBackScreen, this));
	util::effects::reveal(backBt);

	Size sList(s.width - 100, s.height - 400);
	FScrollList* list = FScrollList::create();
	list->initView(sList, 30, 0.07f, FScrollList::SCROLL_TYPE::VERTICAL);
	list->setTag(99);
	getChildByTag(LAYER_CAT)->addChild(list);
	list->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);	
	list->setPosition(50, 0);	

	Node* wordsContainer = Node::create();
	wordsContainer->setContentSize(sList);
	getChildByTag(LAYER_CAT)->addChild(wordsContainer);
	wordsContainer->setPosition(list->getPosition());
	wordsContainer->setVisible(false);
	wordsContainer->setTag(100);

	showList();
}

void _internalLearnChangeScene()
{
	util::graphic::changeSceneWithLayer(IntroScreen::create());
}

Node* LearnScreen::createItem(CONST_STR cat, int type, int w)
{
	Node* node = Node::create();

	auto bg = util::graphic::getSprite(StringUtils::format("%s%d", Constants::ASS_ICO_CAT_BG, type));
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Size itemSize = bg->getContentSize();
	bg->setPosition(0, 0);
	node->addChild(bg, 0);

	auto catIcon = util::graphic::getSprite(StringUtils::format("%s%s", Constants::ASS_ICO_PREFIX, cat.c_str()));
	catIcon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	catIcon->setPosition(itemSize.width / 2, itemSize.height / 2);
	node->addChild(catIcon, 1);

	std::string catClone = cat;
	util::common::capitalize(catClone);
	auto lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, catClone);
	lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	lbl->setPosition(itemSize.width+100, itemSize.height/2);
	lbl->setScale(0.7f);
	node->addChild(lbl, 2);

	auto spr = util::graphic::getSprite(Constants::ASS_BT_BACK);
	spr->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	spr->setFlippedX(true);
	spr->setPosition(Vec2(w - 10, itemSize.height / 2));
	node->addChild(spr, 0);

	util::graphic::addNodeClickCallback(node, CC_CALLBACK_0(LearnScreen::showWords, this, cat), false);

	itemSize.width = w;
	node->setContentSize(itemSize);
	return node;
}

void LearnScreen::showWords(CONST_STR cat)
{	
	this->cat = cat;
	util::graphic::loadTexAtl(cat, false);
	WordedApp::loadSound(cat);

	auto container = getChildByTag(LAYER_CAT)->getChildByTag(100);
	container->setVisible(true);

	util::common::playSound(Constants::ASS_SND_CLICK, false);
	isListCat = false;
	auto list = dynamic_cast<FScrollList*>(getChildByTag(LAYER_CAT)->getChildByTag(99));
	list->clearAllItems();
	list->setVisible(false);

	words = WordedApp::getAllWords(cat);
	idxWord = 0;
	setWord();
}

void LearnScreen::advanceWord(bool next)
{
	idxWord = idxWord + (next ? 1 : -1);
	int size = words.size();
	idxWord = idxWord >= size ? size - 1 : idxWord;
	idxWord = idxWord < 0 ? 0 : idxWord;
	setWord();
}

void LearnScreen::setWord()
{
	auto container = getChildByTag(LAYER_CAT)->getChildByTag(100);
	auto sList = container->getContentSize();

	auto v = container->getChildren();
	for (auto c : v)
	{
		util::effects::fadeAndRemove(c, 0.5f);
	}

	if (idxWord > 0)
	{
		ui::Button* bt = Button::create();
		bt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_BACK), ui::Widget::TextureResType::PLIST);
		bt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		container->addChild(bt, 0);
		bt->setPosition(Vec2(0, sList.height / 2));
		util::graphic::addClickBtCallback(bt, CC_CALLBACK_0(LearnScreen::advanceWord, this, false));
	}
	
	int size = words.size();
	if (idxWord < size-1)
	{
		ui::Button* bt = Button::create();
		bt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_BACK), ui::Widget::TextureResType::PLIST);
		bt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		bt->setFlippedX(true);
		container->addChild(bt, 0);
		bt->setPosition(Vec2(sList.width - 100, sList.height / 2));
		util::graphic::addClickBtCallback(bt, CC_CALLBACK_0(LearnScreen::advanceWord, this, true));
	}

	// word
	auto bg = util::graphic::getSprite(Constants::ASS_ICO_BG_WORD);
	bg->setPosition(sList.width / 2, sList.height / 2 + 200);
	bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	auto bgSize = bg->getContentSize();
	container->addChild(bg, 0);
	util::graphic::addNodeClickCallback(bg, std::bind(&WordedApp::playSound,words[idxWord]) , true);

	std::string wordStr = words[idxWord];
	util::common::capitalize(wordStr);
	Label* lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL,wordStr);
	lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	lbl->setPosition(sList.width / 2, (sList.height - bgSize.height) / 2 - 100);
	container->addChild(lbl, 2);

	Node* icon = util::graphic::getSprite(words[idxWord]);
	icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	container->addChild(icon,1);	
	bgSize.width -= 50;
	bgSize.height -= 50;
	icon->setScale(util::graphic::fit(bgSize, icon));
	icon->setPosition(bg->getPosition());

	if (needTut)
	{
		auto tut = util::graphic::getSprite(Constants::ASS_ICO_TOUCHME);
		container->addChild(tut, 0);
		Vec2 pos = bg->getPosition();		
		tut->setPosition(pos);
		tut->setOpacity(0);
		tut->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		Vector<FiniteTimeAction*> vact;
		vact.pushBack(DelayTime::create(0.5f));
		vact.pushBack(FadeIn::create(0.4f));		
		vact.pushBack(Blink::create(0.7f, 2));
		vact.pushBack(DelayTime::create(0.7f));
		vact.pushBack(FadeOut::create(0.4f));
		vact.pushBack(RemoveSelf::create());
		tut->runAction(Sequence::create(vact));
		needTut = false;
	}

	util::effects::reveal(bg,0.5f);
	util::effects::reveal(icon, 0.5f);
	util::effects::reveal(lbl, 0.5f);

	WordedApp::playSound(words[idxWord]);
}

void LearnScreen::showList()
{	
	if (cat != "")
	{
		util::graphic::removeTexAtl(cat);
		WordedApp::unloadSound(cat);
		cat = "";
	}
	
	auto container = getChildByTag(LAYER_CAT)->getChildByTag(100);
	container->setVisible(true);
	container->removeAllChildren();

	isListCat = true;
	auto list = dynamic_cast<FScrollList*>( getChildByTag(LAYER_CAT)->getChildByTag(99));
	list->setVisible(true);

	int w = list->getContentSize().width;
	auto v = WordedApp::getAllCats();
	int count = 0;
	for (auto s : v)
	{		
		auto node = createItem(s, count % 4, w);
		count++;
		list->addAutoPosItem(node);
		node->setOpacity(0);
		node->runAction(FadeIn::create(count*0.2f + 0.2f));
	}
}

void LearnScreen::onBackScreen()
{
	if (isListCat)
	{
        auto lbl = getChildByTag(LAYER_LBL)->getChildByTag(10);
        util::effects::fadeAndRemove(lbl, 0.5f);
        auto bt = getChildByTag(LAYER_GUI)->getChildByTag(9);
        util::effects::fadeAndRemove(bt, 0.5f);

		auto v = getChildren();
		int vsize = v.size();
		for (auto c : v)
		{
			int tag = c->getTag();
			if (tag == 199)
				util::effects::fadeAndRemove(c, 1, std::bind(&_internalLearnChangeScene));
			else if (tag != 2)
				util::effects::fadeAndRemove(c, 0.5f);
		}

		auto list = dynamic_cast<FScrollList*>(getChildByTag(LAYER_CAT)->getChildByTag(99));
		list->clearAllItems();

		// cache next bg
		auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_INTRO);
		Size s = util::graphic::getScreenSize();
		bg->setPosition(s.width / 2, s.height / 2);
		addChild(bg, 0);
	}
	else
	{
		showList();
	}
	
	util::common::playSound(Constants::ASS_SND_CLICK, false);
}