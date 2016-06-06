#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "cocos2d.h"

USING_NS_CC;

class Obstacle : public Sprite
{
public:
	static Obstacle*					createSp(int k);
	bool					init() override;
	CREATE_FUNC(Obstacle);

	const std::string&					name() const { return name_; }
	const int							width() const{ return width_; }
	const int							height() const { return height_; }
    const int                           deltaY() const {return deltaY_;}

	void					SetKind(const int k);

	/**静态函数，用于记录所有的方块信息*/
	static void						WriteObstacleXML(const std::string& name,const std::string& kind,const bool rotate,const int w ,const int h,const int delta);
private:
	void					initSP();
private:
	std::string						name_;
	bool							b_rotate_;
	int								kind_;
	int								width_;
	int								height_;
    int                             deltaY_;
private:
	static std::vector<std::string>					name_vec_;
	static std::vector<std::string>					kind_vec_;
	static std::vector<bool>						rotate_vec_;
	static std::vector<int>							width_vec_;
	static std::vector<int>							height_vec_;
	static std::vector<int>							deltaY_vec_;
};

#endif