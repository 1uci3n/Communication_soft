set logscale y
set key bottom
set key left
plot "result.dat" using 1:2 w l title "Hard Decode BitError",\
"result.dat" using 1:3 w l title "Hard Decode WordError",\
"result.dat" using 1:4 w l title "Maximum Likelihood Decode BitError",\
"result.dat" using 1:5 w l title "Maximum Likeihood Decode WordError"