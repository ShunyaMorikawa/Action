//========================================
//
//�Q�[�����I�u�W�F�N�g[gameobject.h]
//Author�F�X��x��
//
//========================================
#include "gameobject.h"
#include "renderer.h"
#include "manager.h"

//========================================
//�R���X�g���N�^
//========================================
CGameObject::CGameObject() :
	m_pos(0.0f, 0.0f, 0.0f),
	m_nNumModel(0)
{
	m_ppModel[GAME_OBJ] = {};
}

//========================================
//�f�X�g���N�^
//========================================
CGameObject::~CGameObject()
{
}

//========================================
//������
//========================================
HRESULT CGameObject::Init(void)
{
	for (int nCnt = 0; nCnt < GAME_OBJ; nCnt++)
	{
		m_ppModel[nCnt] = nullptr;
	}

	//�I�u�W�F�N�g����
	m_ppModel[0] = CModel::Create("data\\MODEL\\object\\woodbox.x");

	//�p�[�c�̈ʒu(�S�p�[�c��)
	m_ppModel[0]->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 0.0f));

	//�t�@�C���ǂݍ���
	//LoadObj("data\\FILE\\object.txt");

	//������Ԃ�
	return S_OK;
}

//========================================
//�I��
//========================================
void CGameObject::Uninit()
{
	//�I�u�W�F�N�g(�������g)�̔j��
	Release();
}

//========================================
//�X�V
//========================================
void CGameObject::Update()
{
}

//========================================
//�`��
//========================================
void CGameObject::Draw()
{
	//�`��
	//CObject::Draw();


	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_ppModel[0]->Draw();
}

//========================================
//����
//========================================
CGameObject *CGameObject::Create(void)
{
	//CGameObject�^�̃|�C���^
	CGameObject *pGameObject = nullptr;

	if (pGameObject == nullptr)
	{
		//�C���X�^���X����
		pGameObject = new CGameObject;

		//������
		pGameObject->Init();
	}

	//�|�C���^��Ԃ�
	return pGameObject;
}

//========================================
//�I�u�W�F�N�g�ݒ�
//========================================
void CGameObject::SetObject(CModel * ppModel, int nNumModel)
{
	//�|�C���^
	m_ppModel[nNumModel] = ppModel;

	//�p�[�c�ԍ�
	m_nNumModel++;
}

//========================================
//�t�@�C���ǂݍ���
//========================================
void CGameObject::LoadObj(char * pFilePath)
{
	//�ϐ��錾
	char garbage[640];		//�S�~�i�[�p
	char FileName[32];		//�e���f���̃t�@�C����
	int nIdx = 0;			//���Ԗڂ̃p�[�c��
	int nNumParts = 0;		//�p�[�c��
	int nNum = 0;			//�ǂݍ��ޔԍ�
	int nModelIndex = 0;	//�p�[�c�̔ԍ�

	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);		//�ʒu
	D3DXVECTOR3 rot(0.0f, 0.0f, 0.0f);		//����

	//FILE�̃|�C���^
	FILE *pFile = nullptr;

	//�t�@�C�����J��
	pFile = fopen(pFilePath, "r");

	while (1)
	{//END_SCRIPT������܂ŌJ��Ԃ�
		//�s�v�ȕ������̂Ă�
		fscanf(pFile, "%s", &garbage[0]);

		if (strcmp(&garbage[0], "END_SCRIPT") == 0)
		{//������END_SCRIPT�̂Ƃ�
			//�����o��
			break;
		}

		//========================================
		//�I�u�W�F�N�g�t�@�C���̓ǂݍ���
		//========================================
		if (strcmp(&garbage[0], "OBJECT_FILENAME") == 0)
		{//������OBJECT_FILENAME�̂Ƃ�
			//=�̂Ă�
			fscanf(pFile, "%s", &garbage[0]);

			//�t�@�C���̖��O�擾
			fscanf(pFile, "%s", &FileName[0]);

			//���f���̐���
			m_ppModel[nNum] = CModel::Create(&FileName[0]);

			//���f���ݒ�
			SetObject(m_ppModel[nNum], nNum);

			//���f���̔ԍ������Z����
			nNum++;
		}

		//========================================
		//�I�u�W�F�N�g�ݒ�
		//========================================
		if (strcmp(&garbage[0], "MODELSET") == 0)
		{//������OBJECTSET�̏ꍇ
			while (1)
			{//������END_OBJECTSET�ɂȂ�܂ŌJ��Ԃ�
				fscanf(pFile, "%s", &garbage[0]);

				if (strcmp(&garbage[0], "END_MODELSET") == 0)
				{//������END_CHARACTERSET�̎�
					//�����o��
					break;
				}

				if (strcmp(&garbage[0], "NUM_OBJECT") == 0)
				{//������NUM_PARTS�̎�
					//=�̂Ă�
					fscanf(pFile, "%s", &garbage[0]);

					//�p�[�c��������
					fscanf(pFile, "%d", &nNumParts);
				}
			}

			if (strcmp(&garbage[0], "OBJECTSET") == 0)
			{//������PARTSSET�̎�
				while (1)
				{//END_PARTSSET������܂ŉ�
					fscanf(pFile, "%s", &garbage[0]);

					if (strcmp(&garbage[0], "END_OBJECTSET") == 0)
					{//������END_PARTSSET�̎�
						//�p�[�c�������Z
						nModelIndex++;

						//�����o��
						break;
					}

					if (strcmp(&garbage[0], "INDEX") == 0)
					{//������INDEX�̎�
						//=�̂Ă�
						fscanf(pFile, "%s", &garbage[0]);

						//���Ԗڂ̃p�[�c���̐ݒ�
						fscanf(pFile, "%d", &nIdx);

						//���f���̔ԍ��ݒ�
						m_ppModel[nModelIndex]->SetIndex(m_ppModel[nIdx]);
					}

					if (strcmp(&garbage[0], "POS") == 0)
					{//������PARENT�̎�
						//=�̂Ă�
						fscanf(pFile, "%s", &garbage[0]);

						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);

						//�ʒu��ݒ�
						m_ppModel[nModelIndex]->SetPos(pos);
					}

					if (strcmp(&garbage[0], "ROT") == 0)
					{//������PARENT�̎�
						//=�̂Ă�
						fscanf(pFile, "%s", &garbage[0]);

						fscanf(pFile, "%f", &rot.x);
						fscanf(pFile, "%f", &rot.y);
						fscanf(pFile, "%f", &rot.z);

						//������ݒ�
						m_ppModel[nModelIndex]->SetRotate(rot);
					}
				}
			}
		}
	}

	//�t�@�C�������
	fclose(pFile);
}

//========================================
//3D�I�u�W�F�N�g�̓����蔻��
//========================================
bool CGameObject::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	bool bLand = false;		//���n�������ǂ���
	D3DXVECTOR3 VtxMax = m_pObjX->GetVtxMax();	//�ő�l
	D3DXVECTOR3 VtxMin = m_pObjX->GetVtxMin();	//�ŏ��l

	if (pPos->y - OBJ_WIDHT <= m_pos.y + VtxMax.y
		&& pPos->y + OBJ_WIDHT >= m_pos.y + VtxMin.y)
	{
		//�u���b�N�̍�����߂荞�񂾎�
		if (pPosOld->x + OBJ_WIDHT <= m_pos.x + VtxMin.x	//�O��̈ʒu���u���b�N��荶
			&& pPos->x + OBJ_WIDHT >= m_pos.x + VtxMin.x)	//����̈ʒu���u���b�N���E
		{
			//�u���b�N�̉�
			pPos->x = m_pos.x + VtxMin.x - OBJ_WIDHT;
			//�ړ��ʂ�0�ɂ���
			pMove->x = 0.0f;
		}

		//�u���b�N�̉E����߂荞�񂾎�
		else if (pPosOld->x - OBJ_WIDHT >= m_pos.x + VtxMax.x 	//�O��̈ʒu���u���b�N��荶
			&& pPos->x - OBJ_WIDHT <= m_pos.x + VtxMax.x)		//����̈ʒu���u���b�N���E
		{
			//�u���b�N�̉�
			pPos->x = m_pos.x + VtxMax.x + OBJ_WIDHT;
			//�ړ��ʂ�0�ɂ���
			pMove->x = 0.0f;
		}
	}

	//�u���b�N�̕�
	if (pPos->x - OBJ_WIDHT <= m_pos.x + VtxMax.x
		&& pPos->x + OBJ_WIDHT >= m_pos.x + VtxMin.x)
	{

		//�u���b�N�̏ォ��߂荞�񂾎�
		if (pPosOld->y + OBJ_WIDHT <= m_pos.y + VtxMin.y	//�O��̈ʒu���u���b�N��荶
			&& pPos->y + OBJ_WIDHT >= m_pos.y + VtxMin.y)	//����̈ʒu���u���b�N���E
		{
			//�u���b�N�̉�
			pPos->y = m_pos.y + VtxMin.y - OBJ_WIDHT;

			//���n����
			bLand = true;

			//�ړ��ʂ�0�ɂ���
			pMove->y = 0.0f;
		}

		//�u���b�N�̉�����߂荞�񂾎�
		else if (pPosOld->y - OBJ_WIDHT >= m_pos.y + VtxMax.y 	//�O��̈ʒu���u���b�N��荶
			&& pPos->y - OBJ_WIDHT <= m_pos.y + VtxMax.y)//����̈ʒu���u���b�N���E
		{
			//�u���b�N�̉�
			pPos->y = m_pos.y + VtxMax.y + OBJ_WIDHT;

			//�ړ��ʂ�0�ɂ���
			pMove->y = 0.0f;
		}
	}

	//bLand��Ԃ�
	return bLand;
}

//========================================
//3D�I�u�W�F�N�g�̐���
//========================================
void CGameObject::SetVertex(void)
{
}

//========================================
//3D�I�u�W�F�N�g�̐���
//========================================
void CGameObject::SetSize(float fWidht, float fHeight)
{
}
