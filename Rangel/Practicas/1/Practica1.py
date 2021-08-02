"""
    Instituto Politécnico Nacional 
    Escuela Superior de Cómputo

    Práctica 1: Hilos 
    Aplicaciones para comunicaciones de red
    Profesor: Rangel González Josué


"""

import threading
import glob
import json

#Directorio en donde hará la busqueda en los archivos
directorioLibros="/home/omar/Escritorio/Libros/"
#Palabras a buscar en los archivos .txt
palabrasAContar={"jardín":0 , "pelota":0, "juego":0, "amor":0, "casa":0, "enojo":0}
globalCount={"jardín":0 , "pelota":0, "juego":0, "amor":0, "casa":0, "enojo":0}
totaldePalabras=0

class ThreadWithReturnValue(threading.Thread):
    def __init__(self, group=None, target=None, name=None,
                 args=(), kwargs={}, Verbose=None):
        threading.Thread.__init__(self, group, target, name, args, kwargs)
        self._return = None
    def run(self):
        if self._target is not None:
            self._return = self._target(*self._args, **self._kwargs)
    def join(self, *args):
        threading.Thread.join(self, *args)
        return self._return

#Conteo de palabras 
def wordCount(wordsToMatch, file, result, index):
    global totaldePalabras
    fileToRead=open(directorioLibros+file,"r",encoding="utf-8-sig")
    text=fileToRead.read().split()
    mydict=palabrasAContar.copy()
    for word in text:
        if word in mydict.keys():
            count=mydict[word]
            mydict[word]=count+1
            globalCount[word]+=1
            totaldePalabras=totaldePalabras+1
    result[index]=mydict

# Creamos los nuevos hilos 
txtCounter = len(glob.glob1(directorioLibros,"*.txt"))
print(txtCounter)
# Arreglo de Hilos
thread=[None]*txtCounter
#En este arreglo guardaremos los diccionarios de cada texto
results=[None]*txtCounter
txtFiles = []
for file in glob.glob1(directorioLibros,"*.txt"):
    txtFiles.append(file)
for i in range (0,txtCounter):
    thread[i] = ThreadWithReturnValue(target=wordCount, args=(palabrasAContar, txtFiles[i], results, i ) )
    # Iniciamos los hilos
    thread[i].start()
    thread[i].join()

#Hacemos el conteo
for i in range (0,txtCounter):
    thread[i].join()
    print("Texto: ",txtFiles[i],"palabras:")
    print (results[i])
    dictnAsString= json.dumps(results[i])
    print("")
print("El numero total de palabras es:",totaldePalabras )
print("\n")
print("El conteo global de palabras es:",globalCount )
print("\n")

#Obtenemos el promedio de las palabras a encontar
for word in globalCount.keys():
    globalCount[word]=float(globalCount[word]/totaldePalabras)
print("El promedio es de:", globalCount)
dictnAsString= json.dumps(globalCount)
