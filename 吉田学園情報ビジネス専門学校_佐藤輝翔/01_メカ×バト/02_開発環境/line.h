//===================================================
//
// ���C���w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _LINE_H_
#define _LINE_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "object.h"

//--------------------------------
// �O���錾
//--------------------------------
class CObject3D;

//================================
// ���C���N���X�̒�`
//================================
class CLine : public CObject
{
public:
	CLine();			//�R���X�g���N�^
	~CLine() override;	//�f�X�g���N�^

	//--------------------
	// �����o�֐�
	//--------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//-------------------
	// �Z�b�^�[
	//-------------------
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	static CLine* CreateAll(CLine* line, int nNumber,
		D3DXVECTOR3 pos, D3DXVECTOR3 min, D3DXVECTOR3 max);
	void SetLinePos(int nNumber, D3DXVECTOR3 min, D3DXVECTOR3 max);

	//-------------------
	// �Q�b�^�[
	//-------------------
	D3DXVECTOR3 GetPosition() override { return m_pos; };	//�ʒu�̎擾
	float GetWidth() override { return 0.0f; };				//���̎擾
	float GetHeight() override { return 0.0f; };			//�����̎擾

	//--------------------
	// �ÓI�����o�֐�
	//--------------------
	static CLine* Create(D3DXVECTOR3 pos, D3DXVECTOR3 start
						, D3DXVECTOR3 end, D3DXCOLOR col);

private:
	//--------------------
	// �萔
	//--------------------
	static const int nMaxLine = 128;	//���̍ő吔

	//--------------------
	// �����o�ϐ�
	//--------------------
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_start;	//�n�_
	D3DXVECTOR3 m_end;		//�I�_
	D3DXCOLOR	m_col;		//�F
	D3DXMATRIX	m_mtxWorld;	//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	CObject3D*	m_pObject3D;//�I�u�W�F�N�g3D
};

#endif // !_LINE_H_