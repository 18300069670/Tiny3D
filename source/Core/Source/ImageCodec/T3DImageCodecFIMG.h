

#ifndef __T3D_IMAGE_CODEC_FIMG_H__
#define __T3D_IMAGE_CODEC_FIMG_H__


#include "ImageCodec/T3DImageCodecBase.h"


namespace Tiny3D
{
    class ImageCodecFIMG;

    T3D_DECLARE_SMART_PTR(ImageCodecFIMG);

    class ImageCodecFIMG : public ImageCodecBase
    {
    public:
        typedef std::vector<ImageCodecBase::FileType>   FileTypeList;
        typedef FileTypeList::iterator                  FileTypeListItr;
        typedef FileTypeList::const_iterator            FileTypeListConstItr;

        static ImageCodecFIMGPtr create();

        virtual ~ImageCodecFIMG();

        const FileTypeList &getSupportedFileTypeList() const { return mFileTypeList; }

        virtual bool startup() override;
        virtual bool shutdown() override;

        virtual bool isSupportedType(uint8_t *data, size_t size, FileType &eFileType) const override;
        virtual FileType getFileType() const override;

        virtual bool encode(uint8_t *&data, size_t &size, const Image &image) override;

        virtual bool decode(uint8_t *data, size_t size, Image &image, FileType eFileType) override;

    protected:
        ImageCodecFIMG();

        FileTypeList        mFileTypeList;

        static const size_t MAX_SUPPORTED_FILE_TYPE;
    };
}


#endif  /*__T3D_IMAGE_CODEC_FIMG_H__*/