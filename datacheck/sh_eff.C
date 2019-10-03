#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;
TChain *ev;

void sh_eff(Int_t run){

    HallA_style();

    TCanvas *c1 = new TCanvas("c1","",800,600);
    Int_t N = 1;
   
    T = LoadRun(run,"T");
	E = LoadRun(run,"E");
	if(run>90000) ev = LoadRun(run,"evRight");
	else ev = LoadRun(run,"evLeft");
	if (!T) exit(1);

    cout << run << endl;

    TString target_data = "Unknown";

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

    TH1F *sh_t1 = new TH1F("sh_t1","", 500, 0, 10000);
    TH1F *sh_t2 = new TH1F("sh_t2","", 500, 0, 10000);

    sh_t2->SetTitle(";Cherenkov sum;");
    sh_t1->SetLineColor(2);
    sh_t1->SetLineWidth(3);
    sh_t2->SetLineColor(4);
    sh_t2->SetLineWidth(4);
    sh_t1->SetLineStyle(10);
	//==============shenkov Efficiency ==============================//
	TH1F *sh_hist = new TH1F("sh_hist","", 1000, 0, 2);
	TH1F *pion_hist = new TH1F("pion_hist","", 1000, 0, 2);

	TCut trigger = "DL.bit2>0";
    TCut trigger1 = "DL.bit1>0";
	TCut sh_apiontest = "L.cer.asum_c>100 && L.cer.asum_c<1500 && (L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)<0.5";
	TCut shtest =  dp_cut_L_loose + th_cut_L_loose + ph_cut_L_loose + trigger + track_L;
	TCut piontest =  dp_cut_L_loose + th_cut_L_loose + ph_cut_L_loose + trigger1 + track_L;
    arm = "L";

    if(run>90000){
      trigger = "DR.bit5>0";
      trigger1 = "DR.bit4>0";
      shtest =  dp_cut_R_loose + th_cut_R_loose + ph_cut_R_loose + trigger + track_R;
      piontest =  dp_cut_R_loose + th_cut_R_loose + ph_cut_R_loose + trigger1 + track_R;
      arm = "R";
    }
	TCut sh_ashtest = Form("%s.cer.asum_c>5000 && %s.cer.asum_c<10000",arm.Data(),arm.Data());

	T->Draw("(L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)>>sh_hist", datacurrentcut + shtest + sh_ashtest, "goff");
	T->Draw("(L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)>>pion_hist", datacurrentcut + piontest + sh_apiontest && !trigger, "");

	Double_t cut = 0.02;
	Int_t steps = 1.2/cut+1;
	Double_t init = 0; 
	TH1 *final = new TH1F("final","",steps,0, 1.2);
	TH1 *finalpion = new TH1F("finalpion","",steps,0, 1.2);

	Double_t sh1500 = 0;
   	Double_t pion1500 = 0;

	for(Int_t m=0; m<steps;m++ ){
	
	init = init + cut;
	Int_t bmin = sh_hist->FindBin(init); 
    Int_t bmax = sh_hist->FindBin(1.5); //in your case xmax=0.8
    
  	Double_t integral1 = sh_hist->Integral(bmin,bmax);
  	Double_t integral2 = sh_hist->Integral(0,bmax);
  	Double_t pionintegral1 = pion_hist->Integral(bmin,bmax);
  	Double_t pionintegral2 = pion_hist->Integral(0,bmax);

  	double ceff = integral1/integral2;
  	double peff = 1-pionintegral1/pionintegral2;
  	
  	if (init>0.7 && init < 0.71){ 
  		if(peff==1){peff=0.9999;}
  		sh1500 = ceff; pion1500 = peff;
  		cout<< "sh eff 0.7 = " << ceff <<endl; cout<< "pion eff 0.7 = " << peff <<endl;
  	}    	
	
  	
  	final->Fill(init,ceff);
   	finalpion->Fill(init,peff);
   	
   	//cout << init << " " << ceff << " " << peff << endl;	
  	
   }


	final->SetMarkerStyle(34);
	final->SetMarkerSize(1);
	finalpion->SetMarkerColor(2);
	finalpion->SetMarkerStyle(8);
	finalpion->SetMarkerSize(1);
	final->GetYaxis()->SetRangeUser(0.2,1.05);
	final->SetTitle("; Cherenkov Sum ADC; Efficiency");
	final->Draw("hist p");
	finalpion->Draw("hist psame");

	TLine *line = new TLine(0.7,0.2,0.7,1.05);
	line->SetLineWidth(3);
	line->SetLineStyle(9);
	
  	line->SetLineColor(922);
  	line->Draw("same");

  	auto legend = new TLegend(0.6,0.2,0.85,0.3);
    legend->AddEntry(final,"Electron Efficiency","p");
    legend->AddEntry(finalpion,"Pion Reection Efficiency","p");

    legend->Draw();

    TLatex l;
   	l.SetTextSize(0.03);
    l.DrawLatex(0.71,0.7,Form(">%0.2f%% Electron Efficiency",sh1500*100));
    l.DrawLatex(0.71,0.6,Form("#color[2]{>%0.2f%% Pion Rejection Efficiency}",pion1500*100));
     l.DrawLatex(0.2,0.4,Form("Run %i",run));
    gPad->Update();
   	
   	ofstream outfile;
    outfile.open ("cereff.txt",ios::in|ios::app);
    outfile << setiosflags(ios::left) << setw(8) << run;
    outfile << setiosflags(ios::left) << setw(15) << cer1500;
    outfile << setiosflags(ios::left) << setw(15) << pion1500;
    outfile << endl;
    outfile.close();

    c1->SaveAs(Form("plots/sh_eff_%i.pdf",run)); 

}

