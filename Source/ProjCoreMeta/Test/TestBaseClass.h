#pragma once

#include "MyTestInterface.h"
#include "TestBaseClass.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FTestStruct
{
	GENERATED_BODY()

	UPROPERTY()	
	float flt;

	UPROPERTY()	
	float i;

	UPROPERTY()	
	bool bValue;
};

UCLASS()
class UTestBaseClass 
: public UObject
, public IMyTestInterface
{
	GENERATED_BODY()


	UFUNCTION(BlueprintPure)
	int32 GetBaseInt32() const { return BaseInt32; }

	UFUNCTION(BlueprintPure)
	int32 GetBaseFloat() const { return BaseFloat; }

	UFUNCTION(BlueprintPure)
	bool GetBaseBool() const { return BaseBool; }

	UFUNCTION(BlueprintPure)
	FTestStruct GetBaseTestStruct() const { return BaseTestStruct; }

public:
	virtual FString TestNativeCall_Implementation(FName InName) const override;

	UFUNCTION(BlueprintPure, Category = BaseClass)
	const FString& GetBaseString() const { return BaseString; }

	UFUNCTION(BlueprintPure, Category = BaseClass)
	const FName& GetBaseName() const { return BaseName; }

	UFUNCTION(BlueprintPure, Category = BaseClass)
	const FText& GetBaseText() const { return BaseText; }

	UFUNCTION(BlueprintPure, Category = BaseClass)
	UObject* GetBaseObjectField() const { return BaseObjectField; }

	UFUNCTION(BlueprintPure, Category = BaseClass)
	AActor* GetBaseActorField() const { return BaseActorField; }

	UFUNCTION(BlueprintPure, Category = BaseClass)
	TScriptInterface<IMyTestInterface> GetBaseTestInterfaceField() { return BaseTestInterfaceField; }

private:
	UPROPERTY(SaveGame)
	int32 BaseInt32 = 0;

	UPROPERTY(SaveGame)
	int32 BaseFloat = 0;

	UPROPERTY(SaveGame)
	bool BaseBool;

	UPROPERTY(SaveGame)
	FString BaseString;

	UPROPERTY(SaveGame)
	FName BaseName;

	UPROPERTY(SaveGame)
	FText BaseText;

	UPROPERTY(SaveGame)
	FTestStruct BaseTestStruct;

protected:
	UPROPERTY(SaveGame, BlueprintReadWrite)
	UObject* BaseObjectField = nullptr;

	UPROPERTY(SaveGame, Category = BaseProps, BlueprintReadOnly)
	AActor* BaseActorField = nullptr;

	UPROPERTY(SaveGame, Category = BaseProps, BlueprintReadOnly)
	TScriptInterface<IMyTestInterface> BaseTestInterfaceField;
};