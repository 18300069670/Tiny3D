

#ifndef __T3D_PREREQUISITES_H__
#define __T3D_PREREQUISITES_H__


#include "T3DConfig.h"
#include "T3DMacro.h"
#include <stdarg.h>


#if defined T3DCORE_EXPORT
    #define T3D_ENGINE_API        T3D_EXPORT_API
#else
    #define T3D_ENGINE_API        T3D_IMPORT_API
#endif


#include "T3DPlatform.h"
#include "T3DLog.h"

#include "T3DSphere.h"
#include "T3DAabb.h"
#include "T3DObb.h"
#include "T3DFrustum.h"


#include "T3DRect.h"
#include "T3DMath.h"
#include "T3DMatrix2.h"
#include "T3DMatrix3.h"
#include "T3DMatrix4.h"
#include "T3DQuaternion.h"
#include "T3DVector2.h"
#include "T3DVector3.h"
#include "T3DVector4.h"
#include "T3DPlane.h"



namespace Tiny3D
{
    /// Platform
    class TextCodec;
    class Console;
    class DeviceInfo;
    class DataStream;
    class Dir;
    class FileDataStream;
    class MemoryDataStream;
    class DateTime;
    class RunLoop;
    class RunLoopObserver;
    class Timer;
    class TimerObserver;
    class System;

    /// Log
    class Logger;

    /// Core
    class ApplicationListener;
    class RenderTargetListener;
    class FrameListener;
    class TouchEventListener;
    class KeyboardEventListener;
    class JoystickEventListener;

    class Degree;
    class Radian;
    class Math;
    class Matrix2;
    class Matrix3;
    class Matrix4;
    class Quaternion;
    class Vector2;
    class Vector3;
    class Vector4;

    class Transform;
    
    class Entrance;
    class Plugin;

    class Color4;

    class Plane;
    class Sphere;
    class Frustum;
    class Obb;
    class Aabb;

    class Bound;
    class SphereBound;
    class AabbBound;
    class ObbBound;
    class FrustumBound;

    class Viewport;
    class RenderTarget;
    class RenderWindow;
    class Renderer;

    class HardwareBuffer;
    class HardwareVertexBuffer;
    class HardwareIndexBuffer;

    class VertexElement;
    class VertexDeclaration;

    class HardwareBufferManagerBase;
    class HardwareBufferManager;

    class Resource;
    class ResourceManager;
    class Dylib;
    class DylibManager;
    class Material;
    class MaterialManager;
    class Texture;
    class TextureManager;
    class Archive;
    class ArchiveManager;
    class ArchiveCreator;
    class Model;
    class ModelManager;

    class FileSystemArchive;
    class FileSystemArchiveCreator;
    class ZipArchive;
    class ZipArchiveCreator;

    class Object;
    class Node;

    class SceneManager;
    class SGNode;
    class SGTransformNode;
    class SGVisual;
    class SGCamera;
    class SGShape;
    class SGModel;
    class SGIndicator;
    class SGRenderable;
    class SGLight;
    class SGGeometry;
    class SGMesh;
    class SGSkeleton;
    class SGSphere;
    class SGBox;
    class SGAxis;

    class VertexData;
    class IndexData;

    class RenderGroup;
    class RenderQueue;

    class Variant;

    class Image;

    class InputSystem;
    class TouchDevice;
    class KeyDevice;
    class JoystickDevice;
}


#endif    /*__T3D_PREREQUISITES_H__*/
