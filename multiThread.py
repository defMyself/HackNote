import threading
import time

def func():
	print("func is running...")
	time.sleep(1)

if __name__ == "__main__":

	time_start = time.time()

	for i in range(100):
		t = threading.Thread(target=func)
		t.start()

	time_start = time.time()

	print('time cost', time_end - time_start, 's')
	func()

	
