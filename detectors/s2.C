#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;


void s2(Int_t run){
   
    HallA_style();
    TH1F *s2l = new TH1F("s2l","",100,100,500);
    TH1F *s2r = new TH1F("s2r","",100,100,500);

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
    	T->Draw(Form("%s.s2.la_c[%i]>>s2l",arm.Data(),i),"","goff");
    	T->Draw(Form("%s.s2.ra_c[%i]>>s2r",arm.Data(),i),"","goff");
         
	Double_t len = 80;
	if(i==0 || i==15) len =50;
    	Int_t max_binl = s2l->GetMaximumBin();
    	Double_t minl = s2l->GetBinCenter(max_binl) - len;
    	Double_t maxl = s2l->GetBinCenter(max_binl) + len;
    	s2l->Fit("landau","Q","",minl,maxl);
    	TF1 *myfuncl=s2l->GetFunction("landau");
    	minl = myfuncl->GetParameter(1) - 1.*myfuncl->GetParameter(2);
    	maxl = myfuncl->GetParameter(1) + 1.*myfuncl->GetParError(2);
    	s2l->Fit("landau","Q","",minl,maxl);
    	TF1 *myfunc2l=s2l->GetFunction("landau");
    	cout<<"peak channel l: "<<myfunc2l->GetParameter(1) << "+/-" <<myfunc2l->GetParError(1) <<endl;


    	Int_t max_binr = s2r->GetMaximumBin();
    	Double_t minr = s2r->GetBinCenter(max_binr) - len;
    	Double_t maxr = s2r->GetBinCenter(max_binr) + len;
    	s2r->Fit("landau","Q","",minr,maxr);
    	TF1 *myfuncr=s2r->GetFunction("landau");
    	minr = myfuncr->GetParameter(1) - 1.*myfuncr->GetParameter(2);
    	maxr = myfuncr->GetParameter(1) + 1.*myfuncr->GetParameter(2);
    	s2r->Fit("landau","Q","",minr,maxr);
    	TF1 *myfunc2r=s2r->GetFunction("landau");
    	cout<<"peak channel r: "<<myfunc2r->GetParameter(1) << "+/-" <<myfunc2r->GetParError(1) <<endl;

	Double_t t1 = myfunc2l->GetParameter(1);
	Double_t t1er = myfunc2l->GetParError(1);
	Double_t t2 = myfunc2r->GetParameter(1);
        Double_t t2er = myfunc2r->GetParError(1);

	if (t1 <= 50) { t1 = 0; t1er =0;}
	if (t2 <= 50) { t2 = 0; t2er =0;}
    	
  		outfile << setiosflags(ios::left) << setw(8) << run;
  		outfile << setiosflags(ios::left) << setw(15) << t1;
  		outfile << setiosflags(ios::left) << setw(15) << t1er;
  		outfile << setiosflags(ios::left) << setw(15) << t2;
  		outfile << setiosflags(ios::left) << setw(15) << t2er; 
  		
	}

	outfile << endl;
	outfile.close();


}