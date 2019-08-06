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
#include "/work/halla/triton/nathaly/matc/rootalias_spring2018.h"
#include "/work/halla/triton/nathaly/matc/HallA_style.h"

TChain *T;
TChain *ev;
TChain *E;
void multifoils_check(int run = 3177){

	
HallA_style();
TString arm;
TString target = "Unknown";
double I;
I = 21.5; //=====Only currents +/- 1.5 uA around 22. uA will be taken

//======Left or Right Arm
if (run>90000) arm = "R";
else arm = "L";
//HallA_style();
gStyle->SetOptStat(kFALSE);

//======Left or Right Arm
if (run>90000) arm = "R";
else arm = "L";
//HallA_style();
gStyle->SetOptStat(kFALSE);

//======Loading Run Numbers
T = LoadRun(run,"T");
E = LoadRun(run,"E");
if(run>90000) ev = LoadRun(run,"evRight");
else ev = LoadRun(run,"evLeft");
if (!T) exit(1);

//===========Plots

TH1F *vz = new TH1F("vz","",bins,-0.15,0.15); 
TH2F *vz2D = new TH2F("vz2D","",bins,-0.04,0.04,bins, -0.15, 0.15);

if(run<90000){
T->Draw("L.tr.vz>>vz", sh_cut_L && cer_cut_L && trigger_L, "goff");
T->Draw("L.tr.vz:L.tr.tg_ph>>vz2D", sh_cut_L && cer_cut_L && trigger_L, "goff");
}else{
T->Draw("R.tr.vz>>vz", sh_cut_R && cer_cut_R && trigger_R, "goff");
T->Draw("R.tr.vz:R.tr.tg_ph>>vz2D", sh_cut_R && cer_cut_R && trigger_R, "goff");
}


TCanvas *c1 = new TCanvas("c1","",800,1000);
c1->SetGrid();
c1->Divide(1,2);
c1->cd(1);
c1->cd(1)->SetGrid();
//th->SetTitle("; L.tr.r_x; W (GeV)");
vz->SetTitle(";  vz (m); ");
vz->Draw("colz");
c1->cd(2);
c1->cd(2)->SetGrid();
//ph->SetTitle(";  L.tr.r_y; W (GeV)");

vz2D->SetTitle(";  d#phi ; vz (m)");
vz2D->Draw("colz");

c1->SaveAs(Form("./plots/%i_multifoil.pdf",run)); 

}
