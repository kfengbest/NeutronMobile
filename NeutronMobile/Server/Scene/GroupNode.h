#pragma once

#include "../Base/Globals.h"
#include "Node.h"
#include "vector"

#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_GROUPNODE_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif

namespace Ns { namespace Scene {
    
    class Scene;
    
    class NS_SCENE_API GroupNode : public Node
    {
    public:
        typedef std::vector<Node*> NodeList;
        
        GroupNode();
        virtual ~GroupNode();
        
        void					addChild(Node* pNode);
        void					removeChild(Node* pNode);
        void					removeAllChildren();
        const NodeList&			children() const;

        
    private:
        NodeList m_children;

    };
}}


#undef NS_SCENE_API

