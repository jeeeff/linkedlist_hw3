reset

set ylabel 'time(nsec)'
set xlabel 'number'
set xtics 0,100
set style fill solid
set title 'Linked list sorting performance'
set term png enhanced font 'Verdana,10'
set output 'performance.png'
set key left top
set format y

plot [:][:]'time.txt' \
	using 2:xtic(10) with linespoints linewidth 2 title 'Insertion sorting', \
''  using 3:xtic(10) with linespoints linewidth 2 title 'Merge sort', \
#''  using 4:xtic(10) with linespoints linewidth 2 title 'fib 3'\
