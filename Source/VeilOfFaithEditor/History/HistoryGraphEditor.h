// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class URootHistoryElement;
class UBaseHistoryElement;
class UHistoryElement;
class UHistoryGraph;

class VEILOFFAITHEDITOR_API FHistoryGraphEditor : public FAssetEditorToolkit
{
public:
	void InitHistoryGraphAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost,
	                                UBaseHistoryElement* HistoryElement, URootHistoryElement* InRootElement);
    
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
    
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	TObjectPtr<UHistoryGraph> EdGraph;
	TObjectPtr<URootHistoryElement> RootElement;
    
private:
	TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args) const;
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args) const;

	void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);
	void OnNodeDoubleClicked(UEdGraphNode* Node);

	void OnCommandDeleteSelectedNodes();
	void OnCommandCopySelectedNodes();
	void OnCommandPasteNodes();

	void SetElementsToHistoryConfig();
	void RecursiveGatherElements(UBaseHistoryElement* ParentElement,
		TMap<FGuid, TObjectPtr<UBaseHistoryElement>>& Elements);

	TSharedRef<FHistoryGraphEditor> TryCreateHistoryGraphEditor(
		EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UBaseHistoryElement* HistoryElement,
		URootHistoryElement* AssetElement);

	UHistoryGraph* CreateHistoryGraph();

	TObjectPtr<UBaseHistoryElement> CurrentElement;
	
	TSharedPtr<SGraphEditor> GraphEditor;
	TSharedPtr<FUICommandList> GraphEditorCommands;
	TSharedPtr<IDetailsView> DetailsView;
	TSharedPtr<IToolkitHost> ToolkitHost;
};
