#include "Rhythm.h"

Rhythm::Rhythm()
{
	ReadFromXML();
}

Rhythm::~Rhythm()
{

}

void Rhythm::Next()
{
	times_.pop();
	kinds_.pop();
}

void Rhythm::ReadFromXML()
{
	auto root = __Dictionary::createWithContentsOfFile("Rhythm.xml");
	int size = std::atoi(((String*)root->objectForKey("size"))->getCString());
	log("%d", size);
	for (int i = 1; i <= size; ++i)
	{
		auto r = (__Dictionary*)root->objectForKey(StringUtils::format("Rhythm%d", i));
		auto times = (String*)r->valueForKey("time");
		auto obstacle = (String*)r->valueForKey("obstacle");
		times_.push(std::atof(times->getCString()));
		kinds_.push(std::atoi(obstacle->getCString()));
	}
}