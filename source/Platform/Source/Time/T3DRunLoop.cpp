/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2017  Aaron Wong
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

#include "Time/T3DRunLoop.h"
#include "Time/T3DDateTime.h"
#include "Time/T3DRunLoopObserver.h"


namespace Tiny3D
{
    uint32_t RunLoop::m_unLoopID = 0;

    RunLoop::RunLoop()
    {

    }

    RunLoop::~RunLoop()
    {

    }

    uint32_t RunLoop::start(uint32_t unInterval, bool bRepeat, RunLoopObserver *pObserver)
    {
        if (pObserver == nullptr)
            return T3D_INVALID_LOOP_ID;

        uint32_t unLoopID = m_unLoopID + 1;
        uint64_t unTimestamp = DateTime::currentMSecsSinceEpoch();
        RunLoopInfo info = {unTimestamp, unInterval, pObserver, bRepeat, true};
        std::pair<RunLoopInfosItr, bool> r = m_infos.insert(RunLoopValue(unLoopID, info));

        if (r.second)
        {
            m_unLoopID++;
        }

        return unLoopID;
    }

    uint32_t RunLoop::start(RunLoopObserver *pObserver)
    {
        if (pObserver == nullptr)
            return T3D_INVALID_LOOP_ID;

        uint32_t unLoopID = m_unLoopID + 1;
        uint64_t unTimestamp = DateTime::currentMSecsSinceEpoch();
        RunLoopInfo info = {unTimestamp, 0, pObserver, true, true};
        std::pair<RunLoopInfosItr, bool> r = m_infos.insert(RunLoopValue(unLoopID, info));

        if (r.second)
        {
            m_unLoopID++;
        }

        return unLoopID;
    }

    bool RunLoop::stop(uint32_t unLoopID)
    {
        bool bRet = false;

        RunLoopInfosItr itr = m_infos.find(unLoopID);

        if (itr != m_infos.end())
        {
            itr->second.bAlive = false;
        }

        return bRet;
    }

    void RunLoop::execute()
    {
        RunLoopInfosItr itr = m_infos.begin();
        uint64_t ullTimestamp = DateTime::currentMSecsSinceEpoch();

        while (itr != m_infos.end())
        {
            uint32_t unLoopID = itr->first;
            RunLoopInfo &info = itr->second;

            if (info.bAlive)
            {
                int64_t dt = (int64_t)ullTimestamp - (int64_t)info.ullLastTimestamp;

                if (dt >= (int64_t)info.ullInterval)
                {
                    info.ullLastTimestamp = ullTimestamp;

                    if (!info.bRepeat)
                    {
                        /// ��ѭ������ô��ɾ����
                        info.bAlive = false;
                    }

                    /// �ص�
                    info.pObserver->onExecute(unLoopID, dt);
                }
            }

            ++itr;
        }

        // ɾ�������Ѿ�ͣ����
        itr = m_infos.begin();

        while (itr != m_infos.end())
        {
            RunLoopInfo &info = itr->second;
            RunLoopInfosItr itrCur = itr++;

            if (!info.bAlive)
            {
                m_infos.erase(itrCur);
            }
        }
    }
}
