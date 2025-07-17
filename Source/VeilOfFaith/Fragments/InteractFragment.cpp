// Copyright Floruit, Inc. All Rights Reserved.


#include "InteractFragment.h"

#include "GameFramework/Character.h"
#include "VeilOfFaith/Handlers/Base/Handlerable.h"
#include "VeilOfFaith/Handlers/Base/Interactable.h"
#include "VeilOfFaith/Handlers/Base/InteractParams.h"

void UInteractFragment::Initialize(ACharacter* pCharacter, AController* pController)
{
	Super::Initialize(pCharacter, pController);
}

bool UInteractFragment::TryInteract(TSharedPtr<FInteractParams> Params)
{
	FVector CameraLocation;
	FRotator CameraRotation;
	if (Controller != nullptr)
	{
		Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);
	}
	
	FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * 5000.f);
	FHitResult HitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Character->GetUniqueID());

	if (auto World = GetWorld())
	{
		World->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECC_Visibility, QueryParams);	
	}

	if (HitResult.bBlockingHit)
	{
		auto Actor = HitResult.GetActor();
		if (auto Interactable = Cast<IInteractable>(Actor))
		{
			if (auto Handler = Cast<IHandlerable>(Actor))
			{
				Params->Invoker = Character;
				if (Interactable->TryInteract(Params))
				{
					return true;
				}
				OnInteracted.Broadcast(Handler->GetId());
			}
		}
	}

	return false;
}
