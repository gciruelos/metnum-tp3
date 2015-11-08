import numpy as np
from pylab import *
from math import *

dic_met = {'0': 'Nearest Neighbour',
           '1': 'Interpolacion Lineal',
           '2': 'Splines Cubicos (4)',
           '3': 'Splines Cubicos (8)',
           '4': 'Splines Cubicos (12)'}

dic_ecmlim ={'darthvader': 700.0,
           'ff6': 4000.0,
           'motocross': 3000.0,
           'penal': 1100.0}

dic_psnrlim ={'darthvader': 50.0,
           'ff6': 30.0,
           'motocross': 25.0,
           'penal': 50.0}


dic_centro ={'darthvader': 0.2,
           'ff6': 0.3,
           'motocross':0.2,
           'penal': 0.26}





def generar_grafiquito(ecms, psnrs, video, metodo):
    fig,ax = subplots(1,2) #figure(figsize=[7,4])
    #ax[0] = fig.add_subplot(1,1,1)
    #ax2 = fig.add_subplot(2,2,1)
    ecm_lim = dic_ecmlim[video]
    psnr_lim = dic_psnrlim[video]

    ax[0].boxplot(ecms, 0, '', labels=[1,2,4,8], widths=0.75)
    ax[0].set_ylim([0, ecm_lim])
    ax[0].set_title('ECM')

    ax[1].boxplot(psnrs, 0, '', labels=[1,2,4,8], widths=0.75)
    ax[1].set_ylim([10, psnr_lim])
    ax[1].set_title('PSNR')

    fig.text(0.3, 0.02,'Cantidad de cuadros interpolados', size='small')
    fig.text(dic_centro[video], 0.96, video+' - '+dic_met[metodo], size='large')
    fig.set_size_inches(5.5, 4)
    fig.tight_layout = True

    fig.savefig('resultados_error/'+video+'_'+metodo+'.png', bbox_inches='tight')


def convertir_lista(s):
    return [float(k) for k in s[1:-1].split(',')]


cuadros = 4

videos = ['darthvader', 'ff6','motocross','penal']


for vid in videos:
    for metodo in ['0','1','2','3','4']:
        f = open(vid+'/'+vid+'.'+metodo+'.diff.txt', 'r')
        ecms = []
        psnrs = []


        for _ in range(cuadros):
            f.readline()
            ecm = convertir_lista(f.readline()[24:-1])
            f.readline()
            psnr = convertir_lista(f.readline()[28:-1])
            f.readline()
            f.readline()
            f.readline()
            f.readline()
            ecms.append(ecm)
            psnrs.append(psnr)

        generar_grafiquito(ecms, psnrs, vid, metodo)


