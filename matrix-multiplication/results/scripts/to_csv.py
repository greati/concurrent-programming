import argparse
import numpy as np
import pandas as pd

parser = argparse.ArgumentParser()
parser.add_argument('--filename', '-f', type=str)
args = parser.parse_args()
filename = args.filename

df = pd.read_csv("../"+filename+".txt", sep='\s+')

df['CV'] = np.array(df['std'])/np.array(df['avg'])

sequential = df[df['method']=='S']
concurrent = df[df['method']=='C']
df['Speedup'] = np.full(df['n'].shape, np.nan)
speedups = np.array(sequential['avg'])/np.array(concurrent['avg'])
df.loc[df['method']=='S', 'Speedup'] = speedups

df.columns = ['N','Método','Média','Máximo','Mínimo','DP','CV','Speedup']
df.to_csv("../csv/"+filename+".csv", index=False, float_format='%.6f')