#include "State.h"
#include "StateMachine.h"
#include "Player.h"

#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"

using namespace cocostudio;
using namespace cocos2d::ui;

State::State(StateMachine* s, Player* p, const std::string& nam) :
state_machine_(s),
player_(p),
name_(nam),
size_(40, 60),
pos_(0, 0)
{

}

State::~State()
{

}





/***************************/

RunState::RunState(StateMachine* s, Player* p) :
State(s, p, "Run")
{

}

RunState::~RunState()
{

}

void RunState::Roll()
{
	state_machine_->SetNowState(state_machine_->roll_state());

}

void RunState::Jump()
{
	state_machine_->SetNowState(state_machine_->jump_state());
}

void RunState::Resume()
{

}

void RunState::Refresh()
{
	//player_->removeAllChildren();
	//player_->addChild(node);
	player_->ChangeState( "Run" );
}




/***************************/

JumpState::JumpState(StateMachine* s, Player* p) :
State(s, p, "Jump"),
jump_sprite_(nullptr)
{
	size_ = Size(40, 60);
	pos_ = Vec2(0, 30);
}

JumpState::~JumpState()
{

}

void JumpState::Roll()
{
    player_->jump_sprite()->removeAllChildren();
    state_machine_->SetNowState(state_machine_->roll_state());
}

void JumpState::Jump()
{
	return;
	state_machine_->SetNowState(state_machine_->jump_state());
}

void JumpState::Resume()
{
	//log("resume jump_sprite_ %f", jump_sprite_->getPositionY());
	if (player_->jump_sprite()->getPositionY() > 0)
		return;
	state_machine_->SetNowState(state_machine_->run_state());
}

void JumpState::Refresh()
{
	/*if (jump_sprite_ && jump_sprite_->getReferenceCount() == 0 && jump_sprite_->getPositionY() > 0)
	{
		log("%d ", jump_sprite_->getReferenceCount());
		return;
	}*/
	if (player_->jump_sprite()->getPositionY() > 0)
		return;
	player_->jump_sprite()->stopAllActions();
	player_->jump_sprite()->removeAllChildren();
	player_->jump_sprite()->runAction(JumpTo::create(0.5f, Vec2(0, 0), 120, 1));
	player_->ChangeState( "Jump" );
	auto node = Node::create();
	node->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=](){this->Resume(); }), NULL));
	player_->jump_sprite()->addChild(node);

	//player_->removeAllChildren();
	//player_->addChild(node);
}



/***************************/

RollState::RollState(StateMachine* s, Player* p) :
State(s, p, "Roll")
{
	size_ = Size(38, 38);
	pos_ = Vec2(0, -18);
}

RollState::~RollState()
{

}

void RollState::Roll()
{

}

void RollState::Jump()
{

}

void RollState::Resume()
{
	state_machine_->SetNowState(state_machine_->run_state());
}

void RollState::Refresh()
{
	//player_->removeAllChildren();
	//if (player_->getChildByTag(1) != nullptr)
	//	player_->getChildByTag(1)->retain();
	/*auto sp = Sprite::create("rollPlayer.png");
	//log( "%s  %f %f" , state_machine_->name().c_str() , state_machine_->pos().x , state_machine_->pos().y );
	sp->setPosition(state_machine_->pos());
	sp->runAction(RepeatForever::create(RotateBy::create(0.1f, 60)));
	player_->addChild(sp);*/
	player_->roll_sprite()->setPosition( state_machine_->pos() );
	player_->ChangeState( "Roll" );
}