#include <jni.h>
#include <stdlib.h>
#include <string.h>

/*
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
*/

// Network-related structures
#define MAX_PEER_NAME 64
typedef struct {
  char name[MAX_PEER_NAME];
  short port;
  int socket;
  short base;  // first node offset
  short count; // number of nodes
} nio_peer;
typedef struct {
  int server; // socket file descriptor
  int n_peer;
  nio_peer* peer;
} nio_conn;

// Encoding-related structures
#define MAX_CLASS_PATH   64
#define MAX_CLASS_ATTRS  32
#define MAX_CLASS_NAMES 256
#define nt_bool    1 // 1 byte
#define nt_byte    2 // 1 byte
#define nt_char    3 // 2 bytes
#define nt_short   4 // 2 bytes
#define nt_int     5 // 4 bytes
#define nt_long    6 // 8 bytes
#define nt_float   7 // 4 bytes
#define nt_double  8 // 8 bytes
#define nt_string  9 // 2 bytes=length, x bytes=payload
#define nt_date   10 // encoded as long
typedef struct {
  jclass cls;
  jfieldID field[MAX_CLASS_ATTRS];
  char type[MAX_CLASS_ATTRS]; // types encoded as nt_* chars

//  char[MAX_CLASS_PATH] path;   // absolute class path
//  char[MAX_CLASS_NAMES] names; // '\0'-separated attribute names
  // XXX: field ids
} nio_class;
typedef struct {
  int n_classes;
  nio_class* cls;
} nio_encoder;

// Global state
typedef struct {
  nio_conn conn;
  nio_encoder encoder;
} nio_data;

jfieldID nio_field = NULL;

static inline void init(JNIEnv *env, jobject obj) {
  if (nio_field==NULL) {
    jclass objClass = (*env)->GetObjectClass(env, obj);
    jfieldID nio_field = (*env)->GetFieldID(env, objClass, "ptr", "J");
  }
  nio_data* data = (void*)(long) (*env)->GetLongField(env, obj, nio_field);
  if (data==NULL) {
    data = (nio_data*)malloc(sizeof(nio_data));
    (*env)->SetLongField(env, obj, nio_field, (jlong)(long)((void*)data) );
    printf("init'd\n");
  }
  printf("called %ld\n",(long)data);
}

JNIEXPORT void JNICALL Java_serial_NodeIOImpl_free(JNIEnv *env, jobject obj) {
  if (nio_field==NULL) return;{
    jclass objClass = (*env)->GetObjectClass(env, obj);
    jfieldID nio_field = (*env)->GetFieldID(env, objClass, "ptr", "J");
  }
  nio_data* data = (void*)(long)(*env)->GetLongField(env, obj, nio_field);
  if (data!=NULL) {
    free(data);
    (*env)->SetLongField(env,obj,nio_field,0);

    printf("free'd\n");

  }
}
JNIEXPORT void JNICALL Java_serial_NodeIOImpl_setPeers(JNIEnv *env, jobject obj, jobjectArray peers) { init(env,obj); printf("setPeers\n"); }
JNIEXPORT void JNICALL Java_serial_NodeIOImpl_setTypes(JNIEnv *env, jobject obj, jobjectArray cls) { init(env,obj); printf("setTypes\n"); }
JNIEXPORT void JNICALL Java_serial_NodeIOImpl_send(JNIEnv *env, jobject obj, jobject msg, jint to) { printf("send\n"); }
JNIEXPORT void JNICALL Java_serial_NodeIOImpl_poll(JNIEnv *env, jobject obj) { printf("poll\n"); }

// http://docs.oracle.com/javase/6/docs/technotes/guides/jni/spec/functions.html#NewGlobalRef
// http://www.accordess.com/wpblog/an-overview-of-java-compilation-api-jsr-199/
// http://rkennke.wordpress.com/2007/07/24/efficient-jni-programming-ii-field-and-method-access/

// Benchmark ----------------------------------------------------------------

jclass tcl,dcl;
jfieldID fb,fi1,fi2,fi3,fi4,fi5,ff1,ff2,fs,fd;
jmethodID tin,din,mdt;
/*
Z boolean
B byte
C char
S short
I int
J long
F float
D double
L fully-qualified-class ;
[ type
( arg-types ) ret-type method type

  public boolean b; // 1 o=0
  public byte i1;   // 1 o=1
  public char i2;   // 2 o=2
  public short i3;  // 2 o=4
  public int i4;    // 4 o=6
  public long i5;   // 8 o=10
  public float f1;  // 4 o=18
  public double f2; // 8 o=22
  // 10 + length bytes
  public java.util.Date d; // 8 o=30
  public String s;         // 2 o=38 + length*2 o=40
*/

JNIEXPORT void JNICALL Java_serial_NodeIOImpl_encInit(JNIEnv *env, jobject obj, jobject tuple) {
  tcl = (*env)->NewGlobalRef(env,(*env)->GetObjectClass(env,tuple));
  dcl = (*env)->NewGlobalRef(env,(*env)->FindClass(env,"java/util/Date"));
  fb = (*env)->GetFieldID(env,tcl,"b","Z");
  fi1 = (*env)->GetFieldID(env,tcl,"i1","B");
  fi2 = (*env)->GetFieldID(env,tcl,"i2","C");
  fi3 = (*env)->GetFieldID(env,tcl,"i3","S");
  fi4 = (*env)->GetFieldID(env,tcl,"i4","I");
  fi5 = (*env)->GetFieldID(env,tcl,"i5","J");
  ff1 = (*env)->GetFieldID(env,tcl,"f1","F");
  ff2 = (*env)->GetFieldID(env,tcl,"f2","D");
  fs = (*env)->GetFieldID(env,tcl,"s","Ljava/lang/String;");
  fd = (*env)->GetFieldID(env,tcl,"d","Ljava/util/Date;");
  mdt = (*env)->GetMethodID(env,dcl,"getTime","()J");
  tin = (*env)->GetMethodID(env,tcl,"<init>","()V");
  din = (*env)->GetMethodID(env,dcl,"<init>","(J)V");
}

static inline void pack(JNIEnv *env, jobject obj, char* buf) {
  *(char*)(buf+0) = (*env)->GetBooleanField(env, obj, fb) ? 1 : 0;
  *(char*)(buf+1) = (*env)->GetByteField(env, obj, fi1);
  *(short*)(buf+2) = (*env)->GetCharField(env, obj, fi2);
  *(short*)(buf+4) = (*env)->GetCharField(env, obj, fi3);
  *(int*)(buf+6) = (*env)->GetCharField(env, obj, fi4);
  *(long*)(buf+10) = (*env)->GetCharField(env, obj, fi5);
  *(float*)(buf+18) = (*env)->GetCharField(env, obj, ff1);
  *(double*)(buf+22) = (*env)->GetCharField(env, obj, ff2);
  jobject d = (*env)->GetObjectField(env, obj, fd);
  *(long*)(buf+30) = (*env)->CallLongMethod(env,d, mdt);
  // String
  jstring s = (*env)->GetObjectField(env, obj, fs);
  short len = (short)(*env)->GetStringLength(env, s);
  *(short*)(buf+38) = len;
  const jchar* chs = (*env)->GetStringChars(env, s, NULL);
  memcpy(buf+40,chs,len*2);
  (*env)->ReleaseStringChars(env,s,chs);
  (*env)->DeleteLocalRef(env, d);
  (*env)->DeleteLocalRef(env, s);
}

static inline jobject unpack(JNIEnv *env, char* buf) {
  jobject obj = (*env)->NewObject(env, tcl, tin);
  (*env)->SetBooleanField(env, obj, fb, buf[0]);
  (*env)->SetByteField(env, obj, fi1, *(char*)(buf+1));
  (*env)->SetCharField(env, obj, fi2, *(short*)(buf+2));
  (*env)->SetCharField(env, obj, fi3, *(short*)(buf+4));
  (*env)->SetCharField(env, obj, fi4, *(int*)(buf+6));
  (*env)->SetCharField(env, obj, fi5, *(long*)(buf+10));
  (*env)->SetCharField(env, obj, ff1, *(float*)(buf+18));
  (*env)->SetCharField(env, obj, ff2, *(double*)(buf+22));
  jobject d = (*env)->NewObject(env, dcl, din,*(long*)(buf+30));
  (*env)->SetObjectField(env, obj, fd, d);
  jstring s = (*env)->NewString(env,(jchar*)(buf+40), *(short*)(buf+38));
  (*env)->SetObjectField(env, obj, fs, s);
  (*env)->DeleteLocalRef(env, d);
  (*env)->DeleteLocalRef(env, s);
  return obj;
}

JNIEXPORT jobject JNICALL Java_serial_NodeIOImpl_encDec(JNIEnv *env, jobject obj, jobject tuple) {
  char* buf = (char*)malloc(2048);
  (*env)->DeleteLocalRef(env, obj);
  pack(env,tuple,buf);
  (*env)->DeleteLocalRef(env, tuple);
  jobject res = unpack(env,buf);
  free(buf);
  return res;
}

