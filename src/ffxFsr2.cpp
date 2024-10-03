#define VES "0.0.2"

#include "io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper.h"
#include "ffx-fsr2-api/ffx_fsr2.h"
#include "ffx-fsr2-api/gl/ffx_fsr2_gl.h"
#include "ffx-fsr2-api/ffx_error.h"
#include <stdlib.h>
#include <memory>
#include "glfw3.h"
#include "utils.h"
bool fsr2FirstInit = true;
FfxFsr2Context fsr2Context;
std::unique_ptr<char[]> fsr2ScratchMemory;

static void up_env(JNIEnv *env)
{
    set_env(env);
}
static void check_env(JNIEnv *env)
{
    set_env(env);
}

JNIEXPORT jintArray JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxFsr2CreateGL(JNIEnv *env, jobject, jint scratchMemorySize, jfloat fsr2Ratio, jint width, jint height, jint flags)
{
    if (!fsr2FirstInit)
    {
        ffxFsr2ContextDestroy(&fsr2Context);
    }
    check_env(env);
    unsigned int renderWidth = static_cast<unsigned int>(width / fsr2Ratio);
    unsigned int renderHeight = static_cast<unsigned int>(height / fsr2Ratio);
    FfxFsr2ContextDescription contextDesc = {};
    contextDesc.flags = static_cast<unsigned int>(flags);
    contextDesc.maxRenderSize = {renderWidth, renderHeight};
    contextDesc.displaySize = {static_cast<unsigned int>(width), static_cast<unsigned int>(height)};
    contextDesc.callbacks = {};
    contextDesc.fpMessage = [](FfxFsr2MsgType type, const wchar_t *message)
    {
        char cstr[256] = {};
#ifdef ON_LINUX
        wcstombs(cstr, message, sizeof(cstr));

#else
        wcstombs_s(nullptr, cstr, sizeof(cstr), message, sizeof(cstr));

#endif
        cstr[255] = '\0';
        java_log(cstr, 0);
    };
    fsr2ScratchMemory = std::make_unique<char[]>(ffxFsr2GetScratchMemorySizeGL());
    FfxErrorCode code1 = ffxFsr2GetInterfaceGL(&contextDesc.callbacks, fsr2ScratchMemory.get(), ffxFsr2GetScratchMemorySizeGL(), java_glfwGetProcAddress);
    FfxErrorCode code2 = ffxFsr2ContextCreate(&fsr2Context, &contextDesc);
    java_log("FSR2_CPP ffxFsr2CreateGL",0);
    jint code_c[] = {code1,code2};
    jintArray outJNIArray = (env)->NewIntArray(2);
    (env)->SetIntArrayRegion(outJNIArray, 0 , 2, code_c);
    return outJNIArray;
}
JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxFsr2GetScratchMemorySizeGL(JNIEnv *env, jobject)
{
    check_env(env);
    return static_cast<int>(ffxFsr2GetScratchMemorySizeGL());
}

JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxFsr2ContextDispatch(
    JNIEnv *env,
    jobject,
    jobject color,
    jobject depth,
    jobject motionVectors,
    jobject exposure,
    jobject reactive,
    jobject output,
    jfloat jitterX,
    jfloat jitterY,
    jfloat motionVectorScaleWidth,
    jfloat motionVectorScaleHeight,
    jint renderSizeWidth,
    jint renderSizeHeight,
    jboolean enableSharpening,
    jfloat sharpness,
    jfloat frameTimeDelta,
    jfloat preExposure,
    jboolean reset,
    jfloat cameraNear,
    jfloat cameraFar,
    jfloat cameraFovY,
    jfloat viewSpaceToMetersFactor,
    jboolean deviceDepthNegativeOneToOne,
    jint width,
    jint height)
{
    check_env(env);
    int renderWidth = renderSizeWidth;
    int renderHeight = renderSizeHeight;
    FfxResource reactive_tex = {};
    // if (reactive != -1) reactive_tex = ffxGetTextureResourceGL(reactive, renderWidth, renderHeight, GL_R8_SNORM);
    FfxResource exposure_tex = {};
    // if (exposure != -1) exposure_tex = ffxGetTextureResourceGL(exposure, 1, 1, GL_R32F);
    FfxResource transparencyAndComposition_tex = {};
    FfxFsr2DispatchDescription dispatchDesc = {};
    dispatchDesc.color = ffxResourceJavaToCpp(env, color);
    dispatchDesc.depth = ffxResourceJavaToCpp(env, depth);
    dispatchDesc.motionVectors = ffxResourceJavaToCpp(env, motionVectors);
    dispatchDesc.exposure = exposure_tex;
    dispatchDesc.reactive = reactive_tex;
    dispatchDesc.transparencyAndComposition = transparencyAndComposition_tex;
    dispatchDesc.output = ffxResourceJavaToCpp(env, output);
    dispatchDesc.jitterOffset = {jitterX, jitterY};
    dispatchDesc.motionVectorScale = {float(static_cast<int>(renderWidth)), float(static_cast<int>(renderHeight))};
    dispatchDesc.renderSize = {static_cast<uint32_t>(renderWidth), static_cast<uint32_t>(renderHeight)};
    dispatchDesc.enableSharpening = ToCppBool(enableSharpening);
    dispatchDesc.sharpness = sharpness;
    dispatchDesc.frameTimeDelta = static_cast<float>(frameTimeDelta); // ms
    dispatchDesc.preExposure = preExposure;
    dispatchDesc.reset = ToCppBool(reset);
    dispatchDesc.cameraNear = cameraNear;
    dispatchDesc.cameraFar = cameraFar;
    dispatchDesc.cameraFovAngleVertical = cameraFovY;
    dispatchDesc.viewSpaceToMetersFactor = viewSpaceToMetersFactor;
    dispatchDesc.deviceDepthNegativeOneToOne = ToCppBool(deviceDepthNegativeOneToOne);

    FfxErrorCode err = ffxFsr2ContextDispatch(&fsr2Context, &dispatchDesc);
    return static_cast<int>(err);
}

JNIEXPORT jobject JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxGetTextureResourceGL(JNIEnv *env, jobject, jlong texGL, jint width, jint height, jint type)
{
    FfxResource resource = ffxGetTextureResourceGL(texGL, width, height, type);
    jclass javaffxrescls = env->FindClass("io/homo/superresolution/fsr2/types/FfxResource");
    jmethodID constrocMID = env->GetMethodID(javaffxrescls, "<init>", "(IZJIIIIIIII)V");
    jobject javaffxres_ojb = env->NewObject(javaffxrescls, constrocMID, (jint)texGL, resource.isDepth, (jlong)resource.descriptorData, (jint)resource.description.type, (jint)resource.description.format, resource.description.width, resource.description.height, resource.description.depth, resource.description.mipCount, (jint)resource.description.flags, (jint)resource.state);
    return javaffxres_ojb;
};

JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxFsr2Test(JNIEnv *env, jobject o)
{
    check_env(env);
    jobject j = Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_ffxGetTextureResourceGL(env, o, 0, 1, 1, 0);
    ffxResourceJavaToCpp(env, j);
    return 0;
};

JNIEXPORT jstring JNICALL Java_io_homo_superresolution_fsr2_nativelib_FSR2ApiHelper_getVersionInfo
  (JNIEnv *env, jobject){
     return (env)->NewStringUTF(VES);
  }