// LeaveMeAlone Game by Netologiya. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LeaveMeAloneTarget : TargetRules
{
	public LeaveMeAloneTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LeaveMeAlone" } );
	}
}
