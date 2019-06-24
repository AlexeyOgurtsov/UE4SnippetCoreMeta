#pragma once

#include "MyTestObjectTwo.generated.h"

UCLASS()
class UMyTestObjectTwo : public UObject
{
	GENERATED_BODY()

public:
	static UMyTestObjectTwo* NewTestObject()
	{
		return NewObject<UMyTestObjectTwo>(Cast<UObject>(GetTransientPackage()));
	}

private:
	float FLT;
	float FLT2;
};
