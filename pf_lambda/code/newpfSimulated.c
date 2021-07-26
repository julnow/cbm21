#include<iostream>
#include<string>
#include<cmath>
#include<fstream>

void newpfSimulated(const char *fileName, const char *output){


  TFile* fileIn = TFile::Open(fileName, "read");
  TTree* treeInSIM = fileIn->Get<TTree>("rTree");
//AnalysisTree::Chain* treeInSIM = new AnalysisTree::Chain(std::vector<std::string>({"fileslist.txt"}), std::vector<std::string>({"rTree"}));


auto* sims_tracks = new AnalysisTree::Particles();
treeInSIM->SetBranchAddress("SimParticles", &sims_tracks);
AnalysisTree::Configuration* config = fileIn->Get<AnalysisTree::Configuration>("Configuration");

//simulated Simulated
const int simspx = config->GetBranchConfig("SimParticles").GetFieldId("px");
const int simspy = config->GetBranchConfig("SimParticles").GetFieldId("py");
const int simspz = config->GetBranchConfig("SimParticles").GetFieldId("pz");
const int simspt = config->GetBranchConfig("SimParticles").GetFieldId("pT");
const int simsp = config->GetBranchConfig("SimParticles").GetFieldId("p");
const int simsrap = config->GetBranchConfig("SimParticles").GetFieldId("rapidity");
const int simsphi = config->GetBranchConfig("SimParticles").GetFieldId("phi");
const int simspid = config->GetBranchConfig("SimParticles").GetFieldId("pid");

//momentum
TH1F hsimspx("hsimspx", "#K_{sim} px;px [GeV/c];dN/dpx", 100, -3, 3);
TH1F hsimspy("hsimspy", "#K_{sim} py;py [GeV/c];dN/dpy", 100, -3, 3);
TH1F hsimspz("hsimspz", "#K_{sim} pz;pz [GeV/c];dN/dpz", 100, 0, 14);
TH1F hsimspt("hsimspt", "#K_{sim} pt;pt [GeV/c];dN/dpt", 100, -1, 3);
TH1F hsimsp("hsimsp", "#K_{sim} p;p [GeV/c];dN/dp", 100, 0, 14);
//correlations for sim
TH2F hcors_rap_pt("hcors_rap_pt", "correlation #K_{sim} rapidity pt; rapidity; pT [GeV/c]", 100, -1, 4,  100, -1, 4);
TH2F hcors_phi_pt("hcors_phi_pt", "correlation #K_{sim} #phi pt; #phi [#circ]; pT [GeV/c]", 100, -5, 5,  100, -0.01, 5);
TH2F hcors_px_py("hcors_px_py", "correlations #K_{sim} px py; px [GeV/c]; py [GeV/c]", 100, -3, 3,  100, -3, 3);

//reading of data

//simulation
const int NeventsSIM = treeInSIM->GetEntries();
for(int i=0; i<NeventsSIM; i++){
  treeInSIM -> GetEntry(i);
  //simulated simulated
  for(const auto& sim_track : *(sims_tracks->GetChannels()) ){
    if (sim_track.GetField<int>(simspid) == 310){ //kshort
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
TFile* fileOut1 = TFile::Open(output, "recreate");

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
