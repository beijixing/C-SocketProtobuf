//
//  ReceiveResponse.cpp
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/25.
//
//

#include "ReceiveResponse.h"
#include "ODSocket.h"
#include "ConnectServer.h"

ReceiveResponse::ReceiveResponse(void):
m_nPid(0),
m_bStarted(false),
m_bDetached(false)
{
}
ReceiveResponse::~ReceiveResponse(void)
{
    stop();
}
ReceiveResponse* ReceiveResponse::getInstance()
{
    if (!m_pReceiveResponse) {
        m_pReceiveResponse = new ReceiveResponse();
    }
    return m_pReceiveResponse;
}
int ReceiveResponse::start(void* )//线程启动函数，参数是空类型指针。
{
    int errCode = 0;
    do
    {
        pthread_attr_t attr;
        errCode = pthread_attr_init(&attr);
        if (errCode!=0) {
            break;
        }
        
        errCode = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        if (errCode != 0) {
            pthread_attr_destroy(&attr);
            break;
        }
        
        errCode = pthread_create(&m_nPid, &attr, start_thread, this);
        
    } while (0);
    
    return errCode;
}
void ReceiveResponse::stop()
{
}

void ReceiveResponse::sleep(int tesec)//让当前线程休眠给定时间
{

}

void ReceiveResponse::detach()
{

}
void* ReceiveResponse::wait()
{

}

void* ReceiveResponse::start_thread(void* arg)
{
    ReceiveResponse* responce = (ReceiveResponse*)arg;
    ODSocket cSock = ConnectServer::getInstance()->getSocket();
    if (ConnectServer::getInstance()->m_nState == 0) {
        while (true)
        {
            if (cSock.Select() == 1)//收到消息
            {
                
                
            }
        }
    }
    
}