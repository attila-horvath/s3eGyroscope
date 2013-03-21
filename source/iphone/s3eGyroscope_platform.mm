/*
 * (C) 2012-2013 Attila Horvath.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
 
#include "s3eGyroscope_internal.h"
#import <CoreMotion/CoreMotion.h>
#include "IwDebug.h"
#include "s3eEdk.h"

static CMMotionManager *g_MotionManager = nil;
static NSTimeInterval updateInterval;

s3eResult s3eGyroscopeInit_platform()
{
    
    return S3E_RESULT_SUCCESS;
}

void s3eGyroscopeTerminate_platform()
{
    
}

s3eGyroscopeResult s3eGyroscopeStart_platform()
{	 
	if (g_MotionManager) 
	{
        [g_MotionManager release];
    }
    
	g_MotionManager	= [[CMMotionManager alloc] init];
    
	if([g_MotionManager isGyroAvailable])
    {
		[g_MotionManager setGyroUpdateInterval:1.0f / 6.0f ];
		[g_MotionManager startGyroUpdatesToQueue:[NSOperationQueue mainQueue] withHandler:^(CMGyroData *gyroData,NSError *error)
            {
		s3eGyroscopeData data;		  
                data.m_X = gyroData.rotationRate.x;
				data.m_Y = gyroData.rotationRate.y;
				data.m_Z = gyroData.rotationRate.z;
		s3eEdkCallbacksEnqueue(S3E_EXT_GYROSCOPE_HASH,S3E_GYROSCOPE_CALLBACK_DATA_UPDATE, &data);
		       IwTrace(GYROSCOPE, ("Gyroscope data received"));
            }];

		

       return S3E_GYROSCOPE_RESULT_OK;
	}	
    
    return S3E_GYROSCOPE_NOT_AVAILABLE;
}

s3eGyroscopeResult s3eGyroscopeSetSensorDelay_platform(s3eGyroscopeSensorDelay delay)
{
    
    if (g_MotionManager)
    {
    
	    switch(delay)
	    {
          case DELAY_FASTEST : updateInterval = 1.0f / 85.0f ;
		   break;
	     case DELAY_GAME : updateInterval = 1.0f / 50.0f ;
		   break;
	     case DELAY_UI : updateInterval = 1.0f / 16.0f ;
		   break;
	     case DELAY_NORMAL : updateInterval = 1.0f / 6.0f ;
	        break;
	     default : updateInterval = 1.0f / 6.0f ;
	    }  
	
        [g_MotionManager setGyroUpdateInterval:updateInterval ];
        
        return S3E_GYROSCOPE_RESULT_OK;
    }

    return S3E_GYROSCOPE_NOT_RUNNING;
}

s3eGyroscopeResult s3eGyroscopeStop_platform()
{
    if (g_MotionManager)
    {
        [g_MotionManager release];
        g_MotionManager = nil;
        
        return S3E_GYROSCOPE_RESULT_OK;
    }
    
    return S3E_GYROSCOPE_NOT_RUNNING;
}
