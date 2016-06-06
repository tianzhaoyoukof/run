#include "StateMachine.h"
#include "State.h"

StateMachine::StateMachine(Player* p)
{
	jump_state_ = new JumpState(this, p);
	roll_state_ = new RollState(this, p);
	run_state_ = new RunState(this, p);

	now_state_ = run_state_;
}

StateMachine::~StateMachine()
{
	delete jump_state_;
	delete run_state_;
	delete roll_state_;
}

void StateMachine::Roll()
{
	now_state_->Roll();
	now_state_->Refresh();
}

void StateMachine::Jump()
{
	now_state_->Jump();
	now_state_->Refresh();
}

void StateMachine::Resume()
{
	now_state_->Resume();
	now_state_->Refresh();
}

void StateMachine::SetNowState(const State *s)
{
	now_state_ = const_cast<State*>(s);
	now_state_->Refresh();
}

const std::string& StateMachine::name() const
{
	return now_state_->name();
}

const Size& StateMachine::size() const
{
	return now_state_->size();
}

const Vec2& StateMachine::pos() const
{
	return now_state_->pos();
}