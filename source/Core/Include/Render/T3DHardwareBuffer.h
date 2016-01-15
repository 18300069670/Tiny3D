

#ifndef __T3D_HARDWARE_BUFFER_H__
#define __T3D_HARDWARE_BUFFER_H__


#include "Misc/T3DObject.h"
#include "T3DTypedef.h"


namespace Tiny3D
{
    class T3D_ENGINE_API HardwareBuffer : public Object
    {
    public:
        enum Usage
        {
            /// ��̬���棬���ݷ������Դ��У����ھ�̬�����д�����Ǻ����ġ�
            /// һ�����ڴ�����Ͳ����µ�����
            E_HBU_STATIC = (1 << 0),
            /// ��̬���棬���ݴ����AGP�ڴ��У����������ܺܿ�ĸ���
            E_HBU_DYNAMIC = (1 << 1),
            /// ��Ӧ�ó���ֻ��д���档��������������������ʺϵ��ڴ��ַ��Ϊд���档
            /// ע������Ӵ����õ����ֻ����ж����ݣ����᷵�ش�����Ϣ��
            E_HBU_WRITE_ONLY = (1 << 2),
            /// ����E_HBU_STATIC��E_HBU_WRITE_ONLY
            E_HBU_STATIC_WRITE_ONLY = (E_HBU_STATIC | E_HBU_WRITE_ONLY),
            /// ����E_HBU_DYNAMIC��E_HBU_WRITE_ONLY
            E_HBU_DYNAMIC_WRITE_ONLY = (E_HBU_DYNAMIC | E_HBU_WRITE_ONLY),
        };

        enum LockOptions
        {
            E_HBL_NORMAL = 0,
            E_HBL_DISCARD,
            E_HBL_NO_OVERWRITE,
            E_HBL_READ_ONLY,
            E_HBL_WRITE_ONLY,
        };

        virtual ~HardwareBuffer();

        void *lock(size_t offset, size_t size, LockOptions options);
        void *lock(LockOptions options);
        void unlock();

        virtual bool readData(size_t offset, size_t size, void *dst) = 0;
        virtual bool writeData(size_t offset, size_t size, const void *src, bool discardWholeBuffer = false) = 0;
        
        bool copyData(const HardwareBufferPtr &srcBuffer, size_t srcOffset, size_t dstOffset, size_t size, bool discardWholeBuffer = false);
        bool copyData(const HardwareBufferPtr &srcBuffer);

        size_t getBufferSize() const    { return mBufferSize; }
        Usage getUsage() const          { return mUsage; }
        bool isSystemMemory() const     { return mSystemMemory; }
        bool hasShadowBuffer() const    { return mUseShadowBuffer; }
        bool isLocked() const           { return (mUseShadowBuffer ? mShadowBuffer->isLocked() : mIsLocked); }

    protected:
        HardwareBuffer(Usage usage, bool systemMemory, bool useShadowBuffer);

        virtual void *lockImpl(size_t offset, size_t size, LockOptions options) = 0;
        virtual void unlockImpl() = 0;

        virtual void updateFromShadow();

        size_t  mBufferSize;                /// Ӳ�������С
        size_t  mLockSize;                  /// �������С
        size_t  mLockOffset;                /// ��������ʼƫ��

        Usage   mUsage;                     /// ��������

        HardwareBufferPtr   mShadowBuffer;  /// Ӱ�ӻ��棬��߶�дЧ��

        bool    mSystemMemory;              /// �Ƿ�ʹ��ϵͳ�ڴ�
        bool    mUseShadowBuffer;           /// �Ƿ�ʹ��Ӱ�ӻ���
        bool    mIsLocked;                  /// Ӳ�������Ƿ���
        bool    mIsShadowBufferDirty;       /// Ӱ�ӻ����Ƿ���Ҫ����
    };
}


#endif  /*__T3D_HARDWARE_BUFFER_H__*/
