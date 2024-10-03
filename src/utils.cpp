#include "utils.h"
#include <iostream>
#include <vector>
#include "ffx-fsr2-api/ffx_types.h"

JNIEnv *cur_env;
void set_env(JNIEnv *env)
{
    cur_env = env;
}

JNIEnv *get_env()
{
    return cur_env;
}

void java_log(const char *msg, int level)
{
    jclass cpp_helper = cur_env->FindClass("io/homo/superresolution/fsr2/CPPHelper");
    jmethodID methodID = cur_env->GetStaticMethodID(cpp_helper, "CPP_Log", "(Ljava/lang/String;I)V");
    jstring jmsg = cur_env->NewStringUTF(msg);
    cur_env->CallStaticVoidMethod(cpp_helper, methodID, jmsg, jint(level));
    cur_env->DeleteLocalRef(jmsg);
}

GLFWglproc java_glfwGetProcAddress(const char *name)
{
    jclass cpp_helper = cur_env->FindClass("io/homo/superresolution/fsr2/CPPHelper");
    jmethodID methodID = cur_env->GetStaticMethodID(cpp_helper, "CPP_glfwGetProcAddress", "(Ljava/lang/String;)J");
    if (methodID)
    {
        jstring jmsg = cur_env->NewStringUTF(name);
        jlong jlongValue = cur_env->CallStaticLongMethod(cpp_helper, methodID, jmsg);
        GLFWglproc glfwProc = reinterpret_cast<GLFWglproc>(jlongValue);
        cur_env->DeleteLocalRef(jmsg);
        return glfwProc;
    }
    return 0;
}

/*
using namespace std;

char *get_gpu_info_nv()
{
    char *out = (char *)"";
    json root_json;
    nvmlReturn_t result = nvmlInit();
    if (result != NVML_SUCCESS)
    {
        return (char *)"Failed to initialize NVML: ";
    }
    unsigned int deviceCount;
    result = nvmlDeviceGetCount(&deviceCount);
    if (result != NVML_SUCCESS)
    {
        return (char *)"Failed to get device count: ";
    }

    root_json["device_count"] = deviceCount;
    root_json["gpus"] = {};
    for (unsigned int i = 0; i < deviceCount; i++)
    {
        json gpuinfo;
        gpuinfo["id"] = i;
        gpuinfo["msg"] = "OK";
        nvmlDevice_t device;
        result = nvmlDeviceGetHandleByIndex(i, &device);
        if (result != NVML_SUCCESS)
        {
            gpuinfo["msg"] = "Failed to get handle for device :" + std::string(nvmlErrorString(result));
            root_json["gpus"].push_back(gpuinfo);
            continue;
        }
        char name[NVML_DEVICE_NAME_BUFFER_SIZE];
        result = nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE);
        if (result != NVML_SUCCESS)
        {
            gpuinfo["msg"] = "Failed to get name for device :" + std::string(nvmlErrorString(result));
            root_json["gpus"].push_back(gpuinfo);
            continue;
        }
        gpuinfo["name"] = name;
        nvmlMemory_t memoryInfo;
        result = nvmlDeviceGetMemoryInfo(device, &memoryInfo);
        if (result != NVML_SUCCESS)
        {
            gpuinfo["msg"] = "Failed to get memory info for device :" + std::string(nvmlErrorString(result));
            root_json["gpus"].push_back(gpuinfo);
            continue;
        }
        gpuinfo["memory_free"] = memoryInfo.free;
        gpuinfo["memory_total"] = memoryInfo.total;
        gpuinfo["memory_used"] = memoryInfo.used;
        root_json["gpus"].push_back(gpuinfo);
    }
    std::string jsonString = root_json.dump(4);
    nvmlShutdown();
    return (char *)jsonString.c_str();
}
*/
bool ToCppBool(jboolean value)
{
    return value == JNI_TRUE;
}

FfxResource ffxResourceJavaToCpp(JNIEnv *env, jobject javaffxres)
{
    jclass cls = env->GetObjectClass(javaffxres);
    jfieldID resourceFieldId = env->GetFieldID(cls, "resource", "J");
    jfieldID isDepthFieldId = env->GetFieldID(cls, "isDepth", "Z");
    jfieldID descriptorDataFieldId = env->GetFieldID(cls, "descriptorData", "J");
    jfieldID typeFieldId = env->GetFieldID(cls, "type", "I");
    jfieldID formatFieldId = env->GetFieldID(cls, "format", "I");
    jfieldID widthFieldId = env->GetFieldID(cls, "width", "I");
    jfieldID heightFieldId = env->GetFieldID(cls, "height", "I");
    jfieldID depthFieldId = env->GetFieldID(cls, "depth", "I");
    jfieldID mipCountFieldId = env->GetFieldID(cls, "mipCount", "I");
    jfieldID flagsFieldId = env->GetFieldID(cls, "flags", "I");
    jfieldID stateFieldId = env->GetFieldID(cls, "state", "I");
    uint64_t resourceField = env->GetLongField(javaffxres, resourceFieldId);
    bool isDepth = env->GetBooleanField(javaffxres, isDepthFieldId);
    uint64_t descriptorDataField = env->GetLongField(javaffxres, descriptorDataFieldId);
    int type = env->GetIntField(javaffxres, typeFieldId);
    int format = env->GetIntField(javaffxres, formatFieldId);
    int width = env->GetIntField(javaffxres, widthFieldId);
    int height = env->GetIntField(javaffxres, heightFieldId);
    int depth = env->GetIntField(javaffxres, depthFieldId);
    int mipCount = env->GetIntField(javaffxres, mipCountFieldId);
    int flags = env->GetIntField(javaffxres, flagsFieldId);
    int state = env->GetIntField(javaffxres, stateFieldId);

    FfxResource res = __ffxResourceJavaToCpp(resourceField, isDepth, descriptorDataField, type, format, width, height, depth, mipCount, flags, state);

    return res;
}

FfxResource __ffxResourceJavaToCpp(
    int resource, bool isDepth, uint64_t descriptorData,
    int type, int format, int width, int height, int depth,
    int mipCount, int flags, int state)
{
    FfxResource ffxresource = {};
    ffxresource.resource = reinterpret_cast<void *>(static_cast<uintptr_t>(resource));
    ffxresource.descriptorData = descriptorData;
    ffxresource.state = (FfxResourceStates)state;
    ffxresource.isDepth = isDepth;
    ffxresource.description.flags = (FfxResourceFlags)flags;
    ffxresource.description.type = (FfxResourceType)type;
    ffxresource.description.width = width;
    ffxresource.description.height = height;
    ffxresource.description.depth = depth;
    ffxresource.description.mipCount = mipCount;
    ffxresource.description.format = (FfxSurfaceFormat)format;
    return ffxresource;
}