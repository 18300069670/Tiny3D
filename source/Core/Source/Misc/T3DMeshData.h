

#ifndef __T3D_MESH_DATA_H__
#define __T3D_MESH_DATA_H__


#include "T3DPrerequisitesInternal.h"
#include "T3DTypedefInternal.h"
#include "Misc/T3DObject.h"
#include "Render/T3DHardwareVertexBuffer.h"
#include "Render/T3DRenderer.h"
#include "T3DSubMeshData.h"


namespace Tiny3D
{
    /**
     * @brief ���㻺����
     */
    class VertexBuffer : public Object
    {
    public:
        typedef std::list<VertexElement>        Attributes;
        typedef Attributes::iterator            AttributesItr;
        typedef Attributes::const_iterator      AttributesConstItr;

        typedef std::vector<uint8_t>            Vertices;
        typedef Vertices::iterator              VerticesItr;
        typedef Vertices::const_iterator        VerticesConstItr;

        static VertexBufferPtr create();

        String                  mName;          /// ����������
        Attributes              mAttributes;    /// �������ж�������
        Vertices                mVertices;      /// ��������������
        size_t                  mVertexSize;    /// ÿ������Ĵ�С����λ���ֽ�

    protected:
        VertexBuffer();

    private:
        VertexBuffer(const VertexBuffer &rkOther);
        VertexBuffer &operator =(const VertexBuffer &rkOther);
    };

    /**
     * @brief ��������
     */
    class MeshData : public Object
    {
    public:
        typedef std::list<VertexBufferPtr>      VertexBuffers;
        typedef VertexBuffers::iterator         VertexBuffersItr;
        typedef VertexBuffers::const_iterator   VertexBuffersConstItr;

        typedef std::list<SubMeshDataPtr>       SubMeshDataList;
        typedef SubMeshDataList::iterator       SubMeshDataListItr;
        typedef SubMeshDataList::const_iterator SubMeshDataListConstItr;

        static MeshDataPtr create();

        String              mName;              /// ��������
        VertexBuffers       mBuffers;           /// ����ӵ�еĶ��㻺�����б�
        SubMeshDataList     mSubMeshes;         /// �������б�

    protected:
        MeshData();

    private:
        MeshData(const MeshData &rkOther);
        MeshData &operator =(const MeshData &rkOther);
    };
}


#endif  /*__T3D_MESH_DATA_H__*/
