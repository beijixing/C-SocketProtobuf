//
//  ConnectServer.cpp
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/25.
//
//

#include "ConnectServer.h"
ConnectServer::ConnectServer(void)
:m_nState(1),
 m_nPid(0)
{

}

ConnectServer::~ConnectServer(void)
{
}

ConnectServer* ConnectServer::getInstance()
{
    if ( !m_pConnectServer ) {
        m_pConnectServer = new ConnectServer();
    }
    return  m_pConnectServer;
}

int ConnectServer::start()
{
    int errCode = 0;
    do
    {
        pthread_attr_t tAttr;
        errCode = pthread_attr_init( &tAttr );
        if (errCode != 0) {
            break;
        }
        
        errCode = pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
        if (errCode != 0 ) {
            pthread_attr_destroy(&tAttr);
            break;
        }
        
        errCode = pthread_create(&m_nPid, &tAttr, start_thread, this);
    } while (0);
    
    return errCode;
}

ODSocket ConnectServer::getSocket()
{
    return this->clientSocket;
}

void ConnectServer::stop()//终止当前线程
{
    pthread_cancel(m_nPid);
    pthread_detach(m_nPid);
}

void* ConnectServer::start_thread(void* arg)
{
    ConnectServer* cs = (ConnectServer*)arg;
    ODSocket cdSocket;
    cdSocket.Init();
    bool is_OK = cdSocket.Create(AF_INET, SOCK_STREAM, 0);
    
    if (0 != is_OK) {
        printf("create socket failed");
    }
    const char* ip="127.0.0.1";
    int port =  8080;
    
    bool is_Con = cdSocket.Connect(ip, port);
    if (is_Con) {
        cs->m_nState = 0;
        //接受消息
        printf("connect success");
    }
    else
    {
        cs->m_nState = 1;
    }
    
    cs->clientSocket = cdSocket;
    return NULL;
}
