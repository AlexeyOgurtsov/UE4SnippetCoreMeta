#include "TestClass.h"

UTestClass::UTestClass()
{
}

FString UTestClass::TestNativeCall_Implementation(FName InName) const
{
	return FString::Printf(TEXT("UTestClass::TestNativeCall: InName=\"%s\""), *InName.ToString());
}