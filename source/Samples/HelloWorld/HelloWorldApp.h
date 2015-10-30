

#ifndef __HELLO_WOLRD_APP_H__
#define __HELLO_WOLRD_APP_H__


#include <Tiny3D.h>


class HelloWorldApp 
    : public Tiny3D::ApplicationListener
//     , public Tiny3D::FrameListener
{
public:
    HelloWorldApp();
    virtual ~HelloWorldApp();

protected:  /// from Tiny3D::ApplicationListener
    virtual bool applicationDidFinishLaunching();

    virtual void applicationDidEnterBackground();

    virtual void applicationWillEnterForeground();

// protected:  /// from Tiny3D::FrameListener
//     virtual bool onFrameStarted(const FrameEvent &evt);
//     virtual bool onFrameEnded(const FrameEvent &evt);
};


#endif  /*__HELLO_WOLRD_APP_H__*/
