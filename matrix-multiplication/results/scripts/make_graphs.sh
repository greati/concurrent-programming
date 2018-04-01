#!/bin/bash
python plot_means.py -f notebook -t NB
# python plot_means.py -f sc_4cores -t SC1
# python plot_means.py -f sc_8cores -t SC2
# python plot_means.py -f sc_16cores -t SC3
# python plot_means.py -f sc_32cores -t SC4
echo 'Means done'

python plot_tiles.py -s mean
echo 'Means tile done'

python plot_cv.py -f notebook -t NB
# python plot_cv.py -f sc_4cores -t SC1
# python plot_cv.py -f sc_8cores -t SC2
# python plot_cv.py -f sc_16cores -t SC3
# python plot_cv.py -f sc_32cores -t SC4
echo 'Coefficients of variation done'

python plot_tiles.py -s cv
echo 'CV tile done'

python plot_all_speedups.py
echo 'Speedups done'