#### GNUplot directions to replicate scatter plots:

> Reset session

**Navigate to sample input directory (use forward slashes).**

> cd "C:/Users/Farnam/Desktop/example_data"

**Set Margins for multiplot:**

>if (!exists("MP_LEFT"))   MP_LEFT = .1
>if (!exists("MP_RIGHT"))  MP_RIGHT = .95
>if (!exists("MP_BOTTOM")) MP_BOTTOM = .1
>if (!exists("MP_TOP"))    MP_TOP = .9
>if (!exists("MP_GAP"))    MP_GAP = .05

**Using multiplot to show 4 plots:**

> set multiplot layout 2,2 columnsfirst title "{/:Bold=15 Sample Datasets (input0.txt - input3.txt)}" \
>               margins screen MP_LEFT, MP_RIGHT, MP_BOTTOM, MP_TOP spacing screen MP_GAP

**Then:**

> set datafile separator comma
> row = 0
> set yrange [0:380]
> set xrange [0:50]
>
> set ylabel "theta" offset 2,0
> set xlabel "Sample" offset 0,2
>
> set key off

**Set titles and plot:**

>
> set title "input0.txt" offset 0,-2
> plot 'input0.txt' matrix using 1:0 every :::row::row with points pt 7

>
> set title "input1.txt" offset 0,-2
> plot 'input1.txt' matrix using 1:0 every :::row::row with points pt 7

>
> set title "input2.txt" offset 0,-2
> plot 'input2.txt' matrix using 1:0 every :::row::row with points pt 7

>
> set title "input3.txt" offset 0,-2
> plot 'input3.txt' matrix using 1:0 every :::row::row with points pt 7
