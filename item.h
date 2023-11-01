//========================================
//
//シューティングアクション[item.h]
//Author：森川駿弥
//
//========================================
#include "main.h"
#include "billboard.h"
#include "player.h"

#ifndef _ITEM_H
#define _ITEM_H

//========================================
//マクロ定義
//========================================
#define ITEM_SIZE	(15.0f)		//アイテムのサイズ

#define ITEM_LIFE_TEX	"data\\texture\\item_life.png"

//========================================
//アイテムクラス
//========================================
class CItem : public CBillboard
{
public:
	CItem();	//コンストラクタ
	~CItem();	//デストラクタ

				//メンバ関数
	static CItem *Create(D3DXVECTOR3 pos);
	HRESULT Init() override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	float GetSize(void) { return 25.0f; }		//敵の大きさ

protected:

	bool CollisionPlayer(void);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャ
	D3DXVECTOR3 m_move;		//移動量
	int m_Counter;			//カウンター
	CObject *pObject;		//オブジェクトのポインタ
	CPlayer *pPlayer;		//プレイヤーのポインタ
};

#endif
