// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define REACTIVE_PROPERTY(Type, Name, Getter, Setter) \
private: \
UPROPERTY() \
Type Name; \
Getter \
UFUNCTION() \
Type Get##Name() const { return Name; } \
Setter \
UFUNCTION() \
void Set##Name(Type NewValue) { \
if (Name != NewValue) { \
Name = NewValue; \
On##Name##Changed.Execute(Name); \
} \
} \
public: \
FOn##Name##Changed On##Name##Changed;


#define REACTIVE_ARRAY_PROPERTY(Type, Name, Getter, Setter) \
private: \
UPROPERTY() \
TArray<Type> Name; \
Getter \
UFUNCTION() \
TArray<Type> Get##Name() const { return Name; } \
Setter \
UFUNCTION() \
void Set##Name(TArray<Type> NewValue) { \
if (Name != NewValue) { \
Name = NewValue; \
On##Name##Changed.Execute(Name); \
} \
} \
UFUNCTION() \
void Add##Name(Type Item) const { \
Name.Add(Item); \
On##Name##Changed.Execute(Name); \
} \
UFUNCTION() \
void Remove##Name(Type Item) const { \
Name.Remove(Item); \
On##Name##Changed.Execute(Name); \
} \
public: \
FOn##Name##Changed On##Name##Changed;


#define PROPERTY(Type, Name, Getter, Setter) \
private: \
UPROPERTY() \
Type Name; \
Getter \
UFUNCTION() \
Type Get##Name() const { return Name; } \
Setter \
UFUNCTION() \
void Set##Name(Type NewValue) { Name = NewValue; }