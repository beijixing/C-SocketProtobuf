//
//  DispatchMessage.h
//  TestScrollView
//
//  Created by 郑光龙 on 15/5/30.
//
//

#ifndef __TestScrollView__DispatchMessage__
#define __TestScrollView__DispatchMessage__

#include <stdio.h>
class DispatchMessage{
public:
    
    DispatchMessage();
    virtual ~DispatchMessage();
    
    static DispatchMessage* getInstance();
    void dispatchMessage(const std::string message);
    
private:
//    static DispatchMessage* m_pDispatchMessage;
    
};


#endif /* defined(__TestScrollView__DispatchMessage__) */
