#include <TCanvas.h>
#include <TPad.h>
#include "./ResultClass.C"

void DrawFigure3(){

	stackResult* res1 = new stackResult(true, true);
	stackResult* res2 = new stackResult(true, false);
	stackResult* res3 = new stackResult(false, true);
	stackResult* res4 = new stackResult(false, false);

	TCanvas* can = new TCanvas("can", "can", 2800, 1500);

    TPad* subPad = new TPad("pad", "pad", 0.1, 0.1, 1.0, 1.0);
    subPad->Divide(4, 2, 0.0001, 0.0001);
    subPad->Draw();

	subPad->cd(1);
	res1->mc->Draw("hist");
	res1->data->Draw("same P0");
	res1->leg->Draw("same");
	subPad->cd(2);
	res2->mc->Draw("hist");
	res2->data->Draw("same P0");
	res2->leg->Draw("same");
	subPad->cd(3);
	res3->mc->Draw("hist");
	res3->data->Draw("same P0");
	res3->leg->Draw("same");
	subPad->cd(4);
	res4->mc->Draw("hist");
	res4->data->Draw("same P0");
	res4->leg->Draw("same");
	subPad->cd(5);
	subPad->cd(6);
	subPad->cd(7);
	subPad->cd(8);

	can->Print("./plots/figure3.eps");
}
