# 1.1 --- 
# Vamos a generar 3 listas que parecerían iguales
lista_1 = [1, 2, 3, "toto", ["a", "b", "c"]]
lista_2 = lista_1
lista_3 = lista_1[:]

lista_2[0] = "XXX"
print(lista_2)

# Coloca lo que piensas que debería salir con
# print(lista_1)  -->  
# print(lista_3)  -->  

# Ejemplo:
# print(lista_2)  -->  ['XXX', 2, 3, 'toto', ['a', 'b', 'c']

lista_3[-1][0] = 1000
print(lista_3)

# Coloca lo que piensas que debería salir con
# print(lista_1)  -->
# print(lista_2)  -->

# Ejemplo:
# print(lista_3)  -->  [1, 2, 3, 'toto', [1000, 'b', 'c']]

# Ahora ejecuta los programas y revisa lo que sale de acuerdo a lo que pusiste
# y explica porqué pasa de esa manera.

# 1.2 ---
class coordenadas:
    def __init__(self, x=0, y=0):
        "Inicializa un objet coordenadas"
        self.x = x
        self.y = y

    def __str__(self):
        return "\n\tCoordenada x = {}\n\tCoordenada y = {}".format(self.x, self.y)


a = coordenadas(3, 4)
b = a
b.x = 100

print("b = " + str(b))

# Coloca aqui lo que crees que saldrá si se ejecuta
# print("a = " + str(a))

#  2.1 --

a = [x for x in range(1, 1001) if x % 2 == x % 3 == x % 5 == x % 7 == 0]
b = [x for x in range(1, 1001) if x % (2 * 3 * 5 * 7) == 0]
print(a)
print(b)


# 2.2 --

def histo_lista(lista, imprime=False):
    salida = {elemento: lista.count(elemento) for elemento in set(lista)}
    if imprime:
        total = len(lista)
        for (elemento, veces) in salida.items():
            print("{}\t\t{}\t\t({:d} -> {:.2f}%)".format(str(elemento),
                                                         '*'*veces,
                                                         veces,
                                                         100 * veces / total))
    return salida


# 2.3 ---

def fun_dicos(diccionario, elemento, posicion, valor):
    dic2 = {lab: lista[:] for (lab, lista) in diccionario.items()}
    dic2[elemento][posicion] = valor
    return dic2

# 3.1 ---


def es_primo(x):
    """
    Identfica si un número es primo

    """
    if x % 2 == 0:
        return False
    for a in range(3, int(x**(1/2)), 2):
        if x % a == 0:
            return False
    return True


def proximo_primo(n):
    """
    Encuentra el próximo numero primo

    """
    for x in range(n+1, n**4):
        if es_primo(x):
            return x
    ValueError("No se encontró un primo entre {:d} y {:d}".format(n + 1, n**4))

    
def fun_range(funcion, n):
    """
    Evalua la función funcion en un rango de 1 a n 
    y la devuelve como una lista

    """
    return [funcion(x) for x in range(n)]
