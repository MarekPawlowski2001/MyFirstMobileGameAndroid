//Copyright Bansh Games 2022, All Rights Reserved.
#pragma once

#include "Modules/ModuleManager.h"
#include "AdMobBPLibrary.h"
#include "Misc/ConfigCacheIni.h"
#include "Async/TaskGraphInterfaces.h"

class FAdMobModule : public IModuleInterface
{

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	UFUNCTION(BlueprintCallable)
	static void AdMobShowBanner(int32 Index, bool isOnBottom);

	UFUNCTION(BlueprintCallable)
	static void AdMobHideBanner();

	UFUNCTION(BlueprintCallable)
	static void AdMobCloseBanner();

	// Interstial Ads functionalities

	UFUNCTION(BlueprintCallable)
	static void AdMobLoadInterstitialAd(int32 Index);

	UFUNCTION(BlueprintCallable)
	static void AdMobShowInterstitialAd();
};



