#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//テクスチャ赤
	uint32_t texAngry_ = 0;
	//テクスチャ黄
	uint32_t texSmile_ = 0;

	//3Dモデル赤
	Model* modelAngry_ = nullptr;
	//3Dモデル黄
	Model* modelSmile_ = nullptr;

	//ワールド変換赤
	WorldTransform worldTransformAngry_;
	//ワールド変換黄
	WorldTransform worldTransformSmile_;

	//ビュープロジェクション
	ViewProjection viewProjection_;
};
