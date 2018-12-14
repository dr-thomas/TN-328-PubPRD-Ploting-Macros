#include <TCanvas.h>
#include <TPad.h>
#include "./DrawTunedOverlays.C"

void DrawFigure3(){
	TCanvas* tempCan = DrawTunedOverlays(true, true);

	TCanvas* can = new TCanvas("can", "can", 2800, 1500);

    TPad* subPad = new TPad("pad", "pad", 0.1, 0.1, 1.0, 1.0);
    subPad->Divide(4, 2, 0.0001, 0.0001);
    subPad->Draw();

	subPad->cd(1);
	tempCan->DrawClonePad();
	subPad->cd(2);
	tempCan->DrawClonePad();
	subPad->cd(3);
	tempCan->DrawClonePad();
	subPad->cd(4);
	tempCan->DrawClonePad();
	subPad->cd(5);
	tempCan->DrawClonePad();
	subPad->cd(6);
	tempCan->DrawClonePad();
	subPad->cd(7);
	tempCan->DrawClonePad();
	subPad->cd(8);
	tempCan->DrawClonePad();

	can->Print("./plots/figure3.eps");
}
