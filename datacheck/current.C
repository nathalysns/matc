#include "../rootalias_spring2018.h"
#include "../HallA_style.h"

TChain *T;
TChain *ev;
TChain *E;

void current(Int_t run){

	HallA_style();
   //======Loading Run Numbers
    T = LoadRun(run,"T");
    E = LoadRun(run,"E");
    if(run>90000) ev = LoadRun(run,"evRight");
    else ev = LoadRun(run,"evLeft");
    if (!T) exit(1);

    TString arm = "L";

    if(run>90000){ 
    	arm = "R";
    }

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

    cout << "Current " << datacurrent << endl;


}
