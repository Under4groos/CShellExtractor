# CShellExtractor

Экспорт изображений из различных программ и файлов.

# Resources 
HMODULE LoadLibraryExA([in] LPCSTR lpLibFileName,HANDLE hFile, [in] DWORD  dwFlags);
```
https://learn.microsoft.com/ru-ru/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryexa
```
FARPROC GetProcAddress( [in] HMODULE hModule,[in] LPCSTR  lpProcName);
```
https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress
```
typedef-function-pointer / typedef void (*myfunc)();
```
https://stackoverflow.com/questions/4295432/typedef-function-pointer
```
[DllImport(LibExtern, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "Export_ExtructIconToFile")]public static extern IntPtr ExtructIconToFile(string filePath, string outputPath);
```
https://learn.microsoft.com/ru-ru/dotnet/api/system.runtime.interopservices.dllimportattribute?view=net-9.0
```
## Projects
1. cmd_IconExtract_CS - C# and C++ (dynamic lib)
2. cmd_IconExtract - C++ and C++ (dynamic lib)
3. CShellExtractor - C++

## Using 

### C# and C++

```C#
// Interop.cs
public static class Interop
{
    public const string LibExtern = "CShellExtractor.dll";
    // int Export_ExtructIconToFile(const wchar_t* filePath, const wchar_t* outputPath)
    // CallingConvention = CallingConvention.Cdecl,
    [DllImport(LibExtern, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "Export_ExtructIconToFile")]
    public static extern IntPtr ExtructIconToFile(string filePath, string outputPath);
}

// Program.cs
using cmd_IconExtract_CS;
if(!File.Exists(Interop.LibExtern))
{
    Console.WriteLine($"File not found! {Path.GetFullPath(Interop.LibExtern)}");
    return;
}
IntPtr status = Interop.ExtructIconToFile(
               @"C:\Users\UnderKo\Downloads\Uninstall Tool.rar",
               Path.GetFullPath(@"extruct.png"));
Console.WriteLine(status);
Console.ReadLine();
```


### C++ and C++


```C++
// cmd_IconExtract.cpp
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
```