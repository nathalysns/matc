#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TChain *T;

void trigger(Int_t run){

	HallA_style();
    T = LoadRun(run,"T");

	if (!T) exit(1);
 
    cout << "Run number: " << run << endl;

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
    Double_t shmin = 0.8;
    TCut shcut = Form("((L.prl1.e+L.prl2.e)>L.tr.p[0]*1000*%f)",shmin);
    TCut total =  dp_cut_L_loose + th_cut_L_loose + ph_cut_L_loose + track_L + shcut;
    
    if(run>90000){ 
        arm = "R";
        trig1 = "DR.bit4>0";
        trig2 = "DR.bit5>0";
        trig3 = "DR.bit6>0";
        shcut = Form("((R.sh.e+R.ps.e)>R.tr.p[0]*1000*%f)",shmin);
        total =  dp_cut_R_loose + th_cut_R_loose + ph_cut_R_loose + track_R + shcut;
    }


    TH1F *h1 = new TH1F("h1","",500,0,2);
    TH1F *h2 = new TH1F("h2","",500,0,2);
    TH1F *h3 = new TH1F("h3","",500,0,2);
    TH1F *h4 = new TH1F("h4","",500,0,2);

    T->Draw(Form("EK%sx.x_bj>>h1",arm.Data()), total, "goff" );
    Double_t all = h1->GetEntries();

    T->Draw(Form("EK%sx.x_bj>>h2",arm.Data()), total + trig1 + trig2 + trig3 , "goff" );
    Double_t alltrig = h2->GetEntries();

    T->Draw(Form("EK%sx.x_bj>>h3",arm.Data()), total + trig1 + !trig2 + !trig3 , "goff" );
    Double_t onlytrig1 = h3->GetEntries();

    T->Draw(Form("EK%sx.x_bj>>h4",arm.Data()), total + !trig1 + !trig2 + trig3 , "goff" );
    Double_t onlytrig3 = h4->GetEntries();

    ofstream outfile;
    outfile.open ("trigger.txt",ios::in|ios::app);
    outfile << setiosflags(ios::left) << setw(8) << run;
    outfile << setiosflags(ios::left) << setw(15) << all;
    outfile << setiosflags(ios::left) << setw(15) << alltrig;
    outfile << setiosflags(ios::left) << setw(15) << onlytrig1;
    outfile << setiosflags(ios::left) << setw(15) << onlytrig3;
    outfile << endl;
    outfile.close();
    


}

    
