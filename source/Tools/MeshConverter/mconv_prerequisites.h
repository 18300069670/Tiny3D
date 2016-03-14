

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
}



#endif  /*__MCONV_PREREQUISITES_H__*/
