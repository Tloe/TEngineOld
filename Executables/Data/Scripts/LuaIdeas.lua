require "engine"

engine.AddSceneFile("/Scenes/TestScene.scene")
engine.SetCurrentScene("/Scenes/TestScene.scene")

local uo = engine.CreateUniversalObject()

local value = engine.newValue("transform", "Position")
value1.AddVector({0,0,0})
local transformObject = uo.AddSystemObject("transform", "TransformObject", [value1,value2])

engine.MapConnectionToObjectId(0, 3)

engine.NetworkConnect()
