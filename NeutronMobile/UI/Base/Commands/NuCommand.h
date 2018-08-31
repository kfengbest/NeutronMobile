//
//  Command.h
//  NeutronMobile
//
//  Created by fengka on 8/11/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Geometry2D/Point2D.h"
#include "../Events/TouchEventSite.h"

#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_COMMAND_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif


class Document;

namespace Nu {
    
    
	class NU_BASE_API Command : public Nu::TouchEventSite
	{
    public:
        Command(Document* pDoc);
        virtual ~Command();
      
    protected:
        Document* m_pDocument;
	};
    
    class NU_BASE_API LineCommand : public Nu::Command
	{
    public:
        LineCommand(Document* pDoc);
        virtual ~LineCommand();
       
    protected:
		virtual void touchPress(TouchEvent* pEvent);
        virtual void touchMove(TouchEvent* pEvent);
        virtual void touchRelease(TouchEvent* pEvent);
        
    private:
        Point2D m_firstPoint;
	};
    
    
}

#undef NU_BASE_API
