//
//  GLView.m
//  TestGL
//
//  Created by fengka on 8/25/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "Graphics3dView.h"

#import "Server/Scene/Scene.h"
#import "Server/Scene/Mesh.h"
#import "Renderers/glMesh.h"
#import "Server/Scene/SceneUtility.h"
#import "Server/Scene/Renderer.h"
#import "Server/Scene/Camera.h"
#import "Server/Scene/GeometryNode.h"
#import "Server/Scene/GroupNode.h"
#import "Server/Scene/ObjMesh.h"
#import "Server/Base/Resources/ResourceMgr.h"
#import "Server/Geometry3D/Totus.h"
#import "Server/Geometry3D/Sphere.h"
#import "Server/Geometry3D/Cone.h"

#import "Renderers/GlContext.h"

const static bool s_forceES1 = true;

namespace Dawin {
    class ResourceManager : public Ns::ResourceMgr {
    public:
        std::string getResourcePath() const
        {
            NSString* bundlePath =[[NSBundle mainBundle] resourcePath];
            return [bundlePath UTF8String];
        }
        
        static ResourceManager* get()
        {
            static ResourceManager mgr;
            return &mgr;
        }
    };
}



@interface Graphics3dView(){
    Ns::Scene::Scene* m_pScene;
}
@end


@implementation Graphics3dView

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*)super.layer;
        eaglLayer.opaque = YES;
        
        EAGLRenderingAPI glapi = kEAGLRenderingAPIOpenGLES2;
        m_context = [[EAGLContext alloc] initWithAPI:glapi];
        if (!m_context || s_forceES1) {
            glapi = kEAGLRenderingAPIOpenGLES1;
            m_context = [[EAGLContext alloc] initWithAPI:glapi];
        }
  
        bool bSetContext = [EAGLContext setCurrentContext:m_context];
        
        if (!m_context || !bSetContext) {
            NSLog(@"init opengl context failed");
            return nil;
        }
        
        if (glapi == kEAGLRenderingAPIOpenGLES1) {
            NSLog(@"Using OpenGL ES 1.1");
            m_pRenderer = CreateRenderer1();
        } else {
            NSLog(@"Using OpenGL ES 2.0");
            m_pRenderer = CreateRenderer2();
        }
        
        [self initScene];

        [m_context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:eaglLayer];

        GlContext::get()->initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
        m_pRenderer->initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
        GlContext::get()->renderer(m_pRenderer);
        
        CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        [displayLink addToRunLoop: [NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        
    
    }
    return self;
}

- (void)initScene
{
   
    m_pScene = new Ns::Scene::Scene();
    GlContext::get()->mainScene(m_pScene);
    
/*   
    Ns::Scene::Mesh* pMesh1 = Ns::Scene::SceneUtility::createCone();
    Ns::Scene::GeometryNode* pNode1 = new Ns::Scene::GeometryNode();
    pNode1->geometry(pMesh1);
    mat4 trans1 = mat4::Translate(-1, 0, 0);
    mat4 rot1 = mat4::Rotate(25, vec3(0,0,1));
    pNode1->globalMatrix( rot1 * trans1);
    m_pScene->rootNode()->addChild(pNode1);
  

    Ns::Scene::Mesh* pMesh2 = Ns::Scene::SceneUtility::createCone();
    Ns::Scene::GeometryNode* pNode2 = new Ns::Scene::GeometryNode();
    pNode2->geometry(pMesh2);
    mat4 trans2 = mat4::Translate(0, -1, 0);
    mat4 scale2 = mat4::Scale(0.8);
    pNode2->globalMatrix(scale2 * trans2);
    m_pScene->rootNode()->addChild(pNode2);

    Ns::Scene::Mesh* pMesh3 = Ns::Scene::SceneUtility::createCone();
    Ns::Scene::GeometryNode* pNode3 = new Ns::Scene::GeometryNode();
    pNode3->geometry(pMesh3);
    mat4 trans3 = mat4::Translate(1, 0, 0);
    mat4 rot3 = mat4::Rotate(-25, vec3(0,0,1));
    pNode3->globalMatrix(rot3 * trans3);
    m_pScene->rootNode()->addChild(pNode3);
   */
    
    Ns::Scene::Geometry* pMesh4 = new Ns::Geometry::Torus(m_pScene, 0.8, 0.2);
    Ns::Scene::GeometryNode* pNode4 = new Ns::Scene::GeometryNode();
    pNode4->geometry(pMesh4);
    mat4 trans4 = mat4::Translate(0, -1, 0);
    pNode4->globalMatrix( trans4);
    pNode4->color(vec4(1.0,0,0,1));
    m_pScene->rootNode()->addChild(pNode4);
    
    Ns::Scene::Geometry* pMesh5 = new Ns::Geometry::Sphere(m_pScene, 0.5);
    Ns::Scene::GeometryNode* pNode5 = new Ns::Scene::GeometryNode();
    pNode5->geometry(pMesh5);
    mat4 trans5 = mat4::Translate(1, 0, 0);
    pNode5->globalMatrix( trans5);
    pNode5->color(vec4(0.0,1.0,0,1));
    m_pScene->rootNode()->addChild(pNode5);
 
    Ns::Scene::Geometry* pMesh6 = new Ns::Geometry::Cone(m_pScene, 1.0, 0.3);
    Ns::Scene::GeometryNode* pNode6 = new Ns::Scene::GeometryNode();
    pNode6->geometry(pMesh6);
    mat4 trans6 = mat4::Translate(-1, 0, 0);
    pNode6->globalMatrix( trans6);
    pNode6->color(vec4(0.0,0.0,1.0,1.0));

    m_pScene->rootNode()->addChild(pNode6);
    
    std::string path = Dawin::ResourceManager::get()->getResourcePath();
    Ns::Scene::Geometry* pMesh7 = new Ns::Scene::ObjMesh(m_pScene,  path + "/Ninja.obj");
    Ns::Scene::GeometryNode* pNode7 = new Ns::Scene::GeometryNode();
    pNode7->geometry(pMesh7);
    mat4 trans7 = mat4::Translate(0, 1, 0);
    pNode7->globalMatrix( trans7);
    
    vec3 color(1,1,0.5);
    color = color * 0.75f;
    vec4 diffuse(color.x, color.y, color.z, 1);
    pNode7->color(diffuse);
    m_pScene->rootNode()->addChild(pNode7);
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

- (void)drawView : (CADisplayLink*) displayLink
{

    m_pRenderer->render3D(m_pScene);
    
    [m_context presentRenderbuffer:GL_RENDERBUFFER_OES];
}

- (void) touchesBegan: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint location  = [touch locationInView: self];
    GlContext::get()->camera()->onFingerDown(ivec2(location.x, location.y));
}

- (void) touchesEnded: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint location  = [touch locationInView: self];
    GlContext::get()->camera()->onFingerUp(ivec2(location.x, location.y));
}

- (void) touchesMoved: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint previous  = [touch previousLocationInView: self];
    CGPoint current = [touch locationInView: self];
    GlContext::get()->camera()->onFingerMove(ivec2(previous.x, previous.y),
                                      ivec2(current.x, current.y));
}

@end
