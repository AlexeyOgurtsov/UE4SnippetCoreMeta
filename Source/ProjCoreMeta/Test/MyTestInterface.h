#pragma once

#include "UObject/Interface.h"
#include "MyTestInterface.generated.h"

UINTERFACE()
class UMyTestInterface : public UInterface
{
	GENERATED_BODY()	
};

class IMyTestInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = TestInterface)
	FString TestNativeCall(FName InName) const;
};