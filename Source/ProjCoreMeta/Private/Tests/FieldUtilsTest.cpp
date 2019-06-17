#include "Misc/AutomationTest.h"
#include "Proto/ProtoFieldUtils.h"
#include "Test/TestClass.h"
#include "Util/Core/LogUtilLib.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST( FProptFieldUtilsTest_Quick, "MyProtoTests.FieldUtils.Quick", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter )

namespace
{
	UField* FindFieldWithName(const TArray<UField*>& InField, FName InName)
	{
		M_NOT_IMPL_RET(nullptr);
	}
} // anonymous

/**
* Checks that field with the given name is included.
*
* @param InFields: TArray<UField*>
* @param InName:  name to search (String literal)
*/
#define M_TEST_FIELD_EXISTS(InFields, InName)\
{\
	const UField* const F = FindFieldWithName(InFields, TEXT(InName));\
	TestNotNull(TEXT("Field with is expected to be included"), F);\
}

bool FProptFieldUtilsTest_Quick::RunTest(const FString& Parameters)
{
	const UClass* const RootClass = UTestClass::StaticClass();
	TArray<UField*> const Fields = FProtoFieldUtils::GetFieldsRecursive(RootClass);
	M_TEST_FIELD_EXISTS(Fields, "bBoolProp");

	M_NOT_IMPL();
	return true;
}