#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TString arm;
TString armHRS;
TChain *T;
TChain *E;
TChain *ev;

void cosmics(Int_t run){

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

	TCanvas *c1 = new TCanvas("c1","",500,500);
	if(run<90000) T->Draw("evLeftdnew_r:evLeftLclock/103700", datacurrentcut,"*");
	else T->Draw("evRightdnew_r:evRightLclock/103700", datacurrentcut,"*");

}