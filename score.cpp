//========================================
//
//シューティングアクション[score.cpp]
//Author：森川駿弥
//
//========================================
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "debugproc.h"

//========================================
//マクロ定義
//========================================
#define SCORE_TEX		"data\\texture\\score.png"		//テクスチャへのパス
#define SCORE_SPACE		(40.0f)		//スコアの桁数毎の間隔
#define SCORE_POSX		(900.0f)	//スコアのX座標
#define SCORE_POSY		(35.0f)		//スコアのY座標

//========================================
//静的メンバ変数
//========================================
CNumber *CScore::m_apNumber[] = {};
int CScore::m_Score = 0;

//========================================
//コンストラクタ
//========================================
CScore::CScore()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Score = 0;			//スコアの値
	m_nPatternAnim = 0;		//スコアパターンNo,

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;		//CNumberの配列
	}
}

//========================================
//デストラクタ
//========================================
CScore::~CScore()
{

}

//========================================
//スコア生成
//========================================
CScore *CScore::Create(void)
{
	//CEnemy型のポインタ
	CScore *pScore = nullptr;

	if (pScore == nullptr)
	{//pScoreがnullptrの時
		//スコアの生成
		pScore = new CScore;

		//位置の初期化
		pScore->m_pos = D3DXVECTOR3(SCORE_POSX, SCORE_POSY, 0.0f);

		//初期化
		pScore->Init();

		//スコアの初期値
		pScore->SetScore(0);
	}

	//ポインタを返す
	return pScore;
}

//========================================
//初期化
//========================================
HRESULT CScore::Init(void)
{
	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetTexture();

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] == nullptr)
		{//nullptrの時
			//スコアの生成
			m_apNumber[nCnt] = CNumber::Create();

			if (m_apNumber[nCnt] != nullptr)
			{
				//テクスチャ設定
				m_apNumber[nCnt]->BindTexture(pTexture->Regist(SCORE_TEX));

				//スコアのサイズ
				m_apNumber[nCnt]->SetSize(60.0f, 60.0f);

				D3DXVECTOR3 posNum = m_pos;

				//桁数の間隔
				posNum.x += nCnt * 60.0f;

				//位置の設定
				m_apNumber[nCnt]->SetPosition(D3DXVECTOR3(posNum.x - 70.0f, 35.0f, 0.0f));
			}
		}
	}

	//スコアの値
	m_Score = 0;

	//成功を返す
	return S_OK;
}

//========================================
//終了
//========================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{//nullptrじゃない時
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = nullptr;
		}
	}

	//自分自身の破棄
	CObject::Release();
}

//========================================
//更新
//========================================
void CScore::Update(void)
{
}

//========================================
//描画
//========================================
void CScore::Draw(void)
{
}

//========================================
//スコア設定
//========================================
void CScore::SetScore(int nScore)
{
	m_Score = nScore;

	int aTexU[MAX_SCORE];  //各桁の数字を格納

	aTexU[0] = m_Score % 100000000 / 10000000;
	aTexU[1] = m_Score % 10000000 / 1000000;
	aTexU[2] = m_Score % 1000000 / 100000;
	aTexU[3] = m_Score % 100000 / 10000;
	aTexU[4] = m_Score % 10000 / 1000;
	aTexU[5] = m_Score % 1000 / 100;
	aTexU[6] = m_Score % 100 / 10;
	aTexU[7] = m_Score % 10 / 1;

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{//桁数分回す
		m_apNumber[nCnt]->SetVertexAnim(10, aTexU[nCnt]);
	}
}

//========================================
//頂点情報
//========================================
void CScore::SetVertex(void)
{
}

//========================================
//サイズ調整
//========================================
void CScore::SetSize(float fWidht, float fHeight)
{
}
