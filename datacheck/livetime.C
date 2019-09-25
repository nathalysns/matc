#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <TSystem.h>
#include <TString.h>
#include <TCanvas.h>
#include <TCut.h>
#include <TFile.h>
#include <TH1F.h>
#include <TChain.h>
#include <TTree.h>
#include <TF1.h>
#include <tuple>
#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TChain *T;
TChain *ev;
TChain *E;

void livetime(Int_t run){

HallA_style();
ofstream outfile;

outfile.open ("livetime.txt",ios::in|ios::app);
outfile << setiosflags(ios::left) << setw(8) << run;
//run=leftruns[4];
cout << "Run: " << run << endl;
//======Loading Run Numbers
T = LoadRun(run,"T");
E = LoadRun(run,"E");
if(run>90000) ev = LoadRun(run,"evRight");
else ev = LoadRun(run,"evLeft");
if (!T) exit(1);


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

//========= Prescale Factor ===========================//
int ps;
if(run>90000) ps  = GetPS(T,5);
else ps  = GetPS(T,2);
//========= Livetime ===========================//
double LT, LTrecord, LTcounts, LTer;
LT = LTrecord = LTcounts = LTer = 0;
tie(LT, LTrecord, LTcounts, LTer)= livetime(run,ev,T,datacurrentvalues, ps, datacurrentcut); 
cout << "Prescale Factor: " << ps << " Live-time: " << LT << " +/- " << LTer << endl;
cout << "Number of events recorded: " << LTrecord << endl;
cout << "Number of events counted: " << LTcounts << endl; 
cout << "time with beam: " << datatime_beam << endl;

TCanvas *c1= new TCanvas("c1","",1500,800);
c1->Divide(1,2);
c1->cd(1);
TH1F *h1;
if(run<90000){
T->Draw("evLeftdnew_r:evLeftLclock/103700>>h1","","*");
}else{
T->Draw("evRightdnew_r:evRightLclock/103700>>h1","","*");
}
c1->cd(2);
TH1F *h2;
if(run<90000){
T->Draw("evLeftdnew_r:evLeftLclock/103700>>h2",datacurrentcut,"*");
}else{
T->Draw("evRightdnew_r:evRightLclock/103700>>h1",datacurrentcut,"*");
}

outfile << setiosflags(ios::left) << setw(15) << ps;
outfile << setiosflags(ios::left) << setw(15) << LT;
outfile << setiosflags(ios::left) << setw(15) << LTer;
outfile << setiosflags(ios::left) << setw(15) << LTrecord;
outfile << setiosflags(ios::left) << setw(15) << LTcounts;
outfile << setiosflags(ios::left) << setw(15) << datatime_beam;
outfile << endl;
outfile.close();


}
