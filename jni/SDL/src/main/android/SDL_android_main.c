/*
    SDL_android_main.c, placed in the public domain by Sam Lantinga  3/13/14
*/
#include "../../SDL_internal.h"

#ifdef __ANDROID__

/* Include the SDL main definition header */
#include "SDL_main.h"

/*******************************************************************************
                 Functions called by JNI
*******************************************************************************/
#include <jni.h>

static JavaVM* jvm;

/* Called before SDL_main() to initialize JNI bindings in SDL library */
extern void SDL_Android_Init(JNIEnv* env, jclass cls);

/* Start up the SDL app */
//void Java_uk_co_armedpineapple_cth_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject obj)
void Java_uk_co_armedpineapple_cth_SDLActivity_nativeInit(
		JNIEnv* env, jclass cls, jobject configuration,
		jstring jni_loadgame_path) {

    const char* loadgame_path = (*env)->GetStringUTFChars(env, jni_loadgame_path, 0);

    /* This interface could expand with ABI negotiation, calbacks, etc. */
    SDL_Android_Init(env, cls);

    SDL_SetMainReady();

    /* Run the application code! */
	int status;
	char *argv[3];
	int argc = 1;
	argv[0] = strdup("SDL_app");
	if (strlen(loadgame_path) > 1) {
		char* loadstr = (char*) malloc(
				(8 + strlen(loadgame_path)) * sizeof(char));
		strcpy(loadstr, "--load=");
		loadstr = strcat(loadstr, loadgame_path);
		argv[1] = loadstr;
		argc = 2;
	}

    status = SDL_main(argc, argv, jvm, configuration);

    /* Do not issue an exit or the whole application will terminate instead of just the SDL thread */
    /* exit(status); */
}

#endif /* __ANDROID__ */

/* vi: set ts=4 sw=4 expandtab: */
