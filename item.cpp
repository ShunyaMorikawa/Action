//========================================
//
//�V���[�e�B���O�A�N�V����[item.h]
//Author�F�X��x��
//
//========================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "game.h"
#include "debugproc.h"

//========================================
//�ÓI�����o�ϐ�
//========================================
LPDIRECT3DTEXTURE9 CItem::m_pTexture = nullptr;	//�e�N�X�`���̃|�C���^

//========================================
//�R���X�g���N�^
//========================================
CItem::CItem() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		//�ړ���
	pObject(nullptr),
	pPlayer(nullptr)
{//�l�N���A
}

//========================================
//�f�X�g���N�^
//========================================
CItem::~CItem()
{
}

//========================================
//����
//========================================
CItem *CItem::Create(D3DXVECTOR3 pos)
{
	//CLife�^�̃|�C���^
	CItem *pItem = nullptr;

	if (pItem == nullptr)
	{//pItem��nullptr
		//������
		pItem->Init();

		//�A�C�e���̈ʒu
		pItem->SetPosition(pos);
	}

	//�|�C���^��Ԃ�
	return pItem;
}

//========================================
//������
//========================================
HRESULT CItem::Init(void)
{
	//�e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetTexture();

	//������
	if (FAILED(CBillboard::Init()))
	{// ���s��Ԃ�
		return E_FAIL;
	}

	//�e�N�X�`��
	BindTexture(pTexture->Regist(ITEM_LIFE_TEX));

	//�A�C�e���̑傫��
	CBillboard::SetSizeVertex(ITEM_SIZE, ITEM_SIZE);

	return S_OK;
}

//========================================
//�I��
//========================================
void CItem::Uninit(void)
{
	//�I��
	CBillboard::Uninit();
}

//========================================
//�X�V
//========================================
void CItem::Update(void)
{
}

//========================================
//�`��
//========================================
void CItem::Draw(void)
{
	//�`��
	CBillboard::Draw();
}

//========================================
//�v���C���[�Ƃ̓����蔻��
//========================================
bool CItem::CollisionPlayer(void)
{
	//�ϐ��錾
	float fLength;		//����

	//�v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	//�v���C���[�̈ʒu�擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	//�x�N�g�������߂�
	D3DXVECTOR3 vec = posPlayer - this->GetPosition();

	//�x�N�g�����
	fLength = D3DXVec3Length(&vec);

	return fLength <= ITEM_SIZE;
}
