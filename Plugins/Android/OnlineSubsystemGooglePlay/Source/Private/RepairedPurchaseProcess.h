#include "Android/AndroidJNI.h"


#include "Android/AndroidJavaEnv.h"
#include "CoreMinimal.h"
#include "HAL/ThreadSingleton.h"
#include "HAL/PlatformMisc.h"
#include "HAL/ThreadManager.h"
#include "Containers/UnrealString.h"


#include "Android/AndroidApplication.h"
#include "Android/AndroidInputInterface.h"
#include "Android/AndroidPlatformCrashContext.h"
#include "Android/AndroidStats.h"
#include "Async/TaskGraphInterfaces.h"
#include "HAL/ExceptionHandling.h"
#include "HAL/PlatformStackWalk.h"
#include "Math/Vector.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/CoreDelegates.h"
#include "Misc/DateTime.h"
#include "Misc/EmbeddedCommunication.h"
#include "Misc/FeedbackContext.h"
#include "UnrealEngine.h"
#include "Widgets/Input/IVirtualKeyboardEntry.h"

THIRD_PARTY_INCLUDES_START
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
THIRD_PARTY_INCLUDES_END

#define JNI_CURRENT_VERSION JNI_VERSION_1_6

FScopedJavaObject<jobjectArray> ToJavaStringArray_v2(JNIEnv* Env, const TArray<FStringView>& UnrealStrings)
{
	jclass JavaStringClass = FJavaWrapper::FindClass(Env,"java/lang/String",false);
	jobjectArray ObjectArray = Env->NewObjectArray((jsize)UnrealStrings.Num(), JavaStringClass, NULL);
	for (int32 Idx = 0; Idx < UnrealStrings.Num(); ++Idx)
	{
		// FStringView of an empty FString contains a null pointer as data
		if (UnrealStrings[Idx].GetData())
		{
			Env->SetObjectArrayElement(ObjectArray, Idx, Env->NewStringUTF(TCHAR_TO_UTF8(UnrealStrings[Idx].GetData())));
		}
		else
		{
			Env->SetObjectArrayElement(ObjectArray, Idx, Env->NewStringUTF(""));
		}
	}
	return NewScopedJavaObject(Env, ObjectArray);
}

bool AndroidThunkCpp_Iap_BeginPurchase_v2(const TArray<FStringView>& ProductIds, const FString& AccountId)
{
	FPlatformMisc::LowLevelOutputDebugStringf(TEXT("[JNI] - AndroidThunkCpp_Iap_BeginPurchase_v2"));
	FPlatformMisc::LowLevelOutputDebugStringf(TEXT("ProductIds.size()=%d"), ProductIds.Num());
	FPlatformMisc::LowLevelOutputDebugStringf(TEXT("ProductIds[0]=%s"),*static_cast<FString>(ProductIds[0]));
	bool bResult = false;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		//CHECK_JNI_METHOD(FJavaWrapper::AndroidThunkJava_IapBeginPurchase);

		auto ProductIdsJava = ToJavaStringArray_v2(Env, ProductIds);
		if (AccountId.IsEmpty())
		{
			FPlatformMisc::LowLevelOutputDebugStringf(TEXT("AccountId is Empty"));

			bResult = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GoogleServicesThis, FJavaWrapper::AndroidThunkJava_IapBeginPurchase, *ProductIdsJava, nullptr);
		}
		else
		{
			FPlatformMisc::LowLevelOutputDebugStringf(TEXT("AccountId is not Empty"));
			auto ObfuscatedAccountIdJava = FJavaHelper::ToJavaString(Env, AccountId);
			bResult = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GoogleServicesThis, FJavaWrapper::AndroidThunkJava_IapBeginPurchase, *ProductIdsJava, *ObfuscatedAccountIdJava);
		}
	}

	return bResult;
}