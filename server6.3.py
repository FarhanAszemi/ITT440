import socket
import sys
import time
import errno
import math
from multiprocessing import Process

def calcLog(x):
	print(f"Calculating log({x})")
	x = int(x)
	try:
		answer = math.log(x)
	except:
		answer = "unable to be calculated. Please retry again.."

	return answer

def calcSqrt(x):
	print(f"Calculating square root of {x}")
	x = int(x)
	if(x >= 0):
		try:
			answer = math.sqrt(x)
		except:
			answer = "unable to be calculated. Please retry again.."
	else:
		answer = "unable to be calculated because it is a negative value."

	return answer

def calcExp(x):
	print(f"Calculating exponential of {x}")
	x = float(x)
	try:
		answer = math.exp(x)
	except:
		answer = "unable to be calculated. Please retry again.."

	return answer


def process_start(s_sock):
	s_sock.send(str.encode('Welcome to the Server\n'))
	while True:
		data = s_sock.recv(2048)

		data = data.decode('utf-8')
		try:
			option, value1 = data.split(" ", 2)
		except:
			print("Unable to calculate, client disconnected\n")

		if not data:
			break

		if(option == 'log'):
			answer = calcLog(value1)
		elif(option == 'sqrt'):
			answer = calcSqrt(value1)
		elif(option == 'exp'):
			answer = calcExp(value1)

		message = "[*] The answer is  %s." % str(answer)
		print("[*] Completed\n------------------------------------\n")
		s_sock.sendall(str.encode(message))

	s_sock.close()

if __name__ == '__main__':
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind(("", 8888))
	print("Listening for input from clients...")
	s.listen(3)
	try:
		while True:
			try:
				s_sock, s_addr = s.accept()
				p = Process(target = process_start, args = (s_sock,))
				p.start()

			except socket.error:
				print('Got a socket error')

	except Exception as e:
		print('An exception occured!')
		print(e) 
		sys.exit(1)

	finally:
		s.close()
