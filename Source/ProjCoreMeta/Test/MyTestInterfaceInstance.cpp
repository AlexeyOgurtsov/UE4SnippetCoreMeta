#include "MyTestInterfaceInstance.h"

FString UMyTestInterfaceInstance::TestNativeCall_Implementation(FName InName) const
{
	return FString(TEXT("TestValue"));
}