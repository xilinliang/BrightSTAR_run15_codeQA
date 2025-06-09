#!/bin/csh

set process = "$1"
set mode = "$2"
switch ("$1")

    case SE:

	    set jobMacro = 'jobMacroRun15WestAna.C'     
	    switch ("$2")

	    	case AN:
			
	    		set output_root = 'Run15FMSXFCalc_Ana_$JOBINDEX.root'
			set output_rootall = 'Run15FMSXFCalc_Ana_*.root'
			set output_destination = 'root_result/Run15FMSWestAna/'
  			set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root"'\",\"'"$mode"'\"\)'
			set argument2 = ""
			set argument3 = ""
			set argument4 = "" 
			breaksw

	    	case smallBBC:
			
	    		set output_root1 = 'Run15FMSXFCalc_SmallBBCWp20_$JOBINDEX.root'
	    		set output_root2 = 'Run15FMSXFCalc_SmallBBCWp10_$JOBINDEX.root'
	    		set output_root3 = 'Run15FMSXFCalc_SmallBBCWm10_$JOBINDEX.root'
	    		set output_root4 = 'Run15FMSXFCalc_SmallBBCWm20_$JOBINDEX.root'
			set output_rootall = 'Run15FMSXFCalc_SmallBBCW*.root'
			set output_destination = 'root_result/Run15FMSWestSys/'
  			set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root1"'\",\"smallBBCp20\"\)'
  			set argument2 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root2"'\",\"smallBBCp10\"\)'
  			set argument3 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root3"'\",\"smallBBCm10\"\)'
  			set argument4 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root4"'\",\"smallBBCm20\"\)'
			breaksw

	    	case largeBBC:
			
	    		set output_root1 = 'Run15FMSXFCalc_LargeBBCWp20_$JOBINDEX.root'
	    		set output_root2 = 'Run15FMSXFCalc_LargeBBCWp10_$JOBINDEX.root'
	    		set output_root3 = 'Run15FMSXFCalc_LargeBBCWm10_$JOBINDEX.root'
	    		set output_root4 = 'Run15FMSXFCalc_LargeBBCWm20_$JOBINDEX.root'
			set output_rootall = 'Run15FMSXFCalc_LargeBBCW*.root'
			set output_destination = 'root_result/Run15FMSWestSys/'
  			set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root1"'\",\"largeBBCp20\"\)'
  			set argument2 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root2"'\",\"largeBBCp10\"\)'
  			set argument3 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root3"'\",\"largeBBCm10\"\)'
  			set argument4 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root4"'\",\"largeBBCm20\"\)'
			breaksw

	    	case ROF:
			
	    		set output_root = 'Run15FMSXFCalc_ROF_$JOBINDEX.root'
			set output_rootall = 'Run15FMSXFCalc_ROF_*.root'
			set output_destination = 'root_result/Run15FMSWestSys/'
  			set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root"'\",\"'"$mode"'\"\)'
			set argument2 = ""
			set argument3 = ""
			set argument4 = "" 
			breaksw

	    	case Esum:
			
	    		set output_root1 = 'Run15FMSXFCalc_Esump10_$JOBINDEX.root'
	    		set output_root2 = 'Run15FMSXFCalc_Esump5_$JOBINDEX.root'
	    		set output_root3 = 'Run15FMSXFCalc_Esumm5_$JOBINDEX.root'
	    		set output_root4 = 'Run15FMSXFCalc_Esumm10_$JOBINDEX.root'
			set output_rootall = 'Run15FMSXFCalc_Esum*.root'
			set output_destination = 'root_result/Run15FMSWestSys/'
  			set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root1"'\",\"Esump10\"\)'
  			set argument2 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root2"'\",\"Esump5\"\)'
  			set argument3 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root3"'\",\"Esumm5\"\)'
  			set argument4 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root4"'\",\"Esumm10\"\)'
			breaksw

	    	default:
			echo "Wrong mode!"
			exit 1
			breaksw

	    endsw

	    breaksw
    default:
	    echo "Wrong process!"
	    exit 1
	    breaksw
endsw

echo "process: $process"
echo "jobmacro: $jobMacro"
echo "mode: $mode"

set xmlfilename = "submit_job/submit_$1_$2.xml"
if (-e $xmlfilename) then
	rm $xmlfilename
endif

cat > $xmlfilename << EOF
<?xml version="1.0" encoding="utf-8" ?>
<job maxFilesPerProcess="1" minFilesPerProcess="1" filesPerHour="1" simulateSubmission="false"     >
<command>
  source setup.csh
  $argument1
  $argument2
  $argument3
  $argument4
  ls
</command>


  <SandBox installer="ZIP">
    <Package>
	    <File>file:submit_job/$jobMacro</File>      
      <File>file:.sl73_gcc485</File>
      <File>file:diffAnalysis/lib/libDiffAnalysis.so</File>
      <File>file:rootlogon.C</File>         
      <File>file:polarization_fms.txt</File>         
      <File>file:run15fmsFill_run.list</File>         
      <File>file:setup.csh</File>           
      <File>file:database</File>        
      <File>file:StRoot</File>
    </Package>
  </SandBox>

	<input URL="filelist:/star/data01/pwg/liangxl/BrightSTAR_run15/NanoDstRun15FMSlist.list" />

  <stdout URL="file:$STARHOME/jobOutput/stdout-\$JOBID.out" />
  <stderr URL="file:$STARHOME/jobOutput/err_\$JOBID.out" />
  <output fromScratch="$output_rootall" toURL="file:$STARHOME/$output_destination"/> 

  <output fromScratch="*.log" toURL="file:$STARHOME/jobOutput/"/>
  <Generator>
    <Location>./jobs</Location>
    <ReportLocation>$STARHOME/jobOutput/</ReportLocation>
  </Generator>

</job>

EOF

star-submit $xmlfilename

