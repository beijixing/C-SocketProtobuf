//
//  SocketTest.h
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/24.
//
//

#ifndef __TestScrollView__SocketTest__
#define __TestScrollView__SocketTest__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ODSocket.h"
#include "ui/CocosGUI.h"


class SocketTest :public cocos2d::Layer, public cocos2d::TextFieldDelegate
{
public:
    SocketTest();
    virtual ~SocketTest();
    
 
    
    virtual bool init();
    void connectServer();
    void receiveData();
    
    
    virtual bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF * sender);
    virtual bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF * sender);
    void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);

    
    CREATE_FUNC(SocketTest);
    
    cocos2d::Label *m_pMessage;
    cocos2d::ui::TextField *m_pInputMessage;
    ODSocket socket;
    
};

#endif /* defined(__TestScrollView__SocketTest__) */
