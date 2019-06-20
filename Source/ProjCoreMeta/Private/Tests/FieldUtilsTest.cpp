#include "Misc/AutomationTest.h"
#include "Proto/ProtoFieldUtils.h"
#include "Test/TestClass.h"
#include "Util/Core/LogUtilLib.h"
#include "FieldUtilsArrayTestBase.h"

namespace FieldUtilsTest
{
	class FTestBase_GetFieldsRecursive : public FFieldUtilsArrayTestBase
	{
	public:
		FTestBase_GetFieldsRecursive(const FString& InName, bool const bComplexTask)
		: FFieldUtilsArrayTestBase(InName, bComplexTask)
		{
		} 

		void CheckFieldsIncluded(const UStruct* InStruct)
		{	
			M_LOGFUNC_MSG(TEXT("Checking that fields of struct \"%s\" included"), *ULogUtilLib::GetNameAndClassSafe(InStruct));
			check(InStruct);
			int32 FieldIndex = 0;
			for(UField* ExpectedField : TFieldRange<UField>(InStruct))
			{
				if(Cast<const UFunction>(ExpectedField))			
				{
					M_LOGFUNC_MSG(TEXT("Checking expected field N %d: {%s}"), FieldIndex, *FProtoFieldUtils::GetFieldString(ExpectedField));									
					CheckField(ExpectedField->GetFName());
				}
				else
				{
					M_LOG(TEXT("Skipping expected field {%s}: it's UFunction"), *FProtoFieldUtils::GetFieldString(ExpectedField));
				}
				FieldIndex++;
			}
			M_LOG(TEXT("%d expected fields checked"), FieldIndex);
		}
	};
} // FieldUtilsTest

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_GetFieldsRecursive_Quick, FieldUtilsTest::FTestBase_GetFieldsRecursive, "MyProtoTests.FieldUtils.Quick", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_GetFieldsRecursive_Quick2, FieldUtilsTest::FTestBase_GetFieldsRecursive, "MyProtoTests.FieldUtils.Quick2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );

bool FPropertyFieldUtils_GetFieldsRecursive_Quick::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	const UClass* const RootClass = UTestClass::StaticClass();
	const UStruct* const TestStruct = FTestStruct::StaticStruct();
	TArray<UField*> const ResultFieldSet = FProtoFieldUtils::GetFieldsRecursive(RootClass).Array();
	Fields = ResultFieldSet;

	CheckFieldsIncluded(RootClass);
	CheckFieldsIncluded(TestStruct);
	
	return true;
}

bool FPropertyFieldUtils_GetFieldsRecursive_Quick2::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	//const UClass* const RootClass = UTestClass::StaticClass();
	//TArray<UField*> const ResultFieldSet = FProtoFieldUtils::GetFieldsRecursive(RootClass).Array();
	//Fields = ResultFieldSet;

	return true;
}