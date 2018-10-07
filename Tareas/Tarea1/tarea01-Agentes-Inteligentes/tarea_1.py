#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
tarea_1.py
------------

Tarea de desarrollo de entornos y agentes
==========================================

1. Desarrolla un entorno similar al de los dos cuartos (el cual se
   encuentra en el módulo doscuartos_o.py), pero con tres cuartos en
   el primer piso, y tres cuartos en el segundo piso.

   El entorno se llamará `SeisCuartos`.

   Las acciones totales serán

   ```
   ["ir_Derecha", "ir_Izquierda", "subir", "bajar", "limpiar", "nada"]
   ```

   La acción de `"subir"` solo es legal en el piso de abajo, en los cuartos de los extremos,
   mientras que la acción de `"bajar"` solo es legal en el piso de arriba y en el cuarto de el centro (dos
   escaleras para subir, una escalera para bajar).

   Las acciones de subir y bajar son mas costosas en término de
   energía que ir a la derecha y a la izquierda, por lo que la función
   de desempeño debe de ser de tener limpios todos los cuartos, con el
   menor numero de acciones posibles, y minimizando subir y bajar en
   relación a ir a los lados. El costo de limpiar es menor a los costos
   de cualquier acción.

2. Diseña un Agente reactivo basado en modelo para este entorno y
   compara su desempeño con un agente aleatorio despues de 100 pasos
   de simulación.

3. Al ejemplo original de los dos cuartos, modificalo de manera que el
   agente solo pueda saber en que cuarto se encuentra pero no sabe si
   está limpio o sucio.

   A este nuevo entorno llamalo `DosCuartosCiego`.

   Diseña un agente racional para este problema, pruebalo y comparalo
   con el agente aleatorio.

4. Reconsidera el problema original de los dos cuartos, pero ahora
   modificalo para que cuando el agente decida aspirar, el 80% de las
   veces limpie pero el 20% (aleatorio) deje sucio el cuarto. Igualmente,
   cuando el agente decida cambiar de cuarto, se cambie correctamente de cuarto el 90% de la veces
   y el 10% se queda en su lugar. Diseña
   un agente racional para este problema, pruebalo y comparalo con el
   agente aleatorio.

   A este entorno llámalo `DosCuartosEstocástico`.

Todos los incisos tienen un valor de 25 puntos sobre la calificación de
la tarea.

"""
__author__ = 'ricardoholguin'

import entornos_o
import doscuartos_o
from doscuartos_o import AgenteAleatorio
from random import choice
from random import random
from doscuartos_o import AgenteReactivoModeloDosCuartos

###1
class SeisCuartos(entornos_o.Entorno):
    """
    Los nombres de las habitaciones son de la A a la F, donde A-C son las habitaciones
    del primer piso y D-F son las habitaciones del segundo piso. Ejemplo: A, B, C, D,
    E, F. Siendo A y C las habitaciones que tienen escaleras para subir, y E la
    habitacion que tiene escaleras para bajar

    Por default inicialmente el robot esta en A y todos los cuartos estan sucios
    """
    def __init__(self, x0=["A","sucio","sucio","sucio","sucio","sucio","sucio"]):
        self.x = x0[:]
        self.desempeño = 0

    def acción_legal(self, acción):
        if self.x[0] == "A":
            esLegal = acción in ("subir", "ir_Derecha", "limpiar", "nada")
        elif self.x[0] == "B":
            esLegal = acción in ("ir_Derecha", "ir_Izquierda", "limpiar", "nada")
        elif self.x[0] == "C":
            esLegal = acción in ("ir_Izquierda", "subir", "limpiar", "nada")
        elif self.x[0] == "D":
            esLegal = acción in ("ir_Derecha", "limpiar", "nada")
        elif self.x[0] == "E":
            esLegal = acción in ("bajar", "ir_Derecha", "ir_Izquierda", "limpiar", "nada")
        else:   #Supones que el robot esta en F
            esLegal = acción in ("ir_Izquierda", "limpiar", "nada")

        return esLegal

    def transición(self, acción):
        if not self.acción_legal(acción):
            raise ValueError("La acción no es legal para este estado")

        robot, a, b, c, d, e, f = self.x
        if acción is not "nada" or a=="sucio" or b=="sucio" or c=="sucio" or d=="sucio" or e=="sucio" or f=="sucio":
            self.desempeño -= 1
        if acción is "limpiar":
            self.x[" ABCDEF".find(self.x[0])] = "limpio"
        elif acción is "ir_Derecha":
            if self.x[0] == "A":
                self.x[0] = "B"
            elif self.x[0] == "B":
                self.x[0] = "C"
            elif self.x[0] == "D":
                self.x[0] = "E"
            elif self.x[0] == "E":
                self.x[0] = "F"
        elif acción is "ir_Izquierda":
            if self.x[0] == "B":
                self.x[0] = "A"
            elif self.x[0] == "C":
                self.x[0] = "B"
            elif self.x[0] == "E":
                self.x[0] = "D"
            elif self.x[0] == "F":
                self.x[0] = "E"
        elif acción is "subir":
            if self.x[0] == "A":
                self.x[0] = "D"
                self.desempeño -= 2
            elif self.x[0] == "C":
                self.x[0] = "F"
                self.desempeño -= 2
        elif acción is "bajar":
            if self.x[0] == "E":
                self.x[0] = "B"
                self.desempeño -= 2

    def percepción(self):
        return self.x[0], self.x[" ABCDEF".find(self.x[0])]

###2
class AgenteAleatorioSeisCuartos(entornos_o.Agente):
    """
    Un agente que solo regresa una accion al azar entre las acciones legales

    """
    def __init__(self, acciones):
        self.acciones = acciones

    def programa(self, percepcion):
        if percepcion[0] == "A":
            decisión = choice(["subir", "ir_Derecha", "limpiar", "nada"])
        elif percepcion[0] == "B":
            decisión = choice(["ir_Derecha", "ir_Izquierda", "limpiar", "nada"])
        elif percepcion[0] == "C":
            decisión = choice(["ir_Izquierda", "subir", "limpiar", "nada"])
        elif percepcion[0] == "D":
            decisión = choice(["ir_Derecha", "limpiar", "nada"])
        elif percepcion[0] == "E":
            decisión = choice(["bajar", "ir_Derecha", "ir_Izquierda", "limpiar", "nada"])
        else:   #Supones que el robot esta en F
            decisión = choice(["ir_Izquierda", "limpiar", "nada"])
        return decisión

class AgenteReactivoModeloSeisCuartos(entornos_o.Agente):
    """
    Un agente reactivo basado en modelo

    """
    def __init__(self):
        """
        Inicializa el modelo interno en el peor de los casos

        """
        self.modelo = ['A', 'sucio', 'sucio', 'sucio', 'sucio', 'sucio', 'sucio']

    def programa(self, percepción):
        robot, situación = percepción

        # Actualiza el modelo interno
        self.modelo[0] = robot
        self.modelo[' ABCDEF'.find(robot)] = situación

        # Decide sobre el modelo interno
        a, b = self.modelo[1], self.modelo[2]
        c, d, e, f = self.modelo[3], self.modelo[4], self.modelo[5], self.modelo[6]

        if a==b==c==d==e==f == 'limpio':
            acción = 'nada'
        elif situación == 'sucio':
            acción = 'limpiar'
        elif robot == 'A' or robot == 'B' or robot == 'C':
            if robot == 'A':
                if b == 'sucio' or c == 'sucio':
                    acción = 'ir_Derecha'
                else:
                    acción = 'subir'
            elif robot == 'B':
                if c == 'sucio':
                    acción = 'ir_Derecha'
                else:
                    acción = 'ir_Izquierda' #Si A esta sucio o no el robot se movera
                                            #y asi pueda subir las escaleras.
            else:   #Esta robot en C
                if a == 'sucio' or b == 'sucio':
                    acción = 'ir_Izquierda'
                else:
                    acción = 'subir'
        else:   #Esta robot en D, E o F
            if robot == 'D':
                acción = 'ir_Derecha'
            elif robot == 'E':
                if d == 'sucio':
                    acción = 'ir_Izquierda'
                elif f == 'sucio':
                    acción = 'ir_Derecha'
                else:
                    acción = 'bajar'
            else:   #robot esta en F
                if d == 'sucio' or e == 'sucio':
                    acción = 'ir_Izquierda'

        return acción

###3
class DosCuartosCiego(doscuartos_o.DosCuartos):
    def __init__(self, x0="A"):
        """
        Por default inicialmente el robot está en A y los dos cuartos
        están sucios

        """
        self.x = x0
        self.desempeño = 0

    def transición(self, acción):
        if not self.acción_legal(acción):
            raise ValueError("La acción no es legal para este estado")

        robot = self.x
        if acción is not "nada":
            self.desempeño -= 1
        if acción is "limpiar":
            self.desempeño -= 1
        elif acción is "ir_A":
            self.x = "A"
        elif acción is "ir_B":
            self.x = "B"

    def percepción(self):
        return self.x

class AgenteReactivoModeloDosCuartosCiego(doscuartos_o.AgenteReactivoModeloDosCuartos):
    """
    Un agente reactivo basado en modelo

    """
    def __init__(self):
        """
        Inicializa el modelo interno en el peor de los casos

        """
        self.modelo = ['A', 'sucio', 'sucio']

    def programa(self, percepción):
        robot = percepción
        situación = self.modelo[" AB".find(robot)]

        # Actualiza el modelo interno
        self.modelo[0] = robot

        # Decide sobre el modelo interno
        a, b = self.modelo[1], self.modelo[2]
        if a==b=='limpio':
            acción = 'nada'
        elif situación == 'sucio':
            acción = 'limpiar'
            self.modelo[" AB".find(robot)] = 'limpio'
        elif robot == 'B':
            acción = 'ir_A'
            self.modelo[0] = 'A'
        else:   #robot esta en A
            acción = 'ir_B'
            self.modelo[0] = 'B'

        return acción

###4
class DosCuartosEstocástico(doscuartos_o.DosCuartos):
    def transición(self, acción):
        if not self.acción_legal(acción):
            raise ValueError("La acción no es legal para este estado")

        robot, a, b = self.x
        if acción is not "nada" or a is "sucio" or b is "sucio":
            self.desempeño -= 1
        if acción is "limpiar":
            if random() <= 0.8:
                self.x[" AB".find(self.x[0])] = "limpio"
        elif acción is "ir_A":
            if random() <= 0.9:
                self.x[0] = "A"
        elif acción is "ir_B":
            if random() <= 0.9:
                self.x[0] = "B"

# Requiere el modulo entornos_o.py
# Usa el modulo doscuartos_o.py para reutilizar código
# Agrega los modulos que requieras de python

###pruebas para usar en terminal
cuarto = SeisCuartos()
cuartoDos = DosCuartosCiego()
agenteAlSeis = AgenteAleatorioSeisCuartos(["ir_Derecha", "ir_Izquierda", "subir", "bajar", "limpiar", "nada"])
agenteModSeis = AgenteReactivoModeloSeisCuartos()
agenteAlDos = AgenteAleatorio(['ir_A', 'ir_B', 'limpiar', 'nada'])
agenteModDos = AgenteReactivoModeloDosCuartosCiego()
#Función de prueba para probar todas los entornos con todos los agentes
def test():
    """
    Prueba del entorno y los agentes

    """
    #Prueba del inciso 1 y 2
    print("Prueba del entorno con un agente aleatorio con seis cuartos")
    SeisCuartosAcciones = ["ir_Derecha", "ir_Izquierda", "subir", "bajar", "limpiar", "nada"]
    entornos_o.simulador(SeisCuartos(),
                         AgenteAleatorioSeisCuartos(SeisCuartosAcciones),
                         100)

    print("Prueba del entorno con un agente reactivo con modelo con seis cuartos")
    entornos_o.simulador(SeisCuartos(), AgenteReactivoModeloSeisCuartos(), 100)

    #Prueba del inciso 3
    print("Prueba del entorno con un agente aleatorio con dos cuartos")
    entornos_o.simulador(DosCuartosCiego(),
                         AgenteAleatorio(["ir_A", "ir_B", "limpiar", "nada"]),
                         100)

    print("Prueba del entorno con un agente reactivo con modelo con dos cuartos ciego")
    entornos_o.simulador(DosCuartosCiego(), AgenteReactivoModeloDosCuartosCiego(), 100)

    #Prueba del inciso 4
    print("Prueba del entorno con un agente aleatorio con dos cuartos estocástico")
    entornos_o.simulador(DosCuartosEstocástico(),
                         AgenteAleatorio(['ir_A', 'ir_B', 'limpiar', 'nada']),
                         100)

    print("Prueba del entorno con un agente reactivo con modelo con dos cuartos estocástico")
    entornos_o.simulador(DosCuartosEstocástico(), AgenteReactivoModeloDosCuartos(), 100)
