// LeaveMeAlone Game by Netologiya. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LeaveMeAloneEditorTarget : TargetRules
{
	public LeaveMeAloneEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LeaveMeAlone" } );
	}
}
