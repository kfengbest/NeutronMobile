//
//  Command.cpp
//  NeutronMobile
//
//  Created by fengka on 8/11/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#define __COMPILING_NU_COMMAND_CPP__
#include "NuCommand.h"
#undef __COMPILING_NU_COMMAND_CPP__

#include "../../../Server/Geometry2D/Document.h"
#include "../../../Server/Geometry2D/Line2D.h"
#include "../Events/TouchEventSource.h"
#include "../Events/Touch.h"
#include "../Events/TouchEvents.h"

using namespace Nu;

Command::Command(Document* pDoc)
: TouchEventSite(),
m_pDocument(pDoc)
{
    Nu::TouchEventSource::get()->subscribe(this);
}

Command::~Command()
{
    Nu::TouchEventSource::get()->unsubscribe(this);
}



LineCommand::LineCommand(Document* pDoc)
: Command(pDoc)
{

}

LineCommand::~LineCommand()
{
}

void LineCommand::touchPress(TouchEvent* pEvent)
{
    Ns::Core::Point2 p = pEvent->anyTouch()->position();
    m_firstPoint = Point2D(p.x, p.y);
}

void LineCommand::touchMove(TouchEvent* pEvent)
{
    
}

void LineCommand::touchRelease(TouchEvent* pEvent)
{
    Ns::Core::Point2 p = pEvent->anyTouch()->position();
    Point2D endPoint = Point2D(p.x, p.y);
    
    Line2D* pLine = new Line2D(m_pDocument, m_firstPoint, endPoint);
    pLine->lineThickness( m_pDocument->m_thickness);
    pLine->lineColor(m_pDocument->m_color);
    m_pDocument->addEntity(pLine);
    
}
