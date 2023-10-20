//========================================
//
//�Q�[�����I�u�W�F�N�g[gameobject.h]
//Author�F�X��x��
//
//========================================
#include "gameobject.h"

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

	//�t�@�C���ǂݍ���
	LoadObj("data\\FILE\\object.txt");

	//������Ԃ�
	return S_OK;
}

//========================================
//�I��
//========================================
void CGameObject::Uninit()
{
	CModel::Uninit();
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
	CModel::Draw();
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
