import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

file_label = {'sc_4cores':'SC1', 'sc_8cores':'SC2', 
	'sc_16cores':'SC3', 'sc_32cores':'SC4'}

fig, axes = plt.subplots(2, 2)
file_plt = {'sc_4cores':axes[0, 0], 'sc_8cores':axes[0, 1], 
	'sc_16cores':axes[1, 0], 'sc_32cores':axes[1, 1]}

for file, label in file_label.items():
	df = pd.read_csv(file+".txt", sep='\s+')

	sequential = df[df.method=='S']
	concurrent = df[df.method=='C']

	x = np.log2(sequential['n'])
	subplot = file_plt[file]
	subplot.plot(x, sequential['avg'], label='Sequencial', color="#d73027")
	subplot.plot(x, concurrent['avg'], label='Concorrente', color="#4575b4")
	subplot.set_xlim(1, x.max()+1)
	subplot.set_ylim(-10, 410)
	subplot.set_xticks(x)
	subplot.set_yticks([i*100 for i in range(0,5)])
	subplot.set_title(label, fontsize=13)

axes[0, 0].legend()
fig.subplots_adjust(hspace=0.35, bottom=0.15, left=0.15)
fig.suptitle('Tempos médios de produto matricial - SC', fontsize=13)
fig.text(0.5, 0.04, 'Dimensão de matrizes ($2^i$x$2^i$ elementos)', ha='center', fontsize=12)
fig.text(0.04, 0.5, 'Tempo médio de produto ($ms$)', va='center', rotation='vertical', fontsize=12)
fig.savefig("graphs/tiled_means.png")