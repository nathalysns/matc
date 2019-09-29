#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TChain *T;
TChain *E;
TChain *ev;

void trackcheck(Int_t run){

	HallA_style();
    T = LoadRun(run,"T");
    E = LoadRun(run,"E");

	if(run>90000) ev = LoadRun(run,"evRight");
	else ev = LoadRun(run,"evLeft");
	if (!T) exit(1);
 
    cout << "Run number: " << run << endl;

	TString target_data = "Unknown";
    
    //=================================================//
    TCut  shadc = "-L.prl2.asum_c+1100<L.prl1.asum_c";
    TCut totalcut = shadc + cer_cut_L + trigger_L;
    TCut totalcut1 = shadc + cer_cut_L + trigger_L;
    TCut track0 = "L.tr.n==0";
    TCut track = "L.tr.n>0";

    TString arm = "L";
    if(run>90000){ 
    	track0 = "R.tr.n==0";
    	track = "R.tr.n>0";
    	shadc = " -R.sh.asum_c+1200<R.ps.asum_c && R.sh.asum_c>500";
    	totalcut = shadc + cer_cut_R + trigger_R; 
    	arm = "R";
		if(run>93200){
    		shadc = " -R.sh.asum_c+1200<R.ps.asum_c && R.sh.asum_c>500";
    		totalcut = shadc + cer_cut_R + trigger_R; 
    	} 
	}


	TCanvas *c1 = new TCanvas("c1","",1500, 800);
    c1->Divide(2,2);
    TString VDCwires[] = {"u1","v1","u2","v2"}; 
    TH1F *vdc[4];
    TH1F *vdc2[4];
    TH1F *vdc3[4];

    for (Int_t i=0;i<4;i++){
    	c1->cd(i+1);
    	c1->cd(i+1)->SetLogy();
    	vdc[i] = new TH1F(Form("vdc%i",i),"", 450,-50,400);
    	vdc[i]->SetLineWidth(3);
  		vdc[i]->SetLineColor(1);
  		vdc[i]->SetTitle(Form("; vdc %s wire; ",VDCwires[i].Data()));
    	T->Draw(Form("%s.vdc.%s.wire>>vdc%i",arm.Data(),VDCwires[i].Data(),i),totalcut);
    	vdc2[i] = new TH1F(Form("vdc2%i",i),"", 450,-50,400);
    	vdc2[i]->SetLineWidth(2);
  		vdc2[i]->SetLineColor(2);
    	T->Draw(Form("%s.vdc.%s.wire>>vdc2%i",arm.Data(),VDCwires[i].Data(),i),totalcut+track0,"same");
    	vdc3[i] = new TH1F(Form("vdc3%i",i),"", 450,-50,400);
    	vdc3[i]->SetLineWidth(2);
  		vdc3[i]->SetLineColor(4);
  		vdc3[i]->SetLineStyle(10);
    	T->Draw(Form("%s.vdc.%s.wire>>vdc3%i",arm.Data(),VDCwires[i].Data(),i),totalcut+track,"same");
    }
    
   


  

    
    
/*
    RunInformation  runinformation   = GetRunInformation(run, T, E, ev);
	Double_t datacharge, datacurrent, datatime_beam;
	Double_t dataLumInt, databoiling;
	TCut datacurrentcut;
	vector<Double_t> datacurrentvalues;

	target_data = runinformation.targ;
	datacurrentvalues = runinformation.timevalues;
	datacurrent = runinformation.current;
	datacharge = runinformation.charge;
	datatime_beam = runinformation.time_beam;
	dataLumInt = runinformation.luminosity;
	databoiling = runinformation.boiling;
	datacurrentcut  = runinformation.Current_cut;
	Double_t trk, trker;
	trk = trker = 0;
	
	ofstream outfile;
	outfile.open ("trackcheckdp.txt",ios::in|ios::app);
	outfile << setiosflags(ios::left) << setw(8) << run;
    
	for(Int_t l=0;l<10; l++){
		tie(trk,trker) = track_eff(T, datacurrentcut, l);
		cout << l << " track percentage: " << trk << " +/- " << trker << endl;
		outfile << setiosflags(ios::left) << setw(15) <<  trk;
		outfile << setiosflags(ios::left) << setw(15) <<  trker;
	}

	outfile << endl;
	outfile.close();
	*/	
}