-- init script

--local TEngine = require "TEngine"

print("Running init script!")

local input
while(input ~= 's' and input ~= 'c') do
	print("Run as server (s) or client (c)?")
	input = io.read()
end	

if(input == "s") then
	local data = require("server_config")
	--TEngine.SetData(server_config)
else
	local data = require("client_config")
	--engineRoot.LoadLuaData(client_config)
end

--[[
TEngine.AddSceneFile("/Scenes/TestScene.scene")
TEngine.SetCurrentScene("/Scenes/TestScene.scene")
]]--
