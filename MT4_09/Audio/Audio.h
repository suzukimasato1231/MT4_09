#pragma once
#include<xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <fstream>
#include <cassert>
#include<d3dx12.h>
class Audio
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	ComPtr<IXAudio2>xAudio2;
	IXAudio2MasteringVoice *masterVoice;

	//チャンクヘッダ
	struct ChunkHeader
	{
		char id[4];
		int32_t size;//チャンクサイズ
	};

	struct RiffHeader
	{
		ChunkHeader chunk;
		char type[4];
	};

	struct FormatChunk
	{
		ChunkHeader chunk;
		WAVEFORMATEX fmt;
	};

	struct SoundData
	{
		WAVEFORMATEX wfex;
		BYTE *pBuffer;
		unsigned int BufferSize;
	};

	Audio();
	void Init();

	/// <summary>
	/// 音作成
	/// </summary>
	/// <returns></returns>
	static Audio *Create();

	//WAVE読み込み
	static SoundData SoundLoadWave(const char *firename);
	//メモリ削除
	static void SoundUnload(SoundData *soundData);
	//1回再生
	void Audio::SoundSEPlayWave( const SoundData &soundData);
	//ループ再生
	void Audio::SoundBGMPlayLoopWave( const SoundData &soundData, IXAudio2SourceVoice *pSourceVoice);

	void Audio::SoundStop( const SoundData &soundData, IXAudio2SourceVoice *pSourceVoice);

	IXAudio2SourceVoice *BGM = nullptr;
};

