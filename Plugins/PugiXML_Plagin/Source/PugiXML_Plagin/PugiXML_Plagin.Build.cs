// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

using System.IO;   // m
using System;      // m

public class PugiXML_Plagin : ModuleRules
{
    private string ThirdPartyPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModuleDirectory));   // Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "MyFile"))
        }   
    }


	public PugiXML_Plagin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                Path.Combine(ModuleDirectory, "Include"),
                ModuleDirectory
				// ... add public include paths required here ...
			}
            ) ; 
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Projects",    // IPluginManager           
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "DesktopPlatform",    //  Dialog Window
                "UMG",                //  Widget Component 
                "InputCore",          // InputComponent->BindKey(EKeys::.........
               // "PropertyEditor",     //   button in actor property

				// ... add private dependencies that you statically link with here ...	
			}
			);

        // if (Target.bBuildEditor == true)
        //{
            //@TODO: Needed for the triangulation code used for sprites (but only in editor mode)
            //@TOOD: Try to move the code dependent on the triangulation code to the editor-only module
       //     PrivateDependencyModuleNames.Add("PropertyEditor");
       // }


        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

                                                            
        if (Target.Platform == UnrealTargetPlatform.Win64)  // Target.Configuration == UnrealTargetConfiguration.Debug
        {
            string PlatformString = "Win";


            string PugiXML_Lib = Path.Combine(ModuleDirectory, "Lib", PlatformString, "Debud", "x64", "pugixml.lib");
            Console.WriteLine(">>>>>>>>>__PugiXML_Lib__>>>>>>>>>>   " + PugiXML_Lib);
            PublicAdditionalLibraries.Add(PugiXML_Lib);

            string PugiXML_Bin = Path.Combine(ModuleDirectory, "Bin", PlatformString, "Debud", "x64", "pugixml.dll");
            Console.WriteLine(">>>>>>>>>__PugiXML_Bin__>>>>>>>>>>   " + PugiXML_Bin);
            PublicDelayLoadDLLs.Add("PugiXML_Bin");

            CopyFile(PugiXML_Bin, Path.Combine(BinbFolder(Target), "pugixml.dll"));


           
        }

        Console.WriteLine(">>>>>>>>>__01__>>>>>>>>>>" + ModuleDirectory);

    }

    private string BinbFolder(ReadOnlyTargetRules Target)
    {
        if (Target.Platform == UnrealTargetPlatform.Win64)  
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "..", "..", "Binaries", "Win64"));
        if (Target.Platform == UnrealTargetPlatform.IOS)
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "..", "..", "Binaries", "IOS"));
        if (Target.Platform == UnrealTargetPlatform.Mac)
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "..", "..", "Binaries", "Mac"));
        if (Target.Platform == UnrealTargetPlatform.Android)
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "..", "..", "Binaries", "Android"));
        return "";
    }

    public void CopyFile(String Source, string Dest)
    {
        System.Console.WriteLine("___Copy___ {0} ___to___ {1}  ",  Source, Dest);
        if (System.IO.File.Exists(Dest))
        {
            System.IO.File.SetAttributes(Dest, System.IO.File.GetAttributes(Dest) & ~System.IO.FileAttributes.ReadOnly);
        }
        try
        {
            System.IO.File.Copy(Source, Dest, true);
            System.Console.WriteLine("Copy Ok");
        }
        catch(System.Exception ex)
        {
            System.Console.WriteLine("Filed to copy {0} ", ex.Message);
        }
    }
    
}
