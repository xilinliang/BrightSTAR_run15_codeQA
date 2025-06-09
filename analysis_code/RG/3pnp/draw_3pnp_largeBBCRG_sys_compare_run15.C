void draw_3pnp_largeBBCRG_sys_compare_run15()
{

    gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);
    gStyle->SetOptDate(0);

    	//Double_t BBCpoint2[5]={450,500,600,660,720};
    	//Double_t BBCpoint1[5]={445,495,595,655,715};
    	//Double_t BBCpoint0[5]={440,490,590,650,710};
    	//Double_t BBCpoint3[5]={455,505,605,665,725};
    	//Double_t BBCpoint4[5]={460,510,610,670,730};
    	//Double_t BBCpoint2[5]={450,500,550,600,650};
    	//Double_t BBCpoint1[5]={445,495,545,595,645};
    	//Double_t BBCpoint0[5]={440,490,540,590,640};
    	//Double_t BBCpoint3[5]={455,505,555,605,655};
    	//Double_t BBCpoint4[5]={460,510,560,610,660};
    	//Double_t BBCpoint2_cor[4]={-75,-25,25,75};
    	//Double_t BBCpoint1_cor[4]={-80,-30,20,70};
    	//Double_t BBCpoint0_cor[4]={-85,-35,15,65};
    	//Double_t BBCpoint3_cor[4]={-70,-20,30,80};
    	//Double_t BBCpoint4_cor[4]={-65,-15,35,85};
    	//Double_t BBCpointErr[5]={0,0,0,0,0};
	Double_t ANpoint_1520[5] = {0.165,0.17,0.175,0.18,0.185};
	Double_t ANpoint_2025[5] = {0.215,0.22,0.225,0.23,0.235};
	Double_t ANpoint_2530[5] = {0.265,0.27,0.275,0.28,0.285};
	Double_t ANpoint_3035[5] = {0.315,0.32,0.325,0.33,0.335};
	Double_t ANpoint_3540[5] = {0.365,0.37,0.375,0.38,0.385};
	Double_t ANpoint_4045[5] = {0.415,0.42,0.425,0.43,0.435};
    	Double_t ANpointErr[6]={0,0,0,0,0,0};
    	Double_t AN_1015[5];
    	Double_t AN_1520[5];
    	Double_t AN_2025[5];
    	Double_t AN_2530[5];
    	Double_t AN_3035[5];
    	Double_t AN_3540[5];
    	Double_t AN_4045[5];
    	Double_t AN_3045[5];
    	Double_t YellowAN_1015[5];
    	Double_t YellowAN_1520[5];
    	Double_t YellowAN_2025[5];
    	Double_t YellowAN_2530[5];
    	Double_t YellowAN_3035[5];
    	Double_t YellowAN_3540[5];
    	Double_t YellowAN_4045[5];
    	Double_t YellowAN_3045[5];
    	Double_t ANErr_1015[5];
    	Double_t ANErr_1520[5];
    	Double_t ANErr_2025[5];
    	Double_t ANErr_2530[5];
    	Double_t ANErr_3035[5];
    	Double_t ANErr_3540[5];
    	Double_t ANErr_4045[5];
    	Double_t ANErr_3045[5];
    	Double_t YellowANErr_1520[5];
    	Double_t YellowANErr_2025[5];
    	Double_t YellowANErr_2530[5];
    	Double_t YellowANErr_3035[5];
    	Double_t YellowANErr_3540[5];
    	Double_t YellowANErr_4045[5];
    	//Double_t ANCorr_1015[4];
    	//Double_t ANCorr_1520[4];
    	//Double_t ANCorr_2025[4];
    	//Double_t ANCorr_2530[4];
    	//Double_t ANCorr_3045[4];
    	//Double_t ANDiff_1015[5];
    	//Double_t ANDiff_1520[5];
    	//Double_t ANDiff_2025[5];
    	//Double_t ANDiff_2530[5];
    	//Double_t ANDiff_3045[5];
    	//Double_t ANDiff_un_1015[5];
    	//Double_t ANDiff_un_1520[5];
    	//Double_t ANDiff_un_2025[5];
    	//Double_t ANDiff_un_2530[5];
    	//Double_t ANDiff_un_3045[5];
    	//Double_t YellowANDiff_1015[5];
    	//Double_t YellowANDiff_1520[5];
    	//Double_t YellowANDiff_2025[5];
    	//Double_t YellowANDiff_2530[5];
    	//Double_t YellowANDiff_3045[5];
    	//Double_t YellowANDiff_un_1015[5];
    	//Double_t YellowANDiff_un_1520[5];
    	//Double_t YellowANDiff_un_2025[5];
    	//Double_t YellowANDiff_un_2530[5];
    	//Double_t YellowANDiff_un_3045[5];
    	//Double_t YellowANErr_1015[5];
    	//Double_t YellowANErr_1520[5];
    	//Double_t YellowANErr_2025[5];
    	//Double_t YellowANErr_2530[5];
    	//Double_t YellowANErr_3045[5];
	Double_t XFpoint, ANresult,  ANresultSys, YellowANresult,  YellowANresultSys;
	Double_t maxBlueAN , maxBlueANErr, minBlueAN, minBlueANErr, maxYellowAN, maxYellowANErr, minYellowAN, minYellowANErr , meanBlueAN, StdDevBlueAN, meanYellowAN , StdDevYellowAN;
	Double_t BlueSigni , YellowSigni ;
	Double_t ANDiff_far[5], ANDiff_un_far[5];
	Double_t YellowANDiff_far[5], YellowANDiff_un_far[5];
	
	char beam;
    
	ofstream outputtext;
	outputtext.open("ANtext/Run15FMSfinal_3pnp_RG_Sys_largeBBC.txt");
	ofstream outputtext_no;
	outputtext_no.open("ANtext/Run15FMSfinal_3pnp_RG_Sys_largeBBC_noconstrain.txt");

    	ifstream inputtext;
    	//inputtext.open("largeBBCW450_3pnp.txt");
    	inputtext.open("ANtext/Run15FMSfinal_3pnp_RG_result.txt");

	inputtext >> beam >> XFpoint >> AN_1520[2] >> ANErr_1520[2]  ;
	inputtext >> beam >> XFpoint >> YellowAN_1520[2] >> YellowANErr_1520[2]  ;
	inputtext >> beam >> XFpoint >> AN_2025[2] >> ANErr_2025[2]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2025[2] >> YellowANErr_2025[2]  ;
	inputtext >> beam >> XFpoint >> AN_2530[2] >> ANErr_2530[2]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2530[2] >> YellowANErr_2530[2]  ;
	inputtext >> beam >> XFpoint >> AN_3035[2] >> ANErr_3035[2]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3035[2] >> YellowANErr_3035[2]  ;
	inputtext >> beam >> XFpoint >> AN_3540[2] >> ANErr_3540[2]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3540[2] >> YellowANErr_3540[2]  ;
	inputtext >> beam >> XFpoint >> AN_4045[2] >> ANErr_4045[2]  ;
	inputtext >> beam >> XFpoint >> YellowAN_4045[2] >> YellowANErr_4045[2]  ;


    	ifstream inputtext;
    	//inputtext.open("largeBBCW350_3pnp.txt");
    	inputtext.open("ANtext/Run15FMSfinal_3pnp_RG_SyslargeBBC_m20.txt");

	inputtext >> beam >> XFpoint >> AN_1520[0] >> ANErr_1520[0]  ;
	inputtext >> beam >> XFpoint >> YellowAN_1520[0] >> YellowANErr_1520[0]  ;
	inputtext >> beam >> XFpoint >> AN_2025[0] >> ANErr_2025[0]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2025[0] >> YellowANErr_2025[0]  ;
	inputtext >> beam >> XFpoint >> AN_2530[0] >> ANErr_2530[0]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2530[0] >> YellowANErr_2530[0]  ;
	inputtext >> beam >> XFpoint >> AN_3035[0] >> ANErr_3035[0]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3035[0] >> YellowANErr_3035[0]  ;
	inputtext >> beam >> XFpoint >> AN_3540[0] >> ANErr_3540[0]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3540[0] >> YellowANErr_3540[0]  ;
	inputtext >> beam >> XFpoint >> AN_4045[0] >> ANErr_4045[0]  ;
	inputtext >> beam >> XFpoint >> YellowAN_4045[0] >> YellowANErr_4045[0]  ;

	//ANDiff_1015[0] = AN_1015[0] - AN_1015[2];
	//ANDiff_1520[0] = AN_1520[0] - AN_1520[2];
	//ANDiff_2025[0] = AN_2025[0] - AN_2025[2];
	//ANDiff_2530[0] = AN_2530[0] - AN_2530[2];
	//ANDiff_3045[0] = AN_3045[0] - AN_3045[2];
	//ANDiff_far[0] = ANDiff_1015[0];
	//ANDiff_far[1] = ANDiff_1520[0];
	//ANDiff_far[2] = ANDiff_2025[0];
	//ANDiff_far[3] = ANDiff_2530[0];
	//ANDiff_far[4] = ANDiff_3045[0];
	//ANDiff_un_1015[0] = sqrt(fabs(pow(ANErr_1015[0] , 2) - pow(ANErr_1015[2] ,2)));
	//ANDiff_un_1520[0] = sqrt(fabs(pow(ANErr_1520[0] , 2) - pow(ANErr_1520[2] ,2)));
	//ANDiff_un_2025[0] = sqrt(fabs(pow(ANErr_2025[0] , 2) - pow(ANErr_2025[2] ,2)));
	//ANDiff_un_2530[0] = sqrt(fabs(pow(ANErr_2530[0] , 2) - pow(ANErr_2530[2] ,2)));
	//ANDiff_un_3045[0] = sqrt(fabs(pow(ANErr_3045[0] , 2) - pow(ANErr_3045[2] ,2)));
	//ANDiff_un_far[0] = ANDiff_un_1015[0];
	//ANDiff_un_far[1] = ANDiff_un_1520[0];
	//ANDiff_un_far[2] = ANDiff_un_2025[0];
	//ANDiff_un_far[3] = ANDiff_un_2530[0];
	//ANDiff_un_far[4] = ANDiff_un_3045[0];

	//YellowANDiff_1015[0] = YellowAN_1015[0] - YellowAN_1015[2];
	//YellowANDiff_1520[0] = YellowAN_1520[0] - YellowAN_1520[2];
	//YellowANDiff_2025[0] = YellowAN_2025[0] - YellowAN_2025[2];
	//YellowANDiff_2530[0] = YellowAN_2530[0] - YellowAN_2530[2];
	//YellowANDiff_3045[0] = YellowAN_3045[0] - YellowAN_3045[2];
	//YellowANDiff_far[0] = YellowANDiff_1015[0];
	//YellowANDiff_far[1] = YellowANDiff_1520[0];
	//YellowANDiff_far[2] = YellowANDiff_2025[0];
	//YellowANDiff_far[3] = YellowANDiff_2530[0];
	//YellowANDiff_far[4] = YellowANDiff_3045[0];
	//YellowANDiff_un_1015[0] = sqrt(fabs(pow(YellowANErr_1015[0] , 2) - pow(YellowANErr_1015[2] ,2)));
	//YellowANDiff_un_1520[0] = sqrt(fabs(pow(YellowANErr_1520[0] , 2) - pow(YellowANErr_1520[2] ,2)));
	//YellowANDiff_un_2025[0] = sqrt(fabs(pow(YellowANErr_2025[0] , 2) - pow(YellowANErr_2025[2] ,2)));
	//YellowANDiff_un_2530[0] = sqrt(fabs(pow(YellowANErr_2530[0] , 2) - pow(YellowANErr_2530[2] ,2)));
	//YellowANDiff_un_3045[0] = sqrt(fabs(pow(YellowANErr_3045[0] , 2) - pow(YellowANErr_3045[2] ,2)));
	//YellowANDiff_un_far[0] = YellowANDiff_un_1015[0];
	//YellowANDiff_un_far[1] = YellowANDiff_un_1520[0];
	//YellowANDiff_un_far[2] = YellowANDiff_un_2025[0];
	//YellowANDiff_un_far[3] = YellowANDiff_un_2530[0];
	//YellowANDiff_un_far[4] = YellowANDiff_un_3045[0];



    	ifstream inputtext;
    	//inputtext.open("largeBBCW400_3pnp.txt");
    	inputtext.open("ANtext/Run15FMSfinal_3pnp_RG_SyslargeBBC_m10.txt");

	inputtext >> beam >> XFpoint >> AN_1520[1] >> ANErr_1520[1]  ;
	inputtext >> beam >> XFpoint >> YellowAN_1520[1] >> YellowANErr_1520[1]  ;
	inputtext >> beam >> XFpoint >> AN_2025[1] >> ANErr_2025[1]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2025[1] >> YellowANErr_2025[1]  ;
	inputtext >> beam >> XFpoint >> AN_2530[1] >> ANErr_2530[1]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2530[1] >> YellowANErr_2530[1]  ;
	inputtext >> beam >> XFpoint >> AN_3035[1] >> ANErr_3035[1]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3035[1] >> YellowANErr_3035[1]  ;
	inputtext >> beam >> XFpoint >> AN_3540[1] >> ANErr_3540[1]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3540[1] >> YellowANErr_3540[1]  ;
	inputtext >> beam >> XFpoint >> AN_4045[1] >> ANErr_4045[1]  ;
	inputtext >> beam >> XFpoint >> YellowAN_4045[1] >> YellowANErr_4045[1]  ;

	//ANCorr_1015[0] = 1.0 * (AN_1015[1] - AN_1015[0] ) / sqrt(fabs(pow(ANErr_1015[0],2)-pow(ANErr_1015[1],2)));
	//ANCorr_1520[0] = 1.0 * (AN_1520[1] - AN_1520[0] ) / sqrt(fabs(pow(ANErr_1520[0],2)-pow(ANErr_1520[1],2)));
	//ANCorr_2025[0] = 1.0 * (AN_2025[1] - AN_2025[0] ) / sqrt(fabs(pow(ANErr_2025[0],2)-pow(ANErr_2025[1],2)));
	//ANCorr_2530[0] = 1.0 * (AN_2530[1] - AN_2530[0] ) / sqrt(fabs(pow(ANErr_2530[0],2)-pow(ANErr_2530[1],2)));
	//ANCorr_3045[0] = 1.0 * (AN_3045[1] - AN_3045[0] ) / sqrt(fabs(pow(ANErr_3045[0],2)-pow(ANErr_3045[1],2)));

	//ANDiff_1015[1] = AN_1015[1] - AN_1015[2];
	//ANDiff_1520[1] = AN_1520[1] - AN_1520[2];
	//ANDiff_2025[1] = AN_2025[1] - AN_2025[2];
	//ANDiff_2530[1] = AN_2530[1] - AN_2530[2];
	//ANDiff_3045[1] = AN_3045[1] - AN_3045[2];
	//ANDiff_un_1015[1] = sqrt(fabs(pow(ANErr_1015[1] , 2) - pow(ANErr_1015[2] ,2)));
	//ANDiff_un_1520[1] = sqrt(fabs(pow(ANErr_1520[1] , 2) - pow(ANErr_1520[2] ,2)));
	//ANDiff_un_2025[1] = sqrt(fabs(pow(ANErr_2025[1] , 2) - pow(ANErr_2025[2] ,2)));
	//ANDiff_un_2530[1] = sqrt(fabs(pow(ANErr_2530[1] , 2) - pow(ANErr_2530[2] ,2)));
	//ANDiff_un_3045[1] = sqrt(fabs(pow(ANErr_3045[1] , 2) - pow(ANErr_3045[2] ,2)));

	//YellowANDiff_1015[1] = YellowAN_1015[1] - YellowAN_1015[2];
	//YellowANDiff_1520[1] = YellowAN_1520[1] - YellowAN_1520[2];
	//YellowANDiff_2025[1] = YellowAN_2025[1] - YellowAN_2025[2];
	//YellowANDiff_2530[1] = YellowAN_2530[1] - YellowAN_2530[2];
	//YellowANDiff_3045[1] = YellowAN_3045[1] - YellowAN_3045[2];
	//YellowANDiff_un_1015[1] = sqrt(fabs(pow(YellowANErr_1015[1] , 2) - pow(YellowANErr_1015[2] ,2)));
	//YellowANDiff_un_1520[1] = sqrt(fabs(pow(YellowANErr_1520[1] , 2) - pow(YellowANErr_1520[2] ,2)));
	//YellowANDiff_un_2025[1] = sqrt(fabs(pow(YellowANErr_2025[1] , 2) - pow(YellowANErr_2025[2] ,2)));
	//YellowANDiff_un_2530[1] = sqrt(fabs(pow(YellowANErr_2530[1] , 2) - pow(YellowANErr_2530[2] ,2)));
	//YellowANDiff_un_3045[1] = sqrt(fabs(pow(YellowANErr_3045[1] , 2) - pow(YellowANErr_3045[2] ,2)));



    	//ifstream inputtext;
    	////inputtext.open("largeBBCW450_3pnp.txt");
    	//inputtext.open("largeBBCW550.txt");
    	//inputtext.open("ANtext/Run15FMSfinal_3pnp_RG_SyslargeBBC_m10.txt");

	//inputtext >> beam >> XFpoint >> AN_1015[2] >> ANErr_1015[2]  ;
	//inputtext >> beam >> XFpoint >> YellowAN_1015[2] >> YellowANErr_1015[2]  ;
	//inputtext >> beam >> XFpoint >> AN_1520[2] >> ANErr_1520[2]  ;
	//inputtext >> beam >> XFpoint >> YellowAN_1520[2] >> YellowANErr_1520[2]  ;
	//inputtext >> beam >> XFpoint >> AN_2025[2] >> ANErr_2025[2]  ;
	//inputtext >> beam >> XFpoint >> YellowAN_2025[2] >> YellowANErr_2025[2]  ;
	//inputtext >> beam >> XFpoint >> AN_2530[2] >> ANErr_2530[2]  ;
	//inputtext >> beam >> XFpoint >> YellowAN_2530[2] >> YellowANErr_2530[2]  ;
	//inputtext >> beam >> XFpoint >> AN_3045[2] >> ANErr_3045[2]  ;
	//inputtext >> beam >> XFpoint >> YellowAN_3045[2] >> YellowANErr_3045[2]  ;

	//ANCorr_1015[1] = 1.0 * (AN_1015[2] - AN_1015[1] ) / sqrt(fabs(pow(ANErr_1015[2],2)-pow(ANErr_1015[1],2)));
	//ANCorr_1520[1] = 1.0 * (AN_1520[2] - AN_1520[1] ) / sqrt(fabs(pow(ANErr_1520[2],2)-pow(ANErr_1520[1],2)));
	//ANCorr_2025[1] = 1.0 * (AN_2025[2] - AN_2025[1] ) / sqrt(fabs(pow(ANErr_2025[2],2)-pow(ANErr_2025[1],2)));
	//ANCorr_2530[1] = 1.0 * (AN_2530[2] - AN_2530[1] ) / sqrt(fabs(pow(ANErr_2530[2],2)-pow(ANErr_2530[1],2)));
	//ANCorr_2025[1] = 1.0 * (AN_3045[2] - AN_3045[1] ) / sqrt(fabs(pow(ANErr_3045[2],2)-pow(ANErr_3045[1],2)));


	//ANDiff_1015[2] = 0;
	//ANDiff_1520[2] = 0;
	//ANDiff_2025[2] = 0;
	//ANDiff_2530[2] = 0;
	//ANDiff_3045[2] = 0;
	//ANDiff_un_1015[2] = 0;
	//ANDiff_un_1520[2] = 0;
	//ANDiff_un_2025[2] = 0;
	//ANDiff_un_2530[2] = 0;
	//ANDiff_un_3045[2] = 0;

	//YellowANDiff_1015[2] = 0;
	//YellowANDiff_1520[2] = 0;
	//YellowANDiff_2025[2] = 0;
	//YellowANDiff_2530[2] = 0;
	//YellowANDiff_3045[2] = 0;
	//YellowANDiff_un_1015[2] = 0;
	//YellowANDiff_un_1520[2] = 0;
	//YellowANDiff_un_2025[2] = 0;
	//YellowANDiff_un_2530[2] = 0;
	//YellowANDiff_un_3045[2] = 0;


    	ifstream inputtext;
    	//inputtext.open("largeBBCW500_3pnp.txt");
    	inputtext.open("ANtext/Run15FMSfinal_3pnp_RG_SyslargeBBC_p10.txt");

	inputtext >> beam >> XFpoint >> AN_1520[3] >> ANErr_1520[3]  ;
	inputtext >> beam >> XFpoint >> YellowAN_1520[3] >> YellowANErr_1520[3]  ;
	inputtext >> beam >> XFpoint >> AN_2025[3] >> ANErr_2025[3]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2025[3] >> YellowANErr_2025[3]  ;
	inputtext >> beam >> XFpoint >> AN_2530[3] >> ANErr_2530[3]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2530[3] >> YellowANErr_2530[3]  ;
	inputtext >> beam >> XFpoint >> AN_3035[3] >> ANErr_3035[3]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3035[3] >> YellowANErr_3035[3]  ;
	inputtext >> beam >> XFpoint >> AN_3540[3] >> ANErr_3540[3]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3540[3] >> YellowANErr_3540[3]  ;
	inputtext >> beam >> XFpoint >> AN_4045[3] >> ANErr_4045[3]  ;
	inputtext >> beam >> XFpoint >> YellowAN_4045[3] >> YellowANErr_4045[3]  ;

	//ANCorr_1015[2] = 1.0 * (AN_1015[3] - AN_1015[2] ) / sqrt(fabs(pow(ANErr_1015[2],2)-pow(ANErr_1015[3],2)));
	//ANCorr_1520[2] = 1.0 * (AN_1520[3] - AN_1520[2] ) / sqrt(fabs(pow(ANErr_1520[2],2)-pow(ANErr_1520[3],2)));
	//ANCorr_2025[2] = 1.0 * (AN_2025[3] - AN_2025[2] ) / sqrt(fabs(pow(ANErr_2025[2],2)-pow(ANErr_2025[3],2)));
	//ANCorr_2530[2] = 1.0 * (AN_2530[3] - AN_2530[2] ) / sqrt(fabs(pow(ANErr_2530[2],2)-pow(ANErr_2530[3],2)));
	//ANCorr_2025[2] = 1.0 * (AN_3045[3] - AN_3045[2] ) / sqrt(fabs(pow(ANErr_3045[2],2)-pow(ANErr_3045[3],2)));
	//ANDiff_1015[3] = AN_1015[3] - AN_1015[2];
	//ANDiff_1520[3] = AN_1520[3] - AN_1520[2];
	//ANDiff_2025[3] = AN_2025[3] - AN_2025[2];
	//ANDiff_2530[3] = AN_2530[3] - AN_2530[2];
	//ANDiff_3045[3] = AN_3045[3] - AN_3045[2];
	//ANDiff_un_1015[3] = sqrt(fabs(pow(ANErr_1015[3] , 2) - pow(ANErr_1015[2] ,2)));
	//ANDiff_un_1520[3] = sqrt(fabs(pow(ANErr_1520[3] , 2) - pow(ANErr_1520[2] ,2)));
	//ANDiff_un_2025[3] = sqrt(fabs(pow(ANErr_2025[3] , 2) - pow(ANErr_2025[2] ,2)));
	//ANDiff_un_2530[3] = sqrt(fabs(pow(ANErr_2530[3] , 2) - pow(ANErr_2530[2] ,2)));
	//ANDiff_un_3045[3] = sqrt(fabs(pow(ANErr_3045[3] , 2) - pow(ANErr_3045[2] ,2)));


	//YellowANDiff_1015[3] = YellowAN_1015[3] - YellowAN_1015[2];
	//YellowANDiff_1520[3] = YellowAN_1520[3] - YellowAN_1520[2];
	//YellowANDiff_2025[3] = YellowAN_2025[3] - YellowAN_2025[2];
	//YellowANDiff_2530[3] = YellowAN_2530[3] - YellowAN_2530[2];
	//YellowANDiff_3045[3] = YellowAN_3045[3] - YellowAN_3045[2];
	//YellowANDiff_un_1015[3] = sqrt(fabs(pow(YellowANErr_1015[3] , 2) - pow(YellowANErr_1015[2] ,2)));
	//YellowANDiff_un_1520[3] = sqrt(fabs(pow(YellowANErr_1520[3] , 2) - pow(YellowANErr_1520[2] ,2)));
	//YellowANDiff_un_2025[3] = sqrt(fabs(pow(YellowANErr_2025[3] , 2) - pow(YellowANErr_2025[2] ,2)));
	//YellowANDiff_un_2530[3] = sqrt(fabs(pow(YellowANErr_2530[3] , 2) - pow(YellowANErr_2530[2] ,2)));
	//YellowANDiff_un_3045[3] = sqrt(fabs(pow(YellowANErr_3045[3] , 2) - pow(YellowANErr_3045[2] ,2)));

    	ifstream inputtext;
    	//inputtext.open("largeBBCW550_3pnp.txt");
    	inputtext.open("ANtext/Run15FMSfinal_3pnp_RG_SyslargeBBC_p20.txt");

	inputtext >> beam >> XFpoint >> AN_1520[4] >> ANErr_1520[4]  ;
	inputtext >> beam >> XFpoint >> YellowAN_1520[4] >> YellowANErr_1520[4]  ;
	inputtext >> beam >> XFpoint >> AN_2025[4] >> ANErr_2025[4]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2025[4] >> YellowANErr_2025[4]  ;
	inputtext >> beam >> XFpoint >> AN_2530[4] >> ANErr_2530[4]  ;
	inputtext >> beam >> XFpoint >> YellowAN_2530[4] >> YellowANErr_2530[4]  ;
	inputtext >> beam >> XFpoint >> AN_3035[4] >> ANErr_3035[4]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3035[4] >> YellowANErr_3035[4]  ;
	inputtext >> beam >> XFpoint >> AN_3540[4] >> ANErr_3540[4]  ;
	inputtext >> beam >> XFpoint >> YellowAN_3540[4] >> YellowANErr_3540[4]  ;
	inputtext >> beam >> XFpoint >> AN_4045[4] >> ANErr_4045[4]  ;
	inputtext >> beam >> XFpoint >> YellowAN_4045[4] >> YellowANErr_4045[4]  ;

	//ANCorr_1015[3] = 1.0 * (AN_1015[4] - AN_1015[3] ) / sqrt(fabs(pow(ANErr_1015[4],2)-pow(ANErr_1015[3],2)));
	//ANCorr_1520[3] = 1.0 * (AN_1520[4] - AN_1520[3] ) / sqrt(fabs(pow(ANErr_1520[4],2)-pow(ANErr_1520[3],2)));
	//ANCorr_2025[3] = 1.0 * (AN_2025[4] - AN_2025[3] ) / sqrt(fabs(pow(ANErr_2025[4],2)-pow(ANErr_2025[3],2)));
	//ANCorr_2530[3] = 1.0 * (AN_2530[4] - AN_2530[3] ) / sqrt(fabs(pow(ANErr_2530[4],2)-pow(ANErr_2530[3],2)));
	//ANCorr_2025[3] = 1.0 * (AN_3045[4] - AN_3045[3] ) / sqrt(fabs(pow(ANErr_3045[4],2)-pow(ANErr_3045[3],2)));

	//ANDiff_1015[4] = AN_1015[4] - AN_1015[2];
	//ANDiff_1520[4] = AN_1520[4] - AN_1520[2];
	//ANDiff_2025[4] = AN_2025[4] - AN_2025[2];
	//ANDiff_2530[4] = AN_2530[4] - AN_2530[2];
	//ANDiff_3045[4] = AN_3045[4] - AN_3045[2];
	//ANDiff_un_1015[4] = sqrt(fabs(pow(ANErr_1015[4] , 2) - pow(ANErr_1015[2] ,2)));
	//ANDiff_un_1520[4] = sqrt(fabs(pow(ANErr_1520[4] , 2) - pow(ANErr_1520[2] ,2)));
	//ANDiff_un_2025[4] = sqrt(fabs(pow(ANErr_2025[4] , 2) - pow(ANErr_2025[2] ,2)));
	//ANDiff_un_2530[4] = sqrt(fabs(pow(ANErr_2530[4] , 2) - pow(ANErr_2530[2] ,2)));
	//ANDiff_un_3045[4] = sqrt(fabs(pow(ANErr_3045[4] , 2) - pow(ANErr_3045[2] ,2)));

	//YellowANDiff_1015[4] = YellowAN_1015[4] - YellowAN_1015[2];
	//YellowANDiff_1520[4] = YellowAN_1520[4] - YellowAN_1520[2];
	//YellowANDiff_2025[4] = YellowAN_2025[4] - YellowAN_2025[2];
	//YellowANDiff_2530[4] = YellowAN_2530[4] - YellowAN_2530[2];
	//YellowANDiff_3045[4] = YellowAN_3045[4] - YellowAN_3045[2];
	//YellowANDiff_un_1015[4] = sqrt(fabs(pow(YellowANErr_1015[4] , 2) - pow(YellowANErr_1015[2] ,2)));
	//YellowANDiff_un_1520[4] = sqrt(fabs(pow(YellowANErr_1520[4] , 2) - pow(YellowANErr_1520[2] ,2)));
	//YellowANDiff_un_2025[4] = sqrt(fabs(pow(YellowANErr_2025[4] , 2) - pow(YellowANErr_2025[2] ,2)));
	//YellowANDiff_un_2530[4] = sqrt(fabs(pow(YellowANErr_2530[4] , 2) - pow(YellowANErr_2530[2] ,2)));
	//YellowANDiff_un_3045[4] = sqrt(fabs(pow(YellowANErr_3045[4] , 2) - pow(YellowANErr_3045[2] ,2)));


	//calc the standard dev
	maxBlueAN = -9999.; 
	maxBlueANErr = 0; 
	minBlueAN = 9999.; 
	minBlueANErr = 0; 
	maxYellowAN = -9999.; 
	maxYellowANErr = 0; 
	minYellowAN = 9999.; 
	minYellowANErr = 0; 
	meanBlueAN = 0;
	meanYellowAN = 0;
	StdDevBlueAN = 0;
	StdDevYellowAN = 0;
	for (int i=0; i < 5; i++)
	{

		if (AN_1520[i] < minBlueAN) {minBlueAN = AN_1520[i]; minBlueANErr = ANErr_1520[i];}
		if (AN_1520[i] > maxBlueAN) {maxBlueAN = AN_1520[i]; maxBlueANErr = ANErr_1520[i];}
		meanBlueAN = meanBlueAN + AN_1520[i];
		if (YellowAN_1520[i] < minYellowAN) {minYellowAN = YellowAN_1520[i]; minYellowANErr = YellowANErr_1520[i];}
		if (YellowAN_1520[i] > maxYellowAN) {maxYellowAN = YellowAN_1520[i]; maxYellowANErr = YellowANErr_1520[i];}
		meanYellowAN = meanYellowAN + YellowAN_1520[i];

	}
	meanBlueAN = 1.0 * meanBlueAN / 5.0;
	meanYellowAN = 1.0 * meanYellowAN / 5.0;
	for (int i=0; i<5; i++)
	{

		StdDevBlueAN = StdDevBlueAN + pow((AN_1520[i]- meanBlueAN),2);
		StdDevYellowAN = StdDevYellowAN + pow((YellowAN_1520[i]- meanYellowAN),2);

	}
	StdDevBlueAN = sqrt(1.0 * StdDevBlueAN / 5.0);
	StdDevYellowAN = sqrt(1.0 * StdDevYellowAN / 5.0);
	BlueSigni = 1.0 * (maxBlueAN - minBlueAN) / sqrt(fabs(pow(maxBlueANErr,2) - pow(minBlueANErr,2)));
	YellowSigni = 1.0 * (maxYellowAN - minYellowAN) / sqrt(fabs(pow(maxYellowANErr,2) - pow(minYellowANErr,2)));
	cout << "Blue beam Sys significance: " << BlueSigni << "	Yellow beam Sys significance: " << YellowSigni << endl;
	cout << " xF: 0.15 - 0.2: mean: " << meanBlueAN << "  Std Dev: " <<  StdDevBlueAN << endl; 
	cout << " xF: 0.15 - 0.2: mean: " << meanYellowAN << "  Std Dev: " <<  StdDevYellowAN << endl; 
	if (BlueSigni > 1) {outputtext << "B	0.175	" << StdDevBlueAN << endl;} else {outputtext << "B    0.175   0.0" << endl;}
	if (YellowSigni > 1) {outputtext << "Y	0.175	" << StdDevYellowAN << endl;} else {outputtext << "Y    0.175   0.0" << endl;}
	outputtext_no << "B    0.175   " << StdDevBlueAN << endl;
	outputtext_no << "Y    0.175   " << StdDevYellowAN << endl;

	maxBlueAN = -9999.; 
	maxBlueANErr = 0; 
	minBlueAN = 9999.; 
	minBlueANErr = 0; 
	maxYellowAN = -9999.; 
	maxYellowANErr = 0; 
	minYellowAN = 9999.; 
	minYellowANErr = 0; 
	meanBlueAN = 0;
	meanYellowAN = 0;
	StdDevBlueAN = 0;
	StdDevYellowAN = 0;
	for (int i=0; i < 5; i++)
	{

		if (AN_2025[i] < minBlueAN) {minBlueAN = AN_2025[i]; minBlueANErr = ANErr_2025[i];}
		if (AN_2025[i] > maxBlueAN) {maxBlueAN = AN_2025[i]; maxBlueANErr = ANErr_2025[i];}
		meanBlueAN = meanBlueAN + AN_2025[i];
		if (YellowAN_2025[i] < minYellowAN) {minYellowAN = YellowAN_2025[i]; minYellowANErr = YellowANErr_2025[i];}
		if (YellowAN_2025[i] > maxYellowAN) {maxYellowAN = YellowAN_2025[i]; maxYellowANErr = YellowANErr_2025[i];}
		meanYellowAN = meanYellowAN + YellowAN_2025[i];

	}
	meanBlueAN = 1.0 * meanBlueAN / 5.0;
	meanYellowAN = 1.0 * meanYellowAN / 5.0;
	for (int i=0; i<5; i++)
	{

		StdDevBlueAN = StdDevBlueAN + pow((AN_2025[i]- meanBlueAN),2);
		StdDevYellowAN = StdDevYellowAN + pow((YellowAN_2025[i]- meanYellowAN),2);

	}
	StdDevBlueAN = sqrt(1.0 * StdDevBlueAN / 5.0);
	StdDevYellowAN = sqrt(1.0 * StdDevYellowAN / 5.0);
	BlueSigni = 1.0 * (maxBlueAN - minBlueAN) / sqrt(fabs(pow(maxBlueANErr,2) - pow(minBlueANErr,2)));
	YellowSigni = 1.0 * (maxYellowAN - minYellowAN) / sqrt(fabs(pow(maxYellowANErr,2) - pow(minYellowANErr,2)));
	cout << "Blue beam Sys significance: " << BlueSigni << "	Yellow beam Sys significance: " << YellowSigni << endl;
	cout << " xF: 0.2  - 0.25: mean: " << meanBlueAN << "  Std Dev: " <<  StdDevBlueAN << endl; 
	cout << " xF: 0.3  - 0.25: mean: " << meanYellowAN << "  Std Dev: " <<  StdDevYellowAN << endl; 
	if (BlueSigni > 1) {outputtext << "B	0.225	" << StdDevBlueAN << endl;} else {outputtext << "B    0.225   0.0" << endl;}
	if (YellowSigni > 1) {outputtext << "Y	0.225	" << StdDevYellowAN << endl;} else {outputtext << "Y    0.225   0.0" << endl;}
	outputtext_no << "B    0.225   " << StdDevBlueAN << endl;
	outputtext_no << "Y    0.225   " << StdDevYellowAN << endl;

	maxBlueAN = -9999.; 
	maxBlueANErr = 0; 
	minBlueAN = 9999.; 
	minBlueANErr = 0; 
	maxYellowAN = -9999.; 
	maxYellowANErr = 0; 
	minYellowAN = 9999.; 
	minYellowANErr = 0; 
	meanBlueAN = 0;
	meanYellowAN = 0;
	StdDevBlueAN = 0;
	StdDevYellowAN = 0;
	for (int i=0; i < 5; i++)
	{

		if (AN_2530[i] < minBlueAN) {minBlueAN = AN_2530[i]; minBlueANErr = ANErr_2530[i];}
		if (AN_2530[i] > maxBlueAN) {maxBlueAN = AN_2530[i]; maxBlueANErr = ANErr_2530[i];}
		meanBlueAN = meanBlueAN + AN_2530[i];
		if (YellowAN_2530[i] < minYellowAN) {minYellowAN = YellowAN_2530[i]; minYellowANErr = YellowANErr_2530[i];}
		if (YellowAN_2530[i] > maxYellowAN) {maxYellowAN = YellowAN_2530[i]; maxYellowANErr = YellowANErr_2530[i];}
		meanYellowAN = meanYellowAN + YellowAN_2530[i];

	}
	meanBlueAN = 1.0 * meanBlueAN / 5.0;
	meanYellowAN = 1.0 * meanYellowAN / 5.0;
	for (int i=0; i<5; i++)
	{

		StdDevBlueAN = StdDevBlueAN + pow((AN_2530[i]- meanBlueAN),2);
		StdDevYellowAN = StdDevYellowAN + pow((YellowAN_2530[i]- meanYellowAN),2);

	}
	StdDevBlueAN = sqrt(1.0 * StdDevBlueAN / 5.0);
	StdDevYellowAN = sqrt(1.0 * StdDevYellowAN / 5.0);
	BlueSigni = 1.0 * (maxBlueAN - minBlueAN) / sqrt(fabs(pow(maxBlueANErr,2) - pow(minBlueANErr,2)));
	YellowSigni = 1.0 * (maxYellowAN - minYellowAN) / sqrt(fabs(pow(maxYellowANErr,2) - pow(minYellowANErr,2)));
	cout << "Blue beam Sys significance: " << BlueSigni << "	Yellow beam Sys significance: " << YellowSigni << endl;
	cout << " xF: 0.25 - 0.3: mean: " << meanBlueAN << "  Std Dev: " <<  StdDevBlueAN << endl; 
	cout << " xF: 0.25 - 0.3: mean: " << meanYellowAN << "  Std Dev: " <<  StdDevYellowAN << endl; 
	if (BlueSigni > 1) {outputtext << "B	0.275	" << StdDevBlueAN << endl;} else {outputtext << "B    0.275   0.0" << endl;}
	if (YellowSigni > 1) {outputtext << "Y	0.275	" << StdDevYellowAN << endl;} else {outputtext << "Y    0.275   0.0" << endl;}
	outputtext_no << "B    0.275   " << StdDevBlueAN << endl;
	outputtext_no << "Y    0.275   " << StdDevYellowAN << endl;

	maxBlueAN = -9999.; 
	maxBlueANErr = 0; 
	minBlueAN = 9999.; 
	minBlueANErr = 0; 
	maxYellowAN = -9999.; 
	maxYellowANErr = 0; 
	minYellowAN = 9999.; 
	minYellowANErr = 0; 
	meanBlueAN = 0;
	meanYellowAN = 0;
	StdDevBlueAN = 0;
	StdDevYellowAN = 0;
	for (int i=0; i < 5; i++)
	{

		if (AN_3035[i] < minBlueAN) {minBlueAN = AN_3035[i]; minBlueANErr = ANErr_3035[i];}
		if (AN_3035[i] > maxBlueAN) {maxBlueAN = AN_3035[i]; maxBlueANErr = ANErr_3035[i];}
		meanBlueAN = meanBlueAN + AN_3035[i];
		if (YellowAN_3035[i] < minYellowAN) {minYellowAN = YellowAN_3035[i]; minYellowANErr = YellowANErr_3035[i];}
		if (YellowAN_3035[i] > maxYellowAN) {maxYellowAN = YellowAN_3035[i]; maxYellowANErr = YellowANErr_3035[i];}
		meanYellowAN = meanYellowAN + YellowAN_3035[i];

	}
	meanBlueAN = 1.0 * meanBlueAN / 5.0;
	meanYellowAN = 1.0 * meanYellowAN / 5.0;
	for (int i=0; i<5; i++)
	{

		StdDevBlueAN = StdDevBlueAN + pow((AN_3035[i]- meanBlueAN),2);
		StdDevYellowAN = StdDevYellowAN + pow((YellowAN_3035[i]- meanYellowAN),2);

	}
	StdDevBlueAN = sqrt(1.0 * StdDevBlueAN / 5.0);
	StdDevYellowAN = sqrt(1.0 * StdDevYellowAN / 5.0);
	BlueSigni = 1.0 * (maxBlueAN - minBlueAN) / sqrt(fabs(pow(maxBlueANErr,2) - pow(minBlueANErr,2)));
	YellowSigni = 1.0 * (maxYellowAN - minYellowAN) / sqrt(fabs(pow(maxYellowANErr,2) - pow(minYellowANErr,2)));
	cout << "Blue beam Sys significance: " << BlueSigni << "	Yellow beam Sys significance: " << YellowSigni << endl;
	cout << " xF: 0.15 - 0.2: mean: " << meanBlueAN << "  Std Dev: " <<  StdDevBlueAN << endl; 
	cout << " xF: 0.15 - 0.2: mean: " << meanYellowAN << "  Std Dev: " <<  StdDevYellowAN << endl; 
	if (BlueSigni > 1) {outputtext << "B	0.325	" << StdDevBlueAN << endl;} else {outputtext << "B    0.325   0.0" << endl;}
	if (YellowSigni > 1) {outputtext << "Y	0.325	" << StdDevYellowAN << endl;} else {outputtext << "Y    0.325   0.0" << endl;}
	outputtext_no << "B    0.325   " << StdDevBlueAN << endl;
	outputtext_no << "Y    0.325   " << StdDevYellowAN << endl;

	maxBlueAN = -9999.; 
	maxBlueANErr = 0; 
	minBlueAN = 9999.; 
	minBlueANErr = 0; 
	maxYellowAN = -9999.; 
	maxYellowANErr = 0; 
	minYellowAN = 9999.; 
	minYellowANErr = 0; 
	meanBlueAN = 0;
	meanYellowAN = 0;
	StdDevBlueAN = 0;
	StdDevYellowAN = 0;
	for (int i=0; i < 5; i++)
	{

		if (AN_3540[i] < minBlueAN) {minBlueAN = AN_3540[i]; minBlueANErr = ANErr_3540[i];}
		if (AN_3540[i] > maxBlueAN) {maxBlueAN = AN_3540[i]; maxBlueANErr = ANErr_3540[i];}
		meanBlueAN = meanBlueAN + AN_3540[i];
		if (YellowAN_3540[i] < minYellowAN) {minYellowAN = YellowAN_3540[i]; minYellowANErr = YellowANErr_3540[i];}
		if (YellowAN_3540[i] > maxYellowAN) {maxYellowAN = YellowAN_3540[i]; maxYellowANErr = YellowANErr_3540[i];}
		meanYellowAN = meanYellowAN + YellowAN_3540[i];

	}
	meanBlueAN = 1.0 * meanBlueAN / 5.0;
	meanYellowAN = 1.0 * meanYellowAN / 5.0;
	for (int i=0; i<5; i++)
	{

		StdDevBlueAN = StdDevBlueAN + pow((AN_3540[i]- meanBlueAN),2);
		StdDevYellowAN = StdDevYellowAN + pow((YellowAN_3540[i]- meanYellowAN),2);

	}
	StdDevBlueAN = sqrt(1.0 * StdDevBlueAN / 5.0);
	StdDevYellowAN = sqrt(1.0 * StdDevYellowAN / 5.0);
	BlueSigni = 1.0 * (maxBlueAN - minBlueAN) / sqrt(fabs(pow(maxBlueANErr,2) - pow(minBlueANErr,2)));
	YellowSigni = 1.0 * (maxYellowAN - minYellowAN) / sqrt(fabs(pow(maxYellowANErr,2) - pow(minYellowANErr,2)));
	cout << "Blue beam Sys significance: " << BlueSigni << "	Yellow beam Sys significance: " << YellowSigni << endl;
	cout << " xF: 0.35 - 0.4: mean: " << meanBlueAN << "  Std Dev: " <<  StdDevBlueAN << endl; 
	cout << " xF: 0.35 - 0.4: mean: " << meanYellowAN << "  Std Dev: " <<  StdDevYellowAN << endl; 
	if (BlueSigni > 1) {outputtext << "B	0.375	" << StdDevBlueAN << endl;} else {outputtext << "B    0.375   0.0" << endl;}
	if (YellowSigni > 1) {outputtext << "Y	0.375	" << StdDevYellowAN << endl;} else {outputtext << "Y    0.375   0.0" << endl;}
	outputtext_no << "B    0.375   " << StdDevBlueAN << endl;
	outputtext_no << "Y    0.375   " << StdDevYellowAN << endl;

	maxBlueAN = -9999.; 
	maxBlueANErr = 0; 
	minBlueAN = 9999.; 
	minBlueANErr = 0; 
	maxYellowAN = -9999.; 
	maxYellowANErr = 0; 
	minYellowAN = 9999.; 
	minYellowANErr = 0; 
	meanBlueAN = 0;
	meanYellowAN = 0;
	StdDevBlueAN = 0;
	StdDevYellowAN = 0;
	for (int i=0; i < 5; i++)
	{

		if (AN_4045[i] < minBlueAN) {minBlueAN = AN_4045[i]; minBlueANErr = ANErr_4045[i];}
		if (AN_4045[i] > maxBlueAN) {maxBlueAN = AN_4045[i]; maxBlueANErr = ANErr_4045[i];}
		meanBlueAN = meanBlueAN + AN_4045[i];
		if (YellowAN_4045[i] < minYellowAN) {minYellowAN = YellowAN_4045[i]; minYellowANErr = YellowANErr_4045[i];}
		if (YellowAN_4045[i] > maxYellowAN) {maxYellowAN = YellowAN_4045[i]; maxYellowANErr = YellowANErr_4045[i];}
		meanYellowAN = meanYellowAN + YellowAN_4045[i];

	}
	meanBlueAN = 1.0 * meanBlueAN / 5.0;
	meanYellowAN = 1.0 * meanYellowAN / 5.0;
	for (int i=0; i<5; i++)
	{

		StdDevBlueAN = StdDevBlueAN + pow((AN_4045[i]- meanBlueAN),2);
		StdDevYellowAN = StdDevYellowAN + pow((YellowAN_4045[i]- meanYellowAN),2);

	}
	StdDevBlueAN = sqrt(1.0 * StdDevBlueAN / 5.0);
	StdDevYellowAN = sqrt(1.0 * StdDevYellowAN / 5.0);
	BlueSigni = 1.0 * (maxBlueAN - minBlueAN) / sqrt(fabs(pow(maxBlueANErr,2) - pow(minBlueANErr,2)));
	YellowSigni = 1.0 * (maxYellowAN - minYellowAN) / sqrt(fabs(pow(maxYellowANErr,2) - pow(minYellowANErr,2)));
	cout << "Blue beam Sys significance: " << BlueSigni << "	Yellow beam Sys significance: " << YellowSigni << endl;
	cout << " xF: 0.40 - 0.45: mean: " << meanBlueAN << "  Std Dev: " <<  StdDevBlueAN << endl; 
	cout << " xF: 0.40 - 0.45: mean: " << meanYellowAN << "  Std Dev: " <<  StdDevYellowAN << endl; 
	if (BlueSigni > 1) {outputtext << "B	0.425	" << StdDevBlueAN << endl;} else {outputtext << "B    0.425   0.0" << endl;}
	if (YellowSigni > 1) {outputtext << "Y	0.425	" << StdDevYellowAN << endl;} else {outputtext << "Y    0.425   0.0" << endl;}
	outputtext_no << "B    0.425   " << StdDevBlueAN << endl;
	outputtext_no << "Y    0.425   " << StdDevYellowAN << endl;



	TCanvas *ANplot = new TCanvas("ANPlot","",1024,768);
	ANplot->DrawFrame(2., -0.06, 250., 0.2);
	TH2D * temp = new TH2D("temp","Blue beam A_{N}",8,0.15,0.45,30,-0.05,0.05);
	temp->GetYaxis()->SetTitle("Blue beam A_{N}");
  	temp->GetYaxis()->SetTitleOffset(0.9);
  	temp->GetXaxis()->SetTitle("x_{F}");
  	temp->Draw();


	BlueBeamAN1520 = new TGraphErrors(5, ANpoint_1520 , AN_1520, ANpointErr, ANErr_1520);
	BlueBeamAN1520->SetName("BlueBeamAN1520");
	BlueBeamAN1520->SetTitle("Blue beam A_{N} for BBC cuts");
	BlueBeamAN1520->GetXaxis()->SetTitle("large west BBC cut");
	BlueBeamAN1520->GetYaxis()->SetTitle("Blue beam A_{N}");
	//BlueBeamAN1520->SetMarkerColor(2);
	BlueBeamAN1520->SetMarkerSize(2);
	BlueBeamAN1520->SetMarkerStyle(20);
	//BlueBeamAN1520->SetLineColor(2);
	BlueBeamAN1520->SetLineWidth(2);
	BlueBeamAN1520->Draw("P same");

	BlueBeamAN2025 = new TGraphErrors(5, ANpoint_2025 , AN_2025, ANpointErr, ANErr_2025);
	BlueBeamAN2025->SetName("BlueBeamAN2025");
	BlueBeamAN2025->SetTitle("Blue beam A_{N} for BBC cuts");
	BlueBeamAN2025->GetXaxis()->SetTitle("large west BBC cut");
	BlueBeamAN2025->GetYaxis()->SetTitle("Blue beam A_{N}");
	//BlueBeamAN2025->SetMarkerColor(3);
	BlueBeamAN2025->SetMarkerSize(2);
	BlueBeamAN2025->SetMarkerStyle(20);
	//BlueBeamAN2025->SetLineColor(3);
	BlueBeamAN2025->SetLineWidth(2);
	BlueBeamAN2025->Draw("P same");

	BlueBeamAN2530 = new TGraphErrors(5, ANpoint_2530 , AN_2530, ANpointErr, ANErr_2530);
	BlueBeamAN2530->SetName("BlueBeamAN2530");
	BlueBeamAN2530->SetTitle("Blue beam A_{N} for BBC cuts");
	BlueBeamAN2530->GetXaxis()->SetTitle("large west BBC cut");
	BlueBeamAN2530->GetYaxis()->SetTitle("Blue beam A_{N}");
	//BlueBeamAN2530->SetMarkerColor(13);
	BlueBeamAN2530->SetMarkerSize(2);
	BlueBeamAN2530->SetMarkerStyle(20);
	//BlueBeamAN2530->SetLineColor(13);
	BlueBeamAN2530->SetLineWidth(2);
	BlueBeamAN2530->Draw("P same");

	BlueBeamAN3035 = new TGraphErrors(5, ANpoint_3035 , AN_3035, ANpointErr, ANErr_3035);
	BlueBeamAN3035->SetName("BlueBeamAN3045");
	BlueBeamAN3035->SetTitle("Blue beam A_{N} for BBC cuts");
	BlueBeamAN3035->GetXaxis()->SetTitle("large west BBC cut");
	BlueBeamAN3035->GetYaxis()->SetTitle("Blue beam A_{N}");
	//BlueBeamAN3045->SetMarkerColor(28);
	BlueBeamAN3035->SetMarkerSize(2);
	BlueBeamAN3035->SetMarkerStyle(20);
	//BlueBeamAN3035->SetLineColor(28);
	BlueBeamAN3035->SetLineWidth(2);
	BlueBeamAN3035->Draw("P same");

	BlueBeamAN3540 = new TGraphErrors(5, ANpoint_3540 , AN_3540, ANpointErr, ANErr_3540);
	BlueBeamAN3540->SetName("BlueBeamAN3045");
	BlueBeamAN3540->SetTitle("Blue beam A_{N} for BBC cuts");
	BlueBeamAN3540->GetXaxis()->SetTitle("large west BBC cut");
	BlueBeamAN3540->GetYaxis()->SetTitle("Blue beam A_{N}");
	//BlueBeamA54045->SetMarkerColor(28);
	BlueBeamAN3540->SetMarkerSize(2);
	BlueBeamAN3540->SetMarkerStyle(20);
	//BlueBeamAN3540->SetLineColor(28);
	BlueBeamAN3540->SetLineWidth(2);
	BlueBeamAN3540->Draw("P same");

	BlueBeamAN4045 = new TGraphErrors(5, ANpoint_4045 , AN_4045, ANpointErr, ANErr_4045);
	BlueBeamAN4045->SetName("BlueBeamAN3045");
	BlueBeamAN4045->SetTitle("Blue beam A_{N} for BBC cuts");
	BlueBeamAN4045->GetXaxis()->SetTitle("large west BBC cut");
	BlueBeamAN4045->GetYaxis()->SetTitle("Blue beam A_{N}");
	//BlueBeam404545->SetMarkerColor(28);
	BlueBeamAN4045->SetMarkerSize(2);
	BlueBeamAN4045->SetMarkerStyle(20);
	//BlueBeamAN4045->SetLineColor(28);
	BlueBeamAN4045->SetLineWidth(2);
	BlueBeamAN4045->Draw("P same");

	//TLegend *leg = new TLegend(0.7,0.2,0.88,0.35);
	//leg->SetTextSize(0.03);
	//leg->AddEntry(BlueBeamAN1015,"0.10< x_{F} < 0.15 ","p");
	//leg->AddEntry(BlueBeamAN1520,"0.15< x_{F} < 0.20 ","p");
	//leg->AddEntry(BlueBeamAN2025,"0.20< x_{F} < 0.25 ","p");
	//leg->AddEntry(BlueBeamAN2530,"0.25< x_{F} < 0.30 ","p");
	//leg->AddEntry(BlueBeamAN3045,"0.30< x_{F} < 0.45 ","p");
	//leg->SetBorderSize(0);
	//leg->Draw("same");
//
	ANplot->SaveAs("fig/sys/FMS_BlueAN_largeBBCstudy_RG_3pnp_Sys.pdf");
//	ANplot->SaveAs("FMS_BlueAN_BBCstudy.pdf");
//
//	//cout << "x_F region	BBC 350	BBC 400	BBC 450	BBC 500	BBC 550" <<endl;
//	cout << "x_F region	BBC 450	BBC 500	BBC 550	BBC 600	BBC 650" <<endl;
//	cout << "0.1 - 0.15	" << 1.0 * fabs((AN_1015[0] - AN_1015[2])/AN_1015[2]) << "	" << 1.0 * fabs((AN_1015[1] - AN_1015[2])/AN_1015[2]) << " " << 1.0 * fabs((AN_1015[2] - AN_1015[2])/AN_1015[2]) << " " << 1.0 * fabs((AN_1015[3] - AN_1015[2])/AN_1015[2]) << " " << 1.0 * fabs((AN_1015[4] - AN_1015[2])/AN_1015[2]) << endl;
//	cout << "0.15 - 0.2	" << 1.0 * fabs((AN_1520[0] - AN_1520[2])/AN_1520[2]) << "	" << 1.0 * fabs((AN_1520[1] - AN_1520[2])/AN_1520[2]) << " " << 1.0 * fabs((AN_1520[2] - AN_1520[2])/AN_1520[2]) << " " << 1.0 * fabs((AN_1520[3] - AN_1520[2])/AN_1520[2]) << " " << 1.0 * fabs((AN_1520[4] - AN_1520[2])/AN_1520[2]) << endl;
//	cout << "0.2 - 0.25	" << 1.0 * fabs((AN_2025[0] - AN_2025[2])/AN_2025[2]) << "	" << 1.0 * fabs((AN_2025[1] - AN_2025[2])/AN_2025[2]) << " " << 1.0 * fabs((AN_2025[2] - AN_2025[2])/AN_2025[2]) << " " << 1.0 * fabs((AN_2025[3] - AN_2025[2])/AN_2025[2]) << " " << 1.0 * fabs((AN_2025[4] - AN_2025[2])/AN_2025[2]) << endl;
//	cout << "0.25 - 0.3	" << 1.0 * fabs((AN_2530[0] - AN_2530[2])/AN_2530[2]) << "	" << 1.0 * fabs((AN_2530[1] - AN_2530[2])/AN_2530[2]) << " " << 1.0 * fabs((AN_2530[2] - AN_2530[2])/AN_2530[2]) << " " << 1.0 * fabs((AN_2530[3] - AN_2530[2])/AN_2530[2]) << " " << 1.0 * fabs((AN_2530[4] - AN_2530[2])/AN_2530[2]) << endl;
//	cout << "0.3 - 0.45	" << 1.0 * fabs((AN_3045[0] - AN_3045[2])/AN_3045[2]) << "	" << 1.0 * fabs((AN_3045[1] - AN_3045[2])/AN_3045[2]) << " " << 1.0 * fabs((AN_3045[2] - AN_3045[2])/AN_3045[2]) << " " << 1.0 * fabs((AN_3045[3] - AN_3045[2])/AN_3045[2]) << " " << 1.0 * fabs((AN_3045[4] - AN_3045[2])/AN_3045[2]) << endl;
//
//
	TCanvas *ANplot = new TCanvas("ANPlot","",1024,768);
	ANplot->DrawFrame(2., -0.06, 250., 0.2);
	TH2D * temp = new TH2D("temp","Yellow beam A_{N}",8,0.15,0.45,30,-0.05,0.05);
	temp->GetYaxis()->SetTitle("Yellow beam A_{N}");
  	temp->GetYaxis()->SetTitleOffset(0.9);
  	temp->GetXaxis()->SetTitle("|x_{F}|");
  	temp->Draw();

	YellowBeamAN1520 = new TGraphErrors(5, ANpoint_1520 , YellowAN_1520, ANpointErr, YellowANErr_1520);
	YellowBeamAN1520->SetName("YellowBeamAN1520");
	YellowBeamAN1520->SetTitle("Yellow beam A_{N} for BBC cuts");
	YellowBeamAN1520->GetXaxis()->SetTitle("BBC threshold");
	YellowBeamAN1520->GetYaxis()->SetTitle("Yellow beam A_{N}");
	//YellowBeamAN1520->SetMarkerColor(2);
	YellowBeamAN1520->SetMarkerSize(2);
	YellowBeamAN1520->SetMarkerStyle(20);
	//YellowBeamAN1520->SetLineColor(2);
	YellowBeamAN1520->SetLineWidth(2);
	YellowBeamAN1520->Draw("P same");

	YellowBeamAN2025 = new TGraphErrors(5, ANpoint_2025 , YellowAN_2025, ANpointErr, YellowANErr_2025);
	YellowBeamAN2025->SetName("YellowBeamAN2025");
	YellowBeamAN2025->SetTitle("Yellow beam A_{N} for BBC cuts");
	YellowBeamAN2025->GetXaxis()->SetTitle("BBC threshold");
	YellowBeamAN2025->GetYaxis()->SetTitle("Yellow beam A_{N}");
	//YellowBeamAN2025->SetMarkerColor(3);
	YellowBeamAN2025->SetMarkerSize(2);
	YellowBeamAN2025->SetMarkerStyle(20);
	//YellowBeamAN2025->SetLineColor(3);
	YellowBeamAN2025->SetLineWidth(2);
	YellowBeamAN2025->Draw("P same");

	YellowBeamAN2530 = new TGraphErrors(5, ANpoint_2530, YellowAN_2530, ANpointErr, YellowANErr_2530);
	YellowBeamAN2530->SetName("YellowBeamAN2530");
	YellowBeamAN2530->SetTitle("Yellow beam A_{N} for BBC cuts");
	YellowBeamAN2530->GetXaxis()->SetTitle("BBC threshold");
	YellowBeamAN2530->GetYaxis()->SetTitle("Yellow beam A_{N}");
	YellowBeamAN2530->SetMarkerColor(13);
	YellowBeamAN2530->SetMarkerSize(2);
	YellowBeamAN2530->SetMarkerStyle(20);
	YellowBeamAN2530->SetLineColor(13);
	YellowBeamAN2530->SetLineWidth(2);
	YellowBeamAN2530->Draw("P same");

	YellowBeamAN3045 = new TGraphErrors(5, ANpoint_3035 , YellowAN_3035, ANpointErr, YellowANErr_3035);
	YellowBeamAN3045->SetName("YellowBeamAN3045");
	YellowBeamAN3045->SetTitle("Yellow beam A_{N} for BBC cuts");
	YellowBeamAN3045->GetXaxis()->SetTitle("BBC threshold");
	YellowBeamAN3045->GetYaxis()->SetTitle("Yellow beam A_{N}");
	//YellowBeamAN3045->SetMarkerColor(28);
	YellowBeamAN3045->SetMarkerSize(2);
	YellowBeamAN3045->SetMarkerStyle(20);
	//YellowBeamAN3045->SetLineColor(28);
	YellowBeamAN3045->SetLineWidth(2);
	YellowBeamAN3045->Draw("P same");

	YellowBeamAN3540 = new TGraphErrors(5, ANpoint_3540 , YellowAN_3540, ANpointErr, YellowANErr_3540);
	YellowBeamAN3540->SetName("YellowBeamAN1520");
	YellowBeamAN3540->SetTitle("Yellow beam A_{N} for BBC cuts");
	YellowBeamAN3540->GetXaxis()->SetTitle("BBC threshold");
	YellowBeamAN3540->GetYaxis()->SetTitle("Yellow beam A_{N}");
	//YellowBeam354020->SetMarkerColor(2);
	YellowBeamAN3540->SetMarkerSize(2);
	YellowBeamAN3540->SetMarkerStyle(20);
	//YellowBeam354020->SetLineColor(2);
	YellowBeamAN3540->SetLineWidth(2);
	YellowBeamAN3540->Draw("P same");

	YellowBeamAN4045 = new TGraphErrors(5, ANpoint_4045 , YellowAN_4045, ANpointErr, YellowANErr_4045);
	YellowBeamAN4045->SetTitle("Yellow beam A_{N} for BBC cuts");
	YellowBeamAN4045->GetXaxis()->SetTitle("BBC threshold");
	YellowBeamAN4045->GetYaxis()->SetTitle("Yellow beam A_{N}");
	//YellowBeam404520->SetMarkerColor(2);
	YellowBeamAN4045->SetMarkerSize(2);
	YellowBeamAN4045->SetMarkerStyle(20);
	//YellowBeam404520->SetLineColor(2);
	YellowBeamAN4045->SetLineWidth(2);
	YellowBeamAN4045->Draw("P same");

	ANplot->SaveAs("fig/sys/FMS_YellowAN_largeBBCstudy_RG_3pnp_Sys.pdf");
//	TLegend *leg = new TLegend(0.7,0.7,0.88,0.85);
//	leg->SetTextSize(0.03);
//	leg->AddEntry(YellowBeamAN1015,"0.10< x_{F} < 0.15 ","p");
//	leg->AddEntry(YellowBeamAN1520,"0.15< x_{F} < 0.20 ","p");
//	leg->AddEntry(YellowBeamAN2025,"0.20< x_{F} < 0.25 ","p");
//	leg->AddEntry(YellowBeamAN2530,"0.25< x_{F} < 0.30 ","p");
//	leg->AddEntry(YellowBeamAN3045,"0.30< x_{F} < 0.45 ","p");
//	leg->SetBorderSize(0);
//	leg->Draw("same");
//
//	ANplot->SaveAs("FMS_YellowAN_BBCstudy.pdf");
//	cout << "x_F region	BBC 350	BBC 400	BBC 450	BBC 500	BBC 550" <<endl;
//	cout << "0.1 - 0.15	" << 1.0 * fabs((YellowAN_1015[0] - YellowAN_1015[2])/YellowAN_1015[2]) << "	" << 1.0 * fabs((YellowAN_1015[1] - YellowAN_1015[2])/YellowAN_1015[2]) << " " << 1.0 * fabs((YellowAN_1015[2] - YellowAN_1015[2])/YellowAN_1015[2]) << " " << 1.0 * fabs((YellowAN_1015[3] - YellowAN_1015[2])/YellowAN_1015[2]) << " " << 1.0 * fabs((YellowAN_1015[4] - YellowAN_1015[2])/YellowAN_1015[2]) << endl;
//	cout << "0.15 - 0.2	" << 1.0 * fabs((YellowAN_1520[0] - YellowAN_1520[2])/YellowAN_1520[2]) << "	" << 1.0 * fabs((YellowAN_1520[1] - YellowAN_1520[2])/YellowAN_1520[2]) << " " << 1.0 * fabs((YellowAN_1520[2] - YellowAN_1520[2])/YellowAN_1520[2]) << " " << 1.0 * fabs((YellowAN_1520[3] - YellowAN_1520[2])/YellowAN_1520[2]) << " " << 1.0 * fabs((YellowAN_1520[4] - YellowAN_1520[2])/YellowAN_1520[2]) << endl;
//	cout << "0.2 - 0.25	" << 1.0 * fabs((YellowAN_2025[0] - YellowAN_2025[2])/YellowAN_2025[2]) << "	" << 1.0 * fabs((YellowAN_2025[1] - YellowAN_2025[2])/YellowAN_2025[2]) << " " << 1.0 * fabs((YellowAN_2025[2] - YellowAN_2025[2])/YellowAN_2025[2]) << " " << 1.0 * fabs((YellowAN_2025[3] - YellowAN_2025[2])/YellowAN_2025[2]) << " " << 1.0 * fabs((YellowAN_2025[4] - YellowAN_2025[2])/YellowAN_2025[2]) << endl;
//	cout << "0.25 - 0.3	" << 1.0 * fabs((YellowAN_2530[0] - YellowAN_2530[2])/YellowAN_2530[2]) << "	" << 1.0 * fabs((YellowAN_2530[1] - YellowAN_2530[2])/YellowAN_2530[2]) << " " << 1.0 * fabs((YellowAN_2530[2] - YellowAN_2530[2])/YellowAN_2530[2]) << " " << 1.0 * fabs((YellowAN_2530[3] - YellowAN_2530[2])/YellowAN_2530[2]) << " " << 1.0 * fabs((YellowAN_2530[4] - YellowAN_2530[2])/YellowAN_2530[2]) << endl;
//	cout << "0.3 - 0.45	" << 1.0 * fabs((YellowAN_3045[0] - YellowAN_3045[2])/YellowAN_3045[2]) << "	" << 1.0 * fabs((YellowAN_3045[1] - YellowAN_3045[2])/YellowAN_3045[2]) << " " << 1.0 * fabs((YellowAN_3045[2] - YellowAN_3045[2])/YellowAN_3045[2]) << " " << 1.0 * fabs((YellowAN_3045[3] - YellowAN_3045[2])/YellowAN_3045[2]) << " " << 1.0 * fabs((YellowAN_3045[4] - YellowAN_3045[2])/YellowAN_3045[2]) << endl;
//
//
//
//
//	TCanvas *ANplot = new TCanvas("ANPlot","",1024,768);
//	ANplot->DrawFrame(2., -0.06, 250., 0.2);
//	TH2D * temp = new TH2D("temp","Correlation uncertainty",8,-100,100,30,-0.4,0.4);
//	temp->GetYaxis()->SetTitle("#Delta A_{N} / #sigma_{AB}");
//  	temp->GetYaxis()->SetTitleOffset(0.9);
//  	temp->GetXaxis()->SetTitle("BBC difference");
//  	temp->Draw();
//
//	BlueBeamANCorr1015 = new TGraph(4, BBCpoint0_cor , ANCorr_1015);
//	BlueBeamANCorr1015->SetName("BlueBeamANCorr1015");
//	BlueBeamANCorr1015->SetTitle("Blue beam A_{N} for BBC cuts");
//	BlueBeamANCorr1015->GetXaxis()->SetTitle("BBC difference");
//	BlueBeamANCorr1015->GetYaxis()->SetTitle("#Delta A_{N} / #sigma_{AB}");
//	BlueBeamANCorr1015->SetMarkerColor(kBlue+1);
//	BlueBeamANCorr1015->SetMarkerSize(2);
//	BlueBeamANCorr1015->SetMarkerStyle(20);
//	BlueBeamANCorr1015->SetLineColor(kBlue+1);
//	BlueBeamANCorr1015->SetLineWidth(2);
//	BlueBeamANCorr1015->Draw("P same");
//
//	BlueBeamANCorr1520 = new TGraph(4, BBCpoint1_cor , ANCorr_1520);
//	BlueBeamANCorr1520->SetName("BlueBeamANCorr1520");
//	BlueBeamANCorr1520->SetTitle("Blue beam A_{N} for BBC cuts");
//	BlueBeamANCorr1520->GetXaxis()->SetTitle("BBC difference");
//	BlueBeamANCorr1520->GetYaxis()->SetTitle("#Delta A_{N} / #sigma_{AB}");
//	BlueBeamANCorr1520->SetMarkerColor(2);
//	BlueBeamANCorr1520->SetMarkerSize(2);
//	BlueBeamANCorr1520->SetMarkerStyle(20);
//	BlueBeamANCorr1520->SetLineColor(2);
//	BlueBeamANCorr1520->SetLineWidth(2);
//	BlueBeamANCorr1520->Draw("P same");
//
//	BlueBeamANCorr2025 = new TGraph(4, BBCpoint2_cor , ANCorr_2025);
//	BlueBeamANCorr2025->SetName("BlueBeamANCorr2025");
//	BlueBeamANCorr2025->SetTitle("Blue beam A_{N} for BBC cuts");
//	BlueBeamANCorr2025->GetXaxis()->SetTitle("BBC difference");
//	BlueBeamANCorr2025->GetYaxis()->SetTitle("#Delta A_{N} / #sigma_{AB}");
//	BlueBeamANCorr2025->SetMarkerColor(3);
//	BlueBeamANCorr2025->SetMarkerSize(2);
//	BlueBeamANCorr2025->SetMarkerStyle(20);
//	BlueBeamANCorr2025->SetLineColor(3);
//	BlueBeamANCorr2025->SetLineWidth(2);
//	BlueBeamANCorr2025->Draw("P same");
//
//	BlueBeamANCorr2530 = new TGraph(4, BBCpoint3_cor , ANCorr_2530);
//	BlueBeamANCorr2530->SetName("BlueBeamANCorr2530");
//	BlueBeamANCorr2530->SetTitle("Blue beam A_{N} for BBC cuts");
//	BlueBeamANCorr2530->GetXaxis()->SetTitle("BBC difference");
//	BlueBeamANCorr2530->GetYaxis()->SetTitle("#Delta A_{N} / #sigma_{AB}");
//	BlueBeamANCorr2530->SetMarkerColor(13);
//	BlueBeamANCorr2530->SetMarkerSize(2);
//	BlueBeamANCorr2530->SetMarkerStyle(20);
//	BlueBeamANCorr2530->SetLineColor(13);
//	BlueBeamANCorr2530->SetLineWidth(2);
//	BlueBeamANCorr2530->Draw("P same");
//
//	BlueBeamANCorr3045 = new TGraph(4, BBCpoint4_cor , ANCorr_3045);
//	BlueBeamANCorr3045->SetName("BlueBeamANCorr3045");
//	BlueBeamANCorr3045->SetTitle("Blue beam A_{N} for BBC cuts");
//	BlueBeamANCorr3045->GetXaxis()->SetTitle("BBC difference");
//	BlueBeamANCorr3045->GetYaxis()->SetTitle("#Delta A_{N} / #sigma_{AB}");
//	BlueBeamANCorr3045->SetMarkerColor(28);
//	BlueBeamANCorr3045->SetMarkerSize(2);
//	BlueBeamANCorr3045->SetMarkerStyle(20);
//	BlueBeamANCorr3045->SetLineColor(28);
//	BlueBeamANCorr3045->SetLineWidth(2);
//	BlueBeamANCorr3045->Draw("P same");
//
//	TLegend *leg = new TLegend(0.7,0.2,0.88,0.35);
//	leg->SetTextSize(0.03);
//	leg->AddEntry(BlueBeamANCorr1015,"0.10< x_{F} < 0.15 ","p");
//	leg->AddEntry(BlueBeamANCorr1520,"0.15< x_{F} < 0.20 ","p");
//	leg->AddEntry(BlueBeamANCorr2025,"0.20< x_{F} < 0.25 ","p");
//	leg->AddEntry(BlueBeamANCorr2530,"0.25< x_{F} < 0.30 ","p");
//	leg->AddEntry(BlueBeamANCorr3045,"0.30< x_{F} < 0.45 ","p");
//	leg->SetBorderSize(0);
//	leg->Draw("same");
//
//	//ANplot->SaveAs("FMS_BlueAN_BBCstudy_3pnp.pdf");
//	ANplot->SaveAs("FMS_BlueAN_BBCstudyCorr.pdf");
//
//
//	TCanvas *ANplot = new TCanvas("ANPlot","",1024,768);
//	ANplot->DrawFrame(2., -0.06, 250., 0.2);
//	TH2D * temp = new TH2D("temp","Blue beam A_{N} difference",8,430,700,30,-0.04,0.04);
//	temp->GetYaxis()->SetTitle("Blue beam A_{N} difference");
//  	temp->GetYaxis()->SetTitleOffset(0.9);
//  	temp->GetXaxis()->SetTitle("large west BBC cut");
//  	temp->Draw();
//
//	BlueBeamANdiff1015 = new TGraphErrors(5, BBCpoint0 , ANDiff_1015, BBCpointErr, ANDiff_un_1015);
//	BlueBeamANdiff1015->SetName("BlueBeamAN1015");
//	BlueBeamANdiff1015->SetTitle("Blue beam A_{N} difference for BBC cuts");
//	BlueBeamANdiff1015->GetXaxis()->SetTitle("large west BBC cut");
//	BlueBeamANdiff1015->GetYaxis()->SetTitle("Blue beam A_{N} difference");
//	BlueBeamANdiff1015->SetMarkerColor(kBlue+1);
//	BlueBeamANdiff1015->SetMarkerSize(2);
//	BlueBeamANdiff1015->SetMarkerStyle(20);
//	BlueBeamANdiff1015->SetLineColor(kBlue+1);
//	BlueBeamANdiff1015->SetLineWidth(2);
//	BlueBeamANdiff1015->Draw("P same");
//
//	BlueBeamANdiff1520 = new TGraphErrors(5, BBCpoint1 , ANDiff_1520, BBCpointErr, ANDiff_un_1520);
//	BlueBeamANdiff1520->SetName("BlueBeamAN1520");
//	BlueBeamANdiff1520->SetTitle("Blue beam A_{N} difference for BBC cuts");
//	BlueBeamANdiff1520->GetXaxis()->SetTitle("large west BBC cut");
//	BlueBeamANdiff1520->GetYaxis()->SetTitle("Blue beam A_{N} difference");
//	BlueBeamANdiff1520->SetMarkerColor(2);
//	BlueBeamANdiff1520->SetMarkerSize(2);
//	BlueBeamANdiff1520->SetMarkerStyle(20);
//	BlueBeamANdiff1520->SetLineColor(2);
//	BlueBeamANdiff1520->SetLineWidth(2);
//	BlueBeamANdiff1520->Draw("P same");
//
//	BlueBeamANdiff2025 = new TGraphErrors(5, BBCpoint2 , ANDiff_2025, BBCpointErr, ANDiff_un_2025);
//	BlueBeamANdiff2025->SetName("BlueBeamAN2025");
//	BlueBeamANdiff2025->SetTitle("Blue beam A_{N} difference for BBC cuts");
//	BlueBeamANdiff2025->GetXaxis()->SetTitle("large west BBC cut");
//	BlueBeamANdiff2025->GetYaxis()->SetTitle("Blue beam A_{N} difference");
//	BlueBeamANdiff2025->SetMarkerColor(3);
//	BlueBeamANdiff2025->SetMarkerSize(2);
//	BlueBeamANdiff2025->SetMarkerStyle(20);
//	BlueBeamANdiff2025->SetLineColor(3);
//	BlueBeamANdiff2025->SetLineWidth(2);
//	BlueBeamANdiff2025->Draw("P same");
//
//	BlueBeamANdiff2530 = new TGraphErrors(5, BBCpoint3 , ANDiff_2530, BBCpointErr, ANDiff_un_2530);
//	BlueBeamANdiff2530->SetName("BlueBeamAN2530");
//	BlueBeamANdiff2530->SetTitle("Blue beam A_{N} difference for BBC cuts");
//	BlueBeamANdiff2530->GetXaxis()->SetTitle("large west BBC cut");
//	BlueBeamANdiff2530->GetYaxis()->SetTitle("Blue beam A_{N} difference");
//	BlueBeamANdiff2530->SetMarkerColor(13);
//	BlueBeamANdiff2530->SetMarkerSize(2);
//	BlueBeamANdiff2530->SetMarkerStyle(20);
//	BlueBeamANdiff2530->SetLineColor(13);
//	BlueBeamANdiff2530->SetLineWidth(2);
//	BlueBeamANdiff2530->Draw("P same");
//
//	BlueBeamANdiff3045 = new TGraphErrors(5, BBCpoint4 , ANDiff_3045, BBCpointErr, ANDiff_un_3045);
//	BlueBeamANdiff3045->SetName("BlueBeamAN3045");
//	BlueBeamANdiff3045->SetTitle("Blue beam A_{N} difference for BBC cuts");
//	BlueBeamANdiff3045->GetXaxis()->SetTitle("large west BBC cut");
//	BlueBeamANdiff3045->GetYaxis()->SetTitle("Blue beam A_{N} difference");
//	BlueBeamANdiff3045->SetMarkerColor(28);
//	BlueBeamANdiff3045->SetMarkerSize(2);
//	BlueBeamANdiff3045->SetMarkerStyle(20);
//	BlueBeamANdiff3045->SetLineColor(28);
//	BlueBeamANdiff3045->SetLineWidth(2);
//	BlueBeamANdiff3045->Draw("P same");
//
//	TLegend *leg = new TLegend(0.7,0.2,0.88,0.35);
//	leg->SetTextSize(0.03);
//	leg->AddEntry(BlueBeamANdiff1015,"0.10< x_{F} < 0.15 ","p");
//	leg->AddEntry(BlueBeamANdiff1520,"0.15< x_{F} < 0.20 ","p");
//	leg->AddEntry(BlueBeamANdiff2025,"0.20< x_{F} < 0.25 ","p");
//	leg->AddEntry(BlueBeamANdiff2530,"0.25< x_{F} < 0.30 ","p");
//	leg->AddEntry(BlueBeamANdiff3045,"0.30< x_{F} < 0.45 ","p");
//	leg->SetBorderSize(0);
//	leg->Draw("same");
//
//	ANplot->SaveAs("FMS_BlueANdiff_BBCstudy.pdf");
//
//
//
//	TCanvas *ANplot = new TCanvas("ANPlot","",1024,768);
//	ANplot->DrawFrame(2., -0.06, 250., 0.2);
//	TH2D * temp = new TH2D("temp","Yellow beam A_{N} difference",8,430,700,30,-0.04,0.04);
//	temp->GetYaxis()->SetTitle("Yellow beam A_{N} difference");
//  	temp->GetYaxis()->SetTitleOffset(0.9);
//  	temp->GetXaxis()->SetTitle("large west BBC cut");
//  	temp->Draw();
//
//	YellowBeamANdiff1015 = new TGraphErrors(5, BBCpoint0 , YellowANDiff_1015, BBCpointErr, YellowANDiff_un_1015);
//	YellowBeamANdiff1015->SetName("YellowBeamAN1015");
//	YellowBeamANdiff1015->SetTitle("Yellow beam A_{N} difference for BBC cuts");
//	YellowBeamANdiff1015->GetXaxis()->SetTitle("large west BBC cut");
//	YellowBeamANdiff1015->GetYaxis()->SetTitle("Yellow beam A_{N} difference");
//	YellowBeamANdiff1015->SetMarkerColor(kBlue+1);
//	YellowBeamANdiff1015->SetMarkerSize(2);
//	YellowBeamANdiff1015->SetMarkerStyle(20);
//	YellowBeamANdiff1015->SetLineColor(kBlue+1);
//	YellowBeamANdiff1015->SetLineWidth(2);
//	YellowBeamANdiff1015->Draw("P same");
//
//	YellowBeamANdiff1520 = new TGraphErrors(5, BBCpoint1 , YellowANDiff_1520, BBCpointErr, YellowANDiff_un_1520);
//	YellowBeamANdiff1520->SetName("YellowBeamAN1520");
//	YellowBeamANdiff1520->SetTitle("Yellow beam A_{N} difference for BBC cuts");
//	YellowBeamANdiff1520->GetXaxis()->SetTitle("large west BBC cut");
//	YellowBeamANdiff1520->GetYaxis()->SetTitle("Yellow beam A_{N} difference");
//	YellowBeamANdiff1520->SetMarkerColor(2);
//	YellowBeamANdiff1520->SetMarkerSize(2);
//	YellowBeamANdiff1520->SetMarkerStyle(20);
//	YellowBeamANdiff1520->SetLineColor(2);
//	YellowBeamANdiff1520->SetLineWidth(2);
//	YellowBeamANdiff1520->Draw("P same");
//
//	YellowBeamANdiff2025 = new TGraphErrors(5, BBCpoint2 , YellowANDiff_2025, BBCpointErr, YellowANDiff_un_2025);
//	YellowBeamANdiff2025->SetName("YellowBeamAN2025");
//	YellowBeamANdiff2025->SetTitle("Yellow beam A_{N} difference for BBC cuts");
//	YellowBeamANdiff2025->GetXaxis()->SetTitle("large west BBC cut");
//	YellowBeamANdiff2025->GetYaxis()->SetTitle("Yellow beam A_{N} difference");
//	YellowBeamANdiff2025->SetMarkerColor(3);
//	YellowBeamANdiff2025->SetMarkerSize(2);
//	YellowBeamANdiff2025->SetMarkerStyle(20);
//	YellowBeamANdiff2025->SetLineColor(3);
//	YellowBeamANdiff2025->SetLineWidth(2);
//	YellowBeamANdiff2025->Draw("P same");
//
//	YellowBeamANdiff2530 = new TGraphErrors(5, BBCpoint3 , YellowANDiff_2530, BBCpointErr, YellowANDiff_un_2530);
//	YellowBeamANdiff2530->SetName("YellowBeamAN2530");
//	YellowBeamANdiff2530->SetTitle("Yellow beam A_{N} difference for BBC cuts");
//	YellowBeamANdiff2530->GetXaxis()->SetTitle("large west BBC cut");
//	YellowBeamANdiff2530->GetYaxis()->SetTitle("Yellow beam A_{N} difference");
//	YellowBeamANdiff2530->SetMarkerColor(13);
//	YellowBeamANdiff2530->SetMarkerSize(2);
//	YellowBeamANdiff2530->SetMarkerStyle(20);
//	YellowBeamANdiff2530->SetLineColor(13);
//	YellowBeamANdiff2530->SetLineWidth(2);
//	YellowBeamANdiff2530->Draw("P same");
//
//	YellowBeamANdiff3045 = new TGraphErrors(5, BBCpoint4 , YellowANDiff_3045, BBCpointErr, YellowANDiff_un_3045);
//	YellowBeamANdiff3045->SetName("YellowBeamAN3045");
//	YellowBeamANdiff3045->SetTitle("Yellow beam A_{N} difference for BBC cuts");
//	YellowBeamANdiff3045->GetXaxis()->SetTitle("large west BBC cut");
//	YellowBeamANdiff3045->GetYaxis()->SetTitle("Yellow beam A_{N} difference");
//	YellowBeamANdiff3045->SetMarkerColor(28);
//	YellowBeamANdiff3045->SetMarkerSize(2);
//	YellowBeamANdiff3045->SetMarkerStyle(20);
//	YellowBeamANdiff3045->SetLineColor(28);
//	YellowBeamANdiff3045->SetLineWidth(2);
//	YellowBeamANdiff3045->Draw("P same");
//
//	TLegend *leg = new TLegend(0.7,0.2,0.88,0.35);
//	leg->SetTextSize(0.03);
//	leg->AddEntry(BlueBeamANdiff1015,"0.10< |x_{F}| < 0.15 ","p");
//	leg->AddEntry(BlueBeamANdiff1520,"0.15< |x_{F}| < 0.20 ","p");
//	leg->AddEntry(BlueBeamANdiff2025,"0.20< |x_{F}| < 0.25 ","p");
//	leg->AddEntry(BlueBeamANdiff2530,"0.25< |x_{F}| < 0.30 ","p");
//	leg->AddEntry(BlueBeamANdiff3045,"0.30< |x_{F}| < 0.45 ","p");
//	leg->SetBorderSize(0);
//	leg->Draw("same");
//
//	ANplot->SaveAs("FMS_YellowANdiff_BBCstudy.pdf");
//
//
//    const int xFbin=5;
//
//	Double_t XFpoint_plot[] = {0.125,0.175,0.225,0.275,0.325};
//	Double_t XFpointYellow_plot[] = {0.120,0.170,0.220,0.270,0.320};
//	BlueBeamAN_Far = new TGraphErrors(xFbin , XFpoint_plot , ANDiff_far , BBCpointErr , ANDiff_un_far);
//	BlueBeamAN_Far->SetName("BlueBeamANDiff");
//	BlueBeamAN_Far->SetTitle("A_{N} (x_{F} > 0)");
//	BlueBeamAN_Far->GetXaxis()->SetTitle("|X_{F}|");
//	BlueBeamAN_Far->GetYaxis()->SetTitle("A_{N}");
//	TF1 *ANconstant = new TF1("ANconstant","[0]");
//	BlueBeamAN_Far->Fit("ANconstant");
//	ANconstant->SetLineWidth(2);
//	ANconstant->SetLineColorAlpha(1,0.5);
//	ANconstant->SetLineColor(kBlue+1);
//	cout<<"Blue beam A_{N} with constant fit:"<<ANconstant->GetParameter(0)<<"+/-"<<ANconstant->GetParError(0)<<" value/error ratio:"<<1.0*fabs(ANconstant->GetParameter(0))/(ANconstant->GetParError(0))<<endl;
//	YellowBeamAN_Far = new TGraphErrors(xFbin , XFpointYellow_plot , YellowANDiff_far , BBCpointErr,  YellowANDiff_un_far);
//	YellowBeamAN_Far->SetName("BlueBeamAN");
//	YellowBeamAN_Far->SetTitle("A_{N} (x_{F} < 0)");
//	YellowBeamAN_Far->GetXaxis()->SetTitle("|X_{F}|");
//	YellowBeamAN_Far->GetYaxis()->SetTitle("A_{N}");
//	TF1 *ANconstantY = new TF1("ANconstantY","[0]");
//	YellowBeamAN_Far->Fit("ANconstantY");
//	ANconstantY->SetLineWidth(2);
//	ANconstantY->SetLineColorAlpha(1,0.5);
//	ANconstantY->SetLineColor(kRed+1);
//	cout<<"Yellow beam A_{N} with constant fit:"<<ANconstantY->GetParameter(0)<<"+/-"<<ANconstantY->GetParError(0)<<" value/error ratio:"<<1.0*fabs(ANconstantY->GetParameter(0))/(ANconstantY->GetParError(0))<<endl;
//	TCanvas *ANplot = new TCanvas("ANPlot","",1024,768);
//	ANplot->DrawFrame(2., -0.06, 250., 0.2);
//	TH2D * temp = new TH2D("temp","A_{N} difference",8,0.10,0.35,30,-0.02,0.02);
//	temp->GetYaxis()->SetTitle("A_{N} difference");
//  	temp->GetYaxis()->SetTitleOffset(0.9);
//  	temp->GetXaxis()->SetTitle("|x_{F}|");
//  	temp->Draw();
//	YellowBeamAN_Far->SetMarkerColor(kRed+1);
//	YellowBeamAN_Far->SetMarkerSize(2);
//	YellowBeamAN_Far->SetMarkerStyle(22);
//	YellowBeamAN_Far->SetLineWidth(2);
//	YellowBeamAN_Far->SetLineColor(kRed+1);
//	YellowBeamAN_Far->Draw("P");
//	BlueBeamAN_Far->SetMarkerColor(kBlue+1);
//	BlueBeamAN_Far->SetMarkerSize(2);
//	BlueBeamAN_Far->SetMarkerStyle(20);
//	BlueBeamAN_Far->SetLineColor(kBlue+1);
//	BlueBeamAN_Far->SetLineWidth(2);
//	BlueBeamAN_Far->Draw("P");
//	ANconstantY->Draw("same");
//	ANconstant->Draw("same");
//	TLegend *leg = new TLegend(0.7,0.2,0.88,0.35);
//	leg->SetTextSize(0.06);
//	leg->AddEntry(BlueBeamAN_Far,"x_{F} > 0","p");
//	leg->AddEntry(YellowBeamAN_Far,"x_{F} < 0","p");
//	leg->SetBorderSize(0);
//	leg->Draw("same");
//
//	ANplot->SaveAs("FMS_ANdiff_Sys_Far.pdf");



}
