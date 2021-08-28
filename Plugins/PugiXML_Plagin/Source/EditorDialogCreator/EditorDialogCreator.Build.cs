// Copyright Epic Games, Inc. All Rights Reserved.



using System.IO;   // m
using System;      // m


using UnrealBuildTool;

public class EditorDialogCreator : ModuleRules
{

    //private string ThirdPartyPath // 7777777777777777777777777777777777777777
    //{
    //    get
    //    {
    //        return Path.GetFullPath(Path.Combine(ModuleDirectory));   // Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "MyFile"))
    //    }
    //}

    public EditorDialogCreator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] 
            {
               //  Path.Combine(ModuleDirectory, "..", "PugiXML_Plagin", "IncludeC"),  // 777777777777777777777777777777777777 
               // ModuleDirectory
				// ... add public include paths required here ...
			}
			);
				
		
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
				"Projects",
				"InputCore",
				"UnrealEd",
				"ToolMenus",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

                "UMG", // 777
               // "DesktopPlatform",  // 777
               "AssetRegistry",
               //"MediaAssets",
               "PropertyEditor",
               "DesktopPlatform",   //  WinDialog
                "UnrealEd",


				
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);







        if (Target.Platform == UnrealTargetPlatform.Win64)  // Target.Configuration == UnrealTargetConfiguration.Debug
        {
            string PlatformString = "Win";


            string PugiXML_Lib = Path.Combine(ModuleDirectory, "..", "PugiXML_Plagin", "Lib", PlatformString, "Debud", "x64", "pugixml.lib");
            Console.WriteLine(">>>>>>>>>__PugiXML_Lib__in Editor___>>>>>>>>>>   " + PugiXML_Lib);
            PublicAdditionalLibraries.Add(PugiXML_Lib);

            string PugiXML_Bin = Path.Combine(ModuleDirectory, "..", "PugiXML_Plagin", "Bin", PlatformString, "Debud", "x64", "pugixml.dll");
            Console.WriteLine(">>>>>>>>>__PugiXML_Bin__in Editor___>>>>>>>>>>   " + PugiXML_Bin);
            PublicDelayLoadDLLs.Add("PugiXML_Bin");
           

        }



    }
}
