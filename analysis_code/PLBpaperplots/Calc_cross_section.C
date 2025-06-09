void Calc_cross_section()
{

    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetOptDate(0);
    gStyle->SetEndErrorSize(10);
	TFile *file_diff =  TFile::Open("root_result/Run15FMSEastAna/Run15FMSXFCalc_AnaAll.root");
	TFile *file_inc =  TFile::Open("root_result/Run15FMSIncAna/Run15FMSXFCalc_AnaAll.root");

	TH1F *h1_xF_diff = file_diff->Get("h1_xF_final"); 
	TH1F *h1_xF_inc = file_inc->Get("h1_xF_final"); 

	Double_t N_diff[5];
	Double_t N_inc[5];
	Double_t term= 1.0 * 0.982 / 0.114 / 0.999;
	Double_t xF[] = {0.225,0.275,0.325,0.375,0.425};
	Double_t XFpointErr[] = {0,0,0,0,0,0,0,0};
	Double_t XFSysBluepointErr[] = {0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002};
	Double_t frac[5];
	Double_t frac_sys[5];
	Double_t frac_stat[5];
	Double_t sum_inc, sum_diff, frac_all, frac_all_sys;
	sum_inc = 0;
	sum_diff = 0;

	for (int i=0; i<5; i++)
	{

		N_diff[i] = h1_xF_diff->GetBinContent(i+3);
		sum_diff = sum_diff + N_diff[i];
		N_inc[i] = h1_xF_inc->GetBinContent(i+3);
		sum_inc = sum_inc + N_inc[i];
		frac[i] = 1.0 * N_diff[i] * term / N_inc[i];
		frac_stat[i] = frac[i] *1.0 * sqrt(1.0 / N_inc[i] + 1.0 / N_diff[i]+ 0.1*0.1/98.2/98.2);
		frac_sys[i] = frac[i] * 1.0 * 0.1193;
		cout << xF[i] << " :  N_diff=" <<  N_diff[i] << "	N_inc=" << N_inc[i] << "	frac=" << frac[i] << endl;

	}

	frac_all = 1.0 * sum_diff * term / sum_inc;
	frac_all_sys = frac_all * 1.0 * 0.1193;
	cout << "Overall :  N_diff=" <<  sum_diff << "	N_inc=" << sum_inc << "	frac=" << frac_all << "	frac sys="<< frac_all_sys << endl;

	TCanvas *ANplot = new TCanvas("ANPlot","",1024,768);
	ANplot->DrawFrame(2., -0.06, 250., 0.2);
	TH2D * temp = new TH2D("temp","frac",5,0.2,0.45,30,0.004,0.0095);
	temp->GetYaxis()->SetTitle("fraction");
  	temp->GetYaxis()->SetTitleOffset(0.9);
  	temp->GetXaxis()->SetTitle("x_{F}");
  	temp->Draw();

	TGraphErrors *CSfrac;
	TGraphErrors *CSfrac_sys;
	CSfrac = new TGraphErrors(5,xF, frac, XFSysBluepointErr, frac_stat); 
	CSfrac->SetName("CSfrac");
	CSfrac->SetTitle("Cross section fraction");
	CSfrac->GetXaxis()->SetTitle("x_{F}");
	CSfrac->GetYaxis()->SetTitle("fraction");
	CSfrac->SetMarkerColor(kBlue+1);
	CSfrac->SetMarkerSize(2);
	CSfrac->SetMarkerStyle(22);
	CSfrac->SetLineWidth(2);
	CSfrac->SetLineColor(kBlue+1);
	CSfrac->Draw("P");

	CSfrac_sys = new TGraphErrors(5,xF, frac, XFSysBluepointErr, frac_sys); 
	CSfrac_sys->SetName("CSfrac");
	CSfrac_sys->SetTitle("Cross section fraction");
	CSfrac_sys->GetXaxis()->SetTitle("x_{F}");
	CSfrac_sys->GetYaxis()->SetTitle("fraction");
	CSfrac_sys->SetMarkerColor(kBlue+1);
	CSfrac_sys->SetMarkerSize(2);
	CSfrac_sys->SetLineWidth(2);
	CSfrac_sys->SetLineColor(kBlue+1);
	CSfrac_sys->SetFillStyle(0);
	CSfrac_sys->SetFillColorAlpha(1,0.5);
	CSfrac_sys->Draw("e5");

    TGaxis::SetMaxDigits(3);
    ANplot->Update();


	TLatex T1;
	T1.SetTextAlign(11);
   	T1.SetTextSize(0.035);
	T1.SetTextColor(kRed);
	T1.DrawLatex(0.36,0.0055,"STAR");
	TLatex T2;
        T2.SetTextAlign(11);
        T2.SetTextSize(0.035);
        T2.SetTextColor(kBlack);
   	T2.DrawLatex(0.36,0.0050,"p^{#uparrow} + p #sqrt{s} = 200 GeV");
   	T2.DrawLatex(0.36,0.0045,"fraction = #frac{#sigma_{SD}}{#sigma_{inc}}");

	ANplot->SaveAs("fig/PLBpaperplot/Fig4.pdf");

}
