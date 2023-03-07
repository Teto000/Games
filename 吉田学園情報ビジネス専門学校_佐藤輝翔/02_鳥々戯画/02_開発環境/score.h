//============================
//
// スコアヘッダー
// Author:Teruto Sato
//
//============================

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// スコアクラスの定義
//--------------------------
class CScore : public CObject2D
{
public:
	enum MODE
	{
		MODE_GAME = 0,	//ゲーム画面
		MODE_RESULT,	//リザルト画面
		MODE_MAX
	};

	CScore();				//コンストラクタ
	~CScore() override;		//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//ゲッター
	int GetScore();

	//----------------
	// 静的メンバ関数
	//----------------
	static CScore *Create(MODE mode);
	static void AddScore(int nValue);
	static void SetScore(int nScore);

private:
	//----------------
	// 定数
	//----------------
	static const int nMaxScore = 6;

	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;	//位置
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	float m_fSpace;		//間隔
	MODE  m_mode;		//モード

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_nScore;
	static int m_aPosTexU[nMaxScore];
	static int nNum;
};