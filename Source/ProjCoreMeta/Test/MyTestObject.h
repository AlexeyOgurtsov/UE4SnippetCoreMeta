#pragma once

#include "MyTestObject.generated.h"

UCLASS()
class UMyTestObject : public UObject
{
	GENERATED_BODY()

public:
	static UMyTestObject* NewTestObject()
	{
		return NewObject<UMyTestObject>(Cast<UObject>(GetTransientPackage()));
	}

private:
	float FLT;
	float FLT2;
};
