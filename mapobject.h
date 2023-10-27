//========================================
//
//マップオブジェクト[mapobject.h]
//Author：森川駿弥
//
//========================================
#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_
#include "main.h"
#include "objectX.h"
#include "model.h"

//========================================
//マクロ定義
//========================================
#define GAME_OBJ	(2)			//ゲーム内オブジェクトの最大数
#define OBJ_WIDHT	(25.0f)		//オブジェクトの幅
#define OBJ_HEIGHT	(25.0f)		//オブジェクトの高さ

//========================================
//マップオブジェクトクラス
//========================================
class CMap
{
public:
	CMap();			//コンストラクタ
	~CMap();		//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit();
	void Update();
	void Draw();
	void SetObject(CModel *ppModel, int nNumModel);

	static CMap *Create(void);	//プレイヤー生成
	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//位置設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//位置取得

	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);

	CModel **GetModel(void) { return &m_ppModel[0]; }	//モデル取得

private:

	HRESULT LoadObj(char *pFilePath);

	//メンバ変数
	CModel *m_ppModel[GAME_OBJ];	//モデルへのポインタ
	CObjectX *m_pObjX[GAME_OBJ];	//オブジェクトXのポインタ

	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;		//向き

	int m_nNumModel;		//モデルの総数
};

#endif
