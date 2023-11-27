// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
public class TheOne : ModuleRules
{
	public TheOne(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Json", "JsonUtilities", "AdMob"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		// Uncomment if you are using Slate UI
		 PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		 PrivateDependencyModuleNames.Add("OnlineSubsystem");
		


		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
    		DynamicallyLoadedModuleNames.Add("OnlineSubsystemGooglePlay");
		PrivateDependencyModuleNames.Add("AndroidAdvertising");
		
		var AndroidX = Path.Combine(ModuleDirectory, "AndroidxConfig.xml");
		AdditionalPropertiesForReceipt.Add("AndroidXPlugin", AndroidX);
		}
		
		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
    		DynamicallyLoadedModuleNames.Add("OnlineSubsystemIOS");
			
		}

	}
}
