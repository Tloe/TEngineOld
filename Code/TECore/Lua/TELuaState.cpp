#include "TELuaState.h"

#include "TEFileIO.h"
#include "TEVariant.h"
#include "TELuaTable.h"
#include "TELuaHelpers.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

namespace
{
	int require_fileIO(lua_State* luaState)
	{
		std::string moduleName(lua_tostring(luaState, 1));
		std::string filePath("/Scripts/" + moduleName + ".lua");

		std::vector<U8> data;
		TE::IO::FileIO & fileIO = *static_cast<TE::IO::FileIO*>(lua_touserdata(luaState, lua_upvalueindex(1)));
		fileIO.LoadFile(filePath, data);
		if (!data.empty())
		{
			if (luaL_loadbuffer(luaState, reinterpret_cast<const char*>(&data[0]), data.size(), filePath.c_str()))
			{
				std::string errorMsg(std::string("Error loading module \'" +
					moduleName +
					"' from file: " +
					filePath +
					":\n" +
					std::string(lua_tostring(luaState, -1))));
				luaL_error(luaState, errorMsg.c_str());
			}
		}
		else
		{
			lua_pushstring(luaState, std::string("\n\tno file Custom loader:" + filePath).c_str());
		}

		return 1;
	}
}
	
TE::Lua::State::State(IO::FileIO & fileIO)
	: m_nativeState(luaL_newstate())
{
	StackReseter stackReseter(*this);
	
	luaL_openlibs(m_nativeState);
	luaopen_io(m_nativeState);
	luaopen_base(m_nativeState);
	luaopen_table(m_nativeState);
	luaopen_string(m_nativeState);
	luaopen_math(m_nativeState);
	
	AddCustomLoader(fileIO);

	CreateTableInRegistry(*this, "TEngine_metatables");
}

TE::Lua::State::State(State &&rhs) : m_nativeState(rhs.m_nativeState)
{
	rhs.m_nativeState = nullptr;
}

TE::Lua::State::~State()
{
	if(m_nativeState)
		lua_close(m_nativeState);
}

bool TE::Lua::State::operator()(std::string & chunk)
{
	StackReseter stackReseter(*this);
	bool status = false;
	if (LoadBuffer(chunk.c_str(), chunk.size(), chunk))
		status = CallBuffer();
	return status;
}


TE::Lua::Variable TE::Lua::State::operator[](const std::string & key)
{
	return Variable{ *this, RefFromT(*this, key) };
}

TE::Lua::Variable TE::Lua::State::operator[](I32 key)
{
	return Variable{ *this, RefFromT(*this, key) };
}

void TE::Lua::State::RunFile(IO::FileIO & fileIO, const std::string & filePath)
{
	StackReseter stackReseter(*this);
	std::vector<U8> fileData;
	fileIO.LoadFile(filePath, fileData);

	assert(fileData.size());

	if(LoadBuffer(reinterpret_cast<const char*>(&(fileData[0])), fileData.size(), filePath.c_str()))
		CallBuffer();
}

void TE::Lua::State::RunDataBuffer(std::vector<U8> & dataBuffer, const std::string & bufferName)
{
	if(LoadBuffer(reinterpret_cast<const char*>(&(dataBuffer[0])), dataBuffer.size(), bufferName.c_str()))
		CallBuffer();
}


void TE::Lua::State::AddCustomLoader(IO::FileIO & fileIO)
{
	//get package package.loaders table
	lua_getfield(m_nativeState, LUA_GLOBALSINDEX, "package");
	lua_getfield(m_nativeState, -1, "loaders");
	//Get rid of the packages table
	//lua_remove(m_luaState, -2);

	//Count loaders so we can add to the end of package.loaders
	int loaderCount = 0;
	lua_pushnil(m_nativeState);
	while (lua_next(m_nativeState, -2) != 0)
	{
		lua_pop(m_nativeState, 1);
		++loaderCount;
	}

	//adding loader function to the end of loaders table with a closure
	lua_pushinteger(m_nativeState, loaderCount + 1);
	lua_pushlightuserdata(m_nativeState, static_cast<void*>(&fileIO));
	lua_pushcclosure(m_nativeState, &require_fileIO, 1);
	lua_rawset(m_nativeState, -3);
	//Pop loaders table from stack
	lua_pop(m_nativeState, 2);
}

bool TE::Lua::State::LoadBuffer(const char * buffer, size_t size, std::string name)
{
	if (luaL_loadbuffer(m_nativeState, buffer, size, name.c_str()))
	{
		std::cout << "TEngine: Unable to compile buffer:" << std::endl;
		std::cout << lua_tostring(m_nativeState, -1) << std::endl;

		return false;
	}

	return true;
}

bool TE::Lua::State::CallBuffer()
{
	if (lua_pcall(m_nativeState, 0, LUA_MULTRET, 0))
	{
		std::cout << "TEngine: Could not call buffer:" << std::endl;
		std::cout << lua_tostring(m_nativeState, -1) << std::endl;

		return false;
	}

	return true;
}

std::string TE::Lua::State::StackOutputString()
{
	std::stringstream outputStream;

	outputStream << "---------- " << std::endl <<"stack top: " << lua_gettop(m_nativeState) << std::endl;
	for (int i = 1; i < lua_gettop(m_nativeState) + 1; i++) {
		outputStream << i << ": ";
		if (lua_istable(m_nativeState, i))
			outputStream << " table: " << lua_topointer(m_nativeState, i) << std::endl;
		else if (lua_isnumber(m_nativeState, i))
			outputStream << " number: " << lua_tonumber(m_nativeState, i) << std::endl;
		else if (lua_isuserdata(m_nativeState, i)) {
			void* userdata = (void*)lua_touserdata(m_nativeState, i);
			outputStream << " userdata (" << userdata << ")" << std::endl;
		}
		else if (lua_isstring(m_nativeState, i))
			outputStream << " string: " << lua_tostring(m_nativeState, i) << std::endl;
		else if (lua_isfunction(m_nativeState, i))
			outputStream << " function" << std::endl;
		else if (lua_isnil(m_nativeState, i))
			outputStream << " nil" << std::endl;
		else
			outputStream << " unknown: " << lua_typename(m_nativeState, lua_type(m_nativeState, i)) << std::endl;
	}
	outputStream << "---------- " << std::endl;

	return outputStream.str();
}


void TE::Lua::State::DebugStack()
{
    std::cout << StackOutputString() << std::endl;
}

void TE::Lua::State::DEBUGPrintTable(Table & luaTable)
{
	lua_getglobal(m_nativeState, "printTable");
	luaTable.PushToStack();
	std::cout << StackOutputString();
	if (lua_pcall(m_nativeState, 1, 0, 0))
	{
		std::cout << "Could not call!";
		std::cout << lua_tostring(m_nativeState, -1);
	}
}
