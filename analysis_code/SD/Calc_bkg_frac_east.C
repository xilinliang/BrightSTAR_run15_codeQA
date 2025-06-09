void Calc_bkg_frac_east()
{


	gStyle->SetOptStat(0);
	TFile *file_SD = TFile::Open("root_result/Run15FMSEastAna/Run15FMSXFCalc_AnaAll.root");
	TFile *file_RG = TFile::Open("root_result/Run15FMSEastAna/Run15FMSXFCalc_RGAll.root");

	TH1D *SD_1020 = file_SD->Get("h1_xF_1020");
	TH1D *SD_2025 = file_SD->Get("h1_xF_2025");
	TH1D *SD_2530 = file_SD->Get("h1_xF_2530");
	TH1D *SD_3035 = file_SD->Get("h1_xF_3035");
	TH1D *SD_3540 = file_SD->Get("h1_xF_3540");
	TH1D *SD_4045 = file_SD->Get("h1_xF_4045");
	TH1D *RG_1020 = file_RG->Get("h1_xF_1020");
	TH1D *RG_2025 = file_RG->Get("h1_xF_2025");
	TH1D *RG_2530 = file_RG->Get("h1_xF_2530");
	TH1D *RG_3035 = file_RG->Get("h1_xF_3035");
	TH1D *RG_3540 = file_RG->Get("h1_xF_3540");
	TH1D *RG_4045 = file_RG->Get("h1_xF_4045");

	TH1D *SD_1020_12np = file_SD->Get("h1_xF_1020_12np");
	TH1D *SD_2025_12np = file_SD->Get("h1_xF_2025_12np");
	TH1D *SD_2530_12np = file_SD->Get("h1_xF_2530_12np");
	TH1D *SD_3035_12np = file_SD->Get("h1_xF_3035_12np");
	TH1D *SD_3540_12np = file_SD->Get("h1_xF_3540_12np");
	TH1D *SD_4045_12np = file_SD->Get("h1_xF_4045_12np");
	TH1D *RG_1020_12np = file_RG->Get("h1_xF_1020_12np");
	TH1D *RG_2025_12np = file_RG->Get("h1_xF_2025_12np");
	TH1D *RG_2530_12np = file_RG->Get("h1_xF_2530_12np");
	TH1D *RG_3035_12np = file_RG->Get("h1_xF_3035_12np");
	TH1D *RG_3540_12np = file_RG->Get("h1_xF_3540_12np");
	TH1D *RG_4045_12np = file_RG->Get("h1_xF_4045_12np");

	TH1D *SD_1020_3pnp = file_SD->Get("h1_xF_1020_3pnp");
	TH1D *SD_2025_3pnp = file_SD->Get("h1_xF_2025_3pnp");
	TH1D *SD_2530_3pnp = file_SD->Get("h1_xF_2530_3pnp");
	TH1D *SD_3035_3pnp = file_SD->Get("h1_xF_3035_3pnp");
	TH1D *SD_3540_3pnp = file_SD->Get("h1_xF_3540_3pnp");
	TH1D *SD_4045_3pnp = file_SD->Get("h1_xF_4045_3pnp");
	TH1D *RG_1020_3pnp = file_RG->Get("h1_xF_1020_3pnp");
	TH1D *RG_2025_3pnp = file_RG->Get("h1_xF_2025_3pnp");
	TH1D *RG_2530_3pnp = file_RG->Get("h1_xF_2530_3pnp");
	TH1D *RG_3035_3pnp = file_RG->Get("h1_xF_3035_3pnp");
	TH1D *RG_3540_3pnp = file_RG->Get("h1_xF_3540_3pnp");
	TH1D *RG_4045_3pnp = file_RG->Get("h1_xF_4045_3pnp");

	ofstream frac;
	frac.open("ANtext/frac_east_bkg.txt");
	ofstream frac_12np;
	frac_12np.open("ANtext/frac_east_bkg_12np.txt");
	ofstream frac_3pnp;
	frac_3pnp.open("ANtext/frac_east_bkg_3pnp.txt");

	//ifstream com_sig;
	//com_sig.open("ANtext/Run15FMSfinal_East_result.txt");
	//ifstream com_sig_12np;
	//com_sig_12np.open("ANtext/Run15FMSfinal_12np_East_result.txt");

	Double_t frac_sig, frac_bkg, n_SD, n_RG;
	//Double_t XFpoint, com_sig_AN, com_sig_sta, com_sig_sys, sig_AN, sig_sta, sig_sys, bkg_AN, bkg_sta, bkg_sys;
	//char beam;


	n_SD = SD_1020->GetEntries();
	n_RG = RG_1020->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac << "0.175	" << frac_sig << endl;
	n_SD = SD_2025->GetEntries();
	n_RG = RG_2025->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac << "0.225	" << frac_sig << endl;
	n_SD = SD_2530->GetEntries();
	n_RG = RG_2530->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac << "0.275	" << frac_sig << endl;
	n_SD = SD_3035->GetEntries();
	n_RG = RG_3035->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac << "0.325	" << frac_sig << endl;
	n_SD = SD_3540->GetEntries();
	n_RG = RG_3540->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac << "0.375	" << frac_sig << endl;
	n_SD = SD_4045->GetEntries();
	n_RG = RG_4045->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac << "0.425	" << frac_sig << endl;


	n_SD = SD_1020_12np->GetEntries();
	n_RG = RG_1020_12np->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_12np << "0.175	" << frac_sig << endl;
	n_SD = SD_2025_12np->GetEntries();
	n_RG = RG_2025_12np->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_12np << "0.225	" << frac_sig << endl;
	n_SD = SD_2530_12np->GetEntries();
	n_RG = RG_2530_12np->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_12np << "0.275	" << frac_sig << endl;
	n_SD = SD_3035_12np->GetEntries();
	n_RG = RG_3035_12np->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_12np << "0.325	" << frac_sig << endl;
	n_SD = SD_3540_12np->GetEntries();
	n_RG = RG_3540_12np->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_12np << "0.375	" << frac_sig << endl;
	n_SD = SD_4045_12np->GetEntries();
	n_RG = RG_4045_12np->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_12np << "0.425	" << frac_sig << endl;

	n_SD = SD_1020_3pnp->GetEntries();
	n_RG = RG_1020_3pnp->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_3pnp << "0.175	" << frac_sig << endl;
	n_SD = SD_2025_3pnp->GetEntries();
	n_RG = RG_2025_3pnp->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_3pnp << "0.225	" << frac_sig << endl;
	n_SD = SD_2530_3pnp->GetEntries();
	n_RG = RG_2530_3pnp->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_3pnp << "0.275	" << frac_sig << endl;
	n_SD = SD_3035_3pnp->GetEntries();
	n_RG = RG_3035_3pnp->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_3pnp << "0.325	" << frac_sig << endl;
	n_SD = SD_3540_3pnp->GetEntries();
	n_RG = RG_3540_3pnp->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_3pnp << "0.375	" << frac_sig << endl;
	n_SD = SD_4045_3pnp->GetEntries();
	n_RG = RG_4045_3pnp->GetEntries();
	frac_bkg = 1.0 * 0.002 * n_RG / n_SD;
	frac_sig = 1- frac_bkg;
	frac_3pnp << "0.425	" << frac_sig << endl;



	frac.close();
	frac_12np.close();
	frac_3pnp.close();

}
