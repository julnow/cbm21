void hstack(const char *hName, const char *title, const char *stackName, TFile *defcutfile, TFile *mancutfile){
  //getting signal histogram
  TH1F *defcuts;
  defcutfile->GetObject(hName,defcuts);
  defcuts->SetDirectory(0);
  defcuts->SetFillColor(kRed);
  defcuts->SetLineColor(kRed);
  //getting background histogram
  TH1F *mancuts;
  mancutfile->GetObject(hName,mancuts);
  mancuts->SetDirectory(0);
  mancuts->SetFillColor(kBlue);
  mancuts->SetLineColor(kBlue);
  THStack *stack = new THStack(stackName, title);
  stack->Add(defcuts);
  stack->Add(mancuts);

  TCanvas *c = new TCanvas(stackName,stackName,800,600);
  gStyle->SetPalette(1);
  TLegend *legend = new TLegend(0.75,0.75,0.95,0.95);
  legend->AddEntry(defcuts, "default cuts", "l");
  legend->AddEntry(mancuts, "manual cuts", "l");
  stack->Draw("pfc plc pmc nostack");
  legend->Draw("same");
  c->Write();
}

void mstack(){

  TFile defcut("kaons_default.root");
  TFile cuts("kaon_all_cut.root");

  TFile* fileOut1 = TFile::Open("mstack.root", "recreate");
  hstack("hcanmass", "K_{can} mass;mass [GeV/c^{2}];dN/dmass", "stackhcanmass", &defcut, &cuts);
  defcut.Close();
  cuts.Close();
  fileOut1->Close();


}
