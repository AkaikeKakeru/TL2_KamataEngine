/*テクスチャコンバータ*/
#pragma once
#include <string>
#include <DirectXTex.h>

//テクスチャコンバータ
class TextureConverter {
public:
	/// <summary>
	/// テクスチャをWICからDDSに変換
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	/// <param name="numOptions">オプション数</param>
	/// <param name="options">オプション配列</param>
	void ConvertTextureWICToDDS(
		const std::string& filePath,
		int numOptions = 0,
		char* options[] = nullptr);

	/// <summary>
	/// 使用方法を出力(表示)する
	/// </summary>
	static void OutputUsage();

private:
	/// <summary>
	/// テクスチャファイル読込
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadWICTextureFromFile(
		const std::string& filePath);

	/// <summary>
	/// マルチバイト文字列をワイド文字列に変換
	/// </summary>
	/// <param name="mString">マルチバイト文字列</param>
	/// <returns>ワイド文字列</returns>
	static std::wstring ConvertMultiByteStringToWideString(
		const std::string& mString);

	/// <summary>
	/// フォルダパスとファイル名を分解する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void SeparateFilePath(
		const std::wstring& filePath);

	/// <summary>
	/// DDSテクスチャとしてファイルを書き出し
	/// </summary>
	void SaveDDSTextureToFile(
		int numOptions,
		char* options[]);

private:
	//画像の情報
	DirectX::TexMetadata metadata_;
	//画像イメージのコンテナ
	DirectX::ScratchImage scratchImage_;

	//ディレクトリパス
	std::wstring directoryPath_;
	//ファイル名
	std::wstring fileName_;
	//ファイル拡張子
	std::wstring fileExt_;
};
