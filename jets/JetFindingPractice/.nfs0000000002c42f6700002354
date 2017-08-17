AliAnalysisTaskPatJet* AddTaskPatJet(
    const char *ntracks = "usedefault",
    const char *nclusters = "usedefault",
    const char *ncells = "usedefault"
)
{

    // Get the pointer to the existing analysis manager via the static access method.
    //==============================================================================
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr)
    {
        ::Error("AddTaskEmcalJetSample", "No analysis manager to connect to.");
        return 0;
    }

    // Check the analysis type using the event handlers connected to the analysis manager.
    //==============================================================================
    AliVEventHandler* handler = mgr->GetInputEventHandler();
    if (!handler)
    {
        ::Error("AddTaskEmcalJetSample", "This task requires an input event handler");
        return 0;
    }

    TString trackName(ntracks);
    TString clusName(nclusters);
    TString cellName(ncells);

    if (trackName == "usedefault") {
        trackName = "tracks";
    }

    if (clusName == "usedefault") {
        clusName = "caloClusters";
    }

    if (cellName == "usedefault") {
        cellName = "emcalCells";
    }

    TString name("AliAnalysisTaskPatJet");

    if (!trackName.IsNull()) {
        name += "_";
        name += trackName;
    }

    if (!clusName.IsNull()) {
        name += "_";
        name += clusName;
    }

    if (!cellName.IsNull()) {
        name += "_";
        name += cellName;
    }

    AliAnalysisTaskPatJet *jetTask = new AliAnalysisTaskPatJet(name.Data());

    
    
    jetTask->AddClusterContainer(clusName);

    AliTrackContainer* trackCont = jetTask->AddTrackContainer(trackName);


    mgr->AddTask(jetTask);

    AliAnalysisDataContainer *cin1 = mgr->GetCommonInputContainer();

    TString contname(name);
    contname += "_histos";

    AliAnalysisDataContainer *cout1 = mgr->CreateContainer(contname.Data(), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s", AliAnalysisManager::GetCommonFileName()));

    mgr->ConnectInput(jetTask, 0, cin1);
    mgr->ConnectOutput(jetTask, 1, cout1);


    return jetTask;
}












