#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;


void s2(Int_t run){
   
    HallA_style();
    TH1F *s2l = new TH1F("s2l","",100,150,1000);
    TH1F *s2r = new TH1F("s2r","",100,150,1000);

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

    //run=3102;
    T = LoadRun(run,"T");
    ofstream outfile;
  	outfile.open ("s2.txt",ios::in|ios::app);
  	
    for(Int_t i=0; i<16;i++){
    	T->Draw(Form("%s.s2.la_c[%i]>>s2l",i),arm.Data(),trigger,"goff");
    	T->Draw(Form("%s.s2.ra_c[%i]>>s2r",i),arm.Data(),trigger,"goff");

    	Int_t max_binl = s2l->GetMaximumBin();
    	Double_t minl = s2l->GetBinCenter(max_binl) - 500;
    	Double_t maxl = s2l->GetBinCenter(max_binl) + 500;
    	s2l->Fit("landau","Q","",minl,maxl);
    	TF1 *myfuncl=s2l->GetFunction("landau");
    	minl = myfuncl->GetParameter(1) - 2*myfuncl->GetParameter(2);
    	maxl = myfuncl->GetParameter(1) + 1.5*myfuncl->GetParError(2);
    	s2l->Fit("landau","Q","",minl,maxl);
    	TF1 *myfunc2l=s2l->GetFunction("landau");
    	cout<<"peak channel l: "<<myfunc2l->GetParameter(1) << "+/-" <<myfunc2l->GetParError(1) <<endl;


    	Int_t max_binr = s2r->GetMaximumBin();
    	Double_t minr = s2r->GetBinCenter(max_binr) - 500;
    	Double_t maxr = s2r->GetBinCenter(max_binr) + 500;
    	s2r->Fit("landau","Q","",minr,maxr);
    	TF1 *myfuncr=s2r->GetFunction("landau");
    	minr = myfuncr->GetParameter(1) - 2*myfuncr->GetParameter(2);
    	maxr = myfuncr->GetParameter(1) + 1.5*myfuncr->GetParameter(2);
    	s2r->Fit("landau","Q","",minr,maxr)r
    	TF1 *myfunc2r=s2r->GetFunction("landau");
    	cout<<"peak channel r: "<<myfunc2r->GetParameter(1) << "+/-" <<myfunc2r->GetParError(1) <<endl;

    	
  		outfile << setiosflags(ios::left) << setw(8) << run;
  		outfile << setiosflags(ios::left) << setw(15) << myfunc2l->GetParameter(1);
  		outfile << setiosflags(ios::left) << setw(15) << myfunc2l->GetParError(1);
  		outfile << setiosflags(ios::left) << setw(15) << myfunc2r->GetParameter(1);
  		outfile << setiosflags(ios::left) << setw(15) << myfunc2r->GetParError(1); 
  		
	}

	outfile << endl;
	outfile.close();


}