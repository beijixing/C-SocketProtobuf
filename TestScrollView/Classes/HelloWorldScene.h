#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void initScrollView();
    
    void writer();
    
    void reader();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    
    cocos2d::ui::ListView *m_listView;
    std::string pStr;
    
};

#endif // __HELLOWORLD_SCENE_H__
