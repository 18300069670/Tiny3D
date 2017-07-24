

#ifndef __T3D_ACTION_DATA_H__
#define __T3D_ACTION_DATA_H__


#include "T3DPrerequisitesInternal.h"
#include "T3DTypedefInternal.h"
#include "Misc/T3DObject.h"
#include "T3DVector3.h"
#include "T3DQuaternion.h"


namespace Tiny3D
{
    /**
     * @brief �ؼ�֡����
     */
    class KeyFrameData : public Object
    {
    public:
        /**
         * @brief �ؼ�֡����
         */
        enum Type
        {
            E_TYPE_UNKNOWN = 0,
            E_TYPE_TRANSLATION,     /// ƽ�Ʊ任
            E_TYPE_ROTATION,        /// ��ת�任
            E_TYPE_SCALING,         /// ���ű任
        };

        /**
         * @brief ���عؼ�֡����
         * @note ����ʵ�ַ��ؾ�������
         */
        virtual Type getType() const = 0;

    protected:
        /** ���캯�� */
        KeyFrameData(int64_t timestamp);

    private:
        KeyFrameData(const KeyFrameData &);
        KeyFrameData &operator =(const KeyFrameData &);

    public:
        int64_t     mTimestamp;     /// ��ǰ�ؼ�֡ʱ���
    };

    /**
     * @brief ƽ�ƹؼ�֡����
     */
    class KeyFrameDataT : public KeyFrameData
    {
    public:
        static KeyFrameDataTPtr create(int64_t timestamp, const Vector3 &translation);

        virtual Type getType() const override;

    protected:
        KeyFrameDataT(int64_t timestamp, const Vector3 &translation);

    private:
        KeyFrameDataT(const KeyFrameDataT &);
        KeyFrameDataT &operator =(const KeyFrameDataT &);

    public:
        Vector3     mTranslation;
    };

    /**
     * @brief ��ת�ؼ�֡����
     */
    class KeyFrameDataR : public KeyFrameData
    {
    public:
        static KeyFrameDataRPtr create(int64_t timestamp, const Quaternion &orientation);

        virtual Type getType() const override;

    protected:
        KeyFrameDataR(int64_t timestamp, const Quaternion &orientation);

    private:
        KeyFrameDataR(const KeyFrameDataR &);
        KeyFrameDataR &operator =(const KeyFrameDataR &);

    public:
        Quaternion  mOrientation;
    };

    /**
     * @brief ���Źؼ�֡����
     */
    class KeyFrameDataS : public KeyFrameData
    {
    public:
        static KeyFrameDataSPtr create(int64_t timestamp, const Vector3 &scaling);

        virtual Type getType() const override;

    protected:
        KeyFrameDataS(int64_t timestamp, const Vector3 &scaling);

    private:
        KeyFrameDataS(const KeyFrameDataS &);
        KeyFrameDataS &operator =(const KeyFrameDataS &);

    public:
        Vector3     mScaling;
    };

    /**
     * @brief ��������
     */
    class ActionData : public Object
    {
    public:
        static ActionDataPtr create(const String &name, int32_t duration);

        virtual ~ActionData();

    protected:
        ActionData(const String &name, int32_t duration);

    public:
        typedef std::vector<KeyFrameDataPtr>    KeyFrames;
        typedef KeyFrames::iterator             KeyFramesItr;
        typedef KeyFrames::const_iterator       KeyFramesConstItr;

        typedef std::map<String, KeyFrames>     Bones;
        typedef Bones::iterator                 BonesItr;
        typedef Bones::const_iterator           BonesConstItr;
        typedef std::pair<String, KeyFrames>    BonesValue;

        String      mName;                  /// ��������
        int32_t     mDuration;              /// ����ʱ������λ������
        Bones       mBonesTranslation;      /// ������ع�����ƽ�Ʊ任�ؼ�֡����
        Bones       mBonesRotation;         /// ������ع�������ת�任�ؼ�֡����
        Bones       mBonesScaling;          /// ������ع��������ű任�ؼ�֡����
    };
}


#endif  /*__T3D_ACTION_DATA_H__*/
