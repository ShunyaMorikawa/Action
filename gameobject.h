//========================================
//
//�Q�[�����I�u�W�F�N�g[gameobject.h]
//Author�F�X��x��
//
//========================================
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "main.h"
#include "objectX.h"
#include "model.h"

//========================================
//�}�N����`
//========================================
#define GAME_OBJ	(1)		//�Q�[�����I�u�W�F�N�g�̍ő吔

//========================================
//�Q�[�����I�u�W�F�N�g�N���X
//========================================
class CGameObject : public CModel
{
public:
	CGameObject();		//�R���X�g���N�^
	~CGameObject();		//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit();
	void Update();
	void Draw();
	void SetObject(CModel *ppModel, int nNumModel);

	static CGameObject *Create(void);	//�v���C���[����
	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//�ʒu�擾

	void LoadObj(char *pFilePath);

	CModel **GetModel(void) { return &m_ppModel[0]; }	//���f���擾

private:
	//�����o�ϐ�
	CModel *m_ppModel[GAME_OBJ];	//���f���ւ̃|�C���^
	CObjectX *m_pObjX;		//�I�u�W�F�N�gX�̃|�C���^

	D3DXVECTOR3 m_pos;

	int m_nNumModel;	//���f���̑���
};

#endif