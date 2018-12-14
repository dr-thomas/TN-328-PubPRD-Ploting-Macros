#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>

void DrawTunedOverlays(){

  //string CutStr1 = "(accum_level>4 && PIDnShowers<1 && nMuLike[0]==1";
  string CutStr1 = "(accum_level>4 && PIDnShowers<1 && nMuLike[0]==2";

/*
  TFile* inFmc = new TFile("RootFiles/BSTunedFullRun5WaterIn.root", "OPEN");
  TFile* inFdata = new TFile("RootFiles/FullWaterInData.root", "OPEN");
  float PoTMC=208.;
  float PoTData=28.7;
*/

  TFile* inFmc = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/BSTunedFullRun6Air.root", "OPEN");
  TFile* inFdata = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/FullRun6AirData.root", "OPEN");
  float PoTMC=209.;
  float PoTData=32.4;



  TTree* defaultMC = (TTree*)inFmc->Get("outTdefault");
  //TTree* defaultMC = (TTree*)inFmc->Get("default");
  TTree* defaultData = (TTree*)inFdata->Get("default");

  //float PoTMC=351.;

  //MC corrected numbers:
  //Run5: 224.7
  //Run6: 242.6
  //or Data relative to 208. MC PoT
  //Water-in: 23.80
  //Water-out: 29.33
  //
  float PoTScale=PoTData/PoTMC;
  //

  double PBins[9]={0,400,530,670,800,1000,1380,2010,3410};
  TString PBinsStr[9]={"0","400","530","670","800","1000","1380","2010","3410"};
  double CosBins[9][4]={
    {1,1,1,1},//only one bin here
    {0.84,0.94,1,1},//only three bins here
    {0.85,0.92,0.96,1},//Col. Forbins...
    {0.88,0.93,0.97,1},
    {0.90,0.94,0.97,1},
    {0.91,0.95,0.97,1},
    {0.92,0.96,0.98,1},
    {0.95,0.98,1,1},//only three bins here
    {1,1,1,1}//only one bin here
  };



  TH1F* SigMomMC0 = new TH1F("SigMomMC0","",8,PBins);
  TH1F* SigMomMC1 = new TH1F("SigMomMC1","",8,PBins);
  TH1F* SigMomMC2 = new TH1F("SigMomMC2","",8,PBins);
  TH1F* SigMomMC3 = new TH1F("SigMomMC3","",8,PBins);
  TH1F* SigMomMC7 = new TH1F("SigMomMC7","",8,PBins);
  TH1F* SigMomMCOther = new TH1F("SigMomMCOther","",8,PBins);

  TH1F* SigMomData = new TH1F("SigMomData","",8,PBins);
  
  TH1F* SigMomTemp = new TH1F("SigMomTemp","",8,PBins);
  TH1F* SigMomTempData = new TH1F("SigMomTempData","",8,PBins);

  string CutStr2 = "&& weight<5 && weight>0)*weight";
  //string CutStr2 = "&& weight<5 && weight>0)";
  string CutStr;

  CutStr=CutStr1;
  CutStr+=" && topology==0";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_amom>>SigMomMC0",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && topology==1";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_amom>>SigMomMC1",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && topology==2";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_amom>>SigMomMC2",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && topology==3";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_amom>>SigMomMC3",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && topology==7";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_amom>>SigMomMC7",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && (topology<0 || (topology>3 && topology!=7))";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_amom>>SigMomMCOther",CutStr.c_str());


  SigMomMC0->Scale(PoTScale);
  SigMomMC1->Scale(PoTScale);
  SigMomMC2->Scale(PoTScale);
  SigMomMC3->Scale(PoTScale);
  SigMomMC7->Scale(PoTScale);
  SigMomMCOther->Scale(PoTScale);

  SigMomMC0->SetFillColor(kRed-9);
  SigMomMC1->SetFillColor(kBlue-9);
  SigMomMC7->SetFillColor(kGreen-8);
  SigMomMC3->SetFillColor(kOrange-4);
  SigMomMC2->SetFillColor(kYellow-7);
  SigMomMCOther->SetFillColor(kBlack);


  CutStr=CutStr1;
  CutStr+=CutStr2;
  defaultData->Draw("selmu_amom>>SigMomData",CutStr.c_str());

  defaultMC->Draw("selmu_amom>>SigMomTemp",CutStr.c_str());
  defaultData->Draw("selmu_amom>>SigMomTempData",CutStr.c_str());
  SigMomTemp->Scale(PoTScale);

  
  cout << "Integrals:" << endl;
  cout << SigMomTemp->Integral() << " " << SigMomTempData->Integral() << endl;



  //bin width
  for(int i=0; i<8; i++){
    SigMomMC0->SetBinContent(i+1,(SigMomMC0->GetBinContent(i+1))/(PBins[i+1]-PBins[i]));
    SigMomMC1->SetBinContent(i+1,(SigMomMC1->GetBinContent(i+1))/(PBins[i+1]-PBins[i]));
    SigMomMC2->SetBinContent(i+1,(SigMomMC2->GetBinContent(i+1))/(PBins[i+1]-PBins[i]));
    SigMomMC3->SetBinContent(i+1,(SigMomMC3->GetBinContent(i+1))/(PBins[i+1]-PBins[i]));
    SigMomMC7->SetBinContent(i+1,(SigMomMC7->GetBinContent(i+1))/(PBins[i+1]-PBins[i]));
    SigMomMCOther->SetBinContent(i+1,(SigMomMCOther->GetBinContent(i+1))/(PBins[i+1]-PBins[i]));
    SigMomData->SetBinContent(i+1,(SigMomData->GetBinContent(i+1))/(PBins[i+1]-PBins[i]));
    SigMomData->SetBinError(i+1,(SigMomData->GetBinError(i+1))/(PBins[i+1]-PBins[i]));

  }

  TLegend* leg = new TLegend(0.7,0.6,0.9,0.9);
  leg->AddEntry(SigMomMC0,"CC-0#pi","f");
  leg->AddEntry(SigMomMC1,"CC-1#pi^{-}","f");
  leg->AddEntry(SigMomMC2,"CC-Other","f");
  leg->AddEntry(SigMomMC3,"BKGD","f");
  leg->AddEntry(SigMomMC7,"OOFV","f");
  leg->AddEntry(SigMomMCOther,"Other","f");
  leg->AddEntry(SigMomData,"Data","lep");
  //leg->AddEntry(SigMomData,"NEUT Nominal","lep");



  THStack *hs = new THStack("hs","");
  hs->Add(SigMomMCOther);
  hs->Add(SigMomMC3);
  hs->Add(SigMomMC7);
  hs->Add(SigMomMC2);
  hs->Add(SigMomMC1);
  hs->Add(SigMomMC0);



  TCanvas* c = new TCanvas;
  SigMomData->SetMarkerStyle(8);
  SigMomData->SetMarkerSize(1);
  SigMomData->SetMarkerColor(kBlack);
  SigMomData->GetXaxis()->SetTitle("sel. #mu^{+} momenutm (MeV/c)");

 // if(SigMomData->GetMaximum()>=hs->GetMaximum()) hs->SetMaximum(1.2*(SigMomData->GetMaximum()));
 // else hs->SetMaximum(1.2*(hs->GetMaximum()));
  hs->Draw();
 // hs->GetXaxis()->SetTitle("sel. #mu^{+} momenutm (MeV/c)");
 // hs->GetYaxis()->SetTitle("events / 1 MeV/c");
 // c->Modified();
 // SigMomData->Draw("same PE0");
 // leg->Draw("same");

  c->Print("./plots/TestOverlayMom.eps");

  //cout << hs->Integral() << " " << SigMomData->Integral() << endl;



  return;
}


