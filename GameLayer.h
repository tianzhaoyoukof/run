#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "UITextAtlas.h"

USING_NS_CC;
using namespace cocos2d::ui;

class Player;
class Obstacle;
class Rhythm;
class GameScene;

class GameLayer : public Layer
{
public:
	static GameLayer*                  createNode();
	bool                    init() override;
	CREATE_FUNC(GameLayer);
	GameLayer();
	~GameLayer();
    void                    SetParent();
	void                    update(float delta) override;

	bool                    onTouchBegan(Touch *touch, Event *unused_event) override;
	void                    onTouchMoved(Touch *touch, Event *unused_event) override;
	void                    onTouchEnded(Touch *touch, Event *unused_event) override;
    
    /**重新开始游戏*/
    void                    Restart();
private:

	float					cur_time_;
    /**队的长度*/
    #define                  queue_length_ 7
    /**对尾*/
    int                     tail_;
    /**距离的数字*/
    int                     distance_number_;
    
    /**游戏是否结束*/
    bool                    is_gameover_;
    
    /**水平线的坐标*/
    Vec2                    standard_line_vec_;
    
    Player*                     player_;
    Rhythm*						rhythm_;
    Obstacle*					obstacle_[queue_length_];
    GameScene*                  parent_;
    TextAtlas*                  distance_;
private:
	void					ReadFromXML();
    /**是否碰撞到了*/
    bool                    IsCollision(const Vec2& p1,const Vec2& p2,const Size& s1,const Size& s2);
    /**游戏结束*/
    void                    GameOver();
};

#endif /* Header_h */
