#include <TCanvas.h>
#include <TPad.h>
#include "./ResultClass.C"

void DrawFigure3(){

	//stackResult(bool isSignal, bool isWater, bool isMomentum){
	stackResult** res = new stackResult*[8];
	res[0] = new stackResult(true,true,true);
	res[1] = new stackResult(true,false,true);
	res[2] = new stackResult(false,true,true);
	res[3] = new stackResult(false,false,true);
	res[4] = new stackResult(true,true,false);
	res[5] = new stackResult(true,false,false);
	res[6] = new stackResult(false,true,false);
	res[7] = new stackResult(false,false,false);

	TCanvas* can = new TCanvas("can", "can", 2800, 1500);

    TPad* subPad = new TPad("pad", "pad", 0.1, 0.1, 1.0, 1.0);
    subPad->Divide(4, 2, 0.0001, 0.0001);
    subPad->Draw();

	for(int ii=0; ii<8; ii++){
		subPad->cd(ii+1);
		res[ii]->mc->Draw("hist");
		res[ii]->data->Draw("same P0");
		res[ii]->leg->Draw("same");
	}
	can->Print("./plots/figure3.eps");
}
