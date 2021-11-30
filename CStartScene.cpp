#include "stdafx.h"
#include "CStartScene.h"

#include "CPlayer.h"
#include "CTestPlayer.h"
#include "CCollisionMgr.h"
#include "CCamera.h"

#include "Networker.h"
#include "CKeyMgr.h"
#include "Background.h"
void CStartScene::init()
{
	CBackground* Ground = new CBackground();
	Ground->Init();
	AddObj(Ground,OBJ_TYPE::DEFAULT);

	// �浹 �׷� ����
	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::OTHERPLAYER);
	//CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::OTHERPLAYER, OBJ_TYPE::OTHERPLAYER);
	// ī�޶� �ʱ�ȭ
	CCamera::GetInst()->init();
}

void CStartScene::update()
{
	CScene::update();
}

void CStartScene::Enter()
{
	thread networking{ [] { Networker::get().do_recv(); } };
	networking.detach();
	init();	
}

void CStartScene::Exit()
{
	DeleteAllObject();
}
