#include "../rootalias_spring2018.h"
#include "../HallA_style.h"


TString arm;
TString armHRS;
TChain *T;
TChain *E;
TChain *ev;

void cer_eff(Int_t run){

    HallA_style();

    TCanvas *c1 = new TCanvas("c1","",800,600);
    Int_t N = 101;

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

    TH1F *cer_t1 = new TH1F("cer_t1","", 500, 0, 10000);
    TH1F *cer_t2 = new TH1F("cer_t2","", 500, 0, 10000);

    cer_t2->SetTitle(";Cherenkov sum;");
    cer_t1->SetLineColor(2);
    cer_t1->SetLineWidth(3);
    cer_t2->SetLineColor(4);
    cer_t2->SetLineWidth(2);
    cer_t1->SetLineStyle(10);
	//==============Cerenkov Efficiency ==============================//
	TH1F *cer_hist = new TH1F("cer_hist","", 1000, 0, 20000);
	TH1F *pion_hist = new TH1F("pion_hist","", 1000, 0, 20000);
	TCut sh_acertest = "(L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)<1.1 && (L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)>0.7";
	TCut sh_apiontest = "(L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)<0.5 && (L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)>0.0";
	
	TCut trigger = "DL.bit2>0";
	TCut trigger1 = "DL.bit1>0";
	TCut certest =  dp_cut_L_tight + th_cut_L_tight + ph_cut_L_tight + trigger + track_L;
	TCut piontest =  dp_cut_L_tight + th_cut_L_tight + ph_cut_L_tight + trigger1 + track_L;
	arm = "L";

	if(run>90000){
		trigger = "DR.bit5>0";
		trigger1 = "DR.bit4>0";
		certest =  datacurrent + dp_cut_R_tight + th_cut_R_tight + ph_cut_R_tight + trigger + track_R;
		piontest =  datacurrent + dp_cut_R_tight + th_cut_R_tight + ph_cut_R_tight + trigger1 + track_R;
		arm = "R";
		sh_acertest = "(R.ps.e+R.sh.e)/(R.tr.p[0]*1000)<1.1 && (R.ps.e+R.sh.e)/(R.tr.p[0]*1000)>0.7";
                sh_apiontest = "(R.ps.e+R.sh.e)/(R.tr.p[0]*1000)<0.5 && (R.ps.e+R.sh.e)/(R.tr.p[0]*1000)>0.0";
	}

	T->Draw(Form("%s.cer.asum_c>>cer_hist",arm.Data()),  datacurrentcut + certest + sh_acertest, "goff");
	T->Draw(Form("%s.cer.asum_c>>pion_hist",arm.Data()),  datacurrentcut + piontest + sh_apiontest && !trigger, "goff");

	Int_t cut = 60;
	Int_t steps = 4500/cut;
	Int_t init = 0; 
	TH1 *final = new TH1F("final","",steps,0, 4500);
	TH1 *finalpion = new TH1F("finalpion","",steps,0, 4500);

	Double_t cer1500 = 0;
   	Double_t pion1500 = 0;

	for(Int_t m=0; m<steps;m++ ){
	init = init + cut;
	Int_t bmin = cer_hist->FindBin(init); //in your case xmin=-1.5
    Int_t bmax = cer_hist->FindBin(15000); //in your case xmax=0.8
    Int_t pionbmax = cer_hist->FindBin(4000); 
  	Double_t integral1 = cer_hist->Integral(bmin,bmax);
  	Double_t integral2 = cer_hist->Integral(0,bmax);
  	Double_t pionintegral1 = pion_hist->Integral(bmin,bmax);
  	Double_t pionintegral2 = pion_hist->Integral(0,bmax);

  	double ceff = integral1/integral2;
  	double peff = 1-pionintegral1/pionintegral2;

  	final->Fill(init,ceff);
   	finalpion->Fill(init,peff);
   	
  	if (init == 1500){ 
  		if(peff==1){peff=0.9999;}
  		cer1500 = ceff; pion1500 = peff;cout<< "cer eff 1500 = " << ceff <<endl; cout<< "pion eff 1500 = " << peff <<endl;}  
  	

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

	TLine *line = new TLine(1500,0.2,1500,1.05);
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
    l.DrawLatex(1550,0.7,Form(">%0.2f%% Electron Efficiency",cer1500*100));
    l.DrawLatex(1550,0.6,Form("#color[2]{>%0.2f%% Pion Rejection Efficiency}",pion1500*100));
     l.DrawLatex(2000,0.4,Form("Run %i",run));
    gPad->Update();
   
   	ofstream outfile;
    outfile.open ("cerefft1.txt",ios::in|ios::app);
    outfile << setiosflags(ios::left) << setw(8) << run;
    outfile << setiosflags(ios::left) << setw(15) << cer1500;
    outfile << setiosflags(ios::left) << setw(15) << pion1500;
    outfile << endl;
    outfile.close();

    c1->SaveAs(Form("plots/cer_eff_%i.pdf",run)); 

}

