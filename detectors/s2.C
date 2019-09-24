#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;


void s2(Int_t run){
   
    HallA_style();

    //=================================================//
    TCut totalcut = sh_cut_L + cer_cut_L + track_L;
    TCut trigger = trigger_L;
    TCut trigger1 = trigger1_L;
    TCut trigger3 = trigger3_L;

    Int_t adc_ini =180;
    TString arm = "L";
    if(run>90000){ totalcut = sh_cut_R + cer_cut_R + track_R; arm = "R";
    trigger = trigger_R;
    trigger1 = trigger4_R;
    trigger3 = trigger6_R;
    adc_ini = 90;
    }

   //run=3102;
    T = LoadRun(run,"T");
    ofstream outfile;
  	outfile.open ("s2.txt",ios::in|ios::app);

    TCanvas *c1 = new TCanvas("c1","",1500, 1500);
    c1->Divide(4,4);

    TCanvas *c2 = new TCanvas("c2","",1500, 1500);
    c2->Divide(4,4);

    TH1F *s2l[16];
    TH1F *s2r[16];
  	
    for(Int_t i=0; i<16;i++){
    
 	s2l[i] = new TH1F(Form("s2l%i",i),"",100,adc_ini,500);
        s2r[i] = new TH1F(Form("s2r%i",i),"",100,adc_ini,500);
 
        c1->cd(i+1);
    	T->Draw(Form("%s.s2.la_c[%i]>>s2l%i",arm.Data(),i,i),"","");
     
    	Double_t len = 50;
    	Int_t max_binl = s2l[i]->GetMaximumBin();
    	Double_t minl = s2l[i]->GetBinCenter(max_binl) - len;
    	Double_t maxl = s2l[i]->GetBinCenter(max_binl) + len;
    	s2l[i]->Fit("landau","Q","",minl,maxl);
    	TF1 *myfuncl=s2l[i]->GetFunction("landau");
    	minl = myfuncl->GetParameter(1) - 1.7*myfuncl->GetParameter(2);
    	maxl = myfuncl->GetParameter(1) + 3.*myfuncl->GetParameter(2);
    	s2l[i]->Fit("landau","Q","",minl,maxl);
    	TF1 *myfunc2l=s2l[i]->GetFunction("landau");
    	cout<<"peak channel l: "<<myfunc2l->GetParameter(1) << "+/-" <<myfunc2l->GetParError(1) <<endl;

        c2->cd(i+1);
    	T->Draw(Form("%s.s2.la_c[%i]>>s2r%i",arm.Data(),i,i),"","");
    	Int_t max_binr = s2r[i]->GetMaximumBin();
    	Double_t minr = s2r[i]->GetBinCenter(max_binr) - len;
    	Double_t maxr = s2r[i]->GetBinCenter(max_binr) + len;
    	s2r[i]->Fit("landau","Q","",minr,maxr);
    	TF1 *myfuncr=s2r[i]->GetFunction("landau");
    	minr = myfuncr->GetParameter(1) - 1.7*myfuncr->GetParameter(2);
    	maxr = myfuncr->GetParameter(1) + 3.*myfuncr->GetParameter(2);
    	s2r[i]->Fit("landau","Q","",minr,maxr);
    	TF1 *myfunc2r=s2r[i]->GetFunction("landau");
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
   c1->SaveAs(Form("plots/s2l_%i.pdf",run));
   c2->SaveAs(Form("plots/s2r_%i.pdf",run));
}
