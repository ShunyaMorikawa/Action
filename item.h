//========================================
//
//�V���[�e�B���O�A�N�V����[item.h]
//Author�F�X��x��
//
//========================================
#include "main.h"
#include "billboard.h"
#include "player.h"

#ifndef _ITEM_H
#define _ITEM_H

//========================================
//�}�N����`
//========================================
#define ITEM_SIZE	(15.0f)		//�A�C�e���̃T�C�Y

#define ITEM_LIFE_TEX	"data\\texture\\item_life.png"

//========================================
//�A�C�e���N���X
//========================================
class CItem : public CBillboard
{
public:
	CItem();	//�R���X�g���N�^
	~CItem();	//�f�X�g���N�^

				//�����o�֐�
	static CItem *Create(D3DXVECTOR3 pos);
	HRESULT Init() override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	float GetSize(void) { return 25.0f; }		//�G�̑傫��

protected:

	bool CollisionPlayer(void);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`��
	D3DXVECTOR3 m_move;		//�ړ���
	int m_Counter;			//�J�E���^�[
	CObject *pObject;		//�I�u�W�F�N�g�̃|�C���^
	CPlayer *pPlayer;		//�v���C���[�̃|�C���^
};

#endif
