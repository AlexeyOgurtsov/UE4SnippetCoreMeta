#include "Misc/AutomationTest.h"
#include "Proto/ProtoFieldUtils.h"
#include "Util/Core/LogUtilLib.h"
#include "Test/TestClass.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST( FProtoFieldUtils_Log_PropertyValues, "MyProtoTests.FieldUtils.Log.PropertyValues", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );

bool FProtoFieldUtils_Log_PropertyValues::RunTest(const FString& Parameters)
{
	const UObject* const Obj = NewObject<UTestClass>(Cast<UObject>(GetTransientPackage()));
	FProtoFieldUtils::LogStructPropertyValues(Obj->GetClass(), Obj);
	return true;
}
