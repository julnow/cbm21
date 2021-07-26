#include "TMath.h"

#include<iostream>
#include<string>
#include<cmath>
#include<fstream>

double rt(double x, double y){
  return sqrt(x*x+y*y);
}

double pt(double px, double py){
  return sqrt(px*px+py*py);
}
double gamma(double e, double pz){
  return log((e+pz)/(e-pz))/2;
}
double eta(double t, double z){
  return log((t+z)/(t-z))/2;
}
void normalize(TH1D *h){
  int nbins = h->GetNbinsX();
  for (int i=1; i<nbins; ++i){
    h->SetBinContent(i, h->GetBinContent(i)/h->GetBinCenter(i));
  }
}

void skrypt1() //podajemy nazwę pliku i id cząstki
{
  const char *filename = "test.f19";
  //histogramy
    //piony 0
  const int idp0 = 111;
  //c1
  TH1D *p0x = new TH1D("Rozklad x p0", "pion 0", 100, -100, 100);
  TH1D *p0y = new TH1D("Rozklad y p0", "pion 0", 100, -100, 100);
  TH1D *p0z = new TH1D("Rozklad z p0", "pion 0", 100, -150, 150);
  TH1D *p0t = new TH1D("Rozklad t p0", "pion 0", 100, -5, 200);
  //c2
  TH1D *p0px = new TH1D("Rozklad px p0", "pion 0", 100, -3, 3);
  TH1D *p0py = new TH1D("Rozklad py p0", "pion 0", 100, -3, 3);
  TH1D *p0pz = new TH1D("Rozklad pz p0", "pion 0", 100, -10, 10);
  TH1D *p0e = new TH1D("Rozklad E p0", "pion 0", 100, -1, 11);
  //c3
  TH1D *p0rt = new TH1D("Rozklad rt p0", "pion 0", 100, -0.1, 25);
  TH1D *p0pt = new TH1D("Rozklad pt p0", "pion 0", 100, -0.1, 3);
  TH1D *p0g = new TH1D("Rozklad gamma p0", "pion 0", 100, -2, 2);
  TH1D *p0eta = new TH1D("Rozklad eta p0", "pion 0", 100, -5, 5);
    //piony +
  const int idpp = 211;
  //c1
  TH1D *ppx = new TH1D("Rozklad x pp", "pion +", 100, -100, 100);
  TH1D *ppy = new TH1D("Rozklad y pp", "pion +", 100, -100, 100);
  TH1D *ppz = new TH1D("Rozklad z pp", "pion +", 100, -150, 150);
  TH1D *ppt = new TH1D("Rozklad t pp", "pion +", 100, -5, 200);
  //c2
  TH1D *pppx = new TH1D("Rozklad px pp", "pion +", 100, -3, 3);
  TH1D *pppy = new TH1D("Rozklad py pp", "pion +", 100, -3, 3);
  TH1D *pppz = new TH1D("Rozklad pz pp", "pion +", 100, -10, 10);
  TH1D *ppe = new TH1D("Rozklad E pp", "pion +", 100, -1, 11);
  //c3
  TH1D *pprt = new TH1D("Rozklad rt pp", "pion +", 100, -0.1, 25);
  TH1D *pppt = new TH1D("Rozklad pt pp", "pion +", 100, -0.1, 3);
  TH1D *ppg = new TH1D("Rozklad gamma pp", "pion +", 100, -2, 2);
  TH1D *ppeta = new TH1D("Rozklad eta pp", "pion +", 100, -5, 5);
  //piony -
  const int idpm = -211;
  //c1
  TH1D *pmx = new TH1D("Rozklad x pm", "pion -", 100, -100, 100);
  TH1D *pmy = new TH1D("Rozklad y pm", "pion -", 100, -100, 100);
  TH1D *pmz = new TH1D("Rozklad z pm", "pion -", 100, -150, 150);
  TH1D *pmt = new TH1D("Rozklad t pm", "pion -", 100, -5, 200);
  //c2
  TH1D *pmpx = new TH1D("Rozklad px pm", "pion -", 100, -3, 3);
  TH1D *pmpy = new TH1D("Rozklad py pm", "pion -", 100, -3, 3);
  TH1D *pmpz = new TH1D("Rozklad pz pm", "pion -", 100, -10, 10);
  TH1D *pme = new TH1D("Rozklad E pm", "pion -", 100, -1, 11);
  //c3
  TH1D *pmrt = new TH1D("Rozklad rt pm", "pion -", 100, -0.1, 25);
  TH1D *pmpt = new TH1D("Rozklad pt pm", "pion -", 100, -0.1, 3);
  TH1D *pmg = new TH1D("Rozklad gamma pm", "pion -", 100, -2, 2);
  TH1D *pmeta = new TH1D("Rozklad eta pm", "pion -", 100, -5, 5);
  //protony
  const int idpr = 2212;
  //c1
  TH1D *prx = new TH1D("Rozklad x pr", "proton", 100, -100, 100);
  TH1D *pry = new TH1D("Rozklad y pr", "proton", 100, -100, 100);
  TH1D *prz = new TH1D("Rozklad z pr", "proton", 100, -150, 150);
  TH1D *prt = new TH1D("Rozklad t pr", "proton", 100, -5, 200);
  //c2
  TH1D *prpx = new TH1D("Rozklad px pr", "proton", 100, -3, 3);
  TH1D *prpy = new TH1D("Rozklad py pr", "proton", 100, -3, 3);
  TH1D *prpz = new TH1D("Rozklad pz pr", "proton", 100, -10, 10);
  TH1D *pre = new TH1D("Rozklad E pr", "proton", 100, -1, 11);
  //c3
  TH1D *prrt = new TH1D("Rozklad rt pr", "proton", 100, -0.1, 25);
  TH1D *prpt = new TH1D("Rozklad pt pr", "proton", 100, -0.1, 3);
  TH1D *prg = new TH1D("Rozklad gamma pr", "proton", 100, -2, 2);
  TH1D *preta = new TH1D("Rozklad eta pr", "proton", 100, -5, 5);
  //neutrony
  const int idne = 2112;
  //c1
  TH1D *nex = new TH1D("Rozklad x ne", "neutron", 100, -100, 100);
  TH1D *ney = new TH1D("Rozklad y ne", "neutron", 100, -100, 100);
  TH1D *nez = new TH1D("Rozklad z ne", "neutron", 100, -150, 150);
  TH1D *net = new TH1D("Rozklad t ne", "neutron", 100, -5, 200);
  //c2
  TH1D *nepx = new TH1D("Rozklad px ne", "neutron", 100, -3, 3);
  TH1D *nepy = new TH1D("Rozklad py ne", "neutron", 100, -3, 3);
  TH1D *nepz = new TH1D("Rozklad pz ne", "neutron", 100, -10, 10);
  TH1D *nee = new TH1D("Rozklad E ne", "neutron", 100, -1, 11);
  //c3
  TH1D *nert = new TH1D("Rozklad rt ne", "neutron", 100, -0.1, 25);
  TH1D *nept = new TH1D("Rozklad pt ne", "neutron", 100, -0.1, 3);
  TH1D *neg = new TH1D("Rozklad gamma ne", "neutron", 100, -2, 2);
  TH1D *neeta = new TH1D("Rozklad eta ne", "neutron", 100, -5, 5);


  ifstream fin;
  fin.open(filename);
  string header1, header2, header3;
  //odczyt headeara
  getline(fin, header1);
  getline(fin, header2);
  getline(fin, header3);

  //odczyt danych
  int id, nParticles, pId;
  double skip, px, py, pz, e, m, x, y, z, t;
  while(fin.peek() != EOF){
    fin >> id >> nParticles >> skip >> skip;
    for (int i = 0; i < nParticles; ++i){
      fin >> id >> pId >> px >> py >> pz >> e >> m >> x >> y >> z >> t;
      double gam = gamma(e, pz);
      //filowanie histogramów
      switch(pId){
        case idp0:  //piony 0
          p0x->Fill(x);
          p0y->Fill(y);
          p0z->Fill(z);
          p0t->Fill(t);
          p0px->Fill(px);
          p0py->Fill(py);
          p0pz->Fill(pz);
          p0e->Fill(e);
          p0rt->Fill(rt(x,y));
          p0pt->Fill(pt(px, py));
          if (abs(gam) <1 ){
            p0g->Fill(gamma(e, pz));
          }
          p0eta->Fill(eta(t, z));
          break;
        case idpp: //piony +
          ppx->Fill(x);
          ppy->Fill(y);
          ppz->Fill(z);
          ppt->Fill(t);
          pppx->Fill(px);
          pppy->Fill(py);
          pppz->Fill(pz);
          ppe->Fill(e);
          pprt->Fill(rt(x,y));
          pppt->Fill(pt(px, py));

          if (abs(gam) <1 ){
            ppg->Fill(gamma(e, pz));
          }
          ppeta->Fill(eta(t, z));
          break;
          case idpm: //piony -
            pmx->Fill(x);
            pmy->Fill(y);
            pmz->Fill(z);
            pmt->Fill(t);
            pmpx->Fill(px);
            pmpy->Fill(py);
            pmpz->Fill(pz);
            pme->Fill(e);
            pmrt->Fill(rt(x,y));
            pmpt->Fill(pt(px, py));

            if (abs(gam) <1 ){
              pmg->Fill(gamma(e, pz));
            }
            pmeta->Fill(eta(t, z));
            break;
          case idpr: //protony
            if (t != 0){ //pominniecie pociskow
              prx->Fill(x);
              pry->Fill(y);
              prz->Fill(z);
              prt->Fill(t);
              prpx->Fill(px);
              prpy->Fill(py);
              prpz->Fill(pz);
              pre->Fill(e);
              prrt->Fill(rt(x,y));
              prpt->Fill(pt(px, py));

              if (abs(gam) <1 ){
                prg->Fill(gamma(e, pz));
              }
              preta->Fill(eta(t, z));
            }
            break;
          case idne: //neutrony
            if (t != 0){ //pominniecie pociskow
              nex->Fill(x);
              ney->Fill(y);
              nez->Fill(z);
              net->Fill(t);
              nepx->Fill(px);
              nepy->Fill(py);
              nepz->Fill(pz);
              nee->Fill(e);
              nert->Fill(rt(x,y));
              nept->Fill(pt(px, py));

              if (abs(gam) <1 ){
                neg->Fill(gamma(e, pz));
              }
              neeta->Fill(eta(t, z));
            }
            break;
          default:
            break;
        }
    }
  }

  //wyswietlanie histogramow
  //hist1 - x,y,z,t
  Int_t palette[5];
  palette[0] = kViolet;
  palette[1] = kOrange-2;
  palette[2] = kGreen+3;
  palette[3] = kBlue;
  palette[4] = kRed;
  gStyle->SetPalette(5,palette);
  auto c1 = new TCanvas("c1","c1");
  c1->Divide(2,2);
  c1->SetWindowSize(1280, 800);
  c1->SetLogy(); //skala log
  THStack *hx = new THStack("polozenia x", "x;x [fm];dN/dx");
  hx->Add(ppx);
  hx->Add(p0x);
  hx->Add(pmx);
  hx->Add(prx);
  hx->Add(nex);
  THStack *hy = new THStack("polozenia y", "y;y [fm];dN/dy");
  hy->Add(ppy);
  hy->Add(p0y);
  hy->Add(pmy);
  hy->Add(pry);
  hy->Add(ney);
  THStack *hz = new THStack("polozenia z", "z;z [fm];dN/dz");
  hz->Add(ppz);
  hz->Add(p0z);
  hz->Add(pmz);
  hz->Add(prz);
  hz->Add(nez);
  THStack *ht = new THStack("polotenia t", "t;t [fm/c];dN/dt");
  ht->Add(ppt);
  ht->Add(p0t);
  ht->Add(pmt);
  ht->Add(prt);
  ht->Add(net);
  THStack *hist1[4] = {hx, hy, hz, ht};
  gStyle->SetPalette(1);
  for (int i=0; i<4;++i){
    c1->cd(i+1);
    gPad->SetLogy();
    gStyle->SetMarkerStyle(18);
    gStyle->SetPalette(5,palette);
    hist1[i]->Draw("pfc plc pmc nostack E1");
    gPad->BuildLegend(0.75,0.75,0.95,0.95,"");
  }

  //zapis do pliku png
  char histfile11[100] = "";
	const char *png = ".png";
	const char *histfile_ = "_";
	const char *histfile1 = "urqmdf19";
  const char *histfile2 = "1";
	strcpy(histfile11, histfile1);
	strcat(histfile11, histfile_);
	strcat(histfile11, histfile2);
  strcat(histfile11, png);
	c1->Print(histfile11);
  //hist2 - px,py,pz,e
  auto c2 = new TCanvas("c2","c2");
  c2->Divide(2,2);
  c2->SetWindowSize(1280, 800);
  THStack *hpx = new THStack("pedy x", "px;px [GeV/c];dN/dpx");
  hpx->Add(pppx);
  hpx->Add(p0px);
  hpx->Add(pmpx);
  hpx->Add(prpx);
  hpx->Add(nepx);
  THStack *hpy = new THStack("pedy y", "py;py [GeV/c];dN/dpy");
  hpy->Add(pppy);
  hpy->Add(p0py);
  hpy->Add(pmpy);
  hpy->Add(prpy);
  hpy->Add(nepy);
  THStack *hpz = new THStack("pedy z", "pz;pz [GeV/c];dN/dpz");
  hpz->Add(pppz);
  hpz->Add(p0pz);
  hpz->Add(pmpz);
  hpz->Add(prpz);
  hpz->Add(nepz);
  THStack *he = new THStack("energie", "E;E [GeV];dN/dE");
  he->Add(ppe);
  he->Add(p0e);
  he->Add(pme);
  he->Add(pre);
  he->Add(nee);
  THStack *hist2[4] = {hpx, hpy, hpz, he};
  for (int i=0; i<4;++i){
    c2->cd(i+1);

    gStyle->SetMarkerStyle(18);
    gStyle->SetPalette(5,palette);
    hist2[i]->Draw("pfc plc pmc nostack E1");
    gPad->BuildLegend(0.75,0.75,0.95,0.95,"");
  }
  char histfile22[100] = "";
  histfile2 = "2";
  strcpy(histfile22, histfile1);
  strcat(histfile22, histfile_);
  strcat(histfile22, histfile2);
  strcat(histfile22, png);
  c2->Print(histfile22);
  //hist3 - rt,rp,gamma,eta
  auto c3 = new TCanvas("c3","c3");
  c3->Divide(2,2);
  c3->SetWindowSize(1280, 800);
  THStack *hrt = new THStack("rt","rt;rt [fm];1/rT dN/drT");
  normalize(pprt);
  hrt->Add(pprt);
  normalize(p0rt);
  hrt->Add(p0rt);
  normalize(pmrt);
  hrt->Add(pmrt);
  normalize(prrt);
  hrt->Add(prrt);
  normalize(nert);
  hrt->Add(nert);
  THStack *hpt = new THStack("pt", "pt;pt [GeV/c];1/pT dN/dpT");
  normalize(pppt);
  hpt->Add(pppt);
  normalize(p0pt);
  hpt->Add(p0pt);
  normalize(pmpt);
  hpt->Add(pmpt);
  normalize(prpt);
  hpt->Add(prpt);
  normalize(nept);
  hpt->Add(nept);
  THStack *hg = new THStack("gamma", "#gamma;#gamma;dN/d#gamma");
  hg->Add(ppg);
  hg->Add(p0g);
  hg->Add(pmg);
  hg->Add(prg);
  hg->Add(neg);
  THStack *heta = new THStack("eta", "#eta;#eta;dN/d#eta");
  heta->Add(ppeta);
  heta->Add(p0eta);
  heta->Add(pmeta);
  heta->Add(preta);
  heta->Add(neeta);
  THStack *hist3[4] = {hrt, hpt, hg, heta};
  gStyle->SetPalette(1);
  for (int i=0; i<4;++i){
    c3->cd(i+1);
    gPad->SetLogy();
    gStyle->SetMarkerStyle(18);
    gStyle->SetPalette(5,palette);
    hist3[i]->Draw("pfc plc pmc nostack E1");
    gPad->BuildLegend(0.75,0.75,0.95,0.95,"");
  }
  char histfile33[100] = "";
  histfile2 = "3";
  strcpy(histfile33, histfile1);
  strcat(histfile33, histfile_);
  strcat(histfile33, histfile2);
  strcat(histfile33, png);
  c3->Print(histfile33);

}
