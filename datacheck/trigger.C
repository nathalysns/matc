#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TChain *T;
TChain *E;
TChain *ev;

void trigger(Int_t run){

	HallA_style();
    T = LoadRun(run,"T");
    T = LoadRun(run,"T");
    E = LoadRun(run,"E");
    if(run>90000) ev = LoadRun(run,"evRight");
    else ev = LoadRun(run,"evLeft");


	if (!T) exit(1);
 
    cout << "Run number: " << run << endl;

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

    TH1F *hp=new TH1F("hp","",400,0,4);
    TString mom = "HacL_D1_P0rb";
    if (run>90000 ) mom = "HacR_D1_P0rb";
    T->Draw(Form("%s>>hp",mom.Data()),"","goff");
    Double_t p0 = hp->GetMean();

    //=================================================//
    TString arm = "L";
    TCut trig1 = "DL.bit1>0";
    TCut trig2 = "DL.bit2>0";
    TCut trig3 = "DL.bit3>0";
    TCut total =  dp_cut_L_loose + th_cut_L_loose + ph_cut_L_loose + track_L + sh_cut_L;
    TCut beta = "L.tr.beta>0.7 && L.tr.beta<1.5";
    TCut shtest = "";
    TString sht1 = "";
    Double_t  m, a1, a2, c1, c2; 
    m = a1 = a2 = c1 = c2 = 0; 

    if(run>90000){ 
        arm = "R";
        trig1 = "DR.bit4>0";
        trig2 = "DR.bit5>0";
        trig3 = "DR.bit6>0";
        total =  dp_cut_R_loose + th_cut_R_loose + ph_cut_R_loose + track_R + sh_cut_R;
        beta = "R.tr.beta>0.7 && R.tr.beta<1.5";
        sht1 = "(R.sh.e+R.ps.e)>((%f*(R.tr.p[0]*1000))-%f) && (R.sh.e+R.ps.e)<((%f*(R.tr.p[0]*1000))-%f) && (R.tr.p[0]*1000)>%f &&(R.tr.p[0]*1000)<%f ";
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
        shtest = Form(sht1,m,a1,m,a2,c1,c2);
    }


    TH1F *h1 = new TH1F("h1","",500,0,2);
    TH1F *h2 = new TH1F("h2","",500,0,2);
    TH1F *h3 = new TH1F("h3","",500,0,2);
    TH1F *h4 = new TH1F("h4","",500,0,2);

    T->Draw(Form("EK%sx.x_bj>>h1",arm.Data()), datacurrentcut + total + beta + shtest, "goff" );
    Double_t all = h1->GetEntries();

    T->Draw(Form("EK%sx.x_bj>>h2",arm.Data()), datacurrentcut + total + trig1 + trig2 + trig3 + beta + shtest, "goff" );
    Double_t alltrig = h2->GetEntries();

    T->Draw(Form("EK%sx.x_bj>>h3",arm.Data()), datacurrentcut + total + trig1 + !trig2 + !trig3 + beta + shtest, "goff" );
    Double_t onlytrig1 = h3->GetEntries();

    T->Draw(Form("EK%sx.x_bj>>h4",arm.Data()), datacurrentcut + total + !trig1 + !trig2 + trig3 + beta + shtest, "goff" );
    Double_t onlytrig3 = h4->GetEntries();

    ofstream outfile;
    outfile.open ("triggertest.txt",ios::in|ios::app);
    outfile << setiosflags(ios::left) << setw(8) << run;
    outfile << setiosflags(ios::left) << setw(15) << all;
    outfile << setiosflags(ios::left) << setw(15) << alltrig;
    outfile << setiosflags(ios::left) << setw(15) << onlytrig1;
    outfile << setiosflags(ios::left) << setw(15) << onlytrig3;
    outfile << endl;
    outfile.close();
    


}

    
