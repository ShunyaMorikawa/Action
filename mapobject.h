//========================================
//
//�}�b�v�I�u�W�F�N�g[mapobject.h]
//Author�F�X��x��
//
//========================================
#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_
#include "main.h"
#include "objectX.h"
#include "model.h"

//========================================
//�}�N����`
//========================================
#define GAME_OBJ	(2)			//�Q�[�����I�u�W�F�N�g�̍ő吔
#define OBJ_WIDHT	(25.0f)		//�I�u�W�F�N�g�̕�
#define OBJ_HEIGHT	(25.0f)		//�I�u�W�F�N�g�̍���

//========================================
//�}�b�v�I�u�W�F�N�g�N���X
//========================================
class CMap
{
public:
	CMap();			//�R���X�g���N�^
	~CMap();		//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit();
	void Update();
	void Draw();
	void SetObject(CModel *ppModel, int nNumModel);

	static CMap *Create(void);	//�v���C���[����
	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//�ʒu�擾

	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);

	CModel **GetModel(void) { return &m_ppModel[0]; }	//���f���擾

private:

	HRESULT LoadObj(char *pFilePath);

	//�����o�ϐ�
	CModel *m_ppModel[GAME_OBJ];	//���f���ւ̃|�C���^
	CObjectX *m_pObjX[GAME_OBJ];	//�I�u�W�F�N�gX�̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;		//����

	int m_nNumModel;		//���f���̑���
};

#endif
