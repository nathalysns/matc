#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TChain *T;
TChain *ev;
TChain *E;

void current(Int_t run){

	HallA_style();
   //======Loading Run Numbers
    T = LoadRun(run,"T");
    E = LoadRun(run,"E");
    if(run>90000) ev = LoadRun(run,"evRight");
    else ev = LoadRun(run,"evLeft");
    if (!T) exit(1);

 
    cout << "Run number: " << run << endl;

    TH1F *hp=new TH1F("hp","",400,0,4);
    T->Draw("HacL_D1_P0rb>>hp","","goff");
    Double_t p0 = hp->GetMean();

    //=================================================//
    TCut shcut = Form("(L.prl1.e+L.prl2.e)/(%f*1000)>0.7 && (L.prl1.e+L.prl2.e)/(%f*1000)<1.5",p0,p0);
    TCut totalcut = shcut + cer_cut_L + trigger_L;
    TCut totalcut1 = shcut + cer_cut_L + trigger_L;
    TCut acc = acc_cut_looseL;
    TCut track0 = "L.tr.n==0";
    TCut track1 = "L.tr.n==1";
    TCut track = "L.tr.n>0";
    TString arm = "L";

    if(run>90000){ 
    	track0 = "R.tr.n==0";
        track1 = "R.tr.n==1";
    	track = "R.tr.n>0";
        acc = acc_cut_looseR;
        shcut = Form("(R.sh.e+R.ps.e)/(%f*1000)>0.7 && (R.sh.e+R.ps.e)/(%f*1000)<1.5",p0,p0);
    	totalcut = shcut + cer_cut_R + trigger_R; 
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

    cout << "Current " << datacurrentcut << endl;


}