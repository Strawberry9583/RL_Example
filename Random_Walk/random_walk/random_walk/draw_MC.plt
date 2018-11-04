

set datafile separator comma
set xrange [0:7]
set yrange [0.0:1.0]
set xlabel 'state num'
set ylabel 'state value'
set grid
plot '../data/MC_100_7_unbatched.csv' with linespoints pointtype 1
replot '../data/MC_10_7_unbatched.csv' with linespoints pointtype 2
replot '../data/MC_50_7_unbatched.csv' with linespoints pointtype 3
replot '../data/MC_true_value_7.csv' with linespoints pointtype 4
replot '../data/MC_500_7_unbatched.csv' with linespoints pointtype 5
replot '../data/MC_1000_7_unbatched.csv' with linespoints pointtype 6
replot '../data/MC_10000_7_unbatched.csv' with linespoints pointtype 7
replot '../data/MC_20000_7_unbatched.csv' with linespoints pointtype 8
pause mouse