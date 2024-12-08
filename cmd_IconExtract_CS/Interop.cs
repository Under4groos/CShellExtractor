using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace cmd_IconExtract_CS
{
    public static class Interop
    {
        public const string LibExtern = "CShellExtractor.dll";


        // int Export_ExtructIconToFile(const wchar_t* filePath, const wchar_t* outputPath)
        // CallingConvention = CallingConvention.Cdecl,
        [DllImport(LibExtern, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "Export_ExtructIconToFile")]
        public static extern IntPtr ExtructIconToFile(string filePath, string outputPath);
    }
}
