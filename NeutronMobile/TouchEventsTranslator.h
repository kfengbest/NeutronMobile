//
//  TouchEventsTranslator.h
//  NeutronMobile
//
//  Created by fengka on 8/11/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UI/Base/Events/TouchEvents.h"

@class UIEvent;
@class UITouch;
@class UIView;

class TouchEventTranslator
{
public:
    TouchEventTranslator(UIView* view );
    ~TouchEventTranslator();
    
    void touchBegin(NSSet* touches, UIEvent* event);
    void touchesMoved(NSSet* touches, UIEvent* event);
    void touchesEnded(NSSet* touches, UIEvent* event);
    void touchesCancelled(NSSet* touches, UIEvent* event);
    
    
private:
    TouchEventTranslator( const TouchEventTranslator& );
    TouchEventTranslator& operator=( const TouchEventTranslator& );
    
    Ns::Core::Point2 convert( CGPoint& loc );
    Nu::Touch* convert( UITouch* touch, int id );

private:
    UIView* m_view;

};