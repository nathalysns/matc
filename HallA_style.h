void HallA_style() {
  gROOT->SetStyle("Plain");
  gStyle->SetPaperSize(TStyle::kUSLetter);
  gStyle->SetPaperSize(18,22);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  gStyle->SetNdivisions(505);
  
  gStyle->SetCanvasColor(10);
  //gStyle->SetPadTopMargin(.05);
  //gStyle->SetPadLeftMargin(.15);
  //gStyle->SetPadRightMargin(.1);
  //gStyle->SetPadBottomMargin(.15);
  //gStyle->SetTitleYOffset(50.);
  gStyle->SetLabelFont(42,"X");
  gStyle->SetLabelFont(42,"Y");

   // prepare gStyle to be useful
  //   1 = solid
  //   2 = long dash (30 10)
  //   3 = dotted (4 8)
  //   4 = dash-dot (15 12 4 12)
  //   5 = short dash ( 15 15 )
  //   6 = dash-dot-dot 
  gStyle->SetLineStyleString(1,"[]");
  gStyle->SetLineStyleString(2,"[30 10]");
  gStyle->SetLineStyleString(3,"[4 8]");
  gStyle->SetLineStyleString(4,"[15 12 4 12]");
  gStyle->SetLineStyleString(5,"[15 15]");
  gStyle->SetLineStyleString(6,"[15 12 4 12 4 12]");
  gStyle->SetLabelSize(0.052,"X");
  gStyle->SetLabelSize(0.045,"Y");
  gStyle->SetNdivisions(510,"Y");
  //gStyle->SetNdivisions(205,"X");
  gStyle->SetOptDate(0);
  gStyle->SetDateY(.98);
  gStyle->SetStripDecimals(kFALSE);
  gStyle->SetTitleSize(0.045, "xy");
  gStyle->SetTitleX(0.3f);
  gStyle->SetTitleW(0.4f);
}
