#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MetaTestLib.generated.h"

UCLASS()
class UMetaTestLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Meta=(WorldContext = WorldContextObject), Category = Test)
	static void QuickTest(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Meta=(WorldContext = WorldContextObject), Category = Test)
	static void IterateFieldsTest(UObject* WorldContextObject);
};