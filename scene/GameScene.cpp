#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>


GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	//textureHandle_ = TextureManager::Load("kamata.ico");

	// 3Dモデルデータの生成
	
	// プレイヤー
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));
	modelWeapon_.reset(Model::CreateFromOBJ("hammer", true));

	// 敵
	modelNeedleBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	modelNeedleL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	modelNeedleR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));

	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));

	modelGround_.reset(Model::CreateFromOBJ("Ground", true));

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// デバッグカメラの生成
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(), modelWeapon_.get()
	};
	// 自キャラの初期化
	player_->Initialize(playerModels);

	// 敵キャラの生成
	enemy_ = std::make_unique<Enemy>();
	std::vector<Model*> enemyModels = {
	    modelNeedleBody_.get(), modelNeedleL_arm_.get(), modelNeedleR_arm_.get(),
	};
	
	// 敵キャラの初期化
	enemy_->Initialize(enemyModels);


	// 天球の生成
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_.get());

	// 地面の生成
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_.get());

	// 追従カメラの生成
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize(viewProjection_);
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(followCamera_->GetViewProjection());


}

void GameScene::Update() {

	// プレイヤーの更新
	player_->Update();

	// 敵の更新
	enemy_->Update();

	// 追従カメラの更新
	followCamera_->Update();

	viewProjection_.matView = followCamera_->GetViewProjection()->matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection()->matProjection;


	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_Q)) {
		if (isDebugCameraActive_ == false) {
			isDebugCameraActive_ = true;
		} else {
			isDebugCameraActive_ = false;
		}
	}
#endif // _DEBUG
	// カメラの処理
	if (isDebugCameraActive_ == true) {
		// デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		//railCamera_->Update(/*&viewProjection_*/);

		//viewProjection_.matView = railCamera_->GetViewProjection().matView;
		//viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
		
	}


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
	
	// 天球の描画
	skydome_->Draw(viewProjection_);
	
	// 地面の描画
	ground_->Draw(viewProjection_);

	// 自キャラの描画
	player_->Draw(viewProjection_);
	
	// 敵キャラの描画
	enemy_->Draw(viewProjection_);

	/// </summary>

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
