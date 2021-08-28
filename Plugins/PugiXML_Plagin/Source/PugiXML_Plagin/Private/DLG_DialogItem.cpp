// Fill out your copyright notice in the Description page of Project Settings.


#include "DLG_DialogItem.h"

///#include "PugiXML_Plagin/Include/pugixml.hpp"
#include "PugiXML_Plagin/Include/pugixml.hpp"                   //  PUGI


//#include "XMLGameMode.h"       //      !!!!!!!!!!!!!!!!!!    Change on your GameMod
//#include "DLG_GlobalComponent.h"
#include "EngineUtils.h"           //    ActorIterator

#include "Kismet/GameplayStatics.h"  // Sound at location

#include <sstream>

   


// Sets default values for this component's properties
UDLG_DialogItem::UDLG_DialogItem()
{

	PrimaryComponentTick.bCanEverTick = false;

	// ...
}






















// Called when the game starts
void UDLG_DialogItem::BeginPlay()
{
	Super::BeginPlay();





	if(!DialogParameter.isAlredyLoad && PathToFile != FString("Your dialog file.xml"))
	{
		InitDialog();
	}


/*

	
	//td::string text11(RootNode.text().as_string());
	std::string text11 = "ППППППРРРООООООООООО";
	std::wstring text_wstring11 = pugi::as_wide(text11.c_str());
	FString aaaa(text_wstring11.c_str());
	UE_LOG(LogTemp, Warning, TEXT("YYYYYYYYYYYYYYYYYYYYYYYY '%s'"), *aaaa);




	//   Drew all  TEST
	//std::ostringstream ss;
	//xmlDoc.save(ss);
	////std::string s = ss.str();
	//std::wstring ws = pugi::as_wide(ss.str());
	//FString FSss(ws.c_str());
	//UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *FSss);


	
/*

	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx


	//  Get Pugi::Content from FString
	std::string source = (TCHAR_TO_UTF8(*XmlFileContent));
	pugi::xml_document xmlDoc;
	///pugi::xml_parse_result parse_Res = xmlDoc.load_file("G:\\ARCHIV\\Archive\\UE_Proj\\XML\\Dialod_Name_01.xml");
	//pugi::xml_parse_result parse_Res = xmlDoc.load_buffer(source.c_str(), source.size());  //+++++++
	xmlDoc.load(source.c_str());


	// ========== Get Root Node ==========
	pugi::xml_node RootNode = xmlDoc.child("name");
	std::string RootNodeStr(RootNode.attribute("name").as_string());
	//std::wstring RootNodeWStr = pugi::as_wide(RootNodeStr.c_str());//
	//FString RootNodeFStr(RootNodeWStr.c_str());//
	//UE_LOG(LogTemp, Warning, TEXT("RootNode = '%s'"), *RootNodeFStr);//


	////pugi::xml_node node1 = xmlDoc.child("unit").attribute("name");
	//std::string val1(xmlDoc.child("level1").attribute("name").value());
	//std::string val2(xmlDoc.child("level1").child("data").child("transform").attribute("py").value());
	////-------std::string val3(xmlDoc.child("transform").attribute("py").value());
	//std::string val4(xmlDoc.next_sibling("level1").attribute("name").value());

	//FString str(val4.c_str());


	//// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	//pugi::xpath_node xpathNode = xmlDoc.child("dialog").select_single_node("param11");  // find first node in 'dialog' with param 'param11'
	//if (xpathNode)
	//{
	//	pugi::xml_node selectedNode = xpathNode.node();
	//	std::string val5(xpathNode.node().attribute("param").value());
	//	FString str1(val5.c_str());
	//	UE_LOG(LogTemp, Warning, TEXT("unit->data->...... = '%s'"), *str1)
	//}
	////vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv


	std::string CurrentNodeSTD;
	FString FStringFromSTD;

	//  Get Root Node
	pugi::xml_node RootNode = xmlDoc.child("name");
	std::string RootNodeStr(RootNode.attribute("name").as_string());
	FString RootNodeFStr(RootNodeStr.c_str());
	UE_LOG(LogTemp, Warning, TEXT("RootNode = '%s'"), *RootNodeFStr);
	//std::string _str(node.attribute("name").value());   +++++++++++++++++++++++++++++++++++
	//std::string _str(node.text().as_string());   ++++++++++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++++
	//pugi::xml_node RootNode1 = xmlDoc.child("name");
	//std::string _str0(RootNode1.attribute("name").value());
	//std::string _str1(RootNode1.first_child().attribute("DlgName").value());
	//std::string _str2(RootNode1.next_sibling().attribute("DlgName").value());

	//  ===================    Get <active_dialog>   =================
	CurrentNodeSTD = std::string(RootNode.child("active_dialog").text().as_string());
	FStringFromSTD = FString(CurrentNodeSTD.c_str());
	DialogParameter.CurrentDialog = FName(*FStringFromSTD);
	UE_LOG(LogTemp, Warning, TEXT("<active_dialog> = '%s'"), *DialogParameter.CurrentDialog.ToString());



	//^^^^^^^^^^^^^^  wstring  ^^^^^^^^^   .set_value  ^^^^^^^^^    pugi::as_wide   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	pugi::xpath_node_set DLG_DialogBranchNode = RootNode.select_nodes("dialog");
	for (int32 i = 0; i < DLG_DialogBranchNode.size(); i++)
	{

		//   look for attribute("DlgName")  ==  "DEFAULT"
		std::string _Str(DLG_DialogBranchNode[i].node().attribute("DlgName").as_string());
		//std::wstring _WStr = pugi::as_wide(RootNodeStr.c_str());//
		//FString val(_WStr.c_str());//
		//UE_LOG(LogTemp, Warning, TEXT("value = '%s'"), *val);//
		//-----------------
		//std::string _Str1(DLG_DialogBranchNode[i].node().text().as_string());
		//std::wstring _WStr1 = pugi::as_wide(RootNodeStr.c_str());//
		//FString valval(_WStr1.c_str());//
		//UE_LOG(LogTemp, Warning, TEXT("text = '%s'"), *valval);//

		if (_Str == std::string("DEFAULT"))
		{
			DLG_DialogBranchNode[i].node().attribute("DlgName").set_value("34567890");
		}
	}
	//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv





	pugi::xpath_node_set DLG_AllSegmentsNode = RootNode.select_nodes("dialog");
	for (int32 i = 0; i < DLG_AllSegmentsNode.size(); i++)
		//for (pugi::xml_node DLGSegmentNode : RootNode.child("dialog"))
		//for (pugi::xml_node DLGSegmentNode = RootNode.first_child(); DLGSegmentNode; DLGSegmentNode = DLGSegmentNode.next_sibling())
	{

		////////std::string _Str(DLG_DialogBranchNode[i].node().attribute("DlgName").as_string());

		////////if (_Str == std::string("DEFAULT"))
		////////{
		////////	DLG_DialogBranchNode[i].node().attribute("DlgName").set_value("34567890");
		////////}


		//++++++++++++++++++++++++++++++++++   DLG_AllSegmentsNode[i].node()
		//std::string _str(DLG_AllSegmentsNode[i].node().attribute("DlgName").as_string());
		//FString val(_str.c_str());
		//UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *val);

		pugi::xpath_node_set REP_AllSegmentsNode = DLG_AllSegmentsNode[i].node().select_nodes("replic");
		for (int32 i_Rep = 0; i_Rep < REP_AllSegmentsNode.size(); i_Rep++)
		{
			std::string _str(REP_AllSegmentsNode[i_Rep].node().attribute("if").as_string());
			FString val(_str.c_str());
			UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *val);
		}

	}





	//   ============================   Change attribute .XML by Pugi   =================================
	//pugi::xpath_node_set DLG_LocalVariableNode = RootNode.select_nodes("dialog_variable");
	//for (int32 vr_loc = 0; vr_loc < DLG_LocalVariableNode.size(); vr_loc++)
	//{
	//	//++++++++++++++++++++++++++++++++++   DLG_LocalVariableNode[i].node()......Check  attribute("DlgName") == "DEFAULT"
	//	std::string _str(DLG_LocalVariableNode[vr_loc].node().attribute("name").as_string());
	//	FString val(_str.c_str());
	//	UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *val);
	//	if (_str == std::string("var1_name"))
	//	{
	//		DLG_LocalVariableNode[vr_loc].node().attribute("value").set_value("2233");
	//	}
	//}

	//xmlDoc.save_file("G:\\ARCHIV\\Archive\\UE_Proj\\XML\\Dialod_Name_01_NEW_1.xml");


//   ============================   Save .XML by Pugi   =================================
	//pugi::xml_document ExportXML_Doc;

	//pugi::xml_node root = ExportXML_Doc.document_element();

	//auto declarationNode = ExportXML_Doc.append_child(pugi::node_declaration);
	//declarationNode.append_attribute("version") = "1.0";
	//declarationNode.append_attribute("encoding") = "ISO-8859-1";
	//declarationNode.append_attribute("standalone") = "yes";


	//pugi::xml_node  element = ExportXML_Doc.append_child("file");
	//element.append_child(pugi::node_pcdata).set_value("World");

	//pugi::xml_node nodeChild = element.append_child("Hello");

	//nodeChild.append_attribute("version") = "1.0";
	//nodeChild.append_child(pugi::node_pcdata).set_value("World");

	//pugi::xml_node nodeChild1 = element.append_child("Happy");

	//nodeChild1.append_child(pugi::node_pcdata).set_value("India");

	//bool saveSucceeded = ExportXML_Doc.save_file("G:\\ARCHIV\\Archive\\UE_Proj\\XML\\EXPORT.xml");
//--------------------------------------------------------------------------------


*/
	/*
	for (pugi::xml_node tool = tools.child("Tool"); tool; tool = tool.next_sibling("Tool"))
	{
		 "Tool " << tool.attribute("Filename").value();
		 ": AllowRemote " << tool.attribute("AllowRemote").as_bool();
		 ", Timeout " << tool.attribute("Timeout").as_int();
		 ", Description '" << tool.child_value("Description") << "'\n";
	}
	*/


}



void UDLG_DialogItem::InitDialog()
{

	//   ============   Get LocalVariables from .xml   ====================
	pugi::xml_document xmlVariables;

	FString LVariableXmlPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("LVariables.xml");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*LVariableXmlPath)) return;

	pugi::xml_parse_result parse_VariablesRes = xmlVariables.load_file(StringCast<ANSICHAR>(*LVariableXmlPath).Get());
	if (!parse_VariablesRes) return;

	//  Get Root Node
	pugi::xml_node VariableRootNode = xmlVariables.child("local_variables");








	//   ============   Get DialogParam from .xml   ====================
	pugi::xml_document xmlDoc;

	if (PathToFile == FString("Your dialog file.xml"))
	{
		UE_LOG(LogTemp, Error, TEXT("Unit '%s' rty to Init don't assign dialog"), *GetOwner()->GetName());
		return;
	}

	// !!!!!!!!!!!!	//Encoding Macros need be used carefully because the result is a pointer to a temporary object. 
					//These Macro-calls only should be used when they are used as a function parameter.
	//pugi::xml_parse_result parse_Res = xmlDoc.load_file(TCHAR_TO_ANSI(*PathToFile));   //++++++
	pugi::xml_parse_result parse_Res = xmlDoc.load_file(StringCast<ANSICHAR>(*PathToFile).Get());  //+++++




	//  Get Root Node
	pugi::xml_node RootNode = xmlDoc.child("name");
	//std::string RootNodeStr(RootNode.attribute("name").as_string());

	std::string STD_dlgStr;
	std::string STD_SpeechStr;

	//  1111   =================   DIALOG   nodes  =================
	pugi::xpath_node_set DLG_DialogNodes = RootNode.select_nodes("dialog");
	for (int32 i_Dlg = 0; i_Dlg < DLG_DialogNodes.size(); i_Dlg++)
	{
		FDialogNode DialogTMP;


		STD_dlgStr = std::string(DLG_DialogNodes[i_Dlg].node().attribute("dialog_name").as_string());  //   get attribute("dialog_name")
		std::wstring STD_W_DlgStr = pugi::as_wide(STD_dlgStr.c_str());
		FString DlgStr(STD_W_DlgStr.c_str());

		DialogTMP.Name = FName(*DlgStr);


		//   2222  ================    SPEECH   nodes  =================		
		pugi::xpath_node_set DLG_SpeechNodes = DLG_DialogNodes[i_Dlg].node().select_nodes("speech");  
		for (int32 i_Speech = 0; i_Speech < DLG_SpeechNodes.size(); i_Speech++)
		{
			FSpeechNode SpeechTMP;;

			STD_SpeechStr = std::string(DLG_SpeechNodes[i_Speech].node().attribute("speech_name").as_string());  //   get attribute("speech_name")
			std::wstring STD_W_SpeechStr = pugi::as_wide(STD_SpeechStr.c_str());
			FString SpeechStr(STD_W_SpeechStr.c_str());

			SpeechTMP.Name = FName(*SpeechStr);
			

			////   3333333  ================    SPEECH_CONDITION   nodes  =================	
			//pugi::xpath_node_set DLG_SpeechConditionNodes = DLG_SpeechNodes[i_Speech].node().select_nodes("speech_condition");
			//for (int32 i_SpeechCondition = 0; i_SpeechCondition < DLG_SpeechConditionNodes.size(); i_SpeechCondition++)
			//{
			//	//FDLGVariable Speech_VariableTMP; 
			//					
			//	std::string STD_SpeechVarTypeStr(DLG_SpeechConditionNodes[i_SpeechCondition].node().attribute("var_type").as_string());  //   get attribute("Local/Global")

			//	std::string STD_SpeechVarNameStr(DLG_SpeechConditionNodes[i_SpeechCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")


			//	//VarIndexOrName = 

			//	if (STD_SpeechVarTypeStr == "local")
			//	{
			//		//   444444444444444444  ================    LVariable   nodes  =================	
			//		bool isVariableAbsent = true;
			//		pugi::xpath_node_set DLG_SpeechVariables = VariableRootNode.select_nodes("variable");
			//		for (int32 i_SpeechVariables = 0; i_SpeechVariables < DLG_SpeechVariables.size(); i_SpeechVariables++)
			//		{
			//			std::string STD_Tmp_SpeechVarNameStr(DLG_SpeechVariables[i_SpeechVariables].node().attribute("name").as_string());  //   get attribute("var_name")
			//			if (STD_SpeechVarNameStr == STD_Tmp_SpeechVarNameStr)
			//			{
			//				SpeechTMP.IndexLocalVar.Add(i_SpeechVariables);
			//				isVariableAbsent = false;  //  LocalVariabl ise exist in LVariableFile
			//				break;
			//			}	
			//		}
			//		//  if "checking variable" is absent in "localVariables"  =>> it woun't take into consideration
			//		if (isVariableAbsent)    SpeechTMP.IndexLocalVar.Add(-1);
			//	}
			//}

			//   33333  ================    REPLIC   nodes  =================	
			pugi::xpath_node_set DLG_ReplicNodes = DLG_SpeechNodes[i_Speech].node().select_nodes("replic");
			for (int32 i_Replic = 0; i_Replic < DLG_ReplicNodes.size(); i_Replic++)
			{
				FReplicNode ReplicTMP;


				////   444444  ================    REPLIC_CONDITION   nodes  =================	
				//pugi::xpath_node_set DLG_ReplicConditionNodes = DLG_ReplicNodes[i_Replic].node().select_nodes("replic_condition");
				//for (int32 i_ReplicCondition = 0; i_ReplicCondition < DLG_ReplicConditionNodes.size(); i_ReplicCondition++)
				//{					
				//	std::string STD_ReplicVarTypeStr(DLG_ReplicConditionNodes[i_ReplicCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")

				//	std::string STD_ReplicVarNameStr(DLG_ReplicConditionNodes[i_ReplicCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")

				//	if (STD_ReplicVarTypeStr == "local")
				//	{
				//		//   5555555555  ================    LVariable   nodes  =================	
				//		bool isVariableAbsent = true;
				//		pugi::xpath_node_set DLG_ReplicVariables = VariableRootNode.select_nodes("variable");
				//		for (int32 i_ReplicVariables = 0; i_ReplicVariables < DLG_ReplicVariables.size(); i_ReplicVariables++)
				//		{
				//			std::string STD_Tmp_ReplicVarNameStr(DLG_ReplicVariables[i_ReplicVariables].node().attribute("name").as_string());  //   get attribute("var_name")
				//			if (STD_ReplicVarNameStr == STD_Tmp_ReplicVarNameStr)
				//			{
				//				ReplicTMP.IndexLocalVar.Add(i_ReplicVariables);
				//				isVariableAbsent = false;  //  LocalVariabl ise exist in LVariableFile
				//				break;
				//			}

				//		}
				//		//  if "checking variable" is absent in "localVariables"  =>> it woun't take into consideration
				//		if (isVariableAbsent)    ReplicTMP.IndexLocalVar.Add(-1);
				//	}
				//}

				//   44444  ================    REP   nodes  =================	
				pugi::xpath_node_set DLG_RepNodes = DLG_ReplicNodes[i_Replic].node().select_nodes("rep");
				for (int32 i_Rep = 0; i_Rep < DLG_RepNodes.size(); i_Rep++)
				{
					FRepNode RepTMP;

				//	//   55555  ================    REP_CONDITION   nodes  =================	
				//	pugi::xpath_node_set DLG_RepConditionNodes = DLG_RepNodes[i_Rep].node().select_nodes("rep_condition");
				//	for (int32 i_RepCondition = 0; i_RepCondition < DLG_RepConditionNodes.size(); i_RepCondition++)
				//	{

				//		std::string STD_RepVarTypeStr(DLG_RepConditionNodes[i_RepCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")

				//		std::string STD_RepVarNameStr(DLG_RepConditionNodes[i_RepCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")

				//		if (STD_RepVarTypeStr == "local")
				//		{
				//			//   66666666666666  ================    LVariable   nodes  =================	
				//			bool isVariableAbsent = true;
				//			pugi::xpath_node_set DLG_RepVariables = VariableRootNode.select_nodes("variable");
				//			for (int32 i_RepVariables = 0; i_RepVariables < DLG_RepVariables.size(); i_RepVariables++)
				//			{
				//				std::string STD_Tmp_RepVarNameStr(DLG_RepVariables[i_RepVariables].node().attribute("name").as_string());  //   get attribute("var_name")
				//				if (STD_RepVarNameStr == STD_Tmp_RepVarNameStr)
				//				{
				//					RepTMP.IndexLocalVar.Add(i_RepVariables);
				//					isVariableAbsent = false;  //  LocalVariabl is exist in LVariableFile
				//					break;
				//				}
				//			}
				//			//  if "checking variable" is absent in "localVariables"  =>> it woun't take into consideration
				//			if (isVariableAbsent)    RepTMP.IndexLocalVar.Add(-1);
				//		}
				//	}
					ReplicTMP.RepNode.Add(RepTMP);
				}

				
				SpeechTMP.ReplicNode.Add(ReplicTMP);
			}

			//   3333   ================    RESPONSE   nodes  =================	
			pugi::xpath_node_set DLG_ResponseNodes = DLG_SpeechNodes[i_Speech].node().select_nodes("response");
			for (int32 i_Response = 0; i_Response < DLG_ResponseNodes.size(); i_Response++)
			{
				FResponseNode ResponseTMP;

				////   444444  ================    RESPONSE_CONDITION   nodes  =================	
				//pugi::xpath_node_set DLG_ResponseConditionNodes = DLG_ResponseNodes[i_Response].node().select_nodes("response_condition");
				//for (int32 i_ResponseCondition = 0; i_ResponseCondition < DLG_ResponseConditionNodes.size(); i_ResponseCondition++)
				//{
				//	//bool isValid = true;
				//	//FDLGVariable Response_VariableTMP;

				//	std::string STD_ResponseVarTypeStr(DLG_ResponseConditionNodes[i_ResponseCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")

				//	std::string STD_ResponseVarNameStr(DLG_ResponseConditionNodes[i_ResponseCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")

				//	if (STD_ResponseVarTypeStr == "local")
				//	{
				//		//   5555555555  ================    LVariable   nodes  =================
				//		bool isVariableAbsent = true;
				//		pugi::xpath_node_set DLG_ResponseVariables = VariableRootNode.select_nodes("variable");
				//		for (int32 i_Variables = 0; i_Variables < DLG_ResponseVariables.size(); i_Variables++)
				//		{
				//			std::string STD_Tmp_ResponseVarNameStr(DLG_ResponseVariables[i_Variables].node().attribute("name").as_string());  //   get attribute("var_name")
				//			if (STD_ResponseVarNameStr == STD_Tmp_ResponseVarNameStr)
				//			{
				//				ResponseTMP.IndexLocalVar.Add(i_Variables);
				//				isVariableAbsent = false;  //  LocalVariabl ise exist in LVariableFile
				//				break;
				//			}
				//		}
				//		//  if "checking variable" is absent in "localVariables"  =>> it woun't take into consideration
				//		if (isVariableAbsent)    ResponseTMP.IndexLocalVar.Add(-1);
				//	}
				//}


				////   444444  ================    RESPONSE_Change_VARIABLES   nodes  =================	
				//pugi::xpath_node_set DLG_ResponseVariablesNodes = DLG_ResponseNodes[i_Response].node().select_nodes("change_variable");
				//for (int32 i_ResponseVariables = 0; i_ResponseVariables < DLG_ResponseVariablesNodes.size(); i_ResponseVariables++)
				//{
				//	//bool isValid = true;
				//	//FDLGVariable Response_VariableTMP;

				//	std::string STD_ResponseVarTypeStr(DLG_ResponseVariablesNodes[i_ResponseVariables].node().attribute("var_type").as_string());  //   get attribute("var_type")

				//	std::string STD_ResponseVarNameStr(DLG_ResponseVariablesNodes[i_ResponseVariables].node().attribute("var_name").as_string());  //   get attribute("var_name")
				//	//if (STD_ResponseVarTypeStr == "global")  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				//	//{
				//	//	GlobalVariable.Contains(FName(*VarName_Str))
				//	//	//FString ResponseVarNameStr(STD_ResponseVarNameStr.c_str());
				//	//	//Response_VariableTMP.NameGlobalVar = FName(*ResponseVarNameStr);
				//	//}
				//	//else // if  "local" variable
				//	
				//	if (STD_ResponseVarTypeStr == "local")
				//	{

				//		//   5555555555  ================    LVariable   nodes  =================	
				//		bool isVariableAbsent = true;
				//		pugi::xpath_node_set DLG_ResponseVariables = VariableRootNode.select_nodes("variable");
				//		for (int32 i_Variables = 0; i_Variables < DLG_ResponseVariables.size(); i_Variables++)
				//		{
				//			std::string STD_Tmp_ResponseVarNameStr(DLG_ResponseVariables[i_Variables].node().attribute("name").as_string());  //   get attribute("var_name")
				//			if (STD_ResponseVarNameStr == STD_Tmp_ResponseVarNameStr)
				//			{

				//				ResponseTMP.IndexLocalVar_ToChange.Add(i_Variables);
				//				isVariableAbsent = false;  //  LocalVariabl ise exist in LVariableFile
				//				break;
				//			}
				//		}
				//		//  if "checking variable" is absent in "localVariables"  =>> it woun't take into consideration
				//		if (isVariableAbsent)    ResponseTMP.IndexLocalVar_ToChange.Add(-1);
				//	}
				//}

				SpeechTMP.ResponseNode.Add(ResponseTMP);
			}

			DialogTMP.SpeechNode.Add(SpeechTMP);
		}//
		DialogParameter.DialogNode.Add(DialogTMP);
	}//

	//for (int32 i = 0; i < DialogParameter.MissingVariablesStr.Num(); i++)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("%s"), *DialogParameter.MissingVariablesStr[i]);
	//}
	//   Drew all Cash  TEST  ----------no correct----------
	//for (int32 i = 0; i < DialogParameter.DialogNode.Num(); i++)
	//{
	//	for (int32 i1 = 0; i1 < DialogParameter.DialogNode[i].SpeechNode.Num(); i1++)
	//	{
	//		for (int32 i1_1 = 0; i1_1 < DialogParameter.DialogNode[i].SpeechNode[i1].ReplicRepeatProperty.Num(); i1_1++)
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("replic-------: = '%s'"), *c);
	//		}
	//		for (int32 i1_2 = 0; i1_2 < DialogParameter.DialogNode[i].SpeechNode[i1].ResponseRepeatProperty.Num(); i1_2++)
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("response-----: = '%s'"), *DialogParameter.DialogNode[i].SpeechNode[i1].ResponseRepeatProperty[i1_2]);
	//		}
	//	}
	//}

}


void UDLG_DialogItem::PlayDialog()
{

	//   ================== Get  "DLG_Global  --  Actor  (Sub_BP) on Scene"   -- DoOnce --   ==================
		
	if (!DLG_GlobalActor)
	{
		//for (TObjectIterator<ADLG_GlobalActor> Itr; Itr; ++Itr)
		for (TActorIterator<ADLG_GlobalActor> Itr(GetWorld()); Itr; ++Itr)
		{
			if (Itr->IsA(ADLG_GlobalActor::StaticClass()))
			{
				DLG_GlobalActor = *Itr;
				break;
			}
		}
		   
		//  ------ Spawn, if not  ------
		if (!DLG_GlobalActor)
		{
			BP_GLobalActorClass = StaticLoadClass(ADLG_GlobalActor::StaticClass(), nullptr, 
															TEXT("/PugiXML_Plagin/DLG_GlobalActorBP.DLG_GlobalActorBP_C"));
			//DLG_GlobalActor = GetWorld()->SpawnActor<ADLG_GlobalActor>(ADLG_GlobalActor::StaticClass());
			DLG_GlobalActor = GetWorld()->SpawnActor<ADLG_GlobalActor>(BP_GLobalActorClass);
		}

		if (!DLG_GlobalActor)UE_LOG(LogTemp, Error, TEXT("Not Exist Global DLG_Actor.  Reporter '%s'"), *GetOwner()->GetName());
	}


	if (PathToFile == FString("Your dialog file.xml"))
	{
		UE_LOG(LogTemp, Error, TEXT("Unit '%s' start dialog but don't assign it"), *GetOwner()->GetName());
		return;
	}





	//==================   ALL File Cash as FString  =====================   777777777777777777777777
/*
	//  ----------  if first time   Cash .xml from BP  ----------------
	if (XmlFileContent == FString("none"))
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		FString FilePath = PathToFile;            // FString("G:/ARCHIV/Archive/UE_Proj/XML/Dialod_Name_01.xml");

		if (PlatformFile.FileExists(*FilePath))
		{
			FFileHelper::LoadFileToString(XmlFileContent, *FilePath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unit '%s' cann't open dialog file"), *GetOwner()->GetName());
			return;
		}


		////  ==============================  Prepare Dialog content  ================================

		////  Get xmlFile Content
		//std::string source = (TCHAR_TO_UTF8(*XmlFileContent));
		//pugi::xml_document xmlDoc;
		//xmlDoc.load(source.c_str());

		//pugi::xml_node RootNode = xmlDoc.child("name");
		//std::string RootNodeStr(RootNode.attribute("name").as_string());


	}
*/
	//DLG_GlobalActor->DLG_PlayDialog(XmlFileContent);


	






	      

	 



	DLG_GlobalActor->DLG_PlayDialog(GetOwner(), PathToFile, DialogParameter);// ,//);
		//EResponseReturn::click_default_back);
	//DLG_GlobalActor->DLG_PlayDialog(XmlFileContent); // , DialogParameter








	    
























	//if (PathToFileRuntime == FString("none"))   //  First Call 
	{
		//if(DLG_GlobalActor && PathToFile != FString("Your dialog file.xml"))
			//DLG_GlobalActor->DLG_PlayDialog(PathToFile);
	}
	//else
	{
		//DLG_GlobalActor->DLG_PlayDialog(PathToFileRuntime);
	}
	


	//  777777777777777777777777777777
	//AXMLGameMode *myGmode = Cast<AXMLGameMode>(GetWorld()->GetAuthGameMode());




    

	

	




/*	std::string CurrentNode_STD_C;
	FString FStringFromSTD;


	pugi::xpath_node_set DLG_LocalVariableNode = RootNode.select_nodes("dialog_variable");
	for (int32 vr_loc = 0; vr_loc < DLG_LocalVariableNode.size(); vr_loc++)
	{
		//++++++++++++++++++++++++++++++++++   DLG_LocalVariableNode[i].node()......Check  attribute("DlgName") == "DEFAULT"
		std::string _str(DLG_LocalVariableNode[vr_loc].node().attribute("name").as_string());
		FString val(_str.c_str());
		UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *val);
		if (_str == std::string("var1_name"))
		{
			DLG_LocalVariableNode[vr_loc].node().attribute("value").set_value("2233");
		}
	}

	xmlDoc.save_file("G:\\ARCHIV\\Archive\\UE_Proj\\XML\\Dialod_Name_01_NEW_1.xml");
	*/
}














/*
// Called every frame
void UDLG_DialogItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/
