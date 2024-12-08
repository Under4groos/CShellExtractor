



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