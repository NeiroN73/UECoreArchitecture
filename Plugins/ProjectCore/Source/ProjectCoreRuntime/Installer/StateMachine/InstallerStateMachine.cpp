// Copyright Floruit, Inc. All Rights Reserved.


#include "InstallerStateMachine.h"

#include "States/LoadConfigsState.h"

void UInstallerStateMachine::Initialize(TArray<UInstallerState*> NewStates)
{
	for (auto State : NewStates)
	{
		States.Enqueue(State);
	}

	NextState();
}

void UInstallerStateMachine::Tick(float DeltaSeconds)
{
	CurrentState->Tick(DeltaSeconds);
}

void UInstallerStateMachine::NextState()
{
	if (States.Dequeue(CurrentState))
	{
		CurrentState->StateMachine = this;
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			*FString::Printf(TEXT("Enter in %s"), *CurrentState->GetClass()->GetName()));
		
		CurrentState->Enter();
	}
}
