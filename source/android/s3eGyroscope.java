/*
java implementation of the s3eGyroscope extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
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
 
 
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

import android.util.Log;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorManager;
import android.hardware.SensorEventListener;

class s3eGyroscope implements SensorEventListener
{   
        
    private final int DELAY_FASTEST = 0;
    private final int DELAY_GAME = 1;
    private final int DELAY_UI = 2;
    private final int DELAY_NORMAL = 3;
    
    private final int S3E_GYROSCOPE_RESULT_OK = 0;
    private final int S3E_GYROSCOPE_NOT_AVAILABLE=1;
    private final int S3E_GYROSCOPE_ALREADY_INITIALISED=2;
    private final int S3E_GYROSCOPE_NOT_RUNNING=3;
    private final int S3E_GYROSCOPE_UNKNOWN_ERROR=4;
    
    private native void onGyroNative(float x, float y, float z);
    
    public void onAccuracyChanged(Sensor sensor, int accuracy)
    {   
            int type = sensor.getType();
            if (type == Sensor.TYPE_GYROSCOPE)
            {
               Log.d(TAG, "onAccuracyChanged new accuracy: "+accuracy);
            }
    }
    
    
    
    public void onSensorChanged(SensorEvent ev)
    {
        int type = ev.sensor.getType();
        if (type == Sensor.TYPE_GYROSCOPE)
        {
            //Log.d(TAG, "onSensorChanged TYPE_GYROSCOPE");
            
            onGyroNative(ev.values[0], ev.values[1], ev.values[2]);
        }
    }
    
    
    
    public int s3eGyroscopeStart()
    {   
        Log.d(TAG, "gyroscopeStart");
        
        if (m_Gyroscope == null)
        {
            Context myContext = (Context) LoaderActivity.m_Activity;
            m_SensorManager = (SensorManager) myContext.getSystemService(Context.SENSOR_SERVICE);
            m_Gyroscope = m_SensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
            
            if (m_Gyroscope == null)
            {
                return S3E_GYROSCOPE_NOT_AVAILABLE;
            }
            
            m_SensorManager.registerListener(this, m_Gyroscope, SensorManager.SENSOR_DELAY_GAME);
        }
        else if (m_Gyroscope != null)
        {
            return S3E_GYROSCOPE_ALREADY_INITIALISED;
        }
        
        return S3E_GYROSCOPE_RESULT_OK;
    }
    
    
    
    public int s3eGyroscopeSetSensorDelay(int delay)
    {   
        Log.d(TAG, "sensorDelayValue: " + delay);
        
        if (m_Gyroscope == null)
        {
            return S3E_GYROSCOPE_NOT_RUNNING;
        }
        
        m_SensorManager.unregisterListener(this);
       
       
        switch(delay)
        {
            case DELAY_FASTEST: m_SensorManager.registerListener(this, m_Gyroscope, SensorManager.SENSOR_DELAY_FASTEST);
            break;
            
            case DELAY_GAME: m_SensorManager.registerListener(this, m_Gyroscope, SensorManager.SENSOR_DELAY_GAME);
            break;
            
            case DELAY_UI: m_SensorManager.registerListener(this, m_Gyroscope, SensorManager.SENSOR_DELAY_UI);
            break;
            
            case DELAY_NORMAL: m_SensorManager.registerListener(this, m_Gyroscope, SensorManager.SENSOR_DELAY_NORMAL);
            break;
            
            default: m_SensorManager.registerListener(this, m_Gyroscope, SensorManager.SENSOR_DELAY_NORMAL);
            break;
        }    
        
        return S3E_GYROSCOPE_RESULT_OK;
    }
    
    
    
    public int s3eGyroscopeStop()
    {
        Log.d(TAG, "gyroscopeStop");
        if (m_Gyroscope != null)
        {
            m_SensorManager.unregisterListener(this, m_Gyroscope);
            m_Gyroscope = null;
        }
        else if (m_Gyroscope == null) return S3E_GYROSCOPE_NOT_RUNNING;
            
        return S3E_GYROSCOPE_RESULT_OK;
    
    }
    
    
    
    private SensorManager m_SensorManager;
    private Sensor m_Gyroscope;
    private static final String TAG = "MyGyroscope";
    
}
