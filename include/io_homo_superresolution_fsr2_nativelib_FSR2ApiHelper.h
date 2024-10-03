#ifdef ON_LINUX
    #include "jni_linux64.h"
#else
    #include "jni.h"
#endif
/* Header for class io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper */

#ifndef _Included_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper
#define _Included_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper
 * Method:    ffxFsr2GetScratchMemorySizeGL
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxFsr2GetScratchMemorySizeGL
  (JNIEnv *, jobject);

/*
 * Class:     io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper
 * Method:    ffxFsr2CreateGL
 * Signature: (IFIII)[I
 */
JNIEXPORT jintArray JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxFsr2CreateGL
  (JNIEnv *, jobject, jint, jfloat, jint, jint, jint);

/*
 * Class:     io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper
 * Method:    ffxFsr2Test
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxFsr2Test
  (JNIEnv *, jobject);

/*
 * Class:     io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper
 * Method:    getVersionInfo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_getVersionInfo
  (JNIEnv *, jobject);

/*
 * Class:     io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper
 * Method:    ffxFsr2ContextDispatch
 * Signature: (Lio/homo/superresolution/fsr2/types/FfxResource;Lio/homo/superresolution/fsr2/types/FfxResource;Lio/homo/superresolution/fsr2/types/FfxResource;Lio/homo/superresolution/fsr2/types/FfxResource;Lio/homo/superresolution/fsr2/types/FfxResource;Lio/homo/superresolution/fsr2/types/FfxResource;FFFFIIZFFFZFFFFZII)I
 */
JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxFsr2ContextDispatch
  (JNIEnv *, jobject, jobject, jobject, jobject, jobject, jobject, jobject, jfloat, jfloat, jfloat, jfloat, jint, jint, jboolean, jfloat, jfloat, jfloat, jboolean, jfloat, jfloat, jfloat, jfloat, jboolean, jint, jint);

/*
 * Class:     io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper
 * Method:    ffxGetTextureResourceGL
 * Signature: (JIII)Lio/homo/superresolution/fsr2/types/FfxResource;
 */
JNIEXPORT jobject JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxGetTextureResourceGL
  (JNIEnv *, jobject, jlong, jint, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
