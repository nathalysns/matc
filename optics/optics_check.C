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
void optics_check(int run = 3177){

	
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

TH2F *th = new TH2F("th","",bins,-0.08,0.08,bins, 0.92, 0.96); 
TH2F *ph = new TH2F("ph","",bins,-0.04,0.04,bins, 0.92, 0.96);
TH2F *dp = new TH2F("dp","",bins,-0.04,0.04,bins, 0.92, 0.96);
TH2F *y  = new TH2F("y","",bins,-0.07,0.07,bins, 0.92, 0.96);

TH2F *thp = new TH2F("thp","",bins,-0.08,0.08,bins, 0.92, 0.96); 
TH2F *php = new TH2F("php","",bins,-0.045,0.045,bins, 0.92, 0.96);
TH2F *yfp = new TH2F("yfp","",bins,-0.06,0.06,bins, 0.92, 0.96);
TH2F *xfp  = new TH2F("xfp","",bins,-0.6,0.6,bins, 0.92, 0.96);


T->Draw(Form("sqrt(EK%sxe.W2):R.tr.tg_th>>th",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.tg_ph>>ph",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose , "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.tg_dp>>dp",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.tg_y>>y",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");

T->Draw(Form("sqrt(EK%sxe.W2):R.tr.th>>thp",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.ph>>php",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.y >>yfp",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.x>>xfp",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");

TCanvas *c1 = new TCanvas("c1","",1200,800);
c1->Divide(2,2);
c1->cd(1);
th->SetTitle("; d#theta; W (GeV)");
th->Draw("colz");
c1->cd(2);
ph->SetTitle(";  d#phi; W (GeV)");
ph->Draw("colz");
c1->cd(3);
dp->SetTitle(";  dp; W (GeV)");
dp->Draw("colz");
c1->cd(4);
y->SetTitle(";  tar y; W (GeV)");
y->Draw("colz");
TCanvas *c2 = new TCanvas("c2","",1200,800);
c2->Divide(2,2);
c2->cd(1);
thp->SetTitle(";  #theta _{fp}; W (GeV)");
thp->Draw("colz");
c2->cd(2);
php->SetTitle(";  #phi _{fp}; W (GeV)");
php->Draw("colz");
c2->cd(3);
yfp->SetTitle(";  y_{fp}; W (GeV)");
yfp->Draw("colz");
c2->cd(4);
xfp->SetTitle(";  x_{fp}; W (GeV)");
xfp->Draw("colz");

c1->SaveAs(Form("./plots/%i_1.pdf",run));
c2->SaveAs(Form("./plots/%i_2.pdf",run));

}
