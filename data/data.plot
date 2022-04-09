set terminal postscript color
set output "output.ps"
set title "Project 4 Timing information"
set xlabel ""
set ylabel "Time"

plot [:][:] "data/timings.dat" with line
