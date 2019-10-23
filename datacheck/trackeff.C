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
    TCut totalcut =  cer_cut_L + trigger_L;
    TCut totalcut1 =  cer_cut_L + trigger_L;
    TCut acc = acc_cut_looseL;
    TCut track0 = "L.tr.n==0";
    TCut track1 = "L.tr.n==1";
    TCut track = "L.tr.n>0";
    TString arm = "L";
    TCut zcut = z_cut_L_tight;	
    TCut beta = "L.tr.beta>0.7 && L.tr.beta<1.5";
    TCut shtest = "";
    TString sht1 = "";
    Double_t  m, a1, a2, c1, c2; 
    m = a1 = a2 = c1 = c2 = 0; 
    

    if(run>90000){ 
        m = 1.41;
    	track0 = "R.tr.n==0";
        track1 = "R.tr.n==1";
    	track = "R.tr.n>0";
        acc = acc_cut_looseR;
        shcut = Form("(R.sh.e+R.ps.e)/(%f*1000)>0.7 && (R.sh.e+R.ps.e)/(%f*1000)<1.5",p0,p0);
    	totalcut = cer_cut_R + trigger_R; 
    	arm = "R";
	    zcut = z_cut_R_tight;
        beta = "R.tr.beta>0.7 && R.tr.beta<1.5";
        sht1 = "(R.sh.e+R.ps.e)>((%f*(%f*1000))-%f) && (R.sh.e+R.ps.e)<((%f*(%f*1000))-%f) && (%f*1000)>%f &&(%f*1000)<%f ";
        //
        if(run>94024 && run <94067){a1=1500; a2=900; c1=2810; c2=3120;} //R28-HS
        else if(run>93986 && run <94015){a1=1500; a2=800; c1=2650; c2=3120;} //R28-PK
        else if(run>93741 && run <93774){a1=1500; a2=800; c1=2800; c2=3400;} //R26-HS
        else if(run>93708 && run <93739){a1=1500; a2=800; c1=2750; c2=3400;} //R26-PK
        else if(run>93774 && run <93786){a1=1500; a2=800; c1=2700; c2=3200;} //R26-LS
        else if(run>93591 && run <93644){a1=1600; a2=800; c1=2900; c2=3400;} //R24-PK
        else if(run>93648 && run <93699){a1=1700; a2=800; c1=2700; c2=3300;} //R24-LS
        else if(run>93092 && run <93124){a1=850; a2=250; c1=1320; c2=1550;} //R42-HS
        else if(run>93044 && run <93092){a1=850; a2=100; c1=1200; c2=1550;} //R42-PK
        else if(run>93125 && run <93149){a1=850; a2=100; c1=1200; c2=1550;} //R42-LS
        else {a1=3000; a2=0; c1=1000; c2=4000;}
        shtest = Form(sht1,m,p0,a1,m,p0,a2,p0,c1,p0,c2);

    }


    TH1F *h1 = new TH1F("h1","",500,0,2);
    TH1F *h2 = new TH1F("h2","",500,0,2);
    TH1F *h1eff = new TH1F("h1eff","",500,0,2);
    TH1F *h2eff = new TH1F("h2eff","",500,0,2);

    //====== 0 track inneficiency
    T->Draw(Form("EK%sx.x_bj>>h1",arm.Data()), totalcut + track0 + datacurrentcut + shtest, "goff" );
    T->Draw(Form("EK%sx.x_bj>>h1eff",arm.Data()), totalcut + datacurrentcut + shtest, "goff" );
    Double_t zero_track = h1->GetEntries()/h1eff->GetEntries();
    cout << "Zero track inneficiency: " << zero_track << endl;

    //====== Multitracks
    T->Draw(Form("EK%sx.x_bj>>h2",arm.Data()), totalcut + track1 + acc  + datacurrentcut + shtest, "goff" );
    T->Draw(Form("EK%sx.x_bj>>h2eff",arm.Data()), totalcut + acc  + datacurrentcut + shtest, "goff" );
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

    
