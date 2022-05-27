from socket import *
import hashlib
import os
serverPort = 10000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))
print('The server is ready to receive')
serverName = 'localhost'
a_receive = 20000
f2_node = 11000

HashList = ["000000000000000000000000", "000000000000000000000000", "000000000000000000000000", "000000000000000000000000"]
nonce = 0
Empty = ""
LB = "0000000000000000000000000000000000000000000000000000000000000000"


def Hashing(Tx, Nonce, LastBlock, MerkleRoot): #hashes the things in parameter all togehter
    hashHandler = hashlib.sha256() #length of hash number 256 bits 32-byte HEX
    nonce = 0 #nonce
    while True: #infinte loop
        block_header = Tx + Nonce + LastBlock + MerkleRoot#the thing being hashed
        hashHandler.update(block_header.encode("utf-8")) #encode
        hashValue = hashHandler.hexdigest() #contain only HEX numbers
        #print('nonce:{0}, hash:{1}'.format(nonce, hashValue)) #print format
        nounceFound = True
        for i in range(4): #amount of leading zeros
            if hashValue[i]!='0': #leading number
                nounceFound = False
        if nounceFound: #escapes once leading 4 zeros
            if(Tx == ""):
                print("made it 1")
                f = open('blockchain_f1.txt', 'a')
                f.write(str(nonce) + " " + LastBlock + " " + MerkleRoot + " ")
                f.close()
            break
        else: #keeps going in loop until leading 4 zeros
            nonce = nonce + 1
    return hashValue


with open("balancesF.txt", 'w') as writer:#writes to balance a empty amount for both
    message = "0xF0000001 0x00000000 0xF0000002 0x00000000"
    writer.write(message)

with open("temp_tx_f1.txt", "w") as writer:
    writer.write(" ")

with open("blockchain_f1.txt", "w") as writer:
    writer.write(" ")

num_of_tx = 0
num_of_blocks = 0


def tx_check(tx_list):
    if tx_list[0:10] == "0xA0000001" or tx_list[0:10] == "0xA0000002" or tx_list[0:10] == "0xB0000001" or tx_list[0:10] == "0xB0000002":
        return True
    return False


def send_to_node(node_message):
    serverSocket.sendto(node_message.encode(), (serverName, f2_node))


def send_to_client(client_message):
    serverSocket.sendto(client_message.encode(), (serverName, a_receive))


while 1:
    message, clientAddress = serverSocket.recvfrom(2048)
    modifiedMessage = message.decode()

    # if from other node
    if clientAddress[1] == f2_node:
        print("from f2")
        print(modifiedMessage)
        # if it is a transaction
        if tx_check(modifiedMessage):
            print("this is a transaction")

            # appends to the temp transaction file
            with open("temp_tx_f1.txt", "a") as ap:
                ap.write(modifiedMessage + " ")
                num_of_tx += 1
                if num_of_tx % 4 == 0:
                    num_of_blocks += 1
                    with open("temp_tx_f1.txt", "r") as reader:
                        message = reader.read()
                        send_to_client(message)
            print(f"{num_of_tx} {num_of_blocks}")

            # if it is this nodes turn to mine a block
            if num_of_blocks % 2 == 1 and num_of_tx%4 == 0:
                print("Beginning mine...")
                with open("temp_tx_f1.txt", "r") as reader:
                    temp_txs = reader.read().split(" ")
                with open("temp_tx_f1.txt", "w") as writer:
                    writer.write(" ")

                # mining function goes here
                i = 0
                while i < 4:
                    HashList[i] = Hashing(temp_txs[i], Empty, Empty, Empty)
                    i += 1

                A = HashList[0]
                B = HashList[1]
                C = HashList[2]
                D = HashList[3]
                AB = A + B
                CD = C + D
                AB = Hashing(AB, Empty, Empty, Empty)
                CD = Hashing(CD, Empty, Empty, Empty)
                ABCD = AB + CD
                ABCD = Hashing(ABCD, Empty, Empty, Empty)

                if os.stat("blockchain_f1.txt").st_size != 0:
                    with open('blockchain_f1.txt', 'r') as reader:
                        BlockChain = reader.read().split(" ")
                        NUMELEMS = len(BlockChain)
                        LB = BlockChain[NUMELEMS - 2]

                Hashing(Empty, str(nonce), LB, ABCD)

                # updates the account with the appropriate amount of BC
                with open("balancesF.txt", "r") as reader:
                    account_balances = reader.read().split(" ")
                    index = 0
                    for accounts in account_balances:
                        if accounts == "0xF0000001":
                            account_balances[index + 1] = hex(int(account_balances[index + 1], 16) + 38)
                            with open("balancesF.txt", "w") as writer:
                                for lines in account_balances:
                                    writer.write(lines + " ")
                        else:
                            index += 1
                with open("blockchain_f1.txt", 'r') as reader:
                    tx_block = reader.read()
                    send_to_node(tx_block)
        else:
            print("must be block")
            with open("blockchain_f1.txt", "a") as ap:
                print("coolio")
                ap.write(modifiedMessage)

    # if from the client
    else:
        print("from client")

        #append to the temp transaction file
        with open("temp_tx_f1.txt", "a") as ap:
            ap.write(modifiedMessage)
            num_of_tx += 1
            if num_of_tx%4 == 0:
                num_of_blocks += 1
                with open("temp_tx_f1.txt", "r") as reader:
                    message = reader.read()
                    send_to_client(message)
        send_to_node(modifiedMessage)
        print(f"{num_of_tx} {num_of_blocks}")

        if num_of_blocks%2 == 1 and num_of_tx%4 == 0:
            print("Beginning mine...")
            with open("temp_tx_f1.txt", "r") as reader:
                temp_txs = reader.read().split(" ")
            with open("temp_tx_f1.txt", "w") as writer:
                writer.write(" ")

            # mining function goes here
            i = 0
            while i < 4:
                HashList[i] = Hashing(temp_txs[i], Empty, Empty, Empty)
                i += 1

            A = HashList[0]
            B = HashList[1]
            C = HashList[2]
            D = HashList[3]
            AB = A + B
            CD = C + D
            AB = Hashing(AB, Empty, Empty, Empty)
            CD = Hashing(CD, Empty, Empty, Empty)
            ABCD = AB + CD
            ABCD = Hashing(ABCD, Empty, Empty, Empty)

            if os.stat("blockchain_f1.txt").st_size != 0:
                print("made it 2")
                with open('blockchain_f1.txt', 'r') as reader:
                    BlockChain = reader.read().split(" ")
                    NUMELEMS = len(BlockChain)
                    LB = BlockChain[NUMELEMS - 2]

            Hashing(Empty, str(nonce), LB, ABCD)
            print("made it 3")
            with open("balancesF.txt", "r") as reader:
                account_balances = reader.read().split(" ")
                index = 0
                for accounts in account_balances:
                    if accounts == "0xF0000001":
                        account_balances[index + 1] = hex(int(account_balances[index + 1], 16) + 38)
                        with open("balancesF.txt", "w") as writer:
                            for lines in account_balances:
                                writer.write(lines + " ")
                    else:
                        index += 1
            with open("blockchain_f1.txt", 'r') as reader:
                tx_block = reader.read()
            send_to_node(tx_block)

            # send block to other node here
            # print block here