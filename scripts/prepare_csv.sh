#!/bin/bash
numbins=7 #ptrange-1 entries
ini=0
fin=$numbins
ptrange=(30 50 70 100 140 200 300 600)
# Open the produced .csv file (e.g. kin_calib.csv) which should be located inside the discriminant directory (e.g. DeepCSVBDisc_fits) in the fit directory.
# Remove quotation marks from around SF values (last column).
#Type :
#$>cat kin_calib.csv | grep central | awk '{printf "%.12f\n", $11}' and copy the output in sfval
#Replace the quotation marks in .csv and save.
sfval=(
0.956522166729
0.955152809620
0.964328587055
0.961133480072
0.955408751965
0.939192593098
0.878094434738
0.952563345432
0.938796758652
0.944189071655
0.944512963295
0.935053765774
0.914072155952
0.850596964359
0.942229092121
0.924089431763
0.931741058826
0.928359806538
0.917947828770
0.891818225384
0.802140533924
)
#Remember to change "closure" to "mistag" and "pu" to "pileup" in sfb_report.tex
syst=("jer qcdscale sel trig jes mistag pileup isrDef fsrDef")
# Execute this script ./prepare_csv.sh > CSVv2_Kin.csv and follow next 3 steps:
#1. Open kin_calib.csv. All replace all 'up_statistic' with 'up' and all 'up_total' with 'up_statistic'. Do the same for down.
#2. Change statistics -> statistic 0,$s/statistics/statistic/g
#   Invert down_statistic and down, and same for up <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<????
#3. $>cat kin_calib.csv | grep down
# and
#   $>cat kin_calib.csv | grep up
# Copy the output in the new .csv file (CSVv2_Kin.csv)
#Finally compare some cases for kin_calib.csv, sfb_report.tex, and CSVv2_Kin.csv to make sure that the results are consistent
#cat CSVv2_Kin.csv | grep central; cat CSVv2_Kin.csv | grep up,; cat CSVv2_Kin.csv | grep down,; VS cat sfb_report.tex | grep SF

#The part related to stat is commented for the moment and taken from the .csv file produced by default
#Make sure that there are not lines like ${\rm SF}_{\rm b}$ & $ [ 988.3 \pm 3.3 \pm 3.5 ] \times10^{-3} $  \\
#They have to appear as ${\rm SF}_{\rm b}$ & $  0.9883 \pm 0.0033 \pm 0.0035 $  \\
#Make sure the following command provides the right output (may need to add a space in pm of sfb_report.tex: 0,$s/pm/pm /g)
#Test it once to see everything is reasonable
#stat=`cat sfb_report.tex | grep SF | awk '{printf "%.12f\n", $8}'`

echo "kin ;OperatingPoint, measurementType, sysType, jetFlavor, etaMin, etaMax, ptMin, ptMax, discrMin, discrMax, formula"
for (( wp=0; wp<3; wp++)); do
 #Central
 p=0
 l=0
 r=1
 for s in ${sfval[@]}; do
  if [[ "$ini" -le "$p" ]] && [[ "$p" -lt "$fin" ]]; then
   echo "$wp, kin, central, 0, -2.4, 2.4, ${ptrange[$l]}, ${ptrange[$r]}, 0, 1, \""${sfval[$p]}"\""
   let l=l+1
   let r=r+1
  fi
  let p=p+1
 done
 #Down
 #Statistics
 #p=0
 #l=0
 #r=1
 #for s in $stat; do
 # if [[ "$ini" -le "$p" ]] && [[ "$p" -lt "$fin" ]]; then
 #  valsys=$(awk "BEGIN {printf \"%.12f\",${sfval[$p]}-$s}")
 #  echo "$wp, kin, down_statistic, 0, -2.4, 2.4, ${ptrange[$l]}, ${ptrange[$r]}, 0, 1, \""$valsys"\""
 #  let l=l+1
 #  let r=r+1
 # fi
 # let p=p+1
 #done
 #Systematics
 for sys in $syst; do
  sy=`cat sfb_report.tex | grep $sys | awk '{printf "%.12f\n", $6}'`
  p=0
  l=0
  r=1
  for s in $sy; do
   if [[ "$ini" -le "$p" ]] && [[ "$p" -lt "$fin" ]]; then
    valsys=$(awk "BEGIN {printf \"%.12f\",${sfval[$p]}-${sfval[$p]}*sqrt($s*$s)}") #sqrt($s*$s) is to make $s positive
    echo "$wp, kin, down_$sys, 0, -2.4, 2.4, ${ptrange[$l]}, ${ptrange[$r]}, 0, 1, \""$valsys"\""
    let l=l+1
    let r=r+1
   fi
   let p=p+1
  done
 done
 #Up
 #Statistics
 #p=0
 #l=0
 #r=1
 #for s in $stat; do
 # if [[ "$ini" -le "$p" ]] && [[ "$p" -lt "$fin" ]]; then
 #  valsys=$(awk "BEGIN {printf \"%.12f\",${sfval[$p]}+$s}")
 #  echo "$wp, kin, up_statistic, 0, -2.4, 2.4, ${ptrange[$l]}, ${ptrange[$r]}, 0, 1, \""$valsys"\""
 #  let l=l+1
 #  let r=r+1
 # fi
 # let p=p+1
 #done
 #Systematics
 for sys in $syst; do
  sy=`cat sfb_report.tex | grep $sys | awk '{printf "%.12f\n", $8}'`
  p=0
  l=0
  r=1
  for s in $sy; do
   if [[ "$ini" -le "$p" ]] && [[ "$p" -lt "$fin" ]]; then
    valsys=$(awk "BEGIN {printf \"%.12f\",${sfval[$p]}+${sfval[$p]}*sqrt($s*$s)}")
    echo "$wp, kin, up_$sys, 0, -2.4, 2.4, ${ptrange[$l]}, ${ptrange[$r]}, 0, 1, \""$valsys"\""
    let l=l+1
    let r=r+1
   fi
   let p=p+1
  done
 done
 let ini=ini+numbins
 let fin=fin+numbins
done
