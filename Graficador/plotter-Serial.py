import numpy as np
import matplotlib
import matplotlib.pyplot as plotter
from matplotlib.animation import FuncAnimation

#calculo ALEATORIO
import random

#variables globales
fig ,grafico = plotter.subplots()
#constantes
RANGOX=4000
RANGOY=4000
R=2.0
L=13
#contenedor posicion y angulo
global X,Y,O,TK,Tk
X=Y=O=TK=Tk=0
#contenedores de datos a graficar
datosX, datosY = [], []
#graficador coordenadas
grf, =plotter.plot([],[],color='blue',marker='.',linewidth=0, animated=True)


#Configuracion Grafico
def init():
    #RANGO DE COORDENADAS
    grafico.set_xlim(-RANGOX, RANGOX)
    grafico.set_ylim(-RANGOY, RANGOY)
    grafico.set_title("Posicion Fast-L")
    grafico.set_xlabel("Coordenadas X")
    grafico.set_ylabel("Coordenadas Y")
    return grf,

#MANUAL
def update(frame):
    global TK,Tk
    datos=raw_input("Ingrese datos (T,Wl,Wr):\n")
    if "," in datos:
        coma=datos.index(",")
        TK=int(datos[:coma])
        datos=datos[coma+1:]
        coma=datos.index(",")
        Wl=float(datos[:coma])
        Wr=float(datos[coma+1:])
        calcular_angulo(Wr, Wl)
        calcular_coordenadas(Wr, Wl)
        datosX.append(X)
        datosY.append(Y)
        grf.set_data(datosX, datosY)
        Tk=TK
        return grf,

"""
#ALEATORIO
def update(frame):
    Wr=random.randint(0, 256)
    Wl=random.randint(0, 256)
    calcular_angulo(Wr, Wl)
    calcular_coordenadas(Wr, Wl)
    datosX.append(X)
    datosY.append(Y)
    grf.set_data(datosX, datosY)
    return grf,
"""

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
    ani = FuncAnimation(fig, update,init_func=init, blit=True)
    plotter.show()
    return


if __name__ == "__main__":
    main()
    raw_input()
