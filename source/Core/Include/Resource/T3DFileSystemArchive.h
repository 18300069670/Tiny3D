/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

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
