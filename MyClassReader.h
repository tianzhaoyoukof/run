#ifndef MyClassReader_hpp
#define MyClassReader_hpp

#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class MyClassReader : public cocostudio::NodeReader
{
public:
MyClassReader() {};
~MyClassReader() {};
static MyClassReader* getInstance();
static void purge();
cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* MyClassReader_hpp */
