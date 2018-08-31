//
//  TouchEventsTranslator.m
//  NeutronMobile
//
//  Created by fengka on 8/11/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "TouchEventsTranslator.h"
#import "UI/Base/Events/TouchEventSource.h"

TouchEventTranslator::TouchEventTranslator(UIView* view )
:m_view( view )
{
}


TouchEventTranslator::~TouchEventTranslator()
{

}


void TouchEventTranslator::touchBegin(NSSet* touches, UIEvent* event)
{
    Nu::Touches nuTouches;
    for (UITouch *touch in touches){
        nuTouches.insert(convert(touch, 0));
    }
    
    Nu::TouchEvent touchEvent(nuTouches);
    Nu::TouchEventSource::get()->fireTouchPress(&touchEvent);
  
    Nu::Touches::iterator it = nuTouches.begin();
    for (; it != nuTouches.end(); ++it)
        delete *it;
    nuTouches.clear();
    
}

void TouchEventTranslator::touchesMoved(NSSet* touches, UIEvent* event)
{
    Nu::Touches nuTouches;
    for (UITouch *touch in touches){
        nuTouches.insert(convert(touch, 0));
    }
    
    Nu::TouchEvent touchEvent(nuTouches);
    Nu::TouchEventSource::get()->fireTouchMove(&touchEvent);
    
    Nu::Touches::iterator it = nuTouches.begin();
    for (; it != nuTouches.end(); ++it)
        delete *it;
    nuTouches.clear();
}

void TouchEventTranslator::touchesEnded(NSSet* touches, UIEvent* event)
{
    Nu::Touches nuTouches;
    for (UITouch *touch in touches){
        nuTouches.insert(convert(touch, 0));
    }
    
    Nu::TouchEvent touchEvent(nuTouches);
    Nu::TouchEventSource::get()->fireTouchRelease(&touchEvent);
    
    Nu::Touches::iterator it = nuTouches.begin();
    for (; it != nuTouches.end(); ++it)
        delete *it;
    nuTouches.clear();
}

void TouchEventTranslator::touchesCancelled(NSSet* touches, UIEvent* event)
{

}

Ns::Core::Point2 TouchEventTranslator::convert( CGPoint& loc )
{
    return Ns::Core::Point2(loc.x, loc.y);
}


Nu::Touch* TouchEventTranslator::convert( UITouch* touch, int id )
{
    CGPoint loc = [touch locationInView:m_view];
    CGPoint prevLoc = [touch previousLocationInView:m_view];
    
    Ns::Core::Point2 pos = convert( loc );
    Ns::Core::Point2 prevPos = convert( prevLoc );
    
    Nu::Touch::TouchPhase phase = Nu::Touch::eTouchUnknown;
    
    switch( touch.phase )
    {
        case UITouchPhaseBegan:
            phase = Nu::Touch::eTouchPress;
            break;
            
        case UITouchPhaseMoved:
            phase = Nu::Touch::eTouchMove;
            break;
            
        case UITouchPhaseStationary:
            phase = Nu::Touch::eTouchStationary;
            break;
            
        case UITouchPhaseEnded:
            phase = Nu::Touch::eTouchRelease;
            break;
            
        case UITouchPhaseCancelled:
            phase = Nu::Touch::eTouchCancelled;
            break;
    }
    
    return new Nu::Touch(id, pos, prevPos, (int)touch.tapCount, phase,touch.timestamp);
}