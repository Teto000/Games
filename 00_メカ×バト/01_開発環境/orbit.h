//===================================================
//
// �O�Ճw�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _ORBIT_H_
#define _ORBIT_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object.h"

//--------------------------------
// ���̋O�ՃN���X
//--------------------------------
class COrbit : public CObject
{
public:
	COrbit();	//�R���X�g���N�^
	~COrbit();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �Z�b�^�[
	//------------------
	void SetMtxParent(D3DXMATRIX pMtx) { m_pMtxParent = pMtx; };	//�e�̃}�g���b�N�X�̐ݒ�
	void SetOffset(D3DXVECTOR3 offset) { m_offsetPos = offset; }	//�I�t�Z�b�g���W�̐ݒ�
	void SetColor(D3DXCOLOR col);			//�F�̐ݒ�

	//------------------
	// �Q�b�^�[
	//------------------
	D3DXVECTOR3 GetPosition() override { return m_offsetPos; }	//�ʒu�̎擾
	float GetWidth() override { return 0.0f; }					//���̎擾
	float GetHeight() override { return 0.0f; }					//�����̎擾

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static COrbit* Create(D3DXVECTOR3 offset, D3DXMATRIX mtx);

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxVtx = 2048;	//���_�̍ő吔

	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_offsetPos;			//�I�t�Z�b�g���W
	D3DXVECTOR3 m_worldPos;				//���[���h���W
	D3DXMATRIX	m_mtxWorld;				//���[���h�}�g���b�N�X
	D3DXMATRIX m_pMtxParent;			//�O�Ղ̐e���f���̃}�g���b�N�X
	D3DXCOLOR m_initCol;				//�F�̏����l
	int m_nNumVtx;						//���_��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
};

#endif