#include<iostream>
#include<fstream>
#include<conio.h>
#include<algorithm>
#include"World.h"
#include "Engine.h"
#include"Wall.h"
#include"Player.h"
#include"Goal.h"
#include"Floor.h"
#include"Monster.h"

int Engine::KeyCode = 0;

Engine* Engine::Instance = nullptr;

Engine::Engine()
{
	Instance = this;
	Initilize();
}

Engine::~Engine()
{
	Terminate();
}

void Engine::Initilize()
{
	bRunning = true;
	MyWorld = new World();
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL_INIT_ERROR");
	}

	//윈도창 만들기
	MyWindow = SDL_CreateWindow("Maze", 100, 100, 800, 600, SDL_WINDOW_VULKAN);
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
}

void Engine::Load(string MapFilename)
{
	ifstream MapFile(MapFilename);

	int Y = 0;
	while (MapFile.peek() != EOF)
	{
		char Buffer[1024] = { 0, };
		MapFile.getline(Buffer, 1024);

		for (size_t X = 0; X < strlen(Buffer); X++)
		{
			char Cursor = Buffer[X];
			switch (Cursor)
			{
			case'#':
				MyWorld->MyActors.push_back(new AWall(X, Y, '#', true));
				break;
			case' ':
				MyWorld->MyActors.push_back(new AFloor(X, Y, ' ', false));
				break;
			case'p':
				MyWorld->MyActors.push_back(new APlayer(X, Y, 'P', true));
				break;
			case 'G':
				MyWorld->MyActors.push_back(new AGoal(X, Y, 'G', false));
				break;
			case 'M':
				MyWorld->MyActors.push_back(new AMonster(X, Y, 'M', false));
				break;
			}
			MyWorld->SpawnActor(new AFloor((int)X, Y, ' ', false));

		}
		Y++;
	}
	//그리는 순서를 변경
	sort(MyWorld->MyActors.begin(), MyWorld->MyActors.end(), AActor::Compare);
	MapFile.close();
}

void Engine::Run()
{
	while (bRunning)
	{
		Input();
		MyWorld->Tick();
		SDL_SetRenderDrawColor(MyRenderer, 0xff, 0x00, 0x00, 0xff);
		SDL_RenderClear(MyRenderer);

		MyWorld->Render(); //액터 그릴꺼 등록

		//등록 된 일 시작
		SDL_RenderPresent(MyRenderer);
	}
}

void Engine::Terminate()
{
	delete MyWorld;
	MyWorld = nullptr;

	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
	SDL_Quit();
}

void Engine::Input()
{
	SDL_PollEvent(&MyEvent);
}
