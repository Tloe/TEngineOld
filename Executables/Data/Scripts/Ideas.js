//Conseptual ideas
// inspiration: http://www.youtube.com/watch?v=_8cb84x944I

var spawner = new UniversalObject({
	name: "Spawner",
	systemObjects: [GameSystem : SpawnerObject]
})

spawner.GameObject.updateTimer = 5ms // or frames

spawner.GameObject.onUpdate: {
	spawner.GameObject.updateIn = 3 frames
}

var monster = new UniversalObject({
	name: "Monster",
	systemObjects: [
		GameSystem : ActorObject,
		PhysicsSystem : PhysicsObject,
		AISystem : AIObject
		]
})

monster.PhysicsObject.onColission: playSound
