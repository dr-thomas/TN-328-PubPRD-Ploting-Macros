#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>

class stackResult {
	public:
		THStack* mc;
		TH1F* data;
		TLegend* leg;

		stackResult(bool isSignal, bool isWater, bool isMomentum){
			if(isMomentum) GenMomentum(isSignal, isWater);
			else GenCos(isSignal, isWater);
		};

		void GenMomentum(bool isSignal, bool isWater){

			string CutStr1;
			if(isSignal) {
				CutStr1 = "(accum_level>4 && PIDnShowers<1 && nMuLike[0]==1";
			} else {
				CutStr1 = "(accum_level>4 && PIDnShowers<1 && nMuLike[0]==2";
			}

			TFile* inFmc;
			TFile* inFdata;
			float PoTMC;
			float PoTData;
			if(isWater){
				inFmc = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/BSTunedFullRun5WaterIn.root", "OPEN");
				inFdata = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/FullWaterInData.root", "OPEN");
				PoTMC=208.;
				PoTData=28.7;

			} else {
				inFmc = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/BSTunedFullRun6Air.root", "OPEN");
				inFdata = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/FullRun6AirData.root", "OPEN");
				PoTMC=209.;
				PoTData=32.4;

			}




			TTree* defaultMC = (TTree*)inFmc->Get("outTdefault");
			TTree* defaultData = (TTree*)inFdata->Get("default");

			float PoTScale=PoTData/PoTMC;

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

			data = new TH1F("data","",8,PBins);

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




			CutStr=CutStr1;
			CutStr+=CutStr2;
			defaultData->Draw("selmu_amom>>data",CutStr.c_str());

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
				data->SetBinContent(i+1,(data->GetBinContent(i+1))/(PBins[i+1]-PBins[i]));
				data->SetBinError(i+1,(data->GetBinError(i+1))/(PBins[i+1]-PBins[i]));

			}

			leg = new TLegend(0.7,0.6,0.9,0.9);
			leg->AddEntry(SigMomMC0,"CC-0#pi","f");
			leg->AddEntry(SigMomMC1,"CC-1#pi^{-}","f");
			leg->AddEntry(SigMomMC2,"CC-Other","f");
			leg->AddEntry(SigMomMC3,"BKGD","f");
			leg->AddEntry(SigMomMC7,"OOFV","f");
			leg->AddEntry(SigMomMCOther,"Other","f");
			leg->AddEntry(data,"Data","lep");
			//leg->AddEntry(data,"NEUT Nominal","lep");

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


			mc = new THStack("mc","");
			mc->Add(SigMomMCOther);
			mc->Add(SigMomMC3);
			mc->Add(SigMomMC7);
			mc->Add(SigMomMC2);
			mc->Add(SigMomMC1);
			mc->Add(SigMomMC0);

			data->SetMarkerStyle(8);
			data->SetMarkerSize(1);
			data->SetMarkerColor(kBlack);
			data->GetXaxis()->SetTitle("sel. #mu^{+} momenutm (MeV/c)");

			if(data->GetMaximum()>=mc->GetMaximum()) mc->SetMaximum(1.2*(data->GetMaximum()));
			else mc->SetMaximum(1.2*(mc->GetMaximum()));
		};

		void GenCos(bool isSignal, bool isWater){
		
			TFile* inFmc;
			TFile* inFdata;
			float PoTData;
			float PoTMC;

			if(isWater){
				inFmc = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/BSTunedFullRun5WaterIn.root", "OPEN");
				inFdata = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/FullWaterInData.root", "OPEN");
				PoTData=28.7;
				PoTMC=208;
			} else {
				inFmc = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/BSTunedFullRun6Air.root", "OPEN");
				inFdata = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/FullRun6AirData.root", "OPEN");
				PoTData=34.2;
				PoTMC=209;
			}

			TTree* defaultMC = (TTree*)inFmc->Get("outTdefault");
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

			string CutStr1 = "";
			if(isSignal){
				CutStr1 = "(accum_level>4 && PIDnShowers<1 && nMuLike[0]==1" ;
			} else {
				CutStr1 = "(accum_level>4 && PIDnShowers<1 && nMuLike[0]==2";
			}

			int pBinDraw=0;

			TH1F* SigMomMC0 = new TH1F("SigMomMC0","",nCosBins[pBinDraw],CosBins[pBinDraw]);
			TH1F* SigMomMC1 = new TH1F("SigMomMC1","",nCosBins[pBinDraw],CosBins[pBinDraw]);
			TH1F* SigMomMC2 = new TH1F("SigMomMC2","",nCosBins[pBinDraw],CosBins[pBinDraw]);
			TH1F* SigMomMC3 = new TH1F("SigMomMC3","",nCosBins[pBinDraw],CosBins[pBinDraw]);
			TH1F* SigMomMC7 = new TH1F("SigMomMC7","",nCosBins[pBinDraw],CosBins[pBinDraw]);
			TH1F* SigMomMCOther = new TH1F("SigMomMCOther","",nCosBins[pBinDraw],CosBins[pBinDraw]);


			data = new TH1F("data","",nCosBins[pBinDraw],CosBins[pBinDraw]);

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

			mc = new THStack("mc","");
			mc->Add(SigMomMCOther);
			mc->Add(SigMomMC3);
			mc->Add(SigMomMC7);
			mc->Add(SigMomMC2);
			mc->Add(SigMomMC1);
			mc->Add(SigMomMC0);

			CutStr=CutStr1;
			CutStr+=CutStr2;
			defaultData->Draw("selmu_costheta>>data",CutStr.c_str());


			//bin width
			for(int i=0; i<nCosBins[pBinDraw]; i++){
				SigMomMC0->SetBinContent(i+1,(SigMomMC0->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
				SigMomMC1->SetBinContent(i+1,(SigMomMC1->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
				SigMomMC2->SetBinContent(i+1,(SigMomMC2->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
				SigMomMC3->SetBinContent(i+1,(SigMomMC3->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
				SigMomMC7->SetBinContent(i+1,(SigMomMC7->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
				SigMomMCOther->SetBinContent(i+1,(SigMomMCOther->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
				data->SetBinContent(i+1,(data->GetBinContent(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
				data->SetBinError(i+1,(data->GetBinError(i+1))/(CosBins[pBinDraw][i+1]-CosBins[pBinDraw][i]));
			}

			leg = new TLegend(0.1,0.6,0.4,0.9);
			leg->AddEntry(SigMomMC0,"CC-0#pi","f");
			leg->AddEntry(SigMomMC1,"CC-1#pi^{-}","f");
			leg->AddEntry(SigMomMC2,"CC-Other","f");
			leg->AddEntry(SigMomMC3,"BKGD","f");
			leg->AddEntry(SigMomMC7,"OOFV","f");
			leg->AddEntry(SigMomMCOther,"Other","f");
			leg->AddEntry(data,"Data","lep");

			data->SetMarkerStyle(8);
			data->SetMarkerSize(1);
			data->SetMarkerColor(kBlack);
			data->GetXaxis()->SetTitle("sel. #mu^{+} momenutm (MeV/c)");

			mc->SetMaximum(1.2*(data->GetMaximum()));
		};

};
