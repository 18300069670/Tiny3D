

#include "Resource/T3DFreeTypeAtlas.h"
#include "Resource/T3DFontManager.h"
#include "Resource/T3DMaterial.h"
#include "Resource/T3DMaterialManager.h"
#include "Resource/T3DTexture.h"
#include "Resource/T3DTextureManager.h"
#include "Misc/T3DColor4.h"


namespace Tiny3D
{
    T3D_INIT_SINGLETON(FreeTypeAtlas);

    FreeTypeAtlas::Face::Face(const String &n, MaterialPtr m)
        : name(n)
        , material(m)
    {
        const FontConfig &config = FontManager::getInstance().getConfig();

        // ������������Ҫ��block����
        int32_t blockCols = config.maxTexWidth / config.blockWidth;
        int32_t blockRows = config.maxTexHeight / config.blockHeight;
        int32_t blockCount = blockCols * blockRows;
        Size blockSize(config.blockWidth, config.blockHeight);

        // �������е�block���ŵ�����������
        for (int32_t i = 0; i < blockCount; i++)
        {
            BlockPtr block = new Block();
            block->release();
            block->face = this;
            block->area.left = i % blockCols * config.blockWidth;
            block->area.right = block->area.left + config.blockWidth - 1;
            block->area.top = i / blockCols * config.blockHeight;
            block->area.bottom = block->area.top + config.blockHeight - 1;
            free.push_back(block);
        }
    }

    FreeTypeAtlas::Face::~Face()
    {
    }

    FreeTypeAtlas::FreeTypeAtlas()
    {

    }

    FreeTypeAtlas::~FreeTypeAtlas()
    {

    }

    bool FreeTypeAtlas::hasCharacter(int32_t code, Font::CharPtr &ch) const
    {
        bool found = false;

        auto itr = mCharmap.find(code);
        if (itr != mCharmap.end())
        {
            ch = itr->second;
            found = true;
        }

        return found;
    }

    bool FreeTypeAtlas::updateContent(FontFreeTypePtr font, const String &text, MaterialPtr &material, Font::CharSet &set)
    {
        bool ret = false;

        do 
        {
            UTF16String u16text;
            TextCodec::getInstance().UTF8ToUTF16(text, u16text);

            FT_Face ftFace = font->getFontFace();

            set.clear();
            Font::CharPtr ch;
            size_t i = 0;
            for (i = 0; i < u16text.length(); ++i)
            {
                // װ�����ε����β�
                size_t code = u16text[i];
                if (FT_Load_Char(ftFace, code, FT_LOAD_RENDER))
                {
                    continue;
                }

                // ��������������Ƿ����ֳ��ַ�
                if (!lookupCharMap(font, code, ch))
                {
                    // û�ҵ����棬�²���һ���ַ�������������
                    if (!insertCharMap(font, code, ch))
                    {
                        continue;
                    }

                    set.push_back(ch);
                }
            }

            if (ch != nullptr)
            {
                BlockPtr block = smart_pointer_cast<Block>(ch->mBlock);
                FacePtr face = smart_pointer_cast<Face>(block->face);
                material = face->material;
                ret = true;
            }
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::lookupCharMap(FontFreeTypePtr font, int32_t code, Font::CharPtr &ch)
    {
        bool found = false;

        auto itr = mCharmap.find(code);
        if (itr != mCharmap.end())
        {
            found = true;
            ch = itr->second;
        }

        return found;
    }

    bool FreeTypeAtlas::insertCharMap(FontFreeTypePtr font, int32_t code, Font::CharPtr &ch)
    {
        bool ret = false;

        do 
        {
            const FontConfig &config = FontManager::getInstance().getConfig();

            // ����һ���ʺϵ�block����������ֺŵ��ı�
            FacePtr face;
            BlockPtr block;
            if (!lookupBlock(font, face, block))
            {
                // û���ҵ�һ�����ʵ����飬ֻ�ܲ���һ���µ�����
                if (!insertBlock(font, face, block))
                {
                    T3D_LOG_ERROR("Insert block failed !");
                }
            }

            if (block != nullptr)
            {
                // ��ȡ����߶�
                int32_t fontWidth = font->getFontWidth();
                int32_t fontHeight = font->getFontHeight();

                // ���ж��Ƿ񹻿ռ�����µ��ַ�
                if (block->offset.x + fontWidth > block->area.width()
                    && block->offset.y + fontHeight > block->area.height())
                {
                    // block�ռ䲻�������ַ���ֻ���½�һ��block
                    block = nullptr;

                    if (!insertBlock(font, face, block))
                    {
                        T3D_LOG_ERROR("Insert block failed !");
                    }
                }
            }

            if (block == nullptr)
            {
                // ����blockʧ���ˣ�����û�ռ��ˣ��������õĲ�ͬ����ȥ�����µĿռ�
                if (FontConfig::E_STRATEGY_LRU == config.strategy)
                {
                    // ֱ��ʹ��LRU��̭û�õ��ַ��������̭�󻹲�����ֻ�ܷ��ش���
                    if (!doStrategyLRU(font, face, block, ch))
                    {
                        break;
                    }
                }
                else if (FontConfig::E_STRATEGY_APPEND == config.strategy)
                {
                    // ���ֲ��Ծ�ֱ���½����ʺ�������������ַ�
                    if (!doStrategyAppend(font, face, block, ch))
                    {
                        break;
                    }
                }
                else
                {
                    // �Զ���������ʹ��LRU��̭û�õ��ַ���ʵ��û����̭��ʱ�����½���������������ַ�
                    if (!doStrategyAuto(font, face, block, ch))
                    {
                        break;
                    }
                }
            }
            else
            {
                // �ף���Ȼ�п���������Բ����µ�block���ǲ�����˼�ˣ�ֻ��������

                // ��ͨ����������� freetype �����λͼ
                Size charSize;

                if (!font->loadBitmap(code, charSize))
                {
                    T3D_LOG_ERROR("Load font bitmap failed !");
                    break;
                }

                // �ж��Ƿ���Ҫ����
                if (block->offset.x + charSize.width > block->area.width())
                {
                    // û�취�ˣ�ֻ�ܻ���
                    block->offset.x = 0;
                    block->offset.y += charSize.height;
                }

                TexturePtr texture = face->material->getTexture(0);
                Point uv(block->area.left + block->offset.x, block->area.top + block->offset.y);
                Rect dstRect(uv, charSize);
                if (!font->renderAt(texture, dstRect))
                {
                    T3D_LOG_ERROR("Render at texture failed !");
                    break;
                }

                ch = new Font::Char();
                ch->release();
                ch->mCode = code;
                ch->mBlock = block;
                ch->mArea = dstRect;

                block->charmap.insert(CharMapValue(code, ch));
                ch->mBlock = block;

                mCharmap.insert(CharMapValue(code, ch));
            }

            ret = true;
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::lookupBlock(FontFreeTypePtr font, FacePtr &face, BlockPtr &block)
    {
        bool found = false;

        // ���������������������Ҷ�Ӧ���������Ϣ
        auto itr = mFaces.find(font->getName());
        if (itr != mFaces.end())
        {
            // �ҵ��ж�Ӧ�����������Ϣ
            FaceList &faceList = itr->second;
            
            // ���������ͬ������۲����Ƿ�����ͬ�����С������Ϣ
            for (auto i = faceList.begin(); i != faceList.end(); ++i)
            {
                FacePtr temp = *i;

                // ������ͬ������ۺ���ͬ�ֺţ����Ƿ��ж�Ӧ������
                auto ii = temp->blockmap.find(font->getFontSize());
                if (ii != temp->blockmap.end())
                {
                    BlockList &blockList = ii->second;

                    // ����϶��������һ������Ϊֻ�����һ�����п����Ǵ��ڿ��������block
                    block = blockList.back();
                    found = true;
                }
                else
                {
                    // ���û����ͬ�ֺŵ�block����ȥ��������������һ������Ϊֻ�����һ�����п��ܴ��ڿ�������
                    face = faceList.back();
                }
            }
        }

        return found;
    }

    bool FreeTypeAtlas::insertBlock(FontFreeTypePtr font, FacePtr face, BlockPtr &block)
    {
        bool ret = false;

        do
        {
            const FontConfig &config = FontManager::getInstance().getConfig();

            Point uv;
            Point offset;
            Size blockSize(config.blockWidth, config.blockHeight);

            if (mFaces.empty() || face == nullptr)
            {
                // �ȼ���һ���µĲ��ʺ�����
                const String &fontName = font->getName();
                size_t faceIdx = 0;
                std::stringstream ss;
                ss << fontName << "_#" << faceIdx;
                String name = ss.str();

                MaterialPtr material;
                if (!loadMaterial(name, font, material, config.incTexWidth, config.incTexHeight))
                {
                    break;
                }

                // ����һ����face
                FacePtr newFace;
                if (!createFace(material, fontName, newFace))
                {
                    break;
                }

                face = newFace;
            }

            T3D_ASSERT(face != nullptr);

            TexturePtr texture = face->material->getTexture(0);
            int32_t texWidth = texture->getTexWidth();
            int32_t texHeight = texture->getTexHeight();

            if (!face->free.empty())
            {
                // ���п���block

                size_t blocksUsed = face->blockmap.size();
                size_t blocksFree = face->free.size();

                {
                    // ֱ����չ����
                    TexturePtr newTexture;
                    if (!extendTexture(face->material->getName(), texture, newTexture))
                    {
                        break;
                    }

                    // ����������չ����
                    face->offset.x = texWidth;
                    face->offset.y = 0;

                    blockSize.width = config.blockWidth;
                    blockSize.height = config.blockHeight;
                    offset.setZero();
                }
                        
                if (!createBlock(font->getFontSize(), Rect(uv, blockSize), offset, face, block))
                {
                    break;
                }

                // ������һ��block��ʼλ�ã�Ϊ�����¿���block�ռ���׼��
                face->offset.x += config.blockWidth;
            }
            else
            {
                // û�п���block��ֱ�Ӹ�������ʧ���ˣ����������Ԥ����Դ���
                break;
            }

            ret = true;
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::doStrategyAuto(FontFreeTypePtr font, FacePtr face, BlockPtr &block, Font::CharPtr &ch)
    {
        bool ret = false;

        do 
        {
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::doStrategyLRU(FontFreeTypePtr font, FacePtr face, BlockPtr &block, Font::CharPtr &ch)
    {
        bool ret = false;

        do 
        {
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::doStrategyAppend(FontFreeTypePtr font, FacePtr face, BlockPtr &block, Font::CharPtr &ch)
    {
        bool ret = false;

        do 
        {
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::loadMaterial(const String &name, FontFreeTypePtr font, MaterialPtr &material, size_t texWidth, size_t texHeight)
    {
        bool ret = false;

        do
        {
            const FontConfig &config = FontManager::getInstance().getConfig();

            material = MaterialManager::getInstance().loadMaterial(name, Material::E_MT_MANUAL);
            if (material == nullptr)
            {
                T3D_LOG_ERROR("Load font %s material failed !", name.c_str());
                break;
            }

            TexturePtr texture = material->getTexture(0);

            if (texture == nullptr)
            {
                // û�����������״δ������ʣ����������в��������ȡ����
                if (!createTexture(name, texWidth, texHeight, texture))
                {
                    break;
                }

                material->setTexture(0, texture);
            }

            ret = true;
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::createFace(MaterialPtr material, const String &fontName, FacePtr &face)
    {
        bool ret = false;

        do 
        {
            auto r = mFaces.insert(FaceMapValue(fontName, FaceList()));
            if (!r.second)
            {
                T3D_LOG_ERROR("Insert font face [%s] failed !", fontName.c_str());
                break;
            }

            face = new Face(fontName, material);
            face->release();

            r.first->second.push_back(face);
            ret = true;
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::createBlock(size_t fontSize, const Rect &area, const Point &offset, FacePtr face, BlockPtr &block)
    {
        bool ret = false;

        do 
        {
            auto r = face->blockmap.insert(BlockMapValue(fontSize, BlockList()));
            if (!r.second)
            {
                T3D_LOG_ERROR("Insert font block [%s_%u] failed !", face->name.c_str(), fontSize);
                break;
            }

            // ��face�Ŀ������������ȡһ�����е�block�������ŵ�blockmap��
            block = face->free.front();
            face->free.pop_front();
            block->size = fontSize;
            block->offset.x = block->offset.y;
            r.first->second.push_back(block);

            ret = true;
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::createTexture(const String &name, size_t texWidth, size_t texHeight, TexturePtr &texture)
    {
        bool ret = false;

        do 
        {
            std::stringstream ss;
            ss << name << "_tex_" << texWidth << "x" << texHeight;
            texture = TextureManager::getInstance().loadTexture(ss.str(), texWidth, texHeight, 1, E_PF_A8R8G8B8, Texture::E_TU_BLANK);
            if (texture == nullptr)
            {
                T3D_LOG_ERROR("Load font %s texture failed !", ss.str().c_str());
                break;
            }

            ret = true;
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::copyBitmapToTexture(FontFreeTypePtr font, BlockPtr block, Font::CharPtr ch)
    {
        bool ret = false;

        do 
        {
            FT_Face ftFace = font->getFontFace();
            
            // Դλͼ����
            Rect srcRect(Point(0, 0), Size(ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows));

            uint8_t *srcData = ftFace->glyph->bitmap.buffer;
            int32_t srcPitch = ftFace->glyph->bitmap.pitch;
            int32_t srcWidth = ftFace->glyph->bitmap.width;
            int32_t srcHeight = ftFace->glyph->bitmap.rows;

            // �����bitmap_left�п��ܴ��ڸ�ֵ
            int32_t srcLeft = (ftFace->glyph->bitmap_left >= 0 ? ftFace->glyph->bitmap_left : 0);
            int32_t srcTop = ftFace->glyph->bitmap_top;

            // ����
            int32_t baseline = (ftFace->size->metrics.ascender >> 6);
            // ����߶�
            int32_t fontHeight = (ftFace->size->metrics.height >> 6);

            // Ŀ���������ʼλ��
            int32_t dstLeft = block->offset.x + srcLeft;
            int32_t dstTop = block->offset.y + baseline - srcTop;

            // ˮƽ����
            int32_t advanceX = ftFace->glyph->metrics.horiAdvance;
            // ����ʵ�ʿ�ȣ�ȡ����ֵ��λͼ������ֵ
            int32_t fontWidth = std::max(advanceX, srcWidth);

            if (dstLeft + fontWidth > block->area.right)
            {
                // ��Ҫ�����ˣ����¼���block���ַ������λ��
                block->offset.x = block->area.left;
                block->offset.y += fontHeight;
                dstLeft = block->offset.x + srcLeft;
            }

            // Ŀ�������������
            Rect dstRect(Point(dstLeft, dstTop), Size(srcWidth, srcHeight));
            T3D_ASSERT(dstRect.bottom <= block->area.bottom);

            // �ַ������ַ������Ŀ��������������ǲ���ͬ�ģ���ΪĿ�����������ǹ̶��߶ȵģ�������������ʵ�ʻ��Ƹ߶�
            ch->mArea.left = block->offset.x;
            ch->mArea.right = ch->mArea.left + fontWidth - 1;
            ch->mArea.top = block->offset.y;
            ch->mArea.bottom = ch->mArea.top + fontHeight - 1;

            // ��ȡ�����棬д����
            FacePtr face = smart_pointer_cast<Face>(block->face);
            TexturePtr texture = face->material->getTexture(0);

            // ������Ҫ��ȡ�����������޸ģ���������ӣ�������Ҫ�޸������д���ݽṹ
            T3D_ASSERT(0);
            uint8_t *dstData = nullptr;
            int32_t dstPitch = 0;
            int32_t dstWidth = 0;
            int32_t dstHeight = 0;
            
            uint8_t *dstLine = dstData + dstTop * dstPitch + 4 * dstLeft;
            uint8_t *srcLine = srcData + (srcHeight - 1);

            // ����UV������X����Ϊ����Y����Ϊ������freetype�����bitmap������X����Ϊ����Y����λ��
            for (size_t y = 0; y < srcHeight; y++)
            {
                uint32_t *dst = (uint32_t *)dstLine;
                uint8_t *src = srcLine;
                for (size_t x = 0; x < srcWidth; x++)
                {
                    // ��Ϊ�����ǻҶ�ͼ�����������alphaͨ���ﱸ�ݣ��������ֱ���޸��ı���ɫ�������ٽ����ֿ�
                    Color4 color(*src, *src, *src, *src);
                    *dst = color.A8R8G8B8();
                    dst++;
                    src++;
                }

                dstLine += dstPitch;
                srcLine -= srcPitch;
            }
        } while (0);

        return ret;
    }

    bool FreeTypeAtlas::extendTexture(const String &name, TexturePtr srcTexture, TexturePtr &newTexture)
    {
        bool ret = false;

        do 
        {
            const FontConfig &config = FontManager::getInstance().getConfig();

            int32_t texWidth = srcTexture->getTexWidth();
            int32_t texHeight = srcTexture->getTexHeight();

            size_t incTexWidth = (config.incTexWidth == 0 ? texWidth : config.incTexWidth);
            size_t incTexHeight = (config.incTexHeight == 0 ? texHeight : config.incTexHeight);

            int32_t newTexWidth = 0;
            int32_t newTexHeight = 0;

            if (texWidth + incTexWidth < config.maxTexWidth)
            {
                newTexWidth = texWidth + incTexWidth;
            }
            else
            {
                newTexWidth = config.maxTexWidth;
            }

            if (texHeight + incTexHeight < config.maxTexHeight)
            {
                newTexHeight = texHeight + incTexHeight;
            }
            else
            {
                newTexHeight = config.maxTexHeight;
            }

            // �´���һ������
            if (!createTexture(name, newTexWidth, newTexHeight, newTexture))
            {
                break;
            }

            // �Ѿ�������������ݸ��Ƶ���������ͬ����
            Rect srcRect(Point(0, 0), Size(texWidth, texHeight));
            Rect dstRect = srcRect;
            if (!srcTexture->copyToTexture(newTexture, &srcRect, &dstRect))
            {
                T3D_LOG_ERROR("Copy source texture data to new texture failed !");
                break;
            }

            ret = true;
        } while (0);

        return ret;
    }
}
