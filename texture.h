//========================================
//
//�V���[�e�B���O�A�N�V����[texture.h]
//Author�F�X��x��
//
//========================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"

//========================================
//�}�N����`
//========================================
#define MAX_TEXTURE		(64)	//�e�N�X�`���̍ő吔

//========================================
//�e�N�X�`���N���X
//========================================
class CTexture
{
public:
	CTexture();		//�R���X�g���N�^
	~CTexture();	//�f�X�g���N�^

	//�����o�֐�
	HRESULT Load(void);		//�e�N�X�`���ǂݍ���
	void Unload(void);		//�e�N�X�`���j��

	int Regist(const char *pFilename);			//�e�N�X�`�����蓖��
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	//�e�N�X�`���̃A�h���X�擾

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];	//�e�N�X�`���̔z��
	const char* m_apPath[MAX_TEXTURE];
	static int m_nNumAll;		//����
};

#endif