#include "sevengearDevice.h"
#include "platform/platformInput.h"
#include "core/module.h"
#include "console/engineAPI.h"
#include "T3D/gameBase/gameConnection.h"
#include "vrpn_Analog.h"

MODULE_BEGIN(SevengearDevice)

MODULE_INIT_AFTER(InputEventManager)
MODULE_SHUTDOWN_BEFORE(InputEventManager)

MODULE_INIT
{
	SevengearDevice::staticInit();
	ManagedSingleton< SevengearDevice >::createSingleton();


	// Register the device with the Input Event Manager
	INPUTMGR->registerDevice(SEVENGEARDEV);
}

MODULE_SHUTDOWN
{
	INPUTMGR->unregisterDevice(SEVENGEARDEV);
	ManagedSingleton< SevengearDevice >::deleteSingleton();
}

MODULE_END;

//-----------------------------------------------------------------------------
// SevengearDevice
//-----------------------------------------------------------------------------

U32 SevengearDevice::DEVICECODE = 77;// INPUTMGR->getNextDeviceCode();
vrpn_Analog_Remote *SevengearDevice::vrpnAnalog;

void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a)
{
	for (int i = 0; i < a.num_channel; i++)
	{
		float fvalue = a.channel[i];
		INPUTMGR->buildInputEvent(SuitDeviceType, 0, SI_ROT, SevengearDevice::DEVICECODE, SI_MOVE, fvalue);
	}
}

int SevengearDevice::staticInit()
{
	SevengearDevice::vrpnAnalog = new vrpn_Analog_Remote("7GS@localhost");
	SevengearDevice::vrpnAnalog->register_change_handler(0, handle_analog);
	return 0;
}

bool SevengearDevice::process()
{
	SevengearDevice::vrpnAnalog->mainloop();
	return true;
}

