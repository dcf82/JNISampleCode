#include <jni.h>
#include <android/log.h>
#include "android_debug.h"

extern "C" {
    JNIEXPORT jint JNICALL Java_com_google_sample_NativeDeclarations_getPoints(JNIEnv *, jclass, jobject);
    jint extractInt(JNIEnv *env, jobject arg);
    jfloat extractFloat(JNIEnv *env, jobject arg);
}

JNIEXPORT jint JNICALL
Java_com_google_sample_NativeDeclarations_getPoints(JNIEnv *env, jclass self, jobject treeMap) {

    jclass c_treeMap = env->GetObjectClass(treeMap);

    jmethodID entrySet = env->GetMethodID(c_treeMap, "keySet", "()Ljava/util/Set;");

    jobject mySet = env->CallObjectMethod(treeMap, entrySet);

    jclass c_Set = env->FindClass("java/util/Set");

    jmethodID m_GetSize = env->GetMethodID(c_Set, "size", "()I");

    jmethodID c_toArray = env->GetMethodID(c_Set, "toArray", "()[Ljava/lang/Object;");
    jobjectArray myArray = (jobjectArray)env->CallObjectMethod(mySet, c_toArray);

    jmethodID valueMethod = env->GetMethodID(c_treeMap, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");

    int jSize = env->CallIntMethod(mySet, m_GetSize);
    int key;
    int stringCount = env->GetArrayLength(myArray);
    int count;

    jobject item;
    jobject floatArray;
    jobject objValue;
    jfloat value;

    for (int i = 0; i < stringCount; i++) {
        item = env->GetObjectArrayElement(myArray, i);
        key = extractInt(env, item);

        jclass c_int = env->FindClass("java/lang/Integer");
        jmethodID methodID = env->GetMethodID(c_int, "<init>", "(I)V");
        jobject objInt = env->NewObject(c_int, methodID, key);
        floatArray = env->CallObjectMethod(treeMap, valueMethod, objInt);
        env->DeleteLocalRef(objInt);

        jclass cArrayList = env->FindClass("java/util/ArrayList");
        jmethodID mSizeID = env->GetMethodID(cArrayList, "size", "()I");
        jmethodID getValueMethod = env->GetMethodID(cArrayList, "get", "(I)Ljava/lang/Object;");

        jclass c_float = env->FindClass("java/lang/Float");
        jmethodID floatMethodID = env->GetMethodID(c_float, "<init>", "(F)V");
        jmethodID setItemArrayListMethodID = env->GetMethodID(cArrayList, "set", "(ILjava/lang/Object;)Ljava/lang/Object;");

        count = env->CallIntMethod(floatArray, mSizeID);
        LOGD( "Count :: %d" , count);
        for (int j = 0; j < count; j++) {
            objValue = env->CallObjectMethod(floatArray, getValueMethod, j);
            value = extractFloat(env, objValue);
            LOGD( "Key : %d, Value %f" , key, value);
            jobject objFloat = env->NewObject(c_float, floatMethodID, value * 2.1);
            env->CallObjectMethod(floatArray, setItemArrayListMethodID, j, objFloat);
            env->DeleteLocalRef(objFloat);
        }

    }

    return jSize;
}

jint extractInt(JNIEnv *env, jobject arg)
{
    jclass argClass = env->GetObjectClass(arg);
    jmethodID ajf = env->GetMethodID(argClass, "intValue", "()I");
    return env->CallIntMethod(arg, ajf);
}

jfloat extractFloat(JNIEnv *env, jobject arg)
{
    jclass argClass = env->GetObjectClass(arg);
    jmethodID ajf = env->GetMethodID(argClass, "floatValue", "()F");
    return env->CallFloatMethod(arg, ajf);
}
