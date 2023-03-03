//=====================================
//
// オブジェクトヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _OBJECT_H_
#define _OBJECT_H_	

//--------------------------
// インクルード
//--------------------------
#include <d3dx9.h>

//------------------------
// マクロ定義
//------------------------
#define MAX_OBJECT		(512)	//オブジェクトの最大数
#define MY_MAX_PRIORITY	(3)		//プライオリティの最大数

//--------------------------
// オブジェクトクラス
//--------------------------
class CObject
{
public:
	//------------------------
	// オブジェクトの種類
	//------------------------
	enum EObjType
	{
		OBJTYPE_PLAYER,		//プレイヤー
		OBJTYPE_ENEMY,		//敵
		OBJTYPE_BULLET,		//弾
		OBJTYPE_EXPLOSION,	//爆発
		OBJTYPE_HP,			//HP
		OBJTYPE_MP,			//MP
		OBJTYPE_SCORE,		//スコア
		OBJTYPE_EFFECT,		//エフェクト
		OBJTYPE_BG,			//背景
		OBJTYPE_BARRIER,	//バリア
		OBJTYPE_LEVEL,		//レベル
		OBJTYPE_EXP,		//経験値
		OBJTYPE_SKILL,		//スキル
		OBJTYPE_FADE,		//フェード
		OBJTYPE_ITEM,		//アイテム
		OBJTYPE_MAX,
	};

	//CObject();			//コンストラクタ
	explicit CObject(int nPriority);
	virtual ~CObject();	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void Release();

	//----------------
	// 静的メンバ関数
	//----------------
	//static void CreateAll();
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static int GetNumAll();

	CObject *GETObject(int nPriority, int nCnt);
	void SetObjType(EObjType ObjType);	//種類の設定
	EObjType GetObjType();				//種類の取得

	//ゲッター
	virtual D3DXVECTOR3 GetPosition() = 0;
	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;

private:
	//----------------
	// 静的メンバ変数
	//----------------
	static CObject *m_pObject[MY_MAX_PRIORITY][MAX_OBJECT];	//オブジェクト
	int m_nID;			//格納先の番号
	EObjType m_ObjType;	//オブジェクトの種類
};

#endif // !_OBJECT_H_