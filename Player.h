#pragma once
#include"Actor.h"

//2���� ��ǥ�� �ڽ��� �׸��� �浹 ó���Ѵ�.
//�Է��� ó���Ѵ�.
class APlayer :public AActor
{
public:
	APlayer();
	virtual ~APlayer();
	APlayer(int NewX, int NewY, char NewSpape, bool bNewCollision = false, int NewSortOrder=4);

	virtual void Tick() override;
	bool IsGoal();

};

