#include "Vec3.h"

// http://java.sun.com/docs/books/jni/html/jniTOC.html
// http://www.iam.ubc.ca/guides/javatut99/native1.1/implementing/field.html
// http://www.iam.ubc.ca/guides/javatut99/native1.1/implementing/method.html
// http://www.iam.ubc.ca/guides/javatut99/native1.1/implementing/example-1dot1/FieldAccess.c
// http://shootout.alioth.debian.org/u64/program.php?test=pidigits&lang=scala&id=4
// http://stackoverflow.com/questions/3950635/how-to-compile-dynamic-library-for-a-jni-application-on-linux

JNIEXPORT jobject JNICALL Java_Vec3_dot(JNIEnv *env, jobject a, jobject b) {
	jclass cls = (*env)->GetObjectClass(env, a); // Vec3 class

	// retrieve values and compute dot product
	jfieldID fid;
	fid = (*env)->GetFieldID(env, cls, "x", "I");
	int x = (*env)->GetIntField(env, a, fid) * (*env)->GetIntField(env, b, fid);
	fid = (*env)->GetFieldID(env, cls, "y", "I");
	int y = (*env)->GetIntField(env, a, fid) * (*env)->GetIntField(env, b, fid);
	fid = (*env)->GetFieldID(env, cls, "z", "I");
	int z = (*env)->GetIntField(env, a, fid) * (*env)->GetIntField(env, b, fid);

	// invoke constructor
	cls = (*env)->FindClass(env, "Vec3");

	jmethodID cid = (*env)->GetMethodID(env, cls, "<init>", "(III)V");
	jobject result = (*env)->NewObject(env, cls, cid, x,y,z);
	return result;
}
