

#ifndef __T3D_GEOMETRY_DATA_H__
#define __T3D_GEOMETRY_DATA_H__


#include "Misc/T3DObject.h"
#include "T3DPrerequisitesInternal.h"
#include "DataStruct/T3DVertexData.h"
#include "DataStruct/T3DIndexData.h"
#include "T3DTypedefInternal.h"
#include "Support/tinyxml2/tinyxml2.h"
#include "Render/T3DRenderer.h"


namespace Tiny3D
{
    class GeometryData : public Object
    {
    public:
        typedef std::vector<VertexElement>          VertexAttributes;
        typedef VertexAttributes::iterator          VertexAttributesItr;
        typedef VertexAttributes::const_iterator    VertexAttributesConstItr;

        typedef std::vector<uint8_t>        Vertices;
        typedef Vertices::iterator          VerticesItr;
        typedef Vertices::const_iterator    VerticesConstItr;

        typedef std::vector<uint8_t>        Indices;
        typedef Indices::iterator           IndicesItr;
        typedef Indices::const_iterator     IndicesConstItr;

        struct VertexBuffer
        {
            Vertices            vertices;
            size_t              vertexSize;
        };

        typedef std::vector<VertexBuffer>       VertexBuffers;
        typedef VertexBuffers::iterator         VertexStreamItr;
        typedef VertexBuffers::const_iterator   VertexStreamConstItr;

        /**
         * @brief ���������������ݶ���
         * @param [in] primitiveType : ��Ⱦ�õ�ͼԪ����
         * @param [in] attributes : �������Լ���
         * @param [in] vertices : �������ݻ���
         * @param [in] vertexSize : ������������ռ�õ��ֽڴ�С
         * @param [in] indices : �������ݻ���
         * @param [in] is16bits : ����������16λ����32λ
         * @param [in] materialName : ������Դ����
         * @return ����һ��������Ⱦ���ݶ���
         */
        static GeometryDataPtr create(Renderer::PrimitiveType primitiveType, const VertexAttributes &attributes, const VertexBuffers &buffers, const Indices &indices, bool is16bits, const String &materialName);

        virtual ~GeometryData();

        Renderer::PrimitiveType getPrimitiveType() const
        {
            return mPrimitiveType;
        }

        const VertexBuffers &getVertexBuffers() const
        {
            return mVertexData;
        }

        const IndexDataPtr &getIndexData() const
        {
            return mIndexData;
        }

        const String &getMaterialName() const
        {
            return mMaterialName;
        }

    protected:
        GeometryData();
        bool init(Renderer::PrimitiveType primitiveType, const VertexAttributes &attributes, const VertexBuffers &buffers, const Indices &indices, bool is16bits, const String &materialName);

    private:
        GeometryData(const GeometryData &);
        GeometryData &operator =(const GeometryData &);

    protected:
        Renderer::PrimitiveType mPrimitiveType;
        VertexBuffers           mVertexBuffers;
        Indices
        String                  mMaterialName;
    };
}


#endif  /*__T3D_GEOMETRY_DATA_H__*/
