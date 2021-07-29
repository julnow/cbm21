
//reading from pfsimple for each file
void pfRead_cut_all(const char *fileName, const char *outputFileName){

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
  //cuts
  const int chi2_geo = config->GetBranchConfig("Candidates").GetFieldId("chi2_geo");
  const int chi2_prim_first = config->GetBranchConfig("Candidates").GetFieldId("chi2_prim_first");
  const int chi2_prim_second = config->GetBranchConfig("Candidates").GetFieldId("chi2_prim_second");
  const int chi2_topo = config->GetBranchConfig("Candidates").GetFieldId("chi2_topo");
  const int cosine_first = config->GetBranchConfig("Candidates").GetFieldId("cosine_first");
  const int cosine_second = config->GetBranchConfig("Candidates").GetFieldId("cosine_second");
  const int cosine_topo = config->GetBranchConfig("Candidates").GetFieldId("cosine_topo");
  const int distance = config->GetBranchConfig("Candidates").GetFieldId("distance");
  const int l_over_dl = config->GetBranchConfig("Candidates").GetFieldId("l_over_dl");


  //other parms
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
  const int simrmass = config->GetBranchConfig("Simulated").GetFieldId("mass");

  //Candidates
  TH1F hcanpx("hcanpx", "K_{can} px;px [GeV/c];dN/dpx", 100, -2, 2);
  TH1F hcanpy("hcanpy", "K_{can} py;py [GeV/c];dN/dpy", 100, -2, 2);
  TH1F hcanpz("hcanpz", "K_{can} pz;pz [GeV/c];dN/dpz", 100, 0, 12);
  TH1F hcanpt("hcanpt", "K_{can} pt;pt [GeV/c];dN/dpt", 100, -.1, 2);
  TH1F hcanp("hcanp", "K_{can} p;p [GeV/c];dN/dp", 100, 0, 12);
  TH1F hcanphi("hcanphi", "K_{can} #phi;#phi [rad];dN/d#phi", 100, -3.14, 3.14);
  TH1F hcanmass("hcanmass", "K_{can} mass;mass [GeV/c^{2}];dN/dmass", 100, 0.3, .7);
  //K_{can} - K_{sim}
  TH1F hdifpx("hdifpx", "K_{can} - K_{sim} px;px [GeV/c];dN/dpx", 100, -2, 2);
  TH1F hdifpy("hdifpy", "K_{can} - K_{sim} py;py [GeV/c];dN/dpy", 100, -2, 2);
  TH1F hdifpz("hdifpz", "K_{can} - K_{sim} pz;pz [GeV/c];dN/dpz", 100, -12, 12);
  TH1F hdifpt("hdifpt", "K_{can} - K_{sim} pt;pt [GeV/c];dN/dpt", 100, -2, 2);
  TH1F hdifp("hdifp", "K_{can} - K_{sim} p;p [GeV/c];dN/dp", 100, -12, 12);
  //correlations
  TH2F hcorpx("hcorpx", "correlations px; K_{can}; K_{sim}", 100, -2, 2,  100, -2, 2);
  TH2F hcorpy("hcorpy", "correlations py; K_{can}; K_{sim}", 100, -2, 2,  100, -2, 2);
  TH2F hcorpz("hcorpz", "correlations pz; K_{can}; K_{sim}", 100, -8, 8,  100, -8, 20);
  TH2F hcormass("hcormass", "correlations mass; K_{can}; K_{sim}", 100, 0, 1,  100, 0, 1);
  TH2F hcorpt("hcorpt", "correlations pt; K_{can}; K_{sim}", 100, -1, 3,  100, -1, 3);
  TH2F hcorp("hcorp", "correlations p; K_{can}; K_{sim}", 100, -8, 8,  100, 0, 20);
  TH2F hcorr_rap_pt("hcorr_rap_pt", "correlation K_{can} rapidity pT; rapidity; pT [GeV/c]", 100, -1, 4,  100, -1, 4);
  TH2F hcorr_phi_pt("hcorr_phi_pt", "correlation K_{can} #phi pT; #phi [#circ]; pT [GeV/c]", 100, -5, 5,  100, -0.01, 5);\
  TH2F hcorr_px_py("hcorr_px_py", "correlations K_{can} px py; px [GeV/c]; py [GeV/c]", 100, -3, 3,  100, -3, 3);
  //chi2
  TH1F hchi2_geo("hchi2_geo", "#chi^{2} geometric; #chi^{2}_{geo}; counts", 2000, 0, 1000);
  TH1F hchi2_prim_first("hchi2_prim_first", "#chi^{2} primary for #pi_{+}; #chi^{2}_{prim}; counts", 2000, 0, 1000);
  TH1F hchi2_prim_second("hchi2_prim_second", "#chi^{2} primary for #pi_{-}; #chi^{2}_{prim}; counts", 2000, 0, 1000);
  TH1F hchi2_topo("hchi2_topo", "#chi^{2} topological; #chi^{2}_{topo}; counts", 2000, 0, 1000);
  TH1F hcosine_first("hcosine_first", "cosine of angle between #pi_{+} and kaon; cos #alpha_{K #pi_{+}}; counts", 1000, .9, 1);
  TH1F hcosine_second("hcosine_second", "cosine of angle between #pi_{-} and kaon; cos #alpha_{K #pi_{+}}; counts", 1000, .9, 1);
  TH1F hcosine_topo("hcosine_topo", "cosine topological; cos_{topo}; counts", 1000, -1, 1);
  TH1F hdistance("hdistance", "DCA between secondary tracks; DCA_{#pi_{+}#pi_{-}} [cm]; counts", 500, 0, 6);
  TH1F hl_over_dl("hl_over_dl", "#frac{L}{#Delta L}; #frac{L}{#Delta L}; counts", 200, 0, 100);


    //reading data from pfsimple file
    //pfsimple
    const int NeventsPF = treeInPF->GetEntries();
    for(int i=0; i<NeventsPF; i++){
      treeInPF -> GetEntry(i);
    //candidates
    for (const auto& can_head : *can_header){
      //Candidates
     // if (can_head.GetField<int>(cangen) != 0) continue; //only singal, not background (gen=0)
     const float can_chi2_geo = can_head.GetField<float>(chi2_geo);
     const float can_chi2_prim_first = can_head.GetField<float>(chi2_prim_first);
     const float can_chi2_prim_second = can_head.GetField<float>(chi2_prim_second);
     const float can_chi2_topo = can_head.GetField<float>(chi2_topo);
     const float can_cosine_first = can_head.GetField<float>(cosine_first);
     const float can_cosine_second = can_head.GetField<float>(cosine_second);
     const float can_cosine_topo = can_head.GetField<float>(cosine_topo);
     const float can_distance = can_head.GetField<float>(distance);
     const float can_l_over_dl = can_head.GetField<float>(l_over_dl);
     //cuts
     if (can_l_over_dl < 40) continue;
     if (can_distance > 0.4) continue;
     if (can_chi2_geo > 20) continue;
     if (can_chi2_topo > 12) continue;


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
      hcanphi.Fill(can_phi);
      hcanmass.Fill(can_mass);
      //correlation for reconstructed
      hcorr_rap_pt.Fill(can_rap, can_pt);
      hcorr_px_py.Fill(can_px, can_py);
      hcorr_phi_pt.Fill(can_phi, can_pt);
      //chi2

      hchi2_geo.Fill(can_chi2_geo);
      hchi2_prim_first.Fill(can_chi2_prim_first);
      hchi2_prim_second.Fill(can_chi2_prim_second);
      hchi2_topo.Fill(can_chi2_topo);
      hcosine_first.Fill(can_cosine_first);
      hcosine_second.Fill(can_cosine_second);
      hcosine_topo.Fill(can_cosine_topo);
      hdistance.Fill(can_distance);
      hl_over_dl.Fill(can_l_over_dl);
      //simulated
      const int simr_id = can2simr_matching->GetMatch(can_head.GetId());
      if(simr_id<0) continue;
      const float simr_px = simr_header->GetChannel(simr_id).GetField<float>(simrpx);
      const float simr_py = simr_header->GetChannel(simr_id).GetField<float>(simrpy);
      const float simr_pz = simr_header->GetChannel(simr_id).GetField<float>(simrpz);
      const float simr_pt = simr_header->GetChannel(simr_id).GetField<float>(simrpt);
      const float simr_p = simr_header->GetChannel(simr_id).GetField<float>(simrp);
      const float simr_mass = simr_header->GetChannel(simr_id).GetField<float>(simrmass);
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
      hcormass.Fill(can_mass, simr_mass);


    }
  }

  TFile* fileOut1 = TFile::Open(outputFileName, "recreate");

  hcanpx.Write();
  hcanpy.Write();
  hcanpz.Write();
  hcanpt.Write();
  hcanp.Write();
  hcanphi.Write();
  hcanmass.Write();
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
  hcormass.Write();
  hchi2_geo.Write();
  hchi2_prim_first.Write();
  hchi2_prim_second.Write();
  hchi2_topo.Write();
  hcosine_first.Write();
  hcosine_second.Write();
  hcosine_topo.Write();
  hdistance.Write();
  hl_over_dl.Write();
  hcorr_px_py.Write();
  hcorr_rap_pt.Write();
  hcorr_phi_pt.Write();


  fileOut1->Close();
}
