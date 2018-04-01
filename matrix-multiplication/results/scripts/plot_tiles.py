import argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument('--stat', '-s', type=str)
args = parser.parse_args()
stat = args.stat

file_label = {'sc_4cores':'SC1', 'sc_8cores':'SC2', 
	'sc_16cores':'SC3', 'sc_32cores':'SC4'}

fig, axes = plt.subplots(2, 2)
file_plt = {'sc_4cores':axes[0, 0], 'sc_8cores':axes[0, 1], 
	'sc_16cores':axes[1, 0], 'sc_32cores':axes[1, 1]}

for file, label in file_label.items():
	df = pd.read_csv("../"+file+".txt", sep='\s+')

	sequential = df[df.method=='S']
	concurrent = df[df.method=='C']

	x = np.log2(sequential['n'])
	subplot = file_plt[file]
	if stat=='cv':
		y_s = np.array(sequential['std'])/np.array(sequential['avg'])
		y_c = np.array(concurrent['std'])/np.array(concurrent['avg'])
	elif stat=='mean':
		y_s = sequential['avg']
		y_c = concurrent['avg']
		subplot.set_ylim(-10, 410)
		subplot.set_yticks([i*100 for i in range(0,5)])
	else:
		y_s = 1
		y_c = 1

	subplot.plot(x, y_s, label='Sequencial', color="#d73027")
	subplot.plot(x, y_c, label='Concorrente', color="#4575b4")
	subplot.set_xlim(1, x.max()+1)
	subplot.set_xticks(x)
	subplot.set_title(label, fontsize=13)

axes[0, 0].legend(loc=2)
fig.subplots_adjust(hspace=0.35, bottom=0.15, left=0.15)
if stat=='mean':
	title = 'Tempos médios de produto matricial - SC'
	xlabel = 'Dimensão de matrizes ($2^x$x$2^x$ elementos)'
	ylabel = 'Tempo médio de produto ($ms$)'
	filename = 'tiled_means'
elif stat=='cv':
	title = 'Coeficiente de variação dos tempos de produto matricial - SC'
	xlabel = 'Dimensão de matrizes ($2^x$x$2^x$ elementos)'
	ylabel = 'Coeficiente de Variação'
	filename = 'tiled_cv'

fig.suptitle(title, fontsize=13)
fig.text(0.5, 0.04, xlabel, ha='center', fontsize=12)
fig.text(0.04, 0.5, ylabel, va='center', rotation='vertical', fontsize=12)
fig.savefig("../graphs/"+filename+".png", dpi=500)