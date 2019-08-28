#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;


void s0(Int_t run){

    HallA_style();
    

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

    TH1F *tt2 = new TH1F("tt2","FADC Ls0.ta_c",300,-200,3000);
    TH1F *tt3 = new TH1F("tt3","FADC Ls0.ra_c",300,-200,3000);
   
    T = LoadRun(run,"T");
    cout <<"----run: " << run << endl;
    T->Draw(Form("%s.s0.la_c>>tt2", arm.Data()),trigger,"");
    tt2->SetXTitle(Form("%s.s0.la_c", arm.Data()));
    Int_t max_bin = tt2->GetMaximumBin();
    Double_t min = tt2->GetBinCenter(max_bin) - 100;
    Double_t max = tt2->GetBinCenter(max_bin) + 100;
    tt2->Fit("landau","Q","",min,max);

    TF1 *myfunc=tt2->GetFunction("landau");
    min = myfunc->GetParameter(1) - 2*myfunc->GetParameter(2);
    max = myfunc->GetParameter(1) + 1.5*myfunc->GetParameter(2);
    tt2->Fit("landau","Q","",min,max);
    TF1 *myfunc2=tt2->GetFunction("landau");
    cout<<"peak channel l: "<<myfunc2->GetParameter(1) << "+/-" <<myfunc2->GetParameter(2) <<endl;

    T->Draw(Form("%s.s0.ra_c>>tt3", arm.Data()),trigger,"goff");
    tt2->SetXTitle(Form("%s.s0.ra_c", arm.Data()));
    Int_t max_binr = tt3->GetMaximumBin();
    Double_t minr = tt3->GetBinCenter(max_binr) - 100;
    Double_t maxr = tt3->GetBinCenter(max_binr) + 100;
    tt3->Fit("landau","Q","",minr,maxr);
    TF1 *myfuncr=tt3->GetFunction("landau");
    minr = myfuncr->GetParameter(1) - 2*myfuncr->GetParameter(2);
    maxr = myfuncr->GetParameter(1) + 1.5*myfuncr->GetParameter(2);
    tt3->Fit("landau","Q","",minr,maxr);
    TF1 *myfunc2r=tt3->GetFunction("landau");
    cout<<"peak channel r: "<<myfunc2r->GetParameter(1) << "+/-" <<myfunc2r->GetParameter(2) <<endl;

  ofstream outfile;
  outfile.open ("s0.txt",ios::in|ios::app);
  outfile << setiosflags(ios::left) << setw(8) << run;
  outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParameter(1);
  outfile << setiosflags(ios::left) << setw(15) << myfunc2->GetParameter(2);
  outfile << setiosflags(ios::left) << setw(15) << myfunc2r->GetParameter(1);
  outfile << setiosflags(ios::left) << setw(15) << myfunc2r->GetParameter(2) << endl;
  outfile.close();
}

   
