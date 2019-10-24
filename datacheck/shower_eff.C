#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;
TChain *ev;

void shower_eff(Int_t run){

HallA_style();


   
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


	//==============shenkov Efficiency ==============================//
	TH1F *sh_hist = new TH1F("sh_hist","", 1000, 0., 1.5);
	TH1F *pion_hist = new TH1F("pion_hist","", 1000, 0, 1.5);

	TCut trigger = "DL.bit2>0";
  TCut trigger1 = "DL.bit1>0";
	TCut sh_apiontest = "L.cer.asum_c>100 && L.cer.asum_c<1500 && (L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)<0.5";
	TCut sh_ashtest = "L.cer.asum_c>5000 && L.cer.asum_c<15000 && (L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)>0.2"; 
	TCut shtestbef =  dp_cut_L_tight + th_cut_L_tight + ph_cut_L_tight + trigger + track_L;
	TCut piontest =  dp_cut_L_tight + th_cut_L_tight  + ph_cut_L_tight   + trigger1 + track_L;
  arm = "L";
  TString dr = "(L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)";
  TCut beta = "L.tr.beta>0.7 && L.tr.beta<1.5";
  TCut shtest = "";
  TString sht1 = "";
  Double_t  m, a1, a2, c1, c2; 
  m = a1 = a2 = c1 = c2 = 0; 

  if(run>90000){
      m =1.41;
      trigger = "DR.bit5>0";
      trigger1 = "DR.bit4>0";
      shtestbef =  dp_cut_R_tight + th_cut_R_tight + ph_cut_R_tight + trigger + track_R;
      piontest =  dp_cut_R_tight + th_cut_R_tight + ph_cut_R_tight + trigger1 + track_R;
      sh_apiontest = "R.cer.asum_c>100 && R.cer.asum_c<1500 && (R.sh.e+R.ps.e)/(R.tr.p[0]*1000)<0.5";
      sh_ashtest = "R.cer.asum_c>5000 && R.cer.asum_c<15000 && (R.sh.e+R.ps.e)/(R.tr.p[0]*1000)>0.3";
      dr = "(R.ps.e+R.sh.e)/(R.tr.p[0]*1000)";
      arm = "R";
      beta = "R.tr.beta>0.7 && R.tr.beta<1.5";
      sht1 = "(R.sh.e+R.ps.e)>((%f*(R.tr.p[0]*1000))-%f) && (R.sh.e+R.ps.e)<((%f*(R.tr.p[0]*1000))-%f) && (R.tr.p[0]*1000)>%f &&(R.tr.p[0]*1000)<%f ";
      //
      if(run>94024 && run <94067){a1=1500; a2=900; c1=2810; c2=3120;} //R28-HS
      else if(run>93986 && run <94015){a1=1600; a2=700; c1=2650; c2=3120;} //R28-PK
      else if(run>93741 && run <93774){a1=1600; a2=700; c1=2800; c2=3400;} //R26-HS
      else if(run>93708 && run <93739){a1=1600; a2=700; c1=2750; c2=3400;} //R26-PK
      else if(run>93774 && run <93786){a1=1600; a2=700; c1=2700; c2=3200;} //R26-LS
      else if(run>93591 && run <93644){a1=1700; a2=700; c1=2900; c2=3400;} //R24-PK
      else if(run>93648 && run <93699){a1=1800; a2=700; c1=2700; c2=3300;} //R24-LS
      else if(run>93092 && run <93124){a1=950; a2=150; c1=1320; c2=1550;} //R42-HS
      else if(run>93044 && run <93092){a1=950; a2=0; c1=1200; c2=1550;} //R42-PK
      else if(run>93125 && run <93149){a1=950; a2=0; c1=1200; c2=1550;} //R42-LS
      else {a1=3000; a2=0; c1=1000; c2=4000;}        
      shtest = Form(sht1,m,a1,m,a2,c1,c2);
  }

	T->Draw(Form("%s>>sh_hist",dr.Data()), datacurrentcut + shtestbef + sh_ashtest + shtest, "goff");
	T->Draw(Form("%s>>pion_hist",dr.Data()), datacurrentcut + shtestbef + sh_ashtest, "goff");

  Double_t cuteff = sh_hist->GetEntries()/pion_hist->GetEntries();

  cout << cuteff << endl;

  ofstream outfile;
  outfile.open ("sht1.txt",ios::in|ios::app);
  outfile << setiosflags(ios::left) << setw(8) << run;
  outfile << setiosflags(ios::left) << setw(15) << cuteff;
  outfile << endl;
  outfile.close();



}

