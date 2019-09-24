#include "../rootalias_spring2018.h"
#include "../HallA_style.h"
#include "TMath.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;


void sh(Int_t run){

    Int_t run;
    HallA_style();
    TCanvas* c1 = new TCanvas("c1","",1000,800);
    TH2F *prej = new TH2F("prej","",300,-1.5,1.5,300,0,1.5);
    
    //=================================================//
    TCut totalcut = acc_cut_tightL + track_L;
    TCut trigger = trigger_L;
    TCut trigger1 = trigger1_L;
    TCut trigger3 = trigger3_L;

    TString arm = "L";

    if(run>90000){ totalcut = acc_cut_tightR + z_cut_R_tight + track_R; arm = "R";
    trigger = trigger_R;
    trigger1 = trigger4_R;
    trigger3 = trigger6_R;
    }
    
    T = LoadRun(run,"T");

    if(run>90000){
    prej->SetTitle(";shower trx; E/p" );
    T->Draw("(R.sh.e+R.ps.e)/R.tr.p[0]/1000:R.sh.trx>>prej",trigger,"colz");    
    }else{
    prej->SetTitle(";prl2 trx; E/p");
    T->Draw("(L.prl1.e+L.prl2.e)/L.tr.p[0]/1000:L.prl2.trx>>prej",trigger,"colz");
    }

    c1->SaveAs(Form("sh_%i.pdf",run));
 


}