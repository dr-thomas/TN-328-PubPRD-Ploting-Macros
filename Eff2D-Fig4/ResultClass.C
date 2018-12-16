#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>
#include <TLine.h>

class effResult {
	public:
		TFile* inF;
		TH2F* signal2D;
		TLine** line;
		int nLines;

		effResult(bool isWater){

			if(isWater)
				inF = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/FullRun5WaterIn.root", "OPEN");
			else 
				inF = new TFile("/Volumes/ThomasDrive/p0dCCAnalysis/Selection/DataMCOverlays/RootFiles/FullRun6AirFull.root", "OPEN");
			TTree* defaultT =(TTree*)inF->Get("default");
			TTree* truthT =(TTree*)inF->Get("truth");

			double Pmin=200.;
			double Pmax=3410.;
			int nbins=40;
			double Cmin=0.6;
			double Cmax=1.;

			//PoT numbers:
			//double PoTScale=16./345.;

			//20% roughly of available MC
			//double PoTScale=16.*5.0/345.;
			double PoTScale=30./208.;


			signal2D = new TH2F("signal2D", "signal2D",nbins,Pmin,Pmax,nbins,Cmin,Cmax);
			TH2F* generated2D = new TH2F("generated2D", "generated2D",nbins,Pmin,Pmax,nbins,Cmin,Cmax);

			TString CutsNuDefault="accum_level>4 && selmu_costheta>0.6 && topology==0 && selmu_truemom>200. && nMuLike[0]==1 && PIDnShowers<1";
			TString CutsNuTruth="topology==0 && newmu_mom>200. && newmu_costheta>0.6";

			defaultT->Draw("truelepton_costheta:selmu_truemom>>signal2D",CutsNuDefault,"colz");
			truthT->Draw("newmu_costheta:newmu_mom>>generated2D",CutsNuTruth,"colz");

			signal2D->Divide(generated2D);

			//tuned fine Double Bins
			Float_t PBins[10]={0,400,530,670,800,1000,1380,2010,3410,50000};
			Float_t CosBins[9][5]={
				{-1,1,1,1,1},//only one bin here
				{-1,0.84,0.94,1,1},//only three bins here
				{-1,0.85,0.92,0.96,1},//Col. Forbins...
				{-1,0.88,0.93,0.97,1},
				{-1,0.90,0.94,0.97,1},
				{-1,0.91,0.95,0.97,1},
				{-1,0.92,0.96,0.98,1},
				{-1,0.95,0.98,1,1},//only three bins here
				{-1,1,1,1,1}//only one bin here
			};


			nLines=0;  
			line = new TLine*[240];
			for(int i=1; i<9; i++){
				line[i] = new TLine(PBins[i],0.6,PBins[i],1.0);
				nLines++;
			}
			int tempLineIndex=nLines;
			for(int i=1; i<8; i++){
				//for(int j=1; j<6; j++){
				for(int j=0; j<4; j++){
					line[tempLineIndex] = new TLine(PBins[i],CosBins[i][j+1],PBins[i+1],CosBins[i][j+1]);
					tempLineIndex++;
					nLines++;
				}
			}

			signal2D->SetStats(0);
			signal2D->SetTitle("2D Selection Efficiency");	
			signal2D->GetXaxis()->SetTitle("selected lepton true momentum (MeV/c)");
			signal2D->GetYaxis()->SetTitle("selected lepton true cos(#theta)");
			signal2D->Draw("colz");
			//for(int i=1; i<49; i++){
			for(int i=1; i<nLines; i++){
				line[i]->SetLineWidth(3);
				line[i]->Draw();
			}
		};
};
