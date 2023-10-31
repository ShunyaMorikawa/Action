//========================================
//
//シューティングアクション[item.h]
//Author：森川駿弥
//
//========================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "game.h"
#include "debugproc.h"

//========================================
//静的メンバ変数
//========================================
LPDIRECT3DTEXTURE9 CItem::m_pTexture = nullptr;	//テクスチャのポインタ

//========================================
//コンストラクタ
//========================================
CItem::CItem() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		//移動量
	pObject(nullptr),
	pPlayer(nullptr)
{//値クリア
}

//========================================
//デストラクタ
//========================================
CItem::~CItem()
{
}

//========================================
//生成
//========================================
CItem *CItem::Create(D3DXVECTOR3 pos)
{
	//CLife型のポインタ
	CItem *pItem = nullptr;

	if (pItem == nullptr)
	{//pItemがnullptr
		//初期化
		pItem->Init();

		//アイテムの位置
		pItem->SetPosition(pos);
	}

	//ポインタを返す
	return pItem;
}

//========================================
//初期化
//========================================
HRESULT CItem::Init(void)
{
	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetTexture();

	//初期化
	if (FAILED(CBillboard::Init()))
	{// 失敗を返す
		return E_FAIL;
	}

	//テクスチャ
	BindTexture(pTexture->Regist(ITEM_LIFE_TEX));

	//アイテムの大きさ
	CBillboard::SetSizeVertex(ITEM_SIZE, ITEM_SIZE);

	return S_OK;
}

//========================================
//終了
//========================================
void CItem::Uninit(void)
{
	//終了
	CBillboard::Uninit();
}

//========================================
//更新
//========================================
void CItem::Update(void)
{
}

//========================================
//描画
//========================================
void CItem::Draw(void)
{
	//描画
	CBillboard::Draw();
}

//========================================
//プレイヤーとの当たり判定
//========================================
bool CItem::CollisionPlayer(void)
{
	//変数宣言
	float fLength;		//長さ

	//プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	//プレイヤーの位置取得
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	//ベクトルを求める
	D3DXVECTOR3 vec = posPlayer - this->GetPosition();

	//ベクトル代入
	fLength = D3DXVec3Length(&vec);

	return fLength <= ITEM_SIZE;
}
