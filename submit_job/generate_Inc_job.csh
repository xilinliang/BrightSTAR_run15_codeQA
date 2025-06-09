#!/bin/csh

set process = "$1"
switch ("$1")

    case Inc:

	    set jobMacro = 'jobMacroRun15IncAna.C'     
	    set output_root = 'Run15FMSXFCalc_Ana_$JOBINDEX.root'
	    set output_rootall = 'Run15FMSXFCalc_Ana_*.root'
	    set output_destination = 'root_result/Run15FMSIncAna/'
  	    set argument1 = 'root4star -l -q -b '"$jobMacro"'\(\"\$INPUTFILE0\",\"'"$output_root"'\"\)'

	    breaksw
    default:
	    echo "Wrong process!"
	    exit 1
	    breaksw
endsw

echo "process: $process"
echo "jobmacro: $jobMacro"

set xmlfilename = "submit_job/submit_$1.xml"
if (-e $xmlfilename) then
	rm $xmlfilename
endif

cat > $xmlfilename << EOF
<?xml version="1.0" encoding="utf-8" ?>
<job maxFilesPerProcess="1" minFilesPerProcess="1" filesPerHour="1" simulateSubmission="false"     >
<command>
  source setup.csh
  $argument1
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
      <File>file:run15fmsrunnumber_diff.txt</File>         
      <File>file:setup.csh</File>           
      <File>file:database</File>        
      <File>file:StRoot</File>
    </Package>
  </SandBox>


	<input URL="filelist:/star/data01/pwg/liangxl/BrightSTAR_run15/run15_inc_NanoDstList.list" />
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

