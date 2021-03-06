#pragma once
#include "Model.h"
#include"Camera.h"
#include<Windows.h>
#include<wrl.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<DirectXMath.h>
#include<string>
#include"FbxLoader.h"
class FBXObject3d
{
protected://エイリアス
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public://静的メンバ関数
	static void SetDevice(ID3D12Device *device) { FBXObject3d::device = device; }
	static void SetCamera(Camera *camera) { FBXObject3d::camera = camera; }
	static void SetCmdList(ID3D12GraphicsCommandList *cmdList) { FBXObject3d::cmdList = cmdList; }
private://静的メンバ変数
	//デバイス
	static ID3D12Device *device;
	//カメラ
	static Camera *camera;

	static ID3D12GraphicsCommandList *cmdList;
public://定数
	//ボーンの最大数
	static const int MAX_BONES = 32;
public://サブクラス

		//定数バッファ用データ構造体(座標変換行列用)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;	//ビュープロジェクション行列
		XMMATRIX world;		//ワールド行列
		XMFLOAT3 cameraPos;	//カメラ座標(ワールド座標)
	};
	//定数バッファ用データ構造体(スキニング)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public://メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// グラフィックスパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// モデルのセット
	/// </summary>
	/// <param name="model"></param>
	void SetModel(Model *model) { this->model = model; }
	/// <summary>
	/// アニメーション開始
	/// </summary>
	void PlayAnimation();
protected://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource>constBuffTransform;
	//定数バッファ
	ComPtr<ID3D12Resource>constBufferSkin;

	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature>rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState>pipelinestate;

	//ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	//X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	//ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	//ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	Model *model = nullptr;

	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;
};
