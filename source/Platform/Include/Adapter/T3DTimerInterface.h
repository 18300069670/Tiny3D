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

#ifndef __T3D_TIMER_INTERFACE_H__
#define __T3D_TIMER_INTERFACE_H__


#include "T3DType.h"
#include "T3DMacro.h"


namespace Tiny3D
{
    class TimerObserver;

    const uint32_t T3D_INVALID_TIMER_ID = 0;        /**< ��Ч��ʱ��ID */

    /**
     * @class ITimerAdapter
     * @brief ����ϵͳƽ̨��صĶ�ʱ���ӿ���.
     * @note ��ز���ϵͳƽ̨��Ҫ�̳иýӿ���ʵ�־���ƽ̨��ع���.
     */
    class TimerInterface
    {
        T3D_DECLARE_INTERFACE(TimerInterface);

    public:
        /**
         * @brief ������ʱ������ʱ����ѭ����ʱ.
         * @param [in] unInterval : ��ʱ��ʱ����������
         * @return ���ض�ʱ����ӦID.
         */
        virtual uint32_t start(uint32_t unInterval) = 0;

        /**
         * @brief �رն�ʱ��.
         * @return void
         */
        virtual void stop() = 0;

        /**
         * @brief ���ö�ʱ���ص��۲��߶���.
         * @param [in] pObserver : �۲��߶���
         * @return void
         * @see class ITimerObserver
         */
        virtual void setObserver(TimerObserver *pObserver) = 0;

        /**
         * @brief ��ȡ��ʱ�������Ӧ�Ķ�ʱ��ID
         * @note ��ǰ��ʱ�����ڼ�ʱ���򷵻غϷ��Ķ�Ӧ�Ķ�ʱ��ID�����򷵻���Ч��ʱ��ID.
         * @return ���ض�ʱ��ID
         */
        virtual uint32_t getTimerID() const = 0;
    };
}



#endif  /*__T3D_TIMER_ADPATER_INTERFACE_H__*/
