#include "TEEngine.h"
#include "TEPlatformWindowIncludes.h"
#include "TESystem.h"
#include "TEFileIO.h"
#include "TEEventManager.h"
#include "TEEnvironmentUpdateEvent.h"
#include "TELuaInterface.h"

#include "TELuaTable.h"
#include "TELuaVariable.h"
#include "TEState.h"

#include <assert.h>
#include <algorithm>

TE::Engine::EngineRoot::EngineRoot(TE::IO::FileIO& fileIO, const std::string &initScrip)
    : m_fileIO(fileIO)
    , m_startupScript(initScrip)
    , m_scheduler(m_threadPool)
    , m_environment(m_eventManager)
    , m_changeSyncer(m_threadPool)
    , m_sceneHandler(m_changeSyncer, fileIO, m_systems, m_scheduler)
	, m_luaState(fileIO)
    , m_accumulatedFrameTime(0)
    , m_accumulatedFrameRate(0)
    , m_microsecondsPrFrame()
    , m_totalFrameTime(0)
    , m_updateFrameCount(0)
    , m_drawFrameCount(0)
    , m_previousUpdateFrameCount(0)
    , m_previousDrawFrameCount(0)
    , m_updateFPS(0)
    , m_drawFPS(0)
    , m_previousFPSTime(0)
{
    m_eventManager.Subscribe<Event::EnvironmentUpdateEvent>(this);

	LUAInterface::SetupInterface(*this);
}

TE::Engine::EngineRoot::~EngineRoot()
{
	
}

void TE::Engine::EngineRoot::HandleEvent(Event::EnvironmentUpdateEvent &environmentUpdateEvent)
{
    const std::string & name = environmentUpdateEvent.GetName();
    if(name == "Framerate")
    {
        if(environmentUpdateEvent.GetValue().GetString() == "30Hz")
        {
            m_microsecondsPrFrame = 33333;
        }
        else if(environmentUpdateEvent.GetValue().GetString() == "60Hz")
        {
            m_microsecondsPrFrame = 16666;
        }
        m_maxFrameTime = m_microsecondsPrFrame * 5;
    }
}

/*void TE::Engine::EngineRoot::JSONDeserialize(const Json::Value &jsonValue)
{
    //assert(!jsonValue["Environment"].isNull());
    //assert(!jsonValue["System"].isNull());

    const Json::Value & jsonEnvironment = jsonValue["Environment"];
    for(const std::string & environmentVariable : jsonEnvironment.getMemberNames())
    {
        Event::EnvironmentUpdateEvent event(environmentVariable, Core::Variant(jsonEnvironment[environmentVariable].asString()));
        m_eventManager.QueEvent(event);
    }
	
    const Json::Value & jsonSystems = jsonValue["Systems"];
    for(const std::string & system : jsonSystems.getMemberNames())
    {
        auto systemItr = std::find_if(std::begin(m_systemFactories), std::end(m_systemFactories),
                                    [&system](Engine::SystemFactory* sysGenerator) { return sysGenerator->GetSystemName() == system; });

        U32 systemId = jsonSystems[system]["Id"].asUInt();
        std::vector<Core::Value> values;
        const Json::Value & jsonValues = jsonSystems[system]["Values"];
        for(const std::string & value : jsonValues.getMemberNames())
        {
            Core::Value newValue((*systemItr)->ValueFromString(value));

            if(jsonValues[value].isString())
            {
                newValue.AddString(jsonValues[value].asString());
            }
            else if(jsonValues[value].isArray())
            {
                for(auto & itr : jsonValues[value])
                {
                    newValue.AddString(itr.asString());
                }
            }
            else
            {
                assert(false);
            }

            values.emplace_back(std::move(newValue));
        }

        m_systems.emplace_back((*systemItr)->Generate(systemId, *this, values));
    }
}

void TE::Engine::EngineRoot::JSONSerialize(Json::Value &jsonValue)
{

}
*/

void TE::Engine::EngineRoot::SetData(Lua::Table & luaTable)
{
	std::cout << "SetData";
	//std::cout << luaTable["environment"]["framerate"].GetValue<std::string>();
}

TE::Lua::Table TE::Engine::EngineRoot::GetData()
{
	std::cout << "GetData --- CORRUPT";

	return Lua::Table(-1, m_luaState);
}

I32 func(float f)
{
	return static_cast<I32>(f);
}

class MyClass 
{
public:
	MyClass(I32 i) : m_j(2*i), m_i(i)
	{

	}

	I32 m_j;

	void Add(I32 iv)
	{
		std::cout << iv + m_i + m_j;
	}

private:
	I32 m_i;
};

void TE::Engine::EngineRoot::Startup()
{
	m_luaState.RunFile(m_fileIO, m_startupScript);
	m_luaState.RunFile(m_fileIO, std::string{"/Scripts/test.lua"});

	m_luaState.Register("fu", &func);
	std::string s;
	I32 i;
	U32 u;
	F32 f;
	std::tie(s, i ,u ,f) = m_luaState["test2"]();
	std::cout << s << " " << i << " " << u << " " << f << std::endl;
	
	std::string chunk{ "test3()" };
	m_luaState(chunk);

	I32 i1 = m_luaState["fu"](41.43);
	
	m_luaState["myTable"]["storedValue"] = "howdy!";

	std::string i2 = m_luaState["test4"]();

	std::cout << i1 << " " << i2 << std::endl;

	m_luaState["myTest"] = "Hmmmmm";

	chunk = "print(myTest)";
	m_luaState(chunk);

	m_luaState["MyClass"].SetClass<MyClass, I32>("AddTo", &MyClass::Add);

	chunk = "myclass = MyClass.new(42)";
	m_luaState(chunk);

	chunk = "printTable(myclass)";
	m_luaState(chunk);

	chunk = "printTable(MyClass)";
	m_luaState(chunk);

	chunk = "myclass.AddTo(24)";
	m_luaState(chunk);

	/*
	int a;
	std::string b;
	bool c;
	std::tie(c, a, b) =	m_luaState.CallFunction<bool, int, std::string>("testing", 1, "hi", false);

	assert(a == 1 && b == "hi" && !c);
	*/
	//std::vector<U8> data;
    //m_fileIO.LoadFile(m_initScript, data);

    //Json::Value jsonData;
    //IO::JsonValueFromData(&(data.front()), &(data.back()), jsonData);
    //JSONDeserialize(jsonData);

    for(SystemUPtr& systemPtr : m_systems)
	{
        systemPtr->Startup();
	}

    m_eventManager.HandleQuedEvents();
    assert(m_microsecondsPrFrame != 0);
}

void TE::Engine::EngineRoot::Run()
{
	while (m_environment.GetRuntimeState() != RuntimeState::Quit)
	{
		m_frameTimer.Update();
		U64 frameTime = m_frameTimer.GetDeltaMicroseconds();
		m_totalFrameTime += frameTime;

		if (frameTime > m_maxFrameTime)	frameTime = m_maxFrameTime;

		m_accumulatedFrameTime += frameTime;

		while (m_accumulatedFrameTime >= m_microsecondsPrFrame)
		{
			m_eventManager.HandleQuedEvents();

			m_accumulatedFrameRate += m_microsecondsPrFrame;
			m_accumulatedFrameTime -= m_microsecondsPrFrame;

			++m_updateFrameCount;
			//std::cout << "Frame: " << m_updateFrameCount << std::endl;
			m_scheduler.RunUpdatePassTasks(m_accumulatedFrameRate, m_microsecondsPrFrame);

			if (m_messageLoop && m_messageLoop())
				m_environment.SetRuntimeState(RuntimeState::Quit);
			m_changeSyncer.SyncronizeChanges();
		}

		F32 interpolation = static_cast<F32>(m_accumulatedFrameTime) / m_microsecondsPrFrame;
		++m_drawFrameCount;
		m_scheduler.RunDrawPassTasks(interpolation);

		if (m_totalFrameTime - m_previousFPSTime > Time::Microseconds::Second)
		{
			m_updateFPS = m_updateFrameCount - m_previousUpdateFrameCount;
			m_drawFPS = m_drawFrameCount - m_previousDrawFrameCount;
			m_previousUpdateFrameCount = m_updateFrameCount;
			m_previousDrawFrameCount = m_drawFrameCount;
			m_previousFPSTime = m_totalFrameTime;

			//std::cout << "update FPS: " << m_updateFPS << "Draw FPS: " << m_drawFPS << std::endl;
		}
	}
}

void TE::Engine::EngineRoot::Shutdown()
{
    m_sceneHandler.Cleanup();

    for(SystemUPtr& systemPtr : m_systems)
    {
        systemPtr->Shutdown();
    }
}

void TE::Engine::EngineRoot::SetMessageLoop(std::function<bool()> function)
{
    m_messageLoop = function;
}

void TE::Engine::EngineRoot::AddSystemFactory(TE::Engine::SystemFactory &systemGenerator)
{
    m_systemFactories.emplace_back(&systemGenerator);
}

U32 TE::Engine::EngineRoot::GetSystemId(const std::string &systemName)
{
    auto findItr = std::find_if(std::begin(m_systems), std::end(m_systems),
                                  [&systemName](SystemUPtr & sysPtr) { return sysPtr->GetSystemName() == systemName; } );

    return (*findItr)->GetSystemId();
}

TE::Engine::System &TE::Engine::EngineRoot::GetSystem(const std::string &systemName)
{
    auto findItr = std::find_if(std::begin(m_systems), std::end(m_systems),
                                  [&systemName](SystemUPtr & sysPtr) { return sysPtr->GetSystemName() == systemName; } );

    return *(*findItr);
}

TE::Event::EventManager& TE::Engine::EngineRoot::GetEventManager()
{
	return m_eventManager;
}

TE::Engine::SceneHandler& TE::Engine::EngineRoot::GetSceneHandler()
{
    return m_sceneHandler;
}

TE::IO::FileIO &TE::Engine::EngineRoot::GetFileIO()
{
    return m_fileIO;
}
