#include "HelloWorldScene.h"
#include "HelloWorld.pb.h"
#include "SocketTest.h"
#include <fstream>
#include <iostream>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    initScrollView();
    
    auto socketTest = SocketTest::create();
    
    addChild(socketTest, 2,2);

    writer();
    reader();
    return true;
}
int percent = 0;

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    printf("menuCloseCallback");
    percent = percent + 10;
    if (percent > 100)
    {
        percent = 0;
    }
    
    m_listView->scrollToPercentHorizontal(percent, 0.5, true);
}

void HelloWorld::initScrollView()
{
    m_listView =  ui::ListView::create();
    m_listView->setContentSize(Size( 1336, 640));
    m_listView->setPosition(Vec2(0, 200));
    m_listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    m_listView->setTouchEnabled(true);
    addChild(m_listView, 1, 1);
    int i;
    for (i = 1; i<10; i++)
    {
        ui::ImageView* image = ui::ImageView::create("1.png");
        std::stringstream number;
        number << i;
        ui::Text *text = ui::Text::create(number.str() , "", 20);
        text->setPosition(Vec2(100,200));
        image->addChild( text );
        m_listView->pushBackCustomItem(image);
    }
    m_listView->refreshView();
}

void HelloWorld::writer()
{
    lm::HelloWorld msg1;
    msg1.set_id(10);
    msg1.set_str("hello protobuf");
    msg1.set_opt(4);
    
    
//    std::fstream output("./log", std::ios::out | std::ios::trunc | std::ios::binary);
    
    if (!msg1.SerializeToString(&pStr)) {
        std::cerr << "Faild to write msg" << std::endl;
        return ;
    }
    return ;
}

void HelloWorld::reader()
{
    lm::HelloWorld msg2;
    
//    std::fstream input("./log", std::ios::in | std::ios::binary);
    
    if (!msg2.ParseFromString( pStr )) {
        std::cerr << "Faild to parse msg" << std::endl;
        return ;
    }
    
    std::cout << msg2.id() << std::endl;
    std::cout << msg2.str() << std::endl;
}



