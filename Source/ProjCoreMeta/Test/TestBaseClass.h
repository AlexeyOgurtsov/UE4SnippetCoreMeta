#pragma once

#include "MyTestInterface.h"
#include "MyTestObject.h"
#include "MyTestObjectTwo.h"
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

public:
	UFUNCTION(BlueprintPure)
	int32 GetBaseInt32() const { return BaseInt32; }

	UFUNCTION(BlueprintPure)
	int32 GetBaseFloat() const { return BaseFloat; }

	UFUNCTION(BlueprintPure)
	bool GetBaseBool() const { return BaseBool; }

	UFUNCTION(BlueprintPure)
	FTestStruct GetBaseTestStruct() const { return BaseTestStruct; }

public:
	UTestBaseClass();

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

	UFUNCTION(BlueprintPure, Category = BaseClass)
	TScriptInterface<IMyTestInterface> GetBaseTestInterfaceFieldToField() { return BaseTestInterfaceFieldToField; }

	UFUNCTION(BlueprintPure, Category = BaseClass)
	TScriptInterface<IMyTestInterface> GetBaseTestInterfaceField2() { return BaseTestInterfaceField2; }

	UFUNCTION(BlueprintPure, Category = BaseClass)
	TScriptInterface<IMyTestInterface> GetBaseTestInterfaceFieldNull() { return BaseTestInterfaceFieldNull; }

	UFUNCTION(BlueprintPure, Category = Objects)
	UMyTestObject* GetTestObj() const { return TestObj; }

	UFUNCTION(BlueprintPure, Category = Objects)
	UMyTestObject* GetTestObjToObj() const { return TestObjToObj; }

	UFUNCTION(BlueprintPure, Category = Objects)
	UMyTestObjectTwo* GetTestObj2() const { return TestObj2; }

	UFUNCTION(BlueprintPure, Category = Objects)
	UMyTestObject* GetTestObjNull() const { return TestObjNull; }	

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

	UPROPERTY()
	UMyTestObject* TestObj = nullptr;

	UPROPERTY()
	UMyTestObject* TestObjToObj = nullptr;

	UPROPERTY()
	UMyTestObjectTwo* TestObj2 = nullptr;

	UPROPERTY()
	UMyTestObject* TestObjNull = nullptr;

	UPROPERTY(SaveGame, Category = BaseProps, BlueprintReadOnly)
	TScriptInterface<IMyTestInterface> BaseTestInterfaceField;

	UPROPERTY(SaveGame, Category = BaseProps, BlueprintReadOnly)
	TScriptInterface<IMyTestInterface> BaseTestInterfaceField2;

	UPROPERTY(SaveGame, Category = BaseProps, BlueprintReadOnly)
	TScriptInterface<IMyTestInterface> BaseTestInterfaceFieldToField;

	UPROPERTY(SaveGame, Category = BaseProps, BlueprintReadOnly)
	TScriptInterface<IMyTestInterface> BaseTestInterfaceFieldNull;

	UPROPERTY()
	TArray<float> FloatArray;

	UPROPERTY()
	TArray<int> IntArray;

	UPROPERTY()
	TSet<float> FloatSet;

	UPROPERTY()
	TSet<int> IntSet;

	UPROPERTY()
	TMap<FString, float> FloatMap;

	UPROPERTY()
	TMap<FString, int> IntMap;
};