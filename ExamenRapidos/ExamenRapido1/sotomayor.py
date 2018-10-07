#Examen rapido no 1
#
#Sotomayor Samaniego Luis Fernando

from copy import deepcopy
from math import sqrt

'''
1.1-
    print(lista_1) -> ["XXX", 2, 3, "toto", ["a", "b", "c"]]
    print(lista_2) -> [1, 2, 3, "toto", [1000, "b", "c"]]
'''

print("\n############################")
print("Problema 1.1")
print("############################\n")

lista_1 = [1, 2, 3, "toto", ["a", "b", "c"]]
lista_2 = lista_1
lista_3 = lista_1[:]

lista_2[0] = "XXX"
print(lista_2)

lista_3[-1][0] = 1000
print(lista_3)

#Que debe salir aqui
print(lista_1)
print(lista_2)

'''
Explicacion de resultados:

En ambos casos estaba equivocado. Los resultados fueron:
    print(lista_1) -> ['XXX', 2, 3, 'toto', [1000, 'b', 'c']]
    print(lista_2) -> ['XXX', 2, 3, 'toto', [1000, 'b', 'c']]

lista_2 es una copia superficial de lista_1 por lo que los cambios que sean hechos en una, se ven reflejados en la otra y por eso el cambio del primer elemento de lista_2 afecto al primer elemento de lista_1.

lista_3 es una copia casi superficial de lista_1. Crea una nueva lista y copia los elementos de lista_1 pero en el caso que un elemento sea una construccion (como una lista), solo copia la direccion y no crea un nuevo objeto. Entonces, esto hace que efectivamente la lista ["a", "b", "c"] sea compartida en las 3 listas y cualquier cambio a ella se vera reflejado en las 3. Por ello el cambio a la lista de lista_3 se ve reflejado en lista_1 y lista_2.
'''

'''
1.2-
    print("a = " + str(a)) -> x = 100, y = 4
'''
print("\n############################")
print("Problema 1.2")
print("############################\n")

class coordenadas:
    def __init__(self, x=0, y=0):
        "Inicializa un object coordenadas"
        self.x = x
        self.y = y

    def __str__(self):
        return "\n\tCoordenada x = {}\n\tCoordenada y = {}".format(self.x, self.y)

a = coordenadas(3, 4)
b = a
b.x = 100
print("b = " + str(b))

#Que debe salir aqui
print("a = " + str(a))

'''
Explicacion de resultados:

Estaba en lo correcto, el resultado fue:
    print("a = " + str(a)) -> x = 100, y = 4

Esto se debe a una razon similar al problema 1.1. b es una copia superficial de a y, ya que a es un objeto, las copias que se hagan no crean un objeto igual por lo que la etiqueta a y b comparten el mismo objeto. Entonces un cambio en b se ve reflejado en a.
'''

#############################################################################################

#2) Listas y diccionarios
'''
2.1- Una expresion que genere [1, 1000] divisibles entre [2, 3, 5, 7]
'''
print("\n############################")
print("Problema 2.1")
print("############################\n")

expres = [x for x in range(1, 10001) if all(x % y == 0 for y in [2, 3, 5, 7])]

print( "[x for x in range(1, 10001) if all(x % y == 0 for y in [2, 3, 5, 7])]\n" )
print(expres)

'''
2.2- Recibe lista, cuenta ocurrencias de elemento y regresa diccionario e histograma
'''
print("\n############################")
print("Problema 2.2")
print("############################\n")

def ocurrElem(lista, imprime = True):
    #parte diccionario
    midict = {elem:lista.count(elem) for elem in lista}

    #parte histograma
    if imprime:
        for elem in midict:
            cont = midict[elem]
            print("{}\t\t\t{}\t({} -> {:.2f})%".format(elem, '*'*cont, cont, 100*cont/len(lista)))

    return midict

print("ocurrElem( [1,'a',1, 13, 'hola', 'a', 1, 1, 'a', 1], imprime = True)\n")
d = ocurrElem( [1,'a',1, 13, 'hola', 'a', 1, 1, 'a', 1], imprime = True)

print(d)

'''
2.3- Recibe diccionario, regresa el mismo y una copia con el valor de una entrada en especifico cambiada a otro
'''
print("\n############################")
print("Problema 2.3")
print("############################\n")

def fundicos(diccio, entrada, pos, nuevoVal):
    diccio2 = deepcopy(diccio)
    diccio2[entrada][pos] = nuevoVal

    return diccio2

print( "dic1 = {'Pepe':[12, 'enero', 1980], 'Carolina':[15,'mayo',1975],'Paco':[10,'nov',1970]}\n" )
print( "fundicos(dic1, 'Pepe', 1, 'febrero')\n" )
dic1 = {'Pepe':[12, 'enero', 1980], 'Carolina':[15,'mayo',1975],'Paco':[10,'nov',1970]}
dic2 = fundicos(dic1, 'Pepe', 1, 'febrero')
print(dic1)
print(dic2)

#############################################################################################

#3) Funciones y clases
'''
3.1a- fun1 recibe n y calcula primo superior
'''
def fun1(n):
    if n < 2:
        return 2 #2 es el primer primo

    n = int(n)
    primo = False
    while not primo:
        n += 1
        if not any(n % x == 0 for x in range(2, int(sqrt(n)) + 1)):
            primo = True

    return n


'''
3.1b- fun2 recibe numero y funcion y evalua [1-numero] en la funcion
'''
def fun2(n, funct):
    return [funct(i) for i in range(1, n+1)]


print("\n############################")
print("Problema 3.1")
print("############################\n")

print("Probando las funciones de 1-15")
print( fun2(15, fun1) )
print( fun2(15, sqrt) )


'''
3.2- escribe patrones ascii (3 posibles) de dimension >= 4 dependiendo de lo introducido
     La figura 2 y 3 solo pueden tener dimension par.
'''
def patronAscii(patron, dim):
    if dim < 4:
        print("Dimension debe ser al menos 4")
        return

    if patron == 1:
        numCar = 1
        for i in range(numCar, dim+1):
            for j in range(numCar):
                print("*", end = '')

            numCar += 1
            print("")

    elif patron == 2:
        if dim % 2 != 0:
            print("La figura 2 solo puede tener dimension par")
            return

        dim = int(dim/2)
        #parte arriba-izquierda
        for i in range(dim):
            for j in range(dim):
                print("+", end = '')
            print("")

        #parte abajo-derecha
        for i in range(dim):
            for j in range(dim):
                print(" ", end = '')
            for j in range(dim):
                print("+", end = '')
            print("")

    elif patron == 3:
        if dim % 2 != 0:
            print("La figura 3 solo puede tener dimension par")
            return

        dim = int(dim/2)
        carVac = 0
        car = "*"
        #parte superior
        for i in range(dim):
            print("")
            #parte izquierda
            print(car*(dim-carVac), end = '')
            #parte medio
            print(' '*(carVac*2), end = '')
            #parte derecha
            print(car*(dim-carVac), end = '')

            carVac += 1

        #parte inferior
        for i in range(dim):
            print("")
            carVac -= 1
            #parte izquierda
            print(car*(dim-carVac), end = '')
            #parte medio
            print(' '*(carVac*2), end = '')
            #parte derecha
            print(car*(dim-carVac), end = '')

        print("")

    else:
        print("Solo hay patron 1, 2 o 3")


print("\n############################")
print("Problema 3.2")
print("############################\n")

patronAscii(1, 10)
print("")
patronAscii(2, 10)
patronAscii(3, 10)


'''
3.3- Clase matriz. Sobrecarca suma, mult mat, mult escalar, eliminar columna, eliminar fila.
     Se ocupa n y m (1x1 si no) e inicializada en 0. Manejar errores y programar lo visual
     n es numero de renglones, m es numero de columnas
'''

class Matriz:
    def __init__(self, n = 1, m = 1, especial = None, matriz = None):
        self.n = n
        self.m = m

        if matriz is None:
            if especial is not 'unos':
                self.mat = [[0 for i in range(self.m)] for j in range(self.n)]
            else:
                self.mat = [[1 for i in range(self.m)] for j in range(self.n)]

            if especial is 'diag':
                for i in range(0, min(self.n, self.m)):
                    self.mat[i][i] = 1

        else:
            self.mat = deepcopy(matriz)

    def __add__(self, other):
        if(self.n != other.n or self.m != other.m):
            raise ErrorDimension("Dimensiones diferentes de matrices")

        return Matriz(self.n, self.m, matriz = [[x+y for x,y in zip(l1, l2)] for l1, l2 in zip(self.mat, other.mat)])

    def __mul__(self, other):
        #caso matriz
        if isinstance(other, Matriz):
            if self.m != other.n:
                raise ErrorMultMat("El numero de renglones de la primer matriz no es el numero de columnas de la segunda")
            zipB = list(zip(*other.mat)) #obtiene la transpuesta de la matriz B
            return Matriz(self.n, other.m, matriz = [[sum(x*y for x, y in zip(renA, colB)) for colB in zipB] for renA in self.mat])

        #caso esclarar
        return Matriz(self.n, self.m, matriz = [[other*self.mat[i][j] for j in range(self.m)] for i in range(self.n)]) #si other no es matriz, se considera escalar

    def __rmul__(self, other):
        return self*other

    #Elimina la columna con el indice recibido. 0-indexado
    #Lanza excepcion Out
    def elimCol(self, col):
        if col < 0 or col >= self.m:
            raise ErrorRangoColumna("Se intento accesar a una columna fuera del rango de la matriz")

        for i in range(self.n):
            del self.mat[i][col]

    #Elimina el renglon con el indice recibido. 0-indexado
    def elimRen(self, ren):
        if ren < 0 or ren >= self.n:
            raise ErrorRangoRenglon("Se intento accesar a una columna fuera del rango de la matriz")

        del self.mat[ren]

    def imprimir(self):
        for lista in self.mat:
            for elem in lista:
                print("{}\t".format(elem), end = '')
            print("")

#Clases para cada excepcion diferente. Para este caso solo importa la descripcion de cada clase
class ErrorDimension(Exception):
    pass

class ErrorMultMat(Exception):
    pass

class ErrorRangoColumna(Exception):
    pass

class ErrorRangoRenglon(Exception):
    pass

print("\n############################")
print("Problema 3.3")
print("############################\n")

print( "A = Matriz(n=3, m=4)" )
A = Matriz(n=3, m=4)
A.imprimir()

print( "A = A.elimRen(2)" )
A.elimRen(2)
A.imprimir()

B = Matriz(4,4,'diag')
print( "B = Matriz(4,4,’diag’)" )
B.imprimir()

C = Matriz(4,1,'unos')
print( "C = Matriz(4,1,'unos')" )
C.imprimir()

D = 3*B*C
print("D = 3*B*C")
D.imprimir()
print( "E = 3*B + C" )

try:
    E = 3*B + C
except ErrorDimension as err:
    print(str(err))
