#Examen rápido 1
#Ricardo Holguin Esquer
#Inteligencia artificial
#22/Enero/2018

from copy import deepcopy
import copy


###1
##1.1
#1.1.1: Responde lo que crees que debería de salir con print(lista_1) y print(lista_2)
#R- print(lista_1) --> ['XXX', 2, 3, 'toto', [1000, 'b', 'c']]
#R- print(lista_2) --> ['XXX', 2, 3, 'toto', [1000, 'b','c']]
#
#1.1.2: Una vez que contestaste, ejectua las operaciones y explica el porqué de los resultados
#En la linea de codigo que dice:
#   lista_2 = lista_1
#R- Lo que hace es copiar una lista_1 a lista_2, y los objetos listas son mutables, asi que
#cuando se cambien datos de la lista desde lista_2 tambien se cambian en lista_1 y viceversa,
#es algo así como que comparten dirección de memoria.
#En la linea de codigo que dice:
#   lista_3 = lista_1[:]
#R- Lo que hace es iterar entre todos los elementos que tiene lista_1 y copiarlos a la
#lista_3. Entonces si cambiamos algún elemento de lista_3 no cambiaran en lista_1 o
#lista_2, a excepción del ultimo elemento de las listas el cual es una lista (["a","b","c"])
#y este dato aun sigue siendo mutable, el cual quiere decir que si la cambiamos en cualquier
#variable se cambiaran en todas las demas.
#
##1.2
#1.2.1 Escribe que crees que debería salir con
#   print("a = " + str(a))
#
#a =
#       Coordenada x = 100
#       Coordenada y = 4
#
#1.2.2: Una vez que lo contestaste, revisa el resultado y explícalo brevemente.
#Las clases definidas por usuario son mutables.

###2
##2.1: Escribe, en una sola linea, una expresión que genere todos los números enteros
#que se ncuentran entre 1 y 1000 que sean divisibles por 2, 3, 5 y 7 al mismo tiempo.
[x for x in range(1,1001) if x%2 == 0 if x%3==0 if x%5==0 if x%7==0]
##2.2: Escribe una función que reciba una lista de elementos (letras, numeros, lo que sea),
#cuente la ocurrencia de cada elemento en la lista y la devuelva en forma de diccionario
#e imprima un histograma de ocurrencias
def histograma(L, Imprime = False):
    hist = {}
    aux = set()
    for x in L:
        if not x in aux:
            hist[x] = L.count(x)
            aux.add(x)
    if Imprime:
        total = len(L)
        for x,y in hist.items():
            print("{}\t\t{}\t\t({:d}->{:.2f}%)".format(str(x),
                    'x'*y,
                    y,
                    100*y/total))
    return hist

d = histograma( [1,'a',1, 13, 'hola', 'a', 1, 1, 'a', 1], Imprime = True)
#
##2.3: Escribe una función que modifique un diccionario y regrese el diccionario
#modificado y una copia del original, donde cada entrada del diccionario sea una
#lista de valores
def modDicc(dic, llave, indice, cadena):
    dictCopia = copy.deepcopy(dic)
    dictCopia[llave][indice] = cadena
    return dictCopia

dic1 = {"Pepe":[12, 'enero', 1980], 'Carolina':[15,'mayo',1975],'Paco':[10,'nov',1970]}
dic2 = modDicc(dic1, 'Pepe', 1, 'febrero')
print(dic1)
print(dic2)

###3
##3.1: Escribe una función fun1 que reciba un número n y calcule el número primo
#inmediatamente superior. Escribe una función fun2 que reciba como argumento un
#numero y una función, y devuelva una lista con la evaluación de la función desde
#1 hasta n.
def fun1(n):
    aux = n+1
    seguirBuscando = True
    while seguirBuscando:
        for i in range(2,aux):
            if aux%i == 0:
                aux+=1
                break
        else:
            seguirBuscando = False
    return aux

def fun2(n, fun):
    return [fun(x) for x in range(n)]

print(fun1(13))
print(fun2(2, fun1))
##3.2: Escribe una función, lo más compacta posible, que escoja entre los 3 patrones
#ascii a continuación, e imprima en pantalla el deseado, pero de la dimensión n deseada
#(n ≥ 4, toma encuanta que para algunos valores de n habrá algún(os) patrones que
#no se puedan hacer).

def fig1(n):
    if n < 4:
        n = 4
    for i in range(n):
        for j in range(i+1):
            print("*",end='')
        print('')

def fig2(n):
    if n < 4:
        n = 4
    for i in range(n):
        for j in range(n):
            print("+",end='')
        print()
    for i in range(n):
        for k in range(n):
            print(" ",end='')
        for k in range(n):
            print("+",end='')
        print("")

def fig3(n):
    if n < 4:
        n = 4
    for j in range(n):
        for k in range(n-j):
            print("o", end='')
        for k in range(2*j):
            print(" ", end='')
        for k in range(n-j):
            print("o", end='')
        print("")
    for j in range(n, 0, -1):
        for k in range(n-j+1):
            print("o", end='')
        for k in range(2*(j-1)):
            print(" ", end='')
        for k in range(n-j+1):
            print("o", end='')
        print("")

def patrones(fig, n):
    if fig==1:
        fig1(n)
    elif fig==2:
        fig2(n)
    elif fig==3:
        fig3(n)

patrones(1,4)
patrones(2,4)
patrones(3,4)

##3.3:Diseña una clase Matriz e implementa con sobrecarga la suma de matrices, la
#multiplicación de matrices y la multiplicación por un escalar, eliminar columna
#y eliminar fila. Como inicialización de un objeto es necesario conocer n y m (en
#caso de no proporcionarlos la matriz tendrá una dimensión de 1 × 1. Igualmente,
#de no especificarse todos los elementos se inicializan a 0, a menos que exista
#un tipo espacial ( ’unos’ o ’diag’ por el momento).
class Matriz:
    def __init__(self, n = 1, m = 1, tipo = "ceros", M = None):
        self.n = n;
        self.m = m;
        if M is None:
            if tipo == "ceros":
                self.M = [[0 for x in range(self.m)] for y in range(self.n)]
            elif tipo == "unos":
                self.M = [[1 for x in range(self.m)] for y in range(self.n)]
            elif tipo == "diag":
                self.M = [[0 for x in range(self.m)] for y in range(self.n)]
                for i in range(min(self.n, self.m)):
                    self.M[i][i] = 1
        else:
            self.M = deepcopy(M)

    def __str__(self):
        cadena = ''
        for i in range(self.n):
            for j in range(self.m):
                cadena += str(self.M[i][j]) + " "
            cadena += '\n'
        return cadena

    def __add__(self, other):
        if self.n != other.n or self.m != other.m:
            raise ErrorDimension("Si no son de la misma dimensión las matrices no se pueden sumar")
        else:
            return Matriz(self.n, self.m, M=[[x+y for x,y in zip(m1,m2)] for m1,m2 in zip(self.M, other.M)])

    def __mul__(self, other):
        #matriz x matriz
        if isinstance(other, Matriz):
            if self.m != other.n:
                raise ErrorMultMat("Si el no. de columnas de la primera matriz no son el mismo número de renglones que la segunda matriz no se pueden multiplicar")
            aux = list(zip(*other.M))
            return Matriz(self.n, other.m, M=[[sum(x*y for x,y in zip(renA, colB)) for colB in aux] for renA in self.M])
        #escalar
        else:
            return Matriz(self.n, self.m, M=[[other*self.M[i][j] for j in range(self.m)] for i in range(self.n)])

    def __rmul__(self, other):
        return self*other

    def quitarFila(self, noFila=0):
        self.M = [self.M[i] for i in range(self.n) if not i == noFila]
        self.n-= 1

    def quitarColumna(self, noCol=0):
        self.M = [[self.M[i][j] for j in range(self.m) if not j==noCol] for i in range(self.n)]
        self.m-=1

class ErrorDimension(Exception):
    pass

class ErrorMultMat(Exception):
    pass


A = Matriz(n=3, m=4)
print(A)

A.quitarFila(2)
print(A)

B = Matriz(4,4,'diag')
print(B)

C = Matriz(4,1,'unos')
print(C)

D = 3*B*C
print(D)

E = 3*B + C
print(E)
