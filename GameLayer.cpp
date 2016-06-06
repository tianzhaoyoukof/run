#include "GameLayer.h"
#include "GameScene.h"
#include "Player.h"
#include "Obstacle.h"
#include "Rhythm.h"


#include "cocostudio/WidgetCallBackHandlerProtocol.h"

using namespace cocostudio;


GameLayer* GameLayer::createNode()
{
	auto p = GameLayer::create();
	if (p != nullptr)
	{
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

GameLayer::GameLayer():
    parent_(nullptr),
    distance_number_(0),
    is_gameover_(false)
{

}

GameLayer::~GameLayer()
{
	delete rhythm_;
}

void GameLayer::SetParent()
{
    parent_ = dynamic_cast<GameScene*>(this->getParent());
    distance_ = parent_->distance_;
    distance_->setString(StringUtils::format("%d",distance_number_));
}

bool GameLayer::init()
{
	if (!Layer::init())
		return false;

	auto node = CSLoader::createNode("Layer/Layer.csb");
	standard_line_vec_ = dynamic_cast<Sprite*>(node->getChildByTag(2))->getPosition();
    //distance_ = parent->distance_;
    //distance_->setString("2356");

	player_ = Player::createSP();
	player_->setPosition(standard_line_vec_);
	this->addChild(player_);

	ReadFromXML();

	for (int i = 0; i < 7; ++ i)
	{
		//int r = rand() % 7;
		obstacle_[i] = Obstacle::createSp(i);
		obstacle_[i]->setPosition(Vec2(10 , 100 + i * 50));
		this->addChild(obstacle_[i]);
	}

	cur_time_ = 0.0f;

	rhythm_ = new Rhythm();

	//this->scheduleUpdate();
    tail_ = 1;
	this->schedule(schedule_selector(GameLayer::update), 0.02f);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameLayer::update(float delta)
{
	//log("  %f   sdsdaw",delta);
    if(is_gameover_ == true)
        return ;
	cur_time_ += delta;
    //创造新的障碍
    if(rhythm_->Size() == 0)
        GameOver();
	if (rhythm_->Size() > 0 && cur_time_ > rhythm_->CurTimes())
	{
        //决定用哪个索引的队列
        int index = tail_;
        if(obstacle_[(tail_ + queue_length_ - 1) % queue_length_]->getPositionX() > 20)
            tail_ = (tail_ + 1) % queue_length_;
        else
            index = (tail_ + queue_length_ - 1) % queue_length_;
		obstacle_[index]->SetKind(rhythm_->CurKind());
        obstacle_[index]->setPosition(Vec2(1300, standard_line_vec_.y + obstacle_[index]->deltaY()));
		obstacle_[index]->runAction(MoveTo::create(4.0f,Vec2(-20,standard_line_vec_.y + obstacle_[index]->deltaY())));
		rhythm_->Next();
	}
    
    //检测碰撞
    for (int i = 0; i < queue_length_; ++ i)
    {
        Size s(obstacle_[i]->width(),obstacle_[i]->height());
        if(IsCollision(player_->getPosition() + player_->position(), obstacle_[i]->getPosition(), player_->size(), s) == true)
            GameOver();
    }
    
    //增加一米
    distance_number_ ++;
    distance_->setString(StringUtils::format("%d",distance_number_));
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if(is_gameover_ == true)
        return false;
	auto p = touch->getLocation();
	//log( "%f %f" , p.x , p.y );
	if (p.x > 640.0f)
		player_->Roll();
	else
		player_->Jump();
	return true;
}

void GameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{

}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	player_->Resume();
}

void GameLayer::ReadFromXML()
{
	auto root = __Dictionary::createWithContentsOfFile("Obstacle.xml");
	for (int i = 1; i <= 7; ++i)
	{
		auto r = (__Dictionary*)root->objectForKey(StringUtils::format("Obstacle%d", i));
		auto name = (String*)r->valueForKey("name");
		auto kind = (String*)r->valueForKey("kind");
		auto rotate = (String*)r->valueForKey("rotate");
		int width = std::atoi(((String*)r->valueForKey("width"))->getCString());
		int height = std::atoi(((String*)r->valueForKey("height"))->getCString());
		int deltaY = std::atoi(((String*)r->valueForKey("deltaY"))->getCString());
		log("%s %s %s %d %d %d", name->getCString(), kind->getCString(), rotate->getCString(), width, height, deltaY);
		bool b = false;
		if (std::strcmp(rotate->getCString(),"true") == 0)
			b = true;
		Obstacle::WriteObstacleXML(name->getCString(), kind->getCString(), b, width, height, deltaY);
	}
}

bool GameLayer::IsCollision(const cocos2d::Vec2 &p1, const cocos2d::Vec2 &p2, const cocos2d::Size &s1, const cocos2d::Size &s2)
{
    //log("%f %f %f %f",p1.x,p1.y,p2.x,p2.y);
    //log("%f %f %f %f",s1.width,s1.height,s2.width,s2.height);
    //log("%f   %f", std::abs(p1.x - p2.x) * 2, s1.width + s2.width);
    //log("%f   %f", std::abs(p1.y - p2.y) * 2, s1.height + s2.height);
    if((std::abs(p1.x - p2.x) * 2 < s1.width + s2.width) && (std::abs(p1.y - p2.y) * 2 < s1.height + s2.height))
        return true;
    return false;
}

void GameLayer::GameOver()
{
    for(int i = 0 ; i < queue_length_ ; ++ i)
    {
        obstacle_[i]->stopAllActions();
    }
    is_gameover_ = true;
    parent_->ShowOverBoard();
}

void GameLayer::Restart()
{
    delete rhythm_;
    rhythm_ = new Rhythm();
    for(int i = 0 ; i < queue_length_ ; ++ i)
    {
        obstacle_[i]->setPositionX(-20.0f);
    }
    is_gameover_ = false;
    parent_->HideOverBoard();
    tail_ = 1;
    cur_time_ = 0.0f;
    distance_number_ = 0;
    distance_->setString(StringUtils::format("%d",distance_number_));
}
