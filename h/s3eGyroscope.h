/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
#ifndef S3E_EXT_GYROSCOPE_H
#define S3E_EXT_GYROSCOPE_H

#include <s3eTypes.h>

/*
 * Enum to represent the sensor delay. Values are represented in updates per second.
 *
 */


typedef enum s3eGyroscopeSensorDelay
{
	DELAY_FASTEST = 0,	///get sensor data as fast as possible
	
	DELAY_GAME = 1,		///sensor rate suitable for games 50 Hz
	
	DELAY_UI = 2, 		///rate suitable for the user interface 16Hz
	
	DELAY_NORMAL = 3,	///rate (default) suitable for screen orientation changes 6 Hz

}s3eGyroscopeSensorDelay;

typedef enum s3eGyroscopeResult
{
	S3E_GYROSCOPE_RESULT_OK=0,
	
	S3E_GYROSCOPE_NOT_AVAILABLE=1,
	
	S3E_GYROSCOPE_ALREADY_INITIALISED=2,
	 
	S3E_GYROSCOPE_NOT_RUNNING=3,

	S3E_GYROSCOPE_UNKNOWN_ERROR=4	
	

}s3eGyroscopeResult;


/*
 *	Rotation values in Radians around the x, y, z axes. Rotation is positive in the counter-clockwise direction.
 *
 */
typedef struct s3eGyroscopeData
{
    float m_X; 
  
    float m_Y;
   
	float m_Z;

} s3eGyroscopeData;



/*
 * Calback definition for data updates.
 */

typedef enum s3eGyroscopeCallback
{
    S3E_GYROSCOPE_CALLBACK_DATA_UPDATE =  0,
    
	S3E_GYROSCOPE_CALLBACK_MAX	
	
} s3eGyroscopeCallback;
// \cond HIDDEN_DEFINES
S3E_BEGIN_C_DECL
// \endcond

/**
 * Returns S3E_TRUE if the Gyroscope extension is available.
 */
s3eBool s3eGyroscopeAvailable();

/**
 * Registers a callback to be called for an operating system event.
 *
 * The available callback types are listed in @ref s3eGyroscopeCallback.
 * @param cbid ID of the event for which to register.
 * @param fn callback function.
 * @param userdata Value to pass to the @e userdata parameter of @e NotifyFunc.
 * @return
 *  - @ref S3E_RESULT_SUCCESS if no error occurred.
 *  - @ref S3E_RESULT_ERROR if the operation failed.\n
 *
 * @see s3eGyroscopeUnRegister
 * @note For more information on the system data passed as a parameter to the callback
 * registered using this function, see the @ref s3eGyroscopeCallback enum.
 */
s3eResult s3eGyroscopeRegister(s3eGyroscopeCallback cbid, s3eCallback fn, void* userData);

/**
 * Unregister a callback for a given event.
 * @param cbid ID of the callback for which to register.
 * @param fn Callback Function.
 * @return
 * - @ref S3E_RESULT_SUCCESS if no error occurred.
 * - @ref S3E_RESULT_ERROR if the operation failed.\n
 * @note For more information on the systemData passed as a parameter to the callback
 * registered using this function, see the s3eGyroscopeCallback enum.
 * @note It is not necessary to define a return value for any registered callback.
 * @see s3eGyroscopeRegister
 */
s3eResult s3eGyroscopeUnRegister(s3eGyroscopeCallback cbid, s3eCallback fn);

/*
 * The s3eGyroscopeStart function start the gyroscope sensor and sets the update frequency to its default value.
 *
 */
s3eGyroscopeResult s3eGyroscopeStart();

s3eGyroscopeResult s3eGyroscopeSetSensorDelay( s3eGyroscopeSensorDelay delay );

s3eGyroscopeResult s3eGyroscopeStop();

S3E_END_C_DECL

/** @} */

#endif /* !S3E_EXT_GYROSCOPE_H */