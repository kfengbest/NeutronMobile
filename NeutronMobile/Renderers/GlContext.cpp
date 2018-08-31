
#include "GlContext.h"
#include "../Server/Scene/Camera.h"
#include "../Server/Scene/Renderer.h"
#include "../Server/Scene/Scene.h"


GlContext::GlContext()
: m_width(0),
m_height(0)
{
    
}
GlContext::~GlContext()
{
    
}

GlContext* GlContext::get()
{
    static GlContext ctx;
    return &ctx;
}

void GlContext::initialize(int width, int height)
{
    m_width = width;
    m_height = height;
    
    m_pCamera = new Ns::Scene::Camera();
    m_pCamera->initialize(width, height);
}
