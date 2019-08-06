// compare several multifoil runs for tg_y, vz and tg_y:yp
// this does not work well with root6, better run with root5
// shujie 

#include "rootalias.h"
#include "InputL.h"

Double_t const xoff_fall = -0.007;

TVector3 GetSieveHoleTCS( UInt_t Col, UInt_t Row) 
{
    assert(Col < NSieveCol);
    assert(Row < NSieveRow);

   
    const Double_t CentralColID = (NSieveCol-1)/2.;
    const Double_t CentralRowID = (NSieveRow-1)/2.;

    Double_t X = (Row-CentralRowID)*SieveDX + XOffset[Col] + SieveOffX;
    Double_t Y = (Col-CentralColID)*SieveDY + SieveOffY;
    //TVector3 SieveHoleTCS(SieveOffX + SieveXbyRow[Row], SieveOffY + SieveYbyCol[Col], ZPos);
    //return SieveHoleTCS;
    return TVector3(X,Y,ZPos);
}


TCutG* foil(TChain* T, Int_t root5=0, Int_t fcut=0){


  TVirtualPad *pad = gPad;
  pad->cd();


  //TCut trigger = "((DL.evtypebits>>2)&1)";
  TCut DrawCut=track_L+electron_cut_L+dp_cut_L+th_cut_L+ph_cut_L;//+trigger

  // get p0
  TH1F *momentum = new TH1F("momentum", "", 400, 1,10);

  T->Project("momentum","HacL_D1_P0rb");
  Double_t p0=momentum->GetMean();
  cout<<"momentum="<<p0<<endl;

  TH1F *q1 = new TH1F("q1", "", 4000, -1.5,-1.);

  T->Project("q1","HacL_Q1_LS450_FLD_DATA");
  Double_t q1field=q1->GetMean();
  cout<<"Q1 field="<<q1field<<endl;
  // select foil
  TH2F     *h1  = new TH2F("h1", "target y vs ph", 400, -0.06,0.06,400,-0.06,0.06);
  assert(h1);

  T->Draw("L.tr.tg_y:L.tr.tg_ph>>h1", DrawCut, "COLZ");


  TLatex *t = new TLatex();
  t->SetTextColor(kRed);
  t->SetTextSize(0.06);
  t->SetTextAlign(12);
  t->DrawTextNDC(0.15,0.8,Form("p0=%.2f,Q1 field=%.3f",p0,q1field));
  gPad->SetGrid();

  if(fcut){

    TCanvas *temp = new TCanvas("temp","",1200,800);
    h1->Draw("colz");
    t->DrawTextNDC(0.15,0.85,"==Please select a foil==");

    TCutG* cutg;
    if(root5) 
    cutg = (TCutG*)(TVirtualPad::Pad()->WaitPrimitive("CUTG", "CutG")); // making cut, store to CUTG
    else{ 
      temp->WaitPrimitive("CUTG", "CutG"); // making cut, store to CUTG
      cutg = (TCutG*)gROOT->GetListOfSpecials()->FindObject("CUTG");     
    }
    cout<<"==Processing cut=="<<endl;

    cutg->SetLineColor(kRed);
    cutg->SetLineWidth(2);
    cutg->Draw("PL");

    pad->cd();
    TCutG* cutfoil=(TCutG*)cutg->Clone("cutfoil"); // store previous cut 
    cutfoil->SetName("cutfoil");
    cutfoil->SetVarX("L.tr.tg_ph");  cutfoil->SetVarY("L.tr.tg_y");
    cutfoil->SetLineColor(kRed);
    cutfoil->SetLineWidth(2);
    cutfoil->Draw("PL");
    //  T->Draw("L.tr.vz:L.tr.tg_ph>>h1",DrawCut+"&&cutfoil", "COLZ");
    //return;
    temp->Close();
    cutg->Delete();
    cout<<"==Done=="<<endl;
    return cutfoil;

    }
    return 0 ;

  }
//--------------------------------
// plot sieve pattern
//--------------------------
TCutG* sieve(Int_t runnum, TChain* T, TCutG* cutfoil, Int_t root5 =0, Int_t fcut=0){

  TVirtualPad *pad = gPad;
  pad->cd();
  Double_t xoff=0;
  if((runnum>3000&&runnum<4000) || runnum>94000) xoff=xoff_fall;
    //TCut trigger = "((DL.evtypebits>>2)&1)";
    TCut DrawCut=track_L+electron_cut_L+dp_cut_L+th_cut_L+ph_cut_L;//+trigger

  //print sieve pattern
 TH2F *h2 = new TH2F("h2", "sieve x vs. sieve y", 400, -0.1,0.1,400,-0.09,0.09);
  assert(h2);
  T->Draw(Form("L.tr.tg_th*%g-Lrb.y+%f:L.tr.tg_ph*%g+L.tr.tg_y>>h2",ZPos,xoff,ZPos), DrawCut+"cutfoil", "COLZ");
  Double_t xmin=h2->FindFirstBinAbove(0,1);
  Double_t xmax=h2->FindLastBinAbove(0,1);
  
  Double_t ymin=h2->FindFirstBinAbove(0,2);
  Double_t ymax=h2->FindLastBinAbove(0,2);

  gPad->SetGrid();  
  TLatex *t = new TLatex();
  t->SetTextColor(kRed);
  t->SetTextSize(0.04);
  t->SetTextAlign(12);

  const Double_t plotwidth = 0.004;
  for (UInt_t Row = 0 ; Row < (NSieveRow); Row++) {
    for (UInt_t Col = 0 ; Col < (NSieveCol ); Col++) {
    //const Double_t posx = SieveOffY + SieveYbyCol[Col];
    //const Double_t posy = SieveOffX + SieveXbyRow[Row];
      const TVector3 SieveHolePos = GetSieveHoleTCS(Col,Row);
    const Double_t posx = SieveHolePos.Y();
    const Double_t posy = SieveHolePos.X();

    TLine *lh = new TLine(posx - plotwidth, posy, posx + plotwidth, posy);
    TLine *lv = new TLine(posx, posy - plotwidth, posx, posy + plotwidth);
    lh -> SetLineColor(kBlack);
    lv -> SetLineColor(kBlack);

    lh -> Draw();
    lv -> Draw();
    }
  }

  if(fcut){

    TCanvas *temp = new TCanvas("temp","",1200,800);
    h2->Draw("colz");
    t->DrawTextNDC(0.15,0.85,"==Please select a Column==");

    TCutG* cutg;

    if(root5) 
    cutg = (TCutG*)(TVirtualPad::Pad()->WaitPrimitive("CUTG", "CutG")); // making cut, store to CUTG
    else{ 
      temp->WaitPrimitive("CUTG", "CutG"); // making cut, store to CUTG
      cutg = (TCutG*)gROOT->GetListOfSpecials()->FindObject("CUTG");     
    }

    cout<<"==Processing=="<<endl;
    cutg->SetLineColor(kRed);
    cutg->SetLineWidth(2);
    cutg->Draw("PL");

    pad->cd();
    TCutG* cutcol=(TCutG*)cutg->Clone("cutcol"); // store previous cut 
    cutcol->SetName("cutcol");
    
    cutcol->SetVarY(Form("L.tr.tg_th*%g-Lrb.y",ZPos)); 
    cutcol->SetVarX(Form("L.tr.tg_ph*%g+L.tr.tg_y",ZPos));
    cutcol->SetLineColor(kRed);
    cutcol->SetLineWidth(2);
    cutcol->Draw("PL");
    //  T->Draw("L.tr.vz:L.tr.tg_ph>>h1",DrawCut+"&&cutfoil", "COLZ");
    //return;
    temp->Close();
    cutg->Delete();
    return cutcol;

  }
  return 0;
}

//--------------------------------
// plot column in 1d
//--------------------------
TH1F* column(Int_t runnum,TChain* T, TCutG* cutfoil, TCutG* cutcol, Int_t root5 =0){

  TVirtualPad *pad = gPad;
  pad->cd();

 Double_t xoff=0;
  if((runnum>3000&&runnum<4000) || runnum>94000) xoff=xoff_fall;
 // TCut trigger = "((DL.evtypebits>>2)&1)";
  TCut DrawCut=track_L+electron_cut_L+dp_cut_L+th_cut_L+ph_cut_L;//trigger

  //print theta
 TH1F *h2 = new TH1F("h2", "xptar", 200, -0.1,0.1);
  assert(h2);
  T->Draw(Form("L.tr.tg_th+%f>>h2",xoff), DrawCut+"cutfoil&&cutcol", "");
  gPad->SetGrid();  

  return h2;

  }


void check_optics(string runlist,Int_t root5=0,Int_t plot_sieve=1, Int_t plot_column=0){
  
  gStyle->SetOptStat(0);
  Int_t color[]={1,2,4,6,28};
  cout<<"Will check run "<<runlist<<endl;
  std::stringstream str(runlist); 
  vector<int> ll;
  // str<<endl;
  while (!str.eof()){
   int temp;
   str>>temp;
   ll.push_back(temp);
   cout<<temp<<endl;
  }
  Int_t size = ll.size();
  int nn=0;


  // for the plot_column option
  TString drawoption="";
  TCanvas *cc = new TCanvas("cc","cc",800,600); 
  TLegend *leg = new TLegend(0.45,0.8,0.95,0.95);
  TH1F*   hcol[size]; // to store 1d plot of theta per foil per col
  Double_t ymax=0;


  TString tt[size]; // histrogram title
  TCanvas *c2 = new TCanvas("c2","c2",800*size,1200); 
  TLatex *t = new TLatex();
  t->SetTextColor(kRed);
  t->SetTextSize(0.06);
  t->SetTextAlign(12);

  int col=1+plot_sieve+plot_column;
  if (col>3 ||col<1) {
   cout<<"Error: invalid input value on flag plot_foil and plot_sieve"<<endl;
   return;
  }
  c2->Divide(size,col);
  for (int rr=0;rr<size;rr++){
    gROOT->GetListOfSpecials()->Clear();
    Int_t runnum = ll[rr];
    TChain *T=LoadRun(runnum,"T");
    if (!T) T=LoadOnline(runnum);
    else if(T->GetEntries()==0) T=LoadOnline(runnum);

    cout<<"Run "<<runnum<<": "<<T->GetEntries()<<" TTree entries in total"<<endl;
//  return;
    c2->cd(nn+1);
    cout<<rr<<endl;
    TCutG *cutafoil=foil(T,root5,plot_sieve);
    tt[rr] = Form("Run %d",runnum);
    t->DrawTextNDC(0.15,0.85,tt[rr]);

    if(plot_sieve==1){

      c2->cd(nn+size+1);
      TCutG *cutacolumn=sieve(runnum,T,cutafoil,root5,plot_column);

      if(plot_column==1){

        c2->cd(nn+size*2+1);
        hcol[rr]=column(runnum,T,cutafoil,cutacolumn,root5);
        hcol[rr]->SetLineColor(color[rr]);
        hcol[rr]->SetXTitle("L.tr.tg_th");
        if(hcol[rr]->GetMaximum() > ymax) ymax = hcol[rr]->GetMaximum();
       // TF1*    g1 = new TF1("g1","gaus",-0.1,-0.05);
       // TF1*    g2 = new TF1("g2","gaus",0.05,0.1);
       // fit the holes next to the edge 
        TF1*    g1 = new TF1("g1","gaus",-0.045,-0.03);
        TF1*    g2 = new TF1("g2","gaus",0.03,0.045);
        hcol[rr]->Fit(g1,"R");
        hcol[rr]->Fit(g2,"R");
        Double_t peak1 = g1->GetParameter(1);
        Double_t peak2 = g2->GetParameter(1);
        // fit the first and last peak
        cc->cd();
        hcol[rr]->Draw(drawoption);
	cout<<hcol[rr]->GetEntries()<<" Entries"<<endl;
        leg->AddEntry(hcol[rr],tt[rr]+Form(", peak diff=%.4f",peak2-peak1),"l");
        drawoption="same";
      }
    }

    nn++;
  }
  if(plot_column){
    hcol[0]->SetMaximum(ymax*1.3);
    leg->SetTextSize(0.04);
    leg->Draw("");
  }
}
