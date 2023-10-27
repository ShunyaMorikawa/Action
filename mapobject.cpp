//========================================
//
//ゲーム内オブジェクト[gameobject.h]
//Author：森川駿弥
//
//========================================
#include "mapobject.h"
#include "renderer.h"
#include "manager.h"

//========================================
//コンストラクタ
//========================================
CMap::CMap() :
	m_pos(0.0f, 0.0f, 0.0f),
	m_nNumModel(0)
{
	m_ppModel[GAME_OBJ] = {};
	m_pObjX[GAME_OBJ] = {};
}

//========================================
//デストラクタ
//========================================
CMap::~CMap()
{
}

//========================================
//初期化
//========================================
HRESULT CMap::Init(void)
{
	//成功を返す
	return LoadObj("data\\FILE\\object.txt");
}

//========================================
//終了
//========================================
void CMap::Uninit()
{
}

//========================================
//更新
//========================================
void CMap::Update()
{
}

//========================================
//描画
//========================================
void CMap::Draw()
{
}

//========================================
//生成
//========================================
CMap *CMap::Create(void)
{
	//CGameObject型のポインタ
	CMap *pMapObject = nullptr;

	if (pMapObject == nullptr)
	{
		//インスタンス生成
		pMapObject = new CMap;

		//初期化
		pMapObject->Init();
	}

	//ポインタを返す
	return pMapObject;
}

//========================================
//オブジェクト設定
//========================================
void CMap::SetObject(CModel * ppModel, int nNumModel)
{
	//ポインタ
	m_ppModel[nNumModel] = ppModel;

	//パーツ番号
	m_nNumModel++;
}

//========================================
//ファイル読み込み
//========================================
HRESULT CMap::LoadObj(char *pFilePath)
{
	//変数宣言
	char garbage[640];		//ゴミ格納用
	char FileName[32];		//各モデルのファイル名
	int nIdx = 0;			//何番目のパーツか
	int nNumParts = 0;		//パーツ数
	int nNum = 0;			//読み込む番号
	int nModelIndex = 0;	//パーツの番号

	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);		//位置
	D3DXVECTOR3 rot(0.0f, 0.0f, 0.0f);		//向き

	//FILEのポインタ
	FILE *pFile = nullptr;

	//ファイルを開く
	pFile = fopen(pFilePath, "r");

	if (pFile == NULL)
	{
		return E_FAIL;
	}

	while (1)
	{//END_SCRIPTが来るまで繰り返す
		//不要な文字を捨てる
		fscanf(pFile, "%s", &garbage[0]);

		if (strcmp(&garbage[0], "END_SCRIPT") == 0)
		{//文字列がEND_SCRIPTのとき
			//抜け出す
			break;
		}

		//========================================
		//オブジェクトファイルの読み込み
		//========================================
		if (strcmp(&garbage[0], "OBJECT_FILENAME") == 0)
		{//文字列がOBJECT_FILENAMEのとき
			//=捨てる
			fscanf(pFile, "%s", &garbage[0]);

			//ファイルの名前取得
			fscanf(pFile, "%s", &FileName[0]);

			//モデルの生成
			m_ppModel[nNum] = CModel::Create(&FileName[0]);

			//モデル設定
			SetObject(m_ppModel[nNum], nNum);

			//モデルの番号を加算する
			nNum++;
		}

		//========================================
		//オブジェクト設定
		//========================================
		if (strcmp(&garbage[0], "MODELSET") == 0)
		{//文字列がOBJECTSETの場合
			while (1)
			{//文字列がEND_OBJECTSETになるまで繰り返す
				fscanf(pFile, "%s", &garbage[0]);

				if (strcmp(&garbage[0], "END_MODELSET") == 0)
				{//文字列がEND_CHARACTERSETの時
					//抜け出す
					break;
				}

				if (strcmp(&garbage[0], "NUM_OBJECT") == 0)
				{//文字列がNUM_PARTSの時
					//=捨てる
					fscanf(pFile, "%s", &garbage[0]);

					//パーツ数を入れる
					fscanf(pFile, "%d", &nNumParts);
				}
			}

			if (strcmp(&garbage[0], "OBJECTSET") == 0)
			{//文字列がPARTSSETの時
				while (1)
				{//END_PARTSSETが来るまで回す
					fscanf(pFile, "%s", &garbage[0]);

					if (strcmp(&garbage[0], "END_OBJECTSET") == 0)
					{//文字列がEND_PARTSSETの時
						//パーツ数を加算
						nModelIndex++;

						//抜け出す
						break;
					}

					if (strcmp(&garbage[0], "INDEX") == 0)
					{//文字列がINDEXの時
						//=捨てる
						fscanf(pFile, "%s", &garbage[0]);

						//何番目のパーツかの設定
						fscanf(pFile, "%d", &nIdx);

						//モデルの番号設定
						m_ppModel[nModelIndex]->SetIndex(m_ppModel[nIdx]);
					}

					if (strcmp(&garbage[0], "POS") == 0)
					{//文字列がPARENTの時
						//=捨てる
						fscanf(pFile, "%s", &garbage[0]);

						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);

						//位置を設定
						m_ppModel[nModelIndex]->SetPos(pos);
					}

					if (strcmp(&garbage[0], "ROT") == 0)
					{//文字列がPARENTの時
						//=捨てる
						fscanf(pFile, "%s", &garbage[0]);

						fscanf(pFile, "%f", &rot.x);
						fscanf(pFile, "%f", &rot.y);
						fscanf(pFile, "%f", &rot.z);

						//向きを設定
						m_ppModel[nModelIndex]->SetRotate(rot);
					}
				}
			}
		}
	}

	//ファイルを閉じる
	fclose(pFile);

	return S_OK;
}

//========================================
//3Dオブジェクトの当たり判定
//========================================
//bool CMap::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
//{
//	bool bLand = false;		//着地したかどうか
//	D3DXVECTOR3 VtxMax = m_pObjX->GetVtxMax();	//最大値
//	D3DXVECTOR3 VtxMin = m_pObjX->GetVtxMin();	//最小値
//
//	if (pPos->y - OBJ_WIDHT <= m_pos.y + VtxMax.y
//		&& pPos->y + OBJ_WIDHT >= m_pos.y + VtxMin.y)
//	{
//		//ブロックの左からめり込んだ時
//		if (pPosOld->x + OBJ_WIDHT <= m_pos.x + VtxMin.x	//前回の位置がブロックより左
//			&& pPos->x + OBJ_WIDHT >= m_pos.x + VtxMin.x)	//今回の位置がブロックより右
//		{
//			//ブロックの横
//			pPos->x = m_pos.x + VtxMin.x - OBJ_WIDHT;
//			//移動量を0にする
//			pMove->x = 0.0f;
//		}
//
//		//ブロックの右からめり込んだ時
//		else if (pPosOld->x - OBJ_WIDHT >= m_pos.x + VtxMax.x 	//前回の位置がブロックより左
//			&& pPos->x - OBJ_WIDHT <= m_pos.x + VtxMax.x)		//今回の位置がブロックより右
//		{
//			//ブロックの横
//			pPos->x = m_pos.x + VtxMax.x + OBJ_WIDHT;
//			//移動量を0にする
//			pMove->x = 0.0f;
//		}
//	}
//
//	//ブロックの幅
//	if (pPos->x - OBJ_WIDHT <= m_pos.x + VtxMax.x
//		&& pPos->x + OBJ_WIDHT >= m_pos.x + VtxMin.x)
//	{
//		//ブロックの上からめり込んだ時
//		if (pPosOld->y + OBJ_WIDHT <= m_pos.y + VtxMin.y	//前回の位置がブロックより左
//			&& pPos->y + OBJ_WIDHT >= m_pos.y + VtxMin.y)	//今回の位置がブロックより右
//		{
//			//ブロックの横
//			pPos->y = m_pos.y + VtxMin.y - OBJ_WIDHT;
//
//			//着地した
//			bLand = true;
//
//			//移動量を0にする
//			pMove->y = 0.0f;
//		}
//
//		//ブロックの下からめり込んだ時
//		else if (pPosOld->y - OBJ_WIDHT >= m_pos.y + VtxMax.y 	//前回の位置がブロックより左
//			&& pPos->y - OBJ_WIDHT <= m_pos.y + VtxMax.y)//今回の位置がブロックより右
//		{
//			//ブロックの横
//			pPos->y = m_pos.y + VtxMax.y + OBJ_WIDHT;
//
//			//移動量を0にする
//			pMove->y = 0.0f;
//		}
//	}
//
//	//bLandを返す
//	return bLand;
//}

//========================================
//3Dオブジェクトの生成
//========================================
void CMap::SetVertex(void)
{
}

//========================================
//3Dオブジェクトの生成
//========================================
void CMap::SetSize(float fWidht, float fHeight)
{
}
