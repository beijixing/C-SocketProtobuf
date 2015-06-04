//
//  NetController.h
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/30.
//
//

#ifndef __TestScrollView__NetController__
#define __TestScrollView__NetController__

#include <stdio.h>
#include "ODSocket.h"
class NetController{
public:
    NetController();
    virtual ~NetController();
    static NetController* getInstance();
    void send(const std::string data, int32_t len);
    typedef struct _packageHead
    {
        int dataLen;
        int packageId;
    }PackageHead;
    
private:
    bool init();
    int connect2Server();
    void receiveData();
    bool m_sockState;
    ODSocket m_cSocket;
//    static  NetController* m_pNetCtrl;

};
#endif /* defined(__TestScrollView__NetController__) */
