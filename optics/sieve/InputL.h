// Description of G2P optics

#ifndef ROOT_Input
#define ROOT_Input

#include "TROOT.h"
#include "TMath.h"

using namespace std;
const TString InputID = "GMP_LHRS";

/////////////////////////////////////////////////////////////////////////
// Input Sections
/////////////////////////////////////////////////////////////////////////

const Double_t D2R = TMath::DegToRad();
/////////////////////////////////////////////////////////////////////////
// HRS Position Inputs
const Double_t HRSAngle = 42.001 * D2R; //WARNING: check
const Double_t MissPointH = -1.07e-3; //m, negative when spectrometer points to upstream of target
const Double_t MissPointV = -1.98e-3; //m

const Double_t BeamShiftX = 0.0;

/////////////////////////////////////////////////////////////////////////
// Sieve Position Inputs
const UInt_t NSieveCol = 25;
const Double_t SieveDY = -0.246*25.4e-3; // Horizontal spacing between columns in meter
const UInt_t NSieveRow = 7;
const Double_t SieveDX = .492*2*25.4e-3; // Vertical spacing between rows in meter
const Double_t XOffset[NSieveCol] = {0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0,SieveDX/2.,0};

// SieveOff* are in TCS
const Double_t SieveOffY = 1.90e-3;
const Double_t SieveOffX = -0.24e-3;
const Double_t ZPos = (1070.70+25.4/2.) * 1e-3; // ??????

/////////////////////////////////////////////////////////////////////////
// Vertex Position Inputs
static const UInt_t NFoils = 9; //WARNING: check
//const Double_t targetfoils[] = {-10.0e-2, -7.5e-2, -5.0e-2, -2.0e-2, 0, 2.0e-2, 5.0e-2, 7.5e-2, 10.0e-2, 1e36};
const Double_t targetfoils[] = {-10.0e-2+2.02e-3, -7.5e-2+2.02e-3, -5.0e-2+2.02e-3, -2.0e-2+2.02e-3, 0+2.02e-3, 2.0e-2+2.02e-3, 5.0e-2+2.02e-3, 7.5e-2+2.02e-3, 10.0e-2+2.02e-3, 1e36};

/* ///////////////////////////////////////////////////////////////////////// */
/* // Excitation State Inputs */
/* const UInt_t NKine = 5; //N Delta Scans */

/* #define DIPOLE_MAG2MOM(Mag) (2.702*(Mag)-1.6e-03*(Mag)*(Mag)*(Mag)) */
/* const Double_t HRSCentralMom[] = { */
/*     DIPOLE_MAG2MOM((0.8580545 + 0.8580571) / 2.), // -3% run 5592 5591 */
/*     DIPOLE_MAG2MOM((0.8413956 + 0.8413937) / 2.), // -1% run 5594 5593 */
/*     DIPOLE_MAG2MOM((0.8328684 + 0.8328685) / 2.), //  0% run 5585 5582 */
/*     DIPOLE_MAG2MOM((0.8243780 + 0.8243814) / 2.), //  1% run 5588 5586 */
/*     DIPOLE_MAG2MOM((0.8077295 + 0.8077288) / 2.), //  3% run 5590 5589 */
/*     0 */
/* }; */

/////////////////////////////////////////////////////////////////////////
// Excitation State Inputs
const UInt_t NKine = 5; //N Delta Scans

const Double_t HRSCentralMom[] = {
    2.07805,
    2.03805,
    1.99796,
    1.95799,
    1.91793
};

const Double_t GroundNuclearMass = 0.938272; //GeV/c^2  //Hydrogen Target
const Double_t ExcitationEnergy[] = //selected excitation states for each kinematics
  {0., 0., 0., 0., 0.};
//{0.,0.00443891,0.00443891,0.00443891,0.00443891};

const UInt_t NExcitationStates = 1; // H2 Excitation States
const Double_t ExcitationEnergyList[] = {0};

/////////////////////////////////////////////////////////////////////////
// Information for delta scan runs

const double mElectron = 0.511e-3; // in GeV/c

// Target geometry and materials
const Double_t targetLength = 0.15; // in meter
const Double_t TipRadius = 1.5*2.54*1.e-2; // in meter
const Double_t TargetRadius = TipRadius;
const Double_t WallThickness = 0.173*1.e-3; // in meter
const Double_t TipThickness = 0.132*1.e-3; // in meter
// The number Barak is using in Gmp replay
//const Double_t targetLength = 0.15; // in meter
//const Double_t TipRadius = 0.0381; // in meter
//const Double_t TargetRadius = TipRadius;
//const Double_t WallThickness = 0.173*1.e-3; // in meter
//const Double_t TipThickness = 0.132*1.e-3; // in meter

//const Double_t density_LH2 = 0.0709; // Check again!
const Double_t density_LH2 = 0.0723; // @19K, From cryotarget training slides
const Double_t z_LH2 = 1.;
const Double_t A_LH2 = 1.008;
// The number Barak is using in Gmp replay
//const Double_t density_LH2 = 0.07332; // @19K, From cryotarget training slides
//const Double_t z_LH2 = 1.;
//const Double_t A_LH2 = 1.00727;

const Double_t entrThickness = 0.175e-3; // Loop2
const Double_t density_Al = 2.81;
//const Double_t z_Al = 14.2; // Al7075 13.
//const Double_t A_Al = 29.71; // 26.98
const Double_t z_Al = 13.;
const Double_t A_Al = 26.98;
// The number Barak is using in Gmp replay
//const Double_t entrThickness = 0.175e-3; // Loop2
//const Double_t density_Al = 2.70;
//const Double_t z_Al = 13.;
//const Double_t A_Al = 26.98;

const double SC_window = 0.016*2.54e-2;
const double AirLength = HRSAngle > 0 ? 10.62*2.54e-2 : 13.33*2.54e-2;
const double z_Air = 7.22000;
const double A_Air = 14.46343;
const double density_Air = 1.20480e-3;
const double HRS_window = 0.012*2.54e-2;
const double z_Kapton = 5.02564;
const double A_Kapton = 9.80345;
const double density_Kapton = 1.42000;
// The number Barak is using in Gmp replay
//const double SC_window = 4.064e-4;
//const double AirLength = HRSAngle > 0 ? 10.62*2.54e-2 : 0.3386;
//const double z_Air = 7.22000;
//const double A_Air = 14.46343;
//const double density_Air = 1.20480e-3;
//const double HRS_window = 3.048e-4;
//const double z_Kapton = 5.02564;
//const double A_Kapton = 9.80345;
//const double density_Kapton = 1.42000;

/////////////////////////////////////////////////////////////////////////
// Disable Extended Target Correction

//const Double_t ExtTarCor_ThetaCorr = 0.61;
//const Double_t ExtTarCor_DeltaCorr = 5.18;

/////////////////////////////////////////////////////////////////////////
// Database header

const char * Prefix = "L.OpticsOpt.";
/*
const char * DatabaseHeader = "\
[ R.global ]   \n\
0.3327 1 0.0 270.2 0.0 -1.6e-03        VDC Angle, Plane Spacing, Gamma Coefficents  \n\
matrix elements   \n\
t 0 0 0  -1.001135e+00 -3.313373e-01 -4.290819e-02  4.470852e-03  0.000000e+00  0.000000e+00  0.000000e+00  0\n\
y 0 0 0  -8.060915e-03  1.071977e-03  9.019102e-04 -3.239615e-04  0.000000e+00  0.000000e+00  0.000000e+00  0\n\
p 0 0 0  -2.861912e-03 -2.469069e-03  8.427172e-03  2.274635e-03  0.000000e+00  0.000000e+00  0.000000e+00  0\n\
";
*/
const char * DatabaseHeader = "\
[ L.global ]   \n\
0.3327 1 0.0 270.2 0.0 -1.6e-03        VDC Angle, Plane Spacing, Gamma Coefficents  \n\
matrix elements   \n\
";

const char * DatabaseFooter = "\
XF 1 0 0 0 0 -2.181E+00\n\
XF 0 1 0 0 0 -1.980E-01\n\
XF 0 0 0 0 1  1.191E+01\n\
TF 1 0 0 0 0 -1.000E-01\n\
TF 0 1 0 0 0 -4.690E-01\n\
TF 0 0 0 0 1  1.967E+00\n\
PF 0 0 1 0 0  3.630E-01\n\
PF 0 0 0 1 0 -0.902E+00\n\
YF 0 0 1 0 0 -5.950E-01\n\
YF 0 0 0 1 0 -1.274E+00\n\
";
/////////////////////////////////////////////////////////////////////////

#endif
