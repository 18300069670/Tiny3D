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

#include "IO/T3DDir.h"
#include "Adapter/T3DFactoryInterface.h"
#include "Adapter/T3DDirInterface.h"
#include "T3DSystem.h"
#include "T3DType.h"


namespace Tiny3D
{
    DirInterface *Dir::s_pDirAdapter = nullptr;

    char Dir::NATIVE_SEPARATOR = 0;

    Dir::Dir()
    {
        m_pDirAdpater = T3D_ADAPTER_FACTORY.createDirAdapter();
    }

    Dir::~Dir()
    {
        T3D_SAFE_DELETE(m_pDirAdpater);
    }

    bool Dir::findFile(const String &strPath)
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->findFile(strPath);
        }

        return false;
    }

    bool Dir::findNextFile()
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->findNextFile();
        }

        return false;
    }

    void Dir::close()
    {
        if (m_pDirAdpater != nullptr)
        {
            m_pDirAdpater->close();
        }
    }

    String Dir::getRoot() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->getRoot();
        }

        return "";
    }

    String Dir::getFileName() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->getFileName();
        }

        return "";
    }

    String Dir::getFilePath() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->getFilePath();
        }

        return "";
    }

    String Dir::getFileTitle() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->getFileTitle();
        }

        return "";
    }

    uint32_t Dir::getFileSize() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->getLength();
        }

        return 0;
    }

    bool Dir::isDots() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->isDots();
        }

        return false;
    }

    bool Dir::isDirectory() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->isDirectory();
        }

        return false;
    }

    long_t Dir::getCreationTime() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->getCreationTime();
        }

        return 0;
    }

    long_t Dir::getLastAccessTime() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->getLastAccessTime();
        }

        return 0;
    }

    long_t Dir::getLastWriteTime() const
    {
        if (m_pDirAdpater != nullptr)
        {
            return m_pDirAdpater->getLastWriteTime();
        }

        return 0;
    }

    bool Dir::makeDir(const String &strDir)
    {
        if (nullptr == s_pDirAdapter)
            s_pDirAdapter = T3D_ADAPTER_FACTORY.createDirAdapter();

        if (s_pDirAdapter != nullptr)
        {
            return s_pDirAdapter->makeDir(strDir);
        }

        return false;
    }

    bool Dir::removeDir(const String &strDir)
    {
        if (nullptr == s_pDirAdapter)
            s_pDirAdapter = T3D_ADAPTER_FACTORY.createDirAdapter();

        if (s_pDirAdapter != nullptr)
        {
            return s_pDirAdapter->removeDir(strDir);
        }

        return false;
    }

    bool Dir::remove(const String &strFileName)
    {
        if (nullptr == s_pDirAdapter)
            s_pDirAdapter = T3D_ADAPTER_FACTORY.createDirAdapter();

        if (s_pDirAdapter != nullptr)
        {
            return s_pDirAdapter->remove(strFileName);
        }

        return false;
    }

    bool Dir::exists(const String &strPath)
    {
        if (nullptr == s_pDirAdapter)
            s_pDirAdapter = T3D_ADAPTER_FACTORY.createDirAdapter();

        if (s_pDirAdapter != nullptr)
        {
            return s_pDirAdapter->exists(strPath);
        }

        return false;
    }

    String Dir::getCachePath()
    {
        if (nullptr == s_pDirAdapter)
            s_pDirAdapter = T3D_ADAPTER_FACTORY.createDirAdapter();

        if (s_pDirAdapter != nullptr)
        {
            return s_pDirAdapter->getCachePath();
        }

        return "";
    }

    String Dir::getAppPath()
    {
        if (nullptr == s_pDirAdapter)
            s_pDirAdapter = T3D_ADAPTER_FACTORY.createDirAdapter();

        if (s_pDirAdapter != nullptr)
        {
            return s_pDirAdapter->getAppPath();
        }

        return "";
    }

    char Dir::getNativeSeparator()
    {
        if (NATIVE_SEPARATOR == 0)
        {
            if (nullptr == s_pDirAdapter)
                s_pDirAdapter = T3D_ADAPTER_FACTORY.createDirAdapter();

            if (s_pDirAdapter != nullptr)
            {
                NATIVE_SEPARATOR = s_pDirAdapter->getNativeSeparator();
            }
        }

        return NATIVE_SEPARATOR;
    }
}
