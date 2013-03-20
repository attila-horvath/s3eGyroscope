/*
 * iphone-specific implementation of the s3eGyroscope extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
 
/*
 * Copyright (C) 2013 Attila Horvath
 *
 * This programme is free software; you may redistribute and/or modify
 * it under the terms of the Apache Software Licence v2.0
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
