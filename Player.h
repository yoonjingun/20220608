#pragma once
#include"Actor.h"

//2차원 좌표에 자신을 그리고 충돌 처리한다.
//입력을 처리한다.
class APlayer :public AActor
{
public:
	APlayer();
	virtual ~APlayer();
	APlayer(int NewX, int NewY, char NewSpape, bool bNewCollision = false, int NewSortOrder=4);

	virtual void Tick() override;
	bool IsGoal();

};

