

#include "Resource/T3DFontFreeType.h"
#include "Resource/T3DMaterial.h"
#include "Resource/T3DMaterialManager.h"
#include "Resource/T3DTexture.h"
#include "Resource/T3DTextureManager.h"
#include "Resource/T3DArchive.h"
#include "Resource/T3DArchiveManager.h"



namespace Tiny3D
{
    FontFreeTypePtr FontFreeType::create(const String &name, int32_t fontSize, FontType fontType, const FontConfig &fontConfig)
    {
        FontFreeTypePtr font = new FontFreeType(name, fontSize, fontType, fontConfig);
        font->release();
        return font;
    }

    FontFreeType::FontFreeType(const String &name, int32_t fontSize, FontType fontType, const FontConfig &fontConfig)
        : Font(name, fontSize, fontType, fontConfig)
    {

    }

    FontFreeType::~FontFreeType()
    {

    }

    bool FontFreeType::load()
    {
        bool ret = false;

        ArchivePtr archive;
        MemoryDataStream stream;

        if (T3D_ARCHIVE_MGR.getArchive(mName, archive))
        {
            if (archive->read(mName, stream))
            {
                ret = loadFreeType(stream);
            }
        }

        return ret;
    }

    void FontFreeType::unload()
    {
        FT_Done_FreeType(mFTLibrary);

        Font::unload();
    }

    ResourcePtr FontFreeType::clone() const
    {
        return FontFreeType::create(mName, mFontSize, mFontType, mFontConfig);
    }

    bool FontFreeType::loadFreeType(DataStream &stream)
    {
        bool ret = false;

        do 
        {
            // ��ʼ��freetype
            if (FT_Init_FreeType(&mFTLibrary))
            {
                T3D_LOG_ERROR("Could not init FreeType library !");
                break;
            }

            // ����һ������
            FT_Face face;
            uint8_t *data;
            size_t size = stream.read(data);

            if (FT_New_Memory_Face(mFTLibrary, data, size, 0, &face))
            {
                T3D_LOG_ERROR("Could not open font face !");
                break;
            }

            // ѡ��һ���ַ�����ǰѡ��UNICODE
            FT_Select_Charmap(face, FT_ENCODING_UNICODE);

            // �����ַ���С������26.6�����趨
            FT_F26Dot6 ftSize = (FT_F26Dot6)(mFontSize * (1 << 6));
            int32_t dpi = 72;
            if (FT_Set_Char_Size(face, ftSize, 0, dpi, dpi))
            {
                T3D_LOG_ERROR("Set font size failed !");
                break;
            }

            mFTFace = face;
            ret = true;
        } while (0);

        return ret;
    }

    bool FontFreeType::updateContent(const String &text, MaterialPtr &material, CharSet &set)
    {
        bool ret = false;

        do 
        {
            UTF16String u16text;
            TextCodec::getInstance().UTF8ToUTF16(text, u16text);

            CharPtr ch;
            size_t i = 0;
            for (i = 0; i < u16text.length(); ++i)
            {
                // װ�����ε����β�
                size_t code = u16text[i];
                if (FT_Load_Char(mFTFace, code, FT_LOAD_RENDER))
                {
                    continue;
                }

                // ��������������Ƿ����ֳ��ַ�
                BlockPtr block;
                if (!lookupCharMap(code, block, ch))
                {
                    // û�ҵ����棬�²���һ���ַ�������������
                    if (!insertCharMap(code, block, ch))
                    {
                        continue;
                    }
                }

                mFTFace->glyph->bitmap;
            }

            // ��Ϊȷ������ַ����������ַ�����һ������һ�����������ֱ�ӷ�������һ���ַ���Ӧ�Ĳ��ʾͿ�����
            material = ch->mMaterial;
            ret = true;
        } while (0);

        return ret;
    }

    bool FontFreeType::lookupCharMap(int32_t code, BlockPtr &block, CharPtr &ch)
    {
        bool found = false;

        // �ȱ������ʣ��������濴�Ƿ����ʺϵ������С����
        if (lookupBlock(block))
        {
            // ���ҵ��ֺŶ�Ӧ�����飬�����Ƿ��и��ַ�
            auto itrCh = block->charmap.find(code);

            if (itrCh != block->charmap.end())
            {
                found = true;
                ch = itrCh->second;
            }
        }

        return found;
    }

    bool FontFreeType::insertCharMap(int32_t code, BlockPtr block, CharPtr &ch)
    {
        bool ret = false;

        do 
        {
            // ����һ���ʺϵ�block����������ֺŵ��ı�
            if (block == nullptr)
            {
                if (!insertBlock(block))
                {
                    T3D_LOG_ERROR("Insert block failed !");
                    break;
                }
            }

            ret = true;
        } while (0);

        return ret;
    }

    bool FontFreeType::lookupBlock(BlockPtr &block)
    {
        bool found = false;

        // �ȱ������ʣ��������濴�Ƿ����ʺϵ������С����
        for (auto i = mBlocks.begin(); i != mBlocks.end(); ++i)
        {
            BlockMap &blockmap = i->second;
            auto itr = blockmap.find(mFontSize);

            if (itr != blockmap.end())
            {
                found = true;
                block = itr->second;
            }
        }

        return found;
    }

    bool FontFreeType::insertBlock(BlockPtr &block)
    {
        bool ret = false;

        do 
        {
            String name = mName + "_#0";

            MaterialPtr temp = MaterialManager::getInstance().loadMaterial(name, Material::E_MT_MANUAL);
            if (temp == nullptr)
            {
                T3D_LOG_ERROR("Load font %s material failed !", name.c_str());
                break;
            }

            Texture *texture = temp->getTexture(0);

            if (texture == nullptr)
            {
                // û�����������״δ������ʣ����������в��������ȡ����
                temp->setAmbientColor(Color4::WHITE);
                temp->setDiffuseColor(Color4::WHITE);
                temp->setSpecularColor(Color4::WHITE);
                temp->setEmissiveColor(Color4::WHITE);

                texture = TextureManager::getInstance().loadTexture(name, mFontConfig.initTexWidth, mFontConfig.initTexHeight, 1, E_PF_A8R8G8B8, Texture::E_TU_BLANK);
                if (texture == nullptr)
                {
                    T3D_LOG_ERROR("Load font %s texture failed !", name.c_str());
                    break;
                }

                temp->setTexture(0, texture);
            }

            ret = true;
        } while (0);

        return ret;
    }
}
