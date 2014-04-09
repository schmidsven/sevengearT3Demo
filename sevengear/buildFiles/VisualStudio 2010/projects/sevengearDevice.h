#ifndef _SEVENGEARDEVICE_H_
#define _SEVENGEARDEVICE_H_

#include "platform/input/IInputDevice.h"
#include "platform/input/event.h"
#include "core/util/tSingleton.h"
#include "math/mQuat.h"
#include "math/mPoint4.h"
#include "vrpn_Analog.h"

class SevengearDevice : public IInputDevice
{
public:
	static bool smEnableDevice;
	static U32 DEVICECODE;
protected:
	static vrpn_Analog_Remote *vrpnAnalog;

public:
	static int staticInit();
	bool process();
public:
	static const char* getSingletonName() { return "SevengearDevice"; }
};

/// Returns the SevengearDevice singleton.
#define SEVENGEARDEV ManagedSingleton<SevengearDevice>::instance()

#endif   // _SEVENGEARDEVICE_H_
