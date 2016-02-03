

#ifndef __T3D_FILE_SYSTEM_ARCHIVE_H__
#define __T3D_FILE_SYSTEM_ARCHIVE_H__


#include "Resource/T3DArchive.h"
#include "Resource/T3DArchiveCreator.h"


namespace Tiny3D
{

    class T3D_ENGINE_API FileSystemArchive : public Archive
    {
    public:
        static const char * const ARCHIVE_TYPE;

        static FileSystemArchivePtr create(const String &name);

        virtual ~FileSystemArchive();

        virtual String getArchiveType() const override;

    protected:
        virtual bool load() override;
        virtual void unload() override;
        virtual ResourcePtr clone() const override;

        virtual String getLocation() const override;
        virtual bool exists(const String &name) const override;
        virtual bool read(const String &name, MemoryDataStream &stream) override;
        virtual bool write(const String &name, const MemoryDataStream &stream) override;

        bool getFileStreamFromCache(const String &name, FileDataStream *&stream);
        void initFileStreamCache();
        void cleanFileStreamCache();

    protected:
        FileSystemArchive(const String &name);

        enum
        {
            MAX_FILE_STREAM_CACHE = 10,     /// �ļ������Ļ���
        };

        typedef std::map<String, FileDataStream*>   FileStreamCache;
        typedef FileStreamCache::iterator           FileStreamCacheItr;
        typedef FileStreamCache::const_iterator     FileStreamCacheConstItr;
        typedef FileStreamCache::value_type         FileStreamCacheValue;

        typedef std::map<uint64_t, String>          FileIndexCache;
        typedef FileIndexCache::iterator            FileIndexCacheItr;
        typedef FileIndexCache::const_iterator      FileIndexCacheConstItr;
        typedef FileIndexCache::value_type          FileIndexCacheValue;

        typedef std::list<FileDataStream*>          FileStreamPool;
        typedef FileStreamPool::iterator            FileStreamPoolItr;
        typedef FileStreamPool::const_iterator      FileStreamPoolConstItr;

        FileStreamPool  mFileStreamPool;        /// �����ļ��������

        FileIndexCache  mFileIndexCache;        /// �ļ����������棬���е�һ���Ǵ���ʱ����Ķ���
        FileStreamCache mFileStreamCache;       /// ʹ���е��ļ�������
    };


    class T3D_ENGINE_API FileSystemArchiveCreator : public ArchiveCreator
    {
    public:
        virtual String getType() const override;
        virtual ArchivePtr createObject(int32_t argc, ...) const override;
    };
}


#endif  /*__T3D_FILE_SYSTEM_ARCHIVE_H__*/
