#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;


void cer(Int_t run){

    HallA_style();

    TH1F *cer[10];
    Int_t N = 101;

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

    cout << run << endl;
    TCanvas *c1 = new TCanvas("c1","c1");
    c1->SetCanvasSize(1500, 1500);
    c1->SetWindowSize(500, 500);
    c1->Divide(5,5);
    //run=3102;
    T = LoadRun(run,"T");
    ofstream outfile;
    outfile.open ("cer.txt",ios::in|ios::app);
    outfile << setiosflags(ios::left) << setw(8) << run;
    for(Int_t i=0; i<10;i++){
	c1->cd(i+1);
        cer[i] = new TH1F(Form("cer%i",i),"",100,100,800);
    	T->Draw(Form("%s.cer.a_c[%i]>>cer%i",arm.Data(), i, i), trigger1, "");
        Double_t min = 210;
        Double_t max = 450;
        cer[i]->Fit("gaus","Q","",min,max);
   	TF1 *myfunc=cer[i]->GetFunction("gaus");
   	cout << "Peak  = " <<  myfunc->GetParameter(1) << " +/- " << myfunc->GetParError(2) << endl;
   	outfile << setiosflags(ios::left) << setw(15) << myfunc->GetParError(1);
  	outfile << setiosflags(ios::left) << setw(15) << myfunc->GetParError(2);
	}

    outfile << endl;
    outfile.close();

 
}
