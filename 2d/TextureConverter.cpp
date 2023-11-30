#include "TextureConverter.h"

using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(
	const std::string& filePath) {
	//テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

	//DDS形式に変換して書きだす
	SaveDDSTextureToFile();
}

void TextureConverter::LoadWICTextureFromFile(
	const std::string& filePath) {
	HRESULT result;

	//ファイルパスをワイド文字列に変換
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);

	//テクスチャを読み込む
	result = LoadFromWICFile(
		wfilePath.c_str(),
		WIC_FLAGS_NONE,
		&metadata_,
		scratchImage_
	);

	assert(SUCCEEDED(result));

	//フォルダパスとファイル名を分解
	SeparateFilePath(wfilePath);
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(
	const std::string& mString) {
	//ワイド文字列に変換した際の文字数
	int bufferSize =
		MultiByteToWideChar(
			CP_ACP, 0, mString.c_str(), -1, nullptr, 0
		);

	//ワイド文字列
	std::wstring wString;
	wString.resize(bufferSize);

	//変換する
	MultiByteToWideChar(
		CP_ACP, 0, mString.c_str(), -1, &wString[0], bufferSize
	);

	return wString;
}

void TextureConverter::SeparateFilePath(
	const std::wstring& filePath) {
	size_t pos1;
	std::wstring exceptExt;

	//区切り文字'.'が出てくる一番最後の部分を検索
	pos1 = filePath.rfind('.');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);

		//区切り文字の前までを抜き出す
		exceptExt = filePath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}

	//区切り文字'\\'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('\\');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の前をディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);

		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);

		return;
	}

	//区切り文字'/'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('/');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の前をディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);

		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);

		return;
	}

	//区切り文字がないので、ファイル名のみとして扱う
	directoryPath_ = L"";
	fileName_ = exceptExt;
}

void TextureConverter::SaveDDSTextureToFile() {
	HRESULT result;

	//読みこんだテクスチャをSRGBとして扱う
	metadata_.format = MakeSRGB(metadata_.format);

	//出力ファイルを指定する
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	//DDSファイル書き出し
	result = SaveToDDSFile(
		scratchImage_.GetImages(),
		scratchImage_.GetImageCount(),
		metadata_,
		DDS_FLAGS_NONE,
		filePath.c_str());

	assert(SUCCEEDED(result));
}
