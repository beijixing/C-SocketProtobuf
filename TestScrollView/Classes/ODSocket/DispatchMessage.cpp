//
//  DispatchMessage.cpp
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/30.
//
//

#include "DispatchMessage.h"
#include "HelloWorld.pb.h"
#include <iostream>
DispatchMessage::DispatchMessage()
{
}

DispatchMessage::~DispatchMessage()
{
//    if (m_pDispatchMessage) {
//        delete m_pDispatchMessage;
//    }
}

static DispatchMessage* m_pDispatchMessage = nullptr;

DispatchMessage* DispatchMessage::getInstance()
{
    if (!m_pDispatchMessage) {
        m_pDispatchMessage = new DispatchMessage();
    }
    return m_pDispatchMessage;
}

void DispatchMessage::dispatchMessage(const std::string message)
{
    printf("dispatch message = %s\n", message.c_str());
    lm::HelloWorld msg;
    msg.ParseFromString(message);
    std::cout << msg.opt() << std::endl;
    std::cout << msg.id() << std::endl;
    std::cout << msg.str() << std::endl;
    
    
}
