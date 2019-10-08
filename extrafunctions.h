#ifndef EXTRAFUNCTIONS_H
#define EXTRAFUNCTIONS_H

#include "rootalias_spring2018.h"

vector<string> split(const string& s, const string& delim, const bool keep_empty = true) {
    vector<string> result;
    if (delim.empty()) {
        result.push_back(s);
        return result;
    }
    string::const_iterator substart = s.begin(), subend;
    while (true) {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        string temp(substart, subend);
        if (keep_empty || !temp.empty()) {
            result.push_back(temp);
        }
        if (subend == s.end()) {
            break;
        }
        substart = subend + delim.size();
    }
    return result;
}


Double_t bintrk_ef(TChain *T, Double_t min, Double_t max){


//=======Wire ==========================================//

TH1F *u10 = new TH1F("u10", "", 400, 0, 400);
TH1F *u20 = new TH1F("u20", "", 400, 0, 400);
TH1F *v10 = new TH1F("v10", "", 400, 0, 400);
TH1F *v20 = new TH1F("v20", "", 400, 0, 400);
TH1F *u1 = new TH1F("u1", "", 400, 0, 400);
TH1F *u2 = new TH1F("u2", "", 400, 0, 400);
TH1F *v1 = new TH1F("v1", "", 400, 0, 400);
TH1F *v2 = new TH1F("v2", "", 400, 0, 400);

TCut u1cut = Form("L.vdc.u1.wire>%f && L.vdc.u1.wire<%f",min,max);
TCut u2cut = Form("L.vdc.u2.wire>%f && L.vdc.u2.wire<%f",min,max);
TCut v1cut = Form("L.vdc.v1.wire>%f && L.vdc.v1.wire<%f",min,max);
TCut v2cut = Form("L.vdc.v2.wire>%f && L.vdc.v2.wire<%f",min,max);

T->Draw("L.vdc.u1.wire>>u10",electron_cut_Ltrack  + u1cut + "L.tr.n==0","goff");
T->Draw("L.vdc.u2.wire>>u20",electron_cut_Ltrack  + u2cut + "L.tr.n==0","goff");
T->Draw("L.vdc.v1.wire>>v10",electron_cut_Ltrack  + v1cut + "L.tr.n==0","goff");
T->Draw("L.vdc.v2.wire>>v20",electron_cut_Ltrack  + v2cut + "L.tr.n==0","goff");

T->Draw("L.vdc.u1.wire>>u1",electron_cut_Ltrack + u1cut + "L.tr.n!=0","goff");
T->Draw("L.vdc.u2.wire>>u2",electron_cut_Ltrack + u2cut + "L.tr.n!=0","goff");
T->Draw("L.vdc.v1.wire>>v1",electron_cut_Ltrack + v1cut + "L.tr.n!=0","goff");
T->Draw("L.vdc.v2.wire>>v2",electron_cut_Ltrack + v2cut + "L.tr.n!=0","goff");

Double_t ratio_u1 = u10->Integral()/u1->Integral();
Double_t ratio_u2 = u20->Integral()/u2->Integral();
Double_t ratio_v1 = v10->Integral()/v1->Integral();
Double_t ratio_v2 = v20->Integral()/v2->Integral();

Double_t ratio = 1-((ratio_u1+ratio_u2+ratio_v1+ratio_v2)/4);

cout << "ratios: " << ratio_u1 << " " << ratio_u2  << " "  << ratio_v1 << " " << ratio_v2 << endl;
delete gROOT->FindObjectAny("u10");
delete gROOT->FindObjectAny("u20");
delete gROOT->FindObjectAny("v10");
delete gROOT->FindObjectAny("v20");

delete gROOT->FindObjectAny("u1");
delete gROOT->FindObjectAny("u2");
delete gROOT->FindObjectAny("v1");
delete gROOT->FindObjectAny("v2");

//cout << "Final Ratio: " << ratio << endl;
return ratio;
}



#endif