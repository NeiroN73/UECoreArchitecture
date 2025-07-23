// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#define BIND_FROM_VIEW_MODEL(Type, Name, BinderType) \
public: \
	UPROPERTY() \
	TObjectPtr<BinderType> __##Name##Binder; \
	UPROPERTY() \
	Type Name; \
	UFUNCTION() \
	Type Get##Name() const { return Name; } \
	UFUNCTION() \
	void Set##Name(Type NewValue) { \
		if (__##Name##Binder) \
		{ \
			Name = NewValue; \
			__##Name##Binder->OnBinderTriggered.Execute(Name); \
		} \
	} \
	UFUNCTION() \
	void __Set##Name##Binder(BinderType* NewBinder) \
	{ \
		__##Name##Binder = NewBinder;\
	} 


#define BIND_TO_VIEW_MODEL(ObjectName, BinderType) \
public: \
	UPROPERTY() \
	TObjectPtr<BinderType> __##ObjectName##Binder; \
	void Bind##ObjectName(FSimpleDelegate Delegate) \
	{ \
		__##ObjectName##Binder->OnBinderTriggered.BindLambda([this, Delegate]{ Delegate.ExecuteIfBound(); }); \
	}


#define BIND_TO_VIEW_MODEL_OneParam(ObjectName, BinderType, ValueType) \
public: \
	UPROPERTY() \
	TObjectPtr<BinderType> __##ObjectName##Binder; \
	void Bind##ObjectName(FSimpleDelegate Delegate) \
	{ \
		__##ObjectName##Binder->OnBinderTriggered.BindLambda(Delegate); \
	} 


#define BIND_FROM_VIEW(ObjectName, BinderType) \
auto* ObjectName##Binder = NewObject<BinderType>(); \
ViewModel->__##ObjectName##Binder = ObjectName##Binder; \
ObjectName##Binder->Bind(ObjectName); 


#define BIND_TO_VIEW(ObjectName, BinderType, ValueType) \
auto* ObjectName##Binder = NewObject<BinderType>(); \
ViewModel->__##ObjectName##Binder = ObjectName##Binder; \
ObjectName##Binder->OnBinderTriggered.BindLambda([this, ObjectName##Binder] (const ValueType& Value) \
{ \
ObjectName##Binder->Bind(ObjectName, Value); \
});

