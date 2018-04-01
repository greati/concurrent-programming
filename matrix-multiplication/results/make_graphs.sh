#!/bin/bash
python plot_means.py -f notebook -t NB
python plot_means.py -f sc_4cores -t SC1
python plot_means.py -f sc_8cores -t SC2
python plot_means.py -f sc_16cores -t SC3
python plot_means.py -f sc_32cores -t SC4
python plot_means_tile.py
python plot_all_speedups.py