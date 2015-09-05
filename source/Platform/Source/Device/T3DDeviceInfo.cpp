

#include "T3DDeviceInfo.h"
#include "T3DDeviceInfoInterface.h"
#include "T3DFactoryInterface.h"


T3D_INIT_SINGLETON(Tiny3D::DeviceInfo);


namespace Tiny3D
{
	const uint32_t DeviceInfo::PLATFORM_UNKNOWN = E_PLATFORM_UNKNOWN;
	const uint32_t DeviceInfo::PLATFORM_WINDOWS = E_PLATFORM_WIN32;
	const uint32_t DeviceInfo::PLATFORM_MACOSX = E_PLATFORM_MACOSX;
	const uint32_t DeviceInfo::PLATFORM_LINUX = E_PLATFORM_LINUX;
	const uint32_t DeviceInfo::PLATFORM_IOS = E_PLATFORM_IOS;
	const uint32_t DeviceInfo::PLATFORM_ANDROID = E_PLATFORM_ANDROID;

	const char* DeviceInfo::Unknown = "Unknown";
	const char* DeviceInfo::Windows = "Windows";
	const char* DeviceInfo::MacOSX = "Mac OSX";
	const char* DeviceInfo::Linux = "Linux";
	const char* DeviceInfo::iOS = "iOS";
	const char* DeviceInfo::Android = "Android";

	DeviceInfo::DeviceInfo(FactoryInterface *pAdapterFactory)
		: m_pDevInfoAdapter(nullptr)
	{
		if (pAdapterFactory != nullptr)
		{
			m_pDevInfoAdapter = pAdapterFactory->createDeviceInfoAdapter();
		}
	}

	DeviceInfo::~DeviceInfo()
	{
		T3D_SAFE_DELETE(m_pDevInfoAdapter);
	}

	uint32_t DeviceInfo::getPlatform() const
	{
		uint32_t unPlatform = PLATFORM_UNKNOWN;

		if (m_pDevInfoAdapter != nullptr)
		{
			unPlatform = m_pDevInfoAdapter->getPlatform();
		}

		return unPlatform;
	}

	TString DeviceInfo::getPlatformString() const
	{
		TString strPlatform = Unknown;

		if (m_pDevInfoAdapter != nullptr)
		{
			switch (m_pDevInfoAdapter->getPlatform())
			{
			case PLATFORM_WINDOWS:
				{
					strPlatform = Windows;
				}
				break;
			case PLATFORM_MACOSX:
				{
					strPlatform = MacOSX;
				}
				break;
			case PLATFORM_LINUX:
				{
					strPlatform = Linux;
				}
				break;
			case PLATFORM_IOS:
				{
					strPlatform = iOS;
				}
				break;
			case PLATFORM_ANDROID:
				{
					strPlatform = Android;
				}
				break;
			}
		}

		return strPlatform;
	}

	TString DeviceInfo::getSoftwareVersion() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getSoftwareVersion();
		}
		return "";
	}

	TString DeviceInfo::getOSVersion() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getOSVersion();
		}
		return "";
	}

	TString DeviceInfo::getDeviceVersion() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getDeviceVersion();
		}
		return "";
	}

	int32_t DeviceInfo::getScreenWidth() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getScreenWidth();
		}
		return 0;
	}

	int32_t DeviceInfo::getScreenHeight() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getScreenHeight();
		}
		return 0;
	}

	float DeviceInfo::getScreenDPI() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getScreenDPI();
		}
		return 0.0f;
	}

	TString DeviceInfo::getMacAddress() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getMacAddress();
		}
		return "";
	}

	TString DeviceInfo::getCPUType() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getCPUType();
		}
		return "";
	}

	int32_t DeviceInfo::getNumberOfProcessors() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getNumberOfProcessors();
		}
		return 1;
	}

	uint32_t DeviceInfo::getMemoryCapacity() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getMemoryCapacity();
		}
		return 0;
	}

	TString DeviceInfo::getDeviceID() const
	{
		if (m_pDevInfoAdapter != nullptr)
		{
			return m_pDevInfoAdapter->getDeviceID();
		}
		return "";
	}
}