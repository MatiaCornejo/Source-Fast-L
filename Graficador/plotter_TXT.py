import numpy as np
import matplotlib
import matplotlib.pyplot as plotter

#variables globales

#constantes
RANGOX=10000
RANGOY=1000
R=2.0
L=13
#contenedor posicion y angulo
global X,Y,O,TK,Tk
X=Y=O=TK=Tk=0







def calcular_angulo(Wr, Wl):
    #definir deltaT
    global O,TK,Tk
    O += (R/L)*(Wr - Wl)*(TK-Tk)
    return


def calcular_coordenadas(Wr, Wl):
    #definir deltaT
    global X,Y
    X +=(R*0.5)*np.cos(O)*(Wr + Wl)*(TK-Tk)
    Y +=(R*0.5)*np.sin(O)*(Wr + Wl)*(TK-Tk)
    return

def main():
    global TK, Tk, X, Y
    fig ,grafico = plotter.subplots()
    grafico.set_title("Posicion Fast-L")
    grafico.set_xlabel("Coordenadas X")
    grafico.set_ylabel("Coordenadas Y")
    #graficador coordenadas
    nombre_TXT=raw_input("Ingrese ruta Txt:\n")
    listaDatos=leerTxt(nombre_TXT)
    for datos in listaDatos:
        TK,Wl,Wr=datos
        calcular_angulo(Wr,Wl)
        calcular_coordenadas(Wr,Wl)
        Tk=Tk
        grafico.plot(X,Y,color='blue',marker='.',linewidth=0)
    plotter.show()
    return

def leerTxt(nombre_TXT):
    t=wl=wr=0
    listadatos=[]
    archivo=open(nombre_TXT,'r')
    for linea in archivo:
        coma=linea.index(",")
        t=float(linea[:coma])/1000
        linea=linea[coma+1:]
        coma=linea.index(",")
        wl=float(linea[:coma])
        wr=float(linea[coma+1:])
        listadatos.append((t,wl,wr))
    archivo.close()
    return listadatos

if __name__ == "__main__":
    main()
    raw_input()
