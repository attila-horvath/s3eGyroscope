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

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"


static jobject g_Obj;
static jmethodID g_s3eGyroscopeStart;
static jmethodID g_s3eGyroscopeSetSensorDelay;
static jmethodID g_s3eGyroscopeStop;

void Gyroscope_onGyroNative(JNIEnv* env, jobject obj, jfloat x, jfloat y, jfloat z)
{
    //IwTrace(GYROSCOPE, ("GYROSCOPE values received x:%f y:%f z:%f", x, y, z));
    s3eGyroscopeData ret;
    ret.m_X = x;
    ret.m_Y = y;
    ret.m_Z = z;
    s3eEdkCallbacksEnqueue(S3E_EXT_GYROSCOPE_HASH, S3E_GYROSCOPE_CALLBACK_DATA_UPDATE, &ret, sizeof(ret));
}
s3eResult s3eGyroscopeInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("s3eGyroscope");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_s3eGyroscopeStart = env->GetMethodID(cls, "s3eGyroscopeStart", "()I");
    if (!g_s3eGyroscopeStart)
        goto fail;

    g_s3eGyroscopeSetSensorDelay = env->GetMethodID(cls, "s3eGyroscopeSetSensorDelay", "(I)I");
    if (!g_s3eGyroscopeSetSensorDelay)
        goto fail;

    g_s3eGyroscopeStop = env->GetMethodID(cls, "s3eGyroscopeStop", "()I");
    if (!g_s3eGyroscopeStop)
        goto fail;

		static const JNINativeMethod g_JNIthreadMethods[] =
    {
        {"onGyroNative",       "(FFF)V",   (void *)&Gyroscope_onGyroNative},
    };
    
    if (env->RegisterNatives(cls, g_JNIthreadMethods, 1))
    {
        IwTrace(DEVICE, ("JNI RegisterNatives failed for %s", g_JNIthreadMethods[0].name));
        return  S3E_RESULT_ERROR;
    }

    IwTrace(GYROSCOPE, ("GYROSCOPE init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    IwTrace(s3eGyroscope, ("FAILED!!!!!!!!!!!!!!!!!!!"));
  
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3eGyroscope, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void s3eGyroscopeTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eGyroscopeResult s3eGyroscopeStart_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eGyroscopeResult)env->CallIntMethod(g_Obj, g_s3eGyroscopeStart);
}

s3eGyroscopeResult s3eGyroscopeSetSensorDelay_platform(s3eGyroscopeSensorDelay delay)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
	return (s3eGyroscopeResult)env->CallIntMethod(g_Obj, g_s3eGyroscopeSetSensorDelay,delay);
}

s3eGyroscopeResult s3eGyroscopeStop_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
	return (s3eGyroscopeResult)env->CallIntMethod(g_Obj, g_s3eGyroscopeStop);
}
