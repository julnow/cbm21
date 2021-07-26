TH2F *relativeError(TH2F *hrec, TH2F *hsim){ //finds relative error of division of 2 histograms

  TH2F *hrel = (TH2F*) hrec->Clone();

  float delta, delta1, delta2 = 0.f;
  float simContent, recContent;

   for (int i=1; i<=hrec->GetNbinsX(); i++) {
     for (int j=1; j<=hrec->GetNbinsY(); j++) {
       recContent = hrec->GetBinContent(i,j);
       simContent = hsim->GetBinContent(i,j);
       if (recContent != 0 && simContent != 0){
         //delta in 3 steps:
         delta1 = 1 / recContent;
         delta2 = 1 / simContent;
         delta = sqrt(delta1 + delta2);
         //relative error:
         hrel->SetBinContent(i, j, delta);
       }else{
          hrel->SetBinContent(i, j, 0);
       }
    }
  }
  return hrel;
}


void pfRead(const char *fileName, const char *outputFileName){

  TFile* fileInPF = TFile::Open(fileName, "read");
  TTree* treeInPF = fileInPF->Get<TTree>("aTree");

  //setting headers type
  auto* can_header = new AnalysisTree::Particles();
  auto* simr_header = new AnalysisTree::Particles(); //reconstructed
  auto* can2simr_matching = new AnalysisTree::Matching();

  //getting variables id
  AnalysisTree::Configuration* config = fileInPF->Get<AnalysisTree::Configuration>("Configuration");
  //headers for branches
  treeInPF->SetBranchAddress("Candidates", &can_header);
  treeInPF->SetBranchAddress("Simulated", &simr_header);
  treeInPF->SetBranchAddress(config->GetMatchName("Candidates", "Simulated").c_str(), &can2simr_matching);
  //treeInSIM->SetBranchAddress("SimParticles", &sims_tracks);

  //Candidates reconstructed
  const int canpx = config->GetBranchConfig("Candidates").GetFieldId("px");
  const int canpy = config->GetBranchConfig("Candidates").GetFieldId("py");
  const int canpz = config->GetBranchConfig("Candidates").GetFieldId("pz");
  const int canpt = config->GetBranchConfig("Candidates").GetFieldId("pT");
  const int canp = config->GetBranchConfig("Candidates").GetFieldId("p");
  const int chi2_geo = config->GetBranchConfig("Candidates").GetFieldId("chi2_geo");
  const int chi2_prim_first = config->GetBranchConfig("Candidates").GetFieldId("chi2_prim_first");
  const int chi2_prim_second = config->GetBranchConfig("Candidates").GetFieldId("chi2_prim_second");
  const int chi2_topo = config->GetBranchConfig("Candidates").GetFieldId("chi2_topo");
  const int canrap = config->GetBranchConfig("Candidates").GetFieldId("rapidity");
  const int canphi = config->GetBranchConfig("Candidates").GetFieldId("phi");
  const int cangen = config->GetBranchConfig("Candidates").GetFieldId("generation");
  const int canmass = config->GetBranchConfig("Candidates").GetFieldId("mass");
  //simulated reconstructed
  const int simrpx = config->GetBranchConfig("Simulated").GetFieldId("px");
  const int simrpy = config->GetBranchConfig("Simulated").GetFieldId("py");
  const int simrpz = config->GetBranchConfig("Simulated").GetFieldId("pz");
  const int simrpt = config->GetBranchConfig("Simulated").GetFieldId("pT");
  const int simrp = config->GetBranchConfig("Simulated").GetFieldId("p");

  //Candidates
  TH1F hcanpx("hcanpx", "#Lambda_{can} px;px [GeV/c];dN/dpx", 100, -3, 3);
  TH1F hcanpy("hcanpy", "#Lambda_{can} py;py [GeV/c];dN/dpy", 100, -3, 3);
  TH1F hcanpz("hcanpz", "#Lambda_{can} pz;pz [GeV/c];dN/dpz", 100, 0, 14);
  TH1F hcanpt("hcanpt", "#Lambda_{can} pt;pt [GeV/c];dN/dpt", 100, -1, 3);
  TH1F hcanp("hcanp", "#Lambda_{can} p;p [GeV/c];dN/dp", 100, 0, 14);
  TH1F hcanphi("hcanphi", "#Lambda_{can} #phi;#phi [rad];dN/d#phi", 100, -3.14, 3.14);
  //#Lambda_{can} - #Lambda_{sim}
  TH1F hdifpx("hdifpx", "#Lambda_{can} - #Lambda_{sim} px;px [GeV/c];dN/dpx", 100, -.4, .4);
  TH1F hdifpy("hdifpy", "#Lambda_{can} - #Lambda_{sim} py;py [GeV/c];dN/dpy", 100, -.4, .4);
  TH1F hdifpz("hdifpz", "#Lambda_{can} - #Lambda_{sim} pz;pz [GeV/c];dN/dpz", 100, -.8, .8);
  TH1F hdifpt("hdifpt", "#Lambda_{can} - #Lambda_{sim} pt;pt [GeV/c];dN/dpt", 100, -.4, .4);
  TH1F hdifp("hdifp", "#Lambda_{can} - #Lambda_{sim} p;p [GeV/c];dN/dp", 100, -.8, .8);
  TH2F hcormass("hcormass", "correlations mass; K_{can}; K_{sim}", 100, 0, 1,  100, 0, 1);
  //correlations
  TH2F hcorpx("hcorpx", "correlations px; #Lambda_{can}; #Lambda_{sim}", 100, -3, 3,  100, -3, 3);
  TH2F hcorpy("hcorpy", "correlations py; #Lambda_{can}; #Lambda_{sim}", 100, -3, 3,  100, -3, 3);
  TH2F hcorpz("hcorpz", "correlations pz; #Lambda_{can}; #Lambda_{sim}", 100, 0, 14,  100, 0, 14);
  TH2F hcorr_px_py("hcorr_px_py", "correlations #Lambda_{can} px py; px [GeV/c]; py [GeV/c]", 100, -3, 3,  100, -3, 3);
  TH2F hcorpt("hcorpt", "correlations pt; #Lambda_{can}; #Lambda_{sim}", 100, -1, 3,  100, -1, 3);
  TH2F hcorp("hcorp", "correlations p; #Lambda_{can}; #Lambda_{sim}", 100, 0, 14,  100, 0, 14);
  TH2F hcorr_rap_pt("hcorr_rap_pt", "correlation #Lambda_{can} rapidity pT; rapidity; pT [GeV/c]", 100, -1, 4,  100, -1, 4);
  TH2F hcorr_phi_pt("hcorr_phi_pt", "correlation #Lambda_{can} #phi pT; #phi [#circ]; pT [GeV/c]", 100, -5, 5,  100, -0.01, 5);
  //chi2
  TH1F hchi2_geo("chi2_geo", "chi2_geo; chi2_geo; #", 100, -1, 6);
  TH1F hchi2_prim_first("chi2_prim_first", "chi2_prim_first; chi2_prim_first; #", 200, -1, 1000);
  TH1F hchi2_prim_second("chi2_prim_second", "chi2_prim_second; chi2_prim_second; #", 200, -1, 1000);
  TH1F hchi2_topo("chi2_topo", "chi2_topo; chi2_topo; #", 100, -1, 10);

  //reading of data from simulated histogramsfile
  TFile simFile("simulatedHistograms.root");
  TH1F* hsimspx;
  TH1F* hsimspy;
  TH1F* hsimspz;
  TH1F* hsimspt;
  TH1F* hsimsp;
  //correlations for sim
  TH2F* hcors_rap_pt;
  TH2F* hcors_phi_pt;
  TH2F* hcors_px_py;
  simFile.GetObject("hsimspx",hsimspx);
  hsimspx->SetDirectory(0);
  simFile.GetObject("hsimspy",hsimspy);
  hsimspy->SetDirectory(0);
  simFile.GetObject("hsimspz",hsimspz);
  hsimspz->SetDirectory(0);
  simFile.GetObject("hsimspt",hsimspt);
  hsimspt->SetDirectory(0);
  simFile.GetObject("hsimsp",hsimsp);
  hsimsp->SetDirectory(0);
  simFile.GetObject("hcors_rap_pt",hcors_rap_pt);
  hcors_rap_pt->SetDirectory(0);
  simFile.GetObject("hcors_phi_pt",hcors_phi_pt);
  hcors_phi_pt->SetDirectory(0);
  simFile.GetObject("hcors_px_py",hcors_px_py);
  hcors_px_py->SetDirectory(0);
  simFile.Close();

    //reading data from pfsimple file
    //pfsimple
    const int NeventsPF = treeInPF->GetEntries();
    for(int i=0; i<NeventsPF; i++){
      treeInPF -> GetEntry(i);
    //candidates
    for (const auto& can_head : *can_header){
      //Candidates
      if (can_head.GetField<float>(cangen) == 0) continue; //only singal, not background (gen=0)
      const float can_px = can_head.GetField<float>(canpx);
      const float can_py = can_head.GetField<float>(canpy);
      const float can_pz = can_head.GetField<float>(canpz);
      const float can_pt = can_head.GetField<float>(canpt);
      const float can_p = can_head.GetField<float>(canp);
      const float can_rap = can_head.GetField<float>(canrap);
      const float can_phi = can_head.GetField<float>(canphi);
      const float can_mass = can_head.GetField<float>(canmass);

      hcanpx.Fill(can_px);
      hcanpy.Fill(can_py);
      hcanpz.Fill(can_pz);
      hcanpt.Fill(can_pt);
      hcanp.Fill(can_p);
      hcanmass.Fill(can_mass);
      //correlation for reconstructed
      hcorr_rap_pt.Fill(can_rap, can_pt);
      hcorr_px_py.Fill(can_px, can_py);
      hcorr_phi_pt.Fill(can_phi, can_pt);
      //simulated
      const int simr_id = can2simr_matching->GetMatch(can_head.GetId());
      if(simr_id<0) continue;
      const float simr_px = simr_header->GetChannel(simr_id).GetField<float>(simrpx);
      const float simr_py = simr_header->GetChannel(simr_id).GetField<float>(simrpy);
      const float simr_pz = simr_header->GetChannel(simr_id).GetField<float>(simrpz);
      const float simr_pt = simr_header->GetChannel(simr_id).GetField<float>(simrpt);
      const float simr_p = simr_header->GetChannel(simr_id).GetField<float>(simrp);
      //differences
      hdifpx.Fill(can_px - simr_px);
      hdifpy.Fill(can_py - simr_py);
      hdifpz.Fill(can_pz - simr_pz);
      hdifpt.Fill(can_pt - simr_pt);
      hdifp.Fill(can_p - simr_p);
      //correlations
      hcorpx.Fill(can_px, simr_px);
      hcorpy.Fill(can_py, simr_py);
      hcorpz.Fill(can_pz, simr_pz);
      hcorpt.Fill(can_pt, simr_pt);
      hcorp.Fill(can_p, simr_p);
      //chi2
      const float can_chi2_geo = can_head.GetField<float>(chi2_geo);
      const float can_chi2_prim_first = can_head.GetField<float>(chi2_prim_first);
      const float can_chi2_prim_second = can_head.GetField<float>(chi2_prim_second);
      const float can_chi2_topo = can_head.GetField<float>(chi2_topo);
      hchi2_geo.Fill(can_chi2_geo);
      hchi2_prim_first.Fill(can_chi2_prim_first);
      hchi2_prim_second.Fill(can_chi2_prim_second);
      hchi2_topo.Fill(can_chi2_topo);

    }
  }
  //division of histograms
  TH2F* hcord_rap_pt;
  hcord_rap_pt = (TH2F*) hcorr_rap_pt.Clone();
  hcord_rap_pt->Divide(hcors_rap_pt);
  hcord_rap_pt->SetNameTitle("hcord_rap_pt", "division correlation rapidity pt; rapidity; pT");
  TH2F* hcordr_rap_pt = relativeError(&hcorr_rap_pt, hcors_rap_pt); //relative error
  hcordr_rap_pt->SetNameTitle("hcordr_rap_pt", "#frac{#Delta #varepsilon}{#varepsilon} correlation rapidity pT; rapidity; pT");
  TH2F* hcord_phi_pt;
  hcord_phi_pt = (TH2F*) hcorr_phi_pt.Clone();
  hcord_phi_pt->Divide(hcors_phi_pt);
  hcord_phi_pt->SetNameTitle("hcord_rphi_pt", "division correlation #phi pT; #phi; pT");
  TH2F* hcordr_phi_pt = relativeError(&hcorr_phi_pt, hcors_phi_pt); //relative error
  hcordr_phi_pt->SetNameTitle("hcordr_phi_pt", "#frac{#Delta #varepsilon}{#varepsilon} correlation #phi pT; #phi; pT");
  TH2F* hcord_px_py;
  hcord_px_py = (TH2F*) hcorr_px_py.Clone();
  hcord_px_py->Divide(hcors_px_py);
  hcord_px_py->SetNameTitle("hcord_px_py", "division correlations px py; px; py");
  TH2F* hcordr_px_py = relativeError(&hcorr_px_py, hcors_px_py); //relative error
  hcordr_px_py->SetNameTitle("hcordr_px_py", "#frac{#Delta #varepsilon}{#varepsilon} correlation px py; px; py");

  TFile* fileOut1 = TFile::Open(outputFileName, "recreate");

  hcanpx.Write();
  hcanpy.Write();
  hcanpz.Write();
  hcanpt.Write();
  hcanp.Write();
  hsimspx->Write();
  hsimspy->Write();
  hsimspz->Write();
  hsimspt->Write();
  hsimsp->Write();
  hdifpx.Write();
  hdifpy.Write();
  hdifpz.Write();
  hdifpt.Write();
  hdifp.Write();
  hcorpx.Write();
  hcorpy.Write();
  hcorpz.Write();
  hcorpt.Write();
  hcorp.Write();
  hcanmass.Write();
  hchi2_geo.Write();
  hchi2_prim_first.Write();
  hchi2_prim_second.Write();
  hchi2_topo.Write();
  hcorr_px_py.Write();
  hcorr_rap_pt.Write();
  hcorr_phi_pt.Write();
  hcors_px_py->Write();
  hcors_rap_pt->Write();
  hcors_phi_pt->Write();
  hcord_rap_pt->Write();
  hcordr_rap_pt->Write();
  hcord_px_py->Write();
  hcordr_px_py->Write();
  hcord_phi_pt->Write();
  hcordr_phi_pt->Write();

  fileOut1->Close();
}
