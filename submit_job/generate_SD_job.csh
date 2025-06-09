#!/bin/csh

set process = "$1"
set mode = "$2"
switch ("$1")

    case SD:

	    set jobMacro = 'jobMacroRun15EastAna.C'     
	    switch ("$2")

	    	case AN:
			
	    		set output_root = 'Run15FMSXFCalc_Ana_$JOBINDEX.root'
			set output_rootall = 'Run15FMSXFCalc_Ana_*.root'
			set output_destination = 'root_result/Run15FMSEastAna/'
  			set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root"'\",\"'"$mode"'\",\"'"$process"'\"\)'
			set argument2 = ""
			set argument3 = ""
			set argument4 = "" 
			breaksw

	    	case smallBBC:
			
	    		set output_root1 = 'Run15FMSXFCalc_SmallBBCEp20_$JOBINDEX.root'
	    		set output_root2 = 'Run15FMSXFCalc_SmallBBCEp10_$JOBINDEX.root'
	    		set output_root3 = 'Run15FMSXFCalc_SmallBBCEm10_$JOBINDEX.root'
	    		set output_root4 = 'Run15FMSXFCalc_SmallBBCEm20_$JOBINDEX.root'
			set output_rootall = 'Run15FMSXFCalc_SmallBBCE*.root'
			set output_destination = 'root_result/Run15FMSEastSys/'
  			set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root1"'\",\"smallBBCp20\",\"'"$process"'\"\)'
  			set argument2 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root2"'\",\"smallBBCp10\",\"'"$process"'\"\)'
  			set argument3 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root3"'\",\"smallBBCm10\",\"'"$process"'\"\)'
  			set argument4 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root4"'\",\"smallBBCm20\",\"'"$process"'\"\)'
			breaksw

	    	case largeBBC:
			
	    		set output_root1 = 'Run15FMSXFCalc_LargeBBCEp20_$JOBINDEX.root'
	    		set output_root2 = 'Run15FMSXFCalc_LargeBBCEp10_$JOBINDEX.root'
	    		set output_root3 = 'Run15FMSXFCalc_LargeBBCEm10_$JOBINDEX.root'
	    		set output_root4 = 'Run15FMSXFCalc_LargeBBCEm20_$JOBINDEX.root'
			set output_rootall = 'Run15FMSXFCalc_LargeBBCE*.root'
			set output_destination = 'root_result/Run15FMSEastSys/'
  			set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root1"'\",\"largeBBCp20\",\"'"$process"'\"\)'
  			set argument2 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root2"'\",\"largeBBCp10\",\"'"$process"'\"\)'
  			set argument3 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root3"'\",\"largeBBCm10\",\"'"$process"'\"\)'
  			set argument4 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root4"'\",\"largeBBCm20\",\"'"$process"'\"\)'
			breaksw

	    	case ROF:
			
	    		set output_root = 'Run15FMSXFCalc_ROFEast_$JOBINDEX.root'
			set output_rootall = 'Run15FMSXFCalc_ROFEast_*.root'
			set output_destination = 'root_result/Run15FMSEastSys/'
  			set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root"'\",\"'"$mode"'\",\"'"$process"'\"\)'
			set argument2 = ""
			set argument3 = ""
			set argument4 = "" 
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

