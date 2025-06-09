void Calc_3pnp_systematic_All_6ptRG()
{

	ifstream com_sig;
	com_sig.open("ANtext/Run15FMSfinal_3pnp_RG_result.txt");
	ifstream SBBC;
	SBBC.open("ANtext/Run15FMSfinal_3pnp_RG_Sys_smallBBC.txt");
	ifstream LBBC;
	LBBC.open("ANtext/Run15FMSfinal_3pnp_RG_Sys_largeBBC.txt");
	ifstream ROF;
	ROF.open("ANtext/Run15FMSfinal_3pnp_RG_Sys_ROF.txt");
	//ifstream Dilution;
	//Dilution.open("ANtext/Run15FMScase23_EnergyCorrectionCompare4.txt");
	//ifstream Esum;
	//Esum.open("ANtext/Run15FMSfinal_RGSys_Esum.txt");
	//ifstream MixBkg;
	//MixBkg.open("frac_sys.txt");

	ofstream resultfile;
	resultfile.open("finalANtext/run15_FMS_plot_RG_data_3pnp.txt");
	ofstream Bsysunfile;
	Bsysunfile.open("finalANtext/run15_FMS_BSystematic_RG_summary_3pnp.txt");
	ofstream Ysysunfile;
	Ysysunfile.open("finalANtext/run15_FMS_YSystematic_RG_summary_3pnp.txt");

	//Double_t fra_bkg = 0.0353;	
	Double_t realAN_sig, realAN_sta , diff, MixEvent_frac, frac;
	Double_t XFpointtmp, com_sig_AN, com_sig_sta, com_sig_sys, sig_AN, sig_sta, sig_sys, bkg_AN, bkg_sta, bkg_sys;
	char beam;

	const int nXFUsed = 6;

	Double_t sum_sys_B;
	Double_t sum_sys_Y;

	sum_sys_B = 0;
	sum_sys_Y = 0;

	Bsysunfile << "Xpoint	small BBC 	large BBC	Ring of Fire	sum" << endl;
	Ysysunfile << "Xpoint	small BBC 	large BBC	Ring of Fire	sum" << endl;


    	TFile *file = TFile::Open("root_result/Run15FMSEastAna/Run15FMSXFCalc_RGAll.root");   
    	TH1D *h1_xF1020;
    	TH1D *h1_xF2025;
    	TH1D *h1_xF2530;
    	TH1D *h1_xF3035;
    	TH1D *h1_xF3540;
    	TH1D *h1_xF4045;
    	h1_xF1020 = (TH1D*) file->Get("h1_xF_1020_3pnp");
    	h1_xF2025 = (TH1D*) file->Get("h1_xF_2025_3pnp");
    	h1_xF2530 = (TH1D*) file->Get("h1_xF_2530_3pnp");
    	h1_xF3035 = (TH1D*) file->Get("h1_xF_3035_3pnp");
    	h1_xF3540 = (TH1D*) file->Get("h1_xF_3540_3pnp");
    	h1_xF4045 = (TH1D*) file->Get("h1_xF_4045_3pnp");
	Double_t XFpoint[6];
	Double_t XFpointYellow[6];
	XFpoint[0] = h1_xF1020->GetMean();
	XFpointYellow[0] = XFpoint[0];
	XFpoint[1] = h1_xF2025->GetMean();
	XFpointYellow[1] = XFpoint[1];
	XFpoint[2] = h1_xF2530->GetMean();
	XFpointYellow[2] = XFpoint[2];
	XFpoint[3] = h1_xF3035->GetMean();
	XFpointYellow[3] = XFpoint[3];
	XFpoint[4] = h1_xF3540->GetMean();
	XFpointYellow[4] = XFpoint[4];
	XFpoint[5] = h1_xF4045->GetMean();
	XFpointYellow[5] = XFpoint[5];

	for (int i=0; i< nXFUsed; i=i+1)
	{

		sum_sys_B = 0;
		com_sig >> beam >> XFpointtmp >> com_sig_AN >> com_sig_sta;
		SBBC >> beam >> XFpointtmp >> diff;
		Bsysunfile << XFpoint[i] <<"	" << diff;
		sum_sys_B = sum_sys_B + diff * diff;
		LBBC >> beam >> XFpointtmp >> diff;
		Bsysunfile <<"	"<<diff;
		sum_sys_B = sum_sys_B + diff * diff;
		ROF >> beam >> XFpointtmp >> diff;
		Bsysunfile <<"	"<<diff;
		sum_sys_B = sum_sys_B + diff * diff;
		sum_sys_B = sqrt(sum_sys_B);
		Bsysunfile <<"  "<<sum_sys_B<<endl;
		cout << "B" << "	" << XFpoint[i] << "	" << sum_sys_B <<endl;
		resultfile << XFpoint[i] << "	" << com_sig_AN <<"	"<< com_sig_sta << "	" << sum_sys_B  <<endl;

		sum_sys_Y = 0;
		com_sig >> beam >> XFpointtmp >> com_sig_AN >> com_sig_sta;
		SBBC >> beam >> XFpointtmp >> diff;
		Ysysunfile << XFpointYellow[i] <<"	" << diff;
		sum_sys_Y = sum_sys_Y + diff * diff;
		LBBC >> beam >> XFpointtmp >> diff;
		Ysysunfile <<"  "<<diff;
		sum_sys_Y = sum_sys_Y + diff * diff;
		ROF >> beam >> XFpointtmp >> diff;
		Ysysunfile <<"  "<<diff;
		sum_sys_Y = sum_sys_Y + diff * diff;
		sum_sys_Y = sqrt(sum_sys_Y);
		Ysysunfile <<"  "<<sum_sys_Y<<endl;
		cout << "Y" << "	" << XFpointYellow[i] << "	" << sum_sys_Y <<endl;
		resultfile << XFpointYellow[i] << "	" << com_sig_AN <<"	"<< com_sig_sta << "	" << sum_sys_Y  <<endl;


	}

}
