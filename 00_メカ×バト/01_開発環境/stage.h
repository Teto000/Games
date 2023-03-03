//===================================================
//
// �X�e�[�W�w�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _STAGE_H_
#define _STAGE_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "objectX.h"

//================================
// �X�e�[�W�N���X�̒�`
//================================
class CStage : public CObjectX
{
public:
	CStage();	//�R���X�g���N�^
	~CStage();	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CStage* Create(LPCTSTR text, D3DXVECTOR3 pos);

private:
	LPCTSTR m_text;	//���f���̃p�X
};

#endif