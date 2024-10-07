#ifdef ON_LINUX
    #include "jni_linux64.h"
#else
    #include "jni.h"
#endif
/* Header for class io_homo_superresolution_upscale_NativeApiHelper */

#ifndef _Included_io_homo_superresolution_upscale_NativeApiHelper
#define _Included_io_homo_superresolution_upscale_NativeApiHelper
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_homo_superresolution_upscale_NativeApiHelper
 * Method:    ffxFsr2GetScratchMemorySizeGL
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_io_homo_superresolution_upscale_NativeApiHelper_ffxFsr2GetScratchMemorySizeGL
  (JNIEnv *, jobject);

/*
 * Class:     io_homo_superresolution_upscale_NativeApiHelper
 * Method:    ffxFsr2CreateGL
 * Signature: (IFIII)[I
 */
JNIEXPORT jintArray JNICALL Java_io_homo_superresolution_upscale_NativeApiHelper_ffxFsr2CreateGL
  (JNIEnv *, jobject, jint, jfloat, jint, jint, jint);

/*
 * Class:     io_homo_superresolution_upscale_NativeApiHelper
 * Method:    ffxFsr2Test
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_io_homo_superresolution_upscale_NativeApiHelper_ffxFsr2Test
  (JNIEnv *, jobject);

/*
 * Class:     io_homo_superresolution_upscale_NativeApiHelper
 * Method:    getVersionInfo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_homo_superresolution_upscale_NativeApiHelper_getVersionInfo
  (JNIEnv *, jobject);

/*
 * Class:     io_homo_superresolution_upscale_NativeApiHelper
 * Method:    ffxFsr2ContextDispatch
 * Signature: (Lio/homo/superresolution/upscale/fsr2/types/FfxResource;Lio/homo/superresolution/upscale/fsr2/types/FfxResource;Lio/homo/superresolution/upscale/fsr2/types/FfxResource;Lio/homo/superresolution/upscale/fsr2/types/FfxResource;Lio/homo/superresolution/upscale/fsr2/types/FfxResource;Lio/homo/superresolution/upscale/fsr2/types/FfxResource;FFFFIIZFFFZFFFFZII)I
 */
JNIEXPORT jint JNICALL Java_io_homo_superresolution_upscale_NativeApiHelper_ffxFsr2ContextDispatch
  (JNIEnv *, jobject, jobject, jobject, jobject, jobject, jobject, jobject, jfloat, jfloat, jfloat, jfloat, jint, jint, jboolean, jfloat, jfloat, jfloat, jboolean, jfloat, jfloat, jfloat, jfloat, jboolean, jint, jint);

/*
 * Class:     io_homo_superresolution_upscale_NativeApiHelper
 * Method:    ffxGetTextureResourceGL
 * Signature: (JIII)Lio/homo/superresolution/upscale/fsr2/types/FfxResource;
 */
JNIEXPORT jobject JNICALL Java_io_homo_superresolution_upscale_NativeApiHelper_ffxGetTextureResourceGL
  (JNIEnv *, jobject, jlong, jint, jint, jint);
/*
 * Class:     io_homo_superresolution_upscale_NativeApiHelper
 * Method:    ffxFsr2GetJitterPhaseCount
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_io_homo_superresolution_upscale_NativeApiHelper_ffxFsr2GetJitterPhaseCount
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     io_homo_superresolution_upscale_NativeApiHelper
 * Method:    ffxFsr2GetJitterOffset
 * Signature: (II)[F
 */
JNIEXPORT jfloatArray JNICALL Java_io_homo_superresolution_upscale_NativeApiHelper_ffxFsr2GetJitterOffset
  (JNIEnv *, jobject, jint, jint);
#ifdef __cplusplus
}
#endif
#endif
