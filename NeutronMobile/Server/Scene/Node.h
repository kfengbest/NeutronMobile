#pragma once

#include "../Base/Globals.h"
#include "../Geometry2D/Entity.h"
#include "../Types/Matrix.hpp"

#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_NODE_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif

namespace Ns { namespace Scene {
    
    class Scene;
    
    class NS_SCENE_API Node : Entity
    {
    public:
        Node();
        virtual ~Node();
        
        const mat4& globalMatrix() const {return m_globalMatrix;}
        void globalMatrix(const mat4& matrix){m_globalMatrix = matrix;}

        const vec4& color() const {return m_color;}
        void color(const vec4& c){m_color = c;}

    private:
        mat4 m_globalMatrix;
        vec4 m_color;
    };
}}


#undef NS_SCENE_API

