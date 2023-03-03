//===================================================
//
// �Q�[�W�t���[���w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _FREAM_H_
#define _FREAM_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object2D.h"

//--------------------------------
// �t���[���N���X
//--------------------------------
class CFream : public CObject2D
{
public:
	CFream();				//�R���X�g���N�^
	~CFream() override;		//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CFream* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
};

#endif