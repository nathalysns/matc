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
//#include "/work/halla/triton/nathaly/matc/rootalias_spring2018.h"
//#include "/work/halla/triton/nathaly/matc/HallA_style.h"

#include "/Users/nathaly/Dropbox/matc/rootalias_spring2018.h"
#include "/Users/nathaly/Dropbox/matc/HallA_style.h"

TChain *T;
TChain *ev;
TChain *E;
void optics_check(int run = 3177, TString kin = "test"){

	
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
Double_t thlim = 0.2;
Double_t phlim = 0.08;
Double_t dplim = 0.08;
Double_t ylim = 0.15;
Double_t xfplim = 0.9;
Double_t Elimi = 0.9;
Double_t Elime = 1.;


TH2F *th = new TH2F("th","",bins,-thlim,thlim,bins, Elimi, Elime); 
TH2F *ph = new TH2F("ph","",bins,-phlim,phlim,bins, Elimi, Elime);
TH2F *dp = new TH2F("dp","",bins,-dplim,dplim,bins, Elimi, Elime);
TH2F *y  = new TH2F("y","",bins,-ylim,ylim,bins, Elimi, Elime);

TH2F *thp = new TH2F("thp","",bins,-thlim,thlim,bins, Elimi, Elime); 
TH2F *php = new TH2F("php","",bins,-phlim,phlim,bins, Elimi, Elime);
TH2F *yfp = new TH2F("yfp","",bins,-dplim,dplim,bins, Elimi, Elime);
TH2F *xfp  = new TH2F("xfp","",bins,-xfplim,xfplim,bins, Elimi, Elime);


T->Draw(Form("sqrt(EK%sxe.W2):R.tr.tg_th>>th",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.tg_ph>>ph",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose , "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.tg_dp>>dp",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.tg_y>>y",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");

T->Draw(Form("sqrt(EK%sxe.W2):R.tr.th>>thp",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.ph>>php",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.y >>yfp",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):R.tr.x>>xfp",arm.Data()), cer_cut_R + sh_cut_R + trigger_R + z_cut_R_loose, "goff");

Double_t protonmass = 0.938;
TLine *line1 = new TLine(-thlim,protonmass,thlim,protonmass);
line1->SetLineWidth(4); line1->SetLineColor(2); line1->SetLineStyle(10);

TLine *line2 = new TLine(-phlim,protonmass,phlim,protonmass);
line2->SetLineWidth(4); line2->SetLineColor(2); line2->SetLineStyle(10);
 
TLine *line3 = new TLine(-phlim,protonmass,phlim,protonmass);
line3->SetLineWidth(4); line3->SetLineColor(2); line3->SetLineStyle(10);

TLine *line4 = new TLine(-ylim,protonmass,ylim,protonmass);
line4->SetLineWidth(4); line4->SetLineColor(2); line4->SetLineStyle(10);
 
TLine *line5 = new TLine(-xfplim,protonmass,xfplim,protonmass);
line5->SetLineWidth(4); line5->SetLineColor(2); line5->SetLineStyle(10);

TCanvas *c1 = new TCanvas("c1","",1200,800);
c1->Divide(2,2);
c1->cd(1);
th->SetTitle("; d#theta; W (GeV)");
th->Draw("colz");
line1->Draw("same");

TLatex latex;
latex.DrawLatex(0.08,0.99,"Hydrogen");
latex.DrawLatex(0.08,0.985,Form("Kinematic: %s", kin.Data()));

c1->cd(2);
ph->SetTitle(";  d#phi; W (GeV)");
ph->Draw("colz");
line2->Draw("same");
c1->cd(3);
dp->SetTitle(";  dp; W (GeV)");
dp->Draw("colz");
line3->Draw("same");
c1->cd(4);
y->SetTitle(";  tar y; W (GeV)");
y->Draw("colz");
line4->Draw("same");
TCanvas *c2 = new TCanvas("c2","",1200,800);
c2->Divide(2,2);
c2->cd(1);
thp->SetTitle(";  #theta _{fp}; W (GeV)");
thp->Draw("colz");
line1->Draw("same");
latex.DrawLatex(0.08,0.99,"Hydrogen");
latex.DrawLatex(0.08,0.985,Form("Kinematic: %s", kin.Data()));

c2->cd(2);
php->SetTitle(";  #phi _{fp}; W (GeV)");
php->Draw("colz");
line2->Draw("same");
line3->Draw("same");
c2->cd(3);
yfp->SetTitle(";  y_{fp}; W (GeV)");
yfp->Draw("colz");
line3->Draw("same");
c2->cd(4);
xfp->SetTitle(";  x_{fp}; W (GeV)");
xfp->Draw("colz");
line5->Draw("same");

c1->SaveAs(Form("./plots/%i_1.pdf",run));
c2->SaveAs(Form("./plots/%i_2.pdf",run));

}
