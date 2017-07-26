
#ifndef __T3D_FONT_FREE_TYPE_H__
#define __T3D_FONT_FREE_TYPE_H__


#include "Resource/T3DFont.h"
#include "T3DPrerequisitesInternal.h"
#include "T3DTypedefInternal.h"
#include "Misc/T3DObject.h"
#include "Misc/T3DSmartPtr.h"

#define generic _generic    // keyword for C++/CX
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#undef generic


namespace Tiny3D
{
    class FontFreeType : public Font
    {
    public:
        static FontFreeTypePtr create(const String &name, int32_t fontSize, FontType fontType);

        virtual ~FontFreeType();

        /**
         * @brief ��ȡĳһ���ַ��Ŀ��
         * @note 
         *  - ����û�л�����ַ�������ӿڵ��û��������ϵ���ģ����ҵ�����󣬸��ַ�Ҳ���ᱻ����
         *  - �����Ѿ���������ַ������ֱ�Ӵӻ����з���
         */
        virtual int32_t getCharWidth(int32_t code) const override;

        /**
         * @brief ��ȡĳһ���ַ��ĸ߶�
         * @note ����û�л�����ַ�������ӿڵ��û��������ϵ���ģ����ҵ�����󣬸��ַ�Ҳ���ᱻ����
         */
        virtual int32_t getCharHeight(int32_t code) const override;

        /**
         * @brief ��ȡĳһ���ַ��Ŀ��
         * @note 
         *  - ����û�л�����ַ�������ӿڵ��û��������ϵ���ģ����ҵ�����󣬸��ַ�Ҳ���ᱻ����
         *  - �����Ѿ���������ַ������ֱ�Ӵӻ����з���
         *  - ����ӿ�����ڷֱ��������getFontWidth(int32_t)��getFontHeight(int32_t)���ܻ��һЩ����Ϊ���ֻ��Ҫ��Ⱦһ�ε�bitmap
         */
        virtual Size getCharSize(int32_t code) const override;

        /**
         * @brief �������ݣ���Ҫ�Ǹ�����������
         * @param [in] text : UTF8���ı��ַ���
         * @param [out] material : ���ذ����ı��Ĳ��ʶ���
         * @param [out] set : �����ַ�����Ϣ
         * @return �ɹ�����������ʺ������򷵻�true�����򷵻�false.
         * @see class Char
         */
        virtual bool updateContent(const String &text, MaterialPtr &material, CharSet &set) override;

        /**
         * @brief ͨ��freetype�����bitmap
         * @param [in] code : �ַ���UNICODE����
         * @param [out] charSize : �����ַ��Ŀ��
         * @return ����λͼ�ɹ�����ture�����򷵻�false
         */
        bool loadBitmap(int32_t code, Size &charSize);

        /**
         * @brief ��λͼ������Ⱦ������ָ������
         * @param [in] texture : �������
         * @param [in] dstRect : Ŀ������
         */
        bool renderAt(TexturePtr texture, const Rect &dstRect);

        FT_Face getFontFace() const { return mFTFace; }

    protected:
        FontFreeType(const String &name, int32_t fontSize, FontType fontType);

        virtual bool load() override;
        virtual void unload() override;
        virtual ResourcePtr clone() const override;

        bool loadFreeType(DataStream &stream);

    protected:
        FT_Library      mFTLibrary;
        FT_Face         mFTFace;
    };
}


#endif  /*__T3D_FONT_FREE_TYPE_H__*/
