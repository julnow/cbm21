void hstack(const char *hName, const char *title, const char *stackName, TFile *signFile, TFile *bckgrFile){
  //getting signal histogram
  TH1F *sign;
  signFile->GetObject(hName,sign);
  sign->SetDirectory(0);
  sign->SetFillColor(kRed);
  sign->SetLineColor(kRed);
  //getting background histogram
  TH1F *bckgr;
  bckgrFile->GetObject(hName,bckgr);
  bckgr->SetDirectory(0);
  bckgr->SetFillColor(kBlue);
  bckgr->SetLineColor(kBlue);
  double coeff = sign->GetEntries() / bckgr->GetEntries(); //coefficent, co we can compare them
  bckgr->Scale(coeff);
  THStack *stack = new THStack(stackName, title);
  stack->Add(sign);
  stack->Add(bckgr);

  TCanvas *c = new TCanvas(stackName,stackName,800,600);
  gStyle->SetPalette(1);
  c->SetLogy();
  TLegend *legend = new TLegend(0.75,0.75,0.95,0.95);
  legend->AddEntry(sign, "signal", "l");
  legend->AddEntry(bckgr, "background", "l");
  stack->Draw("plc pmc nostack E1 L");
  legend->Draw("same");
  c->Write();
}


//compares background and signal for topological parameters of kaon reconstruction
void top_selection(const char *signFileName, const char *bckgrFilename){

  TFile signFile(signFileName);
  TFile bckgrFile(bckgrFilename);

  TFile* fileOut1 = TFile::Open("topo.root", "recreate");
  hstack("hchi2_geo", "#chi^{2} geometric; #chi^{2}_{geo}; counts", "stackhchi2_geo", &signFile, &bckgrFile);
  hstack("hchi2_prim_first", "#chi^{2} primary for #pi_{+}; #chi^{2}_{prim}; counts", "stackhchi2_prim_first", &signFile, &bckgrFile);
  hstack("hchi2_prim_second", "#chi^{2} primary for #pi_{-}; #chi^{2}_{prim}; counts", "stackhchi2_prim_second", &signFile, &bckgrFile);
  hstack("hchi2_topo", "#chi^{2} topological; #chi^{2}_{topo}; counts", "stackhchi2_topo", &signFile, &bckgrFile);
  hstack("hcosine_first", "cosine of angle between #pi_{+} and kaon; cos #alpha_{K #pi_{+}}; counts", "stackhcosine_first", &signFile, &bckgrFile);
  hstack("hcosine_second", "cosine of angle between #pi_{-} and kaon; cos #alpha_{K #pi_{+}}; counts", "stackhcosine_second", &signFile, &bckgrFile);
  hstack("hcosine_topo", "cosine topological; cos_{topo}; counts", "stackhcosine_topo", &signFile, &bckgrFile);
  hstack("hdistance", "DCA between secondary tracks; DCA_{#pi_{+}#pi_{-}} [cm]; counts", "stackhdistance", &signFile, &bckgrFile);
  hstack("hl_over_dl", "#frac{L}{#Delta L}; #frac{L}{#Delta L}; counts", "stackhl_over_dl", &signFile, &bckgrFile);

  signFile.Close();
  bckgrFile.Close();
  fileOut1->Close();
}
