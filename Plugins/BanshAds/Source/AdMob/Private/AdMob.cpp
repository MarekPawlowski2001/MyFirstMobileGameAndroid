//Copyright Bansh Games 2022, All Rights Reserved.
#include "AdMob.h"


#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

#define LOCTEXT_NAMESPACE "FAdMobModule"

void FAdMobModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FAdMobModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAdMobModule, AdMob)



void FAdMobModule::AdMobShowBanner(int32 Index, bool isOnBottom) {
	TArray<FString> AdUnitIDs;
	int32 count = GConfig->GetArray(TEXT("/Script/AdsEditor.AdMobSetting"), TEXT("AndroidBannerUnit"), AdUnitIDs, GEngineIni);

#if PLATFORM_ANDROID
	if (count != 0 && !AdUnitIDs[Index].IsEmpty())
	{
		if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
		{
			static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ShowAdBanner_AdMob", "(Ljava/lang/String;Z)V", false);

			FString AdUnitID = AdUnitIDs[Index];
			auto AdUnitIDArg = FJavaHelper::ToJavaString(Env, AdUnitID);
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, *AdUnitIDArg, isOnBottom);
}
		}

#endif
	};

void FAdMobModule::AdMobHideBanner() {
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_HideBanner_AdMob", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
#endif
};

void FAdMobModule::AdMobCloseBanner() {
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CloseBanner_AdMob", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
#endif
};

void FAdMobModule::AdMobLoadInterstitialAd(int32 Index) {
	TArray<FString> AdUnitIDs;
	int32 count = GConfig->GetArray(TEXT("/Script/AdsEditor.AdMobSetting"), TEXT("AndroidInterstitialUnit"), AdUnitIDs, GEngineIni);

#if PLATFORM_ANDROID
	if (count != 0 && !AdUnitIDs[Index].IsEmpty())
	{
		if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
		{

			static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LoadInterstitialAd_AdMob", "(Ljava/lang/String;)V", false);

			auto AdUnitIDArg = FJavaHelper::ToJavaString(Env, AdUnitIDs[Index]);
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, *AdUnitIDArg);
}
		}

#endif
	};


void FAdMobModule::AdMobShowInterstitialAd() {
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ShowInterstitialAd_AdMob", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
#endif
};