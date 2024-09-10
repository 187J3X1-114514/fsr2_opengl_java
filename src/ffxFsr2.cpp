#include "pch.h"
#include "io_homo_superresolution_fsr2_nativelib_ffx_fsr2_api.h"
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
FfxFsr2ContextDescription contextDesc;


static void up_env(JNIEnv *env)
{
    set_env(env);
}
static void check_env(JNIEnv *env)
{
    set_env(env);
}

JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_ffxFsr2GetInterfaceGL(JNIEnv *env, jobject, jint scratchMemorySize, jfloat fsr2Ratio, jint width, jint height, jint flags)
{

    check_env(env);
    unsigned int renderWidth = static_cast<unsigned int>(width / fsr2Ratio);
    unsigned int renderHeight = static_cast<unsigned int>(height / fsr2Ratio);
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
        if (type == FFX_FSR2_MESSAGE_TYPE_WARNING)
        {
            java_log(cstr, 1);
        }
        else
        {
            if (type == FFX_FSR2_MESSAGE_TYPE_ERROR)
            {
                java_log(cstr, 2);
            }
            else
            {
                java_log(cstr, 0);
            }
        }
    };
    fsr2ScratchMemory = std::make_unique<char[]>(scratchMemorySize);
    FfxErrorCode code = ffxFsr2GetInterfaceGL(&contextDesc.callbacks, fsr2ScratchMemory.get(), scratchMemorySize, java_glfwGetProcAddress);
    return static_cast<int>(code);
}
JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_ffxFsr2GetScratchMemorySizeGL(JNIEnv *env, jobject)
{
    check_env(env);
    return static_cast<int>(ffxFsr2GetScratchMemorySizeGL());
}

JNIEXPORT void JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_init(JNIEnv *env, jobject)
{
    up_env(env);
}

JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_ffxFsr2CreateContext(JNIEnv *env, jobject)
{
    check_env(env);
    return static_cast<int>(ffxFsr2ContextCreate(&fsr2Context, &contextDesc));
};

JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_ffxFsr2ContextDestroy(JNIEnv *env, jobject)
{
    check_env(env);
    return static_cast<int>(ffxFsr2ContextDestroy(&fsr2Context));
}
JNIEXPORT jstring JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_getGPUInfoNV(JNIEnv *env, jobject)
{
    check_env(env);
    return env->NewStringUTF(get_gpu_info_nv());
};

JNIEXPORT jstring JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_getGPUInfoAMD(JNIEnv *env, jobject)
{
    check_env(env);
    return env->NewStringUTF("");
};
JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_ffxFsr2ContextDispatch(
    JNIEnv *env,
    jobject,
    jint color,
    jint depth,
    jint motionVectors,
    jint exposure,
    jint reactive,
    jint output,
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
    FfxFsr2DispatchDescription dispatchDesc{
        .color = ffxGetTextureResourceGL(color, renderWidth, renderHeight, GL_R11F_G11F_B10F),
        .depth = ffxGetTextureResourceGL(depth, renderWidth, renderHeight, GL_DEPTH_COMPONENT32F),
        .motionVectors = ffxGetTextureResourceGL(motionVectors, renderWidth, renderHeight, GL_RG16F),
        .exposure = exposure_tex,
        .reactive = reactive_tex,
        .transparencyAndComposition = transparencyAndComposition_tex,
        .output =
            ffxGetTextureResourceGL(output, width, height, GL_R11F_G11F_B10F),
        .jitterOffset = {jitterX, jitterY},
        .motionVectorScale = {float(static_cast<int>(renderWidth)), float(static_cast<int>(renderHeight))},
        .renderSize = {static_cast<uint32_t>(renderWidth), static_cast<uint32_t>(renderHeight)},
        .enableSharpening = ToCppBool(enableSharpening),
        .sharpness = sharpness,
        .frameTimeDelta = static_cast<float>(frameTimeDelta), // ms
        .preExposure = preExposure,
        .reset = ToCppBool(reset),
        .cameraNear = cameraNear,
        .cameraFar = cameraFar,
        .cameraFovAngleVertical = cameraFovY,
        .viewSpaceToMetersFactor = viewSpaceToMetersFactor,
        .deviceDepthNegativeOneToOne = ToCppBool(deviceDepthNegativeOneToOne),
    };

    FfxErrorCode err = ffxFsr2ContextDispatch(&fsr2Context, &dispatchDesc);
    return static_cast<int>(err);
}

JNIEXPORT jobject JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_ffxGetTextureResourceGL(JNIEnv *env, jobject, jlong texGL, jint width, jint height, jint type)
{
    FfxResource resource = ffxGetTextureResourceGL(texGL, width, height, type);
    jclass javaffxrescls = env->FindClass("io/homo/superresolution/fsr2/types/FfxResource");
    jmethodID constrocMID = env->GetMethodID(javaffxrescls, "<init>", "(IZJIIIIIIII)V");
    jobject javaffxres_ojb = env->NewObject(javaffxrescls, constrocMID,(jint)(uintptr_t)(resource.resource),resource.isDepth,(jlong)resource.descriptorData,(jint)resource.description.type,(jint)resource.description.format,resource.description.width,resource.description.height,resource.description.depth,resource.description.mipCount,(jint)resource.description.flags,(jint)resource.state);
    return javaffxres_ojb;
};

JNIEXPORT jint JNICALL Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_ffxFsr2Test(JNIEnv *env, jobject o)
{
    check_env(env);
    jobject j = Java_io_homo_superresolution_fsr2_nativelib_ffx_1fsr2_1api_ffxGetTextureResourceGL(env, o, 0, 1, 1, 0);
    ffxResourceJavaToCpp(env, j);
    return 0;
};