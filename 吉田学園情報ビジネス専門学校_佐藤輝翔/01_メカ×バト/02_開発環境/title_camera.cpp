//===================================================
//
// �J�����̏���
// Author:Teruto Sato
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "title_camera.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "debug_proc.h"
#include "utility.h"

//===========================
// �R���X�g���N�^
//===========================
CTitleCamera::CTitleCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TSPEED = 0.0f;
	m_bLockOn = true;

	//�J�����̐U��
	m_nQuakeFreamCount = 0;
	m_fQuakeMagnitude = 0.0f;
}

//===========================
// �f�X�g���N�^
//===========================
CTitleCamera::~CTitleCamera()
{

}

//========================
// �J�����̏���������
//========================
void CTitleCamera::Init(void)
{
	//---------------------------------
	// ���_�E�����_�E�������ݒ肷��
	//---------------------------------
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -400.0f);
	m_posR = D3DXVECTOR3(0.0f, 250.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_TSPEED = 0.02f;		//�J�����̉�]���x(Turn)
}

//========================
// �J�����̏I������
//========================
void CTitleCamera::Uninit(void)
{

}

//========================
// �J�����̍X�V����
//========================
void CTitleCamera::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//��]
	m_rot.y -= m_TSPEED / 7.0f;

	// ���E�̊p�x�̐��K��
	m_rot.y = CUtility::GetNorRot(m_rot.y);

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�s��ɉ�]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�s��Ɉړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_posV.x, m_posV.y, m_posV.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���[���h�ϊ��s����g����posV,posR�����߂�
	D3DXVec3TransformCoord(&m_worldPosR, &m_posR, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_worldPosV, &m_posV, &m_mtxWorld);
}

//========================
// �J�����̐ݒ菈��
//========================
void CTitleCamera::SetCamera(LPDIRECT3DDEVICE9 pDevice)
{
	//--------------------------------
	// �J�������̐ݒ�
	//--------------------------------
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
					   &m_worldPosV,	//���_
					   &m_worldPosR,	//�����_
					   &m_vecU);		//��̌���

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
							   D3DXToRadian(45.0f),	//����p
							   (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�A�X�y�N�g��
							   10.0f,		//near
							   100000.0f);	//far

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}