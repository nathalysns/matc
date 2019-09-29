#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TChain *T;
TChain *E;
TChain *ev;

void trackcheck(Int_t run){

	HallA_style();
    T = LoadRun(run,"T");
    E = LoadRun(run,"E");

	if(run>90000) ev = LoadRun(run,"evRight");
	else ev = LoadRun(run,"evLeft");
	if (!T) exit(1);
 
    cout << "Run number: " << run << endl;

	TString target_data = "Unknown";
    
    //=================================================//
    TCut  shadc = "-L.prl2.asum_c+1100<L.prl1.asum_c";
    TCut totalcut = shadc + cer_cut_L + trigger_L;
    TCut totalcut1 = shadc + cer_cut_L + trigger_L;
    TCut track0 = "L.tr.n==0";
    TCut track = "L.tr.n>0";

    TString arm = "L";
    if(run>90000){ 
    	track0 = "R.tr.n==0";
    	track = "R.tr.n>0";
    	shadc = " -R.sh.asum_c+1200<R.ps.asum_c && R.sh.asum_c>500";
    	totalcut = shadc + cer_cut_R + trigger_R; 
    	arm = "R";
		if(run>93200){
    		shadc = " -R.sh.asum_c+1200<R.ps.asum_c && R.sh.asum_c>500";
    		totalcut = shadc + cer_cut_R + trigger_R; 
    	} 
	}


	TCanvas *c1 = new TCanvas("c1","",1500, 800);
    c1->Divide(2,2);
    TString VDCwires[] = {"u1","v1","u2","v2"}; 
    TH1F *vdc[4];
    TH1F *vdc2[4];
    TH1F *vdc3[4];

    for (Int_t i=0;i<4;i++){
    	c1->cd(i+1);
    	c1->cd(i+1)->SetLogy();
    	vdc[i] = new TH1F(Form("vdc%i",i),"", 450,-50,400);
    	vdc[i]->SetLineWidth(3);
  		vdc[i]->SetLineColor(1);
  		vdc[i]->SetTitle(Form("; vdc %s wire; ",VDCwires[i].Data()));
    	T->Draw(Form("%s.vdc.%s.wire>>vdc%i",arm.Data(),VDCwires[i].Data(),i),totalcut);
    	vdc[i]->SetMaximum(vdc[i]->GetMaximum()+70000);
    	//cout << "Maximum: " << vdc[i]->GetMaximum() << endl;
    	vdc2[i] = new TH1F(Form("vdc2%i",i),"", 450,-50,400);
    	vdc2[i]->SetLineWidth(2);
  		vdc2[i]->SetLineColor(2);
    	T->Draw(Form("%s.vdc.%s.wire>>vdc2%i",arm.Data(),VDCwires[i].Data(),i),totalcut+track0,"same");
    	vdc3[i] = new TH1F(Form("vdc3%i",i),"", 450,-50,400);
    	vdc3[i]->SetLineWidth(2);
  		vdc3[i]->SetLineColor(4);
  		vdc3[i]->SetLineStyle(10);
    	T->Draw(Form("%s.vdc.%s.wire>>vdc3%i",arm.Data(),VDCwires[i].Data(),i),totalcut+track,"same");

    	if(i==0){
    		auto legend1 = new TLegend(0.15,0.7,0.48,0.85);
    		legend1->AddEntry(vdc[i],"All","l");
			legend1->AddEntry(vdc3[i],"Trigger (s0&s2)&cer &&  Track == 0","l");
			legend1->AddEntry(vdc2[i],"Trigger (s0&s2)&cer &&  Track > 0","l");
			legend1->AddEntry((TObject*)0, Form("Run %i",run), "");
			legend1->Draw();
    	}
    }
    
    c1->SaveAs(Form("plots/vdc_%i.pdf",run));
}