// dllmain.cpp : Определяет точку входа для приложения DLL.

#include <Windows.h>
#include <shellapi.h>
#include <gdiplus.h>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>
#pragma comment(lib, "Gdiplus.lib")

#define FunExport  extern "C"  __declspec(dllexport)
using namespace std;

#pragma region hide


bool DirectoryExists(const wchar_t* dirPath) {
	struct _stat info;
	if (_wstat(dirPath, &info) != 0) return false;
	return (info.st_mode & S_IFDIR) != 0;
}

int GetEncoderClsid(const wchar_t* format, CLSID* pClsid) {
	UINT num = 0;
	UINT size = 0;
	Gdiplus::ImageCodecInfo* pImageCodecInfo = nullptr;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0) return -1;

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == nullptr) return -1;

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT i = 0; i < num; ++i) {
		if (wcscmp(pImageCodecInfo[i].MimeType, format) == 0) {
			*pClsid = pImageCodecInfo[i].Clsid;
			free(pImageCodecInfo);
			return 0;
		}
	}

	free(pImageCodecInfo);
	return -1;
}


int ExtructIconToFile(const char* filePath, const WCHAR* outputPath) {

	Gdiplus::Status status = Gdiplus::Status::Win32Error;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	SHFILEINFOA fileInfo;
	ZeroMemory(&fileInfo, sizeof(fileInfo));



	if (SHGetFileInfoA(filePath, FILE_ATTRIBUTE_NORMAL, &fileInfo, sizeof(SHFILEINFO), SHGFI_LARGEICON | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES)) {
		std::cout << fileInfo.hIcon << endl;
		if (fileInfo.hIcon == nullptr) {



			return 1;
		}

		Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromHICON(fileInfo.hIcon);

		std::cout << bitmap << endl;
		if (bitmap == nullptr) {

			DestroyIcon(fileInfo.hIcon);
			return 2;
		}

		CLSID pngClsid;
		if (GetEncoderClsid(L"image/png", &pngClsid) != 0) {

			delete bitmap;
			DestroyIcon(fileInfo.hIcon);
			return 3;
		}

		status = bitmap->Save(outputPath, &pngClsid, nullptr);


		delete bitmap;
		DestroyIcon(fileInfo.hIcon);



	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	return (int)status;
}


#pragma endregion

FunExport int Export_ExtructIconToFile(const char* filePath, const WCHAR* outputPath) {
	return ExtructIconToFile(filePath, outputPath);
}

#pragma region DllMain

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		setlocale(LC_CTYPE, "rus");

		/*if (AllocConsole())
		{
			FILE* fDummy;
			freopen_s(&fDummy, "CONIN$", "r", stdin);
			freopen_s(&fDummy, "CONOUT$", "w", stderr);
			freopen_s(&fDummy, "CONOUT$", "w", stdout);
			return true;
		}*/

		break;
	}
	return TRUE;
}
#pragma endregion


