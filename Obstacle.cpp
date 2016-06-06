#include "Obstacle.h"

std::vector<std::string> Obstacle::name_vec_;
std::vector<std::string> Obstacle::kind_vec_;
std::vector<bool> Obstacle::rotate_vec_;
std::vector<int> Obstacle::width_vec_;
std::vector<int> Obstacle::height_vec_;
std::vector<int> Obstacle::deltaY_vec_;

Obstacle* Obstacle::createSp(int k)
{
	auto sp = Obstacle::create();
	if (sp)
	{
		sp->kind_ = k;
		sp->initSP();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return nullptr;
}

bool Obstacle::init()
{
	if (!Sprite::init())
		return false;
	return true;
}

void Obstacle::initSP()
{
	this->initWithFile(name_vec_[kind_]);
    height_ = height_vec_[kind_];
    width_ = width_vec_[kind_];
    deltaY_ = deltaY_vec_[kind_];
    if(kind_vec_[kind_] == "up")
        deltaY_ = 50;
	if (rotate_vec_[kind_] == true)
		this->runAction(RepeatForever::create(RotateBy::create(0.3f, -40)));
}

void Obstacle::WriteObstacleXML(const std::string& name, const std::string& kind, const bool rotate, const int w, const int h, const int delta)
{
	name_vec_.push_back(name);
	kind_vec_.push_back(kind);
	rotate_vec_.push_back(rotate);
	width_vec_.push_back(w);
	height_vec_.push_back(h);
	deltaY_vec_.push_back(delta);
}

void Obstacle::SetKind(const int k)
{
	kind_ = k;
    this->stopAllActions();
    this->setRotation(0);
	initSP();
}