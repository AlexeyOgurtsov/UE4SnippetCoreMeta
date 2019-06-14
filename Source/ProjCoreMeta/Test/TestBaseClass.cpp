#include "TestBaseClass.h"

FString UTestBaseClass::TestNativeCall_Implementation(FName InName) const
{
	return FString::Printf(TEXT("UTestBaseClass::TestNativeCall: InName=\"%s\""), *InName.ToString());
}