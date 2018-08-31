#pragma once

#include "../Base/Globals.h"
#include "../Types/Quaternion.hpp"


#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_CAMERA_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif

namespace Ns { namespace Scene {
    
    class Scene;
    
    class NS_SCENE_API Camera{
    
    public:
        
        Camera();
        virtual ~Camera();
        
        void initialize(int width, int height);

        void onFingerUp(ivec2 location);
        void onFingerDown(ivec2 location);
        void onFingerMove(ivec2 oldLocation, ivec2 newLocation);

        const Quaternionf& orientation() const {return m_orientation;}
        
    private:
        vec3 mapToSphere(ivec2 touchpoint) const;

    private:
        Quaternionf m_orientation;
        Quaternionf m_previousOrientation;
        float m_trackballRadius;
        ivec2 m_screenSize;
        ivec2 m_centerPoint;
        ivec2 m_fingerStart;
        bool m_spinning;
    
    };
}}


#undef NS_SCENE_API

