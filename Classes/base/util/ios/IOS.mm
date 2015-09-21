#include "IOS.h"
#import <AudioToolbox/AudioServices.h>

void IOS::vibrate()
{
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}