

#ifndef __MCONV_PREREQUISITES_H__
#define __MCONV_PREREQUISITES_H__


#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include <fbxsdk.h>

#include <T3DLog.h>
#include <T3DPlatform.h>


namespace mconv
{
    enum FileType
    {
        E_FILETYPE_AUTO     = 0,        /// ������չ���Զ��ж��ļ���ʽ
        E_FILETYPE_FBX      = 0x10,     /// FBX��ʽ
        E_FILETYPE_DAE      = 0x20,     /// DAE��ʽ
        E_FILETYPE_T3DB     = 0x40,     /// T3D�����Ƹ�ʽ
        E_FILETYPE_T3DT     = 0x41,     /// T3D�ı�XML��ʽ
        E_FILETYPE_T3D      = E_FILETYPE_T3DB|E_FILETYPE_T3DT,  /// T3D�����ƺ��ı���ʽ
    };

    typedef FbxDouble3 FbxVector3;

    typedef std::list<FbxVector2>           VectorElements2;
    typedef VectorElements2::iterator       VectorElements2Itr;
    typedef VectorElements2::const_iterator VectorElements2ConstItr;

    typedef std::list<FbxVector3>           VectorElements3;
    typedef VectorElements3::iterator       VectorElements3Itr;
    typedef VectorElements3::const_iterator VectorElements3ConstItr;

    typedef std::list<FbxVector4>           VectorElements4;
    typedef VectorElements4::iterator       VectorElements4Itr;
    typedef VectorElements4::const_iterator VectorElements4ConstItr;
}



#endif  /*__MCONV_PREREQUISITES_H__*/
