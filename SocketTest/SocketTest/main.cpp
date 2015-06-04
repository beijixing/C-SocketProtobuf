//
//  main.cpp
//  SocketTest
//
//  Created by 郑光龙 on 15/5/24.
//  Copyright (c) 2015年 郑光龙. All rights reserved.
//

#include <iostream>
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

typedef struct _packageHead
{
    int dataLen;
    int packageId;
}PackageHead;

int main(int argc , char *argv[])
{
        int socket_desc , client_sock , c , read_size;
        struct sockaddr_in server , client;
        char client_message[2000];
        
        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
            printf("Could not create socket");
        }
        puts("Socket created");
        
        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons( 8085 );
        
        //Bind
        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
            //print the error message
            perror("bind failed. Error");
            return 1;
        }
        puts("bind done");
        
        //Listen
        listen(socket_desc , 3);
        
        //Accept and incoming connection
        puts("Waiting for incoming connections...");
        c = sizeof(struct sockaddr_in);
        
        //accept connection from an incoming client
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if (client_sock < 0)
        {
            perror("accept failed");
            return 1;
        }
        puts("Connection accepted");
    
//        char databuf[1024];
//        char* str = "hello socekt!";
//        int slen = (int)strlen(str);
//    
//        memcpy(&databuf[8], &str, slen);
//        memcpy(databuf, &slen, 8);
//        write(client_sock , databuf , strlen(databuf));
//
//    
        //Receive a message from client
//        while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
//        {
//            //Send the message back to client
//            printf("receive client data");
////            printf("clinet message %s\n", client_message);
////            sprintf(client_message, "connect success");
////            printf("lens = %d", sizeof(client_message));
////            write(client_sock , client_message , strlen(client_message));
////            send(client_sock, client_message,2000, 0);
//            memset(client_message, 0, sizeof(client_message));
//        }
    
    PackageHead *m_packageHead;
    memset(client_message, 0, sizeof(client_message));
    while ((read_size = recv(client_sock , client_message , sizeof(PackageHead), 0)) > 0 )
    {
        m_packageHead = (PackageHead*)client_message;
        printf("m_packageHead.Id = %d, m_packageHead.datalen = %d\n",m_packageHead->packageId, m_packageHead->dataLen );
        
        char str[m_packageHead->dataLen];
        memset(str, 0, sizeof(str));
        int recvCnt = 0;
//        memcpy(str, &client_message[sizeof(PackageHead)], m_packageHead->dataLen);
        while (recvCnt < m_packageHead->dataLen)
        {
           read_size = recv(client_sock , str , m_packageHead->dataLen , 0);
           recvCnt = recvCnt+read_size;
            printf("recvCnt = %d\n", recvCnt);
        }
        printf("receive data\n");

        printf("str = %s\n", str);
        memset(client_message, 0, sizeof(client_message));
        PackageHead package;
        package.dataLen = (int)strlen(str);
        package.packageId = 10;
        memcpy(client_message, &package, sizeof(PackageHead));
        memcpy(&client_message[sizeof(PackageHead)], str, strlen(str));
        
        PackageHead *pHead = (PackageHead*)client_message;
        printf("pHead.id = %d, pHead.datalen = %d\n",pHead->packageId, pHead->dataLen );
        printf("client_message = %s\n", &client_message[sizeof(PackageHead)]);
        
        write(client_sock , client_message , sizeof(PackageHead)+strlen(str));
        
        
        memset(client_message, 0, sizeof(client_message));
    }
    
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    
    return 0;
}



