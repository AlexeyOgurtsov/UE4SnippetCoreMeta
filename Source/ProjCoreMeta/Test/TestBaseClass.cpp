#include "TestBaseClass.h"
#include "MyTestInterfaceInstance.h"

UTestBaseClass::UTestBaseClass()
{
	BaseTestInterfaceField.SetObject(NewObject<UMyTestInterfaceInstance>());
}

FString UTestBaseClass::TestNativeCall_Implementation(FName InName) const
{
	return FString::Printf(TEXT("UTestBaseClass::TestNativeCall: InName=\"%s\""), *InName.ToString());
}