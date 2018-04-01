import argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument('--filename', '-f', type=str)
parser.add_argument('--title', '-t', type=str)
args = parser.parse_args()
filename = args.filename
title = args.title

df = pd.read_csv("../"+filename+".txt", sep='\s+')

sequential = df[df.method=='S']
concurrent = df[df.method=='C']

x = np.log2(sequential['n'])
y_s = np.array(sequential['std'])/np.array(sequential['avg'])
y_c = np.array(concurrent['std'])/np.array(concurrent['avg'])
plt.plot(x, y_s, label='Sequencial', color="#d73027")
plt.plot(x, y_c, label='Concorrente', color="#4575b4")

plt.title('Coeficiente de variação dos tempos de produto matricial - '+title, fontsize=13)
plt.xlabel('Dimensão de matrizes ($2^x$x$2^x$ elementos)', fontsize=12)
plt.ylabel('Coeficiente de Variação', fontsize=12)
plt.legend(loc=2)

plt.xlim(1, x.max()+1)
# plt.ylim(-10, 410)
plt.xticks(x)
# plt.yticks([i*50 for i in range(0,9)])
plt.savefig("../graphs/"+filename+"_cv.png", dpi=500)