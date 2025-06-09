
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






void draw_AN_compare_diff_3mults_RG_combined()
{

	gStyle->SetOptStat(0);
	gStyle->SetLineWidth(3);
	gStyle->SetEndErrorSize(8);
	ifstream AN_all;
	AN_all.open("finalANtext/run15_FMS_plot_RG_data.txt");
	ifstream AN_12np;
	AN_12np.open("finalANtext/run15_FMS_plot_RG_data_12np.txt");
	ifstream AN_3pnp;
	AN_3pnp.open("finalANtext/run15_FMS_plot_RG_data_3pnp.txt");
	//AN_3pnp.open("run15_FMS_plot_East_data_12np_noconstrain.txt");
	//AN_3pnp.open("ANtext/Run15FMScase23_EnergyCorrection2_plot.txt");
	char BY;
	double AN12nppoint[6], AN3pnppoint[6], AN12nppointun[6],AN12np[6],AN12npun[6],AN3pnp[6],AN3pnpun[6], AN12npsys[6], AN3pnpsys[6], AN3pnppointun[6];
	double ANallpoint[6], ANallpointun[6],ANall[6],ANallun[6],ANallsys[6];
	double ANY12nppoint[6], ANY3pnppoint[6], ANY12nppointun[6],ANY12np[6],ANY12npun[6],ANY3pnp[6],ANY3pnpun[6], ANY12npsys[6], ANY3pnpsys[6], ANY3pnppointun[6];
	double ANYallpoint[6], ANYallpointun[6],ANYall[6],ANYallun[6],ANYallsys[6],xPointun[6];
	double Ypoint,Yerror,syserror, ANpointtmp;
	for (int i=0;i<6; i=i+1)
	{

		AN_all  >> ANallpoint[i] >> ANall[i] >> ANallun[i] >> ANallsys[i];
		AN_all  >> ANYallpoint[i] >> ANYall[i] >> ANYallun[i] >> ANYallsys[i];
		AN_12np  >> AN12nppoint[i] >> AN12np[i] >> AN12npun[i] >> AN12npsys[i];
		AN_12np  >> ANY12nppoint[i] >> ANY12np[i] >> ANY12npun[i] >> ANY12npsys[i];
		AN_3pnp  >> AN3pnppoint[i] >> AN3pnp[i] >> AN3pnpun[i] >> AN3pnpsys[i];
		AN_3pnp  >> ANY3pnppoint[i] >> ANY3pnp[i] >> ANY3pnpun[i] >> ANY3pnpsys[i];
		xPointun[i]=0;
		ANallpointun[i]=0.005;
		AN12nppointun[i]=0.005;
		AN3pnppointun[i]=0.005;
		ANYallpointun[i]=0.005;
		ANY12nppointun[i]=0.005;
		ANY3pnppointun[i]=0.005;
		ANYallpoint[i] = ANYallpoint[i] -0.013;
		ANY12nppoint[i] = ANY12nppoint[i] -0.013;
		ANY3pnppoint[i] = ANY3pnppoint[i] -0.013;

	}

	TGraphErrors *AN_all_Graph;
	TGraphErrors *AN_12np_Graph;
	TGraphErrors *AN_3pnp_Graph;
	TGraphErrors *AN_all_Graph_Sys;
	TGraphErrors *AN_12np_Graph_Sys;
	TGraphErrors *AN_3pnp_Graph_Sys;
	AN_all_Graph = new TGraphErrors(6,ANallpoint,ANall,xPointun,ANallun);
	AN_12np_Graph = new TGraphErrors(6,AN12nppoint,AN12np,xPointun,AN12npun);
	AN_3pnp_Graph = new TGraphErrors(6,AN3pnppoint,AN3pnp,xPointun,AN3pnpun);

	AN_all_Graph_Sys = new TGraphErrors(6,ANallpoint,ANall,ANallpointun,ANallsys);
	AN_12np_Graph_Sys = new TGraphErrors(6,AN12nppoint,AN12np,AN12nppointun,AN12npsys);
	AN_3pnp_Graph_Sys = new TGraphErrors(6,AN3pnppoint,AN3pnp,AN3pnppointun,AN3pnpsys);
	
	TGraphErrors *ANY_all_Graph;
	TGraphErrors *ANY_12np_Graph;
	TGraphErrors *ANY_3pnp_Graph;
	TGraphErrors *ANY_all_Graph_Sys;
	TGraphErrors *ANY_12np_Graph_Sys;
	TGraphErrors *ANY_3pnp_Graph_Sys;
	ANY_all_Graph = new TGraphErrors(6,ANYallpoint,ANYall,xPointun,ANYallun);
	ANY_12np_Graph = new TGraphErrors(6,ANY12nppoint,ANY12np,xPointun,ANY12npun);
	ANY_3pnp_Graph = new TGraphErrors(6,ANY3pnppoint,ANY3pnp,xPointun,ANY3pnpun);
	ANY_all_Graph_Sys = new TGraphErrors(6,ANYallpoint,ANYall,ANYallpointun,ANYallsys);
	ANY_12np_Graph_Sys = new TGraphErrors(6,ANY12nppoint,ANY12np,ANY12nppointun,ANY12npsys);
	ANY_3pnp_Graph_Sys = new TGraphErrors(6,ANY3pnppoint,ANY3pnp,ANY3pnppointun,ANY3pnpsys);

	//TCanvas *ANplot = new TCanvas("ANPlot","",200,10,1024,768);
        //ANplot->DrawFrame(2., -0.06, 250., 0.2);
	TH2D * htemp = new TH2D("temp","",8,0.14,0.45,30,-0.043,0.065);
        htemp->GetYaxis()->SetTitleOffset(0.9);
        //htemp->GetXaxis()->SetTitle("|x_{F}|");
        htemp->GetXaxis()->SetTitle("x_{F}");
        htemp->GetYaxis()->SetTitle("A_{N}");
        //htemp->Draw();
        AN_all_Graph->SetMarkerColor(kMagenta+3);
	AN_all_Graph->SetLineWidth(2);
        AN_all_Graph->SetMarkerSize(2);
        AN_all_Graph->SetMarkerStyle(33);
	AN_all_Graph->SetLineColor(kMagenta+3);
        AN_12np_Graph->SetMarkerColor(kMagenta+3);
	AN_12np_Graph->SetLineWidth(2);
        AN_12np_Graph->SetMarkerSize(2);
        AN_12np_Graph->SetMarkerStyle(33);
	AN_12np_Graph->SetLineColor(kMagenta+3);
        AN_3pnp_Graph->SetMarkerColor(kMagenta+3);
	AN_3pnp_Graph->SetLineWidth(2);
        AN_3pnp_Graph->SetMarkerSize(2);
	AN_3pnp_Graph->SetLineColor(kMagenta+3);
        AN_3pnp_Graph->SetMarkerStyle(33);
	AN_all_Graph_Sys->SetMarkerColor(kMagenta+3);
	AN_all_Graph_Sys->SetMarkerSize(2);
        AN_all_Graph_Sys->SetMarkerStyle(33);
	AN_all_Graph_Sys->SetLineColor(0);
	AN_all_Graph_Sys->SetLineWidth(0);
	AN_all_Graph_Sys->SetFillStyle(3001);
	AN_all_Graph_Sys->SetFillColorAlpha(28,0.85);
	AN_12np_Graph_Sys->SetMarkerColor(kMagenta+3);
	AN_12np_Graph_Sys->SetMarkerSize(2);
        AN_12np_Graph_Sys->SetMarkerStyle(33);
	AN_12np_Graph_Sys->SetLineColor(0);
	AN_12np_Graph_Sys->SetLineWidth(0);
	AN_12np_Graph_Sys->SetFillStyle(3001);
	AN_12np_Graph_Sys->SetFillColorAlpha(28,0.85);
	AN_3pnp_Graph_Sys->SetMarkerColor(kMagenta+3);
	AN_3pnp_Graph_Sys->SetMarkerSize(2);
	AN_3pnp_Graph_Sys->SetLineColor(0);
        AN_3pnp_Graph_Sys->SetMarkerStyle(33);
	AN_3pnp_Graph_Sys->SetLineWidth(0);
	AN_3pnp_Graph_Sys->SetFillStyle(3001);
	AN_3pnp_Graph_Sys->SetFillColorAlpha(28,0.85);

        ANY_all_Graph->SetMarkerColor(kMagenta+3);
	ANY_all_Graph->SetLineWidth(2);
        ANY_all_Graph->SetMarkerSize(2);
	ANY_all_Graph->SetLineColor(kMagenta+3);
        ANY_all_Graph->SetMarkerStyle(27);
        ANY_12np_Graph->SetMarkerColor(kMagenta+3);
	ANY_12np_Graph->SetLineWidth(2);
        ANY_12np_Graph->SetMarkerSize(2);
	ANY_12np_Graph->SetLineColor(kMagenta+3);
        ANY_12np_Graph->SetMarkerStyle(27);
        ANY_3pnp_Graph->SetMarkerColor(kMagenta+3);
	ANY_3pnp_Graph->SetLineWidth(2);
        ANY_3pnp_Graph->SetMarkerSize(2);
        ANY_3pnp_Graph->SetMarkerStyle(27);
	ANY_3pnp_Graph->SetLineColor(kMagenta+3);
	ANY_all_Graph_Sys->SetMarkerColor(kMagenta+3);
	ANY_all_Graph_Sys->SetMarkerSize(2);
        ANY_all_Graph_Sys->SetMarkerStyle(27);
	ANY_all_Graph_Sys->SetLineColor(0);
	ANY_all_Graph_Sys->SetLineWidth(0);
	ANY_all_Graph_Sys->SetFillStyle(3001);
	ANY_all_Graph_Sys->SetFillColorAlpha(28,0.85);
	ANY_12np_Graph_Sys->SetMarkerColor(kMagenta+3);
	ANY_12np_Graph_Sys->SetMarkerSize(2);
        ANY_12np_Graph_Sys->SetMarkerStyle(27);
	ANY_12np_Graph_Sys->SetLineColor(0);
	ANY_12np_Graph_Sys->SetLineWidth(0);
	ANY_12np_Graph_Sys->SetFillStyle(3001);
	ANY_12np_Graph_Sys->SetFillColorAlpha(28,0.85);
	ANY_3pnp_Graph_Sys->SetMarkerColor(kMagenta+3);
	ANY_3pnp_Graph_Sys->SetMarkerSize(2);
	ANY_3pnp_Graph_Sys->SetLineColor(0);
        ANY_3pnp_Graph_Sys->SetMarkerStyle(27);
	ANY_3pnp_Graph_Sys->SetLineWidth(0);
	ANY_3pnp_Graph_Sys->SetFillStyle(3001);
	ANY_3pnp_Graph_Sys->SetFillColorAlpha(28,0.85);



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
	const Int_t Ny = 3;

	Float_t lMargin = 0.12;
	Float_t rMargin = 0.05;
	Float_t bMargin = 0.05;
	Float_t tMargin = 0.05;

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
			TH2D *hFrame = (TH2D*)htemp->Clone();
			hFrame->Reset();
         		// Format for y axis
         		hFrame->GetYaxis()->SetLabelFont(43);
         		hFrame->GetYaxis()->SetLabelSize(25);
         		hFrame->GetYaxis()->SetLabelOffset(0.02);
         		hFrame->GetYaxis()->SetTitleFont(43);
         		hFrame->GetYaxis()->SetTitleSize(25);
         		hFrame->GetYaxis()->SetTitleOffset(2);
 
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
         		hFrame->GetXaxis()->SetTitleOffset(1.9);
         		////hFrame->GetXaxis()->CenterTitle();
         		hFrame->GetXaxis()->SetNdivisions(505);
 
         		// TICKS X Axis
         		//hFrame->GetXaxis()->SetTickLength(yFactor*0.06/xFactor);
			hFrame->Draw();

			if (j==0)
			{

        			 AN_3pnp_Graph->Draw("Psame");
				 AN_3pnp_Graph_Sys->Draw("e5 same");
        			//ANY_3pnp_Graph->Draw("Psame");
				//ANY_3pnp_Graph_Sys->Draw("e5 same");
        			line1->Draw("same");
				TLatex T5;
        			T5.SetTextAlign(11);
        			T5.SetTextSize(0.088);
   				T5.DrawLatex(0.23,0.053,"Photon multiplicity #geq 3");
				T5->Draw("same");
				TLatex T8;
        			T8.SetTextAlign(11);
        			T8.SetTextSize(0.065);
        			T8.SetTextColor(kBlack);
   				T8.DrawLatex(0.20,-0.037,"3.0\% polarization scale uncertainty not shown");
				T8->Draw("same");


			}
			if (j==1)
			{

        			 AN_12np_Graph->Draw("Psame");
				 AN_12np_Graph_Sys->Draw("e5 same");
        			//ANY_12np_Graph->Draw("Psame");
				//ANY_12np_Graph_Sys->Draw("e5 same");

				TLegend *leg = new TLegend(0.2,0.06,0.38,0.22);
				leg->SetFillStyle(0);
        			leg->SetTextSize(0.08);
        			leg->AddEntry(AN_12np_Graph,"x_{F} > 0","p");
        			//leg->AddEntry(ANY_12np_Graph,"x_{F} < 0 (shifted by -0.013 along the horizontal axis)","p");
        			leg->SetBorderSize(0);
        			//leg->Draw("same");
        			line1->Draw("same");
				TLatex T4;
        			T4.SetTextAlign(11);
        			T4.SetTextSize(0.10);
   				T4.DrawLatex(0.225,0.054,"Photon multiplicity = 1 or 2");
				T4->Draw("same");


			}
			if (j==2)
			{

        			 AN_all_Graph->Draw("Psame");
				 AN_all_Graph_Sys->Draw("e5 same");
        			//ANY_all_Graph->Draw("Psame");
				//ANY_all_Graph_Sys->Draw("e5 same");
				TLatex T1;
				T1.SetTextAlign(11);
   				T1.SetTextSize(0.075);
				T1.SetTextColor(kRed);
				T1.DrawLatex(0.17,-0.016,"STAR");
				T1->Draw("same");

				TLatex T2;
        			T2.SetTextAlign(11);
        			T2.SetTextSize(0.065);
        			T2.SetTextColor(kBlack);
   				//T2.DrawLatex(0.17,-0.037,"p^{#uparrow} + p @ 200 GeV");
   				T2.DrawLatex(0.17,-0.026,"p^{#uparrow} + p #rightarrow EM jet + X");
   				T2.DrawLatex(0.17,-0.036,"#sqrt{s} = 200 GeV");
				T2->Draw("same");

				TLatex T3;
        			T3.SetTextAlign(11);
        			T3.SetTextSize(0.087);
   				T3.DrawLatex(0.24,0.052,"All photon multiplicity");
				T3->Draw("same");

				line1->Draw("same");
				TLatex T9;
        			T9.SetTextAlign(11);
        			T9.SetTextSize(0.065);
        			T9.SetTextColor(kBlack);
   				//T9.DrawLatex(0.29,-0.015,"15 < E^{EM-jet} <  100 GeV");

   				T9.DrawLatex(0.29,-0.025,"2.8 < #eta^{EM-jet} < 3.8");
   				T9.DrawLatex(0.29,-0.035,"p^{EM-jet}_{T} > 2.0 GeV/c");
				T9->Draw("same");

			}


		}

	}
	//C->SaveAs("fig/prelim/Compare_diff_RG_all_12np_3pnp.pdf");
	C->SaveAs("fig/PLBpaperplot/Fig2.pdf");
	//C->SaveAs("fig/prelim/Compare_diff_RG_all_12np_3pnp.png");


}
