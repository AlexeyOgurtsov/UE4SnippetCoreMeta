#include "TestBaseClass.h"
#include "MyTestInterfaceInstance.h"

UTestBaseClass::UTestBaseClass()
{
	BaseTestInterfaceField.SetObject(NewObject<UMyTestInterfaceInstance>());
	BaseTestInterfaceFieldToField = BaseTestInterfaceField;
	BaseTestInterfaceField2.SetObject(NewObject<UMyTestInterfaceInstance>());

	TestObj = UMyTestObject::NewTestObject();
	TestObjToObj = TestObj;
}

FString UTestBaseClass::TestNativeCall_Implementation(FName InName) const
{
	return FString::Printf(TEXT("UTestBaseClass::TestNativeCall: InName=\"%s\""), *InName.ToString());
}