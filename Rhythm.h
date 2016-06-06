#ifndef __RHYTHM_H__
#define __RHYTHM_H__

#include "cocos2d.h"

USING_NS_CC;

class Rhythm
{
public:
	Rhythm();
	~Rhythm();
	void					Next();
	const float					CurTimes() const { return times_.front(); }
	const int					CurKind() const { return kinds_.front(); }
	const unsigned long					Size() const { return times_.size(); }
private:
	void					ReadFromXML();
private:
	std::queue<float>					times_;
	std::queue<int>						kinds_;
};

#endif