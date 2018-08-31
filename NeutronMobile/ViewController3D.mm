//
//  ViewController3D.m
//  TestGL1
//
//  Created by fengka on 8/11/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "ViewController3D.h"
#import "Server/Scene/Scene.h"
#import "Server/Scene/Mesh.h"
#import "Renderers/glMesh.h"
#import "Server/Scene/SceneUtility.h"
#import "Server/Scene/Renderer.h"
#import "Server/Scene/GeometryNode.h"
#import "Server/Scene/GroupNode.h"



@interface ViewController3D ()
{
    
    GLKMatrix4 _rotMatrix;
    GLKMatrix4 _scaleMatrix;
    
    GLKQuaternion _quatStart;
    GLKQuaternion _quat;
    GLKVector3 _anchor_position;
    GLKVector3 _current_position;
    BOOL _slerping;
    float _slerpCur;
    float _slerpMax;
    GLKQuaternion _slerpStart;
    GLKQuaternion _slerpEnd;
    
    Ns::Scene::Renderer* m_pRenderer;
    Ns::Scene::Scene* m_pScene;

}

@property(nonatomic, strong) EAGLContext* context;
@property(nonatomic, strong) GLKBaseEffect* effect;
@end

@implementation ViewController3D
@synthesize context = _context;
@synthesize effect = _effect;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void) setupGL
{
    [EAGLContext setCurrentContext:self.context];
    self.effect = [[GLKBaseEffect alloc] init];
    glEnable(GL_CULL_FACE);
 
    
    m_pRenderer = CreateRenderer();
    m_pScene = new Ns::Scene::Scene();
    
    Ns::Scene::Mesh* pMesh1 = Ns::Scene::SceneUtility::createCube();
    Ns::Scene::GeometryNode* pNode1 = new Ns::Scene::GeometryNode();
    pNode1->geometry(pMesh1);
    m_pScene->rootNode()->addChild(pNode1);
    
    _rotMatrix = GLKMatrix4Identity;
    _scaleMatrix = GLKMatrix4Identity;
    
    _quat = GLKQuaternionMake(0, 0, 0, 1);
    _quatStart = GLKQuaternionMake(0, 0, 0, 1);
    
    UITapGestureRecognizer* dtRecg = [[UITapGestureRecognizer alloc ] initWithTarget:self action:@selector(doubleTap:)];
    dtRecg.numberOfTapsRequired = 2;
    [self.view addGestureRecognizer:dtRecg];
    
    UIPinchGestureRecognizer* pinchRecg = [[UIPinchGestureRecognizer alloc]initWithTarget:self action:@selector(pinching:)];
    [self.view addGestureRecognizer:pinchRecg];
    
    
}

- (void) tearDownGL
{

    self.effect = nil;
}


- (void) glkView:(GLKView*) view drawInRect:(CGRect)rect
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    [self.effect prepareToDraw];
    GLKMatrix4 modelviewMatrix = GLKMatrix4MakeTranslation(0, 0, -6.0);
    modelviewMatrix = GLKMatrix4Rotate(modelviewMatrix, GLKMathDegreesToRadians(45), 1, 0, 0);
    modelviewMatrix = GLKMatrix4Multiply(modelviewMatrix, _rotMatrix);
    modelviewMatrix = GLKMatrix4Multiply(modelviewMatrix, _scaleMatrix);
    self.effect.transform.modelviewMatrix = modelviewMatrix;
   
    m_pRenderer->render3D(m_pScene);
    
}

- (void) update
{
    float aspect = fabs(self.view.bounds.size.width / self.view.bounds.size.height);
    GLKMatrix4 projMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(60.0), aspect, 1.0, 10.0);
    self.effect.transform.projectionMatrix = projMatrix;
    
    if (_slerping) {
        
        _slerpCur += self.timeSinceLastUpdate;
        float slerpAmt = _slerpCur / _slerpMax;
        if (slerpAmt > 1.0) {
            slerpAmt = 1.0;
            _slerping = NO;
        }
        
        _quat = GLKQuaternionSlerp(_slerpStart, _slerpEnd, slerpAmt);
    }

    _rotMatrix = GLKMatrix4MakeWithQuaternion(_quat);
    
}

- (GLKVector3) projectOntoSurface:(GLKVector3) touchPoint
{
    float radius = self.view.bounds.size.width/3;
    GLKVector3 center = GLKVector3Make(self.view.bounds.size.width/2, self.view.bounds.size.height/2, 0);
    GLKVector3 P = GLKVector3Subtract(touchPoint, center);
    
    // Flip the y-axis because pixel coords increase toward the bottom.
    P = GLKVector3Make(P.x, P.y * -1, P.z);
    
    float radius2 = radius * radius;
    float length2 = P.x*P.x + P.y*P.y;
    
    if (length2 <= radius2)
        P.z = sqrt(radius2 - length2);
    else
    {
        P.z = radius2 / (2.0 * sqrt(length2));
        float length = sqrt(length2 + P.z * P.z);
        P = GLKVector3DivideScalar(P, length);
    }
    
    return GLKVector3Normalize(P);
}

- (void)computeIncremental {
    
    GLKVector3 axis = GLKVector3CrossProduct(_anchor_position, _current_position);
    float dot = GLKVector3DotProduct(_anchor_position, _current_position);
    float angle = acosf(dot);
    
    GLKQuaternion Q_rot = GLKQuaternionMakeWithAngleAndVector3Axis(angle * 2, axis);
    Q_rot = GLKQuaternionNormalize(Q_rot);
    
    // TODO: Do something with Q_rot...
    _quat = GLKQuaternionMultiply(Q_rot, _quatStart);
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {

    UITouch * touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    
    _anchor_position = GLKVector3Make(location.x, location.y, 0);
    _anchor_position = [self projectOntoSurface:_anchor_position];
    
    _current_position = _anchor_position;
    _quatStart = _quat;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    
    UITouch * touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    CGPoint lastLoc = [touch previousLocationInView:self.view];
    CGPoint diff = CGPointMake(lastLoc.x - location.x, lastLoc.y - location.y);
    
    float rotX = -1 * GLKMathDegreesToRadians(diff.y / 2.0);
    float rotY = -1 * GLKMathDegreesToRadians(diff.x / 2.0);
    
    bool isInvertible;
    GLKVector3 xAxis = GLKMatrix4MultiplyVector3(GLKMatrix4Invert(_rotMatrix, &isInvertible), GLKVector3Make(1, 0, 0));
    _rotMatrix = GLKMatrix4Rotate(_rotMatrix, rotX, xAxis.x, xAxis.y, xAxis.z);
    GLKVector3 yAxis = GLKMatrix4MultiplyVector3(GLKMatrix4Invert(_rotMatrix, &isInvertible), GLKVector3Make(0, 1, 0));
    _rotMatrix = GLKMatrix4Rotate(_rotMatrix, rotY, yAxis.x, yAxis.y, yAxis.z);
    
    _current_position = GLKVector3Make(location.x, location.y, 0);
    _current_position = [self projectOntoSurface:_current_position];
    
    [self computeIncremental];
}

- (void)doubleTap:(UITapGestureRecognizer *)tap {
    
    _slerping = YES;
    _slerpCur = 0;
    _slerpMax = 1.0;
    _slerpStart = _quat;
    _slerpEnd = GLKQuaternionMake(0, 0, 0, 1);
    
}

- (void)pinching:(UIPinchGestureRecognizer *)sender {
    
    float scale = sender.scale;
    _scaleMatrix = GLKMatrix4MakeScale(scale, scale, scale);
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    GLKView* glView = (GLKView*)self.view;
    glView.context = self.context;
    glView.drawableMultisample = GLKViewDrawableMultisample4X;
    
    [self setupGL];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

@end
