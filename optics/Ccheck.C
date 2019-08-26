#include "/work/halla/triton/nathaly/matc/rootalias_spring2018.h"
#include "/work/halla/triton/nathaly/matc/HallA_style.h"


TChain *T;
TChain *E;
const int binx = 200;

void Ccheck( Int_t run){
HallA_style();
TCanvas* c1 = new TCanvas("c1","VDC t0 calibration",1000,500);
TH1F *h1 = new TH1F("h1","",binx, -0.04, 0.04);	
TH1F *h2 = new TH1F("h2","",binx, -0.04, 0.04);	
c1->Divide(2,1);

TString arm = "L";
TCut trigger = trigger_L;

if(run>90000){
arm ="R";
trigger = trigger_R;
}

HallA_style();

h1->SetTitle(";tg y;");
h2->SetTitle(";z_{react};");

T = LoadRun(run,"T");
cout<< " Run ----- "<< run << endl;

double angle = dn_dat(run,2);


c1->cd(1);
T->Draw(Form("%s.tr.tg_y>>h1",arm.Data()), trigger );
Int_t max_biny = h1->GetMaximumBin();
Double_t miny = h1->GetBinCenter(max_biny) - 0.0035;
Double_t maxy = h1->GetBinCenter(max_biny) + 0.003;
h1->Fit("gaus","","",miny,maxy);
TF1 *myfunc=h1->GetFunction("gaus");
cout << "Peak  = " <<  myfunc->GetParameter(1) << " +/- " << myfunc->GetParameter(2) << endl;

c1->cd(2);
T->Draw(Form("%s.tr.vz>>h2",arm.Data()), trigger);
Int_t max_binz = h2->GetMaximumBin();
Double_t minz = h2->GetBinCenter(max_binz) - 0.006;
Double_t maxz = h2->GetBinCenter(max_binz) + 0.005;
h2->Fit("gaus","","",minz,maxz);
TF1 *myfunc2 = h2->GetFunction("gaus");
cout << "Peak  = " <<  myfunc2->GetParameter(1) << " +/- " << myfunc2->GetParameter(2) << endl;

ofstream outfile;
outfile.open ("Ccheck.txt",ios::in|ios::app);
outfile << setiosflags(ios::left) << setw(8) << run;
outfile << setiosflags(ios::left) << setw(8) << angle;
outfile << setiosflags(ios::left) << setw(15) << myfunc->GetParameter(1);
outfile << setiosflags(ios::left) << setw(15) << myfunc->GetParError(1);
outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParameter(1);
outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParError(1) << endl;
outfile.close();

c1->SaveAs(Form("plots/%i_C.pdf",run));

}



