//
//  ReceiveResponse.h
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/25.
//
//

#ifndef __TestScrollView__ReceiveResponse__
#define __TestScrollView__ReceiveResponse__

#include <stdio.h>
#include "pthread.h"
class ReceiveResponse{
public:
    ReceiveResponse(void);
    virtual ~ReceiveResponse(void);
    
    static ReceiveResponse* getInstance();
    int start(void* = NULL);//线程启动函数，参数是空类型指针。
    void stop();
    void sleep(int tesec);//让当前线程休眠给定时间
    void detach();
    void* wait();
private:
    pthread_t m_nPid;
    bool m_bStarted;
    bool m_bDetached;
    static void* start_thread(void* arg);
    static ReceiveResponse* m_pReceiveResponse;
};


#endif /* defined(__TestScrollView__ReceiveResponse__) */
