
#include "RootInclude.h"
#include "StRootInclude.h"
#include <vector>
#include <iostream>
#include "TGraph.h"

using namespace std;

//Use wildcat in the file name to combine many files.
void DiffJetXFANCalc_6pt_East(TString inFileName, TString outName, TString outNameText, TString photon, TString det)
{

    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetOptDate(0);
    gStyle->SetEndErrorSize(10);

    TChain *ch = new TChain("T");
    
    TFile *file = new TFile(inFileName);   
    TFile *outFile = new TFile(outName, "recreate");

    ofstream outputtext;
    outputtext.open(outNameText);
    //ifstream sysinputtext;
    //sysinputtext.open("run15_FMS_SystematicError_in.txt");


    TH2D *BlueBeamUp;
    TH2D *BlueBeamDown;
    TH2D *YellowBeamUp;
    TH2D *YellowBeamDown;
    TH1D *polBlue_Allfill;
    TH1D *polYellow_Allfill;

    cout << "which type of photon multiplicity? " << photon << endl;
    if (photon == "all")
    {

    	BlueBeamUp = (TH2D*) file->Get("h2_BU_xF_vs_phi");
    	BlueBeamDown = (TH2D*) file->Get("h2_BD_xF_vs_phi");
    	YellowBeamUp = (TH2D*) file->Get("h2_YU_xF_vs_phi");
    	YellowBeamDown = (TH2D*) file->Get("h2_YD_xF_vs_phi");

    }
    if (photon == "12np")
    {

    	BlueBeamUp =     (TH2D*) file->Get("h2_BU_xF_vs_phi_nPhoton12");
    	BlueBeamDown =   (TH2D*) file->Get("h2_BD_xF_vs_phi_nPhoton12");
    	YellowBeamUp =   (TH2D*) file->Get("h2_YU_xF_vs_phi_nPhoton12");
    	YellowBeamDown = (TH2D*) file->Get("h2_YD_xF_vs_phi_nPhoton12");

    }
    if (photon == "3pnp")
    {

    	BlueBeamUp =     (TH2D*) file->Get("h2_BU_xF_vs_phi_nPhoton3p");
    	BlueBeamDown =   (TH2D*) file->Get("h2_BD_xF_vs_phi_nPhoton3p");
    	YellowBeamUp =   (TH2D*) file->Get("h2_YU_xF_vs_phi_nPhoton3p");
    	YellowBeamDown = (TH2D*) file->Get("h2_YD_xF_vs_phi_nPhoton3p");

    }

    polBlue_Allfill = (TH1D*) file->Get("polBlue_Allfill");
    polYellow_Allfill = (TH1D*) file->Get("polYellow_Allfill");

    Double_t pi=3.14;
    Double_t polB,polY;
    int nDrawPoints = 6;
    const int StartBin = 3;

    if (det == "fms")
    {

	int XFbins, nXFusebins, Phibins;
	XFbins = 20;
	nXFusebins = 9;
	Phibins=16;
	Double_t BlueUpNum[Phibins+1][XFbins+1];
	Double_t BlueDownNum[Phibins+1][XFbins+1];
	Double_t YellowUpNum[Phibins+1][XFbins+1];
	Double_t YellowDownNum[Phibins+1][XFbins+1];
	Double_t PhiPoint[] = {pi/16.,3*pi/16.,5*pi/16.,7*pi/16.,9*pi/16.,11*pi/16.,13*pi/16.,15*pi/16.};

	

	Double_t PhiPointErr[] = {0,0,0,0,0,0,0,0};
	//Double_t XFpoint[] = {0.05,0.15,0.25,0.35,0.45,0.55};
	//Double_t XFpoint[] = {0.025,0.075,0.125,0.175,0.225,0.275,0.325,0.375};
	Double_t XFpoint[] = {0.175,0.225,0.275,0.325,0.375,0.425,0.475};
	Double_t XFpointYellow[] = {0.170,0.220,0.270,0.320,0.370,0.420,0.470};
	//Double_t XFpoint[] = {0.225,0.275,0.325,0.375,0.425,0.475};
	//Double_t XFpointYellow[] = {0.220,0.270,0.320,0.370,0.420,0.470};
	Double_t XFpointErr[] = {0,0,0,0,0,0,0,0};
	Double_t XFSysBluepointErr[] = {0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002};
	Double_t XFSysYellowpointErr[] = {0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001};

	Double_t SysErr[20];
	Double_t YellowSysErr[20];
	Double_t sysB , sysY;

	polB=polBlue_Allfill->GetMean();
	polY=polYellow_Allfill->GetMean();

	//get number of event within each bin by XF and phi
	for (int i=0; i<Phibins ; i=i+1)
	{

		for (int j=StartBin; j<XFbins; j=j+1)
		{

			BlueUpNum[i][j] = BlueBeamUp->GetBinContent(i+1,j+1);
			cout<<"Blue beam Up x:"<<i<<" y:"<<j<<" n entries:"<<BlueUpNum[i][j]<<endl; 
			BlueDownNum[i][j] = BlueBeamDown->GetBinContent(i+1,j+1);
			cout<<"Blue beam Down x:"<<i<<" y:"<<j<<" n entries:"<<BlueDownNum[i][j]<<endl; 
			YellowUpNum[i][j] = YellowBeamUp->GetBinContent(i+1,j+1);
			cout<<"Yellow beam Up x:"<<i<<" y:"<<j<<" n entries:"<<BlueUpNum[i][j]<<endl; 
			YellowDownNum[i][j] = YellowBeamDown->GetBinContent(i+1,j+1);
			cout<<"Yellow beam Down x:"<<i<<" y:"<<j<<" n entries:"<<BlueDownNum[i][j]<<endl; 

		}

	}

	Double_t rawAN[Phibins/2];
	Double_t rawANErr[Phibins/2];
	Double_t YellowrawAN[Phibins/2];
	Double_t YellowrawANErr[Phibins/2];
	Double_t ANresult[nXFusebins - StartBin];
	Double_t ANresultErr[nXFusebins - StartBin];
	Double_t YellowANresult[nXFusebins - StartBin];
	Double_t YellowANresultErr[nXFusebins - StartBin];
	Double_t a,b,c,d ,  rawANnomin , rawANdenomin, rawANErrnomin , rawANErrdenomin;
	Double_t xF;

	TGraphErrors *BlueBeamRawAN[nXFusebins];
	TGraphErrors *BlueBeamAN;
	TGraphErrors *BlueBeamSys;
	TGraphErrors *YellowBeamRawAN[nXFusebins];
	TGraphErrors *YellowBeamAN;
	TGraphErrors *YellowBeamSys;

	
	TF1 *BlueFit;
	TF1 *YellowFit;

	for (int j=StartBin; j<nXFusebins; j=j+1)
	{


		for(int i=0; i<(Phibins / 2); i=i+1)
		{

			a = BlueUpNum[i+(Phibins/2)][j]; //a: N^{up} (phi)
			b = BlueDownNum[i][j]; //b: N^{down} (phi + pi)
			c = BlueDownNum[i+(Phibins/2)][j]; //c: N^{down} (phi)
			d = BlueUpNum[i][j]; //d: N^{up} (phi + pi)

			rawANnomin = sqrt(a*b) - sqrt(c*d);
			rawANdenomin = sqrt(a*b) + sqrt(c*d);
			rawAN[i] = rawANnomin / rawANdenomin;

			rawANErrnomin = b*c*d + a*c*d + a*b*d + a*b*c;
			rawANErrdenomin = pow(rawANdenomin,4);
			rawANErr[i] = sqrt(rawANErrnomin / rawANErrdenomin);
			cout<<"XF "<<(0.05*(j))<<" to "<<(0.05*(j+1))<<" phi bin: "<<(0.125*(i))<<"pi to "<<(0.125*(i+1))<<"pi  raw AN="<<rawAN[i]<<"  raw AN uncertainty="<<rawANErr[i]<<endl;

			a = YellowUpNum[i+(Phibins/2)][j]; //a: N^{up} (phi)
			b = YellowDownNum[i][j]; //b: N^{down} (phi + pi)
			c = YellowDownNum[i+(Phibins/2)][j]; //c: N^{down} (phi)
			d = YellowUpNum[i][j]; //d: N^{up} (phi + pi)

			rawANnomin = sqrt(a*b) - sqrt(c*d);
			rawANdenomin = sqrt(a*b) + sqrt(c*d);
			YellowrawAN[i] = rawANnomin / rawANdenomin;

			rawANErrnomin = b*c*d + a*c*d + a*b*d + a*b*c;
			rawANErrdenomin = pow(rawANdenomin,4);
			YellowrawANErr[i] = sqrt(rawANErrnomin / rawANErrdenomin);


		}
		
		BlueBeamRawAN[j] = new TGraphErrors(Phibins / 2,PhiPoint , rawAN, PhiPointErr,rawANErr);
		BlueBeamRawAN[j]->SetName(Form("BlueBeamRawAN_%i",j));
		BlueBeamRawAN[j]->SetTitle(Form("Blue Beam Raw A_{N} by x_{F} %.2f to %.2f",0.05*j, 0.05*(j+1)));
		BlueBeamRawAN[j]->GetXaxis()->SetTitle("#phi");
		BlueBeamRawAN[j]->GetYaxis()->SetTitle("raw A_{N}");
		//BlueBeamRawAN[j]->Write();

		BlueFit = new TF1("BlueFit","[0]*cos(x) + [1]");
		BlueFit->SetParLimits(1,-0.2,0.2);
		BlueBeamRawAN[j]->Fit("BlueFit");
		ANresult[j-StartBin] = BlueFit->GetParameter(0) / polB;
		ANresultErr[j-StartBin] = BlueFit->GetParError(0) / polB;
		BlueBeamRawAN[j]->Write();

		//sysinputtext>>xF>>sysB >> sysY;
		//SysErr[j-StartBin] = fabs(ANresult[j-StartBin] * sysB);
		//cout<<"AN result "<<j-StartBin<<": "<<ANresult[j-StartBin]<<"	AN statics un: "<<ANresultErr[j-StartBin]<<"	AN syst un:"<<SysErr[j-StartBin]<<endl;

		outputtext<<"B"<<"    "<<XFpoint[j-StartBin]<<"    "<<ANresult[j-StartBin]<<"    "<<ANresultErr[j-StartBin]<<endl;

		YellowBeamRawAN[j] = new TGraphErrors(Phibins / 2,PhiPoint , YellowrawAN, PhiPointErr,YellowrawANErr);
		YellowBeamRawAN[j]->SetName(Form("YellowBeamRawAN_%i",j));
		YellowBeamRawAN[j]->SetTitle(Form("Yellow Beam Raw A_{N} by x_{F} %.2f to %.2f",0.05*j, 0.05*(j+1)));
		YellowBeamRawAN[j]->GetXaxis()->SetTitle("#phi");
		YellowBeamRawAN[j]->GetYaxis()->SetTitle("raw A_{N}");
		//BlueBeamRawAN[j]->Write();

		YellowFit = new TF1("YellowFit","[0]*cos(x) + [1]");
		YellowFit->SetParLimits(1,-0.2,0.2);
		YellowBeamRawAN[j]->Fit("YellowFit");
		YellowANresult[j-StartBin] = YellowFit->GetParameter(0) / polY;
		YellowANresultErr[j-StartBin] = YellowFit->GetParError(0) / polY;
		YellowBeamRawAN[j]->Write();
		//YellowSysErr[j-StartBin] = fabs(YellowANresult[j-StartBin] * sysY);
		outputtext<<"Y"<<"    "<<XFpoint[j-StartBin]<<"    "<<YellowANresult[j-StartBin]<<"    "<<YellowANresultErr[j-StartBin]<<endl;
	}

	//BlueBeamAN = new TGraphErrors((nXFusebinsStartBin) , XFpoint , ANresult , XFpointErr , ANresultErr);
	BlueBeamAN = new TGraphErrors(nDrawPoints , XFpoint , ANresult , XFpointErr , ANresultErr);
	TF1 *ANconstant = new TF1("ANconstant","[0]");
	BlueBeamAN->Fit("ANconstant");
	BlueBeamAN->SetName("BlueBeamAN");
	BlueBeamAN->SetTitle("A_{N} (x_{F} > 0)");
	BlueBeamAN->GetXaxis()->SetTitle("X_{F}");
	BlueBeamAN->GetYaxis()->SetTitle("A_{N}");
	BlueBeamAN->Write();
	ANconstant->SetLineWidth(3);
	//ANconstant->Write();
	cout<<"Blue beam A_{N} with constant fit:"<<ANconstant->GetParameter(0)<<"+/-"<<ANconstant->GetParError(0)<<" value/error ratio:"<<1.0*fabs(ANconstant->GetParameter(0))/(ANconstant->GetParError(0))<<endl;

	//BlueBeamSys = new TGraphErrors(nDrawPoints , XFpoint , ANresult , XFSysBluepointErr , SysErr);
	//BlueBeamSys->SetTitle("A_{N} Sys (x_{F} > 0)");
	//BlueBeamSys->GetXaxis()->SetTitle("X_{F}");
	//BlueBeamSys->GetYaxis()->SetTitle("A_{N}");
	//YellowBeamAN = new TGraphErrors((nXFusebinsStartBin) , XFpoint , YellowANresult , XFpointErr , YellowANresultErr);
	YellowBeamAN = new TGraphErrors(nDrawPoints , XFpointYellow , YellowANresult , XFpointErr , YellowANresultErr);
	TF1 *ANconstantY = new TF1("ANconstantY","[0]");
	YellowBeamAN->Fit("ANconstantY");
	YellowBeamAN->GetFunction("ANconstantY")->SetLineColor(6);
	YellowBeamAN->SetName("YellowBeamAN");
	YellowBeamAN->SetTitle("A_{N} (x_{F} < 0)");
	YellowBeamAN->GetXaxis()->SetTitle("X_{F}");
	YellowBeamAN->GetYaxis()->SetTitle("A_{N}");
	YellowBeamAN->Write();
	//ANconstantY->SetLineColor(6);
	ANconstantY->SetLineWidth(3);
	//ANconstantY->Write();
	cout<<"Yellow beam A_{N} with constant fit:"<<ANconstantY->GetParameter(0)<<"+/-"<<ANconstantY->GetParError(0)<<" value/error ratio:"<<1.0*fabs(ANconstantY->GetParameter(0))/(ANconstantY->GetParError(0))<<endl;
	//YellowBeamSys = new TGraphErrors(nDrawPoints , XFpointYellow , YellowANresult , XFSysYellowpointErr , YellowSysErr);
	//YellowBeamSys->SetTitle("A_{N} Sys (x_{F} > 0)");
	//YellowBeamSys->GetXaxis()->SetTitle("X_{F}");
	//YellowBeamSys->GetYaxis()->SetTitle("A_{N}");

	TCanvas *ANplot = new TCanvas("ANPlot","",200,10,1024,768);
	ANplot->DrawFrame(2., -0.06, 250., 0.2);
	//ANplot->SetLeftMargin(0.05);
	//ANplot->SetRightMargin(0.05);
	TH2D * temp = new TH2D("temp","A_{N}",8,0.15,0.45,30,-0.10,0.10);
	//TH2D * temp = new TH2D("temp","A_{N}",8,0.1,0.5,30,-0.10,0.10);
	temp->GetYaxis()->SetTitle("A_{N}");
  	temp->GetYaxis()->SetTitleOffset(0.9);
  	temp->GetXaxis()->SetTitle("|x_{F}|");
  	temp->Draw();
	YellowBeamAN->SetMarkerColor(kRed+1);
	YellowBeamAN->SetMarkerSize(2);
	YellowBeamAN->SetMarkerStyle(22);
	YellowBeamAN->SetLineWidth(2);
	YellowBeamAN->SetLineColor(kRed+1);
	YellowBeamAN->Draw("P");
	//YellowBeamSys->SetMarkerColor(kRed+1);
	//YellowBeamSys->SetMarkerSize(2);
	//YellowBeamSys->SetLineColor(kRed+1);
	//YellowBeamSys->SetLineWidth(2);
	//YellowBeamSys->SetFillStyle(0);
	//YellowBeamSys->SetFillColorAlpha(1,0.5);
//	YellowBeamSys->Draw("e5");
	BlueBeamAN->SetMarkerColor(kBlue+1);
	BlueBeamAN->SetMarkerSize(2);
	BlueBeamAN->SetMarkerStyle(20);
	BlueBeamAN->SetLineColor(kBlue+1);
	BlueBeamAN->SetLineWidth(2);
	BlueBeamAN->Draw("P");
	//BlueBeamSys->SetMarkerColor(kBlue+1);
	//BlueBeamSys->SetMarkerSize(2);
	//BlueBeamSys->SetLineColor(kBlue+1);
	//BlueBeamSys->SetLineWidth(2);
	//BlueBeamSys->SetFillStyle(0);
	//BlueBeamSys->SetFillColorAlpha(1,0.5);
//	BlueBeamSys->Draw("e5");

	TLegend *leg = new TLegend(0.15,0.35,0.23,0.47);
	leg->SetTextSize(0.04);
	leg->AddEntry(BlueBeamAN,"x_{F} > 0","p");
	leg->AddEntry(YellowBeamAN,"x_{F} < 0","p");
	leg->SetBorderSize(0);
	leg->Draw("same");
	TLine *line1 = new TLine(0.15, 0, 0.45, 0);
  	line1->SetLineStyle(7);
  	line1->Draw("same");

//	TLatex T1;
//	T1.SetTextAlign(11);
//   	T1.SetTextSize(0.035);
//	T1.SetTextColor(kRed);
//	T1.DrawLatex(0.11,-0.11,"STAR Preliminary");

	TLatex T2;
        T2.SetTextAlign(11);
        T2.SetTextSize(0.035);
        T2.SetTextColor(kBlack);
   	T2.DrawLatex(0.16,-0.06,"p^{#uparrow} + p #rightarrow EM jet + p + X");
   	T2.DrawLatex(0.16,-0.075,"#sqrt{s} = 200 GeV");
   	T2.DrawLatex(0.16,-0.09,"3.0\% polarization scale uncertainty not shown");
	

	if (photon == "all")
	{

		ANplot->SaveAs("FMS_ANplot.pdf");
		ANplot->SaveAs("FMS_ANplot.png");
		ANplot->SaveAs("FMS_ANplot.root");

	}
	if (photon == "12np")
	{

		ANplot->SaveAs("FMS_ANplot_12np.pdf");
		ANplot->SaveAs("FMS_ANplot_12np.png");
		ANplot->SaveAs("FMS_ANplot_12np.root");

	}
	if (photon == "3pnp")
	{

		ANplot->SaveAs("FMS_ANplot_3pnp.pdf");
		ANplot->SaveAs("FMS_ANplot_3pnp.png");
		ANplot->SaveAs("FMS_ANplot_3pnp.root");

	}



    }





    outFile->Write();
    outFile->Close();
    delete ch;
}
