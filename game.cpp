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
#include "mapobject.h"
#include "bg.h"
#include "time.h"
#include "sound.h"
#include "item.h"
#include "score.h"

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
CMap *CGame::m_pMapObject = nullptr;		//�Q�[�����I�u�W�F�N�g
CBg *CGame::m_pBg = nullptr;				//�w�i�̃|�C���^
CTime *CGame::m_pTime = nullptr;			//�^�C���̃|�C���^
CItem *CGame::m_pItem = nullptr;
CScore *CGame::m_pScore = nullptr;

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
		pGame->Init(MODE::MODE_GAME);
	}

	//�|�C���^��Ԃ�
	return pGame;
}

//========================================
//������
//========================================
HRESULT CGame::Init(MODE)
{
	//CSound�^�̃|�C���^
	CSound *pSound = CManager::GetSound();

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
	
	if (m_pPlayer == nullptr)
	{//�v���C���[�̐���
		m_pPlayer = CPlayer::Create();
	}

	//�v���C���[�̏���������
	if (FAILED(m_pPlayer->Init()))
	{//���������������s�����ꍇ
		return -1;
	}
	
	if (m_pMapObject == nullptr)
	{//�}�b�v�I�u�W�F�N�g�̐���
		m_pMapObject = CMap::Create();
	}

	//�}�b�v�I�u�W�F�N�g�̏���������
	if (FAILED(m_pMapObject->Init()))
	{//���������������s�����ꍇ
		return -1;
	}

	if (m_pTime == nullptr)
	{//�^�C���̐���
		m_pTime = CTime::Create();
	}
	
	if (m_pItem == nullptr)
	{
		m_pItem = CItem::Create(D3DXVECTOR3(50.0f, 0.0f , 0.0f));
	}

	if (m_pScore == nullptr)
	{//�^�C���̐���
		m_pScore = CScore::Create();
	}

	//�|�[�Y�̏��
	m_bPause = false;

	//pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//========================================
//�I��
//========================================
void CGame::Uninit(void)
{
	//CSound�^�̃|�C���^
	CSound *pSound = CManager::GetSound();

	if (m_pPlayer != nullptr)
	{//�v���C���[�j��
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}
	
	if (m_pMapObject != nullptr)
	{//�Q�[�����I�u�W�F�N�g�j��
		m_pMapObject->Uninit();
		m_pMapObject = nullptr;
	}

	if (m_pTime != nullptr)
	{//�^�C���j��
		m_pTime->Uninit();
		m_pTime = nullptr;
	}

	if (m_pItem != nullptr)
	{//�A�C�e���j��
		m_pItem->Uninit();
		m_pItem = nullptr;
	}

	if (m_pScore != nullptr)
	{//�X�R�A�j��
		m_pScore->Uninit();
		m_pScore = nullptr;
	}

	//pSound->Stop();
}

//========================================
//�X�V
//========================================
void CGame::Update(void)
{
	//CInputKeyboard�^�̃|�C���^
	CInputKeyboard *pInputKeyboard = nullptr;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();	//�L�[�{�[�h�̏��擾

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
//�`��
//========================================
void CGame::Draw(void)
{
}
