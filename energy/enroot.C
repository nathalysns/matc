#include "/work/halla/triton/nathaly/matc/rootalias_spring2018.h"
#include "/work/halla/triton/nathaly/matc/HallA_style.h"

TString arm;
TString armHRS;
TString bcm = "dnew";
Double_t bcm_gain = 0.0003485;
Double_t bcm_offset = 0.0127;
TChain *T;
TChain *E;

Double_t rightruns[105] = {93027, 93028, 93029, 93031, 93032, 93042, 93043, 93044, 93045, 93046, 
93047, 93048, 93049, 93050, 93051, 93052, 93053, 93054, 93055, 93056, 
93057, 93058, 93059, 93060, 93061, 93062, 93063, 93064, 93065, 93067, 
93068, 93069, 93070, 93071, 93072, 93073, 93074, 93075, 93076, 93077, 
93078, 93079, 93080, 93081, 93082, 93084, 93085, 93086, 93087, 93088, 
93089, 93090, 93091, 93092, 93093, 93094, 93095, 93096, 93097, 93098, 
93099, 93100, 93101, 93102, 93103, 93104, 93105, 93106, 93107, 93108, 
93109, 93110, 93111, 93112, 93113, 93114, 93115, 93116, 93117, 93118, 
93119, 93120, 93121, 93122, 93123, 93126, 93127, 93130, 93131, 93132, 
93133, 93134, 93135, 93136, 93137, 93138, 93139, 93140, 93141, 93142, 
93143, 93144, 93145, 93147, 93148};

Double_t leftruns[133] = {3018, 3020, 3023, 3024, 3028, 3031, 3042, 3043, 3051, 3052, 3053, 3054, 
3055, 3057, 3058, 3059, 3060, 3061, 3062, 3063, 3064, 3065, 3067, 3068, 3069, 3070, 
3071, 3072, 3073, 3074, 3075, 3076, 3077, 3078, 3079, 3080, 3081, 3082, 
3084, 3085, 3088, 3089, 3090, 3091, 3092, 3093, 3094, 3095, 3096, 3097, 
3099, 3101, 3102, 3103, 3104, 3105, 3106, 3107, 3108, 3110, 3111, 3112, 
3113, 3114, 3115, 3116, 3117, 3118, 3120, 3121, 3122, 3123, 3124, 3125, 
3126, 3127, 3128, 3129, 3130, 3131, 3132, 3133, 3134, 3135, 3136, 3137, 
3138, 3139, 3140, 3141, 3142, 3143, 3144, 3145, 3146, 3147, 3148, 3149, 
3150, 3152, 3153, 3154, 3155, 3156, 3157, 3158, 3159, 3160, 3161, 3162, 
3163, 3164, 3166, 3167, 3168, 3170, 3171, 3172, 3173, 3174, 3175, 3176, 
3177, 3178, 3179, 3180, 3181, 3182, 3183, 3184, 3185, 3187, 3188};

ofstream outfile; 
TH1F *hist = new TH1F("hist","Beam Energy (MeV)", 100, 2221,2223);

int in_array(std::vector<double> vect, double value){
	for(Int_t j=0; j < vect.size(); j++){
		if(vect[j]==value){
		      return 1;
		}
	}
	return 0;
}



std::vector<double> energ;


void enroot(){

int run;
//double cf = 1.002;
double cf = 1.00;
HallA_style();

outfile.open("Run_Energy.dat");
hist->GetXaxis()->SetTitle("Energy (MeV)");

//for(int x =93027; x<93149; x++){
//for(int x =93465; x<94104; x++){
//for(int x =3000; x<3190; x++){
for(int x =830; x<940; x++){

//run = rightruns[x];
run =x;
E = LoadRun(run,"E");

if (!E){
	cout<<"There is not run number: " << run << endl;
	continue;
}


if(run>90000){
	arm = "L";
	armHRS = "Left";
}else{
	arm = "R";
	armHRS = "Right";
}



TString dnewfreq = "ev"+armHRS+bcm+"_r";
TString energy = "HALLA_p";
TString ep_cur_av = "hac_bcm_average";
TCut epics_cur_av = "hac_bcm_average>5";

E->SetBranchStatus("*",0);
E->SetBranchStatus(energy,1);
E->SetBranchStatus(ep_cur_av,1);

Int_t entries = E->GetEntries();



Double_t ener, ener_av, cur;

E->SetBranchAddress("HALLA_p", &ener);
E->SetBranchAddress("hac_bcm_average", &cur);
int count = 0; 

for(int i=0; i<entries; i++){
	E->GetEntry(i);
	if(ener>1 && cur>5){
		if(energ.size()==0){ energ.push_back(ener);} 
		if(in_array(energ,ener)==0){energ.push_back(ener);}
		count++;
	}
}

cout << "=========vector =======" << endl;
ener_av = 0;
int count2 =0;
int check = 0;

cout << " ============================== Test ========================================" << endl;

if(energ.size()>0){

for(int i=0; i<energ.size(); i++){
	cout << energ [i] << endl;
}

cout << energ[0] << endl;


for(int i=0; i<energ.size(); i++){
	for(int j=0; j<entries; j++){
		E->GetEntry(j);
		if(energ[i]==ener && cur>5 ){count2++;}	
	}
	ener_av+=(count2*energ[i]);

	check+=count2;
	count2 =0;
}

ener_av /= check;
if(check==0) ener_av = energ[0];
cout << "Number of Entries: " << check << " Counts: " << entries << endl;
cout << "Average Energy: " << cf*ener_av << endl;

if(ener_av < 100){ ener_av = 0;}
 
//TH1D*HallEner = new TH1D("HallEner", "", 1500, 2215, 2225);
//E->Draw(energy+">>HallEner", epics_cur_av, "goff");

//Double_t Energy = 0;
//int bin = HallEner->GetMaximumBin();
//Energy  = HallEner->GetXaxis()->GetBinCenter(bin);


}
outfile << setiosflags(ios::left) << setw(20) << run;
outfile << setiosflags(ios::left) << setw(20) << setprecision(8) << cf*ener_av << endl;


hist->Fill(cf*ener_av);
//delete HallEner;
delete E;
energ.clear();
}

outfile.close();

//hist->Draw();

}

