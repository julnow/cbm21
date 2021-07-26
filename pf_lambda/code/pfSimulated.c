void pfSimulated(){

AnalysisTree::Chain* treeInSIM = new AnalysisTree::Chain(std::vector<std::string>({"fileslist.txt"}), std::vector<std::string>({"rTree"}));


auto* sims_tracks = new AnalysisTree::Particles();
treeInSIM->SetBranchAddress("SimParticles", &sims_tracks);

//simulated Simulated
const int simspx = treeInSIM->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("px");
const int simspy = treeInSIM->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("py");
const int simspz = treeInSIM->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("pz");
const int simspt = treeInSIM->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("pT");
const int simsp = treeInSIM->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("p");
const int simsrap = treeInSIM->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("rapidity");
const int simsphi = treeInSIM->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("phi");
const int simspid = treeInSIM->GetConfiguration()->GetBranchConfig("SimParticles").GetFieldId("pid");

//momentum
TH1F hsimspx("hsimspx", "#Lambda_{sim} px;px [GeV/c];dN/dpx", 100, -3, 3);
TH1F hsimspy("hsimspy", "#Lambda_{sim} py;py [GeV/c];dN/dpy", 100, -3, 3);
TH1F hsimspz("hsimspz", "#Lambda_{sim} pz;pz [GeV/c];dN/dpz", 100, 0, 14);
TH1F hsimspt("hsimspt", "#Lambda_{sim} pt;pt [GeV/c];dN/dpt", 100, -1, 3);
TH1F hsimsp("hsimsp", "#Lambda_{sim} p;p [GeV/c];dN/dp", 100, 0, 14);
//correlations for sim
TH2F hcors_rap_pt("hcors_rap_pt", "correlation #Lambda_{sim} rapidity pt; rapidity; pT [GeV/c]", 100, -1, 4,  100, -1, 4);
TH2F hcors_phi_pt("hcors_phi_pt", "correlation #Lambda_{sim} #phi pt; #phi [#circ]; pT [GeV/c]", 100, -5, 5,  100, -0.01, 5);
TH2F hcors_px_py("hcors_px_py", "correlations #Lambda_{sim} px py; px [GeV/c]; py [GeV/c]", 100, -3, 3,  100, -3, 3);

//reading of data

//simulation
const int NeventsSIM = treeInSIM->GetEntries();
for(int i=0; i<NeventsSIM; i++){
  treeInSIM -> GetEntry(i);
  //simulated simulated
  for(const auto& sim_track : *(sims_tracks->GetChannels()) ){
    if (sim_track.GetField<int>(simspid) == 3122){
      const float sims_px = sim_track.GetField<float>(simspx);
      const float sims_py = sim_track.GetField<float>(simspy);
      const float sims_pz = sim_track.GetField<float>(simspz);
      const float sims_pt = sim_track.GetField<float>(simspt);
      const float sims_p = sim_track.GetField<float>(simsp);
      const float sims_rap = sim_track.GetField<float>(simsrap);
      const float sims_phi = sim_track.GetField<float>(simsphi);
      hsimspx.Fill(sims_px);
      hsimspy.Fill(sims_py);
      hsimspz.Fill(sims_pz);
      hsimspt.Fill(sims_pt);
      hsimsp.Fill(sims_p);
      //correlations for simulated
      hcors_rap_pt.Fill(sims_rap, sims_pt);
      hcors_px_py.Fill(sims_px, sims_py);
      hcors_phi_pt.Fill(sims_phi, sims_pt);
    }
  }
}

TFile* fileOut1 = TFile::Open("simulatedHistograms.root", "recreate");

hsimspx.Write();
hsimspy.Write();
hsimspz.Write();
hsimspt.Write();
hsimsp.Write();
hcors_rap_pt.Write();
hcors_px_py.Write();
hcors_phi_pt.Write();

fileOut1->Close();
}
