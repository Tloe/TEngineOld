#include <TEInputProperties.h>

namespace
{
	enum
	{
		Property0 = 0,
		Property1,
		Property2,
		Property3,
		Property4,
		Property5,
		Property6,
		Property7,
		Property8
	};
}


TE::Input::TransformPositionPropertyValues::TransformPositionPropertyValues( const Engine::Property& property )
	:
	inputGroup(property[Property0].GetU32()),
	inputString(property[Property1].GetString()),
	inputType(property[Property2].GetU32()),
	inputStateFlags(property[Property3].GetU32()),
	objectHash(property[Property4].GetU32()),
	actionType(property[Property5].GetU32()),
	x(property[Property6].GetF32()),
	y(property[Property7].GetF32()),
	z(property[Property8].GetF32())
{

}


TE::Input::TransformPositionPropertyValues::TransformPositionPropertyValues( Enum inputGroup, const std::string& inputString, Enum inputType, Bitmask inputStateFlags, const std::string& objectString, Enum actionType, F32 x, F32 y, F32 z )
	:
	inputGroup(inputGroup),
	inputString(inputString),
	inputType(inputType),
	inputStateFlags(inputStateFlags),
	objectHash(HashGenerator()(objectString)),
	actionType(actionType),
	x(x),
	y(y),
	z(z)
{

}

TE::Input::TransformPositionPropertyValues::TransformPositionPropertyValues( Enum inputGroup, const std::string& inputString, Enum inputType, Bitmask inputStateFlags, Hash objectHash, Enum actionType, F32 x, F32 y, F32 z )
	:
	inputGroup(inputGroup),
	inputString(inputString),
	inputType(inputType),
	inputStateFlags(inputStateFlags),
	objectHash(objectHash),
	actionType(actionType),
	x(x),
	y(y),
	z(z)
{

}

TE::Engine::Property TE::Input::TransformPositionPropertyValues::GetProperty()
{
	Engine::Property property(9, PropertyType::InputAction::TransformPosition);

	property[Property0].SetU32(inputGroup);
	property[Property1].SetString(inputString);
	property[Property2].SetU32(inputType);
	property[Property3].SetU32(inputStateFlags);
	property[Property4].SetU32(objectHash);
	property[Property5].SetU32(actionType);
	property[Property6].SetF32(x);
	property[Property7].SetF32(y);
	property[Property8].SetF32(z);

	return property;
}
