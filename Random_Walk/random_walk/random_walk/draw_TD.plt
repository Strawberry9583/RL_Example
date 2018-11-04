
set datafile separator comma
set xrange [0:7]
set yrange [0.0:1.0]
set xlabel 'state num'
set ylabel 'state value'
set grid
plot '../data/TD_100_7_unbatched.csv' with linespoints pointtype 1
replot '../data/TD_10_7_unbatched.csv' with linespoints pointtype 2
replot '../data/TD_50_7_unbatched.csv' with linespoints pointtype 3
replot '../data/TD_true_value_7.csv' with linespoints pointtype 4
replot '../data/TD_500_7_unbatched.csv' with linespoints pointtype 5
pause mouse