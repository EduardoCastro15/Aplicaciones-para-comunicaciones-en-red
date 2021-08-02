import threading
import time
import logging
import random


def GenerarArchivo(registros):
    i = 0
    file_of_numbers = open("random.txt", "w")
    while i < registros:
        file_of_numbers.write(str(random.randint(-1000, 1000))+'\n')
        i += 1
    file_of_numbers.close()


class SortByParts():
    def read_amount_of_lines(self, ammount_of_lines):
        i = 0
        result_array = []
        while i < ammount_of_lines:
            result_array.append(int(self.input_file.readline()))
            i += 1
        return result_array

    def worker(self):
        while True:
            if not self.lock_input_file.locked():
                self.lock_input_file.acquire()
                lines_to_read = self.lines_per_worker if self.carry == 0 else self.lines_per_worker + self.carry
                self.carry = 0
                array_to_sort = self.read_amount_of_lines(lines_to_read)
                self.lock_input_file.release()
                array_to_sort.sort()
                if not self.lock_output_file.locked():
                    self.lock_output_file.acquire()
                    for sorted_number in array_to_sort:
                        self.output_file.write(str(sorted_number)+'\n')
                    self.lock_output_file.release()
                    break
                else:
                    logging.debug("waiting to write")
                    time.sleep(self.sleepTime)
            else:
                logging.debug("waiting to read")
                time.sleep(self.sleepTime)

    def __init__(self, nthreads):
        self.lock_input_file = threading.Lock()
        self.lock_output_file = threading.Lock()
        self.barrier = threading.Barrier(nthreads)
        self.barrier = threading.Barrier(nthreads)
        self.input_file = open("random.txt", "r")
        self.output_file = open("randomSorted.txt", "w")
        file_lines = len(self.input_file.readlines())
        self.lines_per_worker = file_lines//nthreads
        self.input_file.seek(0)
        self.sleepTime = 1
        self.carry = file_lines % self.lines_per_worker
        workers = [threading.Thread(name='worker-%s' %
                                    i, target=self.worker) for i in range(nthreads)]
        for w in workers:
            w.start()
        for w in workers:
            w.join()
        self.input_file.close()
        self.output_file.close()


SortByParts(2)
