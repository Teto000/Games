//=====================================
//
// 背景のヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _BG_H_
#define _BG_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// バレットクラス
//--------------------------
class CBg : public CObject
{
public:
	enum BGTYPE
	{
		BGTYPE_GAME = 0,	//ゲーム画面
		BGTYPE_GAME_TIME,	//タイム
		BGTYPE_GAME_SCORE,	//スコア
		BGTYPE_TITLE,		//タイトル画面
		BGTYPE_TITLE_LOGO,	//タイトルロゴ
		BGTYPE_TITLE_ENTER,	//プレスエンター
		BGTYPE_RESULT,		//リザルト画面
		BGTYPE_RESULTTEXT,	//リザルトの文字
		BGTYPE_SELECTMODE,	//モード選択画面
		BGTYPE_TUTORIAL1,	//チュートリアル1
		BGTYPE_TUTORIAL2,	//チュートリアル2
		BGTYPE_MAX
	};

	CBg();				//コンストラクタ
	~CBg() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//ゲッター
	D3DXVECTOR3 GetPosition() override;		//位置の取得
	float GetWidth() override;				//幅の取得
	float GetHeight() override;				//高さの取得

	//----------------
	// 静的メンバ関数
	//----------------
	static CBg *Create(D3DXVECTOR3 pos, BGTYPE type);

private:
	//----------------
	// メンバ変数
	//----------------
	CObject2D *m_pObject2D;		//オブジェクト2D
	D3DXVECTOR3 m_pos;			//位置
	int m_nCntAnim;				//アニメーションカウント
	int m_nCntClear;			//透明にする時間カウント
	float m_fWidth;				//幅
	float m_fHeight;			//高さ
	float m_fTexLeft;			//テクスチャ座標左側
	float m_fTexRight;			//テクスチャ座標右側
	BGTYPE m_type;				//種類
};

#endif // !_BG_H_