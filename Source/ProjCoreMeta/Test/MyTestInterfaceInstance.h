#pragma once

#include "MyTestInterface.h"
#include "MyTestInterfaceInstance.generated.h"

UCLASS()
class UMyTestInterfaceInstance 
: public UObject
, public IMyTestInterface
{
	GENERATED_BODY()

public:
	virtual FString TestNativeCall_Implementation(FName InName) const override;

private:
	UPROPERTY()
	int i;

	UPROPERTY()
	float flt;
};