#include "../rootalias_spring2018.h"
#include "../HallA_style.h"
#include "../extrafunctions.h"

const Int_t      Bin     = 150;
const Int_t      xBin    = 100;

double tg_dp_l=-tg_dp_L_loose;
double tg_dp_u=tg_dp_L_loose;
double tg_th_l=-tg_th_L_loose;
double tg_th_u=tg_th_L_loose; 
double tg_ph_l=-tg_ph_L_loose;
double tg_ph_u=tg_ph_L_loose;
double tg_z_l=-tg_vz_L_loose;
double tg_z_u=tg_vz_L_loose;
string dir= "plots/loose/";

TString target_data = "Unknown";
TString arm = "L";

//========== Histograms ===============================//
const double   dpmin  = -0.08;
const double   dpmax  = 0.08; 
const double   th_min = -0.08; 
const double   th_max = 0.08;
const double   ph_min = -0.05;
const double   ph_max = 0.05; 
const double   ymin   = -0.15;
const double   ymax   = 0.15;
const double   xbjmin = 0.;
const double   xbjmax = 2.;
const double   Emin    = 0;
const double   Emax    = 2;
const Int_t   enbins    = 200;
TLegend *leg2 = new TLegend(0.7,0.65,0.95,0.99);
//Int_t enbins = (Emax-Emin)/0.008;

Int_t c=1;

void test( Int_t run = 3116, Int_t targ = 3, Int_t type_cuts = 1)  {

//=========== Data ====================================//
TH1F *data_dpfinal;
TH1F *data_thfinal;  
TH1F *data_phfinal;  
TH1F *data_yfinal;
TH1F *data_xfinal;
TH1F *data_xfinalev;    
TH1F *data_enfinal;


if(type_cuts==1){
	tg_dp_l=-tg_dp_L_tight;
	tg_dp_u=tg_dp_L_tight;
	tg_th_l=-tg_th_L_tight;
	tg_th_u=tg_th_L_tight; 
	tg_ph_l=-tg_ph_L_tight;
	tg_ph_u=tg_ph_L_tight;
	tg_z_l=-tg_vz_L_tight;
	tg_z_u= tg_vz_L_tight;
	dir= "plots/tight/";
}

//====================  Data File ================================//

double angle = 0;

Double_t lummi = 0;
TString gastar ="";

cout << "Run number: " << run << endl;

//=========== Data ====================================//
TH1F *data_dp = new TH1F("data_dp", "", Bin, dpmin, dpmax);
TH1F *data_th = new TH1F("data_th", "", Bin, th_min, th_max);
TH1F *data_ph = new TH1F("data_ph", "", Bin, ph_min, ph_max);
TH1F *data_y  = new TH1F( "data_y", "", Bin, ymin, ymax);
TH1F *data_x  = new TH1F("data_x",  "",xBin, xbjmin, xbjmax);
TH1F *data_en = new TH1F("data_en", "", enbins, Emin, Emax);

//======Left or Right Arm
if (run>90000) arm = "R";
//======Loading Run Numbers
TChain *T = LoadRun(run,"T");
TChain *E = LoadRun(run,"E");
TChain *ev;
if(run>90000) ev = LoadRun(run,"evRight");
else ev = LoadRun(run,"evLeft");
if (!T) exit(1);




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

Double_t tempdataLumInt = databoiling; // convert to nb
gastar = target_data.Data();

cout << "Target: " << runinformation.targ << endl;
cout << "Current: " << datacurrent << " uA Time with on beam: " << datatime_beam << " s Total Charge: " << datacharge << " uC " << endl; 

//========= Prescale Factor ===========================//
Int_t ps;
if(run>90000) ps  = GetPS(T,5);
else ps  = GetPS(T,2);

//===================== cuts ===============================================//

TCut beta = "L.tr.beta>0.7 && L.tr.beta<1.5";
TCut shtest = "";
TString sht1 = "";
Double_t  m, a1, a2, c1, c2; 
m = a1 = a2 = c1 = c2 = 0; 
angle = dn_dat(run,2)*pi/180;
TCut data_cut  = acc_cut_tightL + electron_cut_L + track_L + datacurrentcut;
TCut zcut = z_cut_L_tight;

if(type_cuts!=1) data_cut  = acc_cut_looseL + electron_cut_L + track_L + datacurrentcut;

if(run>90000){
 beta = "R.tr.beta>0.7 && R.tr.beta<1.5";
 sht1 = "(R.sh.e+R.ps.e)>((%f*(R.tr.p[0]*1000))-%f) && (R.sh.e+R.ps.e)<((%f*(R.tr.p[0]*1000))-%f) && (R.tr.p[0]*1000)>%f &&(R.tr.p[0]*1000)<%f ";
 //
 m=1.41;
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

zcut = z_cut_R_tight;
data_cut  = acc_cut_tightR + electron_cut_R + track_R + datacurrentcut + shtest + beta;
if(type_cuts!=1) data_cut  = acc_cut_looseR + electron_cut_R + track_R + datacurrentcut + shtest + beta;	
}

T->Draw(Form("%s.tr.tg_ph>>data_ph", arm.Data()), data_cut + zcut, "goff");
T->Draw(Form("%s.tr.tg_th>>data_th", arm.Data()), data_cut + zcut, "goff");
T->Draw(Form("%s.tr.tg_dp>>data_dp", arm.Data()), data_cut + zcut, "goff");
T->Draw(Form("%s.tr.tg_y>>data_y", arm.Data()), data_cut, "goff");
T->Draw(Form("EK%sxe.omega>>data_en",arm.Data()), data_cut + zcut, "goff");
T->Draw(Form("EK%sxe.x_bj>>data_x",arm.Data()),  data_cut + zcut, "goff");

TCanvas *c1 = new TCanvas("c1","c1",1200,1200); 
c1->Divide(2,2);
HallA_style();

c1->cd(1);
data_ph->SetLineColor(4);
data_ph->SetLineWidth(3);
data_ph->SetTitle("; d#phi;");//" /#muC ");
data_ph->Draw();
c1->cd(2);
data_th->SetLineColor(4);
data_th->SetLineWidth(3);
data_th->SetTitle("; d#theta;");//" /#muC ");
data_th->Draw();
c1->cd(3);
data_dp->SetLineColor(4);
data_dp->SetLineWidth(3);
data_dp->SetTitle("; dp;");//" /#muC ");
data_dp->Draw();
c1->cd(4);
data_y->SetLineColor(4);
data_y->SetLineWidth(3);
data_y->SetTitle("; y;");//" /#muC ");
data_y->Draw();

TCanvas *c2 = new TCanvas("c2","c2",1200,1200); 
c2->Divide(1,2);
c2->cd(1);
data_en->SetLineColor(4);
data_en->SetLineWidth(3);
data_en->SetTitle("; #omega;");//" /#muC ");
data_en->Draw();
c2->cd(2);
data_x->SetLineColor(4);
data_x->SetLineWidth(3);
data_x->SetTitle("; x_{bj};");//" /#muC ");
data_x->Draw();

c1->SaveAs(Form("plotsloose/target_%i.pdf",run));
c2->SaveAs(Form("plotsloose/phys_%i.pdf",run));
//=========Number of Events ======
double w, T_y, electrons, ratio;
T_y = 0;
electrons = 0;
ratio=0;


ofstream outfile ; 
outfile.open("testt1.txt",ios::out|ios::app);

outfile << setiosflags(ios::left) << setw(20) << "Run" ;
outfile << setiosflags(ios::left) << setw(20) << run ;
outfile << setiosflags(ios::left) << setw(20) << " Data " << endl;

outfile << setiosflags(ios::left) << setw(20) <<  run;
outfile << setiosflags(ios::left) << setw(20) << " PS " ;
outfile << setiosflags(ios::left) << setw(20) << ps;
outfile << setiosflags(ios::left) << setw(20) << " charge " ;
outfile << setiosflags(ios::left) << setw(20) << datacharge << endl;

//====================phi
outfile << setiosflags(ios::left) << setw(20) <<  run;
outfile << setiosflags(ios::left) << setw(20) << " phi " ;
for (Int_t j=0; j<Bin; j++){
	w = data_ph->GetBinCenter(j);
	ratio =  data_ph->GetBinContent(j);
//	if(ratio>0.){
		outfile << setiosflags(ios::left) << setw(20) << w;
		outfile << setiosflags(ios::left) << setw(20) << ratio;
//	}	
}
outfile << endl;

//====================theta
outfile << setiosflags(ios::left) << setw(20) <<  run;
outfile << setiosflags(ios::left) << setw(20) << " theta " ;
for (Int_t j=0; j<Bin; j++){
	w = data_th->GetBinCenter(j);
	ratio =  data_th->GetBinContent(j);
//	if(ratio>0.){
		outfile << setiosflags(ios::left) << setw(20) << w;
		outfile << setiosflags(ios::left) << setw(20) << ratio;
//	}	
}
outfile << endl;

//====================dp
outfile << setiosflags(ios::left) << setw(20) <<  run;
outfile << setiosflags(ios::left) << setw(20) << " dp " ;
for (Int_t j=0; j<Bin; j++){
	w = data_dp->GetBinCenter(j);
	ratio =  data_dp->GetBinContent(j);
//	if(ratio>0.){
		outfile << setiosflags(ios::left) << setw(20) << w;
		outfile << setiosflags(ios::left) << setw(20) << ratio;
//	}	
}
outfile << endl;

//====================y
outfile << setiosflags(ios::left) << setw(20) <<  run;
outfile << setiosflags(ios::left) << setw(20) << " y " ;
for (Int_t j=0; j<Bin; j++){
	w = data_y->GetBinCenter(j);
	ratio =  data_y->GetBinContent(j);
//	if(ratio>0.){
		outfile << setiosflags(ios::left) << setw(20) << w;
		outfile << setiosflags(ios::left) << setw(20) << ratio;
//	}	
}
outfile << endl;

//====================omega
outfile << setiosflags(ios::left) << setw(20) <<  run;
outfile << setiosflags(ios::left) << setw(20) << " omega " ;
for (Int_t j=0; j<enbins; j++){
	w = data_en->GetBinCenter(j);
	ratio =  data_en->GetBinContent(j);
//	if(ratio>0.){
		outfile << setiosflags(ios::left) << setw(20) << w;
		outfile << setiosflags(ios::left) << setw(20) << ratio;
//	}	
}
outfile << endl;

//====================x_bj
outfile << setiosflags(ios::left) << setw(20) <<  run;
outfile << setiosflags(ios::left) << setw(20) << " xbj " ;
for (Int_t j=0; j<xBin; j++){
	w = data_x->GetBinCenter(j);
	ratio =  data_x->GetBinContent(j);
//	if(ratio>0.){
		outfile << setiosflags(ios::left) << setw(20) << w;
		outfile << setiosflags(ios::left) << setw(20) << ratio;
//	}	
}
outfile << endl;

}
