
void CanvasPartition(TCanvas *C,const Int_t Nx,const Int_t Ny,
                     Float_t lMargin, Float_t rMargin,
                     Float_t bMargin, Float_t tMargin)
{
   if (!C) return;
 
   // Setup Pad layout:
   Float_t vSpacing = 0.0;
   Float_t vStep  = (1.- bMargin - tMargin - (Ny-1) * vSpacing) / Ny;
 
   Float_t hSpacing = 0.0;
   Float_t hStep  = (1.- lMargin - rMargin - (Nx-1) * hSpacing) / Nx;
 
   Float_t vposd,vposu,vmard,vmaru,vfactor;
   Float_t hposl,hposr,hmarl,hmarr,hfactor;
 
   for (Int_t i=0;i<Nx;i++) {
 
      if (i==0) {
         hposl = 0.0;
         hposr = lMargin + hStep;
         hfactor = hposr-hposl;
         hmarl = lMargin / hfactor;
         hmarr = 0.0;
      } else if (i == Nx-1) {
         hposl = hposr + hSpacing;
         hposr = hposl + hStep + rMargin;
         hfactor = hposr-hposl;
         hmarl = 0.0;
         hmarr = rMargin / (hposr-hposl);
      } else {
         hposl = hposr + hSpacing;
         hposr = hposl + hStep;
         hfactor = hposr-hposl;
         hmarl = 0.0;
         hmarr = 0.0;
      }
 
      for (Int_t j=0;j<Ny;j++) {
 
         if (j==0) {
            vposd = 0.0;
            vposu = bMargin + vStep;
            vfactor = vposu-vposd;
            vmard = bMargin / vfactor;
            vmaru = 0.0;
         } else if (j == Ny-1) {
            vposd = vposu + vSpacing;
            vposu = vposd + vStep + tMargin;
            vfactor = vposu-vposd;
            vmard = 0.0;
            vmaru = tMargin / (vposu-vposd);
         } else {
            vposd = vposu + vSpacing;
            vposu = vposd + vStep;
            vfactor = vposu-vposd;
            vmard = 0.0;
            vmaru = 0.0;
         }
 
         C->cd(0);
 
         auto name = TString::Format("pad_%d_%d",i,j);
         auto pad = (TPad*) C->FindObject(name.Data());
         if (pad) delete pad;
         pad = new TPad(name.Data(),"",hposl,vposd,hposr,vposu);
         pad->SetLeftMargin(hmarl);
         pad->SetRightMargin(hmarr);
         pad->SetBottomMargin(vmard);
         pad->SetTopMargin(vmaru);
 
         pad->SetFrameBorderMode(0);
         pad->SetBorderMode(0);
         pad->SetBorderSize(0);
 
         pad->Draw();
      }
   }
}
 
double XtoPad(double x)
{
   double xl,yl,xu,yu;
   gPad->GetPadPar(xl,yl,xu,yu);
   double pw = xu-xl;
   double lm = gPad->GetLeftMargin();
   double rm = gPad->GetRightMargin();
   double fw = pw-pw*lm-pw*rm;
   return (x*fw+pw*lm)/pw;
}
 
double YtoPad(double y)
{
   double xl,yl,xu,yu;
   gPad->GetPadPar(xl,yl,xu,yu);
   double ph = yu-yl;
   double tm = gPad->GetTopMargin();
   double bm = gPad->GetBottomMargin();
   double fh = ph-ph*bm-ph*tm;
   return (y*fh+bm*ph)/ph;
}






void draw_AN_compare_inc_SD_RG_combined_V2()
{

	gStyle->SetOptStat(0);
	gStyle->SetLineWidth(3);
	gStyle->SetEndErrorSize(8);
	ifstream AN_inc_12np;
	AN_inc_12np.open("/star/data01/pwg/liangxl/BrightSTAR_run15/finalANtext/run15_FMS_inc_12np.txt");
	ifstream AN_SD_12np;
	AN_SD_12np.open("finalANtext/run15_FMS_plot_SD_data_12np_5pt.txt");
	ifstream AN_RG_12np;
	AN_RG_12np.open("finalANtext/run15_FMS_plot_RG_data_12np.txt");
	ifstream AN_inc_3pnp;
	AN_inc_3pnp.open("/star/data01/pwg/liangxl/BrightSTAR_run15/finalANtext/run15_FMS_inc_3pnp.txt");
	ifstream AN_SD_3pnp;
	AN_SD_3pnp.open("finalANtext/run15_FMS_plot_SD_data_3pnp_5pt.txt");
	ifstream AN_RG_3pnp;
	AN_RG_3pnp.open("finalANtext/run15_FMS_plot_RG_data_3pnp.txt");
	//AN_RG_12np.open("run15_FMS_plot_East_data_12np_noconstrain.txt");
	//AN_RG_12np.open("ANtext/Run15FMScase23_EnergyCorrection2_plot.txt");
	char BY;
	double ANSD12nppoint[5], ANRG12nppoint[6], ANSD12nppointun[5],ANSD12np[5],ANSD12npun[5],ANRG12np[6],ANRG12npun[6], ANSD12npsys[5], ANRG12npsys[6], ANRG12nppointun[6];
	double ANRG12nppoint[6], ANRG12nppoint[6], ANRG12nppointun[6],ANRG12np[6],ANRG12npun[6],ANRG12np[6],ANRG12npun[6], ANRG12npsys[6], ANRG12npsys[6], ANRG12nppointun[6];
	double ANinc12nppoint[6], ANinc12nppointun[6],ANinc12np[6],ANinc12npun[6],ANinc12npsys[6];
	double ANSD3pnppoint[5], ANRG3pnppoint[6], ANSD3pnppointun[5],ANSD3pnp[5],ANSD3pnpun[5],ANRG3pnp[6],ANRG3pnpun[6], ANSD3pnpsys[5], ANRG3pnpsys[6], ANRG3pnppointun[6];
	double ANRG3pnppoint[6], ANRG3pnppoint[6], ANRG3pnppointun[6],ANRG3pnp[6],ANRG3pnpun[6],ANRG3pnp[6],ANRG3pnpun[6], ANRG3pnpsys[6], ANRG3pnpsys[6], ANRG3pnppointun[6];
	double ANinc3pnppoint[6], ANinc3pnppointun[6],ANinc3pnp[6],ANinc3pnpun[6],ANinc3pnpsys[6];
	double xPointun[6],Ypoint,Yerror,syserror, ANpointtmp;
	for (int i=0;i<6; i=i+1)
	{

		AN_inc_12np  >> ANinc12nppoint[i] >> ANinc12np[i] >> ANinc12npun[i] >> ANinc12npsys[i];
		if (i<5)
		{
			AN_SD_12np  >> ANSD12nppoint[i] >> ANSD12np[i] >> ANSD12npun[i] >> ANSD12npsys[i];
			AN_SD_12np  >> Ypoint >> ANpointtmp >> Yerror >>  syserror;
			ANSD12nppointun[i]=0.004;
			ANSD12nppoint[i] = ANSD12nppoint[i] - 0.008;

		}
		AN_RG_12np  >> ANRG12nppoint[i] >> ANRG12np[i] >> ANRG12npun[i] >> ANRG12npsys[i];
		AN_RG_12np  >> Ypoint >> ANpointtmp >> Yerror >>  syserror;
		xPointun[i]=0;
		ANinc12nppointun[i]=0.005;
		ANRG12nppointun[i]=0.004;
		ANRG12nppoint[i] = ANRG12nppoint[i] + 0.008;

		AN_inc_3pnp  >> ANinc3pnppoint[i] >> ANinc3pnp[i] >> ANinc3pnpun[i] >> ANinc3pnpsys[i];
		AN_RG_3pnp  >> ANRG3pnppoint[i] >> ANRG3pnp[i] >> ANRG3pnpun[i] >> ANRG3pnpsys[i];
		AN_RG_3pnp  >> Ypoint >> ANpointtmp >> Yerror >>  syserror;
		cout<< "inc: " << ANinc3pnppoint[i] << ANinc3pnpun[i] << ANinc3pnpsys[i] << endl;
		xPointun[i]=0;
		ANinc3pnppointun[i]=0.005;
		ANRG3pnppointun[i]=0.004;
		ANRG3pnppoint[i] = ANRG3pnppoint[i] + 0.008;
		if (i<5)
		{

			AN_SD_3pnp  >> ANSD3pnppoint[i] >> ANSD3pnp[i] >> ANSD3pnpun[i] >> ANSD3pnpsys[i];
			AN_SD_3pnp  >> Ypoint >> ANpointtmp >> Yerror >>  syserror;
			ANSD3pnppointun[i]=0.004;
			ANSD3pnppoint[i] = ANSD3pnppoint[i] - 0.008;
		}

	}

	TGraphErrors *AN_inc_12np_Graph;
	TGraphErrors *AN_SD_12np_Graph;
	TGraphErrors *AN_RG_12np_Graph;
	TGraphErrors *AN_inc_12np_Graph_Sys;
	TGraphErrors *AN_SD_12np_Graph_Sys;
	TGraphErrors *AN_RG_12np_Graph_Sys;
	AN_inc_12np_Graph = new TGraphErrors(6,ANinc12nppoint,ANinc12np,xPointun,ANinc12npun);
	AN_SD_12np_Graph = new TGraphErrors(5,ANSD12nppoint,ANSD12np,xPointun,ANSD12npun);
	AN_RG_12np_Graph = new TGraphErrors(6,ANRG12nppoint,ANRG12np,xPointun,ANRG12npun);

	AN_inc_12np_Graph_Sys = new TGraphErrors(6,ANinc12nppoint,ANinc12np,ANinc12nppointun,ANinc12npsys);
	AN_SD_12np_Graph_Sys = new TGraphErrors(5,ANSD12nppoint,ANSD12np,ANSD12nppointun,ANSD12npsys);
	AN_RG_12np_Graph_Sys = new TGraphErrors(6,ANRG12nppoint,ANRG12np,ANRG12nppointun,ANRG12npsys);
	
	TGraphErrors *AN_inc_3pnp_Graph;
	TGraphErrors *AN_SD_3pnp_Graph;
	TGraphErrors *AN_RG_3pnp_Graph;
	TGraphErrors *AN_inc_3pnp_Graph_Sys;
	TGraphErrors *AN_SD_3pnp_Graph_Sys;
	TGraphErrors *AN_RG_3pnp_Graph_Sys;
	AN_inc_3pnp_Graph = new TGraphErrors(6,ANinc3pnppoint,ANinc3pnp,xPointun,ANinc3pnpun);
	AN_SD_3pnp_Graph = new TGraphErrors(5,ANSD3pnppoint,ANSD3pnp,xPointun,ANSD3pnpun);
	AN_RG_3pnp_Graph = new TGraphErrors(6,ANRG3pnppoint,ANRG3pnp,xPointun,ANRG3pnpun);

	AN_inc_3pnp_Graph_Sys = new TGraphErrors(6,ANinc3pnppoint,ANinc3pnp,ANinc3pnppointun,ANinc3pnpsys);
	AN_SD_3pnp_Graph_Sys = new TGraphErrors(5,ANSD3pnppoint,ANSD3pnp,ANSD3pnppointun,ANSD3pnpsys);
	AN_RG_3pnp_Graph_Sys = new TGraphErrors(6,ANRG3pnppoint,ANRG3pnp,ANRG3pnppointun,ANRG3pnpsys);
	

	//TCanvas *ANplot = new TCanvas("ANPlot","",200,10,1024,768);
        //ANplot->DrawFrame(2., -0.06, 250., 0.2);
	TH2D * htemp = new TH2D("temp","",8,0.14,0.45,30,-0.079,0.099);
        htemp->GetYaxis()->SetTitleOffset(0.9);
        htemp->GetXaxis()->SetTitle("x_{F}");
        htemp->GetYaxis()->SetTitle("A_{N}");
	TH2D * htemp2 = new TH2D("temp","",8,0.14,0.45,30,-0.079,0.079);
        htemp2->GetYaxis()->SetTitleOffset(0.9);
        htemp2->GetXaxis()->SetTitle("x_{F}");
        htemp2->GetYaxis()->SetTitle("A_{N}");
        //htemp->Draw();
        AN_inc_12np_Graph->SetMarkerColor(kRed+1);
	AN_inc_12np_Graph->SetLineWidth(2);
        AN_inc_12np_Graph->SetMarkerSize(2);
        AN_inc_12np_Graph->SetMarkerStyle(20);
	AN_inc_12np_Graph->SetLineColor(kRed+1);
        AN_SD_12np_Graph->SetMarkerColor(kBlue+1);
	AN_SD_12np_Graph->SetLineWidth(2);
        AN_SD_12np_Graph->SetMarkerSize(2);
        AN_SD_12np_Graph->SetMarkerStyle(22);
	AN_SD_12np_Graph->SetLineColor(kBlue+1);
        AN_RG_12np_Graph->SetMarkerColor(kMagenta+3);
	AN_RG_12np_Graph->SetLineWidth(2);
        AN_RG_12np_Graph->SetMarkerSize(2);
	AN_RG_12np_Graph->SetLineColor(kMagenta+3);
        AN_RG_12np_Graph->SetMarkerStyle(33);
	AN_inc_12np_Graph_Sys->SetMarkerColor(kRed+1);
	AN_inc_12np_Graph_Sys->SetMarkerSize(2);
        AN_inc_12np_Graph_Sys->SetMarkerStyle(28);
	AN_inc_12np_Graph_Sys->SetLineColor(kRed+1);
	AN_inc_12np_Graph_Sys->SetLineWidth(2);
	AN_inc_12np_Graph_Sys->SetFillStyle(0);
	AN_SD_12np_Graph_Sys->SetMarkerColor(kBlue+1);
	AN_SD_12np_Graph_Sys->SetMarkerSize(2);
        AN_SD_12np_Graph_Sys->SetMarkerStyle(22);
	AN_SD_12np_Graph_Sys->SetLineColor(kBlue+1);
	AN_SD_12np_Graph_Sys->SetLineWidth(2);
	AN_SD_12np_Graph_Sys->SetFillStyle(0);
	AN_RG_12np_Graph_Sys->SetMarkerColor(kMagenta+3);
	AN_RG_12np_Graph_Sys->SetMarkerSize(2);
	AN_RG_12np_Graph_Sys->SetLineColor(kMagenta+3);
        AN_RG_12np_Graph_Sys->SetMarkerStyle(33);
	AN_RG_12np_Graph_Sys->SetLineWidth(2);
	AN_RG_12np_Graph_Sys->SetFillStyle(0);

        AN_inc_3pnp_Graph->SetMarkerColor(kRed+1);
	AN_inc_3pnp_Graph->SetLineWidth(2);
        AN_inc_3pnp_Graph->SetMarkerSize(2);
        AN_inc_3pnp_Graph->SetMarkerStyle(20);
	AN_inc_3pnp_Graph->SetLineColor(kRed+1);
        AN_SD_3pnp_Graph->SetMarkerColor(kBlue+1);
	AN_SD_3pnp_Graph->SetLineWidth(2);
        AN_SD_3pnp_Graph->SetMarkerSize(2);
        AN_SD_3pnp_Graph->SetMarkerStyle(22);
	AN_SD_3pnp_Graph->SetLineColor(kBlue+1);
        AN_RG_3pnp_Graph->SetMarkerColor(kMagenta+3);
	AN_RG_3pnp_Graph->SetLineWidth(2);
        AN_RG_3pnp_Graph->SetMarkerSize(2);
	AN_RG_3pnp_Graph->SetLineColor(kMagenta+3);
        AN_RG_3pnp_Graph->SetMarkerStyle(33);
	AN_inc_3pnp_Graph_Sys->SetMarkerColor(kRed+1);
	AN_inc_3pnp_Graph_Sys->SetMarkerSize(2);
        AN_inc_3pnp_Graph_Sys->SetMarkerStyle(28);
	AN_inc_3pnp_Graph_Sys->SetLineColor(kRed+1);
	AN_inc_3pnp_Graph_Sys->SetLineWidth(2);
	AN_inc_3pnp_Graph_Sys->SetFillStyle(0);
	//AN_inc_3pnp_Graph_Sys->SetFillStyle(3001);
	//AN_inc_3pnp_Graph_Sys->SetFillColorAlpha(28,0.5);
	AN_SD_3pnp_Graph_Sys->SetMarkerColor(kBlue+1);
	AN_SD_3pnp_Graph_Sys->SetMarkerSize(2);
        AN_SD_3pnp_Graph_Sys->SetMarkerStyle(22);
	AN_SD_3pnp_Graph_Sys->SetLineColor(kBlue+1);
	AN_SD_3pnp_Graph_Sys->SetLineWidth(2);
	AN_SD_3pnp_Graph_Sys->SetFillStyle(0);
	//AN_SD_3pnp_Graph_Sys->SetFillStyle(3001);
	//AN_SD_3pnp_Graph_Sys->SetFillColorAlpha(28,0.5);
	AN_RG_3pnp_Graph_Sys->SetMarkerColor(kMagenta+3);
	AN_RG_3pnp_Graph_Sys->SetMarkerSize(2);
	AN_RG_3pnp_Graph_Sys->SetLineColor(kMagenta+3);
        AN_RG_3pnp_Graph_Sys->SetMarkerStyle(33);
	AN_RG_3pnp_Graph_Sys->SetLineWidth(2);
	AN_RG_3pnp_Graph_Sys->SetFillStyle(0);
	//AN_RG_3pnp_Graph_Sys->SetFillStyle(3001);
	//AN_RG_3pnp_Graph_Sys->SetFillColorAlpha(28,0.5);




        TLine *line1 = new TLine(0.14, 0, 0.45, 0);
        line1->SetLineStyle(7);
        line1->SetLineWidth(3);
        //line1->Draw("same");

	//

	//ANplot->SaveAs("Energy_correction_compare.pdf");


	TCanvas *C = (TCanvas*) gROOT->FindObject("C");
	C = new TCanvas("C","canvas",840,1024);
	C->SetFillStyle(4000);
	const Int_t Nx = 1;
	const Int_t Ny = 2;

	Float_t lMargin = 0.10;
	Float_t rMargin = 0.05;
	Float_t bMargin = 0.07;
	Float_t tMargin = 0.07;

	CanvasPartition(C,Nx,Ny,lMargin,rMargin,bMargin,tMargin);
	TPad *pad[Nx][Ny];
	
	for (Int_t i=0; i<Nx;i++)
	{


		for (Int_t j=0; j<Ny;j++)
		{

			C->cd(0);
			char pname[64];
			sprintf(pname,"pad_%i_%i",i,j);
			pad[i][j] = (TPad*) gROOT->FindObject(pname);
			pad[i][j]->Draw();
			pad[i][j]->SetFillStyle(4000);
			pad[i][j]->SetFrameFillStyle(4000);
			pad[i][j]->SetTicks();
			pad[i][j]->cd();

			Float_t xFactor = pad[0][0]->GetAbsWNDC()/pad[i][j]->GetAbsWNDC();
			Float_t yFactor = pad[0][0]->GetAbsHNDC()/pad[i][j]->GetAbsHNDC();
			if (j==1) {TH2D *hFrame = (TH2D*)htemp->Clone();} 
			if (j==0) {TH2D *hFrame = (TH2D*)htemp2->Clone();} 
			hFrame->Reset();
         		// Format for y axis
         		hFrame->GetYaxis()->SetLabelFont(43);
         		hFrame->GetYaxis()->SetLabelSize(25);
         		hFrame->GetYaxis()->SetLabelOffset(0.02);
         		hFrame->GetYaxis()->SetTitleFont(43);
         		hFrame->GetYaxis()->SetTitleSize(25);
         		hFrame->GetYaxis()->SetTitleOffset(1.5);
 
         		hFrame->GetYaxis()->CenterTitle();
         		hFrame->GetYaxis()->SetNdivisions(505);
 
         		// TICKS Y Axis
         		hFrame->GetYaxis()->SetTickLength(xFactor*0.04/yFactor);
 
         		// Format for x axis
         		hFrame->GetXaxis()->SetLabelFont(43);
         		hFrame->GetXaxis()->SetLabelSize(25);
         		hFrame->GetXaxis()->SetLabelOffset(0.02);
         		hFrame->GetXaxis()->SetTitleFont(43);
         		hFrame->GetXaxis()->SetTitleSize(29);
         		hFrame->GetXaxis()->SetTitleOffset(1);
         		////hFrame->GetXaxis()->CenterTitle();
         		hFrame->GetXaxis()->SetNdivisions(505);
 
         		// TICKS X Axis
         		//hFrame->GetXaxis()->SetTickLength(yFactor*0.06/xFactor);
			hFrame->Draw();

			if (j==1)
			{

        			 AN_RG_12np_Graph->Draw("Psame");
				 AN_RG_12np_Graph_Sys->Draw("e5 same");
        			 AN_SD_12np_Graph->Draw("Psame");
				 AN_SD_12np_Graph_Sys->Draw("e5 same");
        			 AN_inc_12np_Graph->Draw("Psame");
				 AN_inc_12np_Graph_Sys->Draw("e5 same");
        			line1->Draw("same");
				TLatex T5;
        			T5.SetTextAlign(11);
        			T5.SetTextSize(0.07);
   				T5.DrawLatex(0.2,0.082,"Photon multiplicity = 1 or 2");
				T5->Draw("same");
				TLegend *leg = new TLegend(0.10,0.03,0.68,0.200);
        			leg->SetTextSize(0.04);
				leg->SetFillStyle(0);
        			leg->AddEntry(AN_inc_3pnp_Graph,"Inclusive process","p");
        			leg->AddEntry(AN_RG_3pnp_Graph,"Rapidity Gap event (shifted by +0.008 along the horizontal axis)","p");
        			leg->AddEntry(AN_SD_3pnp_Graph,"Single Diffractive process (shifted by -0.008 along the horizontal axis)","p");
        			leg->SetBorderSize(0);
        			leg->Draw("same");


			}
			if (j==0)
			{


        			 AN_RG_3pnp_Graph->Draw("Psame");
				 AN_RG_3pnp_Graph_Sys->Draw("e5 same");
        			 AN_SD_3pnp_Graph->Draw("Psame");
				 AN_SD_3pnp_Graph_Sys->Draw("e5 same");
        			 AN_inc_3pnp_Graph->Draw("Psame");
				 AN_inc_3pnp_Graph_Sys->Draw("e5 same");
        			line1->Draw("same");
				TLatex T4;
        			T4.SetTextAlign(11);
        			T4.SetTextSize(0.07);
   				T4.DrawLatex(0.22,0.065,"Photon multiplicity #geq 3");
				T4->Draw("same");

				TLatex T1;
				T1.SetTextAlign(11);
   				T1.SetTextSize(0.057);
				T1.SetTextColor(kRed);
				T1.DrawLatex(0.16,-0.055,"STAR");
				T1->Draw("same");
				TLatex T2;
        			T2.SetTextAlign(11);
        			T2.SetTextSize(0.052);
        			T2.SetTextColor(kBlack);
   				T2.DrawLatex(0.16,-0.064,"p^{#uparrow} + p @ 200 GeV");
   				T2.DrawLatex(0.16,-0.073,"3.0\% polarization scale uncertainty not shown");
				T2->Draw("same");

				TLatex T9;
        			T9.SetTextAlign(11);
        			T9.SetTextSize(0.042);
        			T9.SetTextColor(kBlack);
   				T9.DrawLatex(0.29,-0.034,"15 < E^{EM-jet} <  100 GeV");
   				T9.DrawLatex(0.29,-0.044,"2.8 < #eta^{EM-jet} < 3.8");
   				T9.DrawLatex(0.29,-0.054,"p^{EM-jet}_{T} > 2.0 GeV/c");
				T9->Draw("same");

			}
			//if (j==2)
			//{



			//	TLatex T3;
        		//	T3.SetTextAlign(11);
        		//	T3.SetTextSize(0.06);
   			//	T3.DrawLatex(0.25,0.092,"All photon multiplicity");
			//	T3->Draw("same");

			//	line1->Draw("same");

			//}


		}

	}
	//C->SaveAs("fig/prelim/Compare_inc_SD_RG_12np_3pnp_combined.pdf");
	C->SaveAs("fig/PLBpaperplot/Fig5.pdf");
	//C->SaveAs("fig/prelim/Compare_diff_east_all_12np_3pnp.png");


}
