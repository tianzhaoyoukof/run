#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class StateMachine;

class Player : public Sprite
{
public:
	static Player*                  createSP();
	bool                    init() override;
	CREATE_FUNC(Player);
	Player();
	~Player();
	/**∑≠πˆ*/
	void                    Roll();
	/**Ã¯‘æ*/
	void                    Jump();
	/**ª÷∏¥*/
	void                    Resume();
    /**得到碰撞矩形*/
    const Size&                     size() const;
    /**得到目前的任务坐标*/
    const Vec2&                     position() const;
	/**«–ªª◊¥Ã¨*/
	void					ChangeState( const std::string& s );
	/**get∫Ø ˝*/
	Node*						run_node() const { return run_node_; }
	Sprite*						jump_sprite() const { return jump_sprite_; }
	Sprite*						roll_sprite() const { return roll_sprite_; }
private:
	StateMachine*                   state_machine_;

	/**Ã¯‘ææ´¡È*/
	Sprite*						jump_sprite_;
	/**∑≠πˆæ´¡È*/
	Sprite*						roll_sprite_;
	/**≈‹≤ΩΩ·µ„*/
	Node*						run_node_;
private:
	void                    InitSP();
};

#endif /* Header_h */
