// Copyright Floruit, Inc. All Rights Reserved.


#include "DialoguesConfig.h"

TMap<FName, FSoftObjectPath> UDialoguesConfig::GetSoftPaths()
{
	return ToSoftPaths(DialoguesById);
}
