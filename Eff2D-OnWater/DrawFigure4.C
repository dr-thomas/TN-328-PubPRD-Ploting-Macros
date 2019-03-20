#include <TCanvas.h>
#include <TPad.h>
#include "./ResultClass.C"

void DrawFigure4(){

	//effResult(bool isWater){
	effResult* waterEff = new effResult();

	TCanvas* can = new TCanvas("can", "can", 1400, 1000);

	waterEff->signal2D->Draw("colz");
	for(int ii=1; ii<waterEff->nLines; ii++){
		waterEff->line[ii]->SetLineWidth(3);
		waterEff->line[ii]->Draw();
	}

	can->Print("./plots/water-eff.eps");
}
