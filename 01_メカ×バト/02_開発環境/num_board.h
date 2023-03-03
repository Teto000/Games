//===================================================
//
// ���l�\��(�r���{�[�h)�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _NUM_BOARD_H_
#define _NUM_BOARD_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "billboard.h"

//================================
// �i���o�[�N���X
//================================
class CNumBoard : public CBillBoard
{
public:
	CNumBoard();				//�R���X�g���N�^
	~CNumBoard() override;	//�f�X�g���N�^

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
	void Set(int nDigit);	//���l�̐ݒ�
	void SetEnable(bool bEnable) { m_bDraw = bEnable; }	//�`�悷�邩�ǂ���

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CNumBoard* Create(D3DXVECTOR3 pos, int nValue);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	int m_nValue;	//���l
	int m_nDigit;	//����
	bool m_bDraw;	//�`��t���O
};

#endif