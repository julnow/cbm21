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

//reading ready files from pfRead_inital and pfSimulated
void pfRead_final(const char *pfReadFileName, const char *outputFileName, const char *simFileName){

//reading pfRead_inital data
  TFile pfReadFile(pfReadFileName);

  //Candidates
  TH1F *hcanpx;
  //amybe a void function could do it?
  pfReadFile.GetObject("hcanpx",hcanpx);
  hcanpx->SetDirectory(0);
  TH1F *hcanpy;
  pfReadFile.GetObject("hcanpy",hcanpy);
  hcanpy->SetDirectory(0);
  TH1F *hcanpz;
  pfReadFile.GetObject("hcanpz",hcanpz);
  hcanpz->SetDirectory(0);
  TH1F *hcanpt;
  pfReadFile.GetObject("hcanpt",hcanpt);
  hcanpt->SetDirectory(0);
  TH1F *hcanp;
  pfReadFile.GetObject("hcanp",hcanp);
  hcanp->SetDirectory(0);
  TH1F *hcanphi;
  pfReadFile.GetObject("hcanphi",hcanphi);
  hcanphi->SetDirectory(0);
  TH1F *hcanmass;
  pfReadFile.GetObject("hcanmass",hcanmass);
  hcanmass->SetDirectory(0);
  //#K_{can} - #K_{sim}
  TH1F *hdifpx;
  pfReadFile.GetObject("hdifpx",hdifpx);
  hdifpx->SetDirectory(0);
  TH1F *hdifpy;
  pfReadFile.GetObject("hdifpy",hdifpy);
  hdifpy->SetDirectory(0);
  TH1F *hdifpz;
  pfReadFile.GetObject("hdifpz",hdifpz);
  hdifpz->SetDirectory(0);
  TH1F *hdifpt;
  pfReadFile.GetObject("hdifpt",hdifpt);
  hdifpt->SetDirectory(0);
  TH1F *hdifp;
  pfReadFile.GetObject("hdifp",hdifp);
  hdifp->SetDirectory(0);
  //correlations
  TH2F *hcorpx;
  pfReadFile.GetObject("hcorpx",hcorpx);
  hcorpx->SetDirectory(0);
  TH2F *hcorpy;
  pfReadFile.GetObject("hcorpy",hcorpy);
  hcorpy->SetDirectory(0);
  TH2F *hcorpz;
  pfReadFile.GetObject("hcorpz",hcorpz);
  hcorpz->SetDirectory(0);
  TH2F *hcorr_px_py;
  pfReadFile.GetObject("hcorr_px_py",hcorr_px_py);
  hcorr_px_py->SetDirectory(0);
  TH2F *hcorpt;
  pfReadFile.GetObject("hcorpt",hcorpt);
  hcorpt->SetDirectory(0);
  TH2F *hcorp;
  pfReadFile.GetObject("hcorp",hcorp);
  hcorp->SetDirectory(0);
  TH2F *hcormass;
  pfReadFile.GetObject("hcormass",hcormass);
  hcormass->SetDirectory(0);
  TH2F *hcorr_rap_pt;
  pfReadFile.GetObject("hcorr_rap_pt",hcorr_rap_pt);
  hcorr_rap_pt->SetDirectory(0);
  TH2F *hcorr_phi_pt;
  pfReadFile.GetObject("hcorr_phi_pt",hcorr_phi_pt);
  hcorr_phi_pt->SetDirectory(0);
  //chi2
  TH1F *hchi2_geo;
  pfReadFile.GetObject("hchi2_geo",hchi2_geo);
  hchi2_geo->SetDirectory(0);
  TH1F *hchi2_prim_first;
  pfReadFile.GetObject("hchi2_prim_first",hchi2_prim_first);
  hchi2_prim_first->SetDirectory(0);
  TH1F *hchi2_prim_second;
  pfReadFile.GetObject("hchi2_prim_second",hchi2_prim_second);
  hchi2_prim_second->SetDirectory(0);
  TH1F *hchi2_topo;
  pfReadFile.GetObject("hchi2_topo",hchi2_topo);
  hchi2_topo->SetDirectory(0);

  pfReadFile.Close();

  //reading of data from simulated histogramsfile
  TFile simFile(simFileName);
  TH1F* hsimspx;
  TH1F* hsimspy;
  TH1F* hsimspz;
  TH1F* hsimspt;
  TH1F* hsimsp;
  TH1F* hsimmass;
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
  simFile.GetObject("hsimmass",hsimmass);
  hsimmass->SetDirectory(0);
  simFile.GetObject("hcors_rap_pt",hcors_rap_pt);
  hcors_rap_pt->SetDirectory(0);
  simFile.GetObject("hcors_phi_pt",hcors_phi_pt);
  hcors_phi_pt->SetDirectory(0);
  simFile.GetObject("hcors_px_py",hcors_px_py);
  hcors_px_py->SetDirectory(0);
  simFile.Close();


  //division of histograms
  TH2F* hcord_rap_pt;
  hcord_rap_pt = (TH2F*) hcorr_rap_pt->Clone();
  hcord_rap_pt->Divide(hcors_rap_pt);
  hcord_rap_pt->SetNameTitle("hcord_rap_pt", "division correlation rapidity pt; rapidity; pT");
  TH2F* hcordr_rap_pt = relativeError(hcorr_rap_pt, hcors_rap_pt); //relative error
  hcordr_rap_pt->SetNameTitle("hcordr_rap_pt", "#frac{#Delta #varepsilon}{#varepsilon} correlation rapidity pT; rapidity; pT");
  TH2F* hcord_phi_pt;
  hcord_phi_pt = (TH2F*) hcorr_phi_pt->Clone();
  hcord_phi_pt->Divide(hcors_phi_pt);
  hcord_phi_pt->SetNameTitle("hcord_rphi_pt", "division correlation #phi pT; #phi; pT");
  TH2F* hcordr_phi_pt = relativeError(hcorr_phi_pt, hcors_phi_pt); //relative error
  hcordr_phi_pt->SetNameTitle("hcordr_phi_pt", "#frac{#Delta #varepsilon}{#varepsilon} correlation #phi pT; #phi; pT");
  TH2F* hcord_px_py;
  hcord_px_py = (TH2F*) hcorr_px_py->Clone();
  hcord_px_py->Divide(hcors_px_py);
  hcord_px_py->SetNameTitle("hcord_px_py", "division correlations px py; px; py");
  TH2F* hcordr_px_py = relativeError(hcorr_px_py, hcors_px_py); //relative error
  hcordr_px_py->SetNameTitle("hcordr_px_py", "#frac{#Delta #varepsilon}{#varepsilon} correlation px py; px; py");

  TFile* fileOut1 = TFile::Open(outputFileName, "recreate");

  hcanpx->Write();
  hcanpy->Write();
  hcanpz->Write();
  hcanpt->Write();
  hcanp->Write();
  hcanmass->Write();
  hsimspx->Write();
  hsimspy->Write();
  hsimspz->Write();
  hsimspt->Write();
  hsimsp->Write();
  hsimmass->Write();
  hdifpx->Write();
  hdifpy->Write();
  hdifpz->Write();
  hdifpt->Write();
  hdifp->Write();
  hcorpx->Write();
  hcorpy->Write();
  hcorpz->Write();
  hcorpt->Write();
  hcorp->Write();
  hcormass->Write();
  hchi2_geo->Write();
  hchi2_prim_first->Write();
  hchi2_prim_second->Write();
  hchi2_topo->Write();
  hcorr_px_py->Write();
  hcorr_rap_pt->Write();
  hcorr_phi_pt->Write();
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
