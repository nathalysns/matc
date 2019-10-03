#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;
TChain *ev;

void cer_draw(Int_t run){

    HallA_style();

    TCanvas *c1 = new TCanvas("c1","",1000,600);
    Int_t N = 101;

    cout << run << endl;
    T = LoadRun(run,"T");
    E = LoadRun(run,"E");


	if(run>90000) ev = LoadRun(run,"evRight");
	else ev = LoadRun(run,"evLeft");
	if (!T) exit(1);

  TCut trigger = "DL.bit2>0";
  TCut trigger1 = "DL.bit1>0";
  TCut total =  dp_cut_L_loose + th_cut_L_loose + ph_cut_L_loose + track_L;
  arm = "L";

  if(run>90000){
    trigger = "DR.bit5>0";
    trigger1 = "DR.bit4>0";
    total =  dp_cut_R_loose + th_cut_R_loose + ph_cut_R_loose + track_R;
    arm = "R";

  }

  TString target_data = "Unknown";

	RunInformation  runinformation   = GetRunInformation(run, T, E, ev);
	Double_t datacharge, datacurrent, datatime_beam;
	Double_t dataLumInt, databoiling;
	TCut datacurrentcut;
	vector<Double_t> datacurrentvalues;

	target_data = runinformation.targ;
	datacurrentvalues = runinformation.timevalues;
	datacurrent = runinformation.current;
	datacharge = runinformation.charge;
	datatime_beam = runinformation.time_beam;
	dataLumInt = runinformation.luminosity;
	databoiling = runinformation.boiling;
	datacurrentcut  = runinformation.Current_cut;


  TH1F *cer_t1 = new TH1F("cer_t1","", 500, 0, 10000);
  TH1F *cer_t2 = new TH1F("cer_t2","", 500, 0, 10000);
  gPad->SetLogy();
  cer_t1->SetTitle(";Cherenkov sum ADC;");
  cer_t1->SetLineColor(4);
  cer_t1->SetLineWidth(4);
  cer_t2->SetLineColor(2);
  cer_t2->SetLineWidth(2);
  


  T->Draw("L.cer.asum_c>>cer_t1", datacurrentcut + total + trigger1);
  T->Draw("L.cer.asum_c>>cer_t2", datacurrentcut + total + trigger,"same");
    
  auto legend = new TLegend(0.75,0.85,0.95,0.95);
  legend->AddEntry(cer_t1,"Trigger 1(4)","l");
  legend->AddEntry(cer_t2,"Trigger 2(5)","l");
  legend->Draw();
   

  TLatex l;
  l.SetTextSize(0.03);
  l.DrawLatex(4000,10,Form("Run %i",run));
  gPad->Update();

  c1->SaveAs(Form("plots/cer_draw_%i.pdf",run)); 
	
}