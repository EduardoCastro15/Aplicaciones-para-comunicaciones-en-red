import threading


class ProducersConsumers():
    def produce_in_critical(self, free, production):
        if free == 0:
            self.critical_region1 = production
        elif free == 1:
            self.critical_region2 = production
        elif free == 2:
            self.critical_region3 = production

    def consume_from_critical(self, free):
        if free == 0:
            return self.critical_region1
        elif free == 1:
            return self.critical_region2
        elif free == 2:
            return self.critical_region3

    def check_if_left(self):
        counter_finish = 0
        for remaining in self.remaining_productions:
            if remaining == 0:
                counter_finish += 1
        return counter_finish == 5

    def check_consumes(self, to_check):
        if to_check == "11111111":
            return 0
        elif to_check == "22222222":
            return 1
        elif to_check == "33333333":
            return 2
        elif to_check == "44444444":
            return 3
        elif to_check == "55555555":
            return 4

    def consumer(self, nt):
        while True:
            i = 0
            free = -1
            for l in self.lock_consumers:
                if not l.locked():
                    free = i
                    l.acquire()
                    break
                i += 1
            if free >= 0:
                print("Soy el consumidor " + str(nt) + " consumi " + self.consume_from_critical(free) + " en la zona " + str(free))
                self.lock_producers[free].release()
            if self.check_if_left():
                break

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
                if nt == 0 and self.remaining_productions[nt] > 0:
                    to_produce = "11111111"
                elif nt == 1 and self.remaining_productions[nt] > 0:
                    to_produce = "22222222"
                elif nt == 2 and self.remaining_productions[nt] > 0:
                    to_produce = "33333333"
                elif nt == 3 and self.remaining_productions[nt] > 0:
                    to_produce = "44444444"
                elif nt == 4 and self.remaining_productions[nt] > 0:
                    to_produce = "55555555"
                print("Soy el productor " + str(nt) + " produje " + to_produce + " en la zona " + str(free))
                self.produce_in_critical(free, to_produce)
                self.remaining_productions[nt] -= 1
                self.lock_consumers[free].release()
            if self.remaining_productions[nt] <= 0:
                break

    def __init__(self):
        self.lock_producers = [threading.Lock() for i in range(3)]
        self.lock_consumers = [threading.Lock() for i in range(3)]
        for lc in self.lock_consumers:
            lc.acquire()
        self.lock_output_file = threading.Lock()
        # self.barrier = threading.Barrier(nthreads)
        self.critical_region1 = ""
        self.critical_region2 = ""
        self.critical_region3 = ""
        self.remaining_productions = [50 for i in range(5)]
        producers = [threading.Thread(
            name='producer-%s' % i, target=self.producer, args=(i,)) for i in range(5)]
        consumers = [threading.Thread(
            name='consumer-%s' % i, target=self.consumer, args=(i,)) for i in range(2)]
        for w in producers:
            w.start()
        for w in consumers:
            w.start()
        for w in producers:
            w.join()
        for w in consumers:
            w.join()


ProducersConsumers()
