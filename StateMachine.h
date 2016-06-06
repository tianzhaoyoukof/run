//
//  StateMachine.hpp
//  Run
//
//  Created by shuoqu_m on 16/6/2.
//
//

#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include "cocos2d.h"

USING_NS_CC;

class State;
class Player;

class StateMachine
{
public:
	StateMachine(Player* p);
	~StateMachine();
	/**·­¹ö*/
	void                    Roll();
	/**ÌøÔ¾*/
	void                    Jump();
	/**»Ö¸´*/
	void                    Resume();

	/**ÉèÖÃ×´Ì¬*/
	void                    SetNowState(const State* s);
	const State*                  run_state() const { return run_state_; }
	const State*                  jump_state() const { return jump_state_; }
	const State*                  roll_state() const { return roll_state_; }
	const State*                  now_state() const { return now_state_; }

	const std::string&                  name() const;
	const Vec2&                     pos() const;
	const Size&                     size() const;
private:
	State*                  run_state_;
	State*                  jump_state_;
	State*                  roll_state_;
	State*                  now_state_;
};

#endif /* StateMachine_hpp */
