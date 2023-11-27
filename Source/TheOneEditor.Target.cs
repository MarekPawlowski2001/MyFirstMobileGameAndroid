// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheOneEditorTarget : TargetRules
{
	public TheOneEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange( new string[] { "TheOne" } );
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
    }
}
