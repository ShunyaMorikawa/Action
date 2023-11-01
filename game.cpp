//========================================
//
//ゲーム内処理[game.cpp]
//Author：森川駿弥
//
//========================================
#include "game.h"
#include "object2D.h"
#include "objectx.h"
#include "time.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "light.h"
#include "player.h"
#include "polygon.h"
#include "mapobject.h"
#include "bg.h"
#include "time.h"
#include "sound.h"
#include "item.h"
#include "score.h"

//========================================
//マクロ定義
//========================================
#define SCENE_COUNTER	(3600)	//リザルトまでの遷移時間

//========================================
//静的メンバ変数
//========================================
CObject *CGame::m_pObject[] = {};			//オブジェクトのポインタ
CObjectX *CGame::m_pObjectX = nullptr;		//オブジェクトXのポインタ
CObject3D *CGame::m_pObject3D = nullptr;	//オブジェクト3Dのポインタ
CGame *CGame::m_pGame = nullptr;			//ゲームのポインタ
CLight *CGame::m_pLight = nullptr;			//ライトのポインタ
CPlayer *CGame::m_pPlayer = nullptr;		//プレイヤーのポインタ
CPolygon *CGame::m_pPolygon = nullptr;		//ポリゴンのポインタ
CMap *CGame::m_pMapObject = nullptr;		//ゲーム内オブジェクト
CBg *CGame::m_pBg = nullptr;				//背景のポインタ
CTime *CGame::m_pTime = nullptr;			//タイムのポインタ
CItem *CGame::m_pItem = nullptr;
CScore *CGame::m_pScore = nullptr;

//========================================
//コンストラクタ
//========================================
CGame::CGame() : 
	m_bPause(false)
{
}

//========================================
//デストラクタ
//========================================
CGame::~CGame()
{
}

//========================================
//生成
//========================================
CGame *CGame::Create(void)
{
	//CGameのポインタ
	CGame *pGame = nullptr;

	if (pGame == nullptr)
	{
		//インスタンス生成
		pGame = new CGame;

		//初期化
		pGame->Init(MODE::MODE_GAME);
	}

	//ポインタを返す
	return pGame;
}

//========================================
//初期化
//========================================
HRESULT CGame::Init(MODE)
{
	//CSound型のポインタ
	CSound *pSound = CManager::GetSound();

	//ライト生成
	if (m_pLight == nullptr)
	{//m_pLightがnullptrの時
		m_pLight = new CLight;
	}

	//ライトの初期化処理
	if (FAILED(m_pLight->Init()))
	{//初期化処理が失敗した場合
		return -1;
	}
	
	if (m_pPlayer == nullptr)
	{//プレイヤーの生成
		m_pPlayer = CPlayer::Create();
	}

	//プレイヤーの初期化処理
	if (FAILED(m_pPlayer->Init()))
	{//初期化処理が失敗した場合
		return -1;
	}
	
	if (m_pMapObject == nullptr)
	{//マップオブジェクトの生成
		m_pMapObject = CMap::Create();
	}

	//マップオブジェクトの初期化処理
	if (FAILED(m_pMapObject->Init()))
	{//初期化処理が失敗した場合
		return -1;
	}

	if (m_pTime == nullptr)
	{//タイムの生成
		m_pTime = CTime::Create();
	}
	
	if (m_pItem == nullptr)
	{
		m_pItem = CItem::Create(D3DXVECTOR3(50.0f, 0.0f , 0.0f));
	}

	if (m_pScore == nullptr)
	{//タイムの生成
		m_pScore = CScore::Create();
	}

	//ポーズの状態
	m_bPause = false;

	//pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//========================================
//終了
//========================================
void CGame::Uninit(void)
{
	//CSound型のポインタ
	CSound *pSound = CManager::GetSound();

	if (m_pPlayer != nullptr)
	{//プレイヤー破棄
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}
	
	if (m_pMapObject != nullptr)
	{//ゲーム内オブジェクト破棄
		m_pMapObject->Uninit();
		m_pMapObject = nullptr;
	}

	if (m_pTime != nullptr)
	{//タイム破棄
		m_pTime->Uninit();
		m_pTime = nullptr;
	}

	if (m_pItem != nullptr)
	{//アイテム破棄
		m_pItem->Uninit();
		m_pItem = nullptr;
	}

	if (m_pScore != nullptr)
	{//スコア破棄
		m_pScore->Uninit();
		m_pScore = nullptr;
	}

	//pSound->Stop();
}

//========================================
//更新
//========================================
void CGame::Update(void)
{
	//CInputKeyboard型のポインタ
	CInputKeyboard *pInputKeyboard = nullptr;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();	//キーボードの情報取得

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		CManager::SetMode(CScene::MODE_RESULT);
	}

#ifdef _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_F3) == true)
	{
		CManager::SetMode(CScene::MODE_RESULT);
	}
#endif
}

//========================================
//描画
//========================================
void CGame::Draw(void)
{
}
