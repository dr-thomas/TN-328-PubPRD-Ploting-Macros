#include <TCanvas.h>
#include <TPad.h>
#include "./ResultClass.C"

void DrawFigure4(){

	//effResult(bool isWater){
	effResult* waterEff = new effResult(true);
	effResult* airEff = new effResult(false);

	TCanvas* can = new TCanvas("can", "can", 1400, 1000);

	waterEff->signal2D->Draw("colz");
	for(int ii=1; ii<waterEff->nLines; ii++){
		waterEff->line[ii]->SetLineWidth(3);
		waterEff->line[ii]->Draw();
	}
	can->Print("./plots/water-in-eff.eps");

	can = new TCanvas("can", "can", 1400, 1000);
	airEff->signal2D->Draw("colz");
	for(int ii=1; ii<airEff->nLines; ii++){
		airEff->line[ii]->SetLineWidth(3);
		airEff->line[ii]->Draw();
	}

	can->Print("./plots/water-out-eff.eps");
}
