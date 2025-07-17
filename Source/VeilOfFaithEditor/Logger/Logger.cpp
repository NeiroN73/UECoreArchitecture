// Copyright Floruit, Inc. All Rights Reserved.


#include "Logger.h"

#include "IMessageLogListing.h"
#include "MessageLogModule.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

class FMessageLogModule;

void FLogger::ShowMessage(const FString& Message)
{
	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
    
	if (!MessageLogModule.IsRegisteredLogListing("Errors"))
	{
		FMessageLogInitializationOptions InitOptions;
		InitOptions.bShowInLogWindow = true;
		MessageLogModule.RegisterLogListing("Errors", FText::FromString("Errors"), InitOptions);
	}
    
	TSharedPtr<IMessageLogListing> LogListing = MessageLogModule.GetLogListing("Errors");
    
	LogListing->AddMessage(
		FTokenizedMessage::Create(
			EMessageSeverity::Error,
			FText::FromString(Message)
		)
	);
    
	MessageLogModule.OpenMessageLog("Errors");
}

void FLogger::ShowNotification(const FString& Message)
{
	FNotificationInfo Info(FText::FromString(Message));
	Info.ExpireDuration = 5;
	Info.bUseLargeFont = false;
	Info.bUseThrobber = true;
	Info.bFireAndForget = true;
	Info.bAllowThrottleWhenFrameRateIsLow = true;
    
	FSlateNotificationManager::Get().AddNotification(Info);
}

