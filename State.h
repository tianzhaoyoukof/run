#ifndef __STATE_H__
#define __STATE_H__

#include "cocos2d.h"

USING_NS_CC;

class StateMachine;
class Player;

class State
{
public:
	State(StateMachine* s, Player* p, const std::string& nam);
	virtual ~State();
	/**翻滚*/
	virtual void                    Roll() = 0;
	/**跳跃*/
	virtual void                    Jump() = 0;
	/**恢复*/
	virtual void                    Resume() = 0;
	/**刷新函数*/
	virtual void                    Refresh() = 0;
	/**名字*/
    const std::string&                  name() const { return name_; };

	const Size&                     size() const { return size_; }
	const Vec2&                     pos() const { return pos_; }
protected:
	StateMachine*                   state_machine_;
	Player*                         player_;
	/**状态名字*/
	const std::string                   name_;
	/**结点的位置*/
	Vec2                    pos_;
	/**碰撞框的大小*/
	Size                    size_;
};

class RunState : public State
{
public:
	RunState(StateMachine* s, Player* p);
	~RunState() override;
	void                    Roll() override;
	void                    Jump() override;
	void                    Resume() override;
	void                    Refresh() override;
private:

};

class JumpState : public State
{
public:
	JumpState(StateMachine* s, Player* p);
	~JumpState() override;
	void                    Roll() override;
	void                    Jump() override;
	void                    Resume() override;
	void                    Refresh() override;
private:
	Sprite*                     jump_sprite_;
};

class RollState : public State
{
public:
	RollState(StateMachine* s, Player* p);
	~RollState() override;
	void                    Roll() override;
	void                    Jump() override;
	void                    Resume() override;
	void                    Refresh() override;
private:

};

#endif /* State_hpp */
