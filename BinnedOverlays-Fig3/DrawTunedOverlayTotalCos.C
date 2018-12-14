TCanvas* DrawTunedOverlayTotalCos(bool isSignal, bool isWater){

  //TFile* inFmc = new TFile("BSTunedFullRun5WaterIn.root", "OPEN");
  //TFile* inFmc = new TFile("FullRun5WaterIn.root", "OPEN");
  //TFile* inFdata = new TFile("FullRun7WaterData.root", "OPEN");
  //TFile* inFdata = new TFile("FullWaterInData.root", "OPEN");
  //
  //

 /*
  TFile* inFmc = new TFile("./RootFiles/BSTunedFullRun6Air.root", "OPEN");
  TFile* inFdata = new TFile("./RootFiles/FullRun6AirData.root", "OPEN");
  TString outFStr="./plots/WaterOut";
  float PoTData=34.2;
  float PoTMC=209;
 
*/
  TFile* inFmc = new TFile("./RootFiles/BSTunedFullRun5WaterIn.root", "OPEN");
  TFile* inFdata = new TFile("./RootFiles/FullWaterInData.root", "OPEN");
  TString outFStr="./plots/WaterIn";
  float PoTData=28.7;
  float PoTMC=208;

  TTree* defaultMC = (TTree*)inFmc->Get("outTdefault");
  //TTree* defaultMC = (TTree*)inFmc->Get("default");
  TTree* defaultData = (TTree*)inFdata->Get("default");

  

  float PoTScale=PoTData/PoTMC;


  double PBins[9]={0,400,530,670,800,1000,1380,2010,3410};
  TString PBinsStr[9]={"0","400","530","670","800","1000","1380","2010","3410"};

  int nCosBins[8]={9,2,3,3,3,3,3,2};
  double CosBins[9][10]={
  {0.6,0.8,0.85,0.88,0.90,0.92,0.94,0.96,0.98,1.0},
  {},
  {},
  {},
  {},
  {},
  {},
  {},
  {}
  };

  //int pBinDraw=7;
  string CutStr1 = "";
  if(SampleID==0){
    outFStr+="CC0pi";
    CutStr1 = "(accum_level>4 && PIDnShowers<1 && nMuLike[0]==1" ;
  }
  else if(SampleID==1){
    outFStr+="CC1pi";
    CutStr1 = "(accum_level>4 && PIDnShowers<1 && nMuLike[0]==2";
  }
  outFStr+=pBinDrawStr;
  outFStr+=".pdf";


  TH1F* SigMomMC0 = new TH1F("SigMomMC0","",nCosBins[pBinDraw],CosBins[pBinDraw]);
  TH1F* SigMomMC1 = new TH1F("SigMomMC1","",nCosBins[pBinDraw],CosBins[pBinDraw]);
  TH1F* SigMomMC2 = new TH1F("SigMomMC2","",nCosBins[pBinDraw],CosBins[pBinDraw]);
  TH1F* SigMomMC3 = new TH1F("SigMomMC3","",nCosBins[pBinDraw],CosBins[pBinDraw]);
  TH1F* SigMomMC7 = new TH1F("SigMomMC7","",nCosBins[pBinDraw],CosBins[pBinDraw]);
  TH1F* SigMomMCOther = new TH1F("SigMomMCOther","",nCosBins[pBinDraw],CosBins[pBinDraw]);


  TH1F* SigMomData = new TH1F("SigMomData","",nCosBins[pBinDraw],CosBins[pBinDraw]);

  string CutStr2 = ")*weight";
  string CutStr;

  CutStr=CutStr1;
  CutStr+=" && topology==0";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_costheta>>SigMomMC0",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && topology==1";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_costheta>>SigMomMC1",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && topology==2";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_costheta>>SigMomMC2",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && topology==3";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_costheta>>SigMomMC3",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && topology==7";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_costheta>>SigMomMC7",CutStr.c_str());

  CutStr=CutStr1;
  CutStr+=" && (topology<0 || (topology>3 && topology!=7))";
  CutStr+=CutStr2;
  defaultMC->Draw("selmu_costheta>>SigMomMCOther",CutStr.c_str());


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

  THStack *hs = new THStack("hs","");
  hs->Add(SigMomMCOther);
  hs->Add(SigMomMC3);
  hs->Add(SigMomMC7);
  hs->Add(SigMomMC2);
  hs->Add(SigMomMC1);
  hs->Add(SigMomMC0);

  CutStr=CutStr1;
  CutStr+=CutStr2;
  defaultData->Draw("selmu_costheta>>SigMomData",CutStr.c_str());


  //bin width
  for(int i=0; i<nCosBins[pBinDraw]; i++){
    SigMomMC0->SetBinContent(i+1,(SigMomMC0->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
    SigMomMC1->SetBinContent(i+1,(SigMomMC1->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
    SigMomMC2->SetBinContent(i+1,(SigMomMC2->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
    SigMomMC3->SetBinContent(i+1,(SigMomMC3->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
    SigMomMC7->SetBinContent(i+1,(SigMomMC7->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
    SigMomMCOther->SetBinContent(i+1,(SigMomMCOther->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
    SigMomData->SetBinContent(i+1,(SigMomData->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
    SigMomData->SetBinError(i+1,(SigMomData->GetBinError(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
  }

  TLegend* leg = new TLegend(0.1,0.6,0.4,0.9);
  leg->AddEntry(SigMomMC0,"CC-0#pi","f");
  leg->AddEntry(SigMomMC1,"CC-1#pi^{-}","f");
  leg->AddEntry(SigMomMC2,"CC-Other","f");
  leg->AddEntry(SigMomMC3,"BKGD","f");
  leg->AddEntry(SigMomMC7,"OOFV","f");
  leg->AddEntry(SigMomMCOther,"Other","f");
  leg->AddEntry(SigMomData,"Data","lep");

  TCanvas* c = new TCanvas;
  SigMomData->SetMarkerStyle(8);
  SigMomData->SetMarkerSize(1);
  SigMomData->SetMarkerColor(kBlack);
  SigMomData->GetXaxis()->SetTitle("sel. #mu^{+} momenutm (MeV/c)");

  hs->SetMaximum(1.2*(SigMomData->GetMaximum()));
  hs->Draw();
  hs->GetXaxis()->SetTitle("sel. #mu^{+} cos#theta");
  hs->GetYaxis()->SetTitle("events / cos#theta");
  c->Modified();
  SigMomData->Draw("same PE0");
  leg->Draw("same");

  c->Print(outFStr);

  return c;
}


