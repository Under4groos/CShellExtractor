# CShellExtractor

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
