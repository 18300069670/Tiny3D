

#ifndef __T3D_LOG_TASK_H__
#define __T3D_LOG_TASK_H__


#include "T3DLogPrerequisites.h"


namespace Tiny3D
{
    class LogTask
    {
    public:
        enum Type
        {
            E_TYPE_NONE = 0,        /// û������
            E_TYPE_CHECK_EXPIRED,   /// ��������־�ļ�
            E_TYPE_FLUSH_CACHE,     /// �ѻ�����־д���ļ�
            E_TYPE_MAX
        };

        T3D_DECLARE_INTERFACE(LogTask);

        virtual Type getType() const = 0;
    };

    class LogTaskCheckExpired : public LogTask
    {
    public:
        LogTaskCheckExpired(uint32_t unExpired);

        virtual Type getType() const override;

        uint32_t getExpired() const
        {
            return mExpired;
        }

    protected:
        uint32_t mExpired;
    };

    class LogTaskFlushCache : public LogTask
    {
    public:
        virtual Type getType() const override;
    };
}


#endif  /*__T3D_LOG_TASK_H__*/
