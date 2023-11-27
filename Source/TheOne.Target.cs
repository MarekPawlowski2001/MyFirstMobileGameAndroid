// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheOneTarget : TargetRules
{
	public TheOneTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange( new string[] { "TheOne" } );
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
    }
}
