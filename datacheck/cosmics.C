#include "../rootalias_spring2018cosmics.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;
TChain *ev;

void cosmics(Int_t run){

	HallA_style();

    T = LoadRun(run,"T");
	E = LoadRun(run,"E");
	if(run>90000) ev = LoadRun(run,"evRight");
	else ev = LoadRun(run,"evLeft");
	if (!T) exit(1);

    cout << run << endl;

    TString target_data = "Unknown";

	RunInformation  runinformation   = GetRunInformation(run, T, E, ev, 0);

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
/*
	TCanvas *c1 = new TCanvas("c1","",500,500);
	if(run<90000) T->Draw("evLeftdnew_r:evLeftLclock/103700", datacurrentcut,"*");
	else T->Draw("evRightdnew_r:evRightLclock/103700", datacurrentcut,"*");
*/
	arm = "L";
	TCut trig1 = "DL.bit1>0";
	TCut trig2 = "DL.bit2>0";
	TCut trig3 = "DL.bit3>0";
	if(run>90000){
	  arm = "R";
	  trig1 = "DR.bit4>0";
    trig2 = "DR.bit5>0";
    trig3 = "DR.bit6>0";
	}
	cout << datatime_beam << " seconds with no current" << endl;

	TH1F *h1 = new TH1F("h1", "", 500,-10,10);
	TH1F *h2 = new TH1F("h2", "", 500,-10,10);
	TH1F *h3 = new TH1F("h3", "", 500,-10,10);

	T->Draw(Form("EK%sxe.x_bj>>h1",arm.Data()),datacurrentcut + trig1,"goff");
  T->Draw(Form("EK%sxe.x_bj>>h2",arm.Data()),datacurrentcut + trig2,"goff");
  T->Draw(Form("EK%sxe.x_bj>>h3",arm.Data()),datacurrentcut + trig3,"goff");

	cout << "Trigger1(4) counts = " << h1->GetEntries() << endl; 
	cout << "Trigger2(5) counts = " << h2->GetEntries() << endl; 
	cout << "Trigger3(6) counts = " << h3->GetEntries() << endl; 

	//========================================================================//
	
	TH1F *hp=new TH1F("hp","",400,0,4);
  TString mom = "HacL_D1_P0rb";
  if (run>90000 ) mom = "HacR_D1_P0rb";
  T->Draw(Form("%s>>hp",mom.Data()),"","goff");
  Double_t p0 = hp->GetMean();

  //=================================================//
  TCut shcut = Form("(L.prl1.e+L.prl2.e)/(%f*1000)>0.8 && (L.prl1.e+L.prl2.e)/(%f*1000)<1.5",p0,p0);
  TCut totalcut = shcut + cer_cut_L + trigger_L;
  TCut totalcut1 = shcut + cer_cut_L + trigger_L;
  TCut acc = acc_cut_looseL;
  TCut track0 = "L.tr.n==0";
  TCut track1 = "L.tr.n==1";
  TCut track = "L.tr.n>0";
  TString arm = "L";
  TCut zcut = z_cut_L_tight;
  TCut totalrtig =  dp_cut_L_loose + th_cut_L_loose + ph_cut_L_loose + track_L + sh_cut_L;
    
  if(run>90000){
    track0 = "R.tr.n==0";
    track1 = "R.tr.n==1";
    track = "R.tr.n>0";
    acc = acc_cut_looseR;
    shcut = Form("(R.sh.e+R.ps.e)/(%f*1000)>0.8 && (R.sh.e+R.ps.e)/(%f*1000)<1.5",p0,p0);
    totalcut = shcut + cer_cut_R + trigger_R;
    arm = "R";
    zcut = z_cut_R_tight;
    totalrtig = dp_cut_R_loose + th_cut_R_loose + ph_cut_R_loose + track_R + sh_cut_R;
	}

  TH1F *tr1 = new TH1F("tr1","",500,0,2);
  TH1F *tr2 = new TH1F("tr2","",500,0,2);
  TH1F *tr1eff = new TH1F("tr1eff","",500,0,2);
  TH1F *tr2eff = new TH1F("tr2eff","",500,0,2);

    //====== 0 track inneficiency
  T->Draw(Form("EK%sx.x_bj>>tr1",arm.Data()), datacurrentcut + totalcut + track0, "goff" );
  T->Draw(Form("EK%sx.x_bj>>tr1eff",arm.Data()), datacurrentcut + totalcut, "goff" );
  cout << "Events with 0 tracks: " << tr1->GetEntries() << endl;
  cout << "Events with Multitracks in 0 tracks: " << tr1eff->GetEntries() << endl;
    
  //====== Multitracks
  T->Draw(Form("EK%sx.x_bj>>tr2",arm.Data()), datacurrentcut + totalcut + track1 + acc , "goff" );
  T->Draw(Form("EK%sx.x_bj>>tr2eff",arm.Data()), datacurrentcut + totalcut + acc, "goff" );
  cout << "Events with 1 tracks: " << tr2->GetEntries() << endl;
  cout << "Events with Multitracks in 1 tracks: " << tr2eff->GetEntries() << endl;

  TH1F *g1 = new TH1F("g1","",500,0,2);
  TH1F *g2 = new TH1F("g2","",500,0,2);
  TH1F *g3 = new TH1F("g3","",500,0,2);
  TH1F *g4 = new TH1F("g4","",500,0,2);

    T->Draw(Form("EK%sx.x_bj>>g1",arm.Data()), totalrtig, "goff" );
    Double_t all = g1->GetEntries();
    cout << "All trigger = " << all << endl;

    T->Draw(Form("EK%sx.x_bj>>g2",arm.Data()), datacurrentcut + totalrtig + trig1 + trig2 + trig3 , "goff" );
    Double_t alltrig = g2->GetEntries();
    cout << "Trigger 2 = " << alltrig << endl;

    T->Draw(Form("EK%sx.x_bj>>g3",arm.Data()), datacurrentcut + totalrtig + trig1 + !trig2 + !trig3 , "goff" );
    Double_t onlytrig1 = g3->GetEntries();
    cout << "Only Trigger 1 = " << onlytrig1 << endl;

    T->Draw(Form("EK%sx.x_bj>>g4",arm.Data()), datacurrentcut + totalrtig + !trig1 + !trig2 + trig3 , "goff" );
    Double_t onlytrig3 = g4->GetEntries();
    cout << "Only Trigger 3 = " << onlytrig3 << endl;

    ofstream outfile;
    outfile.open ("cosmics.txt",ios::in|ios::app);
    outfile << setiosflags(ios::left) << setw(8) << run;
    outfile << setiosflags(ios::left) << setw(15) << datatime_beam;
    outfile << setiosflags(ios::left) << setw(15) << h1->GetEntries();
    outfile << setiosflags(ios::left) << setw(15) << h2->GetEntries();
    outfile << setiosflags(ios::left) << setw(15) << h3->GetEntries();
    outfile << setiosflags(ios::left) << setw(15) << tr1->GetEntries();
    outfile << setiosflags(ios::left) << setw(15) << tr1eff->GetEntries();
    outfile << setiosflags(ios::left) << setw(15) << tr2->GetEntries();
    outfile << setiosflags(ios::left) << setw(15) << tr2eff->GetEntries();
    outfile << setiosflags(ios::left) << setw(15) << all;
    outfile << setiosflags(ios::left) << setw(15) << alltrig;
    outfile << setiosflags(ios::left) << setw(15) << onlytrig1;
    outfile << setiosflags(ios::left) << setw(15) << onlytrig3;

    outfile << endl;
    outfile.close();


}
