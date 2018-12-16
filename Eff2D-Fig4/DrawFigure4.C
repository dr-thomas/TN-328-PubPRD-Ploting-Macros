#include <TCanvas.h>
#include <TPad.h>
#include "./ResultClass.C"

void DrawFigure4(){

	//effResult(bool isWater){
	effResult* waterEff = new effResult(true);
	effResult* airEff = new effResult(false);

	TCanvas* can = new TCanvas("can", "can", 1400, 1500);

    TPad* subPad = new TPad("pad", "pad", 0., 0., 1.0, 1.0);
    subPad->Divide(1, 2, 0.0001, 0.0001);
    subPad->Draw();

	subPad->cd(1);
	waterEff->signal2D->Draw("colz");
	for(int ii=1; ii<waterEff->nLines; ii++){
		waterEff->line[ii]->SetLineWidth(3);
		waterEff->line[ii]->Draw();
	}
	subPad->cd(2);
	airEff->signal2D->Draw("colz");
	for(int ii=1; ii<airEff->nLines; ii++){
		airEff->line[ii]->SetLineWidth(3);
		airEff->line[ii]->Draw();
	}

	can->Print("./plots/figure4.eps");
}
