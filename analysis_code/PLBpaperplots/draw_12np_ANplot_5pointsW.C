void draw_12np_ANplot_5pointsW()
{

	
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetOptDate(0);
    gStyle->SetEndErrorSize(10);
    //TFile *file = TFile::Open("root_result/Run15FMSWestAna/Run15FMSXFCalc_AnaAll_0401.root");   
	
    ifstream inputtext;
    inputtext.open("finalANtext/run15_FMS_plot_SE_data_12np_5pt.txt");
    //ifstream inputtext_xaxis;
    //inputtext_xaxis.open("run15_FMS_plot_data_xError.txt");
    TH1D *polBlue_Allfill;
    TH1D *polYellow_Allfill;
    //polBlue_Allfill = (TH1D*) file->Get("polBlue_Allfill");
    //polYellow_Allfill = (TH1D*) file->Get("polYellow_Allfill");

    //TH1D *h1_xF1020;
    //TH1D *h1_xF2025;
    //TH1D *h1_xF2530;
    //TH1D *h1_xF3035;
    //TH1D *h1_xF3540;
    //TH1D *h1_xF4045;
    //h1_xF1020 = (TH1D*) file->Get("h1_xF_1020_12np");
    //h1_xF2025 = (TH1D*) file->Get("h1_xF_2025_12np");
    //h1_xF2530 = (TH1D*) file->Get("h1_xF_2530_12np");
    //h1_xF3035 = (TH1D*) file->Get("h1_xF_3035_12np");
    //h1_xF3540 = (TH1D*) file->Get("h1_xF_3540_12np");
    //h1_xF4045 = (TH1D*) file->Get("h1_xF_4045_12np");

    TString det;
    det = "fms";
    const int xFbin = 5;

	Double_t XFpoint[5];
	Double_t XFpointYellow[5];
	//Double_t XFpoint[] = {0.175,0.225,0.275,0.325,0.375,0.425,0.475};
	//Double_t XFpointYellow[] = {0.170,0.220,0.270,0.320,0.370,0.420,0.470};
	//Double_t XFpoint[] = {0.225,0.275,0.325,0.375,0.425,0.475};
	//Double_t XFpointYellow[] = {0.220,0.270,0.320,0.370,0.420,0.470};
	Double_t XFpointErr[] = {0,0,0,0,0,0,0,0};
	Double_t XFSysBluepointErr[] = {0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002};
	Double_t XFSysYellowpointErr[] = {0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001};
	Double_t xFpointtmp;
	Double_t polB, polY;

	//XFpoint[0] = h1_xF1020->GetMean();
	//XFpointYellow[0] = XFpoint[0] - 0.005;
	//XFpoint[1] = h1_xF2025->GetMean();
	//XFpointYellow[1] = XFpoint[1] - 0.005;
	//XFpoint[2] = h1_xF2530->GetMean();
	//XFpointYellow[2] = XFpoint[2] - 0.005;
	//XFpoint[3] = h1_xF3035->GetMean();
	//XFpointYellow[3] = XFpoint[3] - 0.005;
	//XFpoint[4] = h1_xF3540->GetMean();
	//XFpointYellow[4] = XFpoint[4] - 0.005;


	//polB=polBlue_Allfill->GetMean();
	//polY=polYellow_Allfill->GetMean();
	Double_t ANresult[xFbin];
	Double_t ANresultErr[xFbin];
	Double_t ANresultSys[xFbin];
	Double_t ANresultSigma[xFbin];
	Double_t XaxisSys[xFbin];
	Double_t YellowANresult[xFbin];
	Double_t YellowANresultErr[xFbin];
	Double_t YellowANresultSys[xFbin];
	Double_t YellowANresultSigma[xFbin];


	for (int i=0; i<xFbin;i=i+1)

	{

		inputtext >> XFpoint[i] >> ANresult[i] >> ANresultErr[i] >> ANresultSys[i] ;
		inputtext >> XFpointYellow[i] >> YellowANresult[i] >> YellowANresultErr[i] >> YellowANresultSys[i] ;
		//XaxisSys[i] = 0.05 * XFpoint[i];
		XaxisSys[i] = 0.005;
		XFpointYellow[i] = XFpointYellow[i] - 0.013;
		//inputtext_xaxis >> XFpoint[i] >> XaxisSys[i];
		cout << XFpoint[i] << ANresult[i] << ANresultErr[i] << ANresultSys[i] <<endl;
		cout << XFpoint[i] << YellowANresult[i] << YellowANresultErr[i] << YellowANresultSys[i] <<endl;
		ANresultSigma[i] = sqrt(ANresultErr[i]*ANresultErr[i]+ANresultSys[i]*ANresultSys[i]);
		YellowANresultSigma[i] = sqrt(YellowANresultErr[i]*YellowANresultErr[i]+YellowANresultSys[i]*YellowANresultSys[i]);

	}

	
	TGraphErrors *BlueBeamAN;
	TGraphErrors *BlueBeamSys;
	TGraphErrors *BlueBeamSigma;
	TGraphErrors *YellowBeamAN;
	TGraphErrors *YellowBeamSys;
	TGraphErrors *YellowBeamSigma;

	BlueBeamAN = new TGraphErrors(xFbin , XFpoint , ANresult , XFpointErr , ANresultErr);
	BlueBeamAN->SetName("BlueBeamAN");
	BlueBeamAN->SetTitle("A_{N} (x_{F} > 0)");
	BlueBeamAN->GetXaxis()->SetTitle("|X_{F}|");
	BlueBeamAN->GetYaxis()->SetTitle("A_{N}");

	BlueBeamSys = new TGraphErrors(xFbin , XFpoint , ANresult , XaxisSys , ANresultSys);
	BlueBeamSys->SetTitle("A_{N} Sys (x_{F} > 0)");
	BlueBeamSys->GetXaxis()->SetTitle("|X_{F}|");
	BlueBeamSys->GetYaxis()->SetTitle("A_{N}");
	BlueBeamSigma = new TGraphErrors(xFbin , XFpoint , ANresult , XaxisSys , ANresultSigma);
	TF1 *ANconstant = new TF1("ANconstant","[0]");
	BlueBeamSigma->Fit("ANconstant","0");
	ANconstant->SetLineWidth(3);
	ANconstant->SetLineColorAlpha(1,0.5);
	cout << "Blue beam constant fit Chi2: " << ANconstant->GetChisquare() << "	NDF: " << ANconstant->GetNDF() << "	ratio: " << (1.0 * ANconstant->GetChisquare() / ANconstant->GetNDF()) << endl;
	cout<<"Blue beam A_{N} with constant fit:"<<ANconstant->GetParameter(0)<<"+/-"<<ANconstant->GetParError(0)<<" value/error ratio:"<<1.0*fabs(ANconstant->GetParameter(0))/(ANconstant->GetParError(0))<<endl;
	//YellowBeamAN = new TGraphErrors((nXFusebins-2) , XFpoint , YellowANresult , XFpointErr , YellowANresultErr);
	YellowBeamAN = new TGraphErrors(xFbin , XFpointYellow , YellowANresult , XFpointErr , YellowANresultErr);
	YellowBeamAN->SetName("YellowBeamAN");
	YellowBeamAN->SetTitle("A_{N} (x_{F} < 0)");
	YellowBeamAN->GetXaxis()->SetTitle("|X_{F}|");
	YellowBeamAN->GetYaxis()->SetTitle("A_{N}");
	YellowBeamSys = new TGraphErrors(xFbin , XFpointYellow , YellowANresult , XaxisSys , YellowANresultSys);
	YellowBeamSys->SetTitle("A_{N} Sys (x_{F} > 0)");
	YellowBeamSys->GetXaxis()->SetTitle("|X_{F}|");
	YellowBeamSys->GetYaxis()->SetTitle("A_{N}");
	YellowBeamSigma = new TGraphErrors(xFbin , XFpointYellow , YellowANresult , XaxisSys , YellowANresultSigma);
	TF1 *ANconstantY = new TF1("ANconstantY","[0]");
	YellowBeamSigma->Fit("ANconstantY","0");
	//YellowBeamAN->GetFunction("ANconstantY")->SetLineColor(6);
	ANconstantY->SetLineWidth(3);
	ANconstantY->SetLineColor(6);
	//ANconstantY->SetLineColorAlpha(6,0.9);
	cout << "Yellow beam constant fit Chi2: " << ANconstantY->GetChisquare() << "	NDF: " << ANconstantY->GetNDF() << "	ratio: " << (1.0 * ANconstantY->GetChisquare() / ANconstantY->GetNDF()) << endl;
	cout<<"Yellow beam A_{N} with constant fit:"<<ANconstantY->GetParameter(0)<<"+/-"<<ANconstantY->GetParError(0)<<" value/error ratio:"<<1.0*fabs(ANconstantY->GetParameter(0))/(ANconstantY->GetParError(0))<<endl;

	TCanvas *ANplot = new TCanvas("ANPlot","",1024,768);
	ANplot->DrawFrame(2., -0.06, 250., 0.2);
	//ANplot->SetLeftMargin(-0.08);
	//ANplot->SetRightMargin(-0.05);
	TH2D * temp = new TH2D("temp","A_{N}",8,0.20,0.45,30,-0.349,0.149);
	//TH2D * temp = new TH2D("temp","A_{N}",8,0.1,0.5,30,-0.10,0.10);
	temp->GetYaxis()->SetTitle("A_{N}");
	gStyle->SetTitleFontSize(0.05);
  	temp->GetYaxis()->SetTitleOffset(0.9);
  	temp->GetXaxis()->SetTitle("x_{F}");

  	temp->Draw();
	YellowBeamAN->SetMarkerColor(12);
	YellowBeamAN->SetMarkerSize(2);
	YellowBeamAN->SetMarkerStyle(25);
	YellowBeamAN->SetLineWidth(2);
	YellowBeamAN->SetLineColor(12);
	//YellowBeamAN->Draw("P");
	YellowBeamSys->SetMarkerColor(12);
	YellowBeamSys->SetMarkerSize(2);
	YellowBeamSys->SetLineColor(12);
	YellowBeamSys->SetLineWidth(2);
	YellowBeamSys->SetFillStyle(0);
	YellowBeamSys->SetFillColorAlpha(1,0.5);
	//YellowBeamSys->Draw("e5");
	BlueBeamAN->SetMarkerColor(12);
	BlueBeamAN->SetMarkerSize(2);
	BlueBeamAN->SetMarkerStyle(21);
	BlueBeamAN->SetLineColor(12);
	BlueBeamAN->SetLineWidth(2);
	BlueBeamAN->Draw("P");
	BlueBeamSys->SetMarkerColor(12);
	BlueBeamSys->SetMarkerSize(2);
	BlueBeamSys->SetLineColor(12);
	BlueBeamSys->SetLineWidth(2);
	BlueBeamSys->SetFillStyle(0);
	BlueBeamSys->SetFillColorAlpha(1,0.5);
	BlueBeamSys->Draw("e5");

	//ANconstantY->Draw("same");
	//ANconstant->Draw("same");

	TLegend *leg = new TLegend(0.65,0.25,0.78,0.35);
	leg->SetTextSize(0.06);
	leg->AddEntry(BlueBeamAN,"x_{F} > 0","p");
	//leg->AddEntry(YellowBeamAN,"x_{F} < 0","p");
	leg->SetBorderSize(0);
	//leg->Draw("same");
	TLine *line1 = new TLine(0.20, 0, 0.45, 0);
  	line1->SetLineStyle(7);
  	line1->Draw("same");

	TLatex T1;
	T1.SetTextAlign(11);
   	T1.SetTextSize(0.035);
	T1.SetTextColor(kRed);
	T1.DrawLatex(0.24,-0.17,"STAR");

	TLatex T2;
        T2.SetTextAlign(11);
        T2.SetTextSize(0.04);
        T2.SetTextColor(kBlack);
   	T2.DrawLatex(0.24,-0.21,"p^{#uparrow} + p #rightarrow EM jet + p^{#uparrow} + X");
   	T2.DrawLatex(0.24,-0.25,"#sqrt{s} = 200 GeV");
   	T2.DrawLatex(0.24,-0.29,"Photon multiplicity = 1 or 2");
   	T2.DrawLatex(0.24,-0.33,"3.0\% polarization scale uncertainty not shown");
	
	
	//ANplot->SaveAs("fig/prelim/FMS_ANplot_1GeVpT_SE_5pt_12np.pdf");
	//ANplot->SaveAs("fig/prelim/FMS_ANplot_1GeVpT_SE_5pt_12np.png");
	//ANplot->SaveAs("fig/prelim/FMS_ANplot_1GeVpT_SE_5pt_12np.root");
	ANplot->SaveAs("fig/PLBpaperplot/Fig6.pdf");


}
