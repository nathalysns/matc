#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;
TChain *ev;

void sh_draw(Int_t run){

    HallA_style();

    TCanvas *c1 = new TCanvas("c1","",2500,600);
    c1->Divide(2,1);
    TCanvas *c2 = new TCanvas("c2","",1500,600);
    c2->Divide(2,1);
    Int_t N = 1;
    

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

    Int_t shmax = 2000;
    if(run>90000) shmax = 3000;
    TH2F *sh_t1 = new TH2F("sh_t1","", 500, 0,shmax,500,0,shmax);
    TH2F *sh_t2 = new TH2F("sh_t2","", 500, 0,shmax,500,0,shmax);

    TH1F *sh_t3 = new TH1F("sh_t3","", 500, 0, 1.5);
    TH1F *sh_t4 = new TH1F("sh_t4","", 500, 0, 1.5);

    sh_t1->SetTitle(";Trigger1 prl1 ADC channels; prl2 ADC channels");
    sh_t2->SetTitle(";Trigger2 prl1 ADC channels; prl2 ADC channels");
    sh_t3->SetTitle(";Trigger1 E/P; ");
    sh_t4->SetTitle(";Trigger2 E/P; ");

    TString dradc = "L.prl1.e:L.prl2.e";
    TString dr = "(L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)";
    if(run>90000){
      sh_t1->SetTitle(";Trigger4 prl1 ADC channels; shower ADC channels");
      sh_t2->SetTitle(";Trigger5 prl1 ADC channels; shower ADC channels");
      sh_t3->SetTitle(";Trigger4 E/P; ");
      sh_t4->SetTitle(";Trigger5 E/P; ");
      dradc = "R.ps.e:R.sh.e";
      dr = "(R.ps.e+R.sh.e)/(R.tr.p[0]*1000)";
    }


    c1->cd(1);
    T->Draw(Form("%s>>sh_t1",dradc.Data()), datacurrentcut + trigger1  + total,"colz");
    c1->cd(2);
    T->Draw(Form("%s>>sh_t2",dradc.Data()),datacurrentcut +  trigger  + total,"colz" );
    c2->cd(1);
    c2->cd(1)->SetLogy();
    T->Draw(Form("%s>>sh_t3",dr.Data()),datacurrentcut + trigger1  + total,"colz");
    c2->cd(2);
    c2->cd(2)->SetLogy();
    T->Draw(Form("%s>>sh_t4",dr.Data()),datacurrentcut + trigger  + total,"colz" );
    
    c1->SaveAs(Form("plots/sh_adc_%i.pdf",run));
    c2->SaveAs(Form("plots/Ep_%i.pdf",run));

/*
   auto legend = new TLegend(0.75,0.85,0.95,0.95);
   legend->AddEntry(sh_t1,"Trigger 1","l");
   legend->AddEntry(sh_t2,"Trigger 2","l");
   legend->Draw();
   

    TLatex l;
   	l.SetTextSize(0.03);
    l.DrawLatex(4000,10,Form("Run %i",run));
    gPad->Update();

   if(j==0) {c1->SaveAs("shtrig.pdf(");}
   else if (j==N-1){c1->SaveAs("shtrig.pdf)");}
   else {c1->SaveAs("shtrig.pdf");}

   delete sh_t1; delete sh_t2; */
	
}
