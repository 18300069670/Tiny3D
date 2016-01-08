
#ifndef __T3D_SG_MESH_H__
#define __T3D_SG_MESH_H__


#include "SG/Visual/T3DSGVisual.h"


namespace Tiny3D
{
    class T3D_ENGINE_API SGMesh : public SGVisual
    {
    public:
        enum Type
        {
            E_TYPE_NONE = 0,            /// ��mesh
            E_TYPE_BUILT_IN_BOX,        /// ����������mesh
            E_TYPE_BUILT_IN_SPHERE,     /// ��������mesh
            E_TYPE_BUILT_IN_PLANE,      /// ����ƽ��mesh
            E_TYPE_CUSTOM_MESH,         /// �ⲿ���ص�mesh
        };
        static SGNodePtr create(uint32_t unID = E_NID_AUTOMATIC);

        virtual ~SGMesh();

        bool loadBuiltInMesh(Type meshType);
        
    protected:
        SGMesh(uint32_t unID = E_NID_AUTOMATIC);


    };
}


#endif  /*__T3D_SG_MESH_H__*/
