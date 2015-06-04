//
//  SocketTest.cpp
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/24.
//
//

#include "SocketTest.h"
#include "ODSocket.h"
#include "NetController.h"
#include "HelloWorld.pb.h"
USING_NS_CC;
using namespace ui;


SocketTest::SocketTest(void)
{
    
}

SocketTest::~SocketTest()
{}


bool SocketTest::init()
{
    bool bRet = false;
    
   do{
    if (!Layer::init())
        break;
    
       
       Vec2 visibleSize = Director::getInstance()->getVisibleSize();
       
       m_pMessage = Label::createWithSystemFont("this is a socket test", "Arial", 20);
       m_pMessage->setPosition(Vec2(visibleSize.x/2, visibleSize.y/2));
       addChild(m_pMessage);
       
       
       m_pInputMessage = TextField::create( "请输入内容",  "Arial", 40);
       m_pInputMessage->setPosition(Vec2(visibleSize.x/2, 100));
       addChild(m_pInputMessage);
       m_pInputMessage->addEventListener(CC_CALLBACK_2(SocketTest::textFieldEvent, this));
//       connectServer();
       
       
       bRet = true;
   } while(0);
    return bRet;
}

void SocketTest::connectServer()
{
//    return;
    socket.Init();
    socket.Create(AF_INET, SOCK_STREAM, 0);
    
    const char* ip = "192.168.20.101";
    int port = 8085;
 
    bool result = socket.Connect(ip, port);
    
    if (result) {
        socket.Send("login", 5);
        std::thread recvThread = std::thread(&SocketTest::receiveData, this);
        recvThread.detach();
    }
    else
    {
        printf("can not connet to server");
        
    }
    
    
}


void SocketTest::receiveData()
{
    while (true) {

        char data[512+1];
        memset(data, 0, sizeof(data));
        printf("%d ", socket.Select());
//        if (socket.Select() == 1) {
            int result = socket.Recv(data, 512, 0);
            printf("result =  %d\n", result);
            
            if (result <=0 ) break;
            
            printf("%s\n", data);
//        }
        
    }
    
    
    socket.Close();

}

bool SocketTest::onTextFieldAttachWithIME(cocos2d::TextFieldTTF * sender)
{
    return false;
}
bool SocketTest::onTextFieldDetachWithIME(cocos2d::TextFieldTTF * sender)
{
    printf("%s",  sender->getString().c_str());
    return false;
}

void SocketTest::textFieldEvent(Ref *pSender, TextField::EventType type)
{
    if (type == TextField::EventType::ATTACH_WITH_IME)
    {
    
        
    }
    else if(type == TextField::EventType::DETACH_WITH_IME)
    {
        TextField* textField = (TextField*)pSender;
        printf("%s\n", textField->getString().c_str());
//        socket.Send(textField->getString().c_str(), textField->getString().length());

        lm::HelloWorld msg ;
        msg.set_str(textField->getString());
        msg.set_opt(1000);
        msg.set_id(1024);
        
        std::string msgStr;
        msg.SerializeToString(&msgStr);
        
        
//        NetController::getInstance()->send(textField->getString().c_str(), (int32_t)textField->getString().length());
        
        NetController::getInstance()->send(msgStr, (int32_t)msgStr.length());
        
    }
}