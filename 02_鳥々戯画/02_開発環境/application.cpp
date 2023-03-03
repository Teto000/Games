//===================================
//
// アプリケーションの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "application.h"
#include "renderer.h"
#include "object2D.h"
#include "texture.h"
#include "sound.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "skillselect.h"
#include "fade.h"
#include "score.h"
#include "timer.h"
#include "tutorial.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CTitle*				CApplication::m_pTitle = nullptr;		//タイトルクラス
CGame*				CApplication::m_pGame = nullptr;		//ゲームクラス
CResult*			CApplication::m_pResult = nullptr;		//リザルトクラス
CTutorial*			CApplication::m_pTutorial = nullptr;	//チュートリアルクラス
CFade*				CApplication::m_pFade = nullptr;		//フェードクラス
CApplication::MODE	CApplication::m_mode = MODE_MAX;		//ゲームモード

CRenderer*	CApplication::m_pRenderer = nullptr;//レンダラー
CInput*		CApplication::m_pInput = nullptr;	//インプット
CInputJoypad*	CApplication::m_pJoypad = nullptr;		//ジョイパッド
CTexture*	CApplication::m_pTexture = nullptr;	//テクスチャ
CSound*		CApplication::m_pSound = nullptr;	//サウンド

int CApplication::m_nScore = 0;	//スコアの値
int CApplication::m_nTime = 0;	//タイムの値

//===========================
// コンストラクタ
//===========================
CApplication::CApplication()
{

}

//===========================
// デストラクタ
//===========================
CApplication::~CApplication()
{

}

//===========================
// 初期化
//===========================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	//--------------------------
	// インスタンスの生成
	//--------------------------
	m_pRenderer = new CRenderer;	//レンダリング
	m_pInput = new CInput;			//インプット
	m_pTexture = new CTexture;		//テクスチャ
	m_pSound = new CSound;			//サウンド

	//レンダリングの初期化
	if (FAILED(m_pRenderer->Init(hWnd, FALSE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//インプットの初期化
	m_pInput->Init(hInstance, hWnd);

	//----------------------------
	// ジョイパッドの生成と初期化
	//----------------------------
	m_pJoypad = new CInputJoypad;
	m_pJoypad->Init();

	//サウンドの初期化
	m_pSound->Init(hWnd);

	//モードの設定
	SetMode(MODE_TITLE);

	return S_OK;
}

//===========================
// 終了
//===========================
void CApplication::Uninit()
{
	//オブジェクトの全解放
	CObject::ReleaseAll();

	//テクスチャの終了
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//レンダリングの終了
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//インプットの終了
	if (m_pInput != nullptr)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = nullptr;
	}

	//----------------------------
	// ジョイパッドの終了処理
	//----------------------------
	if (m_pJoypad != nullptr)
	{
		m_pJoypad->Uninit();
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	//サウンドの終了
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

}

//===========================
// 更新
//===========================
void CApplication::Update()
{
	//インプットの更新
	m_pInput->Update();	//最初にやる

	//ジョイパッドの更新
	m_pJoypad->Update();

	//レンダリングの更新
	m_pRenderer->Update();

	//モードごとの更新
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Update();
		break;

	case MODE_GAME:
		m_pGame->Update();
		break;

	case MODE_RESULT:
		m_pResult->Update();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Update();
		break;

	default:
		break;
	}

	//フェードの更新
	m_pFade->Update();
}

//===========================
// 描画
//===========================
void CApplication::Draw()
{
	//レンダリングの描画
	m_pRenderer->Draw();

	//フェードの描画
	m_pFade->Draw();
}

//===========================
// モードの設定
//===========================
void CApplication::SetMode(MODE mode)
{
	//現在のモードを終了
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Uninit();
		break;

	case MODE_GAME:
		//スコアの取得
		m_nScore = m_pGame->GetScore()->GetScore();

		//タイムの取得
		m_nTime = m_pGame->GetTimer()->GetTime();

		m_pGame->Uninit();
		break;

	case MODE_RESULT:
		m_pResult->Uninit();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Uninit();
		break;

	default:
		break;
	}

	//オブジェクトの全解放
	CObject::ReleaseAll();

	//モードの切り替え
	m_mode = mode;

	//新しいモードの生成
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle = nullptr;
		m_pTitle = new CTitle;
		m_pTitle->Init();
		break;
	
	case MODE_GAME:
		m_pGame = nullptr;
		m_pGame = new CGame;
		m_pGame->Init();
		break;

	case MODE_RESULT:
		m_pResult = nullptr;
		m_pResult = new CResult;
		m_pResult->Init();
		m_pResult->GetScore()->SetScore(m_nScore);
		m_pResult->GetTimer()->SetTime(m_nTime);
		break;

	case MODE_TUTORIAL:
		m_pTutorial = nullptr;
		m_pTutorial = new CTutorial;
		m_pTutorial->Init();
		break;

	default:
		break;
	}

	//フェードの生成
	m_pFade = nullptr;
	m_pFade = new CFade;
	m_pFade->Init(m_mode);
}

//===========================
// モードの取得
//===========================
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}

//===========================
// レンダリングの取得
//===========================
CRenderer *CApplication::GetRenderer()
{
	return m_pRenderer;
}

//===========================
// インプットの取得
//===========================
CInput *CApplication::GetInput()
{
	return m_pInput;
}

//===========================
// テクスチャの取得
//===========================
CTexture *CApplication::GetTexture()
{
	return m_pTexture;
}

//===========================
// サウンドの取得
//===========================
CSound *CApplication::GetSound()
{
	return m_pSound;
}