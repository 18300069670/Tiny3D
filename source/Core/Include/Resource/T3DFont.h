

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

        struct FontConfig
        {
            enum Strategy
            {
                E_STRATEGY_AUTO = 0,    /// �ڲ��Զ�ѡ��
                E_STRATEGY_LRU,         /// ������ռ䲻��ʱ��ʹ��LRU�㷨��̭�ʱ��û����Ⱦ������
                E_STRATEGY_APPEND,      /// ��������һ�����ʺ�����
            };

            enum DefaultValue
            {
                E_DEFAULT_SIZE = 512,
                E_DEFAULT_MAX = 2048,
            };

            FontConfig()
                : initTexWidth(E_DEFAULT_SIZE)
                , initTexHeight(E_DEFAULT_SIZE)
                , maxTexWidth(E_DEFAULT_MAX)
                , maxTexHeight(E_DEFAULT_MAX)
                , strategy(E_STRATEGY_AUTO)
            {
            }

            size_t      initTexWidth;       /// ��ʼ�����ȣ�Ĭ����512
            size_t      initTexHeight;      /// ��ʼ����߶ȣ�Ĭ����512
            size_t      maxTexWidth;        /// ��������ȣ���ֵ���Ӳ��֧����������ȱȽ�ȡ��Сֵ��Ĭ����2048
            size_t      maxTexHeight;       /// �������߶ȣ���ֵ���Ӳ��֧���������߶ȱȽ�ȡ��Сֵ��Ĭ����2048
            Strategy    strategy;           /// ������ԣ�Ĭ����E_STRATEGY_AUTO���������ݲ�ͬ������ʵ��������
        };

        class Char : public Object
        {
        public:
            Char()
                : mCode(0)
            {}

            MaterialPtr     mMaterial;      /// ���ʶ���
            int32_t         mCode;          /// �ַ�����
            Rect            mArea;          /// �ַ���Ӧ������������Ϣ
        };

        T3D_DECLARE_SMART_PTR(Char);

        typedef std::vector<CharPtr>    CharSet;
        typedef CharSet::iterator       CharSetItr;
        typedef CharSet::const_iterator CharSetConstItr;
        typedef CharSet::value_type     CharSetValue;

        static FontPtr create(const String &name, int32_t fontSize, FontType fontType, const FontConfig &fontConfig);

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
        Font(const String &name, int32_t fontSize, FontType fontType, const FontConfig &fontConfig);

    protected:
        int32_t     mFontSize;
        FontType    mFontType;
        FontConfig  mFontConfig;
    };
}


#endif  /*__T3D_FONT_H__*/
