import numpy as np
import matplotlib
import matplotlib.pyplot as plotter
from matplotlib.animation import FuncAnimation

#variables globales
fig ,grafico = plotter.subplots()
RANGOX=100
RANGOY=100
#contenedores de datos a graficar
datosX, datosY = [], []
#graficador coordenadas
grf, =plotter.plot([],[],color='blue',marker='.',linewidth=0, animated=True)

##

def init():
    #RANGO DE COORDENADAS
    grafico.set_xlim(0, RANGOX)
    grafico.set_ylim(0, RANGOY)
    grafico.set_title("Posicion Fast-L")
    grafico.set_xlabel("Coordenadas X")
    grafico.set_ylabel("Coordenadas Y")
    return grf,

def update(frame):
    coordenadas=raw_input("Ingrese coordenadas:\n")
    if "," in coordenadas and coordenadas!='0':
        coma=coordenadas.index(",")
        datosX.append(int(coordenadas[:coma]))
        datosY.append(int(coordenadas[coma+1:]))
        grf.set_data(datosX, datosY)
        return grf,





def main():
    ani = FuncAnimation(fig, update,init_func=init, blit=True)
    plotter.show()
    return


if __name__ == "__main__":
    main()
    raw_input()
