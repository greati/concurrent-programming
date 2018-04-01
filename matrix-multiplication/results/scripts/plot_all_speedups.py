import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

file_label = {'notebook':'NB', 'sc_4cores':'SC1',
	'sc_8cores':'SC2', 'sc_16cores':'SC3', 'sc_32cores':'SC4'}

file_color = {'notebook':'#c2a5cf', 'sc_4cores':'#c2e699',
	'sc_8cores':'#78c679', 'sc_16cores':'#31a354', 'sc_32cores':'#006837'}

for file, label in file_label.items():
	df = pd.read_csv("../"+file+".txt", sep='\s+')

	sequential = df[df.method=='S']
	concurrent = df[df.method=='C']

	x = np.log2(sequential['n'])
	y = np.array(sequential['avg'])/np.array(concurrent['avg'])
	plt.plot(x, y, color=file_color[file], label=label)

plt.title('$Speedup$ por configuração', fontsize=13)
plt.xlabel('Dimensão de matrizes ($2^x$x$2^x$ elementos)', fontsize=12)
plt.ylabel('$Speedup$ ($\\alpha_x$)', fontsize=12)
plt.legend()

plt.xlim(1, x.max()+1)
plt.xticks(x)
plt.savefig("../graphs/comparative_speedup.png", dpi=500)