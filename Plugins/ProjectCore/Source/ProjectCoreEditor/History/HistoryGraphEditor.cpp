// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryGraphEditor.h"

#include "EdGraphUtilities.h"
#include "HistoryGraph.h"
#include "HistoryGraphSchema.h"
#include "HistoryUtils.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Framework/Commands/GenericCommands.h"
#include "GraphNodes/HistoryGraphNode.h"
#include "GraphNodes/ReturnHistoryGraphNode.h"
#include "Toolkits/ToolkitManager.h"
#include "ProjectCoreRuntime/Configs/HistoryConfig.h"
#include "ProjectCoreRuntime/EditorUtils/Logger/Logger.h"
#include "ProjectCoreRuntime/History/Conditions/Base/HistoryCondition.h"
#include "ProjectCoreRuntime/History/Elements/HistoryElement.h"
#include "ProjectCoreRuntime/History/Elements/RootHistoryElement.h"
#include "ProjectCoreRuntime/History/Triggers/Base/HistoryTrigger.h"
#include "ProjectCoreRuntime/History/Actions/Base/HistoryAction.h"
#include "Windows/WindowsPlatformApplicationMisc.h"

void FHistoryGraphEditor::InitHistoryGraphAssetEditor(const EToolkitMode::Type Mode,
                                                      const TSharedPtr<IToolkitHost>& InitToolkitHost,
                                                      UBaseHistoryElement* HistoryElement,
                                                      URootHistoryElement* InRootElement)
{
	CurrentElement = HistoryElement;
	ToolkitHost = InitToolkitHost;
	RootElement = InRootElement;
	
	RootElement->OnElementSaved.Unbind();
	RootElement->OnElementSaved.BindRaw(this, &FHistoryGraphEditor::SetElementsToHistoryConfig);

	if (auto Graph = RootElement->GetGraph<UHistoryGraph>(CurrentElement))
	{
		EdGraph = Graph;
	}
	else
	{
		EdGraph = CreateHistoryGraph();
		EdGraph->RootElement = RootElement;
		EdGraph->GetSchema()->CreateDefaultNodesForGraph(*EdGraph);
		RootElement->EdGraphsByElement.Add(CurrentElement, EdGraph);
	}

	GraphEditorCommands = MakeShared<FUICommandList>();

	GraphEditorCommands->MapAction(
		FGenericCommands::Get().Delete,
		FExecuteAction::CreateSP(this, &FHistoryGraphEditor::OnCommandDeleteSelectedNodes),
		FCanExecuteAction::CreateLambda([this] { return true; })
	);

	GraphEditorCommands->MapAction(
		FGenericCommands::Get().Copy,
		FExecuteAction::CreateSP(this, &FHistoryGraphEditor::OnCommandCopySelectedNodes),
		FCanExecuteAction::CreateLambda([this] { return true; })
	);

	GraphEditorCommands->MapAction(
		FGenericCommands::Get().Paste,
		FExecuteAction::CreateSP(this, &FHistoryGraphEditor::OnCommandPasteNodes),
		FCanExecuteAction::CreateLambda([this] { return true; })
	);

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this,
		&FHistoryGraphEditor::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FHistoryGraphEditor::OnNodeDoubleClicked);
	
	GraphEditor = SNew(SGraphEditor)
		.GraphEvents(InEvents)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.GraphToEdit(EdGraph)
		.ShowGraphStateOverlay(false);

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.bAllowSearch = true;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::ObjectsUseNameArea;
	DetailsViewArgs.bHideSelectionTip = false;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(CurrentElement);
    
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_CustomGraphEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->AddTab("GraphEditor", ETabState::OpenedTab)
				)
			)
		);
    
	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	InitAssetEditor(
		Mode,
		InitToolkitHost,
		"CustomGraphEditorApp",
		StandaloneDefaultLayout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolbar,
		CurrentElement);
}

void FHistoryGraphEditor::OnCommandDeleteSelectedNodes()
{
	if (!GraphEditor.IsValid())
		return;

	const FGraphPanelSelectionSet SelectedNodes = GraphEditor->GetSelectedNodes();
	if (SelectedNodes.Num() == 0)
		return;

	const FScopedTransaction Transaction(FText::FromString("Delete Nodes"));
    
	for (UObject* SelectedNode : SelectedNodes)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(SelectedNode))
		{
			Node->Modify();
			Node->DestroyNode();
		}
	}
}

void FHistoryGraphEditor::OnCommandCopySelectedNodes()
{
	const TSet<UObject*>& SelectedNodes = GraphEditor->GetSelectedNodes();
	for (UObject* Object : SelectedNodes)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(Object))
		{
			Node->PrepareForCopying();
		}
	}

	FString ExportedText;
	FEdGraphUtilities::ExportNodesToText(SelectedNodes, /*out*/ ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);

	for (UObject* Object : SelectedNodes)
	{
		if (UBaseHistoryElement* Node = Cast<UBaseHistoryElement>(Object))
		{
			//Node->PostCopyNode();
		}
	}
}

void FHistoryGraphEditor::OnCommandPasteNodes()
{
    if (!GraphEditor.IsValid()) return;

    // const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());
    //
    // CurrentElement->Modify();
    // EdGraph->Modify();
    
    FVector2f PasteLocation = GraphEditor->GetPasteLocation2f();
    
    UEdGraph* TargetGraph = GraphEditor->GetCurrentGraph();
    if (!TargetGraph) return;
    
    FString ClipboardContent;
    FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

    TSet<UEdGraphNode*> PastedNodes;
    FEdGraphUtilities::ImportNodesFromText(TargetGraph, ClipboardContent, PastedNodes);

    TArray<UHistoryElement*> NewElements;

    for (UEdGraphNode* Node : PastedNodes)
    {
        Node->NodePosX = PasteLocation.X;
        Node->NodePosY = PasteLocation.Y;
        Node->CreateNewGuid();

        if (auto HistoryNode = Cast<UHistoryGraphNode>(Node))
        {
             auto OldElement = Cast<UHistoryElement>(HistoryNode->GetElement());
             auto Element = DuplicateObject<UHistoryElement>(OldElement, TargetGraph);

        	Element->Guid = FGuid::NewGuid();
        	Element->Triggers.Empty();
        	Element->Actions.Empty();
        	Element->Conditions.Empty();
        	
             for (auto Trigger : OldElement->Triggers)
             {
	             Element->Triggers.Add(DuplicateObject<UHistoryTrigger>(Trigger, Element));
             }
             for (auto Action : OldElement->Actions)
             {
             	Element->Actions.Add(DuplicateObject<UHistoryAction>(Action, Element));
             }
        	for (auto Condition : OldElement->Conditions)
        	{
        		auto NewCondition = DuplicateObject<UHistoryCondition>(Condition, Element);
        		NewCondition->NextElementId.Invalidate();
        		Element->Conditions.Add(NewCondition);
        	}
            
            HistoryNode->SetElement(Element);
            NewElements.Add(Element);
        }
        
        Node->ReconstructNode();
    }

    TargetGraph->NotifyGraphChanged();
    
    if (PastedNodes.Num() > 0)
    {
        GraphEditor->ClearSelectionSet();
        for (UEdGraphNode* Node : PastedNodes)
        {
            GraphEditor->SetNodeSelection(Node, true);
        }
           
        GraphEditor->ZoomToFit(true);
    }

    if (NewElements.Num() > 0)
    {
        DetailsView->SetObject(NewElements[0]);
    }
    else
    {
        DetailsView->SetObject(CurrentElement);
    }
}

void FHistoryGraphEditor::SetElementsToHistoryConfig()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> Assets;
	AssetRegistryModule.Get().GetAssetsByClass(UHistoryConfig::StaticClass()->GetClassPathName(), Assets);

	if (auto Config = Assets.Num() > 0 ? Cast<UHistoryConfig>(Assets[0].GetAsset()) : nullptr)
	{
		Config->Elements.Empty();
		
		if (Config->RootHistoryElement)
		{
			RecursiveGatherElements(Config->RootHistoryElement, Config->RootHistoryElement->Elements);
			Config->RootHistoryElement->Elements.Add(Config->RootHistoryElement->Guid, Config->RootHistoryElement);
			
			Config->MarkPackageDirty();
		}
		else
		{
			FLogger::ShowMessage(TEXT("History in UHistoryConfig is missing!"));
		}
	}
	else
	{
		FLogger::ShowMessage(TEXT("UHistoryConfig is missing!"));
	}
}

void FHistoryGraphEditor::RecursiveGatherElements(UBaseHistoryElement* ParentElement,
	TMap<FGuid, TObjectPtr<UBaseHistoryElement>>& Elements)
{
	auto OutGraphElements = FHistoryUtils::FindElements(RootElement, ParentElement);

	for (auto OutGraphElement : OutGraphElements)
	{
		Elements.Add(OutGraphElement->Guid, OutGraphElement);
		RecursiveGatherElements(OutGraphElement, Elements);
	}
}

TSharedRef<FHistoryGraphEditor> FHistoryGraphEditor::TryCreateHistoryGraphEditor(EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost, UBaseHistoryElement* HistoryElement,
	URootHistoryElement* AssetElement)
{
	TSharedPtr<IToolkit> FoundAssetEditor = FToolkitManager::Get().FindEditorForAsset(HistoryElement);
	TSharedPtr<FHistoryGraphEditor> ExistingEditor = StaticCastSharedPtr<FHistoryGraphEditor>(FoundAssetEditor);
	if (ExistingEditor.IsValid())
	{
		ExistingEditor->FocusWindow();
		return ExistingEditor.ToSharedRef();
	}

	TSharedRef<FHistoryGraphEditor> NewHistoryEditor(new FHistoryGraphEditor());
	NewHistoryEditor->InitHistoryGraphAssetEditor(Mode, InitToolkitHost, HistoryElement, AssetElement);
	return NewHistoryEditor;
}

UHistoryGraph* FHistoryGraphEditor::CreateHistoryGraph()
{
	UHistoryGraph* Graph = NewObject<UHistoryGraph>(CurrentElement, UHistoryGraph::StaticClass(),
		TEXT("HistoryGraph"), RF_Transactional);
	
	Graph->Schema = UHistoryGraphSchema::StaticClass();
	return Graph;
}

void FHistoryGraphEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	TabManager->RegisterTabSpawner("GraphEditor",
		FOnSpawnTab::CreateRaw(this, &FHistoryGraphEditor::SpawnTab_GraphCanvas))
	   .SetDisplayName(NSLOCTEXT("CustomGraphEditor", "GraphEditorTab", "Graph Editor"));
	
	TabManager->RegisterTabSpawner("GraphDetails",
		FOnSpawnTab::CreateSP(this, &FHistoryGraphEditor::SpawnTab_Details))
		.SetDisplayName(NSLOCTEXT("DetailsTabLabel", "Details", "DetailsEditor"));
}

void FHistoryGraphEditor::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection)
{
	if (NewSelection.Num() == 1)
	{
		UObject* ViewSelection = nullptr;
		for (UObject* Selected : NewSelection)
		{
			if (auto HistoryNode = Cast<UHistoryGraphNode>(Selected))
			{
				ViewSelection = HistoryNode->GetElement();
			}
			else if (auto ReturnNode = Cast<UReturnHistoryGraphNode>(Selected))
			{
				if (auto Element = ReturnNode->GetElement())
				{
					ViewSelection = Element;
				}
			}
			break;
		}

		if (DetailsView.IsValid())
		{
			DetailsView->SetObject(ViewSelection, true);
		}
	}
	else
	{
		if (DetailsView.IsValid())
		{
			DetailsView->SetObject(CurrentElement, true);
		}
	}
}

void FHistoryGraphEditor::OnNodeDoubleClicked(UEdGraphNode* Node)
{
	if (Node)
	{
		if (Node->IsA(UReturnHistoryGraphNode::StaticClass()))
		{
			return;
		}
		
		auto HistoryNode = Cast<UHistoryGraphNode>(Node);
		if (auto Element = HistoryNode->GetElement())
		{
			TSharedRef<FHistoryGraphEditor> NewHistoryGraphEditor =
				TryCreateHistoryGraphEditor(EToolkitMode::Standalone, ToolkitHost, Element,RootElement);
		}
	}
}

void FHistoryGraphEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	TabManager->UnregisterTabSpawner("GraphEditor");
}

FName FHistoryGraphEditor::GetToolkitFName() const
{
	return FName("CustomGraphEditor");
}

FText FHistoryGraphEditor::GetBaseToolkitName() const
{
	return NSLOCTEXT("CustomGraphEditor", "AppLabel", "Custom Graph Editor");
}

FString FHistoryGraphEditor::GetWorldCentricTabPrefix() const
{
	return NSLOCTEXT("CustomGraphEditor", "WorldCentricTabPrefix", "CustomGraph ").ToString();
}

FLinearColor FHistoryGraphEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

TSharedRef<SDockTab> FHistoryGraphEditor::SpawnTab_GraphCanvas(const FSpawnTabArgs& Args) const
{
	check(GraphEditor.IsValid());
	return SNew(SDockTab)
		.Label(NSLOCTEXT("CustomGraphEditor", "GraphEditorTitle", "Graph Editor"))
		[
			GraphEditor.ToSharedRef()
		];
}

TSharedRef<SDockTab> FHistoryGraphEditor::SpawnTab_Details(const FSpawnTabArgs& Args) const
{
	TSharedRef<SDockTab> NewTab = SNew(SDockTab)
		.Label(NSLOCTEXT("HistoryDetailsTitle", "Details", "History Details"))
		[
			DetailsView.ToSharedRef()
		];

	return NewTab;
}
