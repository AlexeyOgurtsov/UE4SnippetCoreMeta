#pragma once

#include "Test/TestClass.h"
#include "Test/MyTestInterfaceInstance.h"
#include "FieldUtilsTestUtils.generated.h"

USTRUCT()
struct FTestPropHolder
{
	GENERATED_BODY()

	void Initialize(UObject* InOuter)
	{
		check(InOuter);
		Prop_Obj = NewObject<UTestClass>(InOuter);
	}

	const UClass* GetRootClass() const { return UTestClass::StaticClass(); }
	const UClass* GetInterfaceInstanceClass() const { UMyTestInterfaceInstance::StaticClass(); }

	UBoolProperty* GetProp_Bool() const 
	{
		static const FName PropName(TEXT("Prop_Bool"), FNAME_Find); 
		return CastChecked<UBoolProperty>(FTestPropHolder::StaticStruct()->FindPropertyByName(PropName)); 
	}

	UObjectProperty* GetProp_Obj() const
	{
		static const FName PropName(TEXT("Prop_Obj"), FNAME_Find); 
		return CastChecked<UObjectProperty>(FTestPropHolder::StaticStruct()->FindPropertyByName(PropName)); 
	}

	UStructProperty* GetProp_Struct() const
	{
		static const FName PropName(TEXT("BaseTestStruct"), FNAME_Find);
		return CastChecked<UStructProperty>(UTestClass::StaticClass()->FindPropertyByName(PropName)); 
	}

	UInterfaceProperty* GetProp_Interface() const
	{
		static const FName PropName(TEXT("BaseTestInterfaceField"), FNAME_Find);
		return CastChecked<UInterfaceProperty>(UTestClass::StaticClass()->FindPropertyByName(PropName)); 
	}

	bool GetBool() const { return Prop_Bool; }
	UObject* GetObj() const { return Prop_Obj; }

private:
	UPROPERTY() 
	bool Prop_Bool = false;

	UPROPERTY()
	UObject* Prop_Obj = nullptr;
};