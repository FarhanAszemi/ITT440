import socket


ClientSocket = socket.socket()
host = '192.168.56.6'
port = 8888

print('Waiting for connection')
try:
	ClientSocket.connect((host, port))
except socket.error as e:
	print(str(e))

Response =ClientSocket.recv(1024)
print(Response)

while True:

	answer = 0
	while(answer == 0):
		option = input('Enter type of operation [log / sqrt / exp]: ')
		if(option == 'log'):
			value1 = input("Enter your value: ")
			answer = 1
		elif(option == 'sqrt'):
			value1 = input("Enter your value: ")
			answer = 1
		elif(option == 'exp'):
			value1 = input("Enter your value: ")
			answer = 1
		else:
			print("Invalid operation, please re-enter..")
			answer = 0
			
		

	Input = option + " " +  value1
	ClientSocket.send(str.encode(Input))
	Response = ClientSocket.recv(1024)
	print(Response.decode('utf-8'))
	print("\n")

ClientSocket.close()
