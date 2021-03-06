/*******************************************************************************
 * This file is part of Mesh-converter (A mesh converter for Tiny3D Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#ifndef __MCONV_VERTEX_H__
#define __MCONV_VERTEX_H__


#include "mconv_prerequisites.h"


namespace mconv
{
    class VertexAttribute
    {
    public:
        enum VertexType
        {
            E_VT_POSITION = 0,
            E_VT_TEXCOORD,
            E_VT_NORMAL,
            E_VT_TANGENT,
            E_VT_BINORMAL,
            E_VT_COLOR,
            E_VT_BLEND_WEIGHT,
            E_VT_BLEND_INDEX,
            E_MAX_VERTEX_TYPE,
        };

        enum DataType
        {
            E_VT_FLOAT = 0,
            E_VT_DOUBLE,
            E_VT_INT8,
            E_VT_INT16,
            E_VT_INT32,
            E_VT_INT64,
            E_MAX_DATA_TYPE,
        };

        String vertexTypeStr() const;
        String dataTypeStr() const;

        bool operator ==(const VertexAttribute &rkOther) const
        {
            return (mVertexType == rkOther.mVertexType && mSize == rkOther.mSize && mDataType == rkOther.mDataType);
        }

        bool operator !=(const VertexAttribute &rkOther) const
        {
            return !operator==(rkOther);
        }

        VertexType  mVertexType;
        int         mSize;
        DataType    mDataType;
    };

    typedef std::list<VertexAttribute>          VertexAttributes;
    typedef VertexAttributes::iterator          VertexAttributesItr;
    typedef VertexAttributes::const_iterator    VertexAttributesConstItr;

    class BlendInfo
    {
    public:
        BlendInfo()
            : mBlendIndex(-1)
            , mBlendWeight(0.0f)
        {

        }

        bool operator <(const BlendInfo &other) const
        {
            return mBlendWeight < other.mBlendWeight;
        }

        bool operator ==(const BlendInfo &other) const
        {
            return (mBlendWeight == other.mBlendWeight && mBlendIndex == other.mBlendIndex);
        }

        int     mBlendIndex;
        float   mBlendWeight;
    };

//     typedef std::map<float, BlendInfo>      BlendInfoDict;
//     typedef BlendInfoDict::iterator         BlendInfoDictItr;
//     typedef BlendInfoDict::const_iterator   BlendInfoDictConstItr;
//     typedef std::pair<float, BlendInfo>     BlendInfoValue;
    typedef std::list<BlendInfo>                BlendInfoList;
    typedef BlendInfoList::iterator             BlendInfoListItr;
    typedef BlendInfoList::const_iterator       BlendInfoListConstItr;

    class Vertex
    {
    public:

        Vertex()
            : mCtrlPointIdx(0)
            , mPosition(0.0, 0.0, 0.0)
            , mMaterialIdx(-1)
            , mHash(0)
        {

        }

        void hash()
        {
            std::vector<float> vertices;
            vertices.push_back(mPosition[0]);
            vertices.push_back(mPosition[1]);
            vertices.push_back(mPosition[2]);

            auto itr2 = mTexElements.begin();
            while (itr2 != mTexElements.end())
            {
//                 FbxVector2 &texcoord = *itr2;
                const Vector2 &texcoord = *itr2;
                vertices.push_back(texcoord[0]);
                vertices.push_back(texcoord[1]);
                ++itr2;
            }

            auto itr3 = mNormalElements.begin();
            while (itr3 != mNormalElements.end())
            {
//                 FbxVector3 &normal = *itr3;
                const Vector3 &normal = *itr3;
                vertices.push_back(normal[0]);
                vertices.push_back(normal[1]);
                vertices.push_back(normal[2]);
                ++itr3;
            }

            itr3 = mBinormalElements.begin();
            while (itr3 != mBinormalElements.end())
            {
//                 FbxVector3 &binormal = *itr3;
                const Vector3 &binormal = *itr3;
                vertices.push_back(binormal[0]);
                vertices.push_back(binormal[1]);
                vertices.push_back(binormal[2]);
                ++itr3;
            }

            itr3 = mTangentElements.begin();
            while (itr3 != mTangentElements.end())
            {
//                 FbxVector3 &tangent = *itr3;
                const Vector3 &tangent = *itr3;
                vertices.push_back(tangent[0]);
                vertices.push_back(tangent[1]);
                vertices.push_back(tangent[2]);
                ++itr3;
            }

            auto itr4 = mColorElements.begin();
            while (itr4 != mColorElements.end())
            {
//                 FbxVector4 &color = *itr4;
                const Vector4 &color = *itr4;
                vertices.push_back(color[0]);
                vertices.push_back(color[1]);
                vertices.push_back(color[2]);
                vertices.push_back(color[3]);
                ++itr4;
            }

            int i = 0;

            if (mBlendInfo.size() > 0)
            {
                auto it = mBlendInfo.rbegin();
                while (it != mBlendInfo.rend() && i < 4)
                {
                    BlendInfo &info = *it;//it->second;
                    vertices.push_back(info.mBlendWeight);
                    ++it;
                    ++i;
                }

                while (i < 4)
                {
                    vertices.push_back(0);
                    ++i;
                }

                i = 0;
                while (it != mBlendInfo.rend() && i < 4)
                {
                    BlendInfo &info = *it;//it->second;
                    vertices.push_back((float)info.mBlendIndex);
                    ++it;
                    ++i;
                }

                while (i < 4)
                {
                    vertices.push_back(-1);
                    ++i;
                }
            }

            char *str = (char *)vertices.data();
            int32_t count = vertices.size() * sizeof(float);

            uint32_t value = 5381;
            i = 0;
            while (i < count)
            {
                value += (value << 5) + (*str++);
                i++;
            }

            mHash = (value & 0x7FFFFFFF);
        }

        bool operator <(const Vertex &other) const
        {
            return mHash < other.mHash;
        }

        bool operator ==(const Vertex &other) const
        {
            return mHash == other.mHash;
        }

        int                 mCtrlPointIdx;
        Vector3             mPosition;
        VectorElements2     mTexElements;
        VectorElements3     mNormalElements;
        VectorElements3     mBinormalElements;
        VectorElements3     mTangentElements;
        VectorElements4     mColorElements;
//         BlendInfoDict       mBlendInfo;
        BlendInfoList       mBlendInfo;
        int                 mMaterialIdx;

        uint32_t            mHash;
    };

    typedef std::vector<Vertex>         Vertices;
    typedef Vertices::iterator          VerticesItr;
    typedef Vertices::const_iterator    VerticesConstItr;
}


#endif  /*__MCONV_VERTEX_H__*/
