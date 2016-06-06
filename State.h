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
	/**����*/
	virtual void                    Roll() = 0;
	/**��Ծ*/
	virtual void                    Jump() = 0;
	/**�ָ�*/
	virtual void                    Resume() = 0;
	/**ˢ�º���*/
	virtual void                    Refresh() = 0;
	/**����*/
    const std::string&                  name() const { return name_; };

	const Size&                     size() const { return size_; }
	const Vec2&                     pos() const { return pos_; }
protected:
	StateMachine*                   state_machine_;
	Player*                         player_;
	/**״̬����*/
	const std::string                   name_;
	/**����λ��*/
	Vec2                    pos_;
	/**��ײ��Ĵ�С*/
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
