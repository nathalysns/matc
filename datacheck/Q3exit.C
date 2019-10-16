#include "../rootalias_spring2018.h"
#include "../HallA_style.h"


TString arm;
TChain *T;

void Q3exit(Int_t run){

HallA_style();
T = LoadRun(run,"T");
if (!T) exit(1);
cout << "Run number: " << run << endl;

TCut acc = acc_cut_tightL;
TCut track1 = "L.tr.n==1";
TCut track = "L.tr.n>1";
TString arm = "L";
TCut cutz = z_cut_L_tight;

// to project track from focal plane back to an aperture ( e.g. Q3 exit at -3.57m )
TString  fp_proj   = "L.tr.x+L.tr.th*%g:L.tr.y+L.tr.ph*%g";

if(run>90000){ 
    track1 = "R.tr.n==1";
	track = "R.tr.n>1";
    acc = acc_cut_tightR;
    arm = "R";
    fp_proj    = "R.tr.x+R.tr.th*%g:R.tr.y+R.tr.ph*%g";
    cutz = z_cut_R_tight;
}

TH2F *h1 = new TH2F("h1","",200,-0.4,0.4,200,-0.8,0.8);
TH2F *h2 = new TH2F("h2","",200,-0.4,0.4,200,-0.8,0.8);
TH2F *h3 = new TH2F("h3","",200,-0.4,0.4,200,-0.8,0.8);
TH2F *h4 = new TH2F("h4","",200,-0.4,0.4,200,-0.8,0.8);

// to project track from focal plane back to an aperture ( e.g. Q3 exit at -3.57m )
TString     q3_proj    = Form(fp_proj,-3.57,-3.57);

TCanvas *c1 = new TCanvas("c1","",2000,600);
c1->Divide(4,1);
c1->cd(1);
h1->SetTitle("No Cuts; Horizontal (DCS); Vertical(DCS)");
T->Draw(Form("%s>>h1",q3_proj.Data()),"","colz");
c1->cd(2);
T->Draw(Form("%s>>h2",q3_proj.Data()),track1,"colz");
h2->SetTitle("One track; Horizontal (DCS); Vertical(DCS)");
c1->cd(3);
T->Draw(Form("%s>>h3",q3_proj.Data()),track1 + acc,"colz");
h3->SetTitle("One track + Acceptance; Horizontal (DCS); Vertical(DCS)");
c1->cd(4);
T->Draw(Form("%s>>h4",q3_proj.Data()), track + acc,"colz");
h4->SetTitle(" Multitrack + Acceptance; Horizontal (DCS); Vertical(DCS)");

}