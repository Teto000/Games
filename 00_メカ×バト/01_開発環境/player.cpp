//=============================================================
//
// �v���C���[�̏���
// Author:Teruto Sato
//
//=============================================================

//-------------------------------
// �C���N���[�h
//-------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "player.h"
#include "object.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "camera.h"
#include "debug_proc.h"
#include "model.h"
#include "game.h"
#include "line.h"
#include "enemy.h"
#include "hp.h"
#include "combo.h"
#include "damage.h"
#include "utility.h"
#include "sound.h"
#include "orbit.h"
#include "bullet.h"
#include "message.h"
#include "bg.h"

//-------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------
const float CPlayer::fDefaultAttack = 10.0f;	//��{�̍U����
const float CPlayer::fDefaultSpeed = 9.0f;		//��{�̑��x

//=============================
// �R���X�g���N�^
//=============================
CPlayer::CPlayer() : CObject(0)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O�̈ʒu
	m_Offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����ւ̃I�t�Z�b�g���W
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�傫���̍ő�l
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�傫���̍ŏ��l
	m_worldMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���[���h��̍ő�l
	m_worldMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���[���h��̍ŏ��l
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�傫��
	m_nNumCombo = 0;			//�R���{��
	m_nCntHit = 0;				//�q�b�g���𐔂���
	m_nHitTime = 0;				//�q�b�g�܂ł̎��Ԃ𐔂���
	m_nCntModeTime = 0;			//���[�h�I���܂ł̎��Ԃ𐔂���
	m_nAvoidTime = 0;			//�������
	m_nAvoidStan = 0;			//����d��
	m_nWheelRotValue = 0;		//�^�C���̉�]��
	m_nBulletTime = 0;			//�e�̔��ˎ���
	m_nCntAttack = 0;			//�A�����𐔂���
	m_fSizeWidth = 0.0f;		//�T�C�Y(��)
	m_fSizeDepth = 0.0f;		//�T�C�Y(���s��)
	m_fGravity = 0.0f;			//�d�͂̒l
	m_bFinishAttack = false;	//�_���[�W��^������
	m_bHit = false;				//1�q�b�g�������
	m_bNockBack = false;		//�m�b�N�o�b�N���Ă�����
	m_bEnhance = false;			//�Z�������������
	m_bCntAttack = false;		//�A�����𐔂�����
	m_type = MOTION_IDOL;		//���݂̃��[�V����
	m_pHP = nullptr;			//HP
	m_pCombo = nullptr;			//�R���{
	m_pDamage = nullptr;		//�_���[�W
	m_pOrbit = nullptr;			//�O��
	m_pBullet = nullptr;		//�e
	m_pMessage = nullptr;		//���b�Z�[�W
	m_pBg = nullptr;			//�w�i

	//�X�e�[�^�X
	m_status.nAttack = 0;			//�U����
	m_status.nAttackTime = 0;		//�U������
	m_status.nComboValue = 0;		//�R���{�̉��Z�l
	m_status.fSpeed = 0.0f;			//���x
	m_status.fLife = 0.0f;			//�̗�
	m_status.fRemLife = 0.0f;		//�c��̗�(%)
	m_status.fMaxLife = 0.0f;		//�ő�̗�
	m_status.bAvoidance = false;	//������

	//���f��
	for (int i = 0; i < MAX_PARTS; i++)
	{
		m_pModel[i] = nullptr;
	}

	/* �� ���[�V������� �� */
	m_nCurrentKey = 0;
	m_nCntMotion = 0;

	//-----------------------------------
	// �L�[�Z�b�g���̏�����
	//-----------------------------------
	for (int nCnt = 0; nCnt < MOTION_MAX; nCnt++)
	{
		for (int i = 0; i < MOTION_MAX; i++)
		{
			for (int j = 0; j < MAX_PARTS; j++)
			{
				m_aMotionSet[nCnt].aKeySet[i].aKey[j].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
				m_aMotionSet[nCnt].aKeySet[i].aKey[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
			}

			m_aMotionSet[nCnt].nStartCollision = 0;		//�����蔻��̊J�n����
			m_aMotionSet[nCnt].nNextAtkTime = 0;		//���̍U���̓��͊J�n����
			m_aMotionSet[nCnt].nNumPoint = 0;			//����|�C���g��
			m_aMotionSet[nCnt].nCritical = 0;			//�N���e�B�J����
			m_aMotionSet[nCnt].nNumHit = 0;				//�q�b�g��
			m_aMotionSet[nCnt].nHitInterval = 0;		//�q�b�g�Ԋu
			m_aMotionSet[nCnt].nBreakDamage = 0;		//�u���C�N�Q�[�W�ɗ^����_���[�W
			m_aMotionSet[nCnt].fDamageMag = 0.0f;		//�_���[�W�{��(magnification)

			m_aMotionSet[nCnt].aKeySet[i].nFrame = 0;	//�t���[����
		}

		m_aMotionSet[nCnt].nNumKey = 0;
		m_aMotionSet[nCnt].bLoop = false;
	}
}

//=============================
// �f�X�g���N�^
//=============================
CPlayer::~CPlayer()
{

}

//=============================
// ������
//=============================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	//---------------------------
	// �����l�̐ݒ�
	//---------------------------
	m_pos = pos;									//�ʒu
	m_Offset = D3DXVECTOR3(0.0f, -20.0f, -100.0f);	//����ւ̃I�t�Z�b�g���W
	m_rot.y = D3DX_PI;								//����
	m_fSizeWidth = 30.0f;							//���f���̕�
	m_fSizeDepth = 30.0f;							//���f���̉��s��
	m_nWheelRotValue = 10;							//�^�C���̉�]��
	m_status.fLife = 800.0f;						//�̗�
	m_status.fRemLife = 100.0f;						//�c��̗�(%)
	m_status.fMaxLife = m_status.fLife;				//�ő�̗�
	m_status.nAttack = 20;							//�U����
	m_nNumCombo = 0;								//�R���{��
	m_status.nComboValue = 1;						//�R���{�̉��Z�l
	m_status.fSpeed = 7.0f;							//���x

	//���������Ƃɂ��������_���Ȓl�𐶐�
	srand((unsigned int)time(NULL));

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxRot);

	//---------------------------
	// HP�̐���
	//---------------------------
	{
		D3DXVECTOR3 hpPos(300.0f, 650.0f, 0.0f);
		m_pHP = CHP::Create(hpPos, 500.0f, 60.0f, CHP::GAUGETYPE_HP_PLAYER);
		m_pHP->SetLife(m_status.fLife, m_status.fRemLife);	//HP�̐ݒ�
	}

	//---------------------------
	// ���f���̐���
	//---------------------------
	SetModel();

	//------------------------------
	// ���f���̑傫����ݒ�
	//------------------------------
	m_vtxMin = D3DXVECTOR3(-m_fSizeWidth, 10.0f, -m_fSizeDepth);
	m_vtxMax = D3DXVECTOR3(m_fSizeWidth, 150.0f, m_fSizeDepth);

	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;

	//------------------------------
	// ���[�V�����̓ǂݍ���
	//------------------------------
	GetFileMotion();

	//------------------------------
	// �R���{���\��
	//------------------------------
	m_pCombo = CCombo::Create(D3DXVECTOR3(1110.0f, 365.0f, 0.0f), m_nNumCombo);

	//--------------------------------
	// ���̋O�Ղ̕\��
	//--------------------------------
	m_pOrbit = COrbit::Create(m_Offset, m_pModel[4]->GetmtxWorld());

	return S_OK;
}

//=============================
// �I��
//=============================
void CPlayer::Uninit()
{
	//--------------------------------
	// ���f���̏I��
	//--------------------------------
	for (int i = 0; i < MAX_PARTS; i++)
	{//���f���p�[�c������
		if (m_pModel[i])
		{//���f����null����Ȃ��Ȃ�
			m_pModel[i]->Uninit();
			delete m_pModel[i];
			m_pModel[i] = nullptr;
		}
	}

	CObject::Release();
}

//=============================
// �X�V
//=============================
void CPlayer::Update()
{
	//1�O�̈ʒu��ۑ�
	m_posOld = m_pos;

	//--------------------------------
	// ���[�V�����̃��Z�b�g
	//--------------------------------
	if (GetOutAttack(false, true))
	{//�U�����[�V��������Ȃ��Ȃ�
		//�ҋ@���[�V�����ɂ���
		ChangeMotion(MOTION_IDOL);
	}

	//--------------------------------
	// ���f���̍X�V
	//--------------------------------
	for (int i = 0; i < MAX_PARTS; i++)
	{//���f���p�[�c������
		if (m_pModel[i])
		{//���f����null����Ȃ��Ȃ�
			m_pModel[i]->Update();
		}
	}

	if (!CGame::GetFinish() && CGame::GetStart() && !m_bNockBack)
	{//�I���t���O�������Ă��Ȃ� or �J�n�t���O�������Ă��� or �m�b�N�o�b�N��Ԃ���Ȃ��Ȃ�
		//--------------------------------
		// �ړ�
		//--------------------------------
		// �W���C�p�b�h�ł̑���
		CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

		if (GetOutAttack(false, true))
		{//�U��������Ȃ��Ȃ�
			if (!joypad->IsJoyPadUse(0))
			{//�W���C�p�b�h���g���Ă��Ȃ��Ȃ�
				MoveKeyboard(DIK_W, DIK_S, DIK_A, DIK_D);	//�L�[�{�[�h
			}
			else
			{
				MoveJoypad();	//�W���C�p�b�h
			}
		}

		//�ړ����E�̊m�F
		m_pos = CUtility::LimitMove(m_pos);

		//�^�C���̉�]
		m_pModel[0]->SetRotX(m_rotWheel);

		//������ړI�̊p�x�ɍ��킹��
		SetRot();

		//--------------------------------
		// �U������
		//--------------------------------
		AttackManager();

		//--------------------------------
		// �e�̔���
		//--------------------------------
		m_nBulletTime++;
		int nShotTime = 10;	//�e�𔭎˂���܂ł̎���

		if (m_type == MOTION_IDOL || m_type == MOTION_MOVE)
		{//�U���ȊO�̎��Ȃ�
			if (CInputKeyboard::Press(DIK_O) && m_nBulletTime >= nShotTime)
			{
				m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z));
				m_nBulletTime = 0;
			}
			else if (joypad->Press(CInputJoypad::JOYKEY_LEFT_SHOULDER) && m_nBulletTime >= nShotTime)
			{
				m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z));
				m_nBulletTime = 0;
			}
		}
	}
	else
	{//�I���t���O����������
		//�ҋ@���[�V�����ɂ���
		ChangeMotion(MOTION_IDOL);
	}

	//--------------------------------------
	// �����Ԃ̉���
	//--------------------------------------
	if (m_status.bAvoidance)
	{//�����ԂȂ�
		m_nAvoidTime++;				//������Ԃ̉��Z
		ChangeMotion(MOTION_MOVE);	//�ړ����[�V����

		if (m_nAvoidTime >= 14)
		{//��莞�Ԍo�߂�����
			m_status.fSpeed = fDefaultSpeed;	//����
			m_status.bAvoidance = false;		//������Ă��Ȃ����
			m_nAvoidTime = 0;					//������Ԃ̃��Z�b�g
			m_nAvoidStan = 15;					//����d���̐ݒ�
		}
	}
	else if (m_nAvoidStan > 0)
	{//����d����0����Ȃ�
		m_nAvoidStan--;		//�d�����Ԃ̌���
	}

	//--------------------------------
	// �d�͂̉��Z
	//--------------------------------
	if (m_pos.y > 0.0f)
	{//���ł���Ȃ�
		m_pos.y -= m_fGravity;
		m_fGravity += 0.1f;
	}
	else
	{//�n�ʂɒ�������
		m_pos.y = 0.0f;			//������n�ʂɍ��킹��
		m_fGravity = 0.0f;		//�d�͂̒l�����Z�b�g
		m_bNockBack = false;	//�m�b�N�o�b�N���Ă��Ȃ����
	}

	//--------------------------------
	// ���̋O�Ղ̍X�V
	//--------------------------------
	m_pOrbit->SetMtxParent(m_pModel[4]->GetmtxWorld());

	//--------------------------------
	// ���[�V�����̐ݒ�
	//--------------------------------
	SetMotion(m_type, m_aMotionSet[m_type].bLoop, m_aMotionSet[m_type].nNumKey);

	//--------------------------------
	// �G�Ƃ̓����蔻��
	//--------------------------------
	m_pos = CUtility::GetCollisionPos(m_pos, m_posOld, m_size, m_mtxWorld
		, CObject::OBJTYPE_ENEMY);

	CDebugProc::Print("�v���C���[�̈ʒu %f %f %f", m_pos.x, m_pos.y, m_pos.z);

#ifdef _DEBUG
	if (CInputKeyboard::Trigger(DIK_3))
	{
		//�̗͂̌���
		m_status.fLife = 10.0f;
		m_status.fRemLife = m_status.fLife * 100 / m_status.fMaxLife;
		m_pHP->SetLife(m_status.fLife, m_status.fRemLife);
	}
#endif // _DEBUG
}

//=============================
// �`��
//=============================
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���f���̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���f���̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//���f���̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//--------------------------------
	// ���f���̕`��
	//--------------------------------
	for (int i = 0; i < MAX_PARTS; i++)
	{//���f���p�[�c������
		if (!m_pModel[i])
		{//���f����null�Ȃ�
			return;
		}

		m_pModel[i]->Draw(&m_mtxWorld);
	}
}

//=============================
// ����
//=============================
CPlayer* CPlayer::Create()
{
	CPlayer *pPlayer = nullptr;

	//-----------------------------------------
	// �����Ə�����
	//-----------------------------------------
	pPlayer = new CPlayer;	//����

	if (pPlayer != nullptr)
	{//NULL�`�F�b�N
		//������
		pPlayer->Init(D3DXVECTOR3(0.0f, 0.0f, -300.0f));
		pPlayer->SetObjType(OBJTYPE_PLAYER);
	}

	return pPlayer;
}

//==========================================
// �ړ�
// �����F��L�[,���L�[,���L�[,�E�L�[
//==========================================
void CPlayer::MoveKeyboard(int nUpKey, int nDownKey, int nLeftKey, int nRightKey)
{
	//�J�����̏��擾
	D3DXVECTOR3 cameraRot = CGame::GetCamera()->GetRot();

	//--------------------------------------
	// ������鏈��
	//--------------------------------------
	if (CInputKeyboard::Trigger(DIK_P)
		&& !m_status.bAvoidance && m_nAvoidStan <= 0)
	{//�L�[�������ꂽ & �����Ԃ���Ȃ� & ����d����0�ȉ��Ȃ�
		m_status.fSpeed *= 4.0f;		//����
		m_status.bAvoidance = true;		//������
	}

	//--------------------------------------
	// �v���C���[�̑���
	//--------------------------------------
	if (CInputKeyboard::Press(nLeftKey))
	{//A�L�[�������ꂽ
		if (CInputKeyboard::Press(nUpKey))
		{//W�L�[�������ꂽ
			m_pos.x += sinf(cameraRot.y - D3DX_PI * 0.25f) * m_status.fSpeed;	//�����ړ�
			m_pos.z += cosf(cameraRot.y - D3DX_PI * 0.25f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y + D3DX_PI * 0.75f;	//�����̐؂�ւ�
		}
		else if (CInputKeyboard::Press(nDownKey))
		{//S�L�[�������ꂽ
			m_pos.x += sinf(cameraRot.y - D3DX_PI * 0.75f) * m_status.fSpeed;	//���O�ړ�
			m_pos.z += cosf(cameraRot.y - D3DX_PI * 0.75f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{
			m_pos.x -= sinf(cameraRot.y + D3DX_PI * 0.5f) * m_status.fSpeed;	//���ړ�
			m_pos.z -= cosf(cameraRot.y + D3DX_PI * 0.5f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y + D3DX_PI * 0.5f;
		}
	}
	else if (CInputKeyboard::Press(nRightKey))
	{//D�L�[�������ꂽ
		if (CInputKeyboard::Press(nUpKey))
		{//W�L�[�������ꂽ
			m_pos.x += sinf(cameraRot.y + D3DX_PI * 0.25f) * m_status.fSpeed;	//�E���ړ�
			m_pos.z += cosf(cameraRot.y + D3DX_PI * 0.25f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y - D3DX_PI * 0.75f;
		}
		else if (CInputKeyboard::Press(nDownKey))
		{//S�L�[�������ꂽ
			m_pos.x += sinf(cameraRot.y + D3DX_PI * 0.75f) * m_status.fSpeed;	//�E�O�ړ�
			m_pos.z += cosf(cameraRot.y + D3DX_PI * 0.75f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y - D3DX_PI * 0.25f;
		}
		else
		{
			m_pos.x += sinf(cameraRot.y + D3DX_PI * 0.5f) * m_status.fSpeed;	//�E�ړ�
			m_pos.z += cosf(cameraRot.y + D3DX_PI * 0.5f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y - D3DX_PI * 0.5f;
		}
	}
	else if (CInputKeyboard::Press(nUpKey))
	{//W�L�[�������ꂽ
		m_pos.x -= sinf(cameraRot.y + D3DX_PI * 1.0f) * m_status.fSpeed;	//���ړ�
		m_pos.z -= cosf(cameraRot.y + D3DX_PI * 1.0f) * m_status.fSpeed;
		m_rotDest.y = cameraRot.y + D3DX_PI * 1.0f;
	}
	else if (CInputKeyboard::Press(nDownKey))
	{//S�L�[�������ꂽ
		m_pos.x -= sinf(cameraRot.y + D3DX_PI * 0.0f) * m_status.fSpeed;	//�O�ړ�
		m_pos.z -= cosf(cameraRot.y + D3DX_PI * 0.0f) * m_status.fSpeed;
		m_rotDest.y = cameraRot.y + D3DX_PI * 0.0f;
	}
	else if (m_status.bAvoidance)
	{//����������Ă��Ȃ� & �����ԂȂ�
		m_pos.x -= sinf(cameraRot.y + D3DX_PI * 1.0f) * m_status.fSpeed;
		m_pos.z -= cosf(cameraRot.y + D3DX_PI * 1.0f) * m_status.fSpeed;
		m_rotDest.y = cameraRot.y + D3DX_PI * 1.0f;
	}
	
	//�^�C���̉�]�ʂ̉��Z
	m_rotWheel += D3DXToRadian(-m_nWheelRotValue);

	//--------------------------------------
	// �L�[������Ԃ̏���
	//--------------------------------------
	if (!CInputKeyboard::Press(nUpKey) && !CInputKeyboard::Press(nDownKey)
		&& !CInputKeyboard::Press(nRightKey) && !CInputKeyboard::Press(nLeftKey))
	{//�ړ��L�[��������Ă��Ȃ��Ȃ�
		//�^�C���̉�]�ʂ�0�ɂ���
		m_rotWheel = 0;
	}
	else
	{//�ǂꂩ��������Ă���Ȃ�
		//�ړ����[�V�����ɂ���
		ChangeMotion(MOTION_MOVE);
	}
}

//================================
// �W���C�p�b�h���g�����ړ�
//================================
void CPlayer::MoveJoypad()
{
	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();
	D3DXVECTOR3 stick = joypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0);

	if (joypad->IsJoyPadUse(0) == false)
	{//�W���C�p�b�h���g���Ă��Ȃ��Ȃ�
		return;
	}

	//�X�e�B�b�N�𓮂����l�̐ݒ�
	float fMoveValue = 0.5f;

	//�J�����̏��擾
	D3DXVECTOR3 cameraRot = CGame::GetCamera()->GetRot();

	//--------------------------------------
	// ������鏈��
	//--------------------------------------
	if (joypad->Trigger(CInputJoypad::JOYKEY_A)
		&& !m_status.bAvoidance && m_nAvoidStan <= 0)
	{//�L�[�������ꂽ & �����Ԃ���Ȃ� & ����d����0�ȉ��Ȃ�
		m_status.fSpeed *= 4.0f;		//����
		m_status.bAvoidance = true;		//������
	}

	//------------------------------------------
	// �E�ړ�
	//------------------------------------------
	if (stick.x >= fMoveValue)
	{
		// �X�e�B�b�N��|���������ֈړ�����
		if (stick.y <= -fMoveValue)
		{//�E���ړ�
			m_pos.x += sinf(cameraRot.y + D3DX_PI * 0.25f) * m_status.fSpeed;
			m_pos.z += cosf(cameraRot.y + D3DX_PI * 0.25f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y - D3DX_PI * 0.75f;	//�����̐؂�ւ�
		}
		else if (stick.y >= fMoveValue)
		{//�E�O�ړ�
			m_pos.x += sinf(cameraRot.y + D3DX_PI * 0.75f) * m_status.fSpeed;
			m_pos.z += cosf(cameraRot.y + D3DX_PI * 0.75f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y - D3DX_PI * 0.25f;
		}
		else
		{
			m_pos.x += sinf(cameraRot.y + D3DX_PI * fMoveValue) * m_status.fSpeed;
			m_pos.z += cosf(cameraRot.y + D3DX_PI * fMoveValue) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y - D3DX_PI * fMoveValue;
		}
	}
	//------------------------------------------
	// ���ړ�
	//------------------------------------------
	else if (stick.x <= -fMoveValue)
	{
		if (stick.y <= -fMoveValue)
		{//�����ړ�
			m_pos.x += sinf(cameraRot.y - D3DX_PI * 0.25f) * m_status.fSpeed;
			m_pos.z += cosf(cameraRot.y - D3DX_PI * 0.25f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y + D3DX_PI * 0.75f;
		}
		else if (stick.y >= fMoveValue)
		{//���O�ړ�
			m_pos.x += sinf(cameraRot.y - D3DX_PI * 0.75f) * m_status.fSpeed;
			m_pos.z += cosf(cameraRot.y - D3DX_PI * 0.75f) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{
			m_pos.x -= sinf(cameraRot.y + D3DX_PI * fMoveValue) * m_status.fSpeed;
			m_pos.z -= cosf(cameraRot.y + D3DX_PI * fMoveValue) * m_status.fSpeed;
			m_rotDest.y = cameraRot.y + D3DX_PI * fMoveValue;
		}
	}
	//------------------------------------------
	// ���ړ�
	//------------------------------------------
	else if (stick.y <= -fMoveValue)
	{
		m_pos.x -= sinf(cameraRot.y + D3DX_PI * 1.0f) * m_status.fSpeed;
		m_pos.z -= cosf(cameraRot.y + D3DX_PI * 1.0f) * m_status.fSpeed;
		m_rotDest.y = cameraRot.y + D3DX_PI * 1.0f;
	}
	//------------------------------------------
	// �O�ړ�
	//------------------------------------------
	else if (stick.y >= fMoveValue)
	{
		m_pos.x -= sinf(cameraRot.y + D3DX_PI * 0.0f) * m_status.fSpeed;
		m_pos.z -= cosf(cameraRot.y + D3DX_PI * 0.0f) * m_status.fSpeed;
		m_rotDest.y = cameraRot.y + D3DX_PI * 0.0f;
	}
	else if (m_status.bAvoidance)
	{//����������Ă��Ȃ� & �����ԂȂ�
		m_pos.x -= sinf(cameraRot.y + D3DX_PI * 1.0f) * m_status.fSpeed;
		m_pos.z -= cosf(cameraRot.y + D3DX_PI * 1.0f) * m_status.fSpeed;
		m_rotDest.y = cameraRot.y + D3DX_PI * 1.0f;
	}

	//�^�C���̉�]�ʂ̉��Z
	m_rotWheel += D3DXToRadian(-m_nWheelRotValue);

	if (stick.x < fMoveValue && stick.x > -fMoveValue
		&& stick.y < fMoveValue && stick.y > -fMoveValue)
	{//�X�e�B�b�N����������Ă��Ȃ��Ȃ�
		//�^�C���̉�]�ʂ�0�ɂ���
		m_rotWheel = 0;
	}
	else
	{//�ǂꂩ��������Ă���Ȃ�
	 //�ړ����[�V�����ɂ���
		ChangeMotion(MOTION_MOVE);
	}
}

//================================
// �p�x�̐ݒ�
//================================
void CPlayer::SetRot()
{
	//--------------------------------------
	// ��ɓG�̕���������
	//--------------------------------------
	if (CGame::GetCamera()->GetLockOn())
	{//���b�N�I����ԂȂ�
		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 playerPos(CGame::GetEnemy()->GetPosition());

		//2�_�Ԃ̋��������߂�
		float X = m_pos.x - playerPos.x;
		float Z = m_pos.z - playerPos.z;

		//�p�x�̐ݒ�
		float angle = atan2f(X, Z);

		//�����̐ݒ�
		m_rotDest = D3DXVECTOR3(0.0f, angle, 0.0f);
	}

	//--------------------------------------
	// �ړI�̊p�x�̐��K��
	//--------------------------------------
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{//��]�������p�x��180�ȏ�Ȃ�
		m_rotDest.y -= D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{//��]�������p�x��-180�ȉ��Ȃ�
		m_rotDest.y += D3DX_PI * 2;
	}

	//--------------------------------------
	// �ړI�̊p�x�܂ŉ�]����
	//--------------------------------------
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.08f;	//��������

	//--------------------------------------
	// �p�x�̐��K��
	//--------------------------------------
	m_rot.y = CUtility::GetNorRot(m_rot.y);
}

//================================
// �U���̊Ǘ�
//================================
void CPlayer::AttackManager()
{
	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//�U���L�[�p�ϐ��錾
	int nNorAtkKey = DIK_U;
	int nSpinAtkKey = DIK_I;

	//--------------------------------
	// �U��������Ԃ̉���
	//--------------------------------
	if (CInputKeyboard::Release(DIK_LSHIFT)						//�L�[�������ꂽ
		|| joypad->Release(CInputJoypad::JOYKEY_RIGHT_SHOULDER)	//�{�^���������ꂽ
		|| m_nNumCombo < nNeedEnhanceCombo)						//�R���{��������Ă��Ȃ�
	{
		//�񋭉����
		m_bEnhance = false;
	}

	switch (m_type)
	{
	//------------------------------------------
	// �ҋ@���Ȃ�
	//------------------------------------------
	case MOTION_IDOL:
		if (CInputKeyboard::Trigger(nNorAtkKey) || joypad->Trigger(CInputJoypad::JOYKEY_B))
		{
			ChangeMotion(MOTION_ATTACK_1);
		}
		else if (CInputKeyboard::Trigger(nSpinAtkKey) || joypad->Trigger(CInputJoypad::JOYKEY_Y))
		{
			ChangeMotion(MOTION_ATTACK_SPIN);
		}

		//------------------------------------------
		// �U���̋���
		//------------------------------------------
		EnhanceAttack();
		break;

	//------------------------------------------
	// �ړ����Ȃ�
	//------------------------------------------
	case MOTION_MOVE:
		if (CInputKeyboard::Trigger(nNorAtkKey) || joypad->Trigger(CInputJoypad::JOYKEY_B))
		{
			ChangeMotion(MOTION_ATTACK_1);
		}
		else if (CInputKeyboard::Trigger(nSpinAtkKey) || joypad->Trigger(CInputJoypad::JOYKEY_Y))
		{
			ChangeMotion(MOTION_ATTACK_SPIN);
		}

		//------------------------------------------
		// �U���̋���
		//------------------------------------------
		EnhanceAttack();
		break;

	//------------------------------------------
	// �ʏ�U��(1)�Ȃ�
	//------------------------------------------
	case MOTION_ATTACK_1:
		if (CInputKeyboard::Trigger(nNorAtkKey) || joypad->Trigger(CInputJoypad::JOYKEY_B))
		{
			ChangeMotion(MOTION_ATTACK_2);
		}
		else if (CInputKeyboard::Trigger(nSpinAtkKey) || joypad->Trigger(CInputJoypad::JOYKEY_Y))
		{
			ChangeMotion(MOTION_ATTACK_SPIN);
		}
		break;

	//------------------------------------------
	// �ʏ�U��(2)�Ȃ�
	//------------------------------------------
	case MOTION_ATTACK_2:
		if (CInputKeyboard::Trigger(nSpinAtkKey) || joypad->Trigger(CInputJoypad::JOYKEY_Y))
		{
			ChangeMotion(MOTION_ATTACK_SPIN);
		}

		if (m_typeOld == MOTION_ATTACK_1)
		{//�U��1����̘A�g�Ȃ�
			//------------------------------
			// �A�����̉��Z
			//------------------------------
			if (!m_bCntAttack)
			{//�A���������Z�ł����ԂȂ�
				m_nCntAttack++;			//�A���������Z
				m_bCntAttack = true;	//�o���Ȃ���Ԃɂ���
			}

			//------------------------------
			// �U���̋���
			//------------------------------
			EnhanceAttack();
		}
		break;

	//------------------------------------------
	// ��]�؂�Ȃ�
	//------------------------------------------
	case MOTION_ATTACK_SPIN:
		if (m_typeOld == MOTION_ATTACK_1
			|| m_typeOld == MOTION_ATTACK_2)
		{//�U��1 �� �U��2 ����̘A�g�Ȃ�
			//------------------------------
			// �A�����̉��Z
			//------------------------------
			if (!m_bCntAttack)
			{//�A���������Z�ł����ԂȂ�
				m_nCntAttack++;			//�A���������Z
				m_bCntAttack = true;	//�o���Ȃ���Ԃɂ���
			}

			//------------------------------
			// �U���̋���
			//------------------------------
			EnhanceAttack();
		}
		break;

	default:
		break;
	}

	//�U������
	Attack();
}

//================================
// �U�����������鏈��
//================================
void CPlayer::EnhanceAttack()
{
	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	if (CInputKeyboard::Press(DIK_LSHIFT)						//�L�[�������ꂽ
		|| joypad->Press(CInputJoypad::JOYKEY_RIGHT_SHOULDER))	//�{�^���������ꂽ
	{
		if (m_nNumCombo >= nNeedEnhanceCombo)
		{//�R���{��������Ă���Ȃ�
			//�������
			m_bEnhance = true;
		}
	}
}

//================================
// �U������
//================================
void CPlayer::Attack()
{
	//------------------------------------------
	// �U������������Ă��鎞�̏���
	//------------------------------------------
	if (m_bEnhance)
	{//�U��������������ԂȂ�
		//�O�Ղ̐F�̕ύX
		m_pOrbit->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f));

		//�O�Ղ̒�����ݒ�
		m_pOrbit->SetOffset(D3DXVECTOR3(0.0f, -20.0f, -300.0f));
	}

	if (GetOutAttack(false, true))
	{//�U�����[�V����������Ȃ��Ȃ�
		return;
	}

	//------------------------------------------
	// ���[�V�����ƍU�����Ԃ����킹��
	//------------------------------------------
	int nAttackFream = 0;
	int nOutRigor = 0;
	for (int i = 0; i < m_aMotionSet[m_type].nNumKey; i++)
	{//�L�[��-1�񕪉�
		//�U�����[�V�����̃t���[���������v����
		nAttackFream += m_aMotionSet[m_type].aKeySet[i].nFrame;

		if (i != m_aMotionSet[m_type].nNumKey - 1)
		{//�d���L�[����Ȃ��Ȃ�
			//�t���[���������Z
			nOutRigor += m_aMotionSet[m_type].aKeySet[i].nFrame;
		}
	}

	//------------------------------------------
	// �t���[�����̉��Z
	//------------------------------------------
	if (nAttackFream <= m_status.nAttackTime)
	{//�U�����Ԃ��U�����[�V�����̃t���[�����̍��v�𒴂�����
		//�A���������Z�b�g
		m_nCntAttack = 0;

		//�ҋ@���[�V�����ɂ���
		ChangeMotion(MOTION_IDOL);
	}
	else
	{
		//�U�����Ԃ����Z
		m_status.nAttackTime++;
	}

	//------------------------------------------
	// ���Ƃ̓����蔻��
	//------------------------------------------
	HitSword();
}

//================================
// ���Ƃ̓����蔻��
//================================
void CPlayer::HitSword()
{
	//-------------------------------
	// �����蔻��̑傫����ݒ�
	//-------------------------------
	float fSphereSize;	//���̒��a

	if (m_bEnhance)
	{//������ԂȂ�
		fSphereSize = 500.0f;
	}
	else
	{//������Ԃ���Ȃ��Ȃ�
		fSphereSize = 250.0f;
	}

	if (CUtility::ColliaionWeapon(m_Offset, fSphereSize, m_pModel[4]->GetmtxWorld(), CObject::OBJTYPE_ENEMY)
		&& !m_bFinishAttack
		&& m_status.nAttackTime >= m_aMotionSet[m_type].nStartCollision)
	{//���Ɠ������Ă��� & �U�����I����Ă��Ȃ� & �����蔻��̗L�����ԂȂ�
		//---------------------------------
		// �w��񐔃q�b�g�����鏈��
		//---------------------------------
		if (!m_bHit)
		{//�U�����������Ă��Ȃ��Ȃ�
			//-----------------------------------
			// �Z���Ƃ̃_���[�W�ʂ��v�Z
			//-----------------------------------
			float fDamage = m_status.nAttack * m_aMotionSet[m_type].fDamageMag;
			float fBreakDamage = (float)m_aMotionSet[m_type].nBreakDamage;
			float fComboDamage = (float)m_nNumCombo / 30;

			//�R���{���ɉ����ă_���[�W�A�b�v
			fDamage += fDamage * fComboDamage;

			//�A�����ɉ����ă_���[�W�A�b�v
			fDamage += (10 * m_nCntAttack);

			//-----------------------------------
			// �R���{������ċ��U��
			//-----------------------------------
			if (m_bEnhance)
			{//���U���Ȃ�
				//�_���[�W�A�b�v
				fDamage *= 3.0f;

				//�u���C�N�_���[�W�A�b�v
				fBreakDamage *= 3.0f;
			}

			//-----------------------------
			// �N���e�B�J�����ǂ���
			//-----------------------------
			int nRand = rand() % 101;	//0%�`100%�̒l
			bool bCritical = false;
			if (nRand <= m_aMotionSet[m_type].nCritical)
			{//�����_���Ȓl���N���e�B�J�����ȓ��Ȃ�
				bCritical = true;	//�N���e�B�J����Ԃɂ���
			}

			//-----------------------------
			// �u���C�N��Ԃ��ǂ���
			//-----------------------------
			if (CGame::GetEnemy()->GetState() == CEnemy::ENEMYSTATE_BREAK)
			{//�G���u���C�N��ԂȂ�
				bCritical = true;	//�N���e�B�J����Ԃɂ���
			}

			//-----------------------------
			// �_���[�W�A�b�v����
			//-----------------------------
			//�_���[�W�̕\���ʒu�������_���ɐݒ�
			int nWidth = 50;
			int nRandX = rand() % nWidth - (nWidth / 2);
			int nRandY = rand() % nWidth - (nWidth / 2);
			D3DXVECTOR3 damagePos(m_pos.x + (float)nRandX
								  , m_pos.y + 150.0f + (float)nRandY
								  , m_pos.z);

			if (bCritical)
			{//�N���e�B�J���Ȃ�
				fDamage *= 1.5f;	//�_���[�W1.5�{

				//�_���[�W���̕\��
				m_pDamage = CDamage::Create(damagePos, (int)fDamage, CDamage::DAMAGE_TYPE_CRITICAL);

				//SE�̍Đ�
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CRITICAL);
			}
			else
			{
				//�_���[�W���̕\��
				m_pDamage = CDamage::Create(damagePos, (int)fDamage, CDamage::DAMAGE_TYPE_NONE);

				//SE�̍Đ�
				CSound::PlaySound(CSound::SOUND_LABEL_SE_HIT);
			}

			//-----------------------------
			// �_���[�W��^���鏈��
			//-----------------------------
			if (CGame::GetEnemy()->GetState() != CEnemy::ENEMYSTATE_BREAK)
			{//�G���u���C�N��Ԃ���Ȃ��Ȃ�
				//�̗͂�����
				CGame::GetEnemy()->SubGauge(fDamage, CEnemy::GAUGE_HP);

				//�u���C�N�Q�[�W�̌���
				CGame::GetEnemy()->SubGauge(fBreakDamage, CEnemy::GAUGE_BREAK);
			}
			else
			{//�u���C�N��ԂȂ�
				//�G�̗̑͂�����
				CGame::GetEnemy()->SubGauge(fDamage, CEnemy::GAUGE_HP);
			}

			//-----------------------------
			// �R���{���̉��Z
			//-----------------------------
			CGame::GetPlayer()->AddCombo(m_status.nComboValue);

			//------------------------------
			// �U���̏I������
			//------------------------------
			m_nCntHit++;	//�q�b�g�������Z
			m_bHit = true;	//�U���������������

			if (m_nCntHit >= m_aMotionSet[m_type].nNumHit)
			{//���݂̃q�b�g�����U���̃q�b�g���ȏ�Ȃ�
				m_bFinishAttack = true;	//�U�����I�������Ԃɂ���
				m_nCntHit = 0;			//�q�b�g�������Z�b�g

				if (m_bEnhance)
				{//���U���������Ȃ�
					//�R���{���̏���
					m_nNumCombo = m_pCombo->AddNumber(-nNeedEnhanceCombo);

					//�O�Ղ̒�����ݒ�
					m_pOrbit->SetOffset(m_Offset);
				}
			}
		}
		else if (m_bHit && m_nHitTime >= m_aMotionSet[m_type].nHitInterval)
		{//�U������������ & �q�b�g�܂ł̎��Ԃ��q�b�g�Ԋu���傫���Ȃ�
			m_bHit = false;		//�U�����������Ă��Ȃ����
			m_nHitTime = 0;		//�q�b�g�܂ł̎��Ԃ����Z�b�g
		}
		else
		{
			m_nHitTime++;	//�q�b�g�܂ł̎��Ԃ𐔂���
		}
	}
}

//================================
// �U����Ԃ��ǂ�����Ԃ�
// �������Ftrue:== , false:!=
// �������Ftrue:&& , false:||
//================================
bool CPlayer::GetOutAttack(bool equal, bool and)
{
	if (equal)
	{//�U����ԂȂ�
		if (and)
		{
			//----------------------------
			// �U����ԑS���Ȃ�
			//----------------------------
			if (m_type == MOTION_ATTACK_1
				&& m_type == MOTION_ATTACK_2
				&& m_type == MOTION_ATTACK_SPIN)
			{
				return true;
			}
		}
		else
		{
			//----------------------------
			// �U����Ԃǂꂩ�Ȃ�
			//----------------------------
			if (m_type == MOTION_ATTACK_1
				|| m_type == MOTION_ATTACK_2
				|| m_type == MOTION_ATTACK_SPIN)
			{
				return true;
			}
		}
	}
	else
	{//�U����Ԃ���Ȃ��Ȃ�
		if (and)
		{
			//----------------------------
			// �U����ԑS������Ȃ��Ȃ�
			//----------------------------
			if (m_type != MOTION_ATTACK_1
				&& m_type != MOTION_ATTACK_2
				&& m_type != MOTION_ATTACK_SPIN)
			{
				return true;
			}
		}
		else
		{
			//----------------------------
			// �U����Ԃǂꂩ����Ȃ��Ȃ�
			//----------------------------
			if (m_type != MOTION_ATTACK_1
				|| m_type != MOTION_ATTACK_2
				|| m_type != MOTION_ATTACK_SPIN)
			{
				return true;
			}
		}
	}

	return false;
}

//================================
// �R���{���̉��Z
//================================
void CPlayer::AddCombo(int nNumber)
{
	m_nNumCombo = m_pCombo->AddNumber(nNumber);
}

//=============================
// HP�������̏���
//=============================
void CPlayer::AddLife(float fDamage)
{
	if (m_status.fLife + fDamage <= m_status.fMaxLife)
	{//�̗͂̍ő�l�𒴂��Ȃ��Ȃ�
		m_status.fLife += fDamage;	//�̗͂̌���
	}
	else
	{//������Ȃ�
		//�̗͂��ő�ɂ���
		m_status.fLife = m_status.fMaxLife;
	}

	//----------------------------
	// ���S������
	//----------------------------
	if (m_status.fLife <= 0)
	{//�̗͂��s������
		CGame::SetDeathPlayer();	//�v���C���[�����񂾏��
		
		//���b�Z�[�W�̕\��
		{
			D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
			m_pMessage = CMessage::Create(pos, 800.0f, 200.0f, CMessage::MESSAGE_GAMEOVER);
		}

		//������\������
		{
			D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
			m_pBg = CBg::Create(pos, CBg::BGTYPE_BLACK);
		}
	}

	//�c��̗͂��v�Z
	m_status.fRemLife = m_status.fLife * 100 / m_status.fMaxLife;

	//HP�̐ݒ�
	m_pHP->SetLife(m_status.fLife, m_status.fRemLife);
}

//==========================================
// �m�b�N�o�b�N���鏈��
//==========================================
void CPlayer::NockBack(float fHeight)
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 enemyPos = CGame::GetEnemy()->GetPosition();

	//�G�ƃv���C���[�Ԃ̃x�N�g�����v�Z
	D3DXVECTOR3 vec = enemyPos - m_pos;

	D3DXVec3Normalize(&vec, &vec);	//�x�N�g���̐��K��

	//�m�b�N�o�b�N
	m_pos += -vec * 2.0f;	//�t�x�N�g�������Ɉړ�
	m_pos.y += fHeight;		//�㏸
	m_bNockBack = true;
}

//=============================
// ���f���̐���
//=============================
void CPlayer::SetModel()
{
	//���f��0�F�^�C��
	m_pModel[0] = CModel::Create("data\\MODEL\\Player\\wheel.x", nullptr,
		D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���f��1�F��
	m_pModel[1] = CModel::Create("data\\MODEL\\Player\\body.x", nullptr,
		D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���f��2�F��
	m_pModel[2] = CModel::Create("data\\MODEL\\Player\\head.x", m_pModel[1],
		D3DXVECTOR3(0.0f, 105.0f, 12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���f��3�F�E�r
	m_pModel[3] = CModel::Create("data\\MODEL\\Player\\armR.x", m_pModel[1],
		D3DXVECTOR3(-25.0f, 85.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���f��4�F�E��
	m_pModel[4] = CModel::Create("data\\MODEL\\Player\\handR.x", m_pModel[3],
		D3DXVECTOR3(-4.0f, -40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���f��5�F���r
	m_pModel[5] = CModel::Create("data\\MODEL\\Player\\armL.x", m_pModel[1],
		D3DXVECTOR3(25.0f, 85.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���f��6�F����
	m_pModel[6] = CModel::Create("data\\MODEL\\Player\\handL.x", m_pModel[5],
		D3DXVECTOR3(4.0f, -40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//==========================================
// �t�@�C�����烂�[�V���������擾
//==========================================
void CPlayer::GetFileMotion()
{
	const int nMaxText = 256;	//�����̍ő吔

	FILE *pFile;				//�t�@�C���|�C���^��錾����
	char cText[nMaxText];		//1�s���̕����ǂݎ��p�ϐ�
	char cTextHead[nMaxText];	//�����������悤�̕ϐ�
	int nNumMotion = 0;			//�ǂݍ��ݒ��̃��[�V�����ԍ�
	int nNumKey = 0;			//�ǂݍ��ݒ��̃L�[�ԍ�
	int nNumParts = 0;			//�ǂݍ��ݒ��̃p�[�c�ԍ�

	//--------------------------------
	// �t�@�C���̓ǂݍ���
	//--------------------------------
	//�t�@�C�����J��
	pFile = fopen("data/MOTION/player.txt", "r");

	if (pFile == nullptr)
	{//�J���Ȃ�������
		assert(false);
	}

	//�����̓ǂݎ�菈��
	while (fgets(cText, nMaxText, pFile) != nullptr)
	{
		//������̕���
		sscanf(cText, "%s", &cTextHead);

		//========================================
		// ���[�V�������
		//========================================
		if (strcmp(&cTextHead[0], "MOTIONSET") == 0)
		{//��������MOTIONSET�Ȃ�
			//�����̓ǂݎ�菈��
			while (fgets(cText, nMaxText, pFile) != nullptr)
			{
				//������̕���
				sscanf(cText, "%s", &cTextHead);

				//-------------------------------
				// ���[�v���邩�ǂ���
				//-------------------------------
				if (strcmp(&cTextHead[0], "LOOP") == 0)
				{//��������LOOP�Ȃ�
					int nLoop = 0;

					//�����񂩂烋�[�v�̒l��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &nLoop);

					if (nLoop == 0)
					{//�ǂݎ�����l��0�Ȃ�
						m_aMotionSet[nNumMotion].bLoop = false;
					}
					else if (nLoop == 1)
					{//�ǂݎ�����l��1�Ȃ�
						m_aMotionSet[nNumMotion].bLoop = true;
					}
				}
				//-------------------------------
				// �����蔻��̊J�n����
				//-------------------------------
				else if (strcmp(&cTextHead[0], "COLLISION") == 0)
				{//��������COLLISION�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nStartCollision);
				}
				//-------------------------------
				// ���̍U�����͊J�n����
				//-------------------------------
				else if (strcmp(&cTextHead[0], "NEXT_ATTACK") == 0)
				{//��������NEXT_ATTACK�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nNextAtkTime);
				}
				//-------------------------------
				// �U���ɕK�v�ȃ|�C���g��
				//-------------------------------
				else if (strcmp(&cTextHead[0], "NUM_POINT") == 0)
				{//��������NUM_POINT�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nNumPoint);
				}
				//-------------------------------
				// �N���e�B�J����
				//-------------------------------
				else if (strcmp(&cTextHead[0], "CRITICAL") == 0)
				{//��������CRITICAL�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nCritical);
				}
				//-------------------------------
				// �q�b�g��
				//-------------------------------
				else if (strcmp(&cTextHead[0], "NUM_HIT") == 0)
				{//��������NUM_HIT�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nNumHit);
				}
				//-------------------------------
				// �q�b�g�Ԋu
				//-------------------------------
				else if (strcmp(&cTextHead[0], "HIT_INTERVAL") == 0)
				{//��������HIT_INTERVAL�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nHitInterval);
				}
				//-------------------------------
				// �u���C�N�Q�[�W�ւ̃_���[�W
				//-------------------------------
				else if (strcmp(&cTextHead[0], "BREAK_DAMAGE") == 0)
				{//��������BREAK_DAMAGE�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nBreakDamage);
				}
				//-------------------------------
				// �_���[�W�{��
				//-------------------------------
				else if (strcmp(&cTextHead[0], "DAMAGE_MAG") == 0)
				{//��������DAMAGE_MAG�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %f", &cTextHead, &m_aMotionSet[nNumMotion].fDamageMag);
				}
				//-------------------------------
				// �L�[�̍ő吔
				//-------------------------------
				else if (strcmp(&cTextHead[0], "NUM_KEY") == 0)
				{//��������NUM_KEY�Ȃ�
					//�����񂩂�L�[�̍ő吔��ǂݎ��
					sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].nNumKey);
				}
				//========================================
				// �L�[�Z�b�g���
				//========================================
				else if (strcmp(&cTextHead[0], "KEYSET") == 0)
				{//��������KEYSET�Ȃ�
					//�����̓ǂݎ�菈��
					while (fgets(cText, nMaxText, pFile) != nullptr)
					{
						//������̕���
						sscanf(cText, "%s", &cTextHead);

						//-------------------------------
						// �t���[����
						//-------------------------------
						if (strcmp(&cTextHead[0], "FRAME") == 0)
						{//��������FRAME�Ȃ�
							//�����񂩂�L�[�̍ő吔��ǂݎ��
							sscanf(cText, "%s = %d", &cTextHead, &m_aMotionSet[nNumMotion].aKeySet[nNumKey].nFrame);
						}
						//========================================
						// �L�[���
						//========================================
						else if (strcmp(&cTextHead[0], "KEY") == 0)
						{//��������KEY�Ȃ�
							//�����̓ǂݎ�菈��
							while (fgets(cText, nMaxText, pFile) != nullptr)
							{
								//������̕���
								sscanf(cText, "%s", &cTextHead);

								//-------------------------------
								// �ʒu
								//-------------------------------
								if (strcmp(&cTextHead[0], "POS") == 0)
								{//��������POS�Ȃ�
									//�����񂩂�ʒu��ǂݎ��
									sscanf(cText, "%s = %f %f %f", &cTextHead,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].pos.x,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].pos.y,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].pos.z);
								}
								//-------------------------------
								// ����
								//-------------------------------
								else if (strcmp(&cTextHead[0], "ROT") == 0)
								{//��������ROT�Ȃ�
									//�����񂩂������ǂݎ��
									sscanf(cText, "%s = %f %f %f", &cTextHead,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].rot.x,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].rot.y,
										&m_aMotionSet[nNumMotion].aKeySet[nNumKey].aKey[nNumParts].rot.z);
								}
								else if (strcmp(&cTextHead[0], "END_KEY") == 0)
								{//�L�[�̓ǂݎ�肪�I��������
									if (nNumParts + 1 < MAX_PARTS)
									{//�p�[�c���𒴂��Ȃ��Ȃ�
										//�p�[�c�ԍ��̉��Z
										nNumParts++;
									}
									else
									{//�p�[�c�����ǂݍ��񂾂�
										//�p�[�c�ԍ������Z�b�g
										nNumParts = 0;
									}
									break;
								}
							}
						}
						else if (strcmp(&cTextHead[0], "END_KEYSET") == 0)
						{//�L�[�Z�b�g�̓ǂݎ�肪�I��������
							if (nNumKey < m_aMotionSet[nNumMotion].nNumKey)
							{//�L�[�����ő傶��Ȃ��Ȃ�
								//�L�[�ԍ��̉��Z
								nNumKey++;
							}
							break;
						}
					}
				}
				else if (strcmp(&cTextHead[0], "END_MOTIONSET") == 0)
				{//���[�V�����̓ǂݎ�肪�I��������
					//�L�[�ԍ������Z�b�g
					nNumKey = 0;
					//���[�V�����ԍ��̉��Z
					nNumMotion++;
					break;
				}
			}
		}

		//----------------------------------
		// �ۑ����̕�����̏�����
		//----------------------------------
		ZeroMemory(&cText, sizeof(cText));
		ZeroMemory(&cTextHead, sizeof(cTextHead));
	}

	//�t�@�C�������
	fclose(pFile);
}

//==========================================
// ���[�V�����̐ݒ�
// �����F��ށA���[�v��ԁA�L�[��
//==========================================
void CPlayer::SetMotion(MOTION_TYPE type, bool bLoop, int nNumKey)
{
	if (m_nCurrentKey + 1 >= nNumKey)
	{//�L�[���ő吔�ɒB������
		if (bLoop)
		{//���[�v����Ȃ�
			m_nCurrentKey = 0;	//�L�[�ԍ��̏�����
		}
		else
		{
			return;
		}
	}

	for (int i = 1; i < MAX_PARTS; i++)
	{//���f���p�[�c������
		//-------------------------------------------------------
		// NULL�`�F�b�N
		//-------------------------------------------------------
		if (!m_pModel[i])
		{//���f���p�[�c��null�Ȃ�
			return;
		}

		//�L�[�����������ϐ�
		KEY key = m_aMotionSet[type].aKeySet[m_nCurrentKey].aKey[i];
		KEY keyNext = m_aMotionSet[type].aKeySet[m_nCurrentKey + 1].aKey[i];

		//-------------------------------------------------------
		// ���ݒl���擾
		//-------------------------------------------------------
		//�ʒu���擾
		float fPosX = m_pModel[i]->GetPos().x;
		float fPosY = m_pModel[i]->GetPos().y;
		float fPosZ = m_pModel[i]->GetPos().z;

		//�������擾
		float fRotX = m_pModel[i]->GetRot().x;
		float fRotY = m_pModel[i]->GetRot().y;
		float fRotZ = m_pModel[i]->GetRot().z;

		//-------------------------------------------------------
		// �����̌v�Z
		// (�I���l - �J�n�l)
		//-------------------------------------------------------
		//�ʒu
		float fDifPosX = keyNext.pos.x - key.pos.x;
		float fDifPosY = keyNext.pos.y - key.pos.y;
		float fDifPosZ = keyNext.pos.z - key.pos.z;

		//����
		float fDifRotX = keyNext.rot.x - key.rot.x;
		float fDifRotY = keyNext.rot.y - key.rot.y;
		float fDifRotZ = keyNext.rot.z - key.rot.z;

		//-------------------------------------------------------
		// �����̊p�x�̐��K��
		//-------------------------------------------------------
		fDifRotX = CUtility::GetNorRot(fDifRotX);	//X�̒l
		fDifRotY = CUtility::GetNorRot(fDifRotY);	//Y�̒l
		fDifRotZ = CUtility::GetNorRot(fDifRotZ);	//Z�̒l

		//-------------------------------------------------------
		// ���Βl�̌v�Z
		// (���[�V�����J�E���^�[ / �t���[����)
		//-------------------------------------------------------
		float fNumRelative = m_nCntMotion / (float)m_aMotionSet[type].aKeySet[m_nCurrentKey].nFrame;

		//-------------------------------------------------------
		// ���ݒl�̌v�Z
		// (�J�n�l + (���� * ���Βl))
		//-------------------------------------------------------
		//�����l�̎擾
		D3DXVECTOR3 initPos = m_pModel[i]->GetInitPos();
		D3DXVECTOR3 initRot = m_pModel[i]->GetInitRot();

		//�ʒu
		fPosX = initPos.x + key.pos.x + (fDifPosX * fNumRelative);
		fPosY = initPos.y + key.pos.y + (fDifPosY * fNumRelative);
		fPosZ = initPos.z + key.pos.z + (fDifPosZ * fNumRelative);

		//����
		fRotX = initRot.x + key.rot.x + (fDifRotX * fNumRelative);
		fRotY = initRot.y + key.rot.y + (fDifRotY * fNumRelative);
		fRotZ = initRot.z + key.rot.z + (fDifRotZ * fNumRelative);

		//-------------------------------------------------------
		// ���f�����̐ݒ�
		//-------------------------------------------------------
		//�ʒu�̐ݒ�
		m_pModel[i]->SetPos(D3DXVECTOR3(fPosX, fPosY, fPosZ));

		//�����̐ݒ�
		m_pModel[i]->SetRot(D3DXVECTOR3(fRotX, fRotY, fRotZ));
	}

	//���[�V�����J�E���^�[��i�߂�
	m_nCntMotion++;

	//--------------------------------
	// ������
	//--------------------------------
	if (m_nCntMotion >= m_aMotionSet[type].aKeySet[m_nCurrentKey].nFrame)
	{//���[�V�����J�E���^�[���Đ��t���[���ɒB������
		m_nCurrentKey++;	//�L�[�ԍ������Z
		m_nCntMotion = 0;	//���[�V�����J�E���^�[��������
	}
}

//==========================================
// ���[�V�����̕ύX
// �����F�ύX���������[�V�����̗�
//==========================================
void CPlayer::ChangeMotion(MOTION_TYPE type)
{
	m_typeOld = m_type;		//�O�̃��[�V������ۑ�

	m_type = type;			//���[�V�����̕ύX

	//�O�Ղ̒�����ݒ�
	m_pOrbit->SetOffset(m_Offset);

	//���[�V�������̏�����
	if (GetOutAttack(true, false))
	{//�ǂꂩ�U�����[�V�����Ȃ�
		//SE�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SLASH);

		m_nCurrentKey = 0;
		m_nCntMotion = 0;
		m_status.nAttackTime = 0;	//�U�����Ԃ̃��Z�b�g
		m_bFinishAttack = false;	//�_���[�W��^���Ă��Ȃ���Ԃɂ���
		m_bCntAttack = false;		//�A�����𐔂������Ԃɂ���

		if (m_nNumCombo < nNeedEnhanceCombo)
		{//�R���{��������Ȃ��Ȃ�
			m_bEnhance = false;		//�񋭉����
		}
	}
}