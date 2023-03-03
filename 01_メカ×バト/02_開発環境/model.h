//===================================================
//
// ���f���w�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _MODEL_H_
#define _MODEL_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object.h"

//--------------------------------
// �O���錾
//--------------------------------
class CLine;	//���C��

//================================
// ���f���N���X�̒�`
//================================
class CModel
{
public:
	//----------------
	// ���f���̎��
	//----------------
	enum MODELTYPE
	{
		NONE = 0,
		PLAYER,
		ENEMY,
		MAX
	};

	CModel();	//�R���X�g���N�^
	~CModel();	//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw(D3DMATRIX* mtxPlayer);

	//----------------
	// �Z�b�^�[
	//----------------
	void SetPos(D3DXVECTOR3 pos)	{ m_pos = pos; }		//�ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot)	{ m_rot = rot; }		//�����̐ݒ�
	void SetRotX(float rotX)		{ m_rot.x = rotX; };	//X���̉�]�ʂ�ݒ�
	void SetParent(CModel* pModel)	{ m_pModel = pModel; }	//�e���f���̐ݒ�

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPos()		{ return m_pos; }		//�ʒu�̎擾
	D3DXVECTOR3 GetRot()		{ return m_rot; }		//�����̎擾
	D3DXVECTOR3 GetInitPos()	{ return m_initPos; }	//�ʒu�̏����l�̎擾
	D3DXVECTOR3 GetInitRot()	{ return m_initRot; }	//�����̏����l�̎擾
	D3DXMATRIX GetmtxWorld()	{ return m_mtxWorld; }	//���[���h�}�g���b�N�X�̎擾
	LPD3DXMESH GetMesh()		{ return m_pMesh; };	//���b�V�����̎擾

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CModel* Create(
		LPCTSTR text, CModel* model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	void DrawShadow();	//�e�̕`��

private:
	//----------------
	// �萔
	//----------------
	static const int nMaxLine = 12;			//���̍ő吔

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxParent;		//�e�̃}�g���b�N�X
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_initPos;		//�ʒu�̏����l
	D3DXVECTOR3 m_initRot;		//�����̏����l
	CModel* m_pModel;			//�e���f���ւ̃|�C���^
	LPCTSTR m_modelName;		//���f���̃p�X
	MODELTYPE m_type;			//���
	CLine* m_pLine[nMaxLine];	//���C��
	D3DXVECTOR3 m_vtxMax;		//�傫���̍ő�l
	D3DXVECTOR3 m_vtxMin;		//�傫���̍ŏ��l
	D3DXVECTOR3 m_worldMin;		//���[���h��̍ő�l
	D3DXVECTOR3	m_worldMax;		//���[���h��̍ŏ��l

	/* �� ���f����� �� */
	LPD3DXMESH m_pMesh;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD m_nNumMat;			//�}�e���A�����̐�
};

#endif