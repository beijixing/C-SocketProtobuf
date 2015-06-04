//
//  ConnectServer.h
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/25.
//
//

#ifndef __TestScrollView__ConnectServer__
#define __TestScrollView__ConnectServer__

#include <stdio.h>
#include "ODSocket.h"
#include "pthread.h"

class ConnectServer {
public:
    ConnectServer(void);
    virtual ~ConnectServer(void);
    
    static ConnectServer* getInstance();
    
    int start();
    ODSocket getSocket();

    void stop();//终止当前线程
    
    int m_nState;//0链接成功，1 链接失败
private:
    ODSocket clientSocket;
    pthread_t m_nPid;
    static void* start_thread(void *arg);
    static ConnectServer *m_pConnectServer;
};
#endif /* defined(__TestScrollView__ConnectServer__) */
