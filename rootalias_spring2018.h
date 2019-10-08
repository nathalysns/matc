// 
// adapted from Ou,Longwu's GMp code
// -shujie 03,2018

#ifndef ROOTALIAS_H
#define ROOTALIAS_H


#include <string>
#include <stdio.h> 
#include <iomanip>
#include <locale>
#include <algorithm>
#include <array>
#include <vector>
#include "TSQLServer.h"
#include "TSQLResult.h"
#include "TSQLRow.h"
#include "TTree.h"
#include "TROOT.h"
#include "TStyle.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "TH1.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TLatex.h"
#include "TLeaf.h"
#include "TGraphErrors.h"
#include "TSystem.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TH2.h"
#include "TLine.h"
#include "TEllipse.h"
#include "TCut.h"
#include "TProfile.h"
#include "TFile.h"
#include "TEventList.h"
#include "TSpectrum.h"
#include <TString.h>

const char* PATHS[] = {

  "/Volumes/MOTI/leiqaa",
  "/Users/nathaly/Documents/rootfiles",
  
  //"/Users/nathalysantiesteban/Documents/nathaly",
 
  "/volatile/halla/triton/nathaly/Rootfiles",
  "/volatile/halla/triton/nathaly/Rootfiles/dectest",
  "/volatile/halla/triton/nathaly/Rootfiles/test",
  //"/volatile/halla/triton/nathaly/Rootfiles/reyoptics/", 
  //"/volatile/halla/triton/nathaly/Rootfiles/rightgmp/", 
  //"/volatile/halla/triton/nathaly/Rootfiles/december2017",
  //"/volatile/halla/triton/nathaly/Rootfiles/RHRSspring",
  "/volatile/halla/triton/nathaly",
  //"/volatile/halla/triton/nathaly", 
  "/Volumes/MOTI/spring",
  "/Volumes/MOTI/elastic_energy_analysis/rootfiles",
  0
};

const char* DBFILE[] = {
  "/work/halla/triton/nathaly/official/HallA-Online-Tritium/replay/DB",
  "/Users/nathalysantiesteban/Dropbox/analyzer_replay/Spring/official/HallA-Online-Tritium/replay/DB",
  0
};


struct target
{
  Double_t pos;
  TString name;
};


//=========bcm calibtration constants ==========//
//double I=13.;
const double protonmass = 0.93827231;

//========== Constants for the Spring Calibration =======//
Double_t g = 0.0003451;
Double_t o = -0.0016;//0.0127

const Double_t I_Cut = 2.;
Int_t bins = 150;
const Double_t vz = 0.2;
const Double_t cm2tonb = pow(10,-33);

double zmin, zmax;
double dnew_r, dnew, clock_counts;
Long64_t eventries;
Long64_t eventries2;
TString Lclk = "evLeftLclock/103700";
TString Rclk = "evRightLclock/103700";

const double NA= 6.022140857e23; //mol-1
const double pi=3.1415926535897932;
const double rad=pi/180.0;
//const double q=1.60217662e-13;// microcoulombs
const double q=6.242e12;

//-----------LHRS-----------------------------------------
const double beta_min_L=0.6;
const double sh_min_L=0.7;
const double sh_max_L=20;
const double sh_mineff_L=2;
const double cer_min_L=1500;
const double cer_max_L=30000;
const double cer_mineff_L=1500;
//=========Loose cuts =====================//
const double tg_ph_L_loose=0.05;
const double tg_th_L_loose=0.06;
const double tg_dp_L_loose=0.05;
//=========Tight cuts =====================//
/*const double tg_ph_L_tight=0.025;
const double tg_th_L_tight=0.035;
const double tg_dp_L_tight=0.035;*/
const double tg_ph_L_tight=0.03;
const double tg_th_L_tight=0.035;
const double tg_dp_L_tight=0.03;
//========= Target =====================//
const double tg_vz_L_tight=0.08;
const double tg_vz_L_loose=0.08;

TCut sh_cut_L=Form("((L.prl1.e+L.prl2.e)>L.tr.p[0]*1000*%g) && ((L.prl1.e+L.prl2.e)<L.tr.p[0]*1000*%g)",sh_min_L,sh_max_L);
TCut cer_cut_L=Form("L.cer.asum_c>%g && L.cer.asum_c<%g",cer_min_L, cer_max_L);

TCut cer_cut_Leff="(L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)<1.1 && (L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)>0.9";
TCut sh_cut_Leff="L.cer.asum_c>6000";

TCut track_L="L.tr.n==1";
TCut track_L0="L.tr.n==0";
TCut trigger_L = "DL.bit2>0";;
TCut trigger3_L = "DL.bit3>0";
TCut triggereff_L = "DL.bit1>0";

TCut dp_cut_L_loose = Form("fabs(L.tr.tg_dp)<%g",tg_dp_L_loose);
TCut th_cut_L_loose = Form("abs(L.tr.tg_th-0.002)<%g",tg_th_L_loose);
TCut ph_cut_L_loose = Form("fabs(L.tr.tg_ph)<%g",tg_ph_L_loose);
TCut z_cut_L_loose = Form("fabs(L.tr.vz)<%g",tg_vz_L_loose);
TCut z_cut_L_loose17 = Form("(L.tr.tg_y/sin(17.005*%g/180)+0.0115)<%g",pi,tg_vz_L_loose);
TCut z_cut_L_loose22 = Form("(L.tr.tg_y/sin(22.001*%g/180)+0.0115)<%g",pi,tg_vz_L_loose);

TCut dp_cut_L_tight =Form("fabs(L.tr.tg_dp)<%g",tg_dp_L_tight);
TCut th_cut_L_tight =Form("fabs(L.tr.tg_th)<%g",tg_th_L_tight);
TCut ph_cut_L_tight=Form("fabs(L.tr.tg_ph)<%g",tg_ph_L_tight);
TCut z_cut_L_tight=Form("fabs(L.tr.vz)<%g",tg_vz_L_tight);
TCut z_cut_L_tight17 = Form("(L.tr.tg_y/sin(17.005*%g/180)+0.0115)<%g",pi,tg_vz_L_tight);
TCut z_cut_L_tight22 = Form("(L.tr.tg_y/sin(22.001*%g/180)+0.0115)<%g",pi,tg_vz_L_tight);


TCut Ltotal_cut_loose = dp_cut_L_loose + th_cut_L_loose+ ph_cut_L_loose + sh_cut_L + cer_cut_L + track_L + trigger_L + z_cut_L_loose;
TCut Ltotal_cut_tight = dp_cut_L_tight + th_cut_L_tight + ph_cut_L_tight  + sh_cut_L + cer_cut_L + track_L + trigger_L + z_cut_L_tight;
TCut Ltotal_cut_loose17 = dp_cut_L_loose+ th_cut_L_loose+ ph_cut_L_loose + sh_cut_L + cer_cut_L + track_L + trigger_L + z_cut_L_loose17;
TCut Ltotal_cut_tight17 = dp_cut_L_tight + th_cut_L_tight + ph_cut_L_tight  + sh_cut_L + cer_cut_L + track_L + trigger_L + z_cut_L_tight17;
TCut Ltotal_cut_loose22 = dp_cut_L_loose+ th_cut_L_loose+ ph_cut_L_loose + sh_cut_L + cer_cut_L + track_L + trigger_L + z_cut_L_loose22;
TCut Ltotal_cut_tight22 = dp_cut_L_tight + th_cut_L_tight + ph_cut_L_tight  + sh_cut_L + cer_cut_L + track_L + trigger_L + z_cut_L_tight22;

TCut beta_cut_L=Form("L.tr.beta>%g",beta_min_L);
TCut trigger_2_L="DL.bit2>0";
TCut shower1 = "L.prl2.e>-L.prl1.e+2900 && L.prl2.e<-L.prl1.e+4500";
TCut aperture_L="((L.tr.tg_y+L.tr.tg_ph*1.5)^2/0.64+(L.tr.tg_th*1.5)^2/0.49)<0.01";

const double sh_adc_min_L=1400;
const double sh_adc_max_L=2300;


TCut trigger1_L = "(DL.evtypebits>>1)&1";
//TCut sh_adc_cut_Leff = Form("L.prl1.asum_c>-0.9*L.prl2.asum_c+%g && L.prl1.asum_c<-0.9*L.prl2.asum_c+%g",sh_adc_min_L,sh_adc_max_L);
TCut sh_adc_cut_Leffcer = "L.prl1.asum_c>-0.9*L.prl2.asum_c+300 && L.prl1.asum_c<-0.9*L.prl2.asum_c+4000";
TCut sh_adc_cut_Leff="L.prl1.asum_c>-0.9*L.prl2.asum_c+1000 && L.prl1.asum_c<-0.9*L.prl2.asum_c+5000";
TCut acc_cut_tightL = dp_cut_L_tight + th_cut_L_tight + ph_cut_L_tight;
TCut acc_cut_looseL = dp_cut_L_loose + th_cut_L_loose + ph_cut_L_loose;
TCut electron_cut_L = cer_cut_L+sh_cut_L+trigger_L;
TCut electron_cut_Ltrack = cer_cut_L+trigger_L+sh_adc_cut_Leff;


//--------------RHRS-------------------------------------

const double beta_min_R=0.6;
const double sh_min_R = 0.7;
const double sh_max_R = 20;
const double sh_mineff_R = 0.3;
const double cer_min_R=1500;
const double cer_max_R=30000;
const double cer_mineff_R=1000;
//=========Loose cuts =====================//
const double tg_ph_R_loose=0.05;
const double tg_th_R_loose=0.06;
const double tg_dp_R_loose=0.05;
//=========Tight cuts =====================//
const double tg_ph_R_tight=0.03;
const double tg_th_R_tight=0.035;
const double tg_dp_R_tight=0.03;

//========= Target =====================//
const double tg_vz_R_tight=0.08;
const double tg_vz_R_loose=0.08;


TCut sh_cut_R=Form("((R.ps.e+R.sh.e)>R.tr.p[0]*1000*%g) && ((R.ps.e+R.sh.e)<R.tr.p[0]*1000*%g)",sh_min_R,sh_max_R);
TCut sh_cut_Reff=Form("((R.ps.e+R.sh.e)>R.tr.p[0]*1000*%g) && ((R.ps.e+R.sh.e)<R.tr.p[0]*1000*%g)",sh_mineff_R,sh_max_R);
TCut cer_cut_R=Form("R.cer.asum_c>%g && R.cer.asum_c<%g",cer_min_R, cer_max_R);
TCut cer_cut_Reff=Form("R.cer.asum_c>%g && R.cer.asum_c<%g",cer_mineff_R, cer_max_R);
TCut track_R="R.tr.n==1";
TCut track_R_eff="R.tr.n>0";
TCut trigger4_R = "DR.bit4>0";
TCut trigger_R = "DR.bit5>0";
TCut trigger6_R = "DR.bit6>0";


TCut triggereff_R = "DR.bit4>0";

TCut dp_cut_R_loose = Form("fabs(R.tr.tg_dp)<%g",tg_dp_R_loose);
TCut th_cut_R_loose = Form("fabs(R.tr.tg_th-0.008)<%g",tg_th_R_loose);
TCut ph_cut_R_loose = Form("fabs(R.tr.tg_ph)<%g",tg_ph_R_loose);
TCut z_cut_R_loose = Form("fabs(R.tr.vz)<%g",tg_vz_R_loose);

TCut dp_cut_R_tight =Form("fabs(R.tr.tg_dp)<%g",tg_dp_R_tight);
TCut th_cut_R_tight =Form("fabs(R.tr.tg_th-0.008)<%g",tg_th_R_tight);
TCut ph_cut_R_tight=Form("fabs(R.tr.tg_ph)<%g",tg_ph_R_tight);
TCut z_cut_R_tight=Form("fabs(R.tr.vz)<%g",tg_vz_R_tight);


TCut Rtotal_cut_loose = dp_cut_R_loose+ th_cut_R_loose+ ph_cut_R_loose + sh_cut_R + cer_cut_R + track_R + trigger_R + z_cut_R_loose;
TCut Rtotal_cut_tight = dp_cut_R_tight + th_cut_R_tight + ph_cut_R_tight  + sh_cut_R + cer_cut_R + track_R + trigger_R + z_cut_R_tight;

TCut acc_cut_tightR = dp_cut_R_tight + th_cut_R_tight + ph_cut_R_tight;
TCut acc_cut_looseR = dp_cut_R_loose + th_cut_R_loose + ph_cut_R_loose;
TCut electron_cut_R = cer_cut_R + sh_cut_R +trigger_R;

// called by sort function to do descending sort
// bool wayToSort(int i, int j) { return i > j; }
// bool wayToSort(double i, double j) { return i > j; }
bool isGreater(double i, double j)
{
    return i > j;
}



// poisson function for TF1 fit
Double_t pois_fit(Double_t *x, Double_t *par)
{
   Double_t arg = 0;
  // par[1]-->normalization (y-axis), par[2]-->Lambda, par[0]=scale (x-axis)
   arg = x[0]*1.0/par[0];
   // Poisson=Power(par[1],x)/TMath::Gamma(x+1)/TMath::Exp(par[1])
   //        =prob. of occuring x times if the averg. event rate is par[2]
   // x[0]-->k
   Double_t fitval = par[1]*TMath::Poisson(arg,par[2]);
   //   cout<<fitval<<endl;
   return fitval;
}


//-------------------------------------------
//get target info from epics encoder position
// check if target moved during the run
// works for tritium snice 2018.1
//----------------------------------------- 
TString GetTarget(TChain *tree2, int run){

  //cout << run << endl;
  TString targname;
  
  target h3={33106235,"Tritium"};
  target d2={29367355,"Deuterium"};
  target h={25610043,"Hydrogen"};
  target he3={21875520,"Helium3"};
  target empty={18119995,"EmptyCell"};
  target dummy={15175217,"Dummy"};
  target optics={14394929,"Multifoils"};
  target hole={13108119,"Carbon Hole"};
  target raster={12444209,"Raster Target"};
  target al={11728945,"Thick Aluminum"};
  target single={11013681,"Single Carbon Foil"};
  target ti={10298417,"Titanium"};
  target beo={9583153,"BeO"};

  Double_t pos,pos1,i=0;
  
  tree2->SetBranchAddress("haBDSPOS",&pos);
  
  Int_t nn=tree2->GetEntries(); 
  
  for(i=0;i<nn;i++){
    tree2->GetEntry(i);     
    if(pos<0) continue;
    pos1=pos;
  }

  tree2->GetEntry(Int_t(nn-2)); 
  if (pos1!=pos) targname="unkown,target moved during the run"; 
  else if(fabs(pos)<= 0.000000001 ) {targname ="Unkown";}
  else if(fabs(pos)<50) targname="HOME";
  else if(fabs(pos-h3.pos)<20000)     targname=h3.name;
  else if(fabs(pos-d2.pos)<20000)     targname=d2.name;
  else if(fabs(pos-h.pos)<20000)      targname=h.name;
  else if(fabs(pos-he3.pos)<20000)    targname=he3.name;
  else if(fabs(pos-empty.pos)<20000)  targname=empty.name;
  else if(fabs(pos-dummy.pos)<50)  targname=dummy.name;
  else if(fabs(pos-optics.pos)<50) targname=optics.name;
  else if(fabs(pos-hole.pos)<50)   targname=hole.name;
  else if(fabs(pos-raster.pos)<50) targname=raster.name;
  else if(fabs(pos-al.pos)<50)     targname=al.name;
  else if(fabs(pos-single.pos)<50) targname=single.name;
  else if(fabs(pos-ti.pos)<50)     targname=ti.name;
  else if(fabs(pos-beo.pos)<50)    targname=beo.name;

  //cout<<pos<<"  "<<pos1<<"  "<<targname<<endl;
  return targname;
}

TString GetTargetfall(TChain *tree2, int run){

  //cout << run << endl;
  TString targname;

  target h3={32973114,"Tritium"};
  target d2={29234234,"Deuterium"};
  target h={25495354,"Hydrogen"};
  target he3={21756474,"Helium3"};
  target empty={18017594,"Empty Cell"};
  target dummy={15042096,"Dummy"};
  target optics={14241329,"Multifoils"};
  target hole={12954519,"Carbon Hole"};
  target raster={12290609,"Raster Target"};
  target al={11575345,"Thick Aluminum"};
  target single={10860081,"Single Carbon Foil"};
  target ti={10144817,"Titanium"};
  target beo={9429553,"BeO"};


  Double_t pos,pos1,i=0;
  
  tree2->SetBranchAddress("haBDSPOS",&pos);
  
  Int_t nn=tree2->GetEntries(); 
  
  for(i=0;i<nn;i++){
    tree2->GetEntry(i);     
    if(pos<0) continue;
    pos1=pos;
  }

  tree2->GetEntry(Int_t(nn-2)); 
  if (pos1!=pos) targname="unkown,target moved during the run"; 
  else if(fabs(pos)<= 0.000000001 ) {targname ="Unkown";}
  else if(fabs(pos)<50) targname="HOME";
  else if(fabs(pos-h3.pos)<20000)     targname=h3.name;
  else if(fabs(pos-d2.pos)<20000)     targname=d2.name;
  else if(fabs(pos-h.pos)<20000)      targname=h.name;
  else if(fabs(pos-he3.pos)<20000)    targname=he3.name;
  else if(fabs(pos-empty.pos)<20000)  targname=empty.name;
  else if(fabs(pos-dummy.pos)<50)  targname=dummy.name;
  else if(fabs(pos-optics.pos)<50) targname=optics.name;
  else if(fabs(pos-hole.pos)<50)   targname=hole.name;
  else if(fabs(pos-raster.pos)<50) targname=raster.name;
  else if(fabs(pos-al.pos)<50)     targname=al.name;
  else if(fabs(pos-single.pos)<50) targname=single.name;
  else if(fabs(pos-ti.pos)<50)     targname=ti.name;
  else if(fabs(pos-beo.pos)<50)    targname=beo.name;

  //cout<<pos<<"  "<<pos1<<"  "<<targname<<endl;
  return targname;
}



//--------------------------------

//--------------------------------

TChain* LoadRun(Int_t run, const char* path, const char* tree, Int_t debug)
{
    TChain* tt = new TChain(tree);

    TString basename = Form("tritium_%d",run);
    TString rootfile = basename + ".root";
    
    TString dir = path;
    if (!dir.EndsWith("/")) dir.Append("/");

    rootfile.Prepend(dir.Data());

    Long_t split = 0;

    while ( !gSystem->AccessPathName(rootfile.Data()) ) {
	   tt->Add(rootfile.Data());
	   //cout << "ROOT file " << rootfile << " added to " << tree<<" tree"<<endl;
	   split++;
	   rootfile = basename + "_" + split + ".root";
	   rootfile.Prepend(dir.Data());

    }

    if (split<=0) {
	   if (debug>0) {
      cerr << "Can not find ROOT file for run " << run << endl;
    }
	   delete tt;
      tt = 0;
    }

    return tt;
}

// Load TTree "tree" form all the ROOT files generated from a specific run
// The ROOT files are searched for from the given "PATHS" array given at the beginning of the file
//      run  --- run number
//      tree --- The name of the tree to be loaded
TChain* LoadRun(Int_t run, const char* tree = "T")
{
    Int_t i=0;

    TChain* tt = 0;
    while (PATHS[i]) {
	     tt = LoadRun(run,PATHS[i++],tree,0);
	     if (tt) break;
    }
   
    if (!tt){
        cerr << "Can not find ROOT file for run " << run << endl;
        return 0;
    }

    return tt;
}





//----------------------------
// Load online replay
//----------------------------


TChain* LoadOnline(Int_t run, const char* path, const char* tree,Int_t debug)
{
    TChain* tt = new TChain(tree);

    TString  basename = Form("tritium_online_%d",run);
    TString rootfile = basename + ".root";
    
    TString dir = path;
    if (!dir.EndsWith("/")) dir.Append("/");

    rootfile.Prepend(dir.Data());

    Long_t split = 0;

    while ( !gSystem->AccessPathName(rootfile.Data()) ) {
	tt->Add(rootfile.Data());
	cout << "ROOT file " << rootfile << " added to " << tree<<" tree"<<endl;
	split++;
	rootfile = basename + "_" + split + ".root";
	rootfile.Prepend(dir.Data());

    }

    if (split<=0) {
	if (debug>0) cerr << "Can not find online replay file for run " << run << endl;
	delete tt;
	tt = 0;
    }

    return tt;
}

TChain* LoadOnline(Int_t run, const char* tree = "T")
{
    Int_t i=0;

    TChain* tt = 0;
    while (PATHS[i]) {
	tt = LoadOnline(run,PATHS[i++],tree,1);

	if (tt) break;
    }
   
    if (!tt)
	cerr << "Can not find online replay file for run " << run << endl;

    return tt;
}


// Return PS of a given run
TArrayI GetPS(TTree* tt)
{
  //  TDatime run_time("2018-01-01 00:00:00");
 
    THaRun* run = 0;
    if (!tt->GetDirectory()) tt->LoadTree(0); // Necessary if T is a TChain
    TArrayI ps;
    TDirectory* fDir = tt->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
      ps = run->GetParameters()->GetPrescales();
      delete run;
    }

    return ps;
}

Int_t GetPS(TTree* tt,Int_t trigger)
{
  //  TDatime run_time("2018-01-01 00:00:00");

    THaRun* run = 0;
    Int_t ps;
    if (!tt->GetDirectory()) tt->LoadTree(0); // Necessary if T is a TChain
    TDirectory* fDir = tt->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
       ps = run->GetParameters()->GetPrescales()[trigger-1];
      delete run;
    }
    return ps;
}


TString GetTarget(Int_t run)
{
  TChain* etree=LoadRun(run,"E");
  if(!etree) etree=LoadOnline(run,"E");
  TString targname=GetTarget(etree, run);
  return targname;
  
}


// get rootfile path

TString GetPath(Int_t run)
{
    Int_t i=0;
    TString rootpath="unknown";

    TChain* T = 0;
    while (PATHS[i]) {
	T = LoadRun(run,PATHS[i++],"T",0);
	if (T) {
	 rootpath=PATHS[i-1];
	  return rootpath;
	}
    }

    if (!T) cerr << "Can not find ROOT file for run " << run << endl;

    return rootpath;
}

//=========Functions Nathaly ==================//

//=================================================================//
//=============== Cuts gor time with the current cut =============//
//=================================================================//
vector<Double_t> time_cut(int run, TChain *b1, double I){

  //===========chage constants for december and fall=====//
  
  if(run<1000){
  	g = 3.26e-04;
        o = 1.05e-01;//0.0127
  }
  //if((run>3704 && run<3954) || (run>93729 && run<94016)){
  if(run>93200 && run<94016){
  	g = 3.30e-04;
        o = -8.41e-02;//0.0127
  }
  if((run>3953 && run<4500) || (run>94015)){
        g = 3.25e-04;
        o = -1.59e-01;//0.0127
  }

 //==== needed branches =========================// 
  if(run>90000){
    b1->SetBranchAddress("evRightdnew_r",&dnew_r);
    b1->SetBranchAddress("evRightdnew", &dnew);  
    b1->SetBranchAddress("evRightLclock", &clock_counts);
  }else{
    b1->SetBranchAddress("evLeftdnew_r",&dnew_r);
    b1->SetBranchAddress("evLeftdnew", &dnew);  
    b1->SetBranchAddress("evLeftLclock", &clock_counts); 
  }  

  double cur, tim;
  std::vector <double> cup;
  std::vector <double> trip;
  double test, prev_cur, ttim, tcur;
  dnew_r = dnew = clock_counts =0;  
  test = prev_cur = ttim = tcur = cur = tim = 0;
  Long64_t nentries = b1->GetEntries();
  int time_wait = 10; //seconds
  for (int i=0; i<nentries; i++){
      b1->GetEntry(i);  
      cur = g*dnew_r+o; 
      tim = clock_counts/103700;
      if (cur >(I-I_Cut) && tcur<(I-I_Cut))test = tim;  
      if (cur >(I+I_Cut) && tcur<(I+I_Cut))test = tim; 
      if(cur>(I-I_Cut) && cur<(I+I_Cut) && (tim-test)>time_wait && (ttim-test)<time_wait) {cup.push_back(tim);}
      if((cur<(I-I_Cut) && tcur>(I-I_Cut))|| (cur>(I+I_Cut) && tcur<(I+I_Cut))) trip.push_back(ttim-1);
      if((i==(nentries-1) && cur>(I-I_Cut) && cur<(I+I_Cut))) trip.push_back(ttim); 
      tcur = cur;
      ttim = tim;
  }

  vector <double> t1;
  int n1 = cup.size(); int n2 = trip.size();
  int N;
  if(n1>n2){N = n1;}else{N=n2;}
  int k = 0;
  int z = 1;

  if(cup.size()!=0){

  t1.push_back(cup[0]);
  for(int i=0; i<N; i++){
       if(trip[i]>t1[k] && cup[z]>trip[i] && z<n1 ){ t1.push_back(trip[i]); k++;  if(z>n1){continue; } t1.push_back(cup[z]); z++; k++;}
        if(z==n1){
        if(t1.size()%2==0){cout << z << "  " << trip[i+1] << endl; t1.push_back(trip[i+1]); z++;}
        if(t1.size()%2!=0 && n2==1){t1.push_back(trip[i]); z++;}
        if(t1.size()%2!=0 &&  n2==n1 ){ t1.push_back(trip[i+1]); z++;}
        if(t1.size()%2!=0 && trip[i]<cup[z-1] && trip[i+1]>cup[z-1] ){ t1.push_back(trip[i+1]); z++;}}
    }
  }else{cout << "Not good beam in this run. " << endl;}
  return t1;
}


//=================================================================//
//================Charge Calculation ==============================//
//=================================================================//

tuple<double, double, double> charge_f(int run, TChain *b1, vector<double> t1, Double_t I){

  //===========chage constants for december and fall=====//

  if(run<1000){
    Double_t g = 3.26e-04;
    Double_t o = 1.05e-01;//0.0127
  }
  if((run>3704 && run<3954) || (run>93729 && run<94016)){
    Double_t g = 3.30e-04;
    Double_t o = -8.41e-02;//0.0127
  }
  if((run>3953 && run<4500) || (run>94015)){
    Double_t g = 3.25e-04;
    Double_t o = -1.59e-01;//0.0127
  }

  //=============== branches needed ===============================//
  if(run>90000){

    b1->SetBranchAddress("evRightLclock", &clock_counts);
    b1->SetBranchAddress("evRightdnew_r",&dnew_r);
    b1->SetBranchAddress("evRightdnew", &dnew);
  }else{
    b1->SetBranchAddress("evLeftdnew_r",&dnew_r);
    b1->SetBranchAddress("evLeftdnew", &dnew);  
    b1->SetBranchAddress("evLeftLclock", &clock_counts);
  }
  //============= Initialization of variables ======================//
  double current, charge;
  current=charge=0;
  double tim, ini, end, clkt, clk, clk_ini, clk_end, time_charge;
  tim = ini = end = clkt = clk_ini = clk_end = time_charge =0; 
  dnew_r = dnew = clock_counts = clk = 0; 
  Long64_t nentries = b1->GetEntries();
  int z =0;
  int counts= 0;
  //=============== Calculation ===================================//
  for(int i=0; i<nentries;i++){
    b1->GetEntry(i);
    clk = clock_counts;
    tim = clock_counts/103700;
    if (z<t1.size()){
      if (z%2==0 && tim>=t1[z] && clkt<t1[z]) {ini=dnew; clk_ini = tim; z++; }
      //if (z%2!=0 && tim>=t1[z] && clkt<t1[z]) {end = dnew; clk_end = tim; time_charge+=(clk_end-clk_ini); charge += (g*(end-ini)+(o*time_charge));  z++; } 
      if (z%2!=0 && tim>=t1[z] && clkt<t1[z]) {end = dnew; clk_end = tim; time_charge+=(clk_end-clk_ini); charge += g*dnew_r+o;  counts++; z++; } 
    }
    clkt = tim;
  }

  charge = charge/counts;
  return make_tuple(charge*time_charge, charge, time_charge);
}

//=================================================================//
//========================Livetime ================================//
//=================================================================//

tuple<Double_t, Double_t, Double_t, Double_t> livetime(Int_t run, TChain *b2, TChain *b3, vector<Double_t> t2, Double_t pres, TCut cur_cut){

  Long64_t nentries = b2->GetEntries();
  Double_t t2counts;
  Double_t max;
  TCut Trig; 
  if(run>90000) {
    b2->SetBranchAddress("evRightT5",&t2counts);
    b2->SetBranchAddress("evRightLclock", &clock_counts); 
    max = b3->GetMaximum("evRightLclock")/103700;
    Trig = "(DR.evtypebits>>5)&1";
    //Trig = "DR.bit5>0 &&";
  } else{
    b2->SetBranchAddress("evLeftT2",&t2counts);
    b2->SetBranchAddress("evLeftLclock", &clock_counts); 
    max = b3->GetMaximum("evLeftLclock")/103700;
    Trig = "(DL.evtypebits>>2)&1";
  } 
   
  Double_t tim, prevtim, t2ini, t2fin, prevt2counts, counts;
  tim = prevtim = t2ini = t2fin = prevt2counts = counts =0;  
  Int_t z=0;

  for (int i=0; i<nentries; i++){
    b2->GetEntry(i);
    tim = clock_counts/103700;
    if(tim>=t2[z] && prevtim<t2[z]) t2ini = t2counts;
    if(tim>t2[z+1] && prevtim<=t2[z+1]){ t2fin = t2counts; counts += (t2fin-t2ini); z+=2;}
    prevtim = tim;
    prevt2counts = t2counts;  
  }

  TH1F *X2 = new TH1F("X2","",20,0,10);
  if(run>90000){
    b3->Draw("DR.evtypebits>>X2", Trig + cur_cut,"goff");
    //counts = b2->GetMaximum("evRightT5");
    //b3->Draw("DR.evtypebits>>X2", Trig ,"goff");		
  } else b3->Draw("DL.evtypebits>>X2", Trig + cur_cut,"goff");
  Double_t mes = X2->GetEntries();
  Double_t LT = (pres*mes)/counts;
  Double_t LTer = sqrt((1/mes)+(1/counts))*LT;
  delete X2;
  return make_tuple(LT, mes, counts, LTer);
  
}

//========== boiling factor =============//

tuple<double, double> boiling(Int_t run, Double_t current, Double_t vzcut) {
TString target = GetTarget(run);
double a[4]={1.06e-4,1.036e-4,1.16e-4,1.70e-4};
double b[4]={-0.0068,-0.0051,-0.0067,-0.009};
double c[4]={1,1,1,1};
double thick[4]={85,53.37,142.15,70.8};//mg/cm2 in25 cm
double mass[4]={0.102,3.01e-5,3.2e-5,9.47e-6};//mg
double molar[4]={3.0160492,3.0160293,2.01410178,1.00794}; //g/mol
double B; //Boiling Factor
double L; //Luminosiy Factor

if(target=="Tritium"){
  B =(a[0]*current*current) + (b[0]*current) + c[0];
  L=(NA*thick[0]*vzcut/25)/((molar[0]*1000));}
else if (target=="Helium3"){
  B =(a[1]*current*current) + b[1]*current + c[1] ;
  L=(NA*thick[1]*vzcut/25)/((molar[1]*1000));}
else if (target=="Deuterium"){ B =(a[2]*current*current) + b[2]*current + c[2];
  L=(NA*thick[2]*vzcut/25)/((molar[2]*1000));}
else if (target=="Hydrogen"){ B =(a[3]*current*current) + b[3]*current + c[3];
 L=(NA*thick[3]*vzcut/25)/((molar[3]*1000));}
else {B=1; L=1;}
//cout << "from the rooot alias L: " << L <<endl;
return make_tuple(B,L);

}


//========== DB_run.dat read =============//

double dn_dat(int run, int dat){
  //TString DB_file= "/Users/nathalysantiesteban/Dropbox/Spring_Analysis/calibrations/energy/fromrootfiles/new_db_run.dat";
  TString DB_file="/work/halla/triton/nathaly/official/HallA-Online-Tritium/replay/DB/db_run.dat"; 
  //TString DB_file="/work/halla/triton/nathaly/Fall2018/replay/Fall2018/DB/db_run.dat"; 
  ifstream DB(DB_file);
  string line;
  
  int line_number = 0;
  if (DB.is_open())
  {
    while ( getline (DB,line) )
    {
      if (line.find(Form("run %i", run) ) != string::npos) break;
      line_number++;  
    }
  DB.close();
 }

 //========Information in the DB about the file (dat) ========//
 //==== 1 Energy, 2 angle, 3 momentum, 8 off x, 9 off y, 10 off z ========//

 string read_line;
 DB.open(DB_file);
 for (int lineno = 0; getline (DB,line) && lineno < line_number + dat +1; lineno++)
      if (lineno == line_number + dat ){
          read_line = line;
      }
  DB.close();

  stringstream ss(read_line);
  string string1; ss>>string1;
  string string2; ss>>string2;
  Double_t d1; ss >> d1;   
  return d1;
}

//============ Efficiencies=============//

struct Efficiencies {
  Double_t trackeff =  1.; 
  Double_t trigeff =  1.;
  Double_t trigeffer =  1.;
  Double_t sheff = 1.;
  Double_t sheffer = 1.;
  Double_t cereff = 1.; 
  Double_t cereffer = 1.; 
};

Efficiencies GetEfficiencies(TChain *T, TCut cut_cur, TCut zcut, TCut accut=acc_cut_tightL ){
Efficiencies  efficiencies;
//============ Track Efficiency ========================//
TH1F *track_hist = new TH1F("track_hist","", 11, -1, 10);
TH1F *trackeff_hist = new TH1F("trackeff_hist","", 11, -1, 10);
TH1F *track_hist0 = new TH1F("track_hist0","", 11, -1, 10);
TH1F *trackeff_hist0 = new TH1F("trackeff_hist0","", 11, -1, 10);

//==============Trigger Efficiency ==============================//
TH1F *trig_hist = new TH1F("trig_hist","", 100, -2, 2);
TH1F *trigeff_hist = new TH1F("trigeff_hist","", 100, -2, 2);
//==============Shower Efficiency ==============================//
TH1F *sh_hist = new TH1F("sh_hist","", 1000, 0, 2);
//==============Cerenkov Efficiency ==============================//
TH1F *cer_hist = new TH1F("cer_hist","", 1000, 0, 20000);
//============ Track Efficiency ========================//
//============ One track efficiency ========================//
T->Draw("L.tr.n>>track_hist",cut_cur + trigger_L + cer_cut_L + sh_adc_cut_Leff + dp_cut_L_loose + th_cut_L_loose + ph_cut_L_loose + track_L, "goff");
T->Draw("L.tr.n>>trackeff_hist",cut_cur + trigger_L + cer_cut_L + sh_adc_cut_Leff + dp_cut_L_loose + th_cut_L_loose + ph_cut_L_loose, "goff");
//============ Zero track inefficiency ========================//
T->Draw("L.tr.n>>track_hist0",cut_cur + trigger_L + cer_cut_L + sh_adc_cut_Leff + track_L0, "goff");
T->Draw("L.tr.n>>trackeff_hist0",cut_cur + trigger_L + cer_cut_L + sh_adc_cut_Leff, "goff");

//==============Trigger Efficiency ==============================//
TCut cherenkovtrig = "L.cer.asum_c>1000";
//TCut cherenkovtrig = "";
T->Draw("L.tr.tg_y>>trig_hist", cut_cur + trigger_L + track_L + accut + cherenkovtrig, "goff");
T->Draw("L.tr.tg_y>>trigeff_hist", cut_cur + triggereff_L + track_L + accut + cherenkovtrig, "goff");
//==============Shower Efficiency ==============================//
T->Draw("(L.prl1.e+L.prl2.e)/(L.tr.p[0]*1000)>>sh_hist",cut_cur + accut + trigger_L + track_L  + sh_cut_Leff, "goff");
//==============Cerenkov Efficiency ==============================//
T->Draw("L.cer.asum_c>>cer_hist",cut_cur+accut + trigger_L + track_L + cer_cut_Leff, "goff");
//============ Track Efficiency ========================//
Double_t tr = (track_hist->GetEntries()/trackeff_hist->GetEntries())*(1-track_hist0->GetEntries()/trackeff_hist0->GetEntries());


//==============Trigger Efficiency ==============================//
Double_t trigef = trig_hist->GetEntries()/trigeff_hist->GetEntries();
Double_t trigefer = trigef*sqrt(1/trig_hist->GetEntries()+1/trigeff_hist->GetEntries());


//==============Cerenkov Efficiency ==============================//
Int_t cerbmin = cer_hist->FindBin(1500); 
Int_t cerbmax = cer_hist->FindBin(15000);
Double_t ceref = cer_hist->Integral(cerbmin,cerbmax)/cer_hist->Integral(0,cerbmax);
Double_t cerefer = ceref*sqrt(1/cer_hist->Integral(cerbmin,cerbmax)+1/cer_hist->Integral(0,cerbmax));
//==============Shower Efficiency ==============================//
Int_t shbmin = sh_hist->FindBin(0.7); 
Int_t shbmax = sh_hist->FindBin(1.5); //in your case xmax=0.8
Double_t showeref = sh_hist->Integral(shbmin,shbmax)/sh_hist->Integral(0,shbmax);
Double_t showerefer = showeref*sqrt(1/sh_hist->Integral(shbmin,shbmax)+1/sh_hist->Integral(0,shbmax));


//============== Information ===================================//
efficiencies.trackeff=tr;  
efficiencies.trigeff=trigef;  
efficiencies.trigeffer=trigefer;
efficiencies.sheff=showeref;
efficiencies.sheffer=showerefer;    
efficiencies.cereff=ceref ; 
efficiencies.cereffer=cerefer ; 

delete track_hist; delete trackeff_hist; delete trig_hist; delete trigeff_hist; delete sh_hist;
delete cer_hist; delete track_hist0; delete trackeff_hist0;
return efficiencies;
}

struct RunInformation{
  TString targ = "Unknown"; 
  vector<Double_t> timevalues;
  Double_t charge = 0.;
  Double_t current = 0.;
  Double_t time_beam = 0.;
  Double_t boiling = 0.;
  Double_t luminosity = 0.;
  TCut Current_cut = "";
};

RunInformation GetRunInformation(Int_t run, TChain *T, TChain *E, TChain *ev, Double_t I=21.5){
//if(run==891 || run ==93987 || run ==93995) I=22.;
if(run>932 && run<948 ) I=10.;


RunInformation  runinformation;

//========Time cut of good beam ==============//
vector<Double_t> test = time_cut(run,ev,I);
//cout << test.size() << endl;
//if (test.size()==0) exit(1);
//======= Charge Calculation =================//
//=== Units Current = uA ======//
//=== Units Charge  = uC ======//
//=== Units time    = s  ======//
Double_t charg, curr, t_b;
tie(charg, curr, t_b) = charge_f(run, ev, test, I);
//========= Boiling ===========================//
// === Units Boiling (no units) ====//
// === Units Lum = cm-2 =====//
// === Units LumInt = cm-2 =====//
Double_t B, L;
tie(B, L) = boiling(run, curr, 2*100*tg_vz_L_tight);
//cout << "charge in loop" << charg << endl;
//Double_t LumInt = L*charg*q;
Double_t LumInt = L;
//cout << charg << endl;
//cout << q << endl;
//cout << "From other loop; .... " << LumInt << endl;
//========Time Cut============================//

dnew_r = dnew = clock_counts =0;
TString cut_t = "(";
int t = (int) test.size();
for(int i=0;i<t/2; i++){
    if(run>90000) cut_t = cut_t + Form("(%s>%f && %s<%f)", Rclk.Data(),test[2*i],Rclk.Data(),test[2*i+1]);
    else cut_t = cut_t + Form("(%s>%f && %s<%f)", Lclk.Data(),test[2*i],Lclk.Data(),test[2*i+1]);
    if(i!=(t/2-1)){cut_t = cut_t + " || ";}
    else if (i==(t/2-1)){cut_t += ")";} 
}
TCut cut_cur = Form("%s", cut_t.Data());


if(run<3500 || (run>93000 && run<93200)  ){runinformation.targ=GetTarget(E, run);}
else{runinformation.targ=GetTargetfall(E, run);}
runinformation.timevalues = test;
runinformation.charge = charg;
runinformation.current = curr;
runinformation.time_beam = t_b;
runinformation.boiling = B;
runinformation.luminosity = LumInt;
runinformation.Current_cut = cut_cur;


return runinformation;

}



#endif
