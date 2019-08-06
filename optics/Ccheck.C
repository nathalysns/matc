#include "/work/halla/triton/nathaly/matc/rootalias_spring2018.h"
#include "/work/halla/triton/nathaly/matc/HallA_style.h"

//Double_t Cspring[6]={93142,93130,93112,93087,93048};
//Double_t Cspring[16]={93534,93537,93545,93548,93549,93666,93699,93708,93737,93748,93853,93854,93866,94001,94056,94096};
Double_t Cspring[6]={820,821,925,940};

TChain *T;
TChain *E;
const int binx = 200;

void Ccheck(){
HallA_style();
TCanvas* c1 = new TCanvas("c1","VDC t0 calibration",1000,500);
TH1F *h1 = new TH1F("h1","",binx, -0.04, 0.04);	
TH1F *h2 = new TH1F("h2","",binx, -0.04, 0.04);	
c1->Divide(2,1);



Int_t run;
HallA_style();

h1->SetTitle(";tg y;");
h2->SetTitle(";z_{react};");

Int_t N = 6;
for(Int_t j=0; j<N;j++){

run=Cspring[j];
T = LoadRun(run,"T");
cout<< " Run ----- "<< run << endl;

double angle = dn_dat(run,2);

c1->cd(1);
T->Draw("R.tr.tg_y>>h1", trigger_R);
Int_t max_biny = h1->GetMaximumBin();
Double_t miny = h1->GetBinCenter(max_biny) - 0.0035;
Double_t maxy = h1->GetBinCenter(max_biny) + 0.003;
h1->Fit("gaus","","",miny,maxy);
TF1 *myfunc=h1->GetFunction("gaus");
cout << "Peak  = " <<  myfunc->GetParameter(1) << " +/- " << myfunc->GetParameter(2) << endl;

c1->cd(2);
T->Draw("R.tr.vz>>h2", trigger_R);
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

if(j==0) {c1->SaveAs("PlotsC.pdf(");}
else if(j==N-1) {c1->SaveAs("PlotsC.pdf)");}
else {c1->SaveAs("PlotsC.pdf");}

}



}
