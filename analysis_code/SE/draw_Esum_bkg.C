void draw_Esum_bkg()
{

	Double_t Nsig, Nbkg, frac, frac_bkg,NsigSum, NbkgSum , frac_Err, N_stat;
	Double_t Num[3];

	ofstream Frac_file;
	ofstream Frac_sys;
	NsigSum = 0; NbkgSum = 0; N_stat = 0;
	Frac_file.open("ANtext/frac_SE.txt");
	Frac_sys.open("ANtext/frac_sys_SE.txt");
	 //draw_Esum_bkg_xF(26,39,0 , Nsig, Nbkg)   ; 
	 //draw_Esum_bkg_xF(11,16,0 , Num)   ; 
	 //frac = 1.0 * Num[1] / (Num[0] + Num[1]);
	 //frac_bkg = 1 - frac;
	 //frac_Err = 1.0 * Num[2] / (Num[0] + Num[1]);
	 //cout << frac << "	"<< frac_Err << endl; 
	 //NsigSum = NsigSum + Num[1];
	 //NbkgSum = NbkgSum + Num[0];
	 //N_stat = N_stat + Num[2];
	 //Frac_file << frac <<"	"<< frac_Err << endl; 
	 draw_Esum_bkg_xF(16,21,1 , Num)   ;
	 frac = 1.0 * Num[1] / (Num[0] + Num[1]);
	 frac_bkg = 1 - frac;
	 frac_Err = 1.0 * Num[2] / (Num[0] + Num[1]);
	 cout << frac << "	"<< frac_Err << endl; 
	 NsigSum = NsigSum + Num[1];
	 NbkgSum = NbkgSum + Num[0];
	 N_stat = N_stat + Num[2];
	 frac = 1.0 * NsigSum / (NbkgSum + NsigSum);
	 frac_bkg = 1 - frac;
	 frac_Err = 1.0 * N_stat / (NsigSum + NbkgSum);
	 Frac_file << frac <<"	"<< frac_Err << endl; 
	 Frac_sys << frac_bkg << endl; 
	 draw_Esum_bkg_xF(21,26,2 , Num)   ;
	 frac = 1.0 * Num[1] / (Num[0] + Num[1]);
	 frac_bkg = 1 - frac;
	 frac_Err = 1.0 * Num[2] / (Num[0] + Num[1]);
	 cout << frac << "	"<< frac_Err << endl; 
	 Frac_file << frac <<"	"<< frac_Err << endl; 
	 Frac_sys << frac_bkg << endl; 
	 draw_Esum_bkg_xF(26,31,3 , Num)   ;
	 frac = 1.0 * Num[1] / (Num[0] + Num[1]);
	 frac_bkg = 1 - frac;
	 cout << frac << "	"<< frac_Err << endl; 
	 Frac_file << frac <<"	"<< frac_Err << endl; 
	 Frac_sys << frac_bkg << endl; 
	 //NsigSum = NsigSum + Num[1];
	 //NbkgSum = NbkgSum + Num[0];
	 //N_stat = N_stat + Num[2];
	 //frac = 1.0 * Num[1] / (Num[0] + Num[1]);
	 //frac_Err = 1.0 * sqrt(Num[0]) / (Num[0] + Num[1]);
	 //cout << frac << "	"<< frac_Err << endl; 
	 //Frac_file << frac <<"	"<< frac_Err << endl; 
	 draw_Esum_bkg_xF(31,36,4 , Num)   ;
	 //NsigSum = NsigSum + Num[1];
	 //NbkgSum = NbkgSum + Num[0];
	 //N_stat = N_stat + Num[2];
	 frac = 1.0 * Num[1] / (Num[0] + Num[1]);
	 frac_bkg = 1 - frac;
	 cout << frac << "	"<< frac_Err << endl; 
	 Frac_file << frac <<"	"<< frac_Err << endl; 
	 Frac_sys << frac_bkg << endl; 
	 draw_Esum_bkg_xF(36,41,5, Num)  ;
	 frac = 1.0 * Num[1] / (Num[0] + Num[1]);
	 frac_bkg = 1 - frac;
	 //NsigSum = NsigSum + Num[1];
	 //NbkgSum = NbkgSum + Num[0];
	 //N_stat = N_stat + Num[2];
	 cout << frac << "	"<< frac_Err << endl; 
	 Frac_file << frac <<"	"<< frac_Err << endl; 
	 Frac_sys << frac_bkg << endl; 
	 draw_Esum_bkg_xF(41,46,6, Num) ;
	 frac = 1.0 * Num[1] / (Num[0] + Num[1]);
	 frac_bkg = 1 - frac;
	 //NsigSum = NsigSum + Num[1];
	 //NbkgSum = NbkgSum + Num[0];
	 //N_stat = N_stat + Num[2];
	 cout << frac << "	"<< frac_Err << endl; 
	 Frac_file << frac <<"	"<< frac_Err << endl; 
	 Frac_sys << frac_bkg << endl; 

	 //frac = 1.0 * NsigSum / (NbkgSum + NsigSum);
	 //frac_Err = 1.0 * N_stat / (NsigSum + NbkgSum);
	 //cout << "4 last bins: "<< (NbkgSum + NsigSum) << "	"<< NsigSum << "	" << NbkgSum <<"	"  << frac << "	"<< frac_Err << endl; 
	 //Frac_file << frac <<"	"<< frac_Err << endl; 

}


void draw_Esum_bkg_xF(Int_t lowbin, Int_t upbin, Int_t xFbin , Double_t Num[])
{


	gStyle->SetOptStat(0);

	TFile *Finc =TFile::Open("/star/data01/pwg/liangxl/BrightSTAR_run15/root_result/Run15FMSIncAna/Run15FMSXFCalc_AnaAll6.root");
	TFile *Fzero=TFile::Open("/star/data01/pwg/liangxl/BrightSTAR_EMjet/root_result/FmsQaByFill/FmsQaFill_ZerobiasAll_1113.root"); //
	TFile *Fana =TFile::Open("root_result/Run15FMSWestAna/Run15FMSXFCalc_AnaAll.root");// 
	



	TH1D *inc_jet = Finc->Get("h1E");
	TH1D *zerobias_RP = Fzero->Get("h1_wRpP_passcut");

	zerobias_RP->RebinX(2);

	Int_t Nmax_jet = inc_jet->GetNbinsX();
	Int_t Nmax_RP  = zerobias_RP->GetNbinsX();

	Double_t sum_yield = inc_jet->Integral(lowbin,upbin);
	Double_t sum_ene_bkg[120], sum_ene_bkg_yield[120] , sum_ene_bkg_sigma2[120] , sum_ene_bkg_statfrac[120];
	Double_t frac,Y_jet,Y_RP;
	Double_t stat_frac;
	Double_t Ntot, NsigIn, NbkgIn, frac_sig, frac_bkg, Nbkg_Err; 
	int Esumcut_low, Esumcut_up;
	Int_t jmax, jmin;
	Double_t xFl,xFr;
	if (xFbin == 0) {xFl=0.1 ; xFr=0.15;TH1D *Esum_ana = Fana->Get("h1_sumEwest_XF1015");}
	if (xFbin == 1) {xFl=0.15; xFr=0.2 ;TH1D *Esum_ana = Fana->Get("h1_sumEwest_XF1520");}
	if (xFbin == 2) {xFl=0.2 ; xFr=0.25;TH1D *Esum_ana = Fana->Get("h1_sumEwest_XF2025");}
	if (xFbin == 3) {xFl=0.25; xFr=0.3 ;TH1D *Esum_ana = Fana->Get("h1_sumEwest_XF2530");}
	if (xFbin == 4) {xFl=0.3 ; xFr=0.35;TH1D *Esum_ana = Fana->Get("h1_sumEwest_XF3035");}
	if (xFbin == 5) {xFl=0.35; xFr=0.4 ;TH1D *Esum_ana = Fana->Get("h1_sumEwest_XF3540");}
	if (xFbin == 6) {xFl=0.4 ; xFr=0.45;TH1D *Esum_ana = Fana->Get("h1_sumEwest_XF4045");}

	//Esum_ana->RebinX(2);

	for (int i=0;i<120;i++) {sum_ene_bkg[i]=0; sum_ene_bkg_yield[i]=0; sum_ene_bkg_sigma2[i]=0; sum_ene_bkg_statfrac[i]=0;}

	for (int i=lowbin; i<=upbin; i++)
	{

		Y_jet = inc_jet->GetBinContent(i);
		frac  = 1.0 * Y_jet / sum_yield;
		cout << "jet yield:" << Y_jet << "  frac:"<<frac<<endl;
		jmax = 182 - i;
		if (jmax > 120) jmax = 120;
		jmin = 62 - i;
		if (jmin <=0) continue;

		//cout << "jmin:" << jmin << "jmax:" << jmax << endl;
		for (int j=jmin ; j<=jmax ; j++)
		{

			Y_RP = zerobias_RP->GetBinContent(j-40);
			if (Y_RP <0) Y_RP = 0;
			sum_ene_bkg[i+j-62]= frac * Y_RP + sum_ene_bkg[i+j-62];
			sum_ene_bkg_yield[i+j-62] = Y_jet * Y_RP + sum_ene_bkg_yield[i+j-62]; 
			sum_ene_bkg_sigma2[i+j-62] = sum_ene_bkg_sigma2[i+j-62] + pow(Y_jet,2) * Y_RP + pow(Y_RP,2) * Y_jet;

		}

			
	}


	//Oleg's idea
	//TH1D *h1_ratio = (TH1D*)zerobias_RP->Clone("h1_ratio");
	//h1_ratio->Rebin(4);


	//TH1D *Tbkg = new TH1D("Tbkg",Form("Esum background (%d < x_{F} < %d);E Sum (GeV)",xFl,xFr),280,120.,400.);
	TH1D *Tbkg = new TH1D("Tbkg","Esum background ;E Sum (GeV)",120,60.,180.);
	TH1D *Tbkg_un = new TH1D("Tbkg_un","Esum background stat un;E Sum (GeV)",120,60.,180.);

	Double_t Esum_xaxis[120];

	for (int i=0; i<120;i=i+1) 
	{
		Esum_xaxis[i] = i+60; 
		Tbkg->Fill(i+60,sum_ene_bkg[i]); 
		stat_frac=0;
		if (sum_ene_bkg[i] == 0) {Tbkg_un->Fill(i+60,0);} else {stat_frac = 1.0 * sqrt(sum_ene_bkg_sigma2[i]) / sum_ene_bkg_yield[i]; Tbkg_un->Fill(i+60,(stat_frac * sum_ene_bkg[i]));}
		//cout << (i+120) << "	yield:" << sum_ene_bkg_yield[i] << "	stat:" << sqrt(sum_ene_bkg_sigma2[i]) << endl;
		//cout << (i+120) << "	stat frac:" << stat_frac << endl;

	}

	TGraph *Gbkg = new TGraph(120,Esum_xaxis,sum_ene_bkg);
	Tbkg->SaveAs(Form("fig/QA_west/Esum_bkg_%i.root",xFbin));
	Tbkg->SaveAs(Form("fig/QA_west/Esum_bkg_%i.pdf",xFbin));

	TCanvas *ANplot = new TCanvas("ANPlot","",1024,768);
	ANplot->DrawFrame(2., -0.06, 250., 0.2);
	TH2D *temp = new TH2D("tmp","Esum distribution",120,60.,180.,200,0.,(1.1*Esum_ana->GetMaximum()));
	temp->GetYaxis()->SetTitle("yield");
	temp->GetYaxis()->SetTitleOffset(0.9);
	temp->GetXaxis()->SetTitle("E sum [GeV]");
	if (xFbin == 0) {temp->SetTitle("Esum distribution for 0.1  < x_{F} < 0.15");}
	if (xFbin == 1) {temp->SetTitle("Esum distribution for 0.15 < x_{F} < 0.2 ");}
	if (xFbin == 2) {temp->SetTitle("Esum distribution for 0.2  < x_{F} < 0.25");}
	if (xFbin == 3) {temp->SetTitle("Esum distribution for 0.25 < x_{F} < 0.3 ");}
	if (xFbin == 4) {temp->SetTitle("Esum distribution for 0.3  < x_{F} < 0.35");}
	if (xFbin == 5) {temp->SetTitle("Esum distribution for 0.35 < x_{F} < 0.4 ");}
	if (xFbin == 6) {temp->SetTitle("Esum distribution for 0.4  < x_{F} < 0.45");}
	temp->Draw();

	Esum_ana->SetLineColor(2);
	Esum_ana->SetLineWidth(2);
	Esum_ana->Draw("same");

	if (xFbin == 0) {Esumcut_low=0; Esumcut_up=45;}
	if (xFbin == 1) {Esumcut_low=0; Esumcut_up=45;}
	if (xFbin == 2) {Esumcut_low=0; Esumcut_up=50;}
	if (xFbin == 3) {Esumcut_low=0; Esumcut_up=50;}
	if (xFbin == 4) {Esumcut_low=0; Esumcut_up=55;}
	if (xFbin == 5) {Esumcut_low=0; Esumcut_up=55;}
	if (xFbin == 6) {Esumcut_low=0; Esumcut_up=60;}

	cout << "Esumcut_up: " << Esumcut_up << endl;
	Double_t maxbkg = 0;
	for (int i=Esumcut_up+1; i <= 120; i++) {  if (Esum_ana->GetBinContent(i) > maxbkg) {maxbkg = Esum_ana->GetBinContent(i);}}
	cout << "max background: " << maxbkg << endl;

	Double_t scale= 1.0 * maxbkg / (Tbkg->GetMaximum());
	//cout << "Max bkg = " << (Tbkg->GetMaximum()) << endl;
	cout << "scale = " << scale << endl;
	Tbkg->Scale(scale);
	Tbkg_un->Scale(scale);
	Tbkg->Draw("same");
	ANplot->SaveAs(Form("fig/QA_west/Esum_scale_%i.root",xFbin));
	ANplot->SaveAs(Form("fig/QA_west/Esum_scale_%i.pdf",xFbin));
	//ANplot->SaveAs(Form("Esum_scale_12np_%i.root",xFbin));
	//ANplot->SaveAs(Form("Esum_scale_12np_%i.pdf",xFbin));

	Ntot= Esum_ana->Integral(Esumcut_low, Esumcut_up);
	
	NbkgIn= Tbkg->Integral(Esumcut_low, Esumcut_up );
	Nbkg_Err = Tbkg_un->Integral(Esumcut_low, Esumcut_up );
	//NbkgIn= Tbkg->IntegralAndError(Esumcut_low, Esumcut_up , Nbkg_Err);
	//Nbkg_Err = Tbkg->IntegralAndError(Esumcut_low, Esumcut_up);
	NsigIn= Ntot - NbkgIn; 
	Num[0] = NbkgIn;
	Num[1] = NsigIn;
	Num[2] = Nbkg_Err;
	frac_bkg = 1.0 * NbkgIn / Ntot;
	frac_sig = 1.0 - frac_bkg;
	cout << xFbin << "	Ntot:" << Ntot << "	Nsig:" << NsigIn << "	Nbkg:"<< NbkgIn << "	frac_sig:" << frac_sig << "	frac_bkg:" << frac_bkg << endl;
	cout << xFbin << "	bkg Integral Error:" << Nbkg_Err << endl;

}
