#include "World.h"

World::World()
{
}

World::~World()
{
	for (auto Actor : MyActors)
	{
		delete Actor;
	}
	MyActors.clear();

}


void World::Tick()
{
	for (auto Actor : MyActors)
	{
		Actor->Tick();
	}
}

void World::Render()
{
	for (AActor* Actor : MyActors)
	{
		Actor->Render();
	}
}

void World::SpawnActor(AActor* NewActor)
{
	MyActors.push_back(NewActor);
}

