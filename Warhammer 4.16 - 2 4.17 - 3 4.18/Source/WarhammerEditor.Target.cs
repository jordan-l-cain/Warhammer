// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class WarhammerEditorTarget : TargetRules
{
	public WarhammerEditorTarget(TargetInfo Target) : base (Target)

    {
		Type = TargetType.Editor;
        ExtraModuleNames.Add("Warhammer");
    }

	//
	// TargetRules interface.
	//
}
