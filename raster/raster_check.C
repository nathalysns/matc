#include "../rootalias_spring2018.h"
#include "../HallA_style.h"




void raster_check(Int_t run=3171, TString target="Tritium"){

HallA_style();

TChain *T = LoadRun(run,"T");
TChain *E = LoadRun(run,"E");
TChain *ev;

//=================================================//
if(run>90000){ev= LoadRun(run,"evRight");}
else{ev= LoadRun(run,"evLeft");}
//=================================================//
TCut totalcut = sh_cut_L + cer_cut_L + track_L;
TString arm = "L";
if(run>90000){ totalcut = sh_cut_R + cer_cut_R + track_R; arm = "R";}

//=================================================//

Double_t rx_min = (T->GetMinimum(Form("%srb.x",arm.Data()))-0.001)*1000;
Double_t rx_max = (T->GetMaximum(Form("%srb.x",arm.Data()))+0.001)*1000;
Double_t ry_min = (T->GetMinimum(Form("%srb.y",arm.Data()))-0.001)*1000;
Double_t ry_max = (T->GetMaximum(Form("%srb.y",arm.Data()))+0.001)*1000;
Double_t Wmin = 0.92;
Double_t Wmax = 0.95;

Double_t rasterxcur_min = T->GetMinimum(Form("%srb.Raster.rawcur.x",arm.Data()))-3000;
Double_t rasterxcur_max = T->GetMaximum(Form("%srb.Raster.rawcur.x",arm.Data()))+3000;
Double_t raster2xcur_min = T->GetMinimum(Form("%srb.Raster2.rawcur.x",arm.Data()))-3000;
Double_t raster2xcur_max = T->GetMaximum(Form("%srb.Raster2.rawcur.x",arm.Data()))+3000;
Double_t rasterycur_min = T->GetMinimum(Form("%srb.Raster.rawcur.y",arm.Data()))-3000;
Double_t rasterycur_max = T->GetMaximum(Form("%srb.Raster.rawcur.y",arm.Data()))+3000;
Double_t raster2ycur_min = T->GetMinimum(Form("%srb.Raster2.rawcur.y",arm.Data()))-3000;
Double_t raster2ycur_max = T->GetMaximum(Form("%srb.Raster2.rawcur.y",arm.Data()))+3000;


Double_t bpmxmin = (T->GetMinimum(Form("%srb.BPMB.x",arm.Data()))-2.5);
Double_t bpmxmax = (T->GetMaximum(Form("%srb.BPMB.x",arm.Data())));
Double_t bpmymin = (T->GetMinimum(Form("%srb.BPMB.y",arm.Data())));
Double_t bpmymax = (T->GetMaximum(Form("%srb.BPMB.y",arm.Data()))+3);

cout << bpmxmin << "   " << bpmxmax << endl;
cout << bpmymin << "   " << bpmymax << endl;

Double_t rasterxmin = (T->GetMinimum(Form("%srb.Raster2.target.x",arm.Data()))-0.001)*1000;
Double_t rasterxmax = (T->GetMaximum(Form("%srb.Raster2.target.x",arm.Data()))+0.001)*1000;
Double_t rasterymin = (T->GetMinimum(Form("%srb.Raster2.target.y",arm.Data()))-0.001)*1000;
Double_t rasterymax = (T->GetMaximum(Form("%srb.Raster2.target.y",arm.Data()))+0.001)*1000;

//=================================================//
TString target_data = "Unknown";
RunInformation  runinformation   = GetRunInformation(run, T, E, ev, 22.);
target_data = runinformation.targ;

if(target_data == "Unknown") target_data = target;
//=================================================//

auto* legend = new TLegend(0.12, 0.75, .23, .88);
legend->AddEntry((TObject*)0, "", "");
legend->AddEntry((TObject*)0, Form("Run %i", run), "");
legend->AddEntry((TObject*)0, Form("Taget %s", target_data.Data()), "");
legend->AddEntry((TObject*)0, "", "");

//=================================================//
TCanvas* c1 = new TCanvas("c1","",800,800);
TH2F *rbx_y = new TH2F("rbx_y","", 200,rx_min,rx_max,200,ry_min,ry_max); rbx_y->SetTitle(Form(";%srb.x (mm); %srb.y (mm)",arm.Data(),arm.Data()));
TH2F *Wrby = new TH2F("Wrby","", 200,ry_min,ry_max,200,Wmin,Wmax); Wrby->SetTitle(Form(";%srb.y (mm); W(GeV) ",arm.Data()));
TH2F *Wrbx = new TH2F("Wrbx","", 200,rx_min,rx_max,200,Wmin,Wmax); Wrbx->SetTitle(Form(";%srb.x (mm); W(GeV) ",arm.Data()));
T->Draw(Form("%srb.y*1000:%srb.x*1000>>rbx_y",arm.Data(),arm.Data()) ,"","goff");
T->Draw(Form("sqrt(EK%sx.W2):%srb.x*1000>>Wrbx",arm.Data(),arm.Data()),totalcut,"goff");
T->Draw(Form("sqrt(EK%sx.W2):%srb.y*1000>>Wrby",arm.Data(),arm.Data()),totalcut,"goff");
rbx_y->Draw("colz");
legend->Draw();

if(target_data=="Hydrogen"){
TCanvas* t1 = new TCanvas("t1","",1000,250);
t1->Divide(2,1); t1->cd(1);
t1->cd(1);
Wrbx->Draw("colz");
legend->Draw();
t1->cd(2);
Wrby->Draw("colz");
t1->SaveAs(Form("./plots/%i_W.pdf",run));
}


//=================================================//
TCanvas* c2 = new TCanvas("c2","",1000,1000);
c2->Divide(2,2);
TH2F *bpmxx = new TH2F("bpmxx","", 200,bpmxmin,bpmxmax,200,rasterxmin,rasterxmax);bpmxx->SetTitle(";BPM X target (mm); Raster X target (mm)");
TH2F *bpmxy = new TH2F("bpmxy","", 200,bpmxmin,bpmxmax,200,rasterymin,rasterymax);bpmxy->SetTitle(";BPM X target (mm); Raster Y target (mm)");
TH2F *bpmyx = new TH2F("bpmyx","", 200,bpmymin,bpmymax,200,rasterxmin,rasterxmax);bpmyx->SetTitle(";BPM Y target (mm); Raster X target (mm)");
TH2F *bpmyy = new TH2F("bpmyy","", 200,bpmymin,bpmymax,200,rasterymin,rasterymax);bpmyy->SetTitle(";BPM Y target (mm); Raster Y target (mm)");

c2->cd(1);
T->Draw(Form("%srb.Raster2.target.x*1000:%srb.BPMB.x*1000>>bpmxx",arm.Data(),arm.Data()) ,"","colz");
legend->Draw();
c2->cd(2);
T->Draw(Form("%srb.Raster2.target.y*1000:%srb.BPMB.x*1000>>bpmxy",arm.Data(),arm.Data()) ,"","colz");
c2->cd(3);
T->Draw(Form("%srb.Raster2.target.x*1000:%srb.BPMB.y*1000>>bpmyx",arm.Data(),arm.Data()) ,"","colz");
c2->cd(4);
T->Draw(Form("%srb.Raster2.target.y*1000:%srb.BPMB.y*1000>>bpmyy",arm.Data(),arm.Data()) ,"","colz");

//=================================================//
TCanvas* c3 = new TCanvas("c3","",1500,1200);
c3->Divide(2,2);
TH2F *rasteryx = new TH2F("rasteryx","", 200,rasterxcur_min,rasterxcur_max,200,rasterycur_min,rasterycur_max);rasteryx->SetTitle(";Raster 1 X Current (ADC Channel); Raster 1 Y Current (ADC Channel)");
TH2F *rasteryx2 = new TH2F("rasteryx2","", 200,raster2xcur_min,raster2xcur_max,200,rasterycur_min,rasterycur_max);rasteryx2->SetTitle(";Raster 2 X Current (ADC Channel); Raster 1 Y Current (ADC Channel)");
TH2F *rasterxy = new TH2F("rasterxy","", 200,rasterxcur_min,rasterxcur_max,200,raster2ycur_min,raster2ycur_max);rasterxy->SetTitle(";Raster 1 X Current (ADC Channel); Raster 2 Y Current (ADC Channel)");
TH2F *raster2yx = new TH2F("raster2yx","", 200,raster2xcur_min,raster2xcur_max,200,raster2ycur_min,raster2ycur_max);raster2yx->SetTitle(";Raster 2 X Current (ADC Channel); Raster 2 Y Current (ADC Channel)");

c3->cd(1);
T->Draw(Form("%srb.Raster.rawcur.y:%srb.Raster.rawcur.x>>rasteryx",arm.Data(),arm.Data()) ,"","colz");
legend->Draw();
c3->cd(2);
T->Draw(Form("%srb.Raster.rawcur.y:%srb.Raster2.rawcur.x>>rasteryx2",arm.Data(),arm.Data()) ,"","colz");
c3->cd(3);
T->Draw(Form("%srb.Raster2.rawcur.y:%srb.Raster.rawcur.x>>rasterxy",arm.Data(),arm.Data()) ,"","colz");
c3->cd(4);
T->Draw(Form("%srb.Raster2.rawcur.y:%srb.Raster2.rawcur.x>>raster2yx",arm.Data(),arm.Data()) ,"","colz");
//=================================================//
TCanvas* c4 = new TCanvas("c4","",1000,250);
TH2F *rasterxx = new TH2F("rasterxx","", 200,rasterxcur_min,rasterxcur_max,200,raster2xcur_min,raster2xcur_max);rasterxx->SetTitle(";Raster 1 X Current (ADC Channel); Raster 2 X Current (ADC Channel)");
TH2F *rasteryy = new TH2F("rasteryy","", 200,rasterycur_min,rasterycur_max,200,raster2ycur_min,raster2ycur_max);rasteryy->SetTitle(";Raster 1 Y Current (ADC Channel); Raster 2 Y Current (ADC Channel)");

c4->Divide(2,1);
c4->cd(1);
T->Draw(Form("%srb.Raster2.rawcur.x:%srb.Raster.rawcur.x>>rasterxx",arm.Data(),arm.Data()) ,"","colz");
c4->cd(2);
T->Draw(Form("%srb.Raster2.rawcur.y:%srb.Raster.rawcur.y>>rasteryy",arm.Data(),arm.Data()) ,"","colz");

c1->SaveAs(Form("./plots/%i_size.pdf",run));
c2->SaveAs(Form("./plots/%i_bpmsize.pdf",run));
c3->SaveAs(Form("./plots/%i_currentsize.pdf",run));
c4->SaveAs(Form("./plots/%i_syncsize.pdf",run));

}
