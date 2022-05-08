#include"PushCollision.h"

void PushCollision::Player2Floor(Stage *stage, Player *player)
{
	if (stage == nullptr || player == nullptr)
	{
		return;
	}

	//è∞OBB
	for (int i = 0; i < stage->GetFloorSize(); i++)
	{
		bool isHit = true;		
		OBB diagonal;
		diagonal.Initilize(stage->GetFloorPos(i), stage->GetFloorAngle(i),stage->GetFloorScale(i));
		while (isHit == true)
		{
			OBB pOBB;
			pOBB.Initilize(player->GetPosition(), Vec3{}, player->GetPSize());
			if (OBBCollision::ColOBBs(pOBB, diagonal))
			{
				Vec3 set = { player->GetPosition().x,player->GetPosition().y + 1.0f, player->GetPosition().z };
				player->SetPosition(set);
				player->GroundFlag();
			}
			else
			{
				isHit = false;
			}
		}
	}
}


