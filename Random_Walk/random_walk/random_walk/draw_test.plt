set term push
set terminal jpeg size 1200,800
set output './output.jpeg'
set datafile separator comma
set xrange [0:7]
set yrange [0.0:1.0]
set xlabel 'state num'
set ylabel 'state value'
set grid
plot '../data/MC_100_7_unbatched.csv' with linespoints pointtype 1, \
'../data/MC_10_7_unbatched.csv' with linespoints pointtype 2, \
'../data/MC_50_7_unbatched.csv' with linespoints pointtype 3, \
'../data/MC_true_value_7.csv' with linespoints pointtype 4, \
'../data/MC_500_7_unbatched.csv' with linespoints pointtype 5, \
'../data/MC_1000_7_unbatched.csv' with linespoints pointtype 6, \
'../data/MC_10000_7_unbatched.csv' with linespoints pointtype 7, \
'../data/MC_20000_7_unbatched.csv' with linespoints pointtype 8