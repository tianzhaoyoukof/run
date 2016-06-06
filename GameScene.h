#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"
#include "UITextAtlas.h"

using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;

USING_NS_CC;

class GameLayer;

class BackGroundLayer : public Node
{
public:
    static BackGroundLayer*                     createNode();
    bool                    init() override;
    CREATE_FUNC(BackGroundLayer);
private:
    Sprite*                 bg1_;
    Sprite*                 bg2_;
    Sprite*                 bg3_;
    
    void                    CallBack();
};

class GameScene : public cocos2d::Node
{
public:
	static Scene*                   createScene();
	virtual bool                    init() override;
	CREATE_FUNC(GameScene);

	void PauseCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void                    Pause();
    
    /**展示结束面板*/
    void                    ShowOverBoard();
    void                    HideOverBoard();
    
    TextAtlas*                  distance_;
private:
    void                    RestartCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
private:
	GameLayer*                  game_layer_;
    Button*                     restart_btn_;
    Sprite*                     over_board_;
};

/*class MyClass : public cocos2d::Node, public cocostudio::WidgetCallBackHandlerProtocol
{
public:
CREATE_FUNC(MyClass)
MyClass();
virtual cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string &callBackName);
virtual cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string &callBackName);
virtual cocos2d::ui::Widget::ccWidgetEventCallback onLocateEventCallback(const std::string &callBackName);
void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
void onClick(cocos2d::Ref* sender);
void onEvent(cocos2d::Ref* sender, int eventType);
private:
std::vector<std::string> _touchTypes;
std::string _click;
std::vector<std::string> _eventTypes;
};*/



#endif /* Header_h */
