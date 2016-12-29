

#ifndef __TRANSFORMATION_APP_H__
#define __TRANSFORMATION_APP_H__


#include <Tiny3D.h>


class TransformationApp 
    : public Tiny3D::ApplicationListener
{
public:
    TransformationApp();
    virtual ~TransformationApp();

    int32_t go();

protected:  /// from Tiny3D::ApplicationListener
    virtual bool applicationDidFinishLaunching() override;

    virtual void applicationDidEnterBackground() override;

    virtual void applicationWillEnterForeground() override;

    virtual void applicationWillTerminate() override;

protected:
    Tiny3D::RenderWindowPtr     mRenderWindow;
};


#endif  /*__TRANSFORMATION_APP_H__*/
