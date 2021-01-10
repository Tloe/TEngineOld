#include "TEInput.h"

#include <unordered_map>

namespace
{
	const std::string inputTypeStrs[] =
	{
		"Key0",
		"Key1",
		"Key2",
		"Key3",
		"Key4",
		"Key5",
		"Key6",
		"Key7",
		"Key8",
		"Key9",
		"KeyA",
		"KeyB",
		"KeyC",
		"KeyD",
		"KeyE",
		"KeyF",
		"KeyG",
		"KeyH",
		"KeyI",
		"KeyJ",
		"KeyK",
		"KeyL",
		"KeyM",
		"KeyN",
		"KeyO",
		"KeyP",
		"KeyQ",
		"KeyR",
		"KeyS",
		"KeyT",
		"KeyU",
		"KeyV",
		"KeyW",
		"KeyX",
		"KeyY",
		"KeyZ",
		"KeyF1",
		"KeyF2",
		"KeyF3",
		"KeyF4",
		"KeyF5",
		"KeyF6",
		"KeyF7",
		"KeyF8",
		"KeyF9",
		"KeyF10",
		"KeyF11",
		"KeyF12",
		"KeyControlLeft",
		"KeyControlRight",
		"KeyAltLeft",
		"KeyAltRight",
		"KeyShiftLeft",
		"KeyShiftRight",
		"KeySpace",
		"KeyEnter",
		"KeyEscape",
		"KeyBackspace",
		"KeyTab",
		"KeySeperator",
		"KeyCapslock",
		"KeyUp",
		"KeyDown",
		"KeyLeft",
		"KeyRight",
		"KeyPgUp",
		"KeyPgDown",
		"KeyHome",
		"KeyEnd",
		"KeyNum0",
		"KeyNum1",
		"KeyNum2",
		"KeyNum3",
		"KeyNum4",
		"KeyNum5",
		"KeyNum6",
		"KeyNum7",
		"KeyNum8",
		"KeyNum9",
		"KeyCollon",
		"KeyPlus",
		"KeyComma",
		"KeyMinus",
		"KeyPeriod",
		"KeySlashQuest",
		"KeyTilde",
		"MouseLButton",
		"MouseMButton",
		"MouseRButton",
		"MouseLClick",
		"MouseMClick",
		"MouseRClick",
		"MouseLDoubleClick",
		"MouseMDoubleClick",
		"MouseRDoubleClick",
		"Ascii"
	};

	void FillMapInputTypeEnumMap(std::unordered_map<std::string, TE::InputMapping::InputType>& inputTypeEnums)
	{
		inputTypeEnums.insert(std::make_pair("Key0", TE::InputMapping::InputType::Key0));
		inputTypeEnums.insert(std::make_pair("Key1", TE::InputMapping::InputType::Key1));
		inputTypeEnums.insert(std::make_pair("Key2", TE::InputMapping::InputType::Key2));
		inputTypeEnums.insert(std::make_pair("Key3", TE::InputMapping::InputType::Key3));
		inputTypeEnums.insert(std::make_pair("Key4", TE::InputMapping::InputType::Key4));
		inputTypeEnums.insert(std::make_pair("Key5", TE::InputMapping::InputType::Key5));
		inputTypeEnums.insert(std::make_pair("Key6", TE::InputMapping::InputType::Key6));
		inputTypeEnums.insert(std::make_pair("Key7", TE::InputMapping::InputType::Key7));
		inputTypeEnums.insert(std::make_pair("Key8", TE::InputMapping::InputType::Key8));
		inputTypeEnums.insert(std::make_pair("Key9", TE::InputMapping::InputType::Key9));
		inputTypeEnums.insert(std::make_pair("KeyA", TE::InputMapping::InputType::KeyA));
		inputTypeEnums.insert(std::make_pair("KeyB", TE::InputMapping::InputType::KeyB));
		inputTypeEnums.insert(std::make_pair("KeyC", TE::InputMapping::InputType::KeyC));
		inputTypeEnums.insert(std::make_pair("KeyD", TE::InputMapping::InputType::KeyD));
		inputTypeEnums.insert(std::make_pair("KeyE", TE::InputMapping::InputType::KeyE));
		inputTypeEnums.insert(std::make_pair("KeyF", TE::InputMapping::InputType::KeyF));
		inputTypeEnums.insert(std::make_pair("KeyG", TE::InputMapping::InputType::KeyG));
		inputTypeEnums.insert(std::make_pair("KeyH", TE::InputMapping::InputType::KeyH));
		inputTypeEnums.insert(std::make_pair("KeyI", TE::InputMapping::InputType::KeyI));
		inputTypeEnums.insert(std::make_pair("KeyJ", TE::InputMapping::InputType::KeyJ));
		inputTypeEnums.insert(std::make_pair("KeyK", TE::InputMapping::InputType::KeyK));
		inputTypeEnums.insert(std::make_pair("KeyL", TE::InputMapping::InputType::KeyL));
		inputTypeEnums.insert(std::make_pair("KeyM", TE::InputMapping::InputType::KeyM));
		inputTypeEnums.insert(std::make_pair("KeyN", TE::InputMapping::InputType::KeyN));
		inputTypeEnums.insert(std::make_pair("KeyO", TE::InputMapping::InputType::KeyO));
		inputTypeEnums.insert(std::make_pair("KeyP", TE::InputMapping::InputType::KeyP));
		inputTypeEnums.insert(std::make_pair("KeyQ", TE::InputMapping::InputType::KeyQ));
		inputTypeEnums.insert(std::make_pair("KeyR", TE::InputMapping::InputType::KeyR));
		inputTypeEnums.insert(std::make_pair("KeyS", TE::InputMapping::InputType::KeyS));
		inputTypeEnums.insert(std::make_pair("KeyT", TE::InputMapping::InputType::KeyT));
		inputTypeEnums.insert(std::make_pair("KeyU", TE::InputMapping::InputType::KeyU));
		inputTypeEnums.insert(std::make_pair("KeyV", TE::InputMapping::InputType::KeyV));
		inputTypeEnums.insert(std::make_pair("KeyW", TE::InputMapping::InputType::KeyW));
		inputTypeEnums.insert(std::make_pair("KeyX", TE::InputMapping::InputType::KeyX));
		inputTypeEnums.insert(std::make_pair("KeyY", TE::InputMapping::InputType::KeyY));
		inputTypeEnums.insert(std::make_pair("KeyZ", TE::InputMapping::InputType::KeyZ));
		inputTypeEnums.insert(std::make_pair("KeyF1", TE::InputMapping::InputType::KeyF1));
		inputTypeEnums.insert(std::make_pair("KeyF2", TE::InputMapping::InputType::KeyF2));
		inputTypeEnums.insert(std::make_pair("KeyF3", TE::InputMapping::InputType::KeyF3));
		inputTypeEnums.insert(std::make_pair("KeyF4", TE::InputMapping::InputType::KeyF4));
		inputTypeEnums.insert(std::make_pair("KeyF5", TE::InputMapping::InputType::KeyF5));
		inputTypeEnums.insert(std::make_pair("KeyF6", TE::InputMapping::InputType::KeyF6));
		inputTypeEnums.insert(std::make_pair("KeyF7", TE::InputMapping::InputType::KeyF7));
		inputTypeEnums.insert(std::make_pair("KeyF8", TE::InputMapping::InputType::KeyF8));
		inputTypeEnums.insert(std::make_pair("KeyF9", TE::InputMapping::InputType::KeyF9));
		inputTypeEnums.insert(std::make_pair("KeyF10", TE::InputMapping::InputType::KeyF10));
		inputTypeEnums.insert(std::make_pair("KeyF11", TE::InputMapping::InputType::KeyF11));
		inputTypeEnums.insert(std::make_pair("KeyF12", TE::InputMapping::InputType::KeyF12));
		inputTypeEnums.insert(std::make_pair("KeyControlLeft", TE::InputMapping::InputType::KeyControlLeft));
		inputTypeEnums.insert(std::make_pair("KeyControlRight", TE::InputMapping::InputType::KeyControlRight));
		inputTypeEnums.insert(std::make_pair("KeyAltLeft", TE::InputMapping::InputType::KeyAltLeft));
		inputTypeEnums.insert(std::make_pair("KeyAltRight", TE::InputMapping::InputType::KeyAltRight));
		inputTypeEnums.insert(std::make_pair("KeyShiftLeft", TE::InputMapping::InputType::KeyShiftLeft));
		inputTypeEnums.insert(std::make_pair("KeyShiftRight", TE::InputMapping::InputType::KeyShiftRight));
		inputTypeEnums.insert(std::make_pair("KeySpace", TE::InputMapping::InputType::KeySpace));
		inputTypeEnums.insert(std::make_pair("KeyEnter", TE::InputMapping::InputType::KeyEnter));
		inputTypeEnums.insert(std::make_pair("KeyEscape", TE::InputMapping::InputType::KeyEscape));
		inputTypeEnums.insert(std::make_pair("KeyBackspace", TE::InputMapping::InputType::KeyBackspace));
		inputTypeEnums.insert(std::make_pair("KeyTab", TE::InputMapping::InputType::KeyTab));
        //inputTypeEnums.insert(std::make_pair("KeySeperator", TE::InputMapping::InputType::KeySeperator));
		inputTypeEnums.insert(std::make_pair("KeyCapslock", TE::InputMapping::InputType::KeyCapslock));
		inputTypeEnums.insert(std::make_pair("KeyUp", TE::InputMapping::InputType::KeyUp));
		inputTypeEnums.insert(std::make_pair("KeyDown", TE::InputMapping::InputType::KeyDown));
		inputTypeEnums.insert(std::make_pair("KeyLeft", TE::InputMapping::InputType::KeyLeft));
		inputTypeEnums.insert(std::make_pair("KeyRight", TE::InputMapping::InputType::KeyRight));
		inputTypeEnums.insert(std::make_pair("KeyPgUp", TE::InputMapping::InputType::KeyPgUp));
		inputTypeEnums.insert(std::make_pair("KeyPgDown", TE::InputMapping::InputType::KeyPgDown));
		inputTypeEnums.insert(std::make_pair("KeyHome", TE::InputMapping::InputType::KeyHome));
		inputTypeEnums.insert(std::make_pair("KeyEnd", TE::InputMapping::InputType::KeyEnd));
		inputTypeEnums.insert(std::make_pair("KeyNum0", TE::InputMapping::InputType::KeyNum0));
		inputTypeEnums.insert(std::make_pair("KeyNum1", TE::InputMapping::InputType::KeyNum1));
		inputTypeEnums.insert(std::make_pair("KeyNum2", TE::InputMapping::InputType::KeyNum2));
		inputTypeEnums.insert(std::make_pair("KeyNum3", TE::InputMapping::InputType::KeyNum3));
		inputTypeEnums.insert(std::make_pair("KeyNum4", TE::InputMapping::InputType::KeyNum4));
		inputTypeEnums.insert(std::make_pair("KeyNum5", TE::InputMapping::InputType::KeyNum5));
		inputTypeEnums.insert(std::make_pair("KeyNum6", TE::InputMapping::InputType::KeyNum6));
		inputTypeEnums.insert(std::make_pair("KeyNum7", TE::InputMapping::InputType::KeyNum7));
		inputTypeEnums.insert(std::make_pair("KeyNum8", TE::InputMapping::InputType::KeyNum8));
		inputTypeEnums.insert(std::make_pair("KeyNum9", TE::InputMapping::InputType::KeyNum9));
		inputTypeEnums.insert(std::make_pair("KeyCollon", TE::InputMapping::InputType::KeyCollon));
		inputTypeEnums.insert(std::make_pair("KeyPlus", TE::InputMapping::InputType::KeyPlus));
		inputTypeEnums.insert(std::make_pair("KeyComma", TE::InputMapping::InputType::KeyComma));
		inputTypeEnums.insert(std::make_pair("KeyMinus", TE::InputMapping::InputType::KeyMinus));
		inputTypeEnums.insert(std::make_pair("KeyPeriod", TE::InputMapping::InputType::KeyPeriod));
		inputTypeEnums.insert(std::make_pair("KeySlashQuest", TE::InputMapping::InputType::KeySlashQuest));
		inputTypeEnums.insert(std::make_pair("KeyTilde", TE::InputMapping::InputType::KeyTilde));
        /*inputTypeEnums.insert(std::make_pair("MouseLButton", TE::InputMapping::InputType::MouseLButton));
		inputTypeEnums.insert(std::make_pair("MouseMButton", TE::InputMapping::InputType::MouseMButton));
		inputTypeEnums.insert(std::make_pair("MouseRButton", TE::InputMapping::InputType::MouseRButton));
		inputTypeEnums.insert(std::make_pair("MouseLClick", TE::InputMapping::InputType::MouseLClick));
		inputTypeEnums.insert(std::make_pair("MouseMClick", TE::InputMapping::InputType::MouseMClick));
		inputTypeEnums.insert(std::make_pair("MouseRClick", TE::InputMapping::InputType::MouseRClick));
		inputTypeEnums.insert(std::make_pair("MouseLDoubleClick", TE::InputMapping::InputType::MouseLDoubleClick));
		inputTypeEnums.insert(std::make_pair("MouseMDoubleClick", TE::InputMapping::InputType::MouseMDoubleClick));
		inputTypeEnums.insert(std::make_pair("MouseRDoubleClick", TE::InputMapping::InputType::MouseRDoubleClick));
        inputTypeEnums.insert(std::make_pair("Ascii", TE::InputMapping::InputType::Ascii));*/
	}
}


TE::InputMapping::RangeInput TE::InputMapping::RangeInputFromString( const std::string& str )
{
	if (str == "MouseDeltaX") return RangeInput::MouseDeltaX;
	if (str == "MouseDeltaY") return RangeInput::MouseDeltaY;
	if (str == "MousePosX")	return RangeInput::MouseX;
	if (str == "MousePosY")	return RangeInput::MouseY;

	//LOG fatal
	exit(-1);

	return RangeInput::MouseDeltaX;
}

std::string TE::InputMapping::ToString( TE::InputMapping::InputType inputType )
{
	return ::inputTypeStrs[static_cast<U32>(inputType)];
}

TE::InputMapping::InputType TE::InputMapping::FromString( const std::string& inputType )
{
	static std::unordered_map<std::string, TE::InputMapping::InputType> inputTypeEnums;

	if (inputTypeEnums.empty())
		::FillMapInputTypeEnumMap(inputTypeEnums);

	assert(inputTypeEnums.find(inputType) != inputTypeEnums.end() && "invalid inputType");

	return inputTypeEnums[inputType];
}
