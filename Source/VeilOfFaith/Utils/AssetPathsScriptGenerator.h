// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityObject.h"
#include "Modules/ModuleManager.h"

class FAssetPathsScriptGenerator : public UEditorUtilityObject 
{
	
public:
	static void GenerateScriptAssetPaths();
};
