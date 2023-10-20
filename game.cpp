//========================================
//
//�Q�[��������[game.cpp]
//Author�F�X��x��
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
#include "gameobject.h"
#include "bg.h"

//========================================
//�}�N����`
//========================================
#define SCENE_COUNTER	(3600)	//���U���g�܂ł̑J�ڎ���

//========================================
//�ÓI�����o�ϐ�
//========================================
CObject *CGame::m_pObject[] = {};			//�I�u�W�F�N�g�̃|�C���^
CObjectX *CGame::m_pObjectX = nullptr;		//�I�u�W�F�N�gX�̃|�C���^
CObject3D *CGame::m_pObject3D = nullptr;	//�I�u�W�F�N�g3D�̃|�C���^
CGame *CGame::m_pGame = nullptr;			//�Q�[���̃|�C���^
CLight *CGame::m_pLight = nullptr;			//���C�g�̃|�C���^
CPlayer *CGame::m_pPlayer = nullptr;		//�v���C���[�̃|�C���^
CPolygon *CGame::m_pPolygon = nullptr;		//�|���S���̃|�C���^
CGameObject *CGame::m_pGameObject = nullptr;	//�Q�[�����I�u�W�F�N�g
CBg *CGame::m_pBg = nullptr;					//�w�i�̃|�C���^

//========================================
//�R���X�g���N�^
//========================================
CGame::CGame() : 
	m_bPause(false)
{
}

//========================================
//�f�X�g���N�^
//========================================
CGame::~CGame()
{
}

//========================================
//����
//========================================
CGame *CGame::Create(void)
{
	//CGame�̃|�C���^
	CGame *pGame = nullptr;

	if (pGame == nullptr)
	{
		//�C���X�^���X����
		pGame = new CGame;

		//������
		pGame->Init();
	}

	//�|�C���^��Ԃ�
	return pGame;
}

//========================================
//������
//========================================
HRESULT CGame::Init(void)
{
	//���C�g����
	if (m_pLight == nullptr)
	{//m_pLight��nullptr�̎�
		m_pLight = new CLight;
	}

	//���C�g�̏���������
	if (FAILED(m_pLight->Init()))
	{//���������������s�����ꍇ
		return -1;
	}

	//�v���C���[�̐���
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer;
	}

	//�v���C���[�̏���������
	if (FAILED(m_pPlayer->Init()))
	{//���������������s�����ꍇ
		return -1;
	}

	//�Q�[�����I�u�W�F�N�g
	if (m_pGameObject == nullptr)
	{
		m_pGameObject = new CGameObject;
	}

	//�Q�[�����I�u�W�F�N�g�̏���������
	if (FAILED(m_pGameObject->Init()))
	{//���������������s�����ꍇ
		return -1;
	}

	//�|�[�Y�̏��
	m_bPause = false;

	return S_OK;
}

//========================================
//�I��
//========================================
void CGame::Uninit(void)
{
	if (m_pPlayer != nullptr)
	{//�v���C���[�j��
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}
	
	if (m_pGameObject != nullptr)
	{//�Q�[�����I�u�W�F�N�g�j��
		m_pGameObject->Uninit();
		m_pGameObject = nullptr;
	}
}

//========================================
//�X�V
//========================================
void CGame::Update(void)
{
	//CInputKeyboard�^�̃|�C���^
	CInputKeyboard *pInputKeyboard = nullptr;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();	//�L�[�{�[�h�̏��擾

#ifdef _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_F3) == true)
	{
		CManager::SetMode(CScene::MODE_RESULT);
	}
#endif
}

//========================================
//�`��
//========================================
void CGame::Draw(void)
{
}
