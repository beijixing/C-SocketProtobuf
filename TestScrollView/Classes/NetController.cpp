//
//  NetController.cpp
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/30.
//
//

#include "NetController.h"
#include "DispatchMessage.h"
#include <iostream>
NetController::NetController()
{

}
NetController::~NetController()
{
//    if (m_pNetCtrl) {
//        delete m_pNetCtrl;
//    }
}

static NetController* m_pNetCtrl = nullptr;
NetController* NetController::getInstance()
{
    if (!m_pNetCtrl) {
        m_pNetCtrl = new NetController();
        m_pNetCtrl->init();
    }
    return m_pNetCtrl;
}

bool NetController::init()
{
    bool bRet = false;
    do
    {
        
        if (!connect2Server()) {
            break;
        }
        
        
        bRet = true;
        
    } while (0);
    
    return bRet;
}

int NetController::connect2Server()
{
    m_cSocket.Init();
    m_cSocket.Create(AF_INET, SOCK_STREAM, 0);
    
    const char* ip = "192.168.20.101";
    int port = 8085;
    
    bool result = m_cSocket.Connect(ip, port);
    
    if (result) {
//        m_cSocket.Send("login", 5);
        std::thread recvThread = std::thread(&NetController::receiveData, this);
        recvThread.detach();
    }
    else
    {
        printf("can not connet to server");
        
    }
    m_sockState = result;
    return result;
}

void NetController::receiveData()
{
    while (true)
    {
       
//        printf("%d ", m_cSocket.Select());
//        if (m_cSocket.Select() == 1)
//        {
            char data[1024];
            memset(data, 0, sizeof(data));
            PackageHead *packageHead;

            int result = m_cSocket.Recv(data, sizeof(PackageHead), 0);
            packageHead = (PackageHead*)data;
        
            printf("packageHead.Id = %d, packageHead.datalen = %d\n",packageHead->packageId, packageHead->dataLen );
        
            if (result == 0) {
                printf("error!");
                break;
            }
            else if (result > 0)
            {
                
                char buf[packageHead->dataLen];
                int recvCnt = 0;
                memset(buf, 0, sizeof(buf));
                while (recvCnt < packageHead->dataLen)
                {
                    int ret = m_cSocket.Recv(buf, packageHead->dataLen, 0);
                    recvCnt = recvCnt+ret;
                    printf("recvCnt = %d\n", recvCnt);
                }
                
                
                printf("buf = %s\n", buf);

                
                DispatchMessage::getInstance()->dispatchMessage(buf);
//                printf("DispatchMessage = %s\n", contents.c_str());
            }
            else
            {
                printf("receive data error %d\n", result);
            }
        
//        }
    }

    m_cSocket.Close();
}

void NetController::send(const std::string data, int32_t len)
{
    //        m_cSocket.Send("login", 5);
    CCLOG("发送的数据包长度为 %d", len);
    
    PackageHead packageHead;
    packageHead.dataLen = len;
    packageHead.packageId = 1000;
    char requestData[sizeof(PackageHead)+len];
    int dataSize = len;
    
    memcpy(requestData, &packageHead, sizeof(PackageHead));
    PackageHead *m_packageHead;
    memcpy(&requestData[sizeof(PackageHead)],data.data(),dataSize);
    
    
    int count = 0;
    if (m_sockState)
    {
         count = m_cSocket.Send(requestData, dataSize+sizeof(PackageHead));
    }
    else
    {
        printf("can not connect the internet!");
    }

    m_packageHead = (PackageHead*)requestData;
    printf("m_packageHead.Id = %d, m_packageHead.datalen = %d\n",m_packageHead->packageId, m_packageHead->dataLen );
    printf("count =%d\n", count);
    printf("requestData[8]=%s\n", &requestData[sizeof(PackageHead)]);

//      m_cSocket.Send(data.c_str(), len);
    
}