#pragma once

#include "TestBaseClass.h"
#include "TestClass.generated.h"

UCLASS()
class UTestClass : public UTestBaseClass
{
	GENERATED_BODY()

public:
	virtual FString TestNativeCall_Implementation(FName InName) const override;

	UFUNCTION(BlueprintPure, Category = TestClass)
	bool GetBoolProp() const { return bBoolProp; }

	UFUNCTION(BlueprintPure, Category = TestClass)
	bool GetBoolProp2() const { return bBoolProp2; }

	UPROPERTY()
	bool bBoolProp;

	UPROPERTY()
	bool bBoolProp2;
};