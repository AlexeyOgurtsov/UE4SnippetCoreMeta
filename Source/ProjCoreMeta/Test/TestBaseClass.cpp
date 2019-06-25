#include "TestBaseClass.h"
#include "MyTestInterfaceInstance.h"

UTestBaseClass::UTestBaseClass()
{
	BaseTestInterfaceField.SetObject(NewObject<UMyTestInterfaceInstance>());
	BaseTestInterfaceFieldToField = BaseTestInterfaceField;
	BaseTestInterfaceField2.SetObject(NewObject<UMyTestInterfaceInstance>());

	TestObj = UMyTestObject::NewTestObject();
	TestObjToObj = TestObj;

	FloatArray.Add(1.1f); 	
	FloatArray.Add(2.2f);

	IntArray.Add(1);
	IntArray.Add(2);

	FloatSet.Add(1.1f);
	FloatSet.Add(2.2f);

	FloatMap.Add(FString(TEXT("1_1_f")), 1.1f);
	FloatMap.Add(FString(TEXT("2_2_f")), 2.2f);

	IntMap.Add(FString(TEXT("1i")), 1);
	IntMap.Add(FString(TEXT("2i")), 2);
}

FString UTestBaseClass::TestNativeCall_Implementation(FName InName) const
{
	return FString::Printf(TEXT("UTestBaseClass::TestNativeCall: InName=\"%s\""), *InName.ToString());
}