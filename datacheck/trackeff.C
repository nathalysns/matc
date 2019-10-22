#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TChain *T;
TChain *E;
TChain *ev;

void trackeff(Int_t run){

	HallA_style();
    T = LoadRun(run,"T");
    E = LoadRun(run,"E");
    if(run>90000) ev = LoadRun(run,"evRight");
    else ev = LoadRun(run,"evLeft");

	if (!T) exit(1);
 
    cout << "Run number: " << run << endl;

    TH1F *hp=new TH1F("hp","",400,0,4);
    TString mom = "HacL_D1_P0rb";
    if (run>90000 ) mom = "HacR_D1_P0rb";
    T->Draw(Form("%s>>hp",mom.Data()),"","goff");
    Double_t p0 = hp->GetMean();

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

    //=================================================//
    TCut shcut = Form("(L.prl1.e+L.prl2.e)/(%f*1000)>0.7 && (L.prl1.e+L.prl2.e)/(%f*1000)<1.5",p0,p0);
    TCut totalcut = shcut + cer_cut_L + trigger_L;
    TCut totalcut1 = shcut + cer_cut_L + trigger_L;
    TCut acc = acc_cut_looseL;
    TCut track0 = "L.tr.n==0";
    TCut track1 = "L.tr.n==1";
    TCut track = "L.tr.n>0";
    TString arm = "L";
    TCut zcut = z_cut_L_tight;	
    TCut beta = "L.tr.beta>0.7 && L.tr.beta>1.5";

    if(run>90000){ 
    	track0 = "R.tr.n==0";
        track1 = "R.tr.n==1";
    	track = "R.tr.n>0";
        acc = acc_cut_looseR;
        shcut = Form("(R.sh.e+R.ps.e)/(%f*1000)>0.7 && (R.sh.e+R.ps.e)/(%f*1000)<1.5",p0,p0);
    	totalcut = shcut + cer_cut_R + trigger_R; 
    	arm = "R";
	   zcut = z_cut_R_tight;
       beta = "R.tr.beta>0.7 && R.tr.beta>1.5";
    }


    TH1F *h1 = new TH1F("h1","",500,0,2);
    TH1F *h2 = new TH1F("h2","",500,0,2);
    TH1F *h1eff = new TH1F("h1eff","",500,0,2);
    TH1F *h2eff = new TH1F("h2eff","",500,0,2);

    //====== 0 track inneficiency
    T->Draw(Form("EK%sx.x_bj>>h1",arm.Data()), totalcut + track0 + datacurrentcut, "goff" );
    T->Draw(Form("EK%sx.x_bj>>h1eff",arm.Data()), totalcut + datacurrentcut, "goff" );
    Double_t zero_track = h1->GetEntries()/h1eff->GetEntries();
    cout << "Zero track inneficiency: " << zero_track << endl;

    //====== Multitracks
    T->Draw(Form("EK%sx.x_bj>>h2",arm.Data()), totalcut + track1 + acc  + datacurrentcut + beta, "goff" );
    T->Draw(Form("EK%sx.x_bj>>h2eff",arm.Data()), totalcut + acc  + datacurrentcut + beta, "goff" );
    Double_t multi_track = h2->GetEntries()/h2eff->GetEntries();

    cout << "Multitracks: " << multi_track  << endl;

    ofstream outfile;
    outfile.open ("trackingefftest.txt",ios::in|ios::app);
    outfile << setiosflags(ios::left) << setw(8) << run;
    outfile << setiosflags(ios::left) << setw(15) << zero_track;
    outfile << setiosflags(ios::left) << setw(15) << multi_track;
    outfile << endl;
    outfile.close();
}

    
