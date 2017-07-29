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

#ifndef __T3D_TIMER_H__
#define __T3D_TIMER_H__


#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DPlatformPrerequisites.h"


namespace Tiny3D
{
    class TimerObserver;
    class TimerInterface;

    /**
     * @class VTimer
     * @brief ��ʱ����.
     * @note �����ǲ���ϵͳƽ̨�޹ض�ʱ������ƽ̨�����Ľ�һ����װ.
     */
    class T3D_PLATFORM_API Timer
    {
        T3D_DISABLE_COPY(Timer);

    public:
        /**
         * @brief Constructor for VTimer.
         */
        Timer();

        /**
         * @brief Destructor for VTimer.
         */
        ~Timer();

        /**
         * @brief ������ʱ��.
         * @param [in] unInterval : ��ʱ������
         * @return ��ʱ��ID
         */
        uint32_t start(uint32_t unInterval);

        /**
         * @brief �رն�ʱ��.
         * @return void
         */
        void stop();

        /**
         * @brief ���ö�ʱ���۲��߶���.
         * @param [in] pObserver : �۲��߶���
         * @return void
         */
        void setObserver(TimerObserver *pObserver);

        /**
         * @brief ��ȡ��ʱ��ID.
         * @return ���ض�ʱ��ID
         */
        uint32_t getTimerID() const;

    protected:
        TimerInterface *m_pAdapter;
    };
}

#endif  /*__T3D_TIMER_H__*/
