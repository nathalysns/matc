#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;


void vdc_check( Int_t run ){
HallA_style();


TCanvas* c1 = new TCanvas("c1","VDC t0 calibration",1000,800);
c1->Divide(2,2);
TCanvas* c2 = new TCanvas("c2","VDC t0",1000,800);
c2->Divide(2,2);
TCanvas* c3 = new TCanvas("c3","VDC t0",1000,800);
c3->Divide(2,2);
TCanvas* c4 = new TCanvas("c4","VDC t0",1000,800);
c4->Divide(2,2);
TString vdc[4] = {"u1","u2","v1","v2"};

//------raw time histograms -------------//
Int_t NBins = 100;
Int_t MIN = 1100;
Int_t MAX = 2200;
TH1F* hist1 = new TH1F("hist1","",NBins,MIN,MAX);
TH1F* hist2 = new TH1F("hist2","",NBins,MIN,MAX);
TH1F* hist3 = new TH1F("hist3","",NBins,MIN,MAX);
hist1->SetLineColor(1);
hist1->SetLineWidth(2);
hist1->SetLineStyle(9);
hist2->SetLineColor(2);
hist2->SetLineWidth(2);
hist3->SetLineColor(4);
hist3->SetLineWidth(2);
//------time histograms -------------//
Int_t NBinstime = 100;
Int_t MINtime = -50;
Int_t MAXtime = 400;
TH1F* hist1time = new TH1F("hist1time","",NBinstime,MINtime,MAXtime);
TH1F* hist2time = new TH1F("hist2time","",NBinstime,MINtime,MAXtime);
TH1F* hist3time = new TH1F("hist3time","",NBinstime,MINtime,MAXtime);
hist1time->SetLineColor(1);
hist2time->SetLineColor(2);
hist1time->SetLineStyle(9);
hist1time->SetLineWidth(2);
hist3time->SetLineColor(4);
hist2time->SetLineWidth(2);
hist3time->SetLineWidth(2);
TGaxis::SetMaxDigits(3);

//=================================================//
TCut totalcut = sh_cut_L + cer_cut_L + track_L;
TCut trigger = trigger_L;
TCut trigger1 = trigger1_L;
TCut trigger3 = trigger3_L;

TString arm = "L";
if(run>90000){ totalcut = sh_cut_R + cer_cut_R + track_R; arm = "R";
trigger = trigger_R;
trigger1 = trigger4_R;
trigger3 = trigger6_R;
}
//=================================================//

//-----2D rawtime histograms
Int_t NBins2D = 400;
Int_t MIN2D = 0;
Int_t MAX2D = 400;
TH2F* hist12D = new TH2F("hist12D","",NBins,MIN,MAX,NBins2D,MIN2D,MAX2D);
TH2F* hist12Dtime = new TH2F("hist12Dtime","",NBinstime,MINtime,MAXtime,NBins2D,MIN2D,MAX2D);

T = LoadRun(run,"T");

auto legend1 = new TLegend(0.4,0.7,0.6,0.85);

legend1->AddEntry(hist1time,"Trigger (s0&s2)","l");
legend1->AddEntry(hist2time,"Trigger (s0&s2)&cer","l");
legend1->AddEntry(hist3time,"Trigger (s0||s2)&cer","l");
legend1->AddEntry((TObject*)0, Form("Run %i",run), "");


for(Int_t i =1; i<5; i++){

c1->cd(i);
hist1->SetTitle(Form(";%s Rawtime;",vdc[i-1].Data()));
T->Draw(Form("%s.vdc.%s.rawtime>>hist1",arm.Data(),vdc[i-1].Data()),trigger1,"");
T->Draw(Form("%s.vdc.%s.rawtime>>hist2",arm.Data(),vdc[i-1].Data()),trigger,"same");
T->Draw(Form("%s.vdc.%s.rawtime>>hist3",arm.Data(),vdc[i-1].Data()),trigger3,"same");
if(i==1) legend1->Draw();
gPad->Update();
}

for(Int_t i =1; i<5; i++){
c2->cd(i);
hist1time->SetTitle(Form(";%s time (ns);",vdc[i-1].Data()));
T->Draw(Form("%s.vdc.%s.time/1e-9>>hist1time",arm.Data(),vdc[i-1].Data()),trigger1,"");
T->Draw(Form("%s.vdc.%s.time/1e-9>>hist2time",arm.Data(),vdc[i-1].Data()),trigger,"same");
T->Draw(Form("%s.vdc.%s.time/1e-9>>hist3time",arm.Data(),vdc[i-1].Data()),trigger3,"same");
if(i==1) legend1->Draw();
gPad->Update();
}

for(Int_t i =1; i<5; i++){
c3->cd(i);
hist12D->SetTitle(Form(";%s rawtime; Wire Number;",vdc[i-1].Data()));
T->Draw(Form("%s.vdc.%s.wire:%s.vdc.%s.rawtime>>hist12D",arm.Data(),vdc[i-1].Data(),arm.Data(),vdc[i-1].Data()),"","colz");
gPad->Update();
}

for(Int_t i =1; i<5; i++){
c4->cd(i);
hist12Dtime->SetTitle(Form(";%s time (ns); Wire Number;",vdc[i-1].Data()));
hist1time->SetTitle(Form(";%s rawtime; Wire Number);",vdc[i-1].Data()));
T->Draw(Form("%s.vdc.%s.wire:%s.vdc.%s.time/1e-9>>hist12Dtime",arm.Data(),vdc[i-1].Data(),arm.Data(),vdc[i-1].Data()),"","colz");
gPad->Update();
}

cout<< " Run ----- "<< run << endl;
c1->SaveAs(Form("plots/vdc_%i_Plots.pdf(",run));
c2->SaveAs(Form("plots/vdc_%i_Plots.pdf",run));
c3->SaveAs(Form("plots/vdc_%i_Plots.pdf",run));
c4->SaveAs(Form("plots/vdc_%i_Plots.pdf)",run));

}
