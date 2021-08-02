import threading
import time
import logging
import random

class SortByParts():
    def consumer(self, nt):
        while True:
            i = 0
            free = -1
            for l in self.lock_consumers:
                if not l.locked():
                    free = i
                    l.acquire()
                    break
                if free >= 0:
                    self.output_file.write(self.critical_regions[free][0])
                    self.total_productions[free] -= 1
                    self.lock_producers[free].release()

    def producer(self, nt):
        while True:
            i = 0
            free = -1
            for l in self.lock_producers:
                if not l.locked():
                    free = i
                    l.acquire()
                    break
                i += 1
            if free >= 0:
                to_produce = ""
                if nt == 0:
                    to_produce = "aaaaa\n"
                elif nt == 1:
                    to_produce = "bbbbb\n"
                elif nt == 2:
                    to_produce = "ccccc\n"
                elif nt == 3:
                    to_produce = "ddddd\n"
                elif nt == 4:
                    to_produce = "eeeee\n"
                elif nt == 5:
                    to_produce = "fffff\n"
                elif nt == 6:
                    to_produce = "ggggg\n"
                self.critical_regions[free].append(to_produce)
                self.remaining_productions[free] -= 1
                self.lock_consumers[free].release()

    def __init__(self, nthreads=6):
        self.lock_producers = [threading.Lock() for i in range(0, 6)]
        self.lock_consumers = [threading.Lock() for i in range(0, 6)]
        self.lock_output_file = threading.Lock()
        self.barrier = threading.Barrier(nthreads)
        self.critical_regions = [[], [], [], [], [], []]
        self.remaining_productions = [100000 for i in range(7)]
        self.output_file = open("resultFile.txt", "w")
        producers = [threading.Thread(
            name='producer-%s' % i, target=self.producer, args=(i,)) for i in range(nthreads)]
        consumers = [threading.Thread(
            name='consumer-%s' % i, target=self.consumer, args=(i,)) for i in range(nthreads)]
		for w in producers:
            w.start()
        for w in consumers:
			w.start()
		for w in producers:
            w.join()
        for w in consumers:
            w.join()
        self.output_file.close()


# GenerarArchivo(500000)
SortByParts()
