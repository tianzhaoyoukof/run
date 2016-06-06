#include "Player.h"
#include "StateMachine.h"

#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"

using namespace cocostudio;
using namespace cocos2d::ui;

Player* Player::createSP()
{
	auto p = Player::create();
	if (p != nullptr)
	{
		p->InitSP();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

Player::Player():
	run_node_( nullptr ),
	roll_sprite_( nullptr ),
	jump_sprite_( nullptr )
{
	state_machine_ = new StateMachine(this);
}

Player::~Player()
{
	delete state_machine_;
}

bool Player::init()
{
	if (!Sprite::init())
		return false;

	//this->initWithFile("restartDown.png");
	run_node_ = CSLoader::createNode( "Animate/RunAnimation.csb" );
	auto action = CSLoader::createTimeline( "Animate/RunAnimation.csb" );
	run_node_->runAction( action );
	action->gotoFrameAndPlay( 0 );
	run_node_->setTag( 0 );

	jump_sprite_ = Sprite::create("jumpPlayer.png");
	//jump_sprite_->runAction( JumpTo::create( 0.5f, Vec2(0, 0), 50, 1 ) );
	jump_sprite_->setTag(1);

	roll_sprite_ = Sprite::create("rollPlayer.png");
	//log( "%s  %f %f" , state_machine_->name().c_str() , state_machine_->pos().x , state_machine_->pos().y );
	roll_sprite_->setPosition(state_machine_->pos());
	roll_sprite_->runAction( RepeatForever::create( RotateBy::create( 0.1f, 60 ) ) );
	roll_sprite_->setTag( 2 );

	this->addChild( run_node_ );
	this->addChild( jump_sprite_ );
	this->addChild( roll_sprite_ );
	//this->setPosition(Vec2(100, 100));

	//run_node_->setVisible( false );
	jump_sprite_->setVisible( false );
	roll_sprite_->setVisible( false );

	return true;
}

void Player::InitSP()
{
	//this->removeAllChildren();
	if (state_machine_->name() == "Jump")
	{
		log("jump");
	}
	else if (state_machine_->name() == "Run")
	{
		log("run");
		/*auto node = CSLoader::createNode("Animate/RunAnimation.csb");
		auto action = CSLoader::createTimeline("Animate/RunAnimation.csb");
		node->runAction(action);
		action->gotoFrameAndPlay(0);
		this->addChild(node);*/
	}
	else
	{
		log("roll");
	}
}

void Player::Roll()
{
	state_machine_->Roll();
	//InitSP();
}

void Player::Jump()
{
	state_machine_->Jump();
	//InitSP();
}

void Player::Resume()
{
	state_machine_->Resume();
	//InitSP();
}

const Size& Player::size() const
{
    return state_machine_->size();
}

const Vec2& Player::position() const
{
    if(state_machine_->name() == "Jump")
        return jump_sprite_->getPosition();
    else if(state_machine_->name() == "Roll")
        return roll_sprite_->getPosition();
    return run_node_->getPosition();
}

void Player::ChangeState( const std::string& s )
{
	if (s == "Jump")
	{
		run_node_->setVisible( false );
		jump_sprite_->setVisible( true );
		roll_sprite_->setVisible( false );
	}
	else if (s == "Roll")
	{
		run_node_->setVisible( false );
		jump_sprite_->setVisible( false );
		roll_sprite_->setVisible( true );
	}
	else
	{
		run_node_->setVisible( true );
		jump_sprite_->setVisible( false );
		roll_sprite_->setVisible( false );
	}
}