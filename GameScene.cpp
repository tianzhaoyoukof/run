#include "GameScene.h"
#include "GameLayer.h"
#include "MyClassReader.h"

USING_NS_CC;

using namespace cocostudio::timeline;

BackGroundLayer* BackGroundLayer::createNode()
{
    auto node = BackGroundLayer::create();
    if(node)
        return node;
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool BackGroundLayer::init()
{
    if(!Node::init())
        return false;
    
    bg1_ = Sprite::create("background_1.png");
    bg2_ = Sprite::create("background_2.png");
    bg3_ = Sprite::create("background_3.png");
    
    bg1_->setPosition(Vec2(500,390));
    bg2_->setPosition(Vec2(bg1_->getPositionX() + 1024 , bg1_->getPositionY()));
    bg3_->setPosition(Vec2(bg2_->getPositionX() + 1024 , bg2_->getPositionY()));
    
    float speed = 20.0f;
    
    bg1_->runAction(MoveBy::create(speed,Vec2(-1024,0)));
    bg2_->runAction(MoveBy::create(speed,Vec2(-1024,0)));
    bg3_->runAction(MoveBy::create(speed,Vec2(-1024,0)));
    
    this->addChild(bg1_);
    this->addChild(bg2_);
    this->addChild(bg3_);
    
    this->runAction(Sequence::create(DelayTime::create(speed),CallFunc::create([=](){this->CallBack();}),NULL));
    
    return true;
}

void BackGroundLayer::CallBack()
{
    if(bg1_->getPositionX() < 0)
        bg1_->setPositionX(2548);
    else if(bg1_->getPositionX() < 1024)
        bg3_->setPositionX(2548);
    else
        bg2_->setPositionX(2548);
    float speed = 20.0f;
    bg1_->runAction(MoveBy::create(speed,Vec2(-1024,0)));
    bg2_->runAction(MoveBy::create(speed,Vec2(-1024,0)));
    bg3_->runAction(MoveBy::create(speed,Vec2(-1024,0)));
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(speed),CallFunc::create([=](){this->CallBack();}),NULL));
}

/***************************/

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Node::init())
	{
		return false;
	}

    //CSLoader::getInstance()->registReaderObject( "MyClassReader" , (ObjectFactory::Instance)MyClassReader::getInstance );
	auto rootNode = CSLoader::createNode("Layer/Layer.csb");
	auto player = dynamic_cast< Sprite* >(rootNode->getChildByTag(2));
	player->setVisible(false);
	this->addChild(rootNode);
    
    distance_ = dynamic_cast<TextAtlas*>(rootNode->getChildByTag(4));
    distance_->setString("0");
    
    over_board_ = dynamic_cast<Sprite*>(rootNode->getChildByTag(18));
    over_board_->setPositionX(-200.0f);
    restart_btn_ = dynamic_cast<Button*>(rootNode->getChildByTag(21));
    restart_btn_->setPositionX(-200.0f);
    restart_btn_->addTouchEventListener(CC_CALLBACK_2(GameScene::RestartCallBack, this));
    
    auto bg = BackGroundLayer::createNode();
    this->addChild(bg);

	game_layer_ = GameLayer::createNode();
    this->addChild(game_layer_);
    game_layer_->SetParent();
	


	/*auto r = Dictionary::create();
	CCDictionary* pDict_2 = new CCDictionary();
	//pDict_2->retain();
	pDict_2 = (CCDictionary*)pDict->objectForKey("special");

	auto pD = pDict->objectForKey("Obstacle3");
	auto arr = dynamic_cast<Array*>(pDict->objectForKey("Obstacle3"));
	for (int i = 0; i < arr->count(); ++ i)
	{
		log("%s", ((String*)arr->objectAtIndex(i))->getCString());
	}

	CCLOG("pDict_2:%s", ((CCString*)pDict_2->valueForKey("special_1"))->getCString());

	CCArray* pArray2 = new CCArray();
	//pArray2->retain();
	pArray2 = (CCArray*)pDict_2->objectForKey("special_2");
	for (int i = 0; i < pArray2->count(); i++)
	{
		CCLOG("pArray2%i:%s", i + 1, ((CCString*)pArray2->objectAtIndex(i))->getCString());
	}
	delete pArray2;
	CCArray* pArray3 = new CCArray();
	pArray3->retain();
	pArray3 = (CCArray*)pDict_2->objectForKey("special_3");
	for (int i = 0; i < pArray3->count(); i++)
	{
		CCLOG("pArray3%i:%s", i + 1, ((CCString*)pArray3->objectAtIndex(i))->getCString());
	}



	CCLOG("strings.xmlCounts:%d", pDict->count());
	CCLOG("pDict:%s", pDict);
	CCArray* pArray = new CCArray();
	pArray = pDict->allKeys();//把所有的键值付给pArray  
	for (int i = 0; i < pArray->count(); i++)
	{
		CCLOG("pArray%i:%s", i + 1, ((CCString*)pArray->objectAtIndex(i))->getCString());
	}*/


	/*auto player = CSLoader::createNode("Animate/RunAnimation.csb");
	player->setPosition(Vec2(200 , 200 ) );
	auto run = CSLoader::createTimeline("Animate/RunAnimation.csb");
	player->runAction(run);
	run->gotoFrameAndPlay(0);
	this->addChild(player);*/

	/*CSLoader::getInstance()->registReaderObject( "MyClassReader" , (ObjectFactory::Instance)MyClassReader::getInstance );

	auto rootNode = CSLoader::createNode("Layer/Layer.csb");
	//auto rootNode = CSLoader::createNode("Scene/MainScene.csb");
	//auto btn = dynamic_cast<Button*>( rootNode->getChildByTag(3) );
	//btn->addTouchEventListener(CC_CALLBACK_2(GameScene::PauseCallBack, this));
	//sp->setVisible(false);
	//sp->sta
	addChild(rootNode);

	Sprite* sp = Sprite::create();
	sp->setPosition(Vec2(100,100));
	this->addChild(sp);

	ActionTimeline *action = CSLoader::createTimeline("Layer/Layer.csb");
	rootNode->runAction(action);
	//sp->runAction( action );

	action->gotoFrameAndPlay(0,true);

	auto node2 = Sprite::create("restartDown.png");
	node2->setPosition(Vec2(100,100));
	ActionTimeline *action2 = CSLoader::createTimeline("Animate/Node.csb");
	node2->runAction(action2);
	this->addChild(node2);
	//sp->runAction( action );

	action2->gotoFrameAndPlay(0,true);

	//game_layer_ = GameLayer::createNode();
	//this->addChild(game_layer_);*/

	return true;
}

void GameScene::RestartCallBack(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        log("restart");
        game_layer_->Restart();
    }
}

void GameScene::ShowOverBoard()
{
    over_board_->runAction(MoveTo::create(0.5f, Vec2(640.0f,360.0f)));
    restart_btn_->runAction(Sequence::create(DelayTime::create(0.3f),MoveTo::create(0.3f, Vec2(640.0f,360.0f)), NULL));
}

void GameScene::HideOverBoard()
{
    over_board_->runAction(MoveTo::create(0.5f, Vec2(-400.0f,360.0f)));
    restart_btn_->runAction(MoveTo::create(0.3f, Vec2(-400.0f,360.0f)));
}

/*void GameScene::PauseCallBack(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
if(type == Widget::TouchEventType::ENDED)
CCLOG("onTouch");
}

void GameScene::Pause()
{
log("pause");
}


MyClass::MyClass()
{}

Widget::ccWidgetTouchCallback MyClass::onLocateTouchCallback(const string &callBackName)
{
if (callBackName == "onTouche")//判断事件名，返回对应的函数。下同
{
return CC_CALLBACK_2(MyClass::onTouch, this);
}
return nullptr;
}

Widget::ccWidgetClickCallback MyClass::onLocateClickCallback(const string &callBackName)
{
if (callBackName == "onClick")
{
return CC_CALLBACK_1(MyClass::onClick, this);
}
return nullptr;
}

Widget::ccWidgetEventCallback MyClass::onLocateEventCallback(const string &callBackName)
{
if (callBackName == "onEvent")
{
return CC_CALLBACK_2(MyClass::onEvent, this);
}
return nullptr;
}

void MyClass::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
CCLOG("onTouch");
}

void MyClass::onClick(cocos2d::Ref* sender)
{
CCLOG("onClick");
}

void MyClass::onEvent(cocos2d::Ref* sender, int eventType)
{
CCLOG("onEvent");
}*/