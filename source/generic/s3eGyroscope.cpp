/*
Generic implementation of the s3eGyroscope extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eGyroscope_internal.h"
s3eResult s3eGyroscopeInit()
{
    //Add any generic initialisation code here
    return s3eGyroscopeInit_platform();
}

void s3eGyroscopeTerminate()
{
    //Add any generic termination code here
    s3eGyroscopeTerminate_platform();
}

s3eGyroscopeResult s3eGyroscopeStart()
{
	return s3eGyroscopeStart_platform();
}

s3eGyroscopeResult s3eGyroscopeSetSensorDelay(s3eGyroscopeSensorDelay delay)
{
	return s3eGyroscopeSetSensorDelay_platform(delay);
}

s3eGyroscopeResult s3eGyroscopeStop()
{
	return s3eGyroscopeStop_platform();
}
