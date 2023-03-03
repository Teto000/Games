//===================================================
//
// �^�C�g���J�����w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _TITLE_CAMERA_H_	//���̃}�N������`����ĂȂ�������
#define _TITLE_CAMERA_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "main.h"

//================================
// �^�C�g���J�����N���X�̒�`
//================================
class CTitleCamera
{
public:
	CTitleCamera();	//�R���X�g���N�^
	~CTitleCamera();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	void Init();
	void Uninit();
	void Update();
	void SetCamera(LPDIRECT3DDEVICE9 pDevice);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_posV;			//���݂̎��_
	D3DXVECTOR3 m_posR;			//���݂̒����_
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_worldPosV;	//���[���h���W(���_)
	D3DXVECTOR3 m_worldPosR;	//���[���h���W(�����_)
	D3DXVECTOR3 m_posVDest;		//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;		//�ړI�̒����_
	D3DXVECTOR3 m_rotDest;		//�ړI�̊p�x
	D3DXVECTOR3 m_vecU;			//������x�N�g��
	D3DXVECTOR3 m_maxShake;		//�h��̍ő�l
	D3DXMATRIX  m_mtxWorld;		//���[���h�}�g���b�N�X
	float m_TSPEED;
	bool m_bLockOn;
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;

	//�J�����̐U��
	int m_nQuakeFreamCount;		//�h�炷�t���[����
	float m_fQuakeMagnitude;	//�h��̗�
};

#endif