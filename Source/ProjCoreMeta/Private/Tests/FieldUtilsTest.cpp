#include "Misc/AutomationTest.h"
#include "Proto/ProtoFieldUtils.h"
#include "Test/TestClass.h"
#include "Util/Core/LogUtilLib.h"
#include "FieldUtilsArrayTestBase.h"
#include "FieldUtilsTestUtils.h"


namespace FieldUtilsTest
{
	class FTestBase_GetFieldsRecursive : public FFieldUtilsArrayTestBase
	{
	public:
		FTestBase_GetFieldsRecursive(const FString& InName, bool const bComplexTask)
		: FFieldUtilsArrayTestBase(InName, bComplexTask)
		{
		}
	};

	class FTestBase_TraverseFields : public FFieldUtilsArrayTestBase
	{
	public:
		FTestBase_TraverseFields(const FString& InName, bool const bComplexTask)
		: FFieldUtilsArrayTestBase(InName, bComplexTask)
		{
			PropHolder.Initialize(Cast<UObject>(GetTransientPackage()));
		} 

	protected:
		// ~Checks Begin
		/**
		* Traverse the given property field and check it's included.
		*/
		void TraverseCheckSingle(UField* InField, void* InContainer)
		{
			check(InField);
			TraverseTopFields(InField, InContainer);
			CheckField(InField->GetFName());
		}

		void TraverseCheckRootStruct(UField* InField, void* InContainer, EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite)
		{
			check(InField);
			check(InContainer);

			TraverseTopFields(InField, InContainer, InFieldIterationFlags);
			CheckFieldsIncluded(FProtoFieldUtils::GetStructFromField(InField, InContainer));
		}
		// ~Checks End

		// ~Traverse helpers Begin
		void TraverseFieldsRecursive
		(
			UField* InRootField, void* InContainer,
			EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite
		)
		{
			TraverseFields(InRootField, InContainer, FProtoFieldUtils::TraverseFunc_TraverseSubtree, InFieldIterationFlags);
		}

		void TraverseTopFields
		(
			UField* InRootField, void* InContainer,
			EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite
		)
		{
			TraverseFields(InRootField, InContainer, FProtoFieldUtils::TraverseFunc_SkipSubtree, InFieldIterationFlags);
		}

		template<typename FuncType>
		void TraverseFields
		(
			UField* InRootField, void* InContainer, FuncType Func,
			EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite	
		)
		{
			TSet<UField*> const FieldSet = FProtoFieldUtils::TraverseFields(InRootField, InContainer, Func, ELogFlags::LogEverSuccess, InFieldIterationFlags);
			AssignFields(FieldSet);
		}
		// ~Traverse helpers End

		// ~Testee stuff Begin
		FTestPropHolder& GetPropHolder() { return PropHolder; }
		const UClass* GetRootClass() const { return PropHolder.GetRootClass(); }
		UBoolProperty* GetProp_Bool() const { return PropHolder.GetProp_Bool(); }
		UStructProperty* GetProp_Struct() const { return PropHolder.GetProp_Struct(); }
		UObjectProperty* GetProp_Obj() const { return PropHolder.GetProp_Obj(); }
		UObject* GetObj() const { return PropHolder.GetObj(); }
		// ~Testee stuff End


	private:
		// ~Testee stuff Begin
		FTestPropHolder PropHolder;
		// ~Testee stuff End
	};
} // FieldUtilsTest

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_GetFieldsRecursive_Quick, FieldUtilsTest::FTestBase_GetFieldsRecursive, "MyProtoTests.FieldUtils.Quick", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_GetFieldsRecursive_Quick2, FieldUtilsTest::FTestBase_GetFieldsRecursive, "MyProtoTests.FieldUtils.Quick2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_TraverseFields_OnlyRootProperty, FieldUtilsTest::FTestBase_TraverseFields, "MyProto.FieldUtils.TraverseFields.OnlyRootProperty", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_TraverseFields_RootStructProperty, FieldUtilsTest::FTestBase_TraverseFields, "MyProto.FieldUtils.TraverseFields.RootStructProperty", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_TraverseFields_ClassProperty, FieldUtilsTest::FTestBase_TraverseFields, "MyProto.FieldUtils.TraverseFields.ClassProperty", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );

bool FPropertyFieldUtils_TraverseFields_OnlyRootProperty::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	TraverseCheckSingle(GetProp_Bool(), &GetPropHolder());
	
	return true;
}

bool FPropertyFieldUtils_TraverseFields_RootStructProperty::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	TraverseCheckRootStruct(GetProp_Struct(), GetObj());
	TraverseCheckRootStruct(GetProp_Obj(), GetObj());
	
	return true;
}

bool FPropertyFieldUtils_TraverseFields_ClassProperty::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	TraverseFieldsRecursive
	(
		GetProp_Obj(), GetObj(), EFieldIterationFlags::IncludeComposite
	);

	CheckFieldsIncluded(GetProp_Obj()->GetOwnerClass());
	CheckFieldsIncluded(GetProp_Struct()->GetOwnerStruct());
	CheckFieldsIncluded(UObject::StaticClass());
	CheckFieldsIncluded(AActor::StaticClass());
	CheckFieldsIncluded(UMyTestInterfaceInstance::StaticClass());

	return true;
}

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