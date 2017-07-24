

#ifndef __T3D_FONT_H__
#define __T3D_FONT_H__


#include "T3DResource.h"
#include "Resource/T3DMaterial.h"


namespace Tiny3D
{
    class T3D_ENGINE_API Font : public Resource
    {
    public:
        enum FontType
        {
            E_FT_TRUETYPE = 1,
            E_FT_IMAGE = 2,
        };

        class Char : public Object
        {
        public:
            Char()
                : mCode(0)
            {}

            ObjectPtr       mBlock;         /// �ַ���Ӧ������Ϣ����
            int32_t         mCode;          /// �ַ�����
            Rect            mArea;          /// �ַ���Ӧ������������Ϣ
        };

        T3D_DECLARE_SMART_PTR(Char);

        typedef std::vector<CharPtr>    CharSet;
        typedef CharSet::iterator       CharSetItr;
        typedef CharSet::const_iterator CharSetConstItr;
        typedef CharSet::value_type     CharSetValue;

        static FontPtr create(const String &name, int32_t fontSize, FontType fontType);

        virtual ~Font();

        virtual Type getType() const override;

        /**
         * @brief ���������С
         */
        int32_t getFontSize() const { return mFontSize; }

        /**
         * @brief �����������ͣ���TRUETYPE����IMAGEͼ��
         * @see enum FontType
         */
        FontType getFontType() const { return mFontType; }

        /**
         * @brief �������ݣ���Ҫ�Ǹ�����������
         * @param [in] text : UTF8���ı��ַ���
         * @param [out] material : ���ذ����ı��Ĳ��ʶ���
         * @param [out] set : �����ַ�����Ϣ
         * @return �ɹ�����������ʺ������򷵻�true�����򷵻�false.
         * @see class Char
         */
        virtual bool updateContent(const String &text, MaterialPtr &material, CharSet &set) = 0;

    protected:
        Font(const String &name, int32_t fontSize, FontType fontType);

    protected:
        int32_t     mFontSize;
        FontType    mFontType;
    };
}


#endif  /*__T3D_FONT_H__*/
