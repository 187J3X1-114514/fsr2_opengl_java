#ifdef ON_LINUX
    #include "jni_linux64.h"
#else
    #include "jni.h"
#endif
#include "glfw3.h"
#include "ffx-fsr2-api/ffx_types.h"

void java_log(const char* msg,int level);
void set_env(JNIEnv * env);
char* get_gpu_info_nv();
JNIEnv* get_env();
GLFWglproc java_glfwGetProcAddress(const char* name);
bool ToCppBool(jboolean value);
FfxResource ffxResourceJavaToCpp(JNIEnv* env, jobject javaffxres);
FfxResource __ffxResourceJavaToCpp(
    int resource, bool isDepth, uint64_t descriptorData,
    int type, int format, int width, int height, int depth,
    int mipCount, int flags, int state
);