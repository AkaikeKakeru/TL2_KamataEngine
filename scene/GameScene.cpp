#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelAngry_;
	delete modelSmile_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//テクスチャを読み込む
	texAngry_ = TextureManager::Load("angry.dds");
	texSmile_ = TextureManager::Load("smile.dds");
	//モデル生成
	modelAngry_ = Model::Create();
	
	modelSmile_ = Model::Create();

	//ワールド変換初期化
	worldTransformAngry_.Initialize();
	worldTransformAngry_.matWorld_.m[3][0] += 10.0f;

	worldTransformSmile_.Initialize();
	worldTransformSmile_.matWorld_.m[3][0] -= 10.0f;

	worldTransformAngry_.TransferMatrix();
	worldTransformSmile_.TransferMatrix();

	//ビュープロジェクション初期化
	viewProjection_.Initialize();
}

void GameScene::Update() {

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//3Dモデル描画
	modelAngry_->Draw(worldTransformAngry_, viewProjection_, texAngry_);
	modelSmile_->Draw(worldTransformSmile_, viewProjection_, texSmile_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
