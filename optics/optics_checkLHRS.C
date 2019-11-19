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

#include "/Users/nathaly/Dropbox/matc/optics/rootalias_spring2018.h"
#include "/Users/nathaly/Dropbox/matc/optics/HallA_style.h"

TChain *T;
TChain *ev;
TChain *E;
void optics_checkLHRS(int run = 3177){

	
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

TH2F *th = new TH2F("th","",bins,-0.1,0.1,bins, 0.92, 0.96); 
TH2F *ph = new TH2F("ph","",bins,-0.04,0.04,bins, 0.92, 0.96);
TH2F *dp = new TH2F("dp","",bins,-0.04,0.04,bins, 0.92, 0.96);
TH2F *y  = new TH2F("y","",bins,-0.03,0.03,bins, 0.92, 0.96);

TH2F *thp = new TH2F("thp","",bins,-0.08,0.08,bins, 0.92, 0.96); 
TH2F *php = new TH2F("php","",bins,-0.045,0.045,bins, 0.92, 0.96);
TH2F *yfp = new TH2F("yfp","",bins,-0.06,0.06,bins, 0.92, 0.96);
TH2F *xfp  = new TH2F("xfp","",bins,-0.4,0.4,bins, 0.92, 0.96);


T->Draw(Form("sqrt(EK%sxe.W2):L.tr.tg_th>>th",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.tg_ph>>ph",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.tg_dp>>dp",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.tg_y>>y",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");

/*
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.r_x>>th",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.r_y>>ph",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.r_th>>dp",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.r_ph>>y",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
*/

T->Draw(Form("sqrt(EK%sxe.W2):L.tr.th>>thp",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.ph>>php",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.y >>yfp",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");
T->Draw(Form("sqrt(EK%sxe.W2):L.tr.x>>xfp",arm.Data()), sh_cut_L && cer_cut_L && z_cut_L_loose, "goff");

TLine *line = new TLine(-0.4,0.9382,0.4,0.9382);
line->SetLineColor(kRed);

TCanvas *c1 = new TCanvas("c1","",1200,800);
c1->Divide(2,2);
c1->cd(1);
c1->cd(1)->SetGrid();
//th->SetTitle("; L.tr.r_x; W (GeV)");
th->SetTitle("; d#theta ; W (GeV)");
th->Draw("colz");
c1->cd(2);
c1->cd(2)->SetGrid();
//ph->SetTitle(";  L.tr.r_y; W (GeV)");
ph->SetTitle(";  d#phi ; W (GeV)");
ph->Draw("colz");
c1->cd(3);
c1->cd(3)->SetGrid();
//dp->SetTitle(";  L.tr.r_th; W (GeV)");
dp->SetTitle(";  dp ; W (GeV)");
dp->Draw("colz");
c1->cd(4);
c1->cd(4)->SetGrid();
//y->SetTitle(";  L.tr.r_ph; W (GeV)");
y->SetTitle(";  y ; W (GeV)");
y->Draw("colz");
TCanvas *c2 = new TCanvas("c2","",1200,800);
c2->Divide(2,2);
c2->cd(1)->SetGrid();
c2->cd(2)->SetGrid();
c2->cd(3)->SetGrid();
c2->cd(4)->SetGrid();

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
