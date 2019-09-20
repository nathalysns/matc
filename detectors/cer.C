#include "../rootalias_spring2018.h"
#include "../HallA_style.h"
#include "TMath.h"
TString arm;
TString armHRS;
TChain *T;
TChain *E;
Double_t fitf(Double_t *x, Double_t *par)
{
   /*Double_t arg = 0;
   if (par[2] != 0) arg = (x[0] - par[1])/par[2];

   Double_t fitval = exp(-par[0])*pow(par[0],par[1]/par[2])/TMath::Factorial((Int_t ) par[1]/par[2]) * (par[3]*TMath::Exp(-0.5*arg*arg));
   */
   //Double_t fitval = par[0]*TMath::Power((par[1]/par[2]),(x[0]/par[2]))*(TMath::Exp(-(par[1]/par[2])))/TMath::Gamma((x[0]/par[2])+1.);
   Double_t fitval = par[0]*TMath::Power(par[1],(x[0]/par[2]))*(TMath::Exp(-(par[1])))/TMath::Gamma((x[0]/par[2])+1.);
   
//   p0           3.16472e+03   3.76482e+01   9.50020e-02  -1.23773e-05
//   p1           4.76424e+03   1.08302e+01   7.73625e-02  -1.29758e-04
//   p2           4.91538e+02   8.93434e+00   2.06813e-02   1.43984e-04

   return fitval;
}

void cer(Int_t run){

    HallA_style();

    TH1F *cer[10];
    TH1F *cer2[10];
    Int_t N = 101;

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

    cout << run << endl;
    
    T = LoadRun(run,"T");
   

    TCanvas *c1 = new TCanvas("c1","",1500, 800);
    c1->Divide(5,2);
    TCanvas *c2 = new TCanvas("c2","",1500, 800);
    c2->Divide(5,2);


    ofstream outfile;
    outfile.open ("cer.txt",ios::in|ios::app);
    outfile << setiosflags(ios::left) << setw(8) << run;
  
    //=======Looping in all the pmts

    for(Int_t i=0; i<10;i++){
    Double_t cermin = 2000;
    Double_t cermax = 7000;

    if(run>90000){ cermax = 10000; }

	cer[i] = new TH1F(Form("cer%i",i),"", 100,100,500);
    cer2[i] = new TH1F(Form("cer2%i",i),"",250,cermin,cermax);


    c1->cd(i+1);
    cer[i]->SetTitle(Form("pmt %i;ADC channel;  ",i+1));
    cer[i]->SetLineColor(1);
    cer[i]->SetLineWidth(1);
    T->Draw(Form("%s.cer.a_c[%i]>>cer%i",arm.Data(), i, i), trigger, "");
    Double_t min = 180;
    Double_t max = 420;
    cer[i]->Fit("gaus","Q","",min,max);
   	TF1 *myfunc=cer[i]->GetFunction("gaus");
    myfunc->SetLineColor(2);
    myfunc->SetLineWidth(3);
   	myfunc->Draw("same");

    c2->cd(i+1);
    T->Draw(Form("%s.cer.a_c[%i]>>cer2%i",arm.Data(), i, i), trigger, "");
    cer2[i]->SetTitle(Form("pmt %i; ADC channel;  ",i+1));
    cer2[i]->SetLineColor(1);
    cer2[i]->SetLineWidth(1);
    Double_t min2 = 3500;
    Double_t max2 = 6500;

    if(run>90000){ max2 = 8500; }
    if(run>92000){ min2 = 2500 }

    TF1 *myfunc2 = new TF1("myfunc2",fitf,min2,max2,3);
    myfunc2->SetParameters(100,500,1);
    myfunc2->SetParameters(2000,10,500);
    cer2[i]->Fit("myfunc2","Q","",min2,max2);
    myfunc2->SetLineColor(2);
    myfunc2->SetLineWidth(3);
    myfunc2->Draw("same");

    //================================================
    cout << "================================================" << endl;
    cout << Form("=============== pmt %i ==================",i+1) << endl;
    cout << "Peak  = " <<  myfunc->GetParameter(1) << " +/- " << myfunc->GetParError(1) << endl;
   	cout << "Main Signal p[0]  = " <<  myfunc2->GetParameter(0) << " +/- " << myfunc2->GetParError(0) << endl;
    cout << "Main Signal p[1]  = " <<  myfunc2->GetParameter(1) << " +/- " << myfunc2->GetParError(1) << endl;
    cout << "Main Signal p[2]  = " <<  myfunc2->GetParameter(2) << " +/- " << myfunc2->GetParError(2) << endl;

    outfile << setiosflags(ios::left) << setw(15) << myfunc->GetParameter(1);
  	outfile << setiosflags(ios::left) << setw(15) << myfunc->GetParError(1);
    outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParameter(0);
    outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParError(0);
    outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParameter(1);
    outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParError(1);
    outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParameter(2);
    outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParError(2);


	}

    outfile << endl;
    outfile.close();

    c1->SaveAs(Form("plots/spe_cer_run%i.pdf",run));
    c2->SaveAs(Form("plots/cer_run%i.pdf",run));
}


