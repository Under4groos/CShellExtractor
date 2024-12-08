// cmd_IconExtract.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>


typedef int(*FUNC_ExtructIconToFile)(const char* filePath, const WCHAR* outputPath);

const char* lib_ = "CShellExtractor.dll";
int main()
{


    // int ExtructIconToFile(const char* filePath, const WCHAR* outputPath)
    HMODULE module = LoadLibraryExA(lib_, NULL, 0);
    if (module) {
        FUNC_ExtructIconToFile func_ = (FUNC_ExtructIconToFile)GetProcAddress(module, "Export_ExtructIconToFile");
        if (func_) {


            const char* filepath = "C:\\Users\\UnderKo\\Downloads\\Uninstall Tool.rar";
            const WCHAR* outputPath = L"C:\\Users\\UnderKo\\Downloads\\extruct.png";
            int status = func_(filepath, outputPath);

            std::cout << status << std::endl;
        }
    }






    std::cout << "Hello World!\n";
}
