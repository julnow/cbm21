void momentum(){

  //TString fileName = "1.analysistree.root";
  //TFile* fileIn = TFile::Open(fileName, "read");
  //TTree* treeIn = fileIn->Get<TTree>("rTree");
  AnalysisTree::Chain* treeIn = new AnalysisTree::Chain(std::vector<std::string>({"~/filelist.txt"}), std::vector<std::string>({"rTree"}));


  auto* eve_header = new AnalysisTree::EventHeader();
  auto* rec_header = new AnalysisTree::EventHeader();
  auto* sim_tracks = new AnalysisTree::Particles();
  auto* vtx_tracks = new AnalysisTree::TrackDetector();
  auto* sim_vtx_matching = new AnalysisTree::Matching();

  //AnalysisTree::Configuration* config = fileIn->Get<AnalysisTree::Configuration>("Configuration");
  //treeIn->GetConfiguration() instead of congif
  const int sp = treeIn->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("p"); //simulated
  const int spT = treeIn->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("pT");
  const int seta = treeIn->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("eta");
  const int sphi = treeIn->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("phi");
  const int srap = treeIn->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("rapidity");
  const int sx = treeIn->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("x");
  const int sy = treeIn->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("y");
  const int sz = treeIn->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("z");
  const int rp = treeIn->GetConfiguration()->GetBranchConfig("VtxTracks").GetFieldId("p"); //reconstructed
  const int rpT = treeIn->GetConfiguration()->GetBranchConfig("VtxTracks").GetFieldId("pT");
  const int reta = treeIn->GetConfiguration()->GetBranchConfig("VtxTracks").GetFieldId("eta");
  const int rphi = treeIn->GetConfiguration()->GetBranchConfig("VtxTracks").GetFieldId("phi");



  treeIn->SetBranchAddress("SimParticles", &sim_tracks);
  treeIn->SetBranchAddress("VtxTracks", &vtx_tracks);
  treeIn->SetBranchAddress("RecEventHeader", &rec_header);
  treeIn->SetBranchAddress(treeIn->GetConfiguration()->GetMatchName("VtxTracks", "SimParticles").c_str(), &sim_vtx_matching);

  int N = 0;

  const int Nevents = treeIn->GetEntries();

  //zadania
  TFile* fileOut1 = TFile::Open("momentum.root", "recreate");
  TH1F hspx("hspx", "sim px;px [GeV/c];dN/dpx", 1000, -3, 3); //simulated
  TH1F hspy("hspy", "sim py;py [GeV/c];dN/dpy", 1000, -3, 3);
  TH1F hspz("hspz", "sim pz;pz [GeV/c];dN/dpz", 1000, 0, 6);
  TH1F hsphi("hsphi", "sim phi", 1000, 0, 6);
  TH1F hsp("hsp", "sim p", 1000, 0, 6);
  TH1F hspt("hspt", "sim pt;pt [GeV/c];dN/dpt", 1000, 0, 6);
  TH1F hseta("hseta", "sim eta", 1000, 0, 6);
  TH1F hsrap("hsrap", "sim rapidity", 1000, -3, 6);
  TH1F hsx("hsx", "sim x", 1000, -3, 3);
  TH1F hsy("hsy", "sim y", 1000, -3, 3);
  TH1F hsz("hsz", "sim z", 2100, -100, 2000);
  TH1F hrpx("hrpx", "rec px;px [GeV/c];dN/dpx", 1000, -3, 3); //reconstructed
  TH1F hrpy("hrpy", "rec py;py [GeV/c];dN/dpy", 1000, -3, 3);
  TH1F hrpz("hrpz", "rec pz;pz [GeV/c];dN/dpz", 1000, 0, 6);
  TH1F hrphi("hrphi", "rec phi", 1000, 0, 6);
  TH1F hrp("hrp", "rec p", 1000, 0, 6);
  TH1F hrpt("hrpt", "rec pz", 1000, 0, 6);
  TH1F hreta("hreta", "rec eta", 1000, 0, 6);
//  TH1F hrrap("hrrap", "rec rapidity", 1000, -3, 3);
  TH2F hcpx("hcpx", "cor px", 1000, -3, 3, 1000, -3, 3); //correlation
  TH2F hcpy("hcpy", "cor py", 1000, -3, 3, 1000, -3, 3);
  TH2F hcpz("hcpz", "cor pz", 1000, 0, 6, 1000, 0, 6);
  TH2F hcphi("hcphi", "cor phi", 1000, 0, 6, 1000, 0, 6);
  TH2F hcp("hcp", "cor p", 1000, 0, 6, 1000, 0, 6);
  TH2F hcpt("hcpt", "cor pt", 1000, 0, 6, 1000, 0, 6);
  TH2F hceta("hceta", "cor peta", 1000, 0, 6, 1000, 0, 6);
  TH2F hcrpxpy("hcpxpy", "cor rec pxpy", 1000, -3, 3, 1000, -3, 3);

  for(int i=0; i<Nevents; i++){
    treeIn -> GetEntry(i);


    //simulated
    for(const auto& sim_track : *(sim_tracks->GetChannels()) ){
      const float sim_px = sim_track.GetPx();
      const float sim_py = sim_track.GetPy();
      const float sim_pz = sim_track.GetPz();
      const float sim_p = sim_track.GetField<float>(sp);
      const float sim_pt = sim_track.GetField<float>(spT);
      const float sim_eta = sim_track.GetField<float>(seta);
      const float sim_phi = sim_track.GetField<float>(sphi);
      const float sim_rap = sim_track.GetField<float>(srap);
      const float sim_x = sim_track.GetField<float>(sx);
      const float sim_y = sim_track.GetField<float>(sy);
      const float sim_z = sim_track.GetField<float>(sz);
      hspx.Fill(sim_px);
      hspy.Fill(sim_py);
      hspz.Fill(sim_pz);
      hsp.Fill(sim_p);
      hspt.Fill(sim_pt);
      hseta.Fill(sim_eta);
      hsphi.Fill(sim_phi);
      hsrap.Fill(sim_rap);
      hsx.Fill(sim_x);
      hsy.Fill(sim_y);
      hsz.Fill(sim_z);
    }
    //reconstructed and correlations
    for(const auto& vtx_track : *(vtx_tracks->GetChannels()) ){
           const float rec_px = vtx_track.GetPx(); //reconstructed
           const float rec_py = vtx_track.GetPy();
           const float rec_pz = vtx_track.GetPz();
           const float rec_p = vtx_track.GetField<float>(rp);
           const float rec_pt = vtx_track.GetField<float>(rpT);
           const float rec_eta = vtx_track.GetField<float>(reta);
           const float rec_phi = vtx_track.GetField<float>(rphi);
           hrpx.Fill(rec_px);
           hrpy.Fill(rec_py);
           hrpz.Fill(rec_pz);
           hrp.Fill(rec_p);
           hrpt.Fill(rec_pt);
           hreta.Fill(rec_eta);
           hrphi.Fill(rec_phi);
           const int sim_id = sim_vtx_matching->GetMatch(vtx_track.GetId()); //simulated, match with vtx
           if(sim_id<0) continue;
           const float sim_px = sim_tracks->GetChannel(sim_id).GetPx();
           const float sim_py = sim_tracks->GetChannel(sim_id).GetPy();
           const float sim_pz = sim_tracks->GetChannel(sim_id).GetPz();
           const float sim_p = sim_tracks->GetChannel(sim_id).GetField<float>(sp);
           const float sim_pt = sim_tracks->GetChannel(sim_id).GetField<float>(spT);
           const float sim_eta = sim_tracks->GetChannel(sim_id).GetField<float>(seta);
           const float sim_phi = sim_tracks->GetChannel(sim_id).GetField<float>(sphi);
           const float sim_rap = sim_tracks->GetChannel(sim_id).GetField<float>(srap);
           const float sim_x = sim_tracks->GetChannel(sim_id).GetField<float>(sx);
           const float sim_y = sim_tracks->GetChannel(sim_id).GetField<float>(sy);
           const float sim_z = sim_tracks->GetChannel(sim_id).GetField<float>(sz);
           //correlations
           hcpx.Fill(rec_px, sim_px);
           hcpy.Fill(rec_py, sim_py);
           hcpz.Fill(rec_pz, sim_pz);
           hcp.Fill(rec_p, sim_p);
           hcpt.Fill(rec_pt, sim_pt);
           hceta.Fill(rec_eta, sim_eta);
           hcphi.Fill(rec_phi, sim_phi);
           hcrpxpy.Fill(rec_px, rec_py);
    }
  }

   hspx.Write();
   hspy.Write();
   hspz.Write();
   hsp.Write();
   hspt.Write();
   hseta.Write();
   hsphi.Write();
   hsrap.Write();
   hsx.Write();
   hsy.Write();
   hsz.Write();
   hrpx.Write();
   hrpy.Write();
   hrpz.Write();
   hrp.Write();
   hrpt.Write();
   hreta.Write();
   hrphi.Write();
  // hrrap.Write();
   hcpx.GetXaxis()->SetTitle("reconstructed");
   hcpx.GetYaxis()->SetTitle("simulated");
   hcpx.Write();
   hcpy.GetXaxis()->SetTitle("reconstructed");
   hcpy.GetYaxis()->SetTitle("simulated");
   hcpy.Write();
   hcpz.GetXaxis()->SetTitle("reconstructed");
   hcpz.GetYaxis()->SetTitle("simulated");
   hcpz.Write();
   hcp.GetXaxis()->SetTitle("reconstructed");
   hcp.GetYaxis()->SetTitle("simulated");
   hcp.Write();
   hcp.GetXaxis()->SetTitle("reconstructed");
   hcp.GetYaxis()->SetTitle("simulated");
   hcpt.Write();
   hceta.GetXaxis()->SetTitle("reconstructed");
   hceta.GetYaxis()->SetTitle("simulated");
   hceta.Write();
   hcphi.GetXaxis()->SetTitle("reconstructed");
   hcphi.GetYaxis()->SetTitle("simulated");
   hcphi.Write();
   hcrpxpy.GetXaxis()->SetTitle("reconstructed");
   hcrpxpy.GetYaxis()->SetTitle("simulated");
   hcrpxpy.Write();

  fileOut1->Close();
}
