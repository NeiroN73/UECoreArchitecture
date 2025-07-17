#pragma once

#include "VeilOfFaith/Fragments/Base/Fragment.h"

#define FRAGMENTABLE_BODY() \
private: \
	UPROPERTY() \
	TObjectPtr<UFragmentsFactory> FragmentsFactory; \
	UPROPERTY() \
	TMap<TSubclassOf<UFragment>, TObjectPtr<UFragment>> Fragments; \
	UFUNCTION() \
	void InitializeFragmentable(UFragmentsFactory* InFragmentsFactory) \
	{ \
		FragmentsFactory = InFragmentsFactory;\
	} \
public: \
	template<typename TFragment = UFragment> \
	TFragment* GetFragment(TSubclassOf<TFragment> Class = TFragment::StaticClass()) \
	{ \
		if (auto Fragment = Fragments.Find(Class)) \
 		{ \
			return Cast<TFragment>(*Fragment); \
		} \
		return nullptr; \
	} \
	template<typename TFragment = UFragment> \
	bool HasFragment(TSubclassOf<TFragment> Class = TFragment::StaticClass()) \
	{ \
		if (auto Fragment = Fragments.Contains(Class)) \
		{ \
			return true; \
		} \
		return false; \
	} \
	template<typename TFragment = UFragment> \
	TFragment* TryAddFragment(TSubclassOf<TFragment> Class = TFragment::StaticClass()) \
	{ \
		if (!Fragments.Contains(Class) && FragmentsFactory) \
		{ \
	        auto Fragment = FragmentsFactory->Create<TFragment>(); \
			Fragments.Add(Class, Fragment); \
			return Fragment; \
		} \
		return nullptr; \
	} \
	template<typename TFragment = UFragment> \
	void RemoveFragment(TSubclassOf<TFragment> Class = TFragment::StaticClass()) \
	{ \
 		Fragments.Remove(Class); \
	}