

#ifndef __MCONV_SETTING_H__
#define __MCONV_SETTING_H__


#include "mconv_prerequisites.h"


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

    class Settings
    {
    public:
        String  mSrcPath;
        String  mDstPath;

        FileType    mSrcType;
        FileType    mDstType;

        bool    mVerbose;
    };
}


#endif  /*__MCONV_SETTING_H__*/