//
//  GLView.h
//  TestGL
//
//  Created by fengka on 8/25/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <GLKit/GLKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import "Server/Scene/Renderer.h"

@interface Graphics3dView : UIView{
    EAGLContext* m_context;
    Ns::Scene::Renderer* m_pRenderer;
}

@end
